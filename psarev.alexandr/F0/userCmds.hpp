#ifndef USER_CMDS_HPP
#define USER_CMDS_HPP
#include "internalFuncs.hpp"

namespace psarev
{
  using storage_t = avlTree< std::string, List< std::string > >;

  void cmdHelp(std::istream& in, std::ostream& out);
  void cmdCreate(std::istream& in, std::ostream& out, avlTree< std::string, storage_t >& depot, std::string dest);
  void cmdDelete(std::istream& in, std::ostream& out, avlTree< std::string, storage_t >& depot);
  void cmdList(std::ostream& out, avlTree< std::string, storage_t >& depot);
  void cmdShow(std::istream& in, std::ostream& out, avlTree< std::string, storage_t >& depot);
  void cmdRename(std::istream& in, std::ostream& out, avlTree< std::string, storage_t >& depot);
  void cmdChoose(std::istream& in, std::ostream& out, avlTree< std::string, storage_t >& depot, std::string& storage);
  void cmdSave(std::istream& in, std::ostream& out, avlTree< std::string, storage_t >& depot);

  void cmdPrint(std::istream& in, std::ostream& out, avlTree< std::string, storage_t >& depot, std::string& storage);
  void cmdFono(std::istream& in, std::ostream& out);
  void cmdMakeSent(std::istream& in, std::ostream& out, avlTree< std::string, storage_t >& depot, std::string& storage);
}

#endif
