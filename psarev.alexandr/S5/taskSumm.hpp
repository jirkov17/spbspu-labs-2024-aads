#ifndef TASK_SUMM_HPP
#define TASK_SUMM_HPP
#include <string>
#include <avlTree.hpp>

namespace psarev
{
  struct TaskSumm
  {
  public:
    TaskSumm();
    ~TaskSumm() = default;

    void operator()(const std::pair< const long long, std::string >& dataPair);

    long long getKeySumm();
    std::string getValSumm();

  private:
    long long keySumm;
    std::string valSumm;
  };
}

#endif
