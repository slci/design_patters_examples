#include <iostream>

#include "Person.hpp"
#include "PersonBuilder.hpp"

std::ostream&
operator<<(std::ostream& os, const Person& obj)
{
   return os << "street_address: " << obj.street_address << " post_code: " << obj.post_code << " city: " << obj.city
             << " company_name: " << obj.company_name << " position: " << obj.position << " annual_income: " << obj.annual_income;
}
