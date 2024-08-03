#include "processing.hpp"
#include "types.hpp"

mihalchenko::List< char > mihalchenko::getListFromString(const std::string strToList)
{
  List< char > list;
  for (size_t n = 0; n < strToList.length(); n++)
  {
    list.push_back(strToList[n]);
  }
  return list;
}

void mihalchenko::printedResult(std::ostream &out, Stack< long long > &stack, size_t &num)
{
  for (size_t i = 0; i < num; i++)
  {
    out << stack.getT();
    stack.pop();
    if (i != num - 1)
    {
      out << " ";
    }
  }
  out << std::endl;
}

size_t mihalchenko::calculatePostFix(Queue< std::string > &resiveDigit, Stack< long long > &calculateResult)
{
  FinalTransform finTrans;
  List< char > list = getListFromString("()+-*/%");
  long long llMax = std::numeric_limits< long long >::max();
  long long i = resiveDigit.getSize();
  while ((i > 0) && (i != llMax))
  {
    bool flag = false;
    for (size_t j = 0; j < list.getSize(); j++)
    {
      if (list[j] == resiveDigit[i - 1][0])
      {
        flag = true;
        break;
      }
    }
    if (!flag)
    {
      finTrans.calcRezult.push(stoll(resiveDigit[i - 1]));
      finTrans.commands.push('.');
    }
    else
    {
      finTrans.commands.push(resiveDigit[i - 1][0]);
    }
    i -= 1;
  }

  if (!finTrans.calculate())
  {
    return llMax;
  }

  if (finTrans.calcRezult.getSize() > 0)
  {
    calculateResult.push(finTrans.calcRezult[0].data_);
  }
  resiveDigit.clear();
  resiveDigit.setSize(0);
  return calculateResult.getSize();
}

bool mihalchenko::bildStrPostFix(std::string &currentStr, size_t currentStrSize,
                                  Queue< std::string > &resiveDigit, Stack< std::string > &resiveControl)
{
  size_t ullMax = std::numeric_limits< size_t >::max();
  if (resiveControl.getSize() == ullMax)
  {
    resiveControl.setSize(0);
  }
  bool flgResult = true;
  size_t i = 0;
  std::string elementStr;
  std::string prewCommand = "";
  int counterSc = 0;
  while (i < currentStrSize)
  {
    size_t posWhite = currentStr.find(' ');
    if ((posWhite > 0) && (posWhite != std::string::npos))
    {
      elementStr = currentStr.substr(0, posWhite);
      currentStr.erase(0, posWhite + 1);
      i += posWhite + 1;
    }
    else
    {
      if (currentStr.find(' ') <= currentStr.size())
      {
        elementStr = "";
        currentStr.erase(0, 1);
        i++;
      }
      else
      {
        elementStr = currentStr;
        i += currentStr.size();
      }
    }
    if (elementStr.size() > 0)
    {
      List< char > list1 = getListFromString("()+-*/%");
      bool flag = false;
      for (size_t j = 0; j < list1.getSize(); j++)
      {
        if (list1[j] == elementStr[0])
        {
          flag = true;
        }
      }
      if ((elementStr.size() == 1) && (flag))
      {
        if (elementStr[0] == ')')
        {
          counterSc = counterSc - 1;
          std::string strFS;
          do
          {
            if ((resiveControl.getSize() == 0) || (resiveControl.getSize() == ullMax))
            {
              std::cout << "The logic is broken" << std::endl;
              flgResult = false;
            }
            strFS = resiveControl.getT();
            resiveControl.pop();
            if (strFS != "(")
            {
              resiveDigit.push(strFS);
            }
          } while ((strFS[0] != '(') && (resiveControl.getSize() > 0));
        }
        else if ((prewCommand == "(") || (elementStr[0] == '('))
        {
          resiveControl.push(elementStr);
          if (elementStr[0] == '(')
          {
            counterSc = counterSc + 1;
          }
        }
        else
        {
          if ((resiveControl.getSize() > 0) && (resiveControl.getSize() != ullMax))
          {
            resiveDigit.push(resiveControl.getT());
            resiveControl.pop();
          }
          resiveControl.push(elementStr);
        }
        prewCommand = elementStr;
      }
      else
      {
        resiveDigit.push(elementStr);
      }
    }
    else
    {
      std::cerr << "The logic is broken" << std::endl;
      flgResult = false;
    }
  }
  if (counterSc != 0)
  {
    std::cerr << "Incorrect number of brackets" << std::endl;
    flgResult = false;
  }
  while ((resiveControl.getSize() > 0) && (resiveControl.getSize() != ullMax))
  {
    resiveDigit.push(resiveControl.getT());
    resiveControl.pop();
  }
  return flgResult;
}
