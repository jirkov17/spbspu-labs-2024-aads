#ifndef SEQUENCEHANDLER_H
#define SEQUENCEHANDLER_H

#include <string>
#include <List.hpp>

namespace zhitnyj {
  class SequenceHandler {
  public:
    SequenceHandler() = default;

    void addSequence(const std::string &name, const List< unsigned long long > &sequence);
    void calculateSums();
    void printSequences();
    void printSequencesNames();

  private:
    List< std::string > names;
    List< List< unsigned long long > > sequences;
  };
}

#endif
