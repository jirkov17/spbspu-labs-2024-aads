#include <limits>
#include <functional>
#include <iostream>
#include "commands.hpp"
#include "accessoryFunctions.hpp"
#include "IOFunctions.hpp"

int main()
{
  ponomarev::BSTree < std::string, std::function< void (std::string &, ponomarev::HuffmanCode &) >, int > commands;
  {
    commands["help"] = ponomarev::outputInfoAboutCommands;
    commands["input"] = ponomarev::makeInput;
    commands["encode"] = ponomarev::chooseEncode;
    commands["write"] = ponomarev::writeTextIntoFile;
    commands["set"] = ponomarev::setDecode;
    commands["combine"] = ponomarev::combineFiles;
    commands["table"] = ponomarev::showTable;
    commands["decode"] = ponomarev::makeDecode;
    commands["delete"] = ponomarev::makeDelete;
    commands["clean"] = ponomarev::makeClean;
  }

  ponomarev::printWelcomeMessage(std::cout);
  std::string command = "";
  std::string type = "";
  ponomarev::HuffmanCode data;

  while (std::cin >> command)
  {
    type = ponomarev::cutType(command);
    try
    {
      commands.at(type)(command, data);
    }
    catch (const std::logic_error &)
    {
      ponomarev::printInvalidCommandMessage(std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  data.codes.clear();
  data.freq.clear();
  commands.clear();
  return 0;
}
