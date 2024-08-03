#include "dictionaryCommands.hpp"
#include <fstream>

void nikiforov::printCommands(std::ostream& out)
{
  out << " 1. help - displaying a list of available commands with parameters\n";
  out << " 2. create < filename > - creating a frequency dictionary from a filename file from a folder with a given name\n";
  out << " 3. open < mkdir > - reading all added frequency dictionaries from the mkdir folder\n";
  out << " 4. delete < name > - deleting a frequency dictionary with the name name\n";
  out << " 5. list - output the names of all existing frequency dictionaries\n";
  out << " 6. add < name1 > < name2 > - adding the name2 frequency dictionary to the name1 dictionary\n";
  out << " 7. unite < newname > < name1 > < name2 > - creating a newname dictionary by combining two dictionaries name1 and name2\n";
  out << " 8. rename < name > < newname > - renaming the dictionary name to newname\n";
  out << " 9. clear < name1 > < name2 > - deleting all words from the name1 dictionary that are in the name2 dictionary\n";
  out << " 10. save < mkdir > - saving dictionaries to the mkdir folder where dictionaries will be saved as files\n";
  out << " 11. select < name > - selecting the name dictionary for which the following commands will be executed\n";
  out << " 12. print - output of the entire sorted list of words with their frequency\n";
  out << " 13. print < most > < n > - the < most > option uses the n parameter to output the most frequently occurring n words\n";
  out << " 14. print < count > - the < count > option allows you to display the number of words in the dictionary\n";
  out << " 15. find < word > - find and display information about a word with the name word\n";
  out << " 16. erase < word > - deleting the word word\n";
}

std::string nikiforov::cutNameFile(std::string& str)
{
  size_t startPos = 0;
  size_t finalPos = str.find(".txt");
  if (str.find_last_of('\\') != std::string::npos)
  {
    startPos = str.find_last_of('\\') + 1;
    finalPos -= 4;
  }
  return std::string(str.substr(startPos, finalPos));
}

void nikiforov::createDict(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out, std::string mkdir)
{
  std::string fileName;
  in >> fileName;
  if (!fileName.empty())
  {
    if (!mkdir.empty())
    {
      fileName = mkdir + "\\" + fileName;
    }
    std::ifstream input;
    input.open(fileName);

    if (input.is_open())
    {
      std::string name = cutNameFile(fileName);
      nikiforov::AvlTree< std::string, size_t > dictionary;
      nikiforov::getDictionary(dictionary, input);
      mapDictionaries.emplace(name, dictionary);
      out << " The " << name << " dictionary has been added successfully\n";
    }
    else
    {
      out << " Invalid file name\n";
    }

    input.close();
  }
}

void nikiforov::getDictionary(nikiforov::AvlTree<std::string, size_t>& dictionary, std::istream& in)
{
  std::string word;

  while (!in.eof())
  {
    if (in >> word)
    {
      deleteDelimeters(word);
      if (checkAlpha(word))
      {
        auto search = dictionary.find(word);
        if (search == dictionary.end())
        {
          dictionary.emplace(word, 1);
        }
        else
        {
          dictionary.at(word) = search->second + 1;
        }
      }
    }
  }
}

void nikiforov::deleteDelimeters(std::string& str)
{
  nikiforov::AvlTree< char, char > delimiters;
  {
    delimiters.emplace('"', '"');
    delimiters.emplace('\'', '\'');
    delimiters.emplace('(', ')');
    delimiters.emplace('[', ']');
    delimiters.emplace('<', '>');
    delimiters.emplace('{', '}');
  }

  if ((str.back() == ',' || str.back() == '.' ||
    str.back() == ':' || str.back() == ';' ||
    str.back() == '!' || str.back() == '?'))
  {
    str.erase(str.end() - 1);
  }
  auto pairDelimetrs = delimiters.find(str.front());
  if (pairDelimetrs != delimiters.end())
  {
    if (str.back() == pairDelimetrs->second)
    {
      str.erase(str.end() - 1);
    }
    str.erase(str.begin());
  }
}

bool nikiforov::checkAlpha(std::string& str)
{
  for (size_t i = 0; i < str.size(); i++)
  {
    if (!isalpha(str.at(i)))
    {
      return false;
    }
  }
  return true;
}

void nikiforov::open(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string mkdir;
  in >> mkdir;
  std::string intermediateFile = "intermediateFileWithFiles.txt";
  std::string command = "dir " + mkdir + "\\*.txt /b > " + intermediateFile;
  if (!std::system(command.c_str()))
  {
    std::ifstream fin;
    fin.open(intermediateFile);
    while (!fin.eof())
    {
      createDict(mapDictionaries, fin, out, mkdir);
    }
    out << " The files in the folder have been successfully read\n";
  }
  else
  {
    out << " There is no folder with the specified name\n";
  }
}

void nikiforov::deleteDict(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string nameDictionaryToDel;
  in >> nameDictionaryToDel;

  if (mapDictionaries.erase(nameDictionaryToDel))
  {
    out << " The dictionary has been successfully deleted\n";
  }
  else
  {
    out << " The dictionary does not exist, or it has already been deleted\n";
  }
}

void nikiforov::printNamesDictionaries(const mapDictionaries_t& mapDictionaries, std::ostream& out)
{
  size_t count = 0;
  for (auto it = mapDictionaries.cbegin(); it != mapDictionaries.cend(); ++it) {
    out << ++count << ". " << it->first << "\n";
  }
}

void nikiforov::add(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string name1;
  std::string name2;

  in >> name1 >> name2;

  auto firstDictionary = mapDictionaries.find(name1);
  auto secondDictionary = mapDictionaries.find(name2);

  if (firstDictionary != mapDictionaries.end() && secondDictionary != mapDictionaries.end())
  {
    for (auto it = secondDictionary->second.begin(); it != secondDictionary->second.end(); ++it)
    {
      firstDictionary->second.emplace(it->first, it->second);
    }
    out << " Dictionary '" << name2 << "' successfully added to the dictionary '" << name1 << "'\n";
  }
  else
  {
    out << " Error: Adding a dictionary '" << name2 << "' to the dictionary '" << name1 << "'\n";
  }
}

void nikiforov::unit(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string newname;
  std::string name1;
  std::string name2;

  in >> newname >> name1 >> name2;

  if (newname != name1 && newname != name2)
  {
    auto firstDictionary = mapDictionaries.find(name1);
    auto secondDictionary = mapDictionaries.find(name2);

    if (firstDictionary != mapDictionaries.end() && secondDictionary != mapDictionaries.end())
    {
      nikiforov::AvlTree< std::string, size_t > newDictionary = firstDictionary->second;
      for (auto it = secondDictionary->second.begin(); it != secondDictionary->second.end(); ++it)
      {
        newDictionary.emplace(it->first, it->second);
      }
      mapDictionaries.emplace(newname, newDictionary);
      out << " Dictionary '" << name2 << "' successfully added to the dictionary '" << name1 << "'\n";
    }
    else
    {
      out << " Error: Dictionary merging '" << name1 << "' and '" << name2 << "' to the dictionary '" << newname << "'\n";
    }
  }
  else
  {
    out << " Error: Dictionary merging '" << name1 << "' and '" << name2 << "' to the dictionary '" << newname << "'\n";
  }
}

void nikiforov::rename(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string name;
  std::string newname;

  in >> name >> newname;

  auto nameDictionary = mapDictionaries.find(name);
  if (nameDictionary != mapDictionaries.end())
  {
    auto newnameDictionary = mapDictionaries.find(newname);
    if (newnameDictionary == mapDictionaries.end())
    {
      mapDictionaries.emplace(newname, nameDictionary->second);
      mapDictionaries.erase(nameDictionary->first);
      out << " The '" << name << "' dictionary has been successfully renamed to '" << newname << "'\n";
    }
    else
    {
      out << " Error: The dictionary '" << newname << "' already exists, enter a different name" << "\n";
    }
  }
  else
  {
    out << " Error: There is no dictionary with the name '" << name << "'\n";
  }
}

void nikiforov::clear(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string name1;
  std::string name2;

  in >> name1 >> name2;

  auto firstDictionary = mapDictionaries.find(name1);
  auto secondDictionary = mapDictionaries.find(name2);

  if (firstDictionary != mapDictionaries.end() && secondDictionary != mapDictionaries.end())
  {
    for (auto it = secondDictionary->second.begin(); it != secondDictionary->second.end(); ++it)
    {
      if (firstDictionary->second.find(it->first) != firstDictionary->second.end())
      {
        firstDictionary->second.erase(it->first);
      }
    }
    out << " All existing words in the '" << name2 << "' dictionary have been removed from the '" << name1 << "' dictionary\n";
  }
  else
  {
    out << " Error: One or both of the dictionaries do not exist\n";
  }
}

void nikiforov::save(const mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string nameMkdir;
  in >> nameMkdir;
  std::string commandCreateMkdir = "mkdir " + nameMkdir;

  std::ofstream fout;
  if (!std::system(commandCreateMkdir.c_str()))
  {
    writingDictionaries(mapDictionaries, nameMkdir, fout);
    out << " The data was successfully written to the folder" << nameMkdir << "\n";
  }
  else
  {
    out << " The folder already exists, do you want to overwrite it (yes/no)? \n";
    std::string consent;
    in >> consent;

    if (consent == "yes" || consent == "y")
    {
      writingDictionaries(mapDictionaries, nameMkdir, fout);
      out << " The data was successfully written to the folder" << nameMkdir << "\n";
    }
    else
    {
      out << "The data was not written to the folder " << nameMkdir << "\n";
    }
  }
}

void nikiforov::writingDictionaries(const mapDictionaries_t& mapDictionaries, std::string nameMkdir, std::ofstream& fout)
{
  for (auto it = mapDictionaries.cbegin(); it != mapDictionaries.cend(); ++it)
  {
    fout.open(nameMkdir + "\\" + it->first + ".txt");
    if (fout.is_open())
    {
      printWordAndFrequency(it->second.cbegin(), it->second.cend(), fout);
    }
    fout.close();
  }
}

void nikiforov::select(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out, std::string& nameSelectedDictionary)
{
  std::string nameDictionary;
  in >> nameDictionary;
  auto SelectedDictionary = mapDictionaries.find(nameDictionary);

  if (SelectedDictionary != mapDictionaries.end())
  {
    nameSelectedDictionary = SelectedDictionary->first;
    out << " The dictionary '" << nameDictionary << "' has been successfully selected\n";
  }
  else
  {
    out << " Error: Dictionary with the name '" << nameDictionary << "' does not exist\n";
  }
}

void nikiforov::printDict(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out, std::string nameSelectedDictionary)
{
  if (!nameSelectedDictionary.empty())
  {
    auto SelectedDictionary = mapDictionaries.find(nameSelectedDictionary);

    std::string option;
    if (in.get() != '\n' && in >> option)
    {
      if (option == "most")
      {
        printMost(SelectedDictionary->second, in, out);
      }
      else if (option == "count")
      {
        out << " The dictionary '" << nameSelectedDictionary << "' contains " << SelectedDictionary->second.getSize() << " words\n";
      }
      else
      {
        out << " Error: Invalid option\n";
      }
    }
    else
    {
      out << " The contents of the dictionary '" << nameSelectedDictionary << "':\n";
      for (auto iterPair = SelectedDictionary->second.begin(); iterPair != SelectedDictionary->second.end(); ++iterPair)
      {
        printWordAndFrequency(iterPair, out);
      }
    }
  }
  else
  {
    out << " The dictionary is not selected\n";
    out << " Select a dictionary using the command 'select < name >'\n";
  }
}

void nikiforov::printMost(nikiforov::AvlTree< std::string, size_t >& invertDictionary, std::istream& in, std::ostream& out)
{
  size_t numOfTheMostFrequent = 0;
  in >> numOfTheMostFrequent;
  out << " The " << numOfTheMostFrequent << " most common words\n";

  size_t count = 0;
  for (auto iterPair = invertDictionary.begin(); iterPair != invertDictionary.end(); ++iterPair)
  {
    if (numOfTheMostFrequent != count++)
    {
      out << count << ". ";
      printWordAndFrequency(iterPair, out);
    }
    else
    {
      break;
    }
  }
}

void nikiforov::find(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out, std::string nameSelectedDictionary)
{
  if (!nameSelectedDictionary.empty())
  {
    auto SelectedDictionary = mapDictionaries.find(nameSelectedDictionary);
    std::string enteredWord;
    in >> enteredWord;

    auto iterPair = SelectedDictionary->second.find(enteredWord);
    if (iterPair != SelectedDictionary->second.end())
    {
      printWordAndFrequency(iterPair, out);
    }
    else
    {
      out << " Error: The word '" << enteredWord << "' was not found\n";
    }
  }
  else
  {
    out << " The dictionary is not selected\n";
    out << " Select a dictionary using the command 'select < name >'\n";
  }
}

void nikiforov::erase(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out, std::string nameSelectedDictionary)
{
  if (!nameSelectedDictionary.empty())
  {
    auto SelectedDictionary = mapDictionaries.find(nameSelectedDictionary);
    std::string enteredWord;
    in >> enteredWord;

    auto deletedWord = SelectedDictionary->second.find(enteredWord);
    if (deletedWord != SelectedDictionary->second.end())
    {
      SelectedDictionary->second.erase(deletedWord->first);
      out << " The word '" << enteredWord << "' has been successfully deleted\n";
    }
    else
    {
      out << " Error: The word " << enteredWord << " was not found\n";
    }
  }
  else
  {
    out << " The dictionary is not selected\n";
    out << " Select a dictionary using the command 'select < name >'\n";
  }
}

void nikiforov::printWordAndFrequency(AvlTreeConstIter begin, AvlTreeConstIter end, std::ostream& out)
{
  while (begin != end)
  {
    out << begin->first << " " << begin->second << "\n";
    begin++;
  }
}

void nikiforov::printWordAndFrequency(nikiforov::AvlTree< std::string, size_t >::Iterator iterPair, std::ostream& out)
{
  out << iterPair->first << " " << iterPair->second << "\n";
}
