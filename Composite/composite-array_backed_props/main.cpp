#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>

// Failed solution
struct Creature_fail
{
   int streangth, agility, intelligence; // wisdom, charisma...

   int
   sum() const
   {
      return streangth + agility + intelligence; // + wisdom + charisma + ...
   }

   double
   avg() const
   {
      return sum() / 3.0; // or sum()/5.0...
   }

   int
   max() const
   {
      return std::max(std::max(streangth, agility), intelligence); // std::max(std::max(std::max(std:max(.........
   }
};

// Better?
struct Creature
{
   enum class Abilities : int
   {
      str,
      agl,
      intl,
      COUNT
   };
   std::array< int, (size_t)Abilities::COUNT > abilities;

   int
   strength() const
   {
      return abilities[(size_t)Abilities::str];
   }

   void
   setStrength(int s)
   {
      abilities[(size_t)Abilities::str] = s;
   }
   int
   agility() const
   {
      return abilities[(size_t)Abilities::agl];
   }

   void
   setAgility(int s)
   {
      abilities[(size_t)Abilities::agl] = s;
   }

   int
   intelligence() const
   {
      return abilities[(size_t)Abilities::intl];
   }

   void
   setIntelligence(int s)
   {
      abilities[(size_t)Abilities::intl] = s;
   }


   int
   sum() const
   {
      return std::accumulate(abilities.begin(), abilities.end(), 0);
   }

   double
   avg() const
   {
      return sum() / (double)abilities.size(); // or sum()/5.0...
   }

   int
   max() const
   {
      return *std::max_element(abilities.begin(), abilities.end()); // std::max(std::max(std::max(std:max(.........
   }
};


int
main()
{
   Creature orc;
   orc.setIntelligence(1);
   orc.setAgility(4);
   orc.setStrength(11);

   std::cout << "Avg orc stat: " << orc.avg() << std::endl
             << "Max orc stat: " << orc.max() << std::endl
             << "Sum of all orc stats: " << orc.sum() << std::endl;


   return 0;
}
