#ifndef DYNAMIC_HPP
#define DYNAMIC_HPP

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

using namespace std;

namespace Dynamic {

struct Shape
{
   virtual std::string
   str() const = 0;
};

struct Circle : public Shape
{
   float radius;

   Circle(float r) : radius(r)
   {
   }

   void
   resize(float factor)
   {
      radius *= factor;
   }

   virtual std::string
   str() const override
   {
      std::stringstream ss;
      ss << "Circle r: " << radius;

      return ss.str();
   }
};

struct Rectangle : public Shape
{
   float x, y;

   Rectangle(float x_, float y_) : x(x_), y(y_)
   {
   }

   virtual std::string
   str() const override
   {
      std::stringstream ss;
      ss << "Rectangle x: " << x << " y:" << y;

      return ss.str();
   }
};


// Decorator 1
struct ColoredShape : public Shape
{
   std::unique_ptr< Shape > shape;
   std::string color;

   ColoredShape(std::unique_ptr< Shape > s, std::string c) : shape(std::move(s)), color(std::move(c))
   {
   }

   virtual std::string
   str() const override
   {
      std::stringstream ss;
      ss << color << ' ' << shape->str();

      return ss.str();
   }
};


// Decorator 2
struct TransparentShape : public Shape
{
   std::unique_ptr< Shape > shape;
   int trsp;

   TransparentShape(std::unique_ptr< Shape > s, int t) : shape(std::move(s)), trsp(t)
   {
   }

   virtual std::string
   str() const override
   {
      std::stringstream ss;
      ss << shape->str() << " with " << trsp << "% transparency";

      return ss.str();
   }
};

} // namespace Dynamic

#endif // DYNAMIC_HPP
