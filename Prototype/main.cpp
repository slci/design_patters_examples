#include <iostream>
#include <memory>
#include <sstream>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>

struct Address
{
   std::string street;
   std::string city;
   unsigned int nr;

   Address() = default;

   explicit Address(std::string const& str_, std::string const& city_, unsigned int const nr_) : street(str_), city(city_), nr(nr_)
   {
   }

   friend std::ostream&
   operator<<(std::ostream& os, Address const& address)
   {
      os << address.street << ' ' << address.nr << ", " << address.city;
      return os;
   }

 private:
   friend class boost::serialization::access;

   template < typename Archive >
   void
   serialize(Archive& ar, unsigned int const version)
   {
      (void)version;
      ar& street;
      ar& city;
      ar& nr;
   }
};


struct Contact
{
   std::string name;
   std::unique_ptr< Address > address;

   Contact() : address(std::make_unique< Address >())
   {
   }

   explicit Contact(std::string const& name_, std::unique_ptr< Address > addr_) : name(name_), address(std::move(addr_))
   {
   }


   friend std::ostream&
   operator<<(std::ostream& os, Contact const& contact)
   {
      os << "name: " << contact.name << ", address: " << *contact.address;
      return os;
   }

   Contact
   clone()
   {
      std::ostringstream oss;
      boost::archive::binary_oarchive oa(oss);
      oa << *this;

      std::istringstream iss(oss.str());
      boost::archive::binary_iarchive ia(iss);

      Contact newContact;
      ia >> newContact;

      return newContact;
   }

 private:
   friend class boost::serialization::access;

   template < typename Archive >
   void
   serialize(Archive& ar, unsigned int const version)
   {
      (void)version;
      ar& name;
      ar&* address;
   }
};


int
main()
{
   auto slawek = Contact{"Sławomir Cielepak", std::make_unique< Address >("Tenisowa 23A", "Szczecin", 2U)};

   auto marta = slawek.clone();
   marta.name = "Marta Głuchowska";

   std::cout << slawek << std::endl;
   std::cout << marta << std::endl;

   return 0;
}
