#ifndef MATHLEXER_HPP
#define MATHLEXER_HPP

#include <iostream>
#include <sstream>
#include <vector>

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
   for (size_t n = 0; n < text.size(); ++n)
   {
      switch (text[n])
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
            if (std::isdigit(text[n]))
            {
               std::ostringstream buffer;
               buffer << text[n];
               for (size_t i = n + 1; i < text.size(); ++i)
               {
                  if (std::isdigit(text[i]))
                  {
                     buffer << text[i];
                     ++n;
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
               throw std::runtime_error{std::string("Unexpected token: `") + text[n] + '`'};
            }
      }
   }

   return tokens;
}

#endif // MATHLEXER_HPP
