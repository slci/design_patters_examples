#ifndef BROKERCHAIN_HPP
#define BROKERCHAIN_HPP

#include "SignalAndSlots.hpp"

#include <iostream>


namespace broker {

struct Query
{
   std::string creature_name;
   enum class Argument
   {
      attack,
      defense
   } argument;
   int result;

   Query(std::string const& name, Argument const arg, int const res) : creature_name(name), argument(arg), result(res)
   {
   }
};

// Mediator
struct Game
{
   Signal< Query& > queries;
};

class Creature
{
   Game& game; // mediator

   int attack, defense;
   std::string name;

 public:
   Creature(Game& g, std::string name, int const att, int const def) : game(g), attack(att), defense(def), name(name)
   {
   }

   int
   getAttack() const
   {
      Query q{name, Query::Argument::attack, attack};
      game.queries(q);
      return q.result;
   }

   int
   getDefense() const
   {
      Query q{name, Query::Argument::defense, defense};
      game.queries(q);
      return q.result;
   }

   std::string const&
   getName() const
   {
      return name;
   }

   friend std::ostream&
   operator<<(std::ostream& os, Creature const& c)
   {
      os << "Creature: " << c.name << " [att: " << c.getAttack() << ", def: " << c.getDefense() << ']';
      return os;
   }
};


class CreatureModifier
{
 protected:
   Game& game;
   Creature& creature;
   Signal< Query& >::Connection conn;

 public:
   CreatureModifier(Game& g, Creature& c) : game(g), creature(c)
   {
   }
};


class DoubleAttackModifier : public CreatureModifier
{
 public:
   DoubleAttackModifier(Game& g, Creature& c) : CreatureModifier(g, c)
   {
      conn = game.queries.connect([&](Query& q) {
         if (q.creature_name == creature.getName() && q.argument == Query::Argument::attack)
         {
            q.result *= 3;
         }
      });
   }
};


class IncreasedDefenseModifier : public CreatureModifier
{
 public:
   IncreasedDefenseModifier(Game& g, Creature& c) : CreatureModifier(g, c)
   {
      conn = game.queries.connect([&](Query& q) {
         if (q.creature_name == creature.getName() && q.argument == Query::Argument::defense)
         {
            q.result += 1;
         }
      });
   }
};

} // namespace broker

#endif // BROKERCHAIN_HPP
