#include "inputFunctions.hpp"
#include <istream>
#include "typing.hpp"
#include "computationalFunctions.hpp"

void ponomarev::inputExpressions(std::istream & input, Queue< std::string > & expressions)
{
  std::string expression = "";
  while (!input.eof())
  {
    std::getline(input, expression);
    if (!expression.empty())
    {
      expressions.push(expression);
    }
  }
}

void ponomarev::getResults(Queue< std::string > & expressions, Stack< long long > & res)
{
  std::string expression;
  long long resOfExpression = 0;
  Postfix postfix;

  while (!expressions.isEmpty())
  {
    expression = expressions.getElem();
    expressions.pop();
    resOfExpression = calculate(expression);
    res.push(resOfExpression);
  }
}
