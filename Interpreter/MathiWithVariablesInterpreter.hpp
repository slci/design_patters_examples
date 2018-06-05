#ifndef MATHIWITHVARIABLESINTERPRETER_HPP
#define MATHIWITHVARIABLESINTERPRETER_HPP

#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <vector>

namespace interpreter_with_vars {

struct Token
{
   enum Type
   {
      integer,
      variable,
      plus,
      minus
   } type;

   std::string text;

   Token(const Type t, const std::string& str) : type(t), text(str)
   {
   }
};


struct Element
{
   virtual int
   eval() const = 0;
};


struct Integer : Element
{
   int value;

   Integer(const int newVal) : value(newVal)
   {
   }

   int
   eval() const override
   {
      return value;
   }
};


struct Variable : Element
{
   char name;
   const std::map< char, int >& variables;

   Variable(const char n, const std::map< char, int >& vars) : name(n), variables(vars)
   {
   }

   int
   eval() const override
   {
      return variables.at(name);
   }
};


struct BinaryOperation : Element
{
   enum Type
   {
      addition,
      subtraction
   } type;

   std::shared_ptr< Element > lhs, rhs;

   int
   eval() const override
   {
      switch (type)
      {
         case addition:
            return lhs->eval() + rhs->eval();
         case subtraction:
            return lhs->eval() - rhs->eval();
      }
      return 0;
   }
};


struct ExpressionProcessor
{
   std::map< char, int > variables;


   std::vector< Token >
   lex(const std::string text)
   {
      std::vector< Token > tokens;
      for (size_t charIdx = 0; charIdx < text.size(); ++charIdx)
      {
         switch (text[charIdx])
         {
            case '+':
               tokens.emplace_back(Token::plus, "+");
               break;
            case '-':
               tokens.emplace_back(Token::minus, "-");
               break;
            default:
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
                  tokens.emplace_back(Token::integer, buffer.str());
               }
               else if (std::isalpha(text[charIdx]))
               {
                  std::ostringstream buffer;
                  buffer << text[charIdx];
                  for (size_t i = charIdx + 1; i < text.size(); ++i)
                  {
                     if (std::isalpha(text[i]))
                     {
                        buffer << text[i];
                        ++charIdx;
                     }
                     else
                     {
                        break;
                     }
                  }
                  tokens.emplace_back(Token::variable, buffer.str());
               }
               else
               {
                  throw std::runtime_error{std::string("error: Unexpected token: `") + text[charIdx] + '`'};
               }
         }
      }

      return tokens;
   }


   std::shared_ptr< Element >
   parse(const std::vector< Token >& tokens)
   {
      auto rootOp = std::make_shared< BinaryOperation >();

      bool haveLhs{false};
      bool haveRhs{false};

      for (size_t tokenIdx = 0; tokenIdx < tokens.size(); ++tokenIdx)
      {
         const auto& token = tokens[tokenIdx];
         switch (token.type)
         {
            case Token::integer:
            {
               const int value = std::stoi(token.text);
               auto integer = std::make_shared< Integer >(value);
               if (!haveLhs)
               {
                  rootOp->lhs = integer;
                  haveLhs = true;
               }
               else if (!haveRhs)
               {
                  rootOp->rhs = integer;
                  haveRhs = true;
               }
               else
               {
                  throw std::logic_error{"this should not happen!"};
               }
               break;
            }
            case Token::variable:
            {
               if (token.text.length() > 1)
               {
                  throw std::invalid_argument{"error: invalid variable name"};
               }

               auto var = std::make_shared< Variable >(token.text.at(0), variables);
               if (!haveLhs)
               {
                  rootOp->lhs = var;
                  haveLhs = true;
               }
               else if (!haveRhs)
               {
                  rootOp->rhs = var;
                  haveRhs = true;
               }
               else
               {
                  throw std::logic_error{"this should not happen!"};
               }
               break;
            }
            case Token::minus:
            {
               if (!haveLhs)
               {
                  throw std::runtime_error{"error: no lhs for binary operation!"};
               }
               else if (!haveRhs)
               {
                  rootOp->type = BinaryOperation::subtraction;
               }
               else
               {
                  auto newRootOp = std::make_shared< BinaryOperation >();
                  newRootOp->type = BinaryOperation::subtraction;
                  newRootOp->lhs = rootOp;
                  haveRhs = false;
                  rootOp = newRootOp;
               }
               break;
            }
            case Token::plus:
            {
               if (!haveLhs)
               {
                  throw std::runtime_error{"error: no lhs for binary operation!"};
               }
               else if (!haveRhs)
               {
                  rootOp->type = BinaryOperation::addition;
               }
               else
               {
                  auto newRootOp = std::make_shared< BinaryOperation >();
                  newRootOp->type = BinaryOperation::addition;
                  newRootOp->lhs = rootOp;
                  haveRhs = false;
                  rootOp = newRootOp;
               }
               break;
            }
         }
      }


      return rootOp;
   }


   int
   calculate(const std::string& text)
   {
      try
      {
         auto tokens = lex(text);
         auto expression = parse(tokens);

         return expression->eval();
      }
      catch (...)
      {
         return 0;
      }
   }
};

} // namespace interpreter_with_vars

#endif // MATHIWITHVARIABLESINTERPRETER_HPP
