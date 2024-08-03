#include <map>
#include <functional>
#include "sorts.hpp"
#include "DataProcessing.hpp"
#include "ErrorMessage.hpp"

int main(int argc, char* argv[])
{
  using namespace sukacheva;
  if (argc != 4)
  {
    std::cerr << "<INVALID NUMBER OF ARGUMENTS>\n";
    return 1;
  }
  std::string cmp = argv[1];
  std::string type = argv[2];
  try
  {
    long long size = std::stoll(argv[3]);
    std::map< std::string, std::map < std::string, std::function< void(std::string type, size_t size, std::ostream& out) > > > sort{};
    std::map < std::string, std::function< void(std::string type, size_t size, std::ostream& out) > > ints{};
    std::map < std::string, std::function< void(std::string type, size_t size, std::ostream& out) > > floats{};
    {
      using namespace std::placeholders;
      ints["ascending"] = std::bind(sortConts< int, std::less< int > >, _1, _2, _3, std::less< int >());
      ints["descending"] = std::bind(sortConts< int, std::greater< int > >, _1, _2, _3, std::greater< int >());

      floats["ascending"] = std::bind(sortConts< float, std::less< float > >, _1, _2, _3, std::less< float >());
      floats["descending"] = std::bind(sortConts< float, std::greater< float > >, _1, _2, _3, std::greater< float >());

      sort["ints"] = ints;
      sort["floats"] = floats;
    }
    sort.at(argv[2]).at(argv[1])(type, size, std::cout);
  }
  catch (const std::exception& e)
  {
    ErrorMessage(std::cerr);
    return 1;
  }

  return 0;
}
