#ifndef OUTPUT_HPP
#define OUTPUT_HPP
#include <istream>

namespace zheleznyakov
{
  namespace output
  {
    template< typename Container >
    void iterOut(Container & c, std::ostream & out)
    {
      auto iter(c.begin());
      while (iter != c.end())
      {
        out << (*iter);
        out << (++iter == c.end() ? '\n' : ' ');
      }
    }
  }

  namespace errors
  {
    void wrongArgsCount(std::ostream & out)
    {
      out << "Wrong arguments count\n";
    }

    void wrongSortOrder(std::ostream & out)
    {
      out << "Wrong sort order\n";
    }

    void wrongDataType(std::ostream & out)
    {
      out << "Wrong data type\n";
    }

    void wrongSize(std::ostream & out)
    {
      out << "Wrong size\n";
    }

    void outExecution(std::ostream & out)
    {
      out << "Execution error occured\n";
    }
  }
}
#endif
