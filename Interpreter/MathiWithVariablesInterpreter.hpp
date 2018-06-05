#ifndef MATHIWITHVARIABLESINTERPRETER_HPP
#define MATHIWITHVARIABLESINTERPRETER_HPP

#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <vector>
#include <optional>

struct ExpressionProcessor
{
   std::map< char, int > variables;
   
   
   enum class Operation
   {
       plus,
       minus,
       invalid
   };

   int
   calculate(const std::string& text)
   {
      std::optional<int> lhs;
      Operation op{Operation::invalid};
       
      for (size_t charIdx = 0; charIdx < text.size(); ++charIdx)
      {
         switch (text[charIdx])
         {
            case '+':
            {
                if (!lhs)
                {
                    throw std::runtime_error{"error: + operator needs lhs"};
                }
                else
                {
                      op = Operation::plus;
                }
                break;
            }
            case '-':
            {
                if (!lhs)
                {
                    throw std::runtime_error{"error: - operator needs lhs"};
                }
                else
                {
                      op = Operation::minus;
                }
                break;
            }
            default:
            {
               if (std::isdigit(text[charIdx]))
               {
                  std::ostringstream buffer;
                  buffer << text[charIdx];
                  for (size_t i = charIdx + 1; i < text.size(); ++i)
                  {
                     if (std::isdigit(text[i]))
                     {
                        buffer << text[i];
                        ++charIdx;
                     }
                     else
                     {
                        break;
                     }
                  }
                  if (!lhs)
                  {
                        lhs = std::stoi(buffer.str());
                  }
                  else
                  {
                        switch (op)
                        {
                              case Operation::plus:
                                    lhs = lhs.value() + std::stoi(buffer.str());
                                    break;
                              case Operation::minus:
                                    lhs = lhs.value() - std::stoi(buffer.str());
                                    break;
                              default:
                                    throw std::runtime_error{"error: invalid operation"};
                        }
                  }
               }
               else if (std::isalpha(text[charIdx]))
               {
                  if ((charIdx + 1) < text.size() && std::isalpha(text[charIdx + 1]))
                  {
                        throw std::runtime_error{"error: multi-charater variables unsupported"};
                  }
                  else
                  {
                        if (!lhs)
                        {
                              lhs = variables.at(text[charIdx]);
                        }
                        else
                        {
                              switch (op)
                              {
                                    case Operation::plus:
                                          lhs = lhs.value() + variables.at(text[charIdx]);
                                          break;
                                    case Operation::minus:
                                          lhs = lhs.value() - variables.at(text[charIdx]);
                                          break;
                                    default:
                                          throw std::runtime_error{"error: invalid operation"};
                              }
                        }
                  }
               }
               else
               {
                  throw std::runtime_error{std::string("error: Unexpected character: `") + text[charIdx] + '`'};
               }
            }
         }
      }

      if (lhs)
      {
            return lhs.value();
      }
      else
      {
            return 0;
      }
   }
};

#endif // MATHIWITHVARIABLESINTERPRETER_HPP
