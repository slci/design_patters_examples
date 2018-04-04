#ifndef PERSONADRESSBUILDER_HPP
#define PERSONADRESSBUILDER_HPP

#include "PersonBuilder.hpp"

#include <string>

class PersonAddressBuilder : public PersonBuilderBase
{
 public:
   explicit PersonAddressBuilder(Person& person) : PersonBuilderBase{person}
   {
   }

   PersonAddressBuilder&
   at(std::string street_address);

   PersonAddressBuilder&
   with_postcode(std::string post_code);

   PersonAddressBuilder&
   in(std::string city);
};

#endif // PERSONADRESSBUILDER_HPP
