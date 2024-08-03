#ifndef DATAPROCESSING_HPP
#define DATAPROCESSING_HPP
#include <iosfwd>
#include "Stack.hpp"
#include "Queue.hpp"
#include "DataTypes.hpp"

namespace sukacheva {
  Queue< std::string > inputStatement(std::istream& input);
  Postfix makePostfix(Queue< std::string >& infix);
  long long calculate(Postfix& postfix);
}
#endif
