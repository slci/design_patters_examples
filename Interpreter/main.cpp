#include <iostream>
#include <string>

#include "SimpleMathInterpreter.hpp"

int
main()
{
   try
   {
      std::string input{"(13-4)-(12+1)"};

      auto tokens = lex(input);
      auto expression = parse(tokens);

      std::cout << "(13-4)-(12+1) = " << expression->eval() << "\n";
   }
   catch (std::exception& e)
   {
      std::cerr << "Unhandled exception: " << e.what() << std::endl;
   }
}
