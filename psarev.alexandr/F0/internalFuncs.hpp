#ifndef INTERNAL_FUNCS_HPP
#define INTERNAL_FUNCS_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <list.hpp>
#include <avlTree.hpp>

namespace psarev
{
  using storage_t = avlTree< std::string, List< std::string > >;

  std::ostream& outInvCommand(std::ostream& out);
  std::ostream& outEmptyFile(std::ostream& out);
  std::ostream& outEmptyFile(std::ostream& out);
  std::ostream& outEmptyFile(std::ostream& out);
  std::ostream& outSucCreate(std::ostream& out, const std::string name);
  std::ostream& outSucChoose(std::ostream& out, const std::string name);
  std::ostream& outSucDelete(std::ostream& out, const std::string name);
  std::ostream& outStoreName(std::ostream& out, const std::string name);
  std::ostream& outDirectWrite(std::ostream& out);
  std::ostream& outAdmMessage(std::ostream& out);
  std::ostream& outTypesAmount(std::ostream& out, const std::string type, size_t amo);

  storage_t readStorage(std::istream& in);

  void cleanUpWord(std::string& word);
  bool checkLiter(const std::string& word);

  std::string getSpType(std::string& word);
  bool checkType(std::string& word, size_t& endSize, List< std::string >& ends);

  void outDepot(std::string dest, std::ofstream& out, avlTree< std::string, storage_t >& depot);

  int letToSound(int let, bool& softFact);
  bool printSound(std::ostream& out, int sound, bool softFact);
}

#endif
