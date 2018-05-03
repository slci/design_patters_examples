#include "Dynamic.hpp"
#include "Static.hpp"

using namespace std;

int
main()
{
   // Dynamic decorators test
   auto c = std::make_unique< Dynamic::Circle >(123.0f);
   auto rc = std::make_unique< Dynamic::ColoredShape >(std::move(c), "Red");
   auto trc = std::make_unique< Dynamic::TransparentShape >(std::move(rc), 20);

   std::cout << trc->str() << std::endl;
   //   trc->resize(2.0f); Can't! The Circle API is lost when decorated :(

   auto trc2 = Static::TransparentShape< Static::ColoredShape< Static::Circle > >(30, "Purple", 3.1415f);

   std::cout << trc2.str() << std::endl;

   // We can access the full Circle API! :D
   trc2.resize(2.0f);
   std::cout << trc2.str() << std::endl;

   // Static decorators test
}
