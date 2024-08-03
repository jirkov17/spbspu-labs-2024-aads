#ifndef WORKERBST_HPP
#define WORKERBST_HPP
#include <vector>
#include <BinarySearchTree.hpp>

using Dictionary = BinarySearchTree< std::string, BinarySearchTree< int, std::string >* >;
void Menu(Dictionary& bst);
void readFile(Dictionary& bst, const std::string& path);
void print(Dictionary& bst, const std::string&);
void complement(Dictionary& bst, std::vector< std::string >::iterator begin, std::vector< std::string >::iterator end);
void intersect(Dictionary& bst, std::vector< std::string >::iterator begin, std::vector< std::string >::iterator end);
void unify(Dictionary& bst, std::vector< std::string >::iterator begin, std::vector< std::string >::iterator end);
void parseArguments(Dictionary& bst, const std::string& str);
int parseNum(const std::string& num);
void readDataSet(Dictionary& bst, const std::string& dataSet);
void warningEmpty(std::ostream& out);
void warningInvCom(std::ostream& out);
void clearTree(Dictionary& bst);

#endif
