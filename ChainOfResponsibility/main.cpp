#include <iostream>

#include "PointerChain.hpp"

int
main()
{
   pointer_chain::Creature goblin{"Goblin", 7, 1};
   std::cout << goblin;

   pointer_chain::CreatureModifier root{goblin};
   pointer_chain::DoubleAttackModifier r1{goblin};
   pointer_chain::DoubleAttackModifier r1_2{goblin};
   pointer_chain::IncreasedDefenceModifier r2{goblin};

   pointer_chain::NoBonusModifier curse{goblin};

   root.add(r1);
   root.add(r1_2);
   root.add(curse); // break the chain of resp.
   root.add(r2);

   root.handle();

   std::cout << goblin;

   return 0;
}
