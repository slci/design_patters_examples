#include <iostream>
#include <memory>
#include <string>
#include <vector>

enum class Size
{
   tiny,
   small,
   medium,
   large,
   huge
};

enum class Color
{
   red,
   green,
   blue,
   yellow,
   orange,
   white,
   black
};

struct Product
{
   std::string name;
   Size size;
   Color color;
};


template < typename T > struct Specification
{
   virtual bool
   isSatisfied(T const& item) const = 0;
};


template < typename T > struct Filter
{
   explicit Filter(std::unique_ptr< const Specification< T > > s) : spec(std::move(s))
   {
   }

   std::vector< const T* >
   applyOn(std::vector< T > const& items) const
   {
      std::vector< const T* > result;
      for (auto const& item : items)
      {
         if (spec->isSatisfied(item))
         {
            result.push_back(&item);
         }
      }

      return result;
   }

   std::unique_ptr< const Specification< T > > spec;
};


struct ColorSpecification : public Specification< Product >
{
   explicit ColorSpecification(Color const color) : colorSpec(color)
   {
   }

   bool
   isSatisfied(Product const& item) const override
   {
      return (item.color == colorSpec);
   }

   Color colorSpec;
};


struct SizeSpecification : public Specification< Product >
{
   explicit SizeSpecification(Size const size) : sizeSpec(size)
   {
   }

   bool
   isSatisfied(Product const& item) const override
   {
      return (item.size == sizeSpec);
   }

   Size sizeSpec;
};

struct SizeAndColorSpecification : public Specification< Product >
{
   explicit SizeAndColorSpecification(Size const s, Color const c) : size(s), color(c)
   {
   }

   bool
   isSatisfied(Product const& item) const override
   {
      return ((item.size == size) && (item.color == color));
   }

   Size const size;
   Color const color;
};


int
main()
{
   std::vector< Product > products{{"Apple", Size::small, Color::red},     {"Watermelon", Size::medium, Color::green},
                                   {"Carrot", Size::small, Color::orange}, {"Lemon", Size::small, Color::yellow},
                                   {"Cabbage", Size::large, Color::green}, {"Cherry", Size::small, Color::red}};


   auto spec = std::make_unique< SizeAndColorSpecification >(Size::small, Color::red);
   auto filter = Filter< Product >{std::move(spec)};

   for (auto const p : filter.applyOn(products))
   {
      std::cout << p->name << " is red and small\n";
   }
}
