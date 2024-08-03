#include <fstream>
#include "taskSumm.hpp"
#include "traverseCmds.hpp"

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cerr << "Error: Wrong parameters amount!\n";
    return 2;
  }

  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "Error: Can't open a file!\n";
    return 2;
  }

  using base_t = psarev::avlTree< long long, std::string >;
  base_t data;

  psarev::fillTree(input, data);
  if (data.isEmpty())
  {
    psarev::outEmpty(std::cout);
    return 0;
  }

  psarev::avlTree< std::string, std::function< void(std::ostream&, base_t&) > > travCmds;
  travCmds.insert({ "ascending", psarev::ascending });
  travCmds.insert({ "descending", psarev::descending });
  travCmds.insert({ "breadth", psarev::breadth });

  std::string direct = argv[1];

  if (!data.isEmpty())
  {
    try
    {
      auto cmdIter = travCmds.find(direct);
      if (cmdIter != travCmds.end() && !direct.empty())
      {
        (*cmdIter).second(std::cout, data);
      }
      else if (!direct.empty())
      {
        psarev::outInvCommand(std::cout);
        return 1;
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  else
  {
    psarev::outEmpty(std::cout);
  }

  return 0;
}
