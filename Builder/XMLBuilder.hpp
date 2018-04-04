#ifndef XMLBUILDER_HPP
#define XMLBUILDER_HPP

struct XMLElement
{
 private:
   XMLElement() = default;

   XMLElement(std::string name, std::size_t indent = INDENT) : name(std::move(name)), indent_size(indent)
   {
   }

   XMLElement(std::string name, std::string text, std::size_t indent = INDENT)
      : name(std::move(name)), text(std::move(text)), indent_size(indent)
   {
   }

 public:
   friend struct XMLBuilder;

   XMLElement(XMLElement&&) = default;

   XMLElement&
   operator=(XMLElement&&) = default;

   friend std::ostream&
   operator<<(std::ostream& os, XMLElement const& elem)
   {
      std::string i0(elem.indent_size, ' ');
      std::string i1(elem.indent_size + INDENT, ' ');
      os << i0 << "<" << elem.name << ">" << std::endl;

      if (elem.text.size() > 0)
      {
         os << i1 << elem.text << std::endl;
      }

      for (auto const& e : elem.elements)
      {
         os << e;
      }

      os << i0 << "</" << elem.name << ">" << std::endl;

      return os;
   }

   XMLElement&
   add_child(std::string name)
   {
      elements.push_back(XMLElement{name, indent_size + INDENT});
      return elements.back();
   }

   XMLElement&
   add_child(std::string name, std::string text)
   {
      elements.push_back(XMLElement{name, text, indent_size + INDENT});
      return elements.back();
   }

   XMLElement&
   add_child(XMLElement&& elem)
   {
      elem.indent_size += INDENT;

      for (auto& elem : elem.elements)
      {
         elem.indent_size += INDENT;
      }

      elements.push_back(std::move(elem));
      return elements.back();
   }

   std::string name;
   std::string text;

   std::vector< XMLElement > elements;

   std::size_t indent_size = 0;

   static std::size_t const INDENT = 4;
};


struct XMLBuilder
{
   XMLElement root;

   XMLBuilder(std::string root_name, std::size_t indent = 0)
   {
      root.name = root_name;
      root.indent_size = indent;
   }

   XMLBuilder&
   add_child(std::string name, std::string text)
   {
      root.elements.push_back(XMLElement{name, text, root.indent_size + XMLElement::INDENT});
      return *this;
   }

   operator XMLElement()
   {
      return std::move(root);
   }
};


#endif // XMLBUILDER_HPP
