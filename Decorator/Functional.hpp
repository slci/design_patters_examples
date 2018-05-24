#ifndef FUNCTIONAL_HPP
#define FUNCTIONAL_HPP

#include <functional>
#include <iostream>
#include <string>

using namespace std;

struct Logger
{
   function< void() > func;
   string name;


   Logger(function< void() > f, string n) : func(f), name(n)
   {
   }


   void
   operator()() const
   {
      cout << "Entering " << name << endl;
      func();
      cout << "Leaving " << name << endl;
   }
};


#endif // FUNCTIONAL_HPP
