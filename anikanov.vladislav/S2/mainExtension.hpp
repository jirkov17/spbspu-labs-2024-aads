#ifndef MAINEXTENSION_HPP
#define MAINEXTENSION_HPP

#include <string>
#include "elementOfExpression.hpp"
#include <queue.hpp>
#include "operation.hpp"

namespace anikanov {

  using elementType = std::shared_ptr< anikanov::ElementOfExpression >;

  bool checkPriority(const elementType &first, const std::shared_ptr< anikanov::Operation > &second);

  bool checkForward(const elementType &element);

  anikanov::Queue< std::shared_ptr< anikanov::ElementOfExpression > > toPostfix(const std::string &exp);

  long long calculate(anikanov::Queue< std::shared_ptr< anikanov::ElementOfExpression > > &postfix);
}

#endif
