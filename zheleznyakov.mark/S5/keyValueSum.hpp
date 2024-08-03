#ifndef KEY_VALUE_SUM_HPP
#define KEY_VALUE_SUM_HPP
#include <string>

namespace zheleznyakov
{
  struct KeyValueSum
  {
  public:
    KeyValueSum();

    void operator()(std::pair< long long, std::string >);

    long long getKeySum();
    std::string getValueSum();
  private:
    long long keySum_;
    std::string valueSum_;
  };
}
#endif
