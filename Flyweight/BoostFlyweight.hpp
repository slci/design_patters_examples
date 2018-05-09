#ifndef BOOSTFLYWEIGHT_HPP
#define BOOSTFLYWEIGHT_HPP
#include <boost/flyweight.hpp>
#include <string>

using namespace std;

namespace boost_flyweigth {

struct User
{
   boost::flyweight< string > first_name, last_name;

   User(string const& f_name, string const& l_name) : first_name(f_name), last_name(l_name)
   {
   }

   string const&
   firstName() const
   {
      return first_name.get();
   }

   string const&
   lastName() const
   {
      return last_name.get();
   }


   friend ostream&
   operator<<(ostream& os, const User& user)
   {
      os << "first_name[" << user.first_name.get_key() << "]: " << user.firstName() << " last_name[" << user.last_name.get_key()
         << "]: " << user.lastName();
      return os;
   }
};

} // namespace boost_flyweigth

#endif // BOOSTFLYWEIGHT_HPP
