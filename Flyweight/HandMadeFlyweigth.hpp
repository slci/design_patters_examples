#ifndef HANDMADEFLYWEIGTH_HPP
#define HANDMADEFLYWEIGTH_HPP

#include <boost/bimap.hpp>
#include <iostream>
#include <vector>

using namespace std;

namespace hand_made {

using nameId = uint32_t;

struct User
{
   User(string const& f_name, string const& l_name) : first_name(add(f_name)), last_name(add(l_name))
   {
   }

   string const&
   firstName() const
   {
      return names.left.find(first_name)->second;
   }

   string const&
   lastName() const
   {
      return names.left.find(last_name)->second;
   }

   friend ostream&
   operator<<(ostream& os, const User& user)
   {
      os << "first_name[" << user.first_name << "]: " << user.firstName() << " last_name[" << user.last_name << "]: " << user.lastName();
      return os;
   }

 protected:
   nameId first_name, last_name;

   static boost::bimap< nameId, string > names;
   static nameId seed;

   static nameId
   add(string const& name)
   {
      auto it = names.right.find(name);
      if (it == names.right.end())
      {
         auto id = seed++;
         names.insert({id, name});
         return id;
      }
      else
      {
         return it->second;
      }
   }
};

nameId User::seed = 0U;
boost::bimap< nameId, string > User::names{};

} // namespace hand_made

#endif // HANDMADEFLYWEIGTH_HPP
