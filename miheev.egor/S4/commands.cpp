#include "commands.hpp"

void miheev::commands::print(std::istream& in, std::ostream& out, const miheev::Datasets& datasets)
{
  std::string datasetName = "";
  in >> datasetName;
  const Data& data = datasets.at(datasetName);

  if (data.empty())
  {
    sendEmpty(out);
    return;
  }

  Data::ConstIterator citer(data.cbegin());
  out << datasetName << ' ';
  for (; citer != data.cend();)
  {
    out << citer->first << ' ' << citer->second;
    if (++citer != data.cend())
    {
      out << ' ';
    }
  }
  out << '\n';
}

void generateComplement(const miheev::Data& lhs, const miheev::Data& rhs, miheev::Data& container)
{
  miheev::Data::ConstIterator lIter(lhs.cbegin());
  for (; lIter != lhs.cend(); ++lIter)
  {
    if (!rhs.contains(lIter->first))
    {
      container.insert(*lIter);
    }
  }
}

void miheev::commands::complement(std::istream& in, std::ostream&, miheev::Datasets& datasets)
{
  std::string newName = "", dataset1 = "", dataset2 = "";
  in >> newName >> dataset1 >> dataset2;
  Data container;
  generateComplement(datasets.at(dataset1), datasets.at(dataset2), container);
  datasets[newName] = container;
}

void generateIntersection(const miheev::Data& lhs, const miheev::Data& rhs, miheev::Data& container)
{
  miheev::Data::ConstIterator lIter(lhs.cbegin());
  for (; lIter != lhs.cend(); ++lIter)
  {
    if (rhs.contains(lIter->first))
    {
      container.insert(*lIter);
    }
  }
}

void miheev::commands::intersect(std::istream& in, std::ostream&, miheev::Datasets& datasets)
{
  std::string newName = "", dataset1 = "", dataset2 = "";
  in >> newName >> dataset1 >> dataset2;
  Data container;
  generateIntersection(datasets.at(dataset1), datasets.at(dataset2), container);
  datasets[newName] = container;
}

void generateUnion(const miheev::Data& lhs, const miheev::Data& rhs, miheev::Data& container)
{
  miheev::Data::ConstIterator rIter(rhs.cbegin());
  container = lhs;
  for (; rIter != rhs.cend(); ++rIter)
  {
    if (!container.contains(rIter->first))
    {
      container.insert(*rIter);
    }
  }
}

void miheev::commands::unite(std::istream& in, std::ostream&, miheev::Datasets& datasets)
{
  std::string newName = "", dataset1 = "", dataset2 = "";
  in >> newName >> dataset1 >> dataset2;
  Data container;
  generateUnion(datasets.at(dataset1), datasets.at(dataset2), container);
  datasets[newName] = container;
}
