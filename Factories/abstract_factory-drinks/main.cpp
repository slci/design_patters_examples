#include <HotDrinkFactory.hpp>

int
main()
{
   HotDrinkFactory&& machine = CoffeeMachine{};

   auto drink = machine.makeDrink(200);

   return 0;
}
