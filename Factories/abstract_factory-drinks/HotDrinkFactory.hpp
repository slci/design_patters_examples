#ifndef HOTDRINKFACTORY_HPP
#define HOTDRINKFACTORY_HPP

#include "HotDrink.hpp"

#include <memory>

struct HotDrinkFactory
{
   virtual std::unique_ptr< HotDrink >
   makeDrink(int const vol) = 0;
};


struct TeaMachine : public HotDrinkFactory
{
   std::unique_ptr< HotDrink >
   makeDrink(int const vol)
   {
      auto tea = std::make_unique< Tea >();
      tea->prepare(vol);
      return tea;
   }
};

struct CoffeeMachine : public HotDrinkFactory
{
   std::unique_ptr< HotDrink >
   makeDrink(int const vol)
   {
      auto coffee = std::make_unique< Coffee >();
      coffee->prepare(vol);
      return coffee;
   }
};

#endif // HOTDRINKFACTORY_HPP
