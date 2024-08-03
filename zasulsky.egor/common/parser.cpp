#include "parser.hpp"
#include <string>
#include <iostream>

 Parser::Parser(std::string toparse) :
  parsable_(toparse),
  current_(toparse.find_first_not_of(" "))
{}

std::string Parser::operator ()()
{
  if (current_ > parsable_.length())
  {
    return "";
  }
  size_t start = current_;
  size_t end = 0;
  auto pos = parsable_.substr(current_).find_first_of(" ");
  if (pos == std::string::npos)
    end = parsable_.length();
  else
    end = current_ + parsable_.substr(current_).find_first_of(" ");
  current_ = 1 + end;
  return parsable_.substr(start, end - start);
}
