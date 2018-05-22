#ifndef VIRTUALPROXY_HPP
#define VIRTUALPROXY_HPP
#include <iostream>
#include <memory>

namespace virtual_proxy {

struct Image
{
   Image() = default;
   virtual ~Image() = default;

   virtual void
   draw() = 0;
};

struct Bitmap : Image
{
   Bitmap(std::string const& filename)
   {
      std::cout << "Loading bitmap from " << filename << "\n";
   }

   void
   draw() override
   {
      std::cout << "Drawing a bitmap\n";
   }
};


struct LazyBitmap : Image
{
   LazyBitmap(std::string const& file) : filename(file)
   {
   }

   void
   draw() override
   {
      if (!bmp)
      {
         bmp = std::make_unique< Bitmap >(filename);
      }

      bmp->draw();
   }

 private:
   std::string filename;
   std::unique_ptr< Bitmap > bmp{nullptr};
};

} // namespace virtual_proxy

#endif // VIRTUALPROXY_HPP
