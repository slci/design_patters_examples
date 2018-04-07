#include <cmath>
#include <iostream>

class Point
{
 public:
   friend std::ostream&
   operator<<(std::ostream& os, Point const& point)
   {
      os << "(x:" << point.x << ", y:" << point.y << ')';
      return os;
   }

   class Factory
   {
    public:
      Factory() = delete;

      static Point
      newCartesianPoint(double x, double y)
      {
         return Point{x, y};
      }

      static Point
      newPolar(double r, double theta)
      {
         return Point{r * std::cos(theta), r * std::sin(theta)};
      }
   };

 private:
   Point(double x_, double y_) : x(x_), y(y_)
   {
   }

   double x, y;
};


int
main()
{
   auto p = Point::Factory::newPolar(5.0, M_PI_4);
   std::cout << "New point: " << p << std::endl;
   return 0;
}
