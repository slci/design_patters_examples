#include "BehavioralCommand.hpp"


int
main()
{
   behavioral::BankAccount ba;

   /*vector<BankAccountCommand> commands{*/
   behavioral::CompositeBankAccountCommand commands{
      behavioral::BankAccountCommand{ba, behavioral::BankAccountCommand::deposit, std::numeric_limits< int >::max()},
      behavioral::BankAccountCommand{ba, behavioral::BankAccountCommand::deposit, 1},
      behavioral::BankAccountCommand{ba, behavioral::BankAccountCommand::withdraw, 200},
      behavioral::BankAccountCommand{ba, behavioral::BankAccountCommand::withdraw, 200}};

   // apply all the commands
   /*for (auto& cmd : commands)
   {
      cmd();
   }*/
   commands.call();

   // undo all the commands
   /*std::for_each(commands.rbegin(), commands.rend(),
      [](const BankAccountCommand& cmd) { cmd.undo(); });*/
   commands.undo();
}
