#include "BehavioralCommand.hpp"


int
main()
{
   behavioral::BankAccount ba;
   /*vector<BankAccountCommand> commands{*/
   behavioral::CompositeBankAccountCommand commands{behavioral::BankAccountCommand{ba, behavioral::BankAccountCommand::deposit, 100},
                                                    behavioral::BankAccountCommand{ba, behavioral::BankAccountCommand::withdraw, 200}};

   cout << ba.balance << endl;

   // apply all the commands
   /*for (auto& cmd : commands)
   {
   cmd.call();
   }*/
   commands.call();

   cout << ba.balance << endl;

   /*for_each(commands.rbegin(), commands.rend(),
   [](const BankAccountCommand& cmd) { cmd.undo(); });*/
   commands.undo();

   cout << ba.balance << endl;
}
