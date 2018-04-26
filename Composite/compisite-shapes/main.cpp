#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct GraphicObject
{
   virtual void
   draw() = 0;
};

struct Circle : GraphicObject
{
   void
   draw() override
   {
      std::cout << "Circle\n";
   }
};


struct Group : GraphicObject
{
   std::string name;
   std::vector< std::unique_ptr< GraphicObject > > objects;

   Group(std::string name) : name(std::move(name))
   {
   }

   void
   draw() override
   {
      std::cout << "Group: " << name << " containing: \n";
      for (auto const& obj : objects)
      {
         std::cout << ' ';
         obj->draw();
      }
   }
};

int
main()
{
   Group root("root");
   root.objects.emplace_back(std::make_unique< Circle >());
   root.objects.emplace_back(std::make_unique< Circle >());

   auto childGroup = std::make_unique< Group >("sub-group");
   childGroup->objects.emplace_back(std::make_unique< Circle >());
   childGroup->objects.emplace_back(std::make_unique< Circle >());
   childGroup->objects.emplace_back(std::make_unique< Circle >());

   root.objects.push_back(std::move(childGroup));


   root.draw();
}
