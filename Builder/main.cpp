#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include "XMLBuilder.hpp"

int
main()
{
   XMLElement root = XMLBuilder("ul").add_child("li", "hello").add_child("li", "world").add_child("li", "!");

   // add nested list as child of root
   auto& nestedList = root.add_child(XMLBuilder("ul").add_child("li", "nested").add_child("li", "hello").add_child("li", "world"));

   nestedList.add_child(XMLBuilder("nested_elem").add_child("key", "value"));

   std::cout << root.str() << std::endl;

   return 0;
}
