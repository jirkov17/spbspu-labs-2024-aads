#include "internalFuncs.hpp"
#include <cctype>

std::ostream& psarev::outInvCommand(std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
  return out;
}

std::ostream& psarev::outEmptyFile(std::ostream& out)
{
  out << "Error: File is empty!\n";
  return out;
}

std::ostream& psarev::outSucCreate(std::ostream& out, std::string name)
{
  out << "Storage <" << name << "> has been created!\n";
  return out;
}

std::ostream& psarev::outSucChoose(std::ostream& out, std::string name)
{
  out << "Storage <" << name << "> has been choosen!\n";
  return out;
}

std::ostream& psarev::outSucDelete(std::ostream& out, std::string name)
{
  out << "Storage <" << name << "> has been deleted!\n";
  return out;
}

std::ostream& psarev::outStoreName(std::ostream& out, std::string name)
{
  out << "Storage <" << name << "> \n";
  return out;
}

std::ostream& psarev::outDirectWrite(std::ostream& out)
{
  out << "Whole depot was printed at the directory!\n";
  return out;
}

std::ostream& psarev::outAdmMessage(std::ostream& out)
{
  out << "Directory with that name already exists, do you want to overwrite it? (Y/N)\n";
  return out;
}

std::ostream& psarev::outTypesAmount(std::ostream& out, const std::string type, size_t amo)
{
  out << type << ": " << amo << " ";
  return out;
}

using storage_t = psarev::avlTree< std::string, psarev::List< std::string > >;

psarev::avlTree< std::string, psarev::List< std::string > > psarev::readStorage(std::istream& in)
{
  storage_t resStorage;
  std::string word = "";

  while (!in.eof())
  {
    if (in >> word)
    {
      cleanUpWord(word);
      if (checkLiter(word))
      {
        std::string spType = getSpType(word);
        auto scanFor = resStorage.find(spType);
        if (scanFor == resStorage.end())
        {
          List< std::string > words;
          words.pushBack(word);
          resStorage.insert({ spType, words });
        }
        else
        {
          (resStorage.at(spType)).pushBack(word);
        }
      }
    }
  }
  return resStorage;
}

void psarev::cleanUpWord(std::string& word)
{
  const std::string puncts = ".,:;?!";
  for (char p : puncts)
  {
    if (word.back() == p)
    {
      word.pop_back();
    }
  }

  const std::string extras = "(){}[]<>'";
  for (char ex : extras)
  {
    if (word.back() == ex)
    {
      word.pop_back();
    }
    if (word.front() == ex)
    {
      word.erase(word.begin());
    }
  }
}

bool psarev::checkLiter(const std::string& word)
{
  for (char c : word)
  {
    if (!isalpha(c))
    {
      return false;
    }
  }
  return true;
}

std::string psarev::getSpType(std::string& word)
{
  std::string resType = "";
  storage_t rusEnds;

  rusEnds["noun"] = { "а", "ев", "ов", "ье", "иями", "ями", "ами", "еи", "ии", "и", "ией" };
  List< std::string > nSec = { "ем", "ам", "ом", "о", "у", "ах", "иях", "ях" };
  List< std::string > nThi = { "я", "ок", "мва", "яна", "ровать", "ег", "ги" };
  List< std::string > nFou = { "ий", "й", "иям", "ю", "ия", "ья", "ям", "ием" };
  List< std::string > nFif = { "ы", "ь", "ию", "ью", "га", "сть", "сти", "ей", "ой" };
  rusEnds["noun"].insert(rusEnds["noun"].end(), nSec.begin(), nSec.end());
  rusEnds["noun"].insert(rusEnds["noun"].end(), nThi.begin(), nThi.end());
  rusEnds["noun"].insert(rusEnds["noun"].end(), nFou.begin(), nFou.end());
  rusEnds["noun"].insert(rusEnds["noun"].end(), nFif.begin(), nFif.end());

  rusEnds["verb"] = { "ила", "ыла", "ена", "ейте", "уйте", "ите", "или", "ыли", "ей", "уй" };
  List< std::string > vSec = { "ено", "ят", "ует", "уют", "ит", "ыт", "ены", "ить" };
  List< std::string > vThi = { "на", "ете", "йте", "ли", "й", "л", "ем", "н", "ло" };
  List< std::string > vFou = { "им", "ым", "ен", "ило", "ыло", "ть", "ешь", "нно", "ет" };
  List< std::string > vFif = { "ыть", "ишь", "ую", "ют", "ны", "ю", "ла", "ил", "ыл" };
  rusEnds["verb"].insert(rusEnds["verb"].end(), vSec.begin(), vSec.end());
  rusEnds["verb"].insert(rusEnds["verb"].end(), vThi.begin(), vThi.end());
  rusEnds["verb"].insert(rusEnds["verb"].end(), vFou.begin(), vFou.end());
  rusEnds["verb"].insert(rusEnds["verb"].end(), vFif.begin(), vFif.end());

  rusEnds["adjective"] = { "ее", "ие", "ые", "ое", "ими", "ыми", "ей", "ий", "ый", "ой" };
  List< std::string > aSec = { "его", "ого", "ему", "ому", "их", "ых", "ую", "юю" };
  List< std::string > aThi = { "ая", "яя", "ою", "ею", "ем", "им", "ым", "ом" };
  rusEnds["adjective"].insert(rusEnds["adjective"].end(), aSec.begin(), aSec.end());
  rusEnds["adjective"].insert(rusEnds["adjective"].end(), aThi.begin(), aThi.end());

  rusEnds["adverb"] = { "чно", "еко", "око", "имо", "мно", "жно", "жко", "ело", "тно" };
  List< std::string > dSec = { "здо", "зко", "шо", "хо", "но", "льно" };
  rusEnds["adjective"].insert(rusEnds["adjective"].end(), dSec.begin(), dSec.end());

  rusEnds["numeric"] = { "много", "еро", "вое", "рое", "еро", "сти", "двух", "рех", "еми" };
  List< std::string > uSec = { "дного", "сот", "сто", "ста", "тысяча", "тысячи" };
  List< std::string > uThi = { "мью", "тью", "одним", "умя", "тью", "мя", "тью" };
  List< std::string > uFou = { "три", "одна", "яти", "ьми", "ати", "две" };
  rusEnds["numeric"].insert(rusEnds["numeric"].end(), uSec.begin(), uSec.end());
  rusEnds["numeric"].insert(rusEnds["numeric"].end(), uThi.begin(), uThi.end());
  rusEnds["numeric"].insert(rusEnds["numeric"].end(), uFou.begin(), uFou.end());

  rusEnds["conjuct"] = { "более", "менее", "очень", "крайне", "когда", "однако", "если" };
  List< std::string > cSec = { "зато", "что", "или", "потом", "это", "того", "тоже" };
  List< std::string > cThi = { "и", "да", "кабы", "коли", "ничем", "чем", "также" };
  List< std::string > cFou = { "словно", "ежели", "хотя", "как", "так", "чтоб" };
  rusEnds["conjuct"].insert(rusEnds["conjuct"].end(), cSec.begin(), cSec.end());
  rusEnds["conjuct"].insert(rusEnds["conjuct"].end(), cThi.begin(), cThi.end());
  rusEnds["conjuct"].insert(rusEnds["conjuct"].end(), cFou.begin(), cFou.end());

  rusEnds["prepos"] = { "в", "на", "slovo", "из", "за", "у", "от", "с", "об", "к", "перед" };
  List< std::string > pSec = { "из-под", "для", "про", "до", "о", "вокруг", "при" };
  List< std::string > pThi = { "возле", "из-за", "без", "между", "под", "около" };
  rusEnds["prepos"].insert(rusEnds["prepos"].end(), pSec.begin(), pSec.end());
  rusEnds["prepos"].insert(rusEnds["prepos"].end(), pThi.begin(), pThi.end());

  for (auto iter = rusEnds["prepos"].cbegin(); iter != rusEnds["prepos"].cend(); ++iter)
  {
    if (word == *iter)
    {
      return "Prepos";
    }
  }
  for (auto iter = rusEnds["conjuct"].cbegin(); iter != rusEnds["conjuct"].cend(); ++iter)
  {
    if (word == *iter)
    {
      return "Conjuct";
    }
  }
  for (auto iter = rusEnds["numeric"].cbegin(); iter != rusEnds["numeric"].cend(); ++iter)
  {
    if (word == *iter)
    {
      return "Numeric";
    }
  }

  List< std::string > spTypes = { "noun", "verb", "adjective", "adverb", "numeric" };
  for (auto iter = spTypes.begin(); iter != spTypes.end(); ++iter)
  {
    for (size_t i = 0; i <= 6; i++)
    {
      if (checkType(word, i, rusEnds[*iter]))
      {
        return *iter;
      }
    }
  }

  return resType;
}

bool psarev::checkType(std::string& word, size_t& endSize, List< std::string >& ends)
{
  std::string endL = word.substr(word.length() - endSize);
  for (auto iter = ends.begin(); iter != ends.end(); ++iter)
  {
    if (endL == *iter)
    {
      return true;
    }
  }
  return false;
}

void psarev::outDepot(std::string dest, std::ofstream& out, avlTree< std::string, storage_t >& depot)
{
  for (auto storage : depot)
  {
    out.open(dest + "\\" + storage.first + ".txt");
    if (out.is_open())
    {
      for (auto iter : storage.second)
      {
        size_t len = (iter.second).getSize();
        for (size_t i = 0; i < len; i++)
        {
          out << iter.second[i] << " ";
        }
      }
    }
    out.close();
  }
}

int psarev::letToSound(int let, bool& softFact)
{
  const std::string softMakers = "ёйеячищюь";
  const std::string notSoftMakers = "цукнгшзхъфывапролджэсмтб";

  avlTree< int, int > softSounds = { { -11887, -12098 }, { -12103, -12103 }, { -11889, -12112 }, { -11897, -11897 },
  { -12104, -12104 }, { -11895, -11895 }, { -11890, -11901 } };

  for (int l : softMakers)
  {
    if (l == let)
    {
      softFact = true;
      return (*(softSounds.find(l))).second;
    }
  }

  avlTree< int, int > nSoftSounds = { { -11898, -11898 }, { -11901, -11901 }, { -12102, -12102 }, { -12099, -12099 },
  { -12109, -12102 }, { -11896, -11896 }, { -12105, -11903 }, { -11899, -11899 }, { -11900, -11900 },
  { -11893, -11893 }, { -12110, -12110 }, { -12112, -12112 }, { -12097, -12097 }, { -11904, -11904 },
  { -12098, -12098 }, { -12101, -12101 }, { -12108, -11902 }, { -12106, -11896 }, { -11891, -11891 },
  { -11903, -11903 }, { -12100, -12100 }, { -11902, -11902 }, { -12111, -12097 } };

  for (int l : notSoftMakers)
  {
    if (l == let)
    {
      softFact = false;
      return (*(nSoftSounds.find(l))).second;
    }
  }
  return ' ';
}

bool psarev::printSound(std::ostream& out, int sound, bool softFact)
{
  const std::string vowel = "уыаоэи";
  for (int l : vowel)
  {
    if (l == sound)
    {
      out << "[ " << sound << " ] - гласный";
      if (l == -12098 && softFact)
      {
        out << " ,ударный";
      }
      out << '\n';
      return true;
    }
  }

  const std::string deafNPair = "хцчщ";
  const std::string deafPair = "кшфпст";
  const std::string voicedNPair = "йнрмл";
  const std::string voicedPair = "гзвдж";
  for (int l : deafNPair)
  {
    if (l == sound)
    {
      out << "[ " << sound << " ] - согласный, глухой непарный";
      if ((softFact && l == -11899) || (l != -11899))
      {
        out << " ,мягкий";
        if (l == -11899)
        {
          out << " парный";
        }
        else
        {
          out << " непарный";
        }
      }
      else if (!softFact && l == -11899)
      {
        out << " ,твердый парный";
      }
      out << '\n';
      return false;
    }
  }

  for (int l : deafPair)
  {
    if (l == sound)
    {
      out << "[ " << sound << " ] - согласный, глухой парный";
      if (softFact && l != -11896)
      {
        out << " ,мягкий";
        if (l == -11896)
        {
          out << " непарный";
        }
        else
        {
          out << " парный";
        }
      }
      else
      {
        if (l == -11896)
        {
          out << " ,твердый непарный";
        }
        else
        {
          out << " ,твердый парный";
        }
      }
      out << '\n';
      return false;
    }
  }

  for (int l : voicedNPair)
  {
    if (l == sound)
    {
      out << "[ " << sound << " ] - согласный, звонкий непарный";
      if (l == -12103)
      {
        out << " ,мягкий непарный";
      }
      else if (softFact)
      {
        out << " ,мягкий парный";
      }
      else
      {
        out << " ,твердый парный";
      }
      out << '\n';
      return false;
    }
  }

  for (int l : voicedPair)
  {
    if (l == sound)
    {
      out << "[ " << sound << " ] - согласный, звонкий парный";
      if (softFact)
      {
        out << " ,мягкий парный";
      }
      else
      {
        out << " ,твердый парный";
      }
      out << '\n';
      return false;
    }
  }

  return false;
}
