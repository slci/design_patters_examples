#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include "XMLBuilder.hpp"

#include "GroovyStyleHTMLBuilder.hpp"

int
main()
{
   // XML builder test
   XMLElement root = XMLBuilder("ul").add_child("li", "hello").add_child("li", "world").add_child("li", "!");
   auto& nestedList = root.add_child(XMLBuilder("ul").add_child("li", "nested").add_child("li", "hello").add_child("li", "world"));
   nestedList.add_child(XMLBuilder("nested_elem").add_child("key", "value"));

   std::cout << root << std::endl;


   // Grovy style HTML builder test
   // clang-format off
   std::cout <<
                P {
                    Img {"http://pokemon.com/pikachu.png"}
                }
             << std::endl;
   // clang-format on
}
