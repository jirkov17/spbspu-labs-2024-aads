#include "userCmds.hpp"
#include <stdexcept>

void psarev::cmdHelp(std::istream& in, std::ostream& out)
{
  if (in.get() != '\n')
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  out << "1. help - Displaying commands available to the user.\n";
  out << "2. create < filename > < name > - Creating a storage < name >, with all the words from the text in the file < filename >.\n";
  out << "3. delete < name > - Deleting the < name > storage.\n";
  out << "4. list - Displaying the names of all existing storages.\n";
  out << "5. show < name > - Displaying all the speechType types and equivalent lists lengths in the < name > storage.\n";
  out << "6. rename < name > < newName > - Renaming < name > storage to < newName >.\n";
  out << "7. choose < name > - Selecting the < name > storage for further interaction with its elements.\n";
  out << "7.1 print < speechType > - Displaying a list of all words of the specified < speechType > from the choosed storage.\n";
  out << "7.2 fono < word > - Performing phonetic analisys of the word < word > and displaying the result on the screen.\n";
  out << "7.3 makeSent < num > - Making a sentence from < num > words in the choosed storage, if it possible.\n";
  out << "7.4 save < dest > - Saving whole depot to the < dest > directory.\n";
}

using storage_t = psarev::avlTree< std::string, psarev::List< std::string > >;

void psarev::cmdCreate(std::istream& in, std::ostream& out, psarev::avlTree< std::string, storage_t >& depot, std::string dest)
{
  std::string file;
  in >> file;
  if (!file.empty())
  {
    if (!dest.empty())
    {
      file = dest + "\\" + file;
    }
    std::ifstream fileIn;
    fileIn.open(file);
    if (fileIn.is_open())
    {
      std::string name;
      in >> name;
      if (!in)
      {
        psarev::outInvCommand(out);
      }
      depot.insert({ name, storage_t() });
      storage_t tempoStorage = depot[name];
      storage_t newStorage = psarev::readStorage(fileIn);
      tempoStorage = newStorage;
      psarev::outSucCreate(out, name);
    }
  }
  else
  {
    psarev::outEmptyFile(out);
  }
}

void psarev::cmdChoose(std::istream& in, std::ostream& out, avlTree< std::string, storage_t >& depot, std::string& storage)
{
  std::string chName;
  in >> chName;
  if (!in)
  {
    return;
  }

  auto chStorage = depot.find(chName);
  if (chStorage != depot.end())
  {
    storage = chName;
    psarev::outSucChoose(out, chName);
  }
  else
  {
    psarev::outInvCommand(out);
  }
}

void psarev::cmdDelete(std::istream& in, std::ostream& out, avlTree< std::string, storage_t >& depot)
{
  std::string tempoS;
  in >> tempoS;

  if (depot.erase(tempoS))
  {
    psarev::outSucChoose(out, tempoS);
  }
  else
  {
    psarev::outInvCommand(out);
  }
}

void psarev::cmdList(std::ostream& out, avlTree< std::string, storage_t >& depot)
{
  for (auto iter = depot.begin(); iter != depot.end(); ++iter)
  {
    psarev::outStoreName(out, (*iter).first);
  }
}

void psarev::cmdShow(std::istream& in, std::ostream& out, avlTree< std::string, storage_t >& depot)
{
  std::string tempoS;
  in >> tempoS;

  psarev::outStoreName(out, tempoS);

  for (auto iter = depot[tempoS].begin(); iter != depot[tempoS].end(); ++iter)
  {
    psarev::outTypesAmount(out, (*iter).first, ((*iter).second).getSize());
  }
}

void psarev::cmdRename(std::istream& in, std::ostream& out, avlTree< std::string, storage_t >& depot)
{
  std::string name;
  std::string newName;
  in >> name >> newName;

  auto desireSt = depot.find(name);
  if (desireSt != depot.end())
  {
    auto renamedSt = depot.find(newName);
    if (renamedSt == depot.end())
    {
      depot.insert({ newName, desireSt->second });
      depot.erase(desireSt->first);
    }
    else
    {
      psarev::outInvCommand(out);
    }
  }
  else
  {
    psarev::outInvCommand(out);
  }
}

void psarev::cmdSave(std::istream& in, std::ostream& out, avlTree< std::string, storage_t >& depot)
{
  std::string dest;
  in >> dest;
  std::string makeDest = "mkdir " + dest;

  std::ofstream fileOut;
  if (!std::system(makeDest.c_str()))
  {
    outDepot(dest, fileOut, depot);
    psarev::outDirectWrite(out);
  }
  else
  {
    psarev::outAdmMessage(out);

    std::string decis;
    in >> decis;
    if (decis == "Y")
    {
      outDepot(dest, fileOut, depot);
      psarev::outDirectWrite(out);
    }
    else
    {
      psarev::outInvCommand(out);
    }
  }
}

void psarev::cmdPrint(std::istream& in, std::ostream& out, avlTree<std::string, storage_t>& depot, std::string& storage)
{
  std::string speechType;
  in >> speechType;
  if (!in)
  {
    return;
  }
  auto chStorage = depot.find(storage);
  storage_t curStorage = (*chStorage).second;
  for (auto iter = curStorage.begin(); iter != curStorage.end(); iter++)
  {
    if ((*iter).first == speechType)
    {
      out << (*iter).first << ": \n";
      for (size_t i = 0; i < (*iter).second.getSize(); i++)
      {
        out << (*iter).second[i] << " ";
      }
      out << "\n";
    }
  }
}

void psarev::cmdFono(std::istream& in, std::ostream& out)
{
  std::string word;
  in >> word;
  if (!in)
  {
    return;
  }

  List< std::string > soundsVec;
  bool softFact = false;
  const std::string vowels = "ёуеыаоэяию";
  const std::string cons = "йцкнгшщзхфвпрлджчсмтб";
  const std::string other = "ъь";
  std::string transc = "[]";
  for (int let : word)
  {
    for (int l : vowels)
    {
      if (let == l)
      {
        transc += letToSound(let, softFact);
      }
    }
    for (int l : cons)
    {
      if (let == l)
      {
        transc += letToSound(let, softFact);
      }
      if (l == -11887 || l == -12107 || l == -11889 || l == -12104 || l == -11890)
      {
        softFact = true;
      }
      else
      {
        softFact = false;
      }
    }
    for (int l : other)
    {
      if (l == -11892)
      {
        softFact = true;
      }
    }
  }

  softFact = false;
  for (int s : transc)
  {
    if (s != '[' && s != ']')
    {
      softFact = printSound(out, s, softFact);
    }
  }
}

void psarev::cmdMakeSent(std::istream& in, std::ostream& out, avlTree<std::string, storage_t>& depot, std::string& storage)
{
  size_t usNum;
  in >> usNum;
  if (!in)
  {
    return;
  }

  auto chStorage = depot.find(storage);
  storage_t curStorage = (*chStorage).second;
  for (auto iter = curStorage.begin(); iter != curStorage.end(); iter++)
  {
    size_t curNum = 0;
    for (size_t i = 0; i < (*iter).second.getSize(); i++)
    {
      if (curNum <= usNum)
      {
        out << (*iter).second[i] << " ";
        curNum++;
      }
      else
      {
        break;
      }
    }
    out << "\n";
  }
}
