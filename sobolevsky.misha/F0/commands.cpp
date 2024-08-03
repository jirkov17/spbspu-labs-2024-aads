#include "commands.hpp"
#include <string>
#include <limits>
#include <algorithm>
#include <functional>
#include <cmath>
#include <cctype>
#include "myMultiMap.hpp"
#include "myMap.hpp"
#include "myList.hpp"
#include "utilsForDictsAndErrors.hpp"

using mypair = std::pair< std::string, sobolevsky::MyMultiMap< size_t, std::string > >;

void sobolevsky::getCommands(std::istream & in, std::ostream & out)
{
  if (in.get() != '\n')
  {
    throw std::exception();
  }
  out << "1.commands - output of the list of commands available to the user\n";
  out << "2.loadAndCreate < filename > - loading text from a file and creating a frequency dictionary\n";
  out << "3.delete < name > - frequency dictionary deletion\n";
  out << "4.allDicts - displays the names of all dictionaries\n";
  out << "5.compareDicts < name1 > < name2 > - comparison of two frequency dictionaries\n";
  out << "6.rename < oldName > < newName > - dictionary renaming\n";
  out << "7.select < name > - selecting a vocabulary for further work specifically with that vocabulary alone\n";
  out << "7.1.1.holyTrinity - outputs the three most frequently occurring words in the dictionary\n";
  out << "7.1.2.holyTrinity -amount - outputs the three most frequently occurring words in the dictionary\n";
  out << "7.2.1.printDict -(n/all) - output a sorted list of a certain number of words without their frequency\n";
  out << "7.2.2.printDict -(n/all) -amount - output a sorted list of a certain number of words with their frequency\n";
  out << "7.3.unigueWords - outputs a list of unique words with no repetitions\n";
  out << "7.4.wordCount - outputs the number of words in the text\n";
  out << "7.5.save < filename > - saves the entire sorted frequency dictionary to a file\n";
}

void sobolevsky::getLoadAndCreate(std::shared_ptr< sobolevsky::List< mypair > > myVec, std::istream & in)
{
  if (in.get() == '\n')
  {
    error(std::cerr);
    return;
  }
  std::string file;
  in >> file;
  std::ifstream text(file);
  if (!text)
  {
    errorInpName(std::cerr);
    return;
  }
  if (in.get() != '\n')
  {
    error(std::cerr);
    return;
  }

  sobolevsky::MyMap< std::string, size_t > myMap;
  while (!text.eof())
  {
    if (text.fail())
    {
      text.clear();
      text.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::string word;
    text >> word;
    std::transform(word.begin(), word.end(), word.begin(), charCheck);
    word.erase(remove(word.begin(),word.end(),0),word.end());
    if (word.length() < 1)
    {
      continue;
    }
    if (myMap.find(word) == myMap.end())
    {
      myMap.insert(std::make_pair(word, 1));
    }
    else
    {
      myMap.find(word)->second++;
    }
  }

  MyMultiMap< size_t, std::string > myMultiMap;
  for (std::pair< std::string, size_t > const &pair : myMap)
  {
    myMultiMap.insert(std::make_pair(pair.second, pair.first));
  }
  myVec->pushBack(std::pair< std::string, MyMultiMap<size_t, std::string> >(file, myMultiMap));
}

void sobolevsky::getDelete(std::shared_ptr< sobolevsky::List< mypair > > myVec, std::istream & in)
{
  if (in.get() == '\n')
  {
    error(std::cerr);
    return;
  }
  std::string name;
  in >> name;
  if (in.get() != '\n')
  {
    error(std::cerr);
  }
  if (findIf(myVec->begin(), myVec->end(), name) == myVec->end())
  {
    errorInpName(std::cerr);
    return;
  }
  else
  {
    myVec->erase(findIf(myVec->begin(), myVec->end(), name));
  }
}

void sobolevsky::getAllDicts(std::shared_ptr< sobolevsky::List< mypair > > myVec,std::istream & in, std::ostream & out)
{
  if (myVec->size() == 0)
  {
    errorInpName(std::cerr);
    return;
  }

  if (in.get() != '\n')
  {
    error(std::cerr);
    return;
  }

  for (mypair &pair : *myVec)
  {
    out << pair.first << "\n";
  }
}

void sobolevsky::getRename(std::shared_ptr< sobolevsky::List< mypair > > myVec, std::istream & in)
{
  if (in.get() == '\n')
  {
    error(std::cerr);
    return;
  }
  std::string oldName, newName;
  in >> oldName >> newName;
  if(findIf(myVec->begin(), myVec->end(), oldName) != myVec->end() &&
  findIf(myVec->begin(), myVec->end(), newName) == myVec->end())
  {
    findIf(myVec->begin(), myVec->end(), oldName)->first = newName;
  }
  else
  {
    errorInpName(std::cerr);
    return;
  }
  if (in.get() != '\n')
  {
    error(std::cerr);
    return;
  }
}

void sobolevsky::getCompareDicts(std::shared_ptr< sobolevsky::List< mypair > > myVec, std::istream & in, std::ostream & out)
{
  if (in.get() == '\n')
  {
    error(std::cerr);
    return;
  }
  if (myVec->size() < 2)
  {
    errorInpName(std::cerr);
    return;
  }
  std::string name1, name2;
  in >> name1 >> name2;
  if(findIf(myVec->begin(), myVec->end(), name1) != myVec->end() &&
  findIf(myVec->begin(), myVec->end(), name2) != myVec->end())
  {
    mypair pair1(*findIf(myVec->begin(), myVec->end(), name1));
    mypair pair2(*findIf(myVec->begin(), myVec->end(), name2));
    MyMap< std::string, size_t > allwords;
    for (typename MyMultiMap< size_t, std::string >::Iterator iter = pair1.second.begin(); iter != pair1.second.end(); iter++)
    {
      if (iter->size() == 1)
      {
        allwords.insert(std::make_pair((*iter)[0], 0));
      }
      else
      {
        for (size_t i = 0; i < iter->size(); i++)
        {
          allwords.insert(std::make_pair((*iter)[i], 0));
        }
      }
    }
    for (typename MyMultiMap< size_t, std::string >::Iterator iter = pair2.second.begin(); iter != pair2.second.end(); iter++)
    {
      if (iter->size() == 1)
      {
        allwords.insert(std::make_pair((*iter)[0], 0));
      }
      else
      {
        for (size_t i = 0; i < iter->size(); i++)
        {
          allwords.insert(std::make_pair((*iter)[i], 0));
        }
      }
    }
    MyMap< std::string, size_t > vec1(allwords);
    MyMap< std::string, size_t > vec2(allwords);
    for (typename MyMultiMap< size_t, std::string >::Iterator iter = pair1.second.begin(); iter != pair1.second.end(); iter++)
    {
      if (iter->size() == 1)
      {
        vec1.find((*iter)[0])->second++;
      }
      else
      {
        for (size_t i = 0; i < iter->size(); i++)
        {
          vec1.find((*iter)[i])->second++;
        }
      }
    }
    for (typename MyMultiMap< size_t, std::string >::Iterator iter = pair2.second.begin(); iter != pair2.second.end(); iter++)
    {
      if (iter->size() == 1)
      {
        vec2.find((*iter)[0])->second++;
      }
      else
      {
        for (size_t i = 0; i < iter->size(); i++)
        {
          vec2.find((*iter)[i])->second++;
        }
      }
    }
    size_t productOfVecs = 0;
    size_t vecLenght1 = 0;
    size_t vecLenght2 = 0;
    for (std::pair< std::string, size_t > const &pair : allwords)
    {
      productOfVecs += (vec1.at(pair.first) * vec2.at(pair.first));
      vecLenght1 += vec1.at(pair.first) * vec1.at(pair.first);
      vecLenght2 += vec2.at(pair.first) * vec2.at(pair.first);
    }
    out << "similarity coefficient of two dictionaries: " << productOfVecs/(std::sqrt(vecLenght1) * std::sqrt(vecLenght2)) << "\n";
  }
  else
  {
    errorInpName(std::cerr);
    return;
  }
  if (in.get() != '\n')
  {
    error(std::cerr);
    return;
  }
}

void sobolevsky::holyTrinity(mypair &myPair, std::istream & in, std::ostream & out)
{
  if (in.get() == '\n')
  {
    dictOutput(myPair, out, 3, false);
  }
  else
  {
    std::string mode;
    in >> mode;
    if (mode == "-amount")
    {
      dictOutput(myPair, out, 3, true);
    }
    if (in.get() != '\n')
    {
      error(std::cerr);
      return;
    }
  }
}

void sobolevsky::printDict(mypair &myPair, std::istream & in, std::ostream & out)
{
  if (in.get() == '\n')
  {
    error(std::cerr);
    return;
  }
  char mode;
  in >> mode;
  if (mode == '-')
  {
    std::string mode2;
    in >> mode2;
    size_t numOfWords;
    if (mode2 == "all")
    {
      numOfWords = myPair.second.size();
    }
    else
    {
      numOfWords = std::stoull(mode2);
      if (numOfWords < 1 || numOfWords > myPair.second.size())
      {
        errorInpName(std::cerr);
        return;
      }
    }
    if (in.get() == '\n')
    {
      dictOutput(myPair, out, numOfWords, false);
    }
    else
    {
      std::string mode;
      in >> mode;
      if (mode == "-amount")
      {
        dictOutput(myPair, out, numOfWords, true);
      }
      if (in.get() != '\n')
      {
        error(std::cerr);
        return;
      }
    }
  }
}

void sobolevsky::uniqeWords(mypair &myPair, std::istream & in, std::ostream & out)
{
  if (in.get() != '\n')
  {
    error(std::cerr);
    return;
  }
  for (MyMultiMap< size_t, std::string >::Iterator iter = myPair.second.begin(); iter != myPair.second.end(); iter++)
  {
    if (iter->size() == 1)
    {
      out << (*iter)[0] << "\n";
    }
    else
    {
      break;
    }
  }
}

void sobolevsky::wordCount(mypair &myPair, std::istream & in, std::ostream & out)
{
  if (in.get() != '\n')
  {
    error(std::cerr);
    return;
  }
  out << myPair.second.size() << "\n";
}

void sobolevsky::save(mypair &myPair, std::istream &in)
{
  if (in.get() == '\n')
  {
    error(std::cerr);
    return;
  }
  std::string fileName;
  in >> fileName;
  std::ofstream file(fileName);
  if (!file)
  {
    errorInpName(std::cerr);
    return;
  }
  if (in.get() != '\n')
  {
    error(std::cerr);
    return;
  }
  dictOutput(myPair, file, myPair.second.size(), true);
}

void sobolevsky::getSelect(std::shared_ptr< sobolevsky::List< mypair > > myVec, std::istream & in, std::ostream & out)
{
  if (in.get() == '\n')
  {
    error(std::cerr);
    return;
  }
  std::string name;
  in >> name;
  if (findIf(myVec->begin(), myVec->end(), name) == myVec->end())
  {
    errorInpName(std::cerr);
    return;
  }
  mypair currPair(*findIf(myVec->begin(), myVec->end(), name));
  std::map< std::string, std::function< void(mypair &, std::istream &, std::ostream &) > > commands;
  commands["holyTrinity"] = holyTrinity;
  commands["printDict"] = printDict;
  commands["uniqueWords"] = uniqeWords;
  commands["wordCount"] = wordCount;
  commands["save"] = std::bind(save, std::placeholders::_1, std::placeholders::_2);
  std::string cmd;
  while (in >> cmd)
  {
    commands.at(cmd)(currPair, in, out);
  }
}
