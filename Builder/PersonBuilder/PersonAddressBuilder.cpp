#include "PersonAddressBuilder.hpp"

PersonAddressBuilder&
PersonAddressBuilder::at(std::string street_address)
{
   person.street_address = street_address;
   return *this;
}

PersonAddressBuilder&
PersonAddressBuilder::with_postcode(std::string post_code)
{
   person.post_code = post_code;
   return *this;
}

PersonAddressBuilder&
PersonAddressBuilder::in(std::string city)
{
   person.city = city;
   return *this;
}
