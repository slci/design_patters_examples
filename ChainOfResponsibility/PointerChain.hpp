#ifndef POINTERCHAIN_HPP
#define POINTERCHAIN_HPP
#include <iostream>

namespace pointer_chain {

struct Creature
{
   std::string name;
   int attack, defense;

   Creature(std::string const name, int const attack, int const defense) : name(std::move(name)), attack(attack), defense(defense)
   {
   }

   friend std::ostream&
   operator<<(std::ostream& os, Creature const& c)
   {
      os << "Creature: " << c.name << " [att: " << c.attack << ", def: " << c.defense << "]\n";
      return os;
   }
};


class CreatureModifier
{
   CreatureModifier* next{nullptr};

 protected:
   Creature& creature;

 public:
   CreatureModifier(Creature& c) : creature(c)
   {
   }

   void
   add(CreatureModifier& cm)
   {
      if (next)
         next->add(cm);
      else
         next = &cm;
   }

   virtual void
   handle()
   {
      if (next)
      {
         next->handle();
      }
   }
};


class DoubleAttackModifier : public CreatureModifier
{
 public:
   DoubleAttackModifier(Creature& cr) : CreatureModifier(cr)
   {
   }

   void
   handle() override
   {
      creature.attack *= 2;
      CreatureModifier::handle(); //!!!11
   }
};


class IncreasedDefenceModifier : public CreatureModifier
{
 public:
   IncreasedDefenceModifier(Creature& cr) : CreatureModifier(cr)
   {
   }

   void
   handle() override
   {
      creature.defense += 15;
      CreatureModifier::handle(); //!!!!11
   }
};


class NoBonusModifier : public CreatureModifier
{
 public:
   NoBonusModifier(Creature& cr) : CreatureModifier(cr)
   {
   }

   void
   handle() override
   {
      // break chain of responsibility
   }
};


} // namespace pointer_chain

#endif // POINTERCHAIN_HPP
