#ifndef PROPERTYPROXY_HPP
#define PROPERTYPROXY_HPP

#include <iostream>


template < typename T > struct Property
{
   T value;

   Property() = default;

   Property(T value)
   {
      *this = value;
   }

   operator T()
   {
      std::cout << "Cast return\n";
      return value;
   }

   T&
   operator=(T new_value)
   {
      std::cout << "Assignment!\n";
      return value = new_value;
   }
};


#endif // PROPERTYPROXY_HPP
