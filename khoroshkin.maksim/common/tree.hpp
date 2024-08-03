#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <functional>
#include <utility>
#include <iterator>
#include <cmath>
#include <initializer_list>
#include "stack.hpp"
#include "queue.hpp"

namespace khoroshkin
{
  template< typename Key, typename Value, typename Comp = std::less< Key > >
  class Tree
  {
  public:
    class Node;
    class Iterator;
    class ConstIterator;

    using iterator = Iterator;
    using const_iterator = ConstIterator;
    using value_type = std::pair< const Key, Value >;

    Tree();
    Tree(size_t count, const value_type & keyAndValue);
    template< class InputIt >
    Tree(InputIt first, InputIt last);
    Tree(std::initializer_list< value_type > init);
    Tree(const Tree & rhs);
    Tree(Tree && rhs);
    ~Tree();

    void insert(Key key, Value value);
    void insert(value_type pair);
    template< class... Args >
    void emplace(Args&&... args);
    size_t erase(const Key & key);
    iterator find(const Key & key);
    Value & operator[](const Key & key);
    void clear();

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    template< typename F >
    F traverse_lnr(F f) const;
    template< typename F >
    F traverse_rnl(F f) const;
    template< typename F >
    F traverse_breadth(F f) const;

  private:
    Node * root;
    size_t size;

    Node * insert(Key k, Value v, Node * node, Node * prev);
    iterator find(const Key & key, Node * node);
    void clear(Node * node);

    int getHeight(Node * node);
    size_t updateHeight(Node * node);
    int checkBalance(Node * node);
    Node * isBalanced(Node * node);

    void leftRotate(Node * node);
    void rightRotate(Node * node);
    void rightLeftRotate(Node * node);
    void leftRightRotate(Node * node);

    Node * copyTree(Node * node, Node * parent);
    Node * findMin(Node * node);
    Node * findMax(Node * node);

    void doBalance(Node * overweight);
  };
}

template< typename Key, typename Value, typename Comp >
class khoroshkin::Tree< Key, Value, Comp >::Node
{
public:
  friend class Tree;

  Node(Key key_, Value data_, Node * parent = nullptr, int height_ = 0, Node * left_ = nullptr, Node * right_ = nullptr);

private:
  value_type kv_pair;
  Node * parent;
  int height;
  Node * left;
  Node * right;
};


template< typename Key, typename Value, typename Comp >
khoroshkin::Tree< Key, Value, Comp >::Node::Node(Key key_, Value data_, Node * parent_, int height_, Node * left_, Node * right_) :
  kv_pair(std::make_pair(key_, data_)), parent(parent_), height(height_), left(left_), right(right_)
{}

template< typename Key, typename Value, typename Comp >
typename khoroshkin::Tree< Key,Value,Comp >::Node * khoroshkin::Tree< Key,Value,Comp >::insert(Key k, Value v, Node* node, Node * prev)
{
  Comp comp;
  if (node == nullptr)
  {
    node = new Node(k, v, prev);
    size++;
  }
  else if (comp(k, node->kv_pair.first))
  {
    node->left = insert(k, v, node->left, node);
  }
  else if (!comp(k, node->kv_pair.first))
  {
    node->right = insert(k, v, node->right, node);
  }
  return node;
}

template< typename Key, typename Value, typename Comp >
typename khoroshkin::Tree< Key, Value, Comp >::iterator khoroshkin::Tree< Key, Value, Comp >::find(const Key & key, Node * node)
{
  Comp comp;
  if (node == nullptr)
  {
    return Iterator(ConstIterator(nullptr, root));
  }
  if (node->kv_pair.first == key)
  {
    return Iterator(ConstIterator(node, root));
  }
  else if (comp(key, node->kv_pair.first))
  {
    return find(key, node->left);
  }
  else if (!comp(key, node->kv_pair.first))
  {
    return find(key, node->right);
  }
  throw std::logic_error("such element not exist");
}

template< typename Key, typename Value, typename Comp >
void khoroshkin::Tree< Key, Value, Comp >::clear(Node * node)
{
  if (node == nullptr)
  {
    return;
  }
  clear(node->left);
  clear(node->right);
  delete node;
}

template< typename Key, typename Value, typename Comp >
class khoroshkin::Tree< Key, Value, Comp >::ConstIterator : public std::iterator< std::bidirectional_iterator_tag, value_type >
{
  public:
    friend class Tree< Key, Value, Comp >;
    using this_t = ConstIterator;

    ConstIterator();
    ConstIterator(const this_t&) = default;
    ~ConstIterator() = default;

    this_t & operator=(const this_t &) = default;
    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);

    const value_type & operator*() const;
    const value_type * operator->() const;

    bool operator!=(const this_t & rhs) const;
    bool operator==(const this_t & rhs) const;

  private:
    Node * node_;
    Node * root_;
    ConstIterator(Node * node, Node * root);
};

template< typename Key, typename Value, typename Comp >
khoroshkin::Tree< Key, Value, Comp >::ConstIterator::ConstIterator() :
  node_(nullptr), root_(nullptr)
{}

template< typename Key, typename Value, typename Comp >
khoroshkin::Tree< Key, Value, Comp >::ConstIterator::ConstIterator(Node * node, Node * root) :
  node_(node), root_(root)
{}

template< typename Key, typename Value, typename Comp >
typename khoroshkin::Tree< Key, Value, Comp >::ConstIterator & khoroshkin::Tree< Key, Value, Comp >::ConstIterator::operator++()
{
  if (node_->right)
  {
    node_ = node_->right;
    while (node_->left)
    {
      node_ = node_->left;
    }
  }
  else
  {
    Node * tempParent = node_->parent;
    while (tempParent && node_ == tempParent->right)
    {
      node_ = tempParent;
      tempParent = node_->parent;
    }
    node_ = tempParent;
  }
  return *this;
}

template< typename Key, typename Value, typename Comp >
typename khoroshkin::Tree< Key, Value, Comp >::ConstIterator khoroshkin::Tree< Key, Value, Comp >::ConstIterator::operator++(int)
{
  this_t result(*this);
  ++(*this);
  return result;
}

template< typename Key, typename Value, typename Comp >
typename khoroshkin::Tree< Key, Value, Comp >::ConstIterator & khoroshkin::Tree< Key, Value, Comp >::ConstIterator::operator--()
{
  if (node_ == nullptr)
  {
    node_ = root_;
    while (node_->right)
    {
      node_ = node_->right;
    }
  }
  else
  {
    if (node_->left)
    {
      node_ = node_->left;
      while (node_->right)
      {
        node_ = node_->right;
      }
    }
    else
    {
      Node * tempParent = node_->parent;
      while (tempParent && node_ == tempParent->left)
      {
        node_ = tempParent;
        tempParent = node_->parent;
      }
      node_ = tempParent;
    }
  }
  return *this;
}

template< typename Key, typename Value, typename Comp >
typename khoroshkin::Tree< Key, Value, Comp >::ConstIterator khoroshkin::Tree< Key, Value, Comp >::ConstIterator::operator--(int)
{
  this_t result(*this);
  --(*this);
  return result;
}

template < typename Key, typename Value, typename Comp >
const typename khoroshkin::Tree< Key,Value,Comp >::value_type & khoroshkin::Tree< Key,Value,Comp >::ConstIterator::operator*() const
{
  return node_->kv_pair;
}

template < typename Key, typename Value, typename Comp >
const typename khoroshkin::Tree< Key,Value,Comp >::value_type * khoroshkin::Tree< Key,Value,Comp >::ConstIterator::operator->() const
{
  return std::addressof(node_->kv_pair);
}

template < typename Key, typename Value, typename Comp >
bool khoroshkin::Tree< Key, Value, Comp >::ConstIterator::operator==(const this_t & rhs) const
{
  return node_ == rhs.node_;
}

template < typename Key, typename Value, typename Comp >
bool khoroshkin::Tree< Key, Value, Comp >::ConstIterator::operator!=(const this_t & rhs) const
{
  return !(*this == rhs);
}

template< typename Key, typename Value, typename Comp >
class khoroshkin::Tree< Key, Value, Comp >::Iterator : public std::iterator< std::bidirectional_iterator_tag, Key, Value, Comp >
{
  public:
    friend class Tree< Key, Value, Comp >;
    using this_t = Iterator;
    Iterator();
    Iterator(ConstIterator iter);
    Iterator(const this_t &) = default;
    ~Iterator() = default;

    this_t & operator=(const this_t &) = default;
    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);

    value_type & operator*();
    value_type * operator->();
    const value_type & operator*() const;
    const value_type * operator->() const;

    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;

  private:
    ConstIterator iter_;
};

template< typename Key, typename Value, typename Comp >
khoroshkin::Tree< Key, Value, Comp >::Iterator::Iterator() :
  iter_(ConstIterator())
{}

template< typename Key, typename Value, typename Comp >
khoroshkin::Tree< Key, Value, Comp >::Iterator::Iterator(ConstIterator iter) :
  iter_(iter)
{}

template< typename Key, typename Value, typename Comp >
typename khoroshkin::Tree< Key, Value, Comp >::Iterator::this_t & khoroshkin::Tree< Key, Value, Comp >::Iterator::operator++()
{
  ++iter_;
  return *this;
}

template< typename Key, typename Value, typename Comp >
typename khoroshkin::Tree< Key, Value, Comp >::Iterator::this_t khoroshkin::Tree< Key, Value, Comp >::Iterator::operator++(int)
{
  this_t result = iter_;
  ++iter_;
  return result;
}

template< typename Key, typename Value, typename Comp >
typename khoroshkin::Tree< Key, Value, Comp >::Iterator & khoroshkin::Tree< Key, Value, Comp >::Iterator::operator--()
{
  --iter_;
  return *this;
}

template< typename Key, typename Value, typename Comp >
typename khoroshkin::Tree< Key, Value, Comp >::Iterator khoroshkin::Tree< Key, Value, Comp >::Iterator::operator--(int)
{
  this_t result = iter_;
  --iter_;
  return result;
}

template< typename Key, typename Value, typename Comp >
typename khoroshkin::Tree< Key, Value, Comp >::value_type & khoroshkin::Tree< Key, Value, Comp >::Iterator::operator*()
{
  return iter_.node_->kv_pair;
}

template< typename Key, typename Value, typename Comp >
typename khoroshkin::Tree< Key, Value, Comp >::value_type * khoroshkin::Tree< Key, Value, Comp >::Iterator::operator->()
{
  return std::addressof(iter_.node_->kv_pair);
}

template< typename Key, typename Value, typename Comp >
const typename khoroshkin::Tree< Key, Value, Comp >::value_type & khoroshkin::Tree< Key, Value, Comp >::Iterator::operator*() const
{
  return iter_.node_->kv_pair;
}

template< typename Key, typename Value, typename Comp >
const typename khoroshkin::Tree< Key, Value, Comp >::value_type * khoroshkin::Tree< Key, Value, Comp >::Iterator::operator->() const
{
  return std::addressof(iter_.node_->kv_pair);
}

template< typename Key, typename Value, typename Comp >
bool khoroshkin::Tree< Key, Value, Comp >::Iterator::operator!=(const this_t & rhs) const
{
  return !(rhs == *this);
}

template< typename Key, typename Value, typename Comp >
bool khoroshkin::Tree< Key, Value, Comp >::Iterator::operator==(const this_t & rhs) const
{
  return iter_ == rhs.iter_;
}

template< typename Key, typename Value, typename Comp >
khoroshkin::Tree< Key, Value, Comp >::Tree() :
  root(nullptr), size(0)
{}

template< typename Key, typename Value, typename Comp >
khoroshkin::Tree< Key, Value, Comp >::Tree(size_t count, const value_type & keyAndValue) :
  root(nullptr), size(0)
{
  for (size_t i = 0; i < count; ++i)
  {
    insert(keyAndValue);
  }
}

template< typename Key, typename Value, typename Comp >
template< class InputIt >
khoroshkin::Tree< Key, Value, Comp >::Tree(InputIt first, InputIt last)
{
  for (;first != last; ++first)
  {
    insert(*first);
  }
}

template< typename Key, typename Value, typename Comp >
khoroshkin::Tree< Key, Value, Comp >::Tree(std::initializer_list< value_type > init) :
  root(nullptr), size(0)
{
  for (auto it = init.begin(); it != init.end(); ++it)
  {
    insert(*it);
  }
}

template< typename Key, typename Value, typename Comp >
khoroshkin::Tree< Key, Value, Comp >::Tree(const Tree & rhs) :
  root(nullptr), size(rhs.size)
{
  root = copyTree(rhs.root, nullptr);
}

template< typename Key, typename Value, typename Comp >
khoroshkin::Tree< Key, Value, Comp >::Tree(Tree && rhs) :
  root(nullptr), size(std::move(rhs.size))
{
  root = copyTree(std::move(rhs.root), nullptr);
  rhs.clear();
  rhs.root = nullptr;
  rhs.size = 0;
}

template< typename Key, typename Value, typename Comp >
khoroshkin::Tree< Key, Value, Comp >::~Tree()
{
  clear();
  root = nullptr;
}

template< typename Key, typename Value, typename Comp >
void khoroshkin::Tree< Key, Value, Comp >::insert(khoroshkin::Tree< Key, Value, Comp >::value_type pair)
{
  insert(pair.first, pair.second);
}

template< typename Key, typename Value, typename Comp >
void khoroshkin::Tree< Key, Value, Comp >::insert(Key key, Value value)
{
  root = insert(key, value, root, nullptr);
  updateHeight(root);
  Node * overweight = isBalanced(find(key).iter_.node_);
  doBalance(overweight);
}

template< typename Key, typename Value, typename Comp >
void khoroshkin::Tree< Key, Value, Comp >::doBalance(Node * overweight)
{
  while (overweight)
  {
    if (checkBalance(overweight) == 2)
    {
      if (checkBalance(overweight->right) >= 0)
      {
        leftRotate(overweight);
      }
      else
      {
        rightLeftRotate(overweight);
      }
    }
    else
    {
      if (checkBalance(overweight->left) < 0)
      {
        rightRotate(overweight);
      }
      else
      {
        leftRightRotate(overweight);
      }
    }
    overweight = isBalanced(overweight);
  }
}

template< typename Key, typename Value, typename Comp >
size_t khoroshkin::Tree< Key, Value, Comp >::erase(const Key & key)
{
  auto todelete = find(key);
  if (todelete == end())
  {
    return 0;
  }
  Node * todeleteNode = todelete.iter_.node_;
  Node * toCheckBalance = nullptr;
  if (!todeleteNode->left && !todeleteNode->right)
  {
    if (todeleteNode->parent)
    {
      (todeleteNode->parent->left == todeleteNode) ? todeleteNode->parent->left = nullptr : todeleteNode->parent->right = nullptr;
      toCheckBalance = todeleteNode->parent;
      delete todeleteNode;
    }
    else
    {
      root = nullptr;
      delete todeleteNode;
    }
  }
  else
  {
    if (getHeight(todeleteNode->left) > getHeight(todeleteNode->right))
    {
      Node * toreplace = findMax(todeleteNode->left);
      (toreplace->parent != todeleteNode) ? toCheckBalance = toreplace->parent : toCheckBalance = todeleteNode->parent;
      toreplace->parent->right = toreplace->left;
      if (toreplace->left)
      {
        toreplace->left->parent = toreplace->parent;
      }
      toreplace->parent = todeleteNode->parent;
      if (toreplace->parent)
      {
        if (toreplace->parent->left == todeleteNode)
        {
          toreplace->parent->left = toreplace;
        }
        else
        {
          toreplace->parent->right = toreplace;
        }
      }
      toreplace->right = todeleteNode->right;
      if (toreplace->right)
      {
        toreplace->right->parent = toreplace;
      }
      if (todeleteNode->left != toreplace)
      {
        toreplace->left = todeleteNode->left;
        toreplace->left->parent = toreplace;
      }
      if (todeleteNode == root)
      {
        root = toreplace;
      }
      delete todeleteNode;
    }
    else
    {
      Node * toreplace = findMin(todeleteNode->right);
      (toreplace->parent != todeleteNode) ? toCheckBalance = toreplace->parent : toCheckBalance = todeleteNode->parent;
      toreplace->parent->left = toreplace->right;
      if (toreplace->right)
      {
        toreplace->right->parent = toreplace->parent;
      }
      toreplace->parent = todeleteNode->parent;
      if (toreplace->parent)
      {
        if (toreplace->parent->right == todeleteNode)
        {
          toreplace->parent->right = toreplace;
        }
        else
        {
          toreplace->parent->left = toreplace;
        }
      }
      toreplace->left = todeleteNode->left;
      if (toreplace->left)
      {
        toreplace->left->parent = toreplace;
      }
      if (todeleteNode->right != toreplace)
      {
        toreplace->right = todeleteNode->right;
        toreplace->right->parent = toreplace;
      }
      if (todeleteNode == root)
      {
        root = toreplace;
      }
      delete todeleteNode;
    }
  }
  updateHeight(root);
  Node * overweight = isBalanced(toCheckBalance);
  doBalance(overweight);
  size--;
  return 1;
}

template< typename Key, typename Value, typename Comp >
void khoroshkin::Tree< Key, Value, Comp >::leftRotate(Node * node)
{
  if (node->parent)
  {
    Node * parent = node->parent;
    Node * newChild;
    if (parent->right == node)
    {
      parent->right = node->right;
      newChild = parent->right;
    }
    else
    {
      parent->left = node->right;
      newChild = parent->left;
    }
    newChild->parent = parent;
    node->right = node->right->left;
    newChild->left = node;
    node->parent = newChild;
  }
  else
  {
    Node * temp = node;
    root = node->right;
    temp->right = root->right->left;
    root->left = temp;
    temp->parent = root;
    root->parent = nullptr;
  }
  updateHeight(root);
}

template< typename Key, typename Value, typename Comp >
void khoroshkin::Tree< Key, Value, Comp >::rightRotate(Node * node)
{
  if (node->parent)
  {
    Node * parent = node->parent;
    Node * newChild;
    if (parent->left == node)
    {
      parent->left = node->left;
      newChild = parent->left;
    }
    else
    {
      parent->right = node->left;
      newChild = parent->right;
    }
    newChild->parent = parent;
    node->left = node->left->right;
    newChild->right = node;
    node->parent = newChild;
  }
  else
  {
    Node * temp = node;
    root = node->left;
    temp->left = root->left->right;
    root->right = temp;
    temp->parent = root;
    root->parent = nullptr;
  }
  updateHeight(root);
}

template< typename Key, typename Value, typename Comp >
void khoroshkin::Tree< Key, Value, Comp >::rightLeftRotate(Node * node)
{
  rightRotate(node->right);
  leftRotate(node);
}

template< typename Key, typename Value, typename Comp >
void khoroshkin::Tree< Key, Value, Comp >::leftRightRotate(Node * node)
{
  leftRotate(node->left);
  rightRotate(node);
}

template< typename Key, typename Value, typename Comp >
typename khoroshkin::Tree< Key, Value, Comp >::iterator khoroshkin::Tree< Key, Value, Comp >::find(const Key & key)
{
  return find(key, root);
}

template< typename Key, typename Value, typename Comp >
Value & khoroshkin::Tree< Key, Value, Comp >::operator[](const Key & key)
{
  return (*find(key, root)).second;
}

template< typename Key, typename Value, typename Comp >
void khoroshkin::Tree< Key, Value, Comp >::clear()
{
  clear(root);
}

template< typename Key, typename Value, typename Comp >
bool khoroshkin::Tree< Key, Value, Comp >::isEmpty() const noexcept
{
  return !size;
}

template< typename Key, typename Value, typename Comp >
size_t khoroshkin::Tree< Key, Value, Comp >::getSize() const noexcept
{
  return size;
}

template< typename Key, typename Value, typename Comp >
typename khoroshkin::Tree< Key, Value, Comp >::iterator khoroshkin::Tree< Key, Value, Comp >::begin() noexcept
{
  if (isEmpty())
  {
    return cend();
  }
  Node * temp = root;
  while (temp->left != nullptr)
  {
    temp = temp->left;
  }
  return Iterator(ConstIterator(temp, root));
}

template< typename Key, typename Value, typename Comp >
typename khoroshkin::Tree< Key, Value, Comp >::iterator khoroshkin::Tree< Key, Value, Comp >::end() noexcept
{
  return Iterator(ConstIterator(nullptr, root));
}

template< typename Key, typename Value, typename Comp >
typename khoroshkin::Tree< Key, Value, Comp >::const_iterator khoroshkin::Tree< Key, Value, Comp >::cbegin() const noexcept
{
  if (isEmpty())
  {
    return cend();
  }
  Node * temp = root;
  while (temp->left != nullptr)
  {
    temp = temp->left;
  }
  return ConstIterator(temp, root);
}

template< typename Key, typename Value, typename Comp >
typename khoroshkin::Tree< Key, Value, Comp >::const_iterator khoroshkin::Tree< Key, Value, Comp >::cend() const noexcept
{
  return ConstIterator(nullptr, root);
}

template< typename Key, typename Value, typename Comp >
int khoroshkin::Tree< Key, Value, Comp >::getHeight(Node * node)
{
  return (node) ? node->height : 0;
}

template< typename Key, typename Value, typename Comp >
size_t khoroshkin::Tree< Key, Value, Comp >::updateHeight(Node * node)
{
  if (node == nullptr)
  {
    return 0;
  }
  return node->height = std::max(updateHeight(node->left), updateHeight(node->right)) + 1;
}

template< typename Key, typename Value, typename Comp >
int khoroshkin::Tree< Key, Value, Comp >::checkBalance(Node * node)
{
  return getHeight(node->right) - getHeight(node->left);
}

template< typename Key, typename Value, typename Comp >
typename khoroshkin::Tree< Key, Value, Comp >::Node * khoroshkin::Tree< Key, Value, Comp >::isBalanced(Node * node)
{
  Node * temp = node;
  while (temp)
  {
    if (std::abs(checkBalance(temp)) > 1)
    {
      return temp;
    }
    temp = temp->parent;
  }
  return nullptr;
}

template< typename Key, typename Value, typename Comp >
typename khoroshkin::Tree< Key, Value, Comp >::Node * khoroshkin::Tree< Key, Value, Comp >::copyTree(Node * node, Node * parent)
{
  if (node == nullptr)
  {
    return nullptr;
  }
  Node * newnode = new Node(node->kv_pair.first, node->kv_pair.second, parent, node->height);
  newnode->left = copyTree(node->left, newnode);
  newnode->right = copyTree(node->right, newnode);
  return newnode;
}

template< typename Key, typename Value, typename Comp >
typename khoroshkin::Tree< Key, Value, Comp >::Node * khoroshkin::Tree< Key, Value, Comp >::findMin(Node * node)
{
  if (node && node->left)
  {
    return findMin(node->left);
  }
  return node;
}

template< typename Key, typename Value, typename Comp >
typename khoroshkin::Tree< Key, Value, Comp >::Node * khoroshkin::Tree< Key, Value, Comp >::findMax(Node * node)
{
  if (node && node->right)
  {
    return findMax(node->right);
  }
  return node;
}

template< typename Key, typename Value, typename Comp >
template< class... Args >
void khoroshkin::Tree< Key, Value, Comp >::emplace(Args&&... args)
{
  insert(std::forward< Args >(args)...);
}

template< typename Key, typename Value, typename Comp >
template< typename F >
F khoroshkin::Tree< Key, Value, Comp >::traverse_lnr(F f) const
{
  Stack< Node * > parents;
  Node * iterative = root;
  while (iterative != nullptr || !parents.isEmpty())
  {
    while (iterative != nullptr)
    {
      parents.push(iterative);
      iterative = iterative->left;
    }
    if (!parents.isEmpty())
    {
      Node * poppedNode = parents.top();
      try
      {
        f(poppedNode->kv_pair);
      }
      catch(const std::exception & e)
      {
        throw e;
      }
      parents.pop();
      iterative = poppedNode->right;
    }
  }
  return f;
}

template< typename Key, typename Value, typename Comp >
template< typename F >
F khoroshkin::Tree< Key, Value, Comp >::traverse_rnl(F f) const
{
  Stack< Node * > parents;
  Node * iterative = root;
  while (iterative != nullptr || !parents.isEmpty())
  {
    while (iterative != nullptr)
    {
      parents.push(iterative);
      iterative = iterative->right;
    }
    if (!parents.isEmpty())
    {
      Node * poppedNode = parents.top();
      try
      {
        f(poppedNode->kv_pair);
      }
      catch(const std::exception & e)
      {
        throw e;
      }
      parents.pop();
      iterative = poppedNode->left;
    }
  }
  return f;
}

template< typename Key, typename Value, typename Comp >
template< typename F >
F khoroshkin::Tree< Key, Value, Comp >::traverse_breadth(F f) const
{
  Queue< Node * > currentLevel;
  currentLevel.push(root);
  while (!currentLevel.isEmpty())
  {
    if (currentLevel.front() != nullptr)
    {
      Node * poppedNode = currentLevel.front();
      try
      {
        f(poppedNode->kv_pair);
      }
      catch(const std::exception & e)
      {
        throw e;
      }
      currentLevel.pop();
      currentLevel.push(poppedNode->left);
      currentLevel.push(poppedNode->right);
    }
    else
    {
      currentLevel.pop();
    }
  }
  return f;
}

#endif
