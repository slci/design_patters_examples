#ifndef PERSON_HPP
#define PERSON_HPP

#include <memory>
#include <string>

struct Person
{
   std::string name;

   Person(std::string name);
   virtual ~Person();

   void
   greet();

 private:
   // fwd pimpl declaration
   struct PersonImpl;
   std::unique_ptr< PersonImpl > impl;
};


#endif // PERSON_HPP
