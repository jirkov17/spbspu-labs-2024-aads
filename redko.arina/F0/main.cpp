#include <functional>
#include "userCommands.hpp"
#include "inputFunctions.hpp"
#include "messageFunctions.hpp"

int main()
{
  std::cout << "--------- Huffman Coding ---------\n";
  std::cout << "type <help> to see list of commands\n";

  redko::BSTree< std::string, std::function< void(const std::string &)> > functions;
  functions.insert({ "help", redko::help });
  functions.insert({ "code", redko::code });
  functions.insert({ "decode", redko::decode });
  functions.insert({ "recode", redko::recode });
  functions.insert({ "compare", redko::compare });

  std::string description = "";
  std::string command = "";
  while (std::getline(std::cin, description) && description != "quit")
  {
    command = redko::cutName(description);
    try
    {
      functions.at(command)(description);
    }
    catch (const std::out_of_range &)
    {
      redko::printInvalidMessage(std::cout);
    }
  }

  return 0;
}
