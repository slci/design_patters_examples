#ifndef GROOVYSTYLEHTMLBUILDER_HPP
#define GROOVYSTYLEHTMLBUILDER_HPP

#include <sstream>
#include <utility>

class Tag
{
 public:
   Tag(std::string const& name, std::string const& text) : name(name), text(text)
   {
   }

   Tag(std::string const& name, std::vector< Tag > const& children) : name(name), children(children)
   {
   }

   friend std::ostream&
   operator<<(std::ostream& os, Tag const& tag)
   {
      os << "<" << tag.name;

      for (auto const& att : tag.attributes)
      {
         os << " " << att.first << "=\"" << att.second << "\"";
      }

      if (!tag.children.empty() && !tag.text.empty())
      {
         os << "/>" << std::endl;
      }
      else
      {
         os << ">" << std::endl;

         if (!tag.text.empty())
         {
            os << tag.text << std::endl;
         }

         for (auto const& child : tag.children)
         {
            os << child;
         }

         os << "</" << tag.name << ">" << std::endl;
      }

      return os;
   }

 protected:
   std::string name;
   std::string text;
   std::vector< std::pair< std::string, std::string > > attributes;

   std::vector< Tag > children;
};

// Paragraph tag
class P : public Tag
{
 public:
   P(std::string const& text) : Tag("p", text)
   {
   }

   P(std::initializer_list< Tag > children) : Tag("p", children)
   {
   }
};

// Image tag
class Img : public Tag
{
 public:
   Img(std::string const& url) : Tag("img", "")
   {
      attributes.emplace_back(std::make_pair("src", url));
   }
};

#endif // GROOVYSTYLEHTMLBUILDER_HPP
