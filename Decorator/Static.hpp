#ifndef STATIC_HPP
#define STATIC_HPP

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

using namespace std;

namespace Static {

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


// Static decorator 1
template < typename T > struct ColoredShape : public T
{
   static_assert(is_base_of< Shape, T >::value, "Template argument must be a Shape");

   string color;

   // Forwarding constructor
   template < typename... Args > ColoredShape(std::string c, Args... args) : T(std::forward< Args >(args)...), color(std::move(c))
   {
   }

   std::string
   str() const override
   {
      std::stringstream ss;
      ss << color << ' ' << T::str();

      return ss.str();
   }
};


// Static decorator 2
template < typename T > struct TransparentShape : public T
{
   static_assert(is_base_of< Shape, T >::value, "Template argument must be a Shape");

   int trsp;

   // Forwarding constructor
   template < typename... Args > TransparentShape(int t, Args... args) : T(std::forward< Args >(args)...), trsp(t)
   {
   }

   std::string
   str() const override
   {
      std::stringstream ss;
      ss << T::str() << " with " << trsp << "% transparency";

      return ss.str();
   }
};

} // namespace Static

#endif // STATIC_HPP
