#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

enum class Size
{
   tiny,
   small,
   medium,
   large,
   huge
};

enum class Color
{
   red,
   green,
   blue,
   yellow,
   orange,
   white,
   black
};

struct Product
{
   std::string name;
   Size size;
   Color color;
};


template < typename Spec > struct Filter
{
   explicit Filter(Spec&& spec) : specification(spec)
   {
   }

   std::vector< const Product* >
   applyOn(std::vector< Product > const& items) const
   {
      std::vector< const Product* > result;
      for (auto const& item : items)
      {
         if (specification.isSatisfied(item))
         {
            result.push_back(&item);
         }
      }

      return result;
   }

   Spec specification;
};


struct ColorSpecification
{
   explicit ColorSpecification(Color const c) : color(c)
   {
   }


   bool
   isSatisfied(Product const& p) const
   {
      return p.color == color;
   }

   Color const color;
};

struct SizeSpecification
{
   explicit SizeSpecification(Size const s) : size(s)
   {
   }


   bool
   isSatisfied(Product const& p) const
   {
      return p.size == size;
   }

   Size const size;
};


template < typename Spec1, typename Spec2 > struct AndSpecification
{
   explicit AndSpecification(Spec1&& s1, Spec2&& s2) : spec1(std::move(s1)), spec2(std::move(s2))
   {
   }

   bool
   isSatisfied(Product const& p) const
   {
      return spec1.isSatisfied(p) && spec2.isSatisfied(p);
   }

   Spec1 spec1;
   Spec2 spec2;
};

template < typename Spec1, typename Spec2 > struct OrSpecification
{
   explicit OrSpecification(Spec1&& s1, Spec2&& s2) : spec1(std::move(s1)), spec2(std::move(s2))
   {
   }

   bool
   isSatisfied(Product const& p) const
   {
      return spec1.isSatisfied(p) || spec2.isSatisfied(p);
   }

   Spec1 spec1;
   Spec2 spec2;
};


int
main()
{
   std::vector< Product > products{{"Apple", Size::small, Color::red},     {"Watermelon", Size::large, Color::green},
                                   {"Carrot", Size::small, Color::orange}, {"Lemon", Size::small, Color::yellow},
                                   {"Cabbage", Size::large, Color::green}, {"Cherry", Size::small, Color::red}};


   auto filter = Filter{AndSpecification{ColorSpecification{Color::green}, SizeSpecification{Size::large}}};

   for (auto const p : filter.applyOn(products))
   {
      std::cout << p->name << " is red and small\n";
   }
}
