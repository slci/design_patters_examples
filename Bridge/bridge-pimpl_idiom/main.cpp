#include <Person.hpp>
#include <iostream>

/**
 * @brief The Renderer struct
 */
struct Renderer
{
   virtual void
   render_circle(float x, float y, float radius) = 0;
};

/**
 * @brief The VectorRenderer struct
 */
struct VectorRenderer : Renderer
{
   void
   render_circle(float x, float y, float radius) override
   {
      std::cout << "Drawing a vector circle of radius " << radius << " in x:" << x << " y:" << y << std::endl;
   }
};

/**
 * @brief The RasterRenderer struct
 */
struct RasterRenderer : Renderer
{
   void
   render_circle(float x, float y, float radius) override
   {
      std::cout << "Rasterizing a circle of radius " << radius << " in x:" << x << " y:" << y << std::endl;
   }
};

/**
 * @brief The Shape struct
 */
struct Shape
{
 protected:
   Renderer& renderer;

   Shape(Renderer& r) : renderer(r)
   {
   }

 public:
   virtual void
   draw() = 0;

   virtual void
   resize(float const factor) = 0;
};

/**
 * @brief The Circle struct
 */
struct Circle : public Shape
{
   float x, y, r;

   Circle(Renderer& renderer, float x, float y, float radius) : Shape(renderer), x(x), y(y), r(radius)
   {
   }

 public:
   void
   draw() override
   {
      renderer.render_circle(x, y, r);
   }
   void
   resize(const float factor) override
   {
      r *= factor;
   }
};

int
main()
{
   // PIMPL test
   Person p{"Sławek"};
   p.greet();


   // Renderer test
   RasterRenderer rr;
   Circle c1(rr, 1.f, 1.f, 3.14f);

   c1.draw();
}
