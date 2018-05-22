#include "CommunicationProxy.hpp"
#include "PropertyProxy.hpp"
#include "VirtualProxy.hpp"

struct Creature
{
   Property< int > strength;
   Property< int > agility;
};

using namespace std;

int
main()
{
   // Property Proxy test
   Creature c;

   c.agility = 123;
   c.strength = 321;

   std::cout << c.agility << ' ' << c.strength << std::endl;


   // Virtual Proxy test
   auto img1 = virtual_proxy::LazyBitmap{"a picture 1"};
   auto img2 = virtual_proxy::LazyBitmap{"a picture 2"};
   img2.draw();
   img1.draw();
   img1.draw();


   // Communication Proxy test
   communication_proxy::RemoteService rs("some service");

   for (size_t i = 0; i < 3; ++i)
   {
      communication_proxy::tryit(rs);
   }
}
