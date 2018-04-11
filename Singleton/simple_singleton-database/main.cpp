#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

#include <gtest/gtest.h>

using namespace std::chrono_literals;

template < typename T > class Singleton
{
 public:
   Singleton(Singleton const&) = delete;
   Singleton&
   operator=(Singleton const&) = delete;

   static T&
   instance()
   {
      static T* instance = nullptr;

      static std::mutex mtx;
      std::scoped_lock< std::mutex > lock(mtx);

      if (nullptr == instance)
      {
         // Simulate race condition
         std::this_thread::sleep_for(200ms);
         instance = new T();
      }

      return *instance;
   }

 protected:
   Singleton() = default;
};


class Database
{
 public:
   virtual unsigned long
   populationOf(std::string const& capital) = 0;
};


class SingletonDatabase : public Singleton< SingletonDatabase >, public Database
{
   friend class Singleton;

   SingletonDatabase()
   {
      std::ifstream ifs{"capitals.txt"};

      std::string name, pop;

      while (std::getline(ifs, name))
      {
         std::getline(ifs, pop);

         capitals[name] = std::stoul(pop);
      }
   }

   SingletonDatabase(SingletonDatabase const&) = delete;
   SingletonDatabase&
   operator=(SingletonDatabase const&) = delete;

   std::map< std::string, unsigned long > capitals;

 public:
   unsigned long
   populationOf(std::string const& capital) override
   {
      return capitals.at(capital);
   }
};

class DummyDatabase : public Database
{
 public:
   unsigned long
   populationOf(const std::string&) override
   {
      return 666;
   }
};


// Example where testing is hard
struct SingletonRecorFinder
{
   Database& db;

   SingletonRecorFinder(Database& database = SingletonDatabase::instance()) : db(database)
   {
   }

   unsigned long
   totalPopulation(std::vector< std::string > const& names)
   {
      unsigned long acc{0};
      for (auto const& name : names)
      {
         // acc += SingletonDatabase::instance().populationOf(name); // Be smart here and replace singleton with mock...
         acc += db.populationOf(name); // Better!
      }

      return acc;
   }
};


TEST(RecordFinderTest, SingletonTotalPopulationTest)
{
   SingletonRecorFinder rf;

   std::vector< std::string > names{"Zadupiewo", "ZdupyDoMordyszyn", "Warsaw", "ChujeMuje"};
   ASSERT_EQ(9222555U, rf.totalPopulation(names));
}

TEST(RecordFinderTest, SingletonTotalPopulationTest_mocked)
{
   DummyDatabase dummy{};
   SingletonRecorFinder rf{dummy};

   std::vector< std::string > names{"Zadupiewo", "ZdupyDoMordyszyn", "Warsaw", "ChujeMuje"};
   ASSERT_EQ(4 * 666U, rf.totalPopulation(names));
}


int
main(int argc, char* argv[])
{
   testing::InitGoogleTest(&argc, argv);

   return RUN_ALL_TESTS();
}
