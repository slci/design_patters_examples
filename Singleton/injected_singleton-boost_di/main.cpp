#include <boost/di.hpp>
#include <iostream>
#include <memory>

struct IFoo
{
   virtual std::string
   name() = 0;
};

struct Foo : public IFoo
{
   static int id;

   Foo()
   {
      ++id;
   }

 public:
   std::string
   name() override
   {
      return std::string("Foo ") + std::to_string(id);
   }
};
int Foo::id = 0;

// Needs a singleton instance of Foo
struct Bar
{
   Bar() = delete;
   Bar(Bar const&) = delete;
   Bar&
   operator=(Bar const&) = delete;
   Bar(Bar&&) = delete;
   Bar&
   operator=(Bar&&) = delete;


   explicit Bar(std::shared_ptr< IFoo > foo, int x_) : fooInstance(foo), x(x_)
   {
      std::cout << "Creating Bar " << x << std::endl;
   }

   std::string
   name() const
   {
      return fooInstance->name();
   }

 private:
   std::shared_ptr< IFoo > fooInstance;
   int x;
};


class X
{
 public:
   X() = default;

   int
   getX() const
   {
      return x;
   }

 private:
   int x{666};
};

int
main()
{
   auto injector = boost::di::make_injector(boost::di::bind< IFoo >().to< Foo >().in(boost::di::singleton));

   auto bar1 = injector.create< std::shared_ptr< Bar > >();
   auto bar2 = injector.create< std::shared_ptr< Bar > >();
   auto x = injector.create< X >();

   std::cout << bar1->name() << std::endl;
   std::cout << bar2->name() << std::endl;

   std::cout << x.getX() << std::endl;
}
