#ifndef HOTDRINK_HPP
#define HOTDRINK_HPP

#include <iostream>

struct HotDrink
{
   virtual ~HotDrink() = default;

   virtual void
   prepare(int volume) = 0;
};


struct Tea : public HotDrink
{
   void
   prepare(int volume) override
   {
      std::cout << "Preparing " << volume << " ml of tea\n";
   }
};


struct Coffee : public HotDrink
{
   void
   prepare(int volume) override
   {
      std::cout << "Preparing " << volume << " ml of coffee\n";
   }
};

#endif // HOTDRINK_HPP
