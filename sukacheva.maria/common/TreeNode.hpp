#ifndef TREENODE_HPP
#define TREENODE_HPP
#include <utility>
#include <cstddef>

namespace sukacheva
{
  namespace details
  {
    template < typename Value, typename Key >
    struct TreeNode {
      TreeNode(Key k, Value v) : data(std::make_pair(k, v)), left(nullptr), right(nullptr), parent(nullptr), height(0) {}
      TreeNode(Key k, Value v, TreeNode* p) : data(std::make_pair(k, v)), left(nullptr), right(nullptr), parent(p), height(0) {}
      TreeNode(std::pair< Key, Value > data_) : data(data_), left(nullptr), right(nullptr), parent(nullptr), height(0) {}
      std::pair< Key, Value > data;
      TreeNode* left;
      TreeNode* right;
      TreeNode* parent;
      size_t height;
    };
  }
}

#endif
