#include "PersonJobBuilder.hpp"

PersonJobBuilder&
PersonJobBuilder::at(std::string company_name)
{
   person.company_name = company_name;
   return *this;
}

PersonJobBuilder&
PersonJobBuilder::as_a(std::string position)
{
   person.position = position;
   return *this;
}

PersonJobBuilder&
PersonJobBuilder::earning(int annual_income)
{
   person.annual_income = annual_income;
   return *this;
}
