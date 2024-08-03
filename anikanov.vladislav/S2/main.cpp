#include <fstream>
#include <iostream>
#include <string>
#include <queue.hpp>
#include <stack.hpp>
#include "mainExtension.hpp"
#include "elementOfExpression.hpp"

int main(int argc, char *argv[])
{
  using namespace anikanov;
  std::string expression;
  anikanov::Queue< std::shared_ptr< ElementOfExpression > > postfix;
  anikanov::Stack< long long > answers;
  std::ifstream ifstream;

  if (argc > 2) {
    std::cerr << "Wrong count of arguments\n";
    return 3;
  }

  if (argc == 2) {
    ifstream = std::ifstream(argv[1]);
  }

  std::istream &input = (argc >= 2) ? ifstream : std::cin;

  while (std::getline(input, expression)) {
    if (expression.empty()) {
      expression.clear();
      continue;
    }

    try {
      postfix = toPostfix(expression);
      answers.push(calculate(postfix));
    } catch (const std::logic_error &err) {
      std::cerr << err.what() << "\n";
      return 1;
    } catch (const std::runtime_error &err) {
      std::cerr << err.what() << "\n";
      return 2;
    }

    expression.clear();
  }

  while (!answers.isEmpty()) {
    std::cout << answers.top();
    answers.pop();
    if (!answers.isEmpty()) {
      std::cout << " ";
    }
  }

  std::cout << "\n";

  return 0;
}
