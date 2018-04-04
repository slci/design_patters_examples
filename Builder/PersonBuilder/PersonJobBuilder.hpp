#ifndef PERSONJOBBUILDER_HPP
#define PERSONJOBBUILDER_HPP

#include "PersonBuilder.hpp"

class PersonJobBuilder : public PersonBuilderBase
{
 public:
   explicit PersonJobBuilder(Person& person) : PersonBuilderBase{person}
   {
   }

   PersonJobBuilder&
   at(std::string company_name);

   PersonJobBuilder&
   as_a(std::string position);

   PersonJobBuilder&
   earning(int annual_income);
};

#endif // PERSONJOBBUILDER_HPP
