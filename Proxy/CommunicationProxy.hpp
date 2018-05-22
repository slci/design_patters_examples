#ifndef COMMUNICATIONPROXY_HPP
#define COMMUNICATIONPROXY_HPP
#include <chrono>
#include <future>
#include <iostream>

using namespace std::chrono_literals;

namespace communication_proxy {

struct Pingable
{
   virtual std::wstring
   ping(const std::wstring& message) = 0;
};


struct Pong : Pingable
{
   std::wstring
   ping(const std::wstring& message)
   {
      return message + L" pong";
   }
};

struct RemoteService : Pingable
{
   std::string address;
   bool connected{false};


   RemoteService(std::string addr) : address(std::move(addr))
   {
   }

   ~RemoteService()
   {
      disconnect();
   }

   void
   connect()
   {
      if (!connected)
      {
         std::cout << "Connecting to " << address << "\n";
         connected = true;
      }
   }

   void
   disconnect()
   {
      if (connected)
      {
         std::cout << "Disconnecting from " << address << "\n";
         connected = false;
      }
   }

   std::wstring
   ping(const std::wstring& message) override
   {
      connect();
      std::wcout << "msg: " << message << " sent to remote, waiting for response... ";
      auto f = std::async([]() {
         std::this_thread::sleep_for(1s);
         return L"pong";
      });

      return f.get();
   }
};

void
tryit(Pingable& pp)
{
   auto response = pp.ping(L"ping");
   std::wcout << " Respnse: " << response << "\n";
}

} // namespace communication_proxy

#endif // COMMUNICATIONPROXY_HPP
