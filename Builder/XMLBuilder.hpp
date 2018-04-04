#ifndef XMLBUILDER_HPP
#define XMLBUILDER_HPP

struct XMLElement
{
 private:
   XMLElement() = default;

   XMLElement(std::string name) : name(std::move(name))
   {
   }

   XMLElement(std::string name, std::string text) : name(std::move(name)), text(std::move(text))
   {
   }

 public:
   friend struct XMLBuilder;

   XMLElement(XMLElement&&) = default;

   XMLElement&
   operator=(XMLElement&&) = default;

   std::string
   str(std::size_t const indent = 0) const
   {
      std::ostringstream oss;

      std::string i0(indent_size * indent, ' ');
      std::string i1(indent_size * (indent + 1), ' ');
      oss << i0 << "<" << name << ">" << std::endl;

      if (text.size() > 0)
      {
         oss << i1 << text << std::endl;
      }

      for (auto const& e : elements)
      {
         oss << e.str(indent + 1);
      }

      oss << i0 << "</" << name << ">" << std::endl;

      return oss.str();
   }

   XMLElement&
   add_child(std::string name)
   {
      elements.push_back(XMLElement{name});
      return elements.back();
   }

   XMLElement&
   add_child(std::string name, std::string text)
   {
      elements.push_back(XMLElement{name, text});
      return elements.back();
   }

   XMLElement&
   add_child(XMLElement&& elem)
   {
      elements.push_back(std::move(elem));
      return elements.back();
   }

   std::string name;
   std::string text;

   std::vector< XMLElement > elements;

   std::size_t const indent_size = 4;
};


struct XMLBuilder
{
   XMLElement root;

   XMLBuilder(std::string root_name)
   {
      root.name = root_name;
   }

   XMLBuilder&
   add_child(std::string name, std::string text)
   {
      root.elements.push_back(XMLElement{name, text});
      return *this;
   }

   operator XMLElement()
   {
      return std::move(root);
   }
};


#endif // XMLBUILDER_HPP
