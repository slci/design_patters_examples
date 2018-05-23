#include <iostream>

#include "BrokerChain.hpp"
#include "PointerChain.hpp"

int
main()
{
   // Pointer chain test
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


   // Broker Chain test
   broker::Game game;
   broker::Creature ogre{game, "Ogre", 1, 1};
   {
      broker::IncreasedDefenseModifier idm1{game, ogre}; // As long as modifiers live, ogre is stronger!
      std::cout << ogre << "\n";

      {
         broker::DoubleAttackModifier dam{game, ogre};
         broker::IncreasedDefenseModifier idm2{game, ogre};
         std::cout << ogre << "\n";
      }
   }

   std::cout << ogre << "\n"; // Ogre is lame again..
}
