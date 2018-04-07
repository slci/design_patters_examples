#ifndef PERSON_HPP
#define PERSON_HPP

#include <iosfwd>
#include <string>

class PersonBuilder;

class Person
{
 public:
   Person(Person&& other) = default;

   Person&
   operator=(Person&& other) = default;

   friend std::ostream&
   operator<<(std::ostream& os, const Person& obj);

   // Friend builders
   friend class PersonBuilder;
   friend class PersonAddressBuilder;
   friend class PersonJobBuilder;

   // private:
   Person() = default;

   // address
   std::string street_address;
   std::string post_code;
   std::string city;

   // employment
   std::string company_name;
   std::string position;
   int annual_income{0};
};

#endif // PERSON_HPP
