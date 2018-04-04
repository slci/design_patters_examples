#include <iostream>
#include <string>
#include <tuple>
#include <vector>

// A. High-level modules should not depend on low-level modules.
//    Both should depend on abstractions.
// B. Abstractions should not depend on details.
//    Details should depend on abstractions.


enum class Relationship
{
   parent,
   child,
   sibling
};


struct Person
{
   std::string name;
};


struct RelationshipBrowser
{
   virtual std::vector< Person >
   findAllChildrenOf(std::string const& name) const = 0;
};


struct Relationships : public RelationshipBrowser // low-level
{
   std::vector< std::tuple< Person, Relationship, Person > > relations;

   void
   add_parent_child(Person const& parent, Person const& child)
   {
      relations.emplace_back(parent, Relationship::parent, child);
      relations.emplace_back(child, Relationship::child, parent);
   }

   void
   add_brothers(Person const& bro1, Person const& bro2)
   {
      relations.emplace_back(bro1, Relationship::sibling, bro2);
      relations.emplace_back(bro2, Relationship::sibling, bro1);
   }

   std::vector< Person >
   findAllChildrenOf(const std::string& name) const override
   {
      std::vector< Person > result;

      for (auto && [ first, rel, second ] : relations)
      {
         if (first.name == "John" && rel == Relationship::parent)
         {
            result.push_back(Person{second.name});
         }
      }

      return result;
   }
};


struct Research // high-level
{
   // this is wrong, it bring dependency to low-level data
   //   Research(Relationships const& relationships)
   //   {
   //      for (auto && [ first, rel, second ] : relationships.relations)
   //      {
   //         if (first.name == "John" && rel == Relationship::parent)
   //         {
   //            std::cout << "John has a child called " << second.name << std::endl;
   //         }
   //      }
   //   }

   // this is better, depending only on interface
   Research(RelationshipBrowser const& browser)
   {
      auto rels = browser.findAllChildrenOf("Chris");

      for (auto& child : rels)
      {
         std::cout << "John has a child called " << child.name << std::endl;
      }
   }
};


int
main()
{
   Person john{"John"};
   Person child1{"Chris"};
   Person child2{"Kyle"};
   Person brother{"Robert"};

   Relationships relationships;
   relationships.add_parent_child(john, child1);
   relationships.add_parent_child(john, child2);
   relationships.add_brothers(john, brother);


   Research _{relationships};
}
