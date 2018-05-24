#ifndef BEHAVIORALCOMMAND_HPP
#define BEHAVIORALCOMMAND_HPP

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

namespace behavioral {

struct BankAccount
{
   int balance = 0;
   int overdraft_limit = -500;

   void
   deposit(int amount)
   {
      balance += amount;
      cout << "deposited " << amount << ", balance now " << balance << "\n";
   }

   bool
   withdraw(int amount)
   {
      if (balance - amount >= overdraft_limit)
      {
         balance -= amount;
         cout << "withdrew " << amount << ", balance now " << balance << "\n";
         return true;
      }
      return false;
   }
};


struct Command
{
   bool succeeded;

   virtual void
   call() = 0;

   virtual void
   undo() = 0;
};


struct BankAccountCommand : Command
{
   BankAccount& account;
   enum Action
   {
      deposit,
      withdraw
   } action;
   int amount;

   BankAccountCommand(BankAccount& account, const Action action, const int amount) : account(account), action(action), amount(amount)
   {
      succeeded = false;
   }

   void
   call() override
   {
      switch (action)
      {
         case deposit:
            account.deposit(amount);
            succeeded = true;
            break;
         case withdraw:
            succeeded = account.withdraw(amount);
            break;
      }
   }

   void
   undo() override
   {
      if (!succeeded)
         return;

      switch (action)
      {
         case withdraw:
            if (succeeded)
               account.deposit(amount);
            break;
         case deposit:
            account.withdraw(amount);
            break;
      }
   }
};


struct CompositeBankAccountCommand : Command
{
   CompositeBankAccountCommand(const initializer_list< BankAccountCommand >& _Ilist) : commands(_Ilist)
   {
   }

   virtual ~CompositeBankAccountCommand() = default;

   void
   call() override
   {
      for (auto& cmd : commands)
         cmd.call();
   }

   void
   undo() override
   {
      for (auto it = commands.rbegin(); it != commands.rend(); ++it)
         it->undo();
   }

 protected:
   vector< BankAccountCommand > commands;
};


struct DependentCompositeCommand : CompositeBankAccountCommand
{
   explicit DependentCompositeCommand(const initializer_list< BankAccountCommand >& _Ilist) : CompositeBankAccountCommand{_Ilist}
   {
   }

   void
   call() override
   {
      bool ok = true;
      for (auto& cmd : commands)
      {
         if (ok)
         {
            cmd.call();
            ok = cmd.succeeded;
         }
         else
         {
            cmd.succeeded = false;
         }
      }
   }
};


struct MoneyTransferCommand : DependentCompositeCommand
{
   MoneyTransferCommand(BankAccount& from, BankAccount& to, int amount)
      : DependentCompositeCommand{BankAccountCommand{from, BankAccountCommand::withdraw, amount},
                                  BankAccountCommand{to, BankAccountCommand::deposit, amount}}
   {
   }
};

} // namespace behavioral


#endif // BEHAVIORALCOMMAND_HPP
