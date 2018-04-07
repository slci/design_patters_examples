#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include "XMLBuilder.hpp"

#include "GroovyStyleHTMLBuilder.hpp"

#include "PersonBuilder/PersonAddressBuilder.hpp"
#include "PersonBuilder/PersonBuilder.hpp"
#include "PersonBuilder/PersonJobBuilder.hpp"

// clang-format off

int main()
{
  // XML fluent builder test
  XMLElement root = XMLBuilder("ul")
                       .add_child("li", "hello")
                       .add_child("li", "world")
                       .add_child("li", "!");
  XMLElement nestedList = XMLBuilder("ul")
                             .add_child("li", "nested")
                             .add_child("li", "hello")
                             .add_child("li", "world");
  root.add_child(std::move(nestedList));

  nestedList.add_child(XMLBuilder("nested_elem").add_child("key", "value"));

  std::cout << root << std::endl;

  // Grovy style HTML builder test
  std::cout <<
      P {
          Img {"http://pokemon.com/pikachu.png"}
      }
      << std::endl;


  // Person facade builder
  Person p = PersonBuilder()
     .lives().at("123 London Road").with_postcode("SW1 1GB").in("London")
     .works().at("PragmaSoft").as_a("Consultant").earning(10e6);

  // Typical construction
  Person p2;
  p2.street_address = "Tenisowa 23A/2";
  p2.post_code = "71-073";
  p2.city = "Szczecin";
  p2.company_name = "Mobica Limited";
  p2.position = "Senior Software Engineer";
  p2.annual_income = 100'000'000;

  std::cout << p << std::endl;
  std::cout << p2 << std::endl;
}
