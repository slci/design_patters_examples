#include <iostream>
#include <string>

#include "MathiWithVariablesInterpreter.hpp"
#include "SimpleMathInterpreter.hpp"

int
main()
{
   // Simple Math interpreter test
   try
   {
      std::string input{"(13-4)-(12+1)"};

      auto tokens = simple_interpreter::lex(input);
      auto expression = simple_interpreter::parse(tokens);

      std::cout << input << " = " << expression->eval() << "\n";
   }
   catch (std::exception& e)
   {
      std::cerr << "Unhandled exception: " << e.what() << std::endl;
   }


   // Math with variables interpreter test

   auto processor = ExpressionProcessor{};
   processor.variables['x'] = 3;

   std::string input{"10-6+x"};
   std::cout << input << " = " << processor.calculate(input) << "\n";
}
