#ifndef PERSONBUILDER_HPP
#define PERSONBUILDER_HPP

#include "Person.hpp"

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase
{
 public:
   // builder facets
   PersonAddressBuilder
   lives() const;

   PersonJobBuilder
   works() const;

   operator Person() const
   {
      return std::move(person);
   }

 protected:
   Person& person;

   explicit PersonBuilderBase(Person& person) : person{person}
   {
   }
};

class PersonBuilder : public PersonBuilderBase
{
 public:
   PersonBuilder() : PersonBuilderBase{p}
   {
   }

 private:
   Person p;
};

#endif // PERSONBUILDER_HPP
