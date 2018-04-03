#include <iostream>

class Rectangle
{
 public:
   explicit Rectangle(int const w, int const h) : width_(w), height_(h)
   {
   }

   int
   area() const
   {
      return width_ * height_;
   }

   int
   width() const
   {
      return width_;
   }

   int
   height() const
   {
      return height_;
   }

   virtual void
   setWidht(int const w)
   {
      width_ = w;
   }

   virtual void
   setHeight(int const h)
   {
      height_ = h;
   }

 protected:
   int width_;
   int height_;
};


struct Square : public Rectangle
{
   explicit Square(int const size) : Rectangle(size, size)
   {
   }

   void
   setWidht(int const w) override
   {
      width_ = w;
      height_ = w;
   }

   void
   setHeight(int const h) override
   {
      height_ = h;
      width_ = h;
   }
};


void
process(Rectangle& r)
{
   int w = r.width();
   r.setHeight(10);

   std::cout << "Expected area: " << (w * 10) << " got: " << r.area() << std::endl;
}

int
main()
{
   auto r = Rectangle{15, 13};
   process(r);

   auto s = Square{5};
   process(s);
}
