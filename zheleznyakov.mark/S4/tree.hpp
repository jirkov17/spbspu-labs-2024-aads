#ifndef TREE_HPP
#define TREE_HPP
#include <utility>
#include <stdexcept>
#include <functional>

namespace zheleznyakov {
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class Tree {
  public:
    using data_t = typename std::pair< Key, Value >;

    Tree();
    ~Tree() = default;

    Value at(const Key & k);

    void push(const Key &, const Value &);
  private:
    struct Node
    {
      Node(
        Node * parent = nullptr,
        Node * left = nullptr,
        Node * right = nullptr
      ):
        parent{parent},
        left{left},
        right{right}
      {}

      data_t data;
      Node * parent;
      Node * left;
      Node * right;
    };

    Node * root_;
  };
}

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::Tree():
  root_{nullptr}
{}

template < typename Key, typename Value, typename Compare >
Value zheleznyakov::Tree< Key, Value, Compare >::at(const Key & k) {
  Node* current = root_;
  Compare cmp;

  while (current != nullptr)
  {
    if (cmp(current->data.first, k))
    {
      current = current->right;
    }
    else if (cmp(k, current->data.first))
    {
      current = current->left;
    }
    else
    {
      return current->data.second;
    }
  }
  throw std::out_of_range("No such key");
}

template <typename Key, typename Value, typename Compare>
void zheleznyakov::Tree<Key, Value, Compare>::push(const Key & k, const Value & v) {
  Node* new_node = new Node();
  new_node->data = std::make_pair(k, v);

  Compare cmp;

  if (root_ == nullptr)
  {
    root_ = new_node;
    return;
  }

  Node* current = root_;
  Node* parent = nullptr;

  while (current != nullptr)
  {
    parent = current;
    if (cmp(k, current->data.first))
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }

  new_node->parent = parent;
  if (cmp(k, parent->data.first))
  {
    parent->left = new_node;
  }
  else
  {
    parent->right = new_node;
  }
}
#endif
