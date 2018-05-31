#ifndef MATHLEXER_HPP
#define MATHLEXER_HPP

#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include <boost/lexical_cast.hpp>

struct Token
{
   enum Type
   {
      integer,
      plus,
      minus,
      lparen,
      rparen
   } type;

   std::string text;

   Token(const Type t, const std::string& str) : type(t), text(str)
   {
   }

   friend std::ostream&
   operator<<(std::ostream& os, const Token& token)
   {
      os << "`" << token.text << "`";
      return os;
   }
};


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
         case '(':
            tokens.emplace_back(Token::lparen, "(");
            break;
         case ')':
            tokens.emplace_back(Token::rparen, ")");
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
            else
            {
               throw std::runtime_error{std::string("error: Unexpected token: `") + text[charIdx] + '`'};
            }
      }
   }

   return tokens;
}


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
   }
};


std::shared_ptr< Element >
parse(const std::vector< Token >& tokens)
{
   auto rootOp = std::make_shared< BinaryOperation >();

   bool haveLhs{false};

   for (size_t tokenIdx = 0; tokenIdx < tokens.size(); ++tokenIdx)
   {
      const auto& token = tokens[tokenIdx];
      switch (token.type)
      {
         case Token::integer:
         {
            const int value = boost::lexical_cast< int >(token.text);
            auto integer = std::make_shared< Integer >(value);
            if (!haveLhs)
            {
               rootOp->lhs = integer;
               haveLhs = true;
            }
            else
            {
               rootOp->rhs = integer;
            }
            break;
         }
         case Token::minus:
         {
            rootOp->type = BinaryOperation::subtraction;
            break;
         }
         case Token::plus:
         {
            rootOp->type = BinaryOperation::addition;
            break;
         }
         case Token::lparen:
         {
            bool rparenFound{false};
            size_t rparenIdx = tokenIdx + 1;
            for (; rparenIdx < tokens.size(); ++rparenIdx)
            {
               if (tokens[rparenIdx].type == Token::rparen)
               {
                  rparenFound = true;
                  break;
               }
               else if (tokens[rparenIdx].type == Token::lparen)
               {
                  throw std::runtime_error{"error: Nested parens not supported yet"};
               }
            }
            if (rparenFound)
            {
               std::vector< Token > subExpression{tokens.begin() + tokenIdx + 1, tokens.begin() + rparenIdx};
               auto element = parse(subExpression);
               if (!haveLhs)
               {
                  rootOp->lhs = element;
                  haveLhs = true;
               }
               else
               {
                  rootOp->rhs = element;
               }
               tokenIdx = rparenIdx;
            }
            else
            {
               throw std::runtime_error{"error: Missing `)`"};
            }
            break;
         }
         case Token::rparen:
         {
            throw std::runtime_error{"error: `)` should be ignored"};
            break;
         }
      }
   }


   return rootOp;
}

#endif // MATHLEXER_HPP
