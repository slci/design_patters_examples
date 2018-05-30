#include <iostream>
#include <string>

#include "MathLexer.hpp"

int
main()
{
   std::string input{"(13-4)-(12+1)"};

   auto tokens = lex(input);

   for (const auto& t : tokens)
   {
      std::cout << t << " ";
   }
   std::cout << "\n";
}
