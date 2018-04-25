#include <Person.hpp>
#include <iostream>

struct Person::PersonImpl
{
   PersonImpl() = default;
   virtual ~PersonImpl() = default;

   void
   greet(std::string const& name);
};

Person::Person(std::string name) : name(std::move(name)), impl(std::make_unique< PersonImpl >())
{
}

Person::~Person()
{
}

void
Person::greet()
{
   impl->greet(name);
}

void
Person::PersonImpl::greet(const std::string& name)
{
   std::cout << "Hello " << name << std::endl;
}
