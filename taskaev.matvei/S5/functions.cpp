#include <iostream>
#include <string>
#include <limits>
#include "functions.hpp"
#include <BSTree.hpp>
#include <Queue.hpp>

namespace taskaev
{
  bool numbers(const std::string& str)
  {
    size_t size = str.length();
    bool isFlag = false;
    if (size > 1 && str[0] == '-')
    {
      isFlag = true;
    }

    for (size_t i = 0; i < size; i++)
    {
      if (isFlag && i > 0 && !std::isdigit(str[i]))
      {
        return false;
      }
      else if (!isFlag && !std::isdigit(str[i]))
      {
        return false;
      }
    }
    return true;
  }

  void createTree(std::istream& in, BSTree< int, std::string >& tree)
  {
    std::string data = "";
    std::getline(in, data);
    if (!data.empty())
    {
      std::string temps = "";
      std::string names = "";
      size_t i = 0;
      int key = 0;
      while (i < data.length())
      {
        if (data[i] != ' ')
        {
          temps += data[i];
        }
        else
        {
          if (numbers(temps) == true)
          {
            try
            {
              key = std::stoi(temps);
            }
            catch (const std::out_of_range& e)
            {
              throw std::out_of_range("Error: VAlGRIND\n");
            }
            temps.clear();
          }
          else
          {
            names = temps;
            temps.clear();
            tree.insert(key, names);
          }
        }
        i++;
      }
      if (!names.empty())
      {
        names = temps;
        tree.insert(key, names);
      }
    }
  }

  void ascending(BSTree< int, std::string >& tree)
  {
    if (tree.empty())
    {
      errorEmpty(std::cout);
      return;
    }
    else
    {
      Queue< std::string > queue;
      long long result = 0;
      tree.traverse_lnr([&](const std::pair< const int, std::string >& value)
        {
          int max = std::numeric_limits< int >::max();
          int min = std::numeric_limits< int >::min();
          if (value.first > 0 && max - value.first < result)
          {
            throw std::overflow_error("Error: overflow\n");
          }
          else if (value.first < 0 && min - value.first > result)
          {
            throw std::underflow_error("Error: underflow\n");
          }
          result = result + value.first;
          queue.push(value.second);
        });
      std::cout << result << " ";
      while (!queue.isEmpty())
      {
        std::cout << queue.front();
        queue.pop();
        if (!queue.isEmpty())
        {
          std::cout << " ";
        }
        else
        {
          std::cout << "\n";
        }
      }
    }
  }

  void descending(BSTree< int, std::string >& tree)
  {
    if (tree.empty())
    {
      errorEmpty(std::cout);
      return;
    }
    else
    {
      Queue< std::string > queue;
      int result = 0;
      tree.traverse_rnl([&](const std::pair< const int, std::string >& value)
        {
          int max = std::numeric_limits< int >::max();
          int min = std::numeric_limits< int >::min();
          if (value.first > 0 && max - value.first < result)
          {
            throw std::overflow_error("Error: overflow\n");
          }
          else if (value.first < 0 && min - value.first > result)
          {
            throw std::underflow_error("Error: underflow\n");
          }
          result = result + value.first;
          queue.push(value.second);
        });
      std::cout << result << " ";
      while (!queue.isEmpty())
      {
        std::cout << queue.front();
        queue.pop();
        if (!queue.isEmpty())
        {
          std::cout << " ";
        }
        else
        {
          std::cout << "\n";
        }
      }
    }
  }

  void breadth(BSTree< int, std::string >& tree)
  {
    if (tree.empty())
    {
      errorEmpty(std::cout);
      return;
    }
    else
    {
      Queue< std::string > queue;
      int result = 0;
      tree.traverse_breadth([&](const std::pair< const int, std::string >& value)
        {
          int max = std::numeric_limits< int >::max();
          int min = std::numeric_limits< int >::min();
          if (value.first > 0 && max - value.first < result)
          {
            throw std::overflow_error("Error: overflow\n");
          }
          else if (value.first < 0 && min - value.first > result)
          {
            throw std::underflow_error("Error: underflow\n");
          }
          result = result + value.first;
          queue.push(value.second);
        });
      std::cout << result << " ";
      while (!queue.isEmpty())
      {
        std::cout << queue.front();
        queue.pop();
        if (!queue.isEmpty())
        {
          std::cout << " ";
        }
        else
        {
          std::cout << "\n";
        }
      }
    }
  }

  void errorEmpty(std::ostream& out)
  {
    out << "<EMPTY>\n";
  }

}
