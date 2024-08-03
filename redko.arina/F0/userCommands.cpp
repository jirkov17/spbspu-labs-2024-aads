#include "userCommands.hpp"
#include <fstream>
#include <iterator>
#include <limits>
#include "inputFunctions.hpp"
#include "messageFunctions.hpp"

void redko::help(const std::string & descr)
{
  if (descr.empty())
  {
    std::cout << "help\n";
    std::cout << "      see list of commands\n";
    std::cout << "code\n";
    std::cout << "      encode text from input\n";
    std::cout << "      finish text input by typing <end> on a new line\n";
    std::cout << "code <filename>\n";
    std::cout << "      encode text from the file\n";
    std::cout << "decode\n";
    std::cout << "      decode text from input\n";
    std::cout << "      enter the encoded text first, then the alphabet encoding\n";
    std::cout << "      finish the alphabet encoding input by typing <end> on a new line\n";
    std::cout << "decode <filename>\n";
    std::cout << "      decode text from the file\n";
    std::cout << "      the first part of the file must contain encoded text\n";
    std::cout << "      the second part of the file must contain the alphabet encoding\n";
    std::cout << "recode <filename1> <filename2>\n";
    std::cout << "      unite and encode the text from both files\n";
    std::cout << "      the first part of the file must contain encoded text\n";
    std::cout << "      the second part of the file must contain the alphabet encoding\n";
    std::cout << "print\n";
    std::cout << "      display result on the screen\n";
    std::cout << "save <filename>\n";
    std::cout << "      save result to the file\n";
    std::cout << "quit\n";
    std::cout << "      exit the result processing mode\n";
    std::cout << "      exit the program when there is nothing to work with\n";
    std::cout << "compare <filename1> <filename2>\n";
    std::cout << "      compare encodings of identical characters in files\n";
  }
  else
  {
    printInvalidMessage(std::cout);
  }
}

void redko::code(const std::string & descr)
{
  std::string str = "";
  std::string res = "";

  if (descr.empty())
  {
    while (std::getline(std::cin, str) && str != "end")
    {
      res += str;
      res += '\n';
    }
  }
  else
  {
    std::ifstream input(descr);
    if (!input)
    {
      printInvalidFile(std::cout);
      return;
    }
    std::getline(input, res);
    while (std::getline(input, str))
    {
      res += '\n';
      res += str;
    }
  }
  if (res.empty())
  {
    printEmptyInput(std::cout);
    return;
  }
  HuffmanCode obj(res);
  obj.encode();

  std::cout << "<succesfully encoded>\n";

  std::string description = "";
  while (std::getline(std::cin, description) && description != "quit")
  {
    if (description == "print")
    {
      print("code", obj);
    }
    else if (cutName(description) == "save")
    {
      save("code", description, obj);
    }
    else
    {
      printInvalidMessage(std::cout);
    }
  }
}

void redko::decode(const std::string & descr)
{
  HuffmanCode obj;

  if (descr.empty())
  {
    if (!(std::cin >> obj))
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      printInvalidFormat(std::cout);
      return;
    }
  }
  else
  {
    std::ifstream input(descr);
    if (!input)
    {
      printInvalidFile(std::cout);
      return;
    }
    if (!(input >> obj) && !input.eof())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      printInvalidFormat(std::cout);
      return;
    }
  }

  obj.decode();

  std::cout << "<succesfully decoded>\n";

  std::string description = "";
  while (std::getline(std::cin, description) && description != "quit")
  {
    if (description == "print")
    {
      print("decode", obj);
    }
    else if (cutName(description) == "save")
    {
      save("decode", description, obj);
    }
    else
    {
      printInvalidMessage(std::cout);
    }
  }
}

void redko::recode(const std::string & descr)
{
  std::string d = descr;
  std::fstream firstInput(cutName(d));
  std::fstream secondInput(cutName(d));

  if (!firstInput || !secondInput)
  {
    printInvalidFile(std::cout);
    return;
  }

  HuffmanCode firstObj;
  if (!(firstInput >> firstObj) && !firstInput.eof())
  {
    firstInput.clear();
    firstInput.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    printInvalidFormat(std::cout);
    return;
  }
  firstObj.decode();

  HuffmanCode secondObj;
  if (!(secondInput >> secondObj) && !secondInput.eof())
  {
    secondInput.clear();
    secondInput.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    printInvalidFormat(std::cout);
    return;
  }
  secondObj.decode();

  std::string united = firstObj.getDecoded() + secondObj.getDecoded();
  HuffmanCode result(united);
  result.encode();

  std::cout << "<succesfully recoded>\n";

  std::string description = "";
  while (std::getline(std::cin, description) && description != "quit")
  {
    if (description == "print")
    {
      print("code", result);
    }
    else if (cutName(description) == "save")
    {
      save("code", description, result);
    }
    else
    {
      printInvalidMessage(std::cout);
    }
  }
}

void redko::print(const std::string & command, HuffmanCode obj)
{
  if (command == "code")
  {
    std::cout << obj.getEncoded() << '\n';
  }
  else
  {
    std::cout << obj.getDecoded() << '\n';
  }
}

void redko::save(const std::string & command, const std::string & descr, HuffmanCode obj)
{
  std::ofstream output(descr);
  if (!output)
  {
    printInvalidFormat(std::cout);
    return;
  }

  if (command == "code")
  {
    output << obj.getEncoded();
    auto encoding = obj.getEncoding();
    for (auto i : encoding)
    {
      output << '\n' << i.second << " :" << i.first;
    }
  }
  else
  {
    output << obj.getDecoded();
  }
}

void redko::compare(const std::string & descr)
{
  std::string d = descr;
  std::fstream firstInput(cutName(d));
  std::fstream secondInput(cutName(d));
  if (!firstInput || !secondInput)
  {
    printInvalidFile(std::cout);
    return;
  }

  HuffmanCode firstObj;
  if (!(firstInput >> firstObj) && !firstInput.eof())
  {
    firstInput.clear();
    firstInput.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    printInvalidFormat(std::cout);
    return;
  }
  auto firstEncoding = firstObj.getEncoding();

  HuffmanCode secondObj;
  if (!(secondInput >> secondObj) && !secondInput.eof())
  {
    secondInput.clear();
    secondInput.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    printInvalidFormat(std::cout);
    return;
  }
  auto secondEncoding = secondObj.getEncoding();
  size_t count = 0;
  for (auto curr = firstEncoding.begin(); curr != firstEncoding.end(); ++curr)
  {
    auto it = secondEncoding.find(curr->first);
    if (it != secondEncoding.end())
    {
      ++count;
      std::cout << curr->first << ": " << curr->second << ' ' << it->second << '\n';
    }
  }
  if (count == 0)
  {
    std::cout << "<no matching symbols>\n";
  }
}
