#include <limits>
#include "userCmds.hpp"

int main()
{
  using storage_t = psarev::avlTree< std::string, psarev::List< std::string > >;
  psarev::avlTree< std::string, storage_t > depot;
  std::string defaultSt = "";

  psarev::avlTree< std::string, std::function < void(std::istream&, std::ostream&, psarev::avlTree< std::string, storage_t >&) > > userCmds;
  {
    using namespace std::placeholders;
    userCmds.insert({"help", std::bind(psarev::cmdHelp, _1, _2) });
    userCmds.insert({"create", std::bind(psarev::cmdCreate, _1, _2, _3, "") });
    userCmds.insert({"delete", psarev::cmdDelete });
    userCmds.insert({"list", std::bind(psarev::cmdList, _2, _3) });
    userCmds.insert({"show", psarev::cmdShow });
    userCmds.insert({"rename", psarev::cmdRename });
    userCmds.insert({"choose", std::bind(psarev::cmdCreate, _1, _2, _3, defaultSt) });
    userCmds.insert({"save", psarev::cmdSave });

    userCmds.insert({"print", std::bind(psarev::cmdPrint, _1, _2, _3, defaultSt) });
    userCmds.insert({"fono", std::bind(psarev::cmdFono, _1, _2) });
    userCmds.insert({"makeSent", std::bind(psarev::cmdMakeSent, _1, _2, _3, defaultSt) });
  }

  std::string userCmd = "";
  while (std::cin >> userCmd)
  {
    try
    {
      userCmds.at(userCmd)(std::cin, std::cout, depot);
    }
    catch (const std::logic_error&)
    {
      psarev::outInvCommand(std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
