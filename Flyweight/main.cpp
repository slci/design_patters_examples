#include "BoostFlyweight.hpp"
#include "HandMadeFlyweigth.hpp"
#include "TextFormatting.hpp"


int
main()
{
   // Hand made flyweigth test
   hand_made::User u1{"John", "Doe"};
   hand_made::User u2{"John", "Smith"};

   assert(&u1.firstName() == &u2.firstName());
   assert(&u1.lastName() != &u2.lastName());

   std::cout << u1 << std::endl << u2 << std::endl;


   // Boost flyweigth test
   boost_flyweigth::User u3{"Marta", "Głuchowska"};
   boost_flyweigth::User u4{"Marta", "Dębska"};

   assert(&u3.firstName() == &u4.firstName());
   assert(&u3.lastName() != &u4.lastName());

   std::cout << u3 << std::endl << u4 << std::endl;

   text_fmt::BetterFormattedText text{"SomeCamelCaseText"};

   std::cout << text << "\n";
   text.getRange(4, 8).capitalize = true;
   std::cout << text << "\n";
}
