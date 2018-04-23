#include <boost/functional/hash.hpp>
#include <iostream>
#include <memory>
#include <vector>

struct Point
{
   int x, y;

   friend std::size_t
   hash_value(Point const& p)
   {
      std::size_t seed = 0x123456F;
      boost::hash_combine(seed, p.x);
      boost::hash_combine(seed, p.y);
      return seed;
   }
};

struct PointsObject
{
   virtual std::vector< Point >::const_iterator
   begin() const = 0;

   virtual std::vector< Point >::const_iterator
   end() const = 0;
};


struct Line
{
   Point start, end;

   friend std::size_t
   hash_value(Line const& l)
   {
      std::size_t seed = 0x543210F;
      boost::hash_combine(seed, l.start);
      boost::hash_combine(seed, l.end);
      return seed;
   }
};


struct VectorObject
{
   virtual std::vector< Line >::const_iterator
   begin() const = 0;

   virtual std::vector< Line >::const_iterator
   end() const = 0;

   virtual ~VectorObject() = default;
};


struct VectorRectangle : public VectorObject
{
   VectorRectangle(int x, int y, int width, int height)
   {
      lines.emplace_back(Line{Point{x, y}, Point{x + width, y}});
      lines.emplace_back(Line{Point{x + width, y}, Point{x + width, y + height}});
      lines.emplace_back(Line{Point{x, y}, Point{x, y + height}});
      lines.emplace_back(Line{Point{x, y + height}, Point{x + width, y + height}});
   }

   std::vector< Line >::const_iterator
   begin() const override
   {
      return lines.cbegin();
   }


   std::vector< Line >::const_iterator
   end() const override
   {
      return lines.cend();
   }

   virtual ~VectorRectangle() = default;

 private:
   std::vector< Line > lines;
};


struct VectorObj2PointsAdapter : public PointsObject
{
   explicit VectorObj2PointsAdapter(VectorObject const& obj)
   {
      for (auto const& line : obj)
      {
         add_line(line);
      }
   }

   virtual std::vector< Point >::const_iterator
   begin() const override
   {
      return points.cbegin();
   }

   virtual std::vector< Point >::const_iterator
   end() const override
   {
      return points.cend();
   }

 private:
   void
   add_line(Line const& line)
   {
      static int count = 0;
      std::cout << count++ << ": Generating points for line (no caching)\n";

      // no interpolation
      int left = std::min(line.start.x, line.end.x);
      int right = std::max(line.start.x, line.end.x);
      int top = std::min(line.start.y, line.end.y);
      int bottom = std::max(line.start.y, line.end.y);

      int dx = right - left;
      int dy = bottom - top;

      // only vertical or horizontal lines support
      if (dx == 0 && dy != 0) // vertical
      {
         for (int y = top; y <= bottom; ++y)
         {
            points.emplace_back(Point{left, y});
         }
      }
      else if (dx != 0 && dy == 0) // horizontal
      {
         for (int x = top; x <= right; ++x)
         {
            points.emplace_back(Point{x, top});
         }
      }
   }

   std::vector< Point > points;
};


struct VectorObj2PointsCachingAdapter : public PointsObject
{
   explicit VectorObj2PointsCachingAdapter(VectorObject const& obj)
   {
      for (auto const& line : obj)
      {
         boost::hash< Line > hash;
         auto line_hash = hash(line);

         auto cached_line = cache.find(line_hash);
         if (cached_line != cache.cend())
         {
            points.insert(points.end(), cached_line->second.begin(), cached_line->second.end());
         }
         else
         {
            add_line(line, line_hash);
         }
      }
   }

   virtual std::vector< Point >::const_iterator
   begin() const override
   {
      return points.cbegin();
   }

   virtual std::vector< Point >::const_iterator
   end() const override
   {
      return points.cend();
   }

 private:
   void
   add_line(Line const& line, std::size_t line_hash)
   {
      static int count = 0;
      std::cout << count++ << ": Generating points for line (no caching)\n";

      // no interpolation
      int left = std::min(line.start.x, line.end.x);
      int right = std::max(line.start.x, line.end.x);
      int top = std::min(line.start.y, line.end.y);
      int bottom = std::max(line.start.y, line.end.y);

      int dx = right - left;
      int dy = bottom - top;

      std::vector< Point > points;

      // only vertical or horizontal lines support
      if (dx == 0 && dy != 0) // vertical
      {
         for (int y = top; y <= bottom; ++y)
         {
            points.emplace_back(Point{left, y});
         }
      }
      else if (dx != 0 && dy == 0) // horizontal
      {
         for (int x = top; x <= right; ++x)
         {
            points.emplace_back(Point{x, top});
         }
      }

      cache[line_hash] = points;
   }

   static std::map< size_t, std::vector< Point > > cache;
   std::vector< Point > points;
};

std::map< size_t, std::vector< Point > > VectorObj2PointsCachingAdapter::cache{};

struct IDrawer
{
   virtual void
   drawPoints(PointsObject const&) = 0;

   virtual ~IDrawer() = default;
};

struct DrawerImpl : public IDrawer
{
   void
   drawPoints(PointsObject const& obj) override
   {
      (void)obj;
      std::cout << "Drawing points by DrawerImpl..\n";
   }

   virtual ~DrawerImpl() = default;
};


int
main()
{
   std::vector< std::unique_ptr< VectorObject > > vectorObjects;
   vectorObjects.emplace_back(std::make_unique< VectorRectangle >(10, 10, 100, 100));
   vectorObjects.emplace_back(std::make_unique< VectorRectangle >(30, 30, 60, 60));

   std::unique_ptr< IDrawer > drawer = std::make_unique< DrawerImpl >();

   for (int n = 0; n < 5; ++n)
   {
      for (auto const& obj : vectorObjects)
      {
         // Can't draw vector objects! only raw points...
         // drawer->drawPoints(*obj);
         auto points = VectorObj2PointsCachingAdapter(*obj);
         drawer->drawPoints(points);
      }
   }

   return 0;
}
