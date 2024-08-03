#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <cassert>
#include "Stack.hpp"
#include "Queue.hpp"

namespace reznikova
{
  template< typename Key, typename Value, typename Comparator = std::less< Key > >
  class Tree
  {
  public:
    class Node;
    class ConstIterator;
    class Iterator;
    using pair_type = std::pair< const Key, Value >;

    Tree();
    template< class InputIt >
    Tree(InputIt first, InputIt last);
    Tree(std::initializer_list< std::pair< const Key, Value > > init);
    Tree(const Tree & otherTree);
    Tree(Tree && otherTree);
    ~Tree();
    Tree & operator=(const Tree & otherTree);
    Tree & operator=(Tree && otherTree);

    template< typename F >
    F traverse_lnr(F f) const;
    template< typename F >
    F traverse_rnl(F f) const;
    template< typename F >
    F traverse_breadth(F f) const;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;
    Iterator begin() noexcept;
    Iterator end() noexcept;
    size_t getSize() const noexcept;
    bool isEmpty() const noexcept;
    void insert(const Key & key, const Value & value);
    template< class InputIt >
    void insert(InputIt first, InputIt last);
    void clear(Node * node);
    void swap(Tree & otherTree);
    Value & at(const Key & key);
    ConstIterator find(const Key & key) const;
    Value & operator[](const Key & key);
    void erase(Iterator position);
    size_t erase(const Key & key);
    template< class InputIt >
    void erase(InputIt first, InputIt last);
    size_t count(const Key & key);
    std::pair< Iterator, Iterator > equal_range(const Key & key) const;
    Iterator lower_bound(const Key & key);
    Iterator upper_bound(const Key & key);

  private:
    void updateHeight(Node * node);
    Node * LLrotation(Node * turnNode);
    Node * RRrotation(Node * turnNode);
    int height(Node * node);
    int getBalance(Node * node);
    Node * balance(Node * node);
    Node * insert(Node * node, const Key & key, const Value & value, Node* parent);
    Node * erase(Node * node, const Key & key);
    Node * find(Node * node, const Key & key) const;
    Node* lowerBoundNode(Node * node, const Key & key) const;
    Node* upperBoundNode(Node * node, const Key & key) const;

    Node * root_;
    Comparator cmp_;
    size_t size_;
  };
}

using namespace reznikova;

template< typename Key, typename Value, typename Comparator >
class Tree< Key, Value, Comparator >::Node
{
public:
  friend class Tree< Key, Value, Comparator >;
  explicit Node(Key key_, Value value_) :
    parent_(nullptr),
    left_(nullptr),
    right_(nullptr),
    value_pair_(std::make_pair(key_, value_)),
    height_(1)
  {}
private:
  Node * parent_;
  Node * left_;
  Node * right_;
  std::pair< const Key, Value > value_pair_;
  int height_;
};

template< typename Key, typename Value, typename Comparator >
struct Tree< Key, Value, Comparator >::ConstIterator
{
public:
  friend class Tree< Key, Value, Comparator >;
  using this_t = ConstIterator;
  using node_t = Node;
  using pair_type = std::pair< const Key, Value >;
  ConstIterator();
  ConstIterator(node_t * node, node_t * root);
  ConstIterator(const ConstIterator &) = default;
  ~ConstIterator() = default;
  this_t & operator=(const ConstIterator &) = default;
  this_t & operator++();
  this_t operator++(int);
  this_t & operator--();
  this_t operator--(int);
  const pair_type & operator*() const;
  const pair_type * operator->() const;
  bool operator!=(const this_t & rhs) const;
  bool operator==(const this_t & rhs) const;
private:
  node_t * node_;
  node_t * root_;
};

template< typename Key, typename Value, typename Comparator >
Tree< Key, Value, Comparator >::ConstIterator::ConstIterator():
  node_(nullptr),
  root_(nullptr)
{}

template< typename Key, typename Value, typename Comparator >
Tree< Key, Value, Comparator >::ConstIterator::ConstIterator(node_t * node, node_t * root):
  node_(node),
  root_(root)
{}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::ConstIterator & Tree< Key, Value, Comparator >::ConstIterator::operator++()
{
  assert(node_ != nullptr);
  if (node_->right_)
  {
    node_ = node_->right_;
    while (node_->left_)
    {
      node_ = node_->left_;
    }
  }
  else
  {
    Node * temp = node_->parent_;
    while (temp and (node_ == temp->right_))
    {
      node_ = temp;
      temp = temp->parent_;
    }
    node_ = temp;
  }
  return *this;
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::ConstIterator Tree< Key, Value, Comparator >::ConstIterator::operator++(int)
{
  this_t result(*this);
  ++(*this);
  return result;
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::ConstIterator & Tree< Key, Value, Comparator >::ConstIterator::operator--()
{
  if (node_ == nullptr)
  {
    node_ = root_;
    while (node_->right_)
    {
      node_ = node_->right_;
    }
  }
  else
  {
    if (node_->left_)
    {
      node_ = node_->left_;
      while (node_->right_)
      {
        node_ = node_->right_;
      }
    }
    else
    {
      Node * temp = node_->parent_;
      while (temp and (node_ == temp->left_))
      {
        node_ = temp;
        temp = temp->parent_;
      }
      node_ = temp;
    }
  }
  return *this;
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::ConstIterator Tree< Key, Value, Comparator >::ConstIterator::operator--(int)
{
  this_t result(*this);
  --(*this);
  return result;
}

template< typename Key, typename Value, typename Comparator >
const std::pair< const Key, Value > & Tree< Key, Value, Comparator >::ConstIterator::operator*() const
{
  assert(node_ != nullptr);
  return node_->value_pair_;
}

template< typename Key, typename Value, typename Comparator >
const std::pair< const Key, Value > * Tree< Key, Value, Comparator >::ConstIterator::operator->() const
{
  assert(node_ != nullptr);
  return std::addressof(node_->value_pair_);
}

template< typename Key, typename Value, typename Comparator >
bool Tree< Key, Value, Comparator >::ConstIterator::operator!=(const ConstIterator & rhs) const
{
  return !(node_ == rhs.node_);
}

template< typename Key, typename Value, typename Comparator >
bool Tree< Key, Value, Comparator >::ConstIterator::operator==(const ConstIterator & rhs) const
{
  return node_ == rhs.node_;
}

template< typename Key, typename Value, typename Comparator >
struct Tree< Key, Value, Comparator >::Iterator
{
public:
  friend class Tree< Key, Value, Comparator >;
  using this_t = Iterator;
  using node_t = Node;
  using pair_type = std::pair< const Key, Value >;
  Iterator();
  Iterator(node_t * node, node_t * root);
  Iterator(const Iterator &) = default;
  ~Iterator() = default;
  this_t & operator=(const Iterator &) = default;
  this_t & operator++();
  this_t operator++(int);
  this_t & operator--();
  this_t operator--(int);
  const pair_type & operator*() const;
  const pair_type * operator->() const;
  bool operator!=(const this_t & rhs) const;
  bool operator==(const this_t & rhs) const;
private:
  node_t * node_;
  node_t * root_;
};

template< typename Key, typename Value, typename Comparator >
Tree< Key, Value, Comparator >::Iterator::Iterator():
  node_(nullptr),
  root_(nullptr)
{}

template< typename Key, typename Value, typename Comparator >
Tree< Key, Value, Comparator >::Iterator::Iterator(node_t * node, node_t * root):
  node_(node),
  root_(root)
{}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Iterator & Tree< Key, Value, Comparator >::Iterator::operator++()
{
  assert(node_ != nullptr);
  if (node_->right_)
  {
    node_ = node_->right_;
    while (node_->left_)
    {
      node_ = node_->left_;
    }
  }
  else
  {
    Node * temp = node_->parent_;
    while (temp and (node_ == temp->right_))
    {
      node_ = temp;
      temp = temp->parent_;
    }
    node_ = temp;
  }
  return *this;
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Iterator Tree< Key, Value, Comparator >::Iterator::operator++(int)
{
  this_t result(*this);
  ++(*this);
  return result;
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Iterator & Tree< Key, Value, Comparator >::Iterator::operator--()
{
  if (node_ == nullptr)
  {
    node_ = root_;
    while (node_->right_)
    {
      node_ = node_->right_;
    }
  }
  else
  {
    if (node_->left_)
    {
      node_ = node_->left_;
      while (node_->right_)
      {
        node_ = node_->right_;
      }
    }
    else
    {
      Node * temp = node_->parent_;
      while (temp and (node_ == temp->left_))
      {
        node_ = temp;
        temp = temp->parent_;
      }
      node_ = temp;
    }
  }
  return *this;
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Iterator Tree< Key, Value, Comparator >::Iterator::operator--(int)
{
  this_t result(*this);
  --(*this);
  return result;
}

template< typename Key, typename Value, typename Comparator >
const std::pair< const Key, Value > & Tree< Key, Value, Comparator >::Iterator::operator*() const
{
  assert(node_ != nullptr);
  return node_->value_pair_;
}

template< typename Key, typename Value, typename Comparator >
const std::pair< const Key, Value > * Tree< Key, Value, Comparator >::Iterator::operator->() const
{
  assert(node_ != nullptr);
  return std::addressof(node_->value_pair_);
}

template< typename Key, typename Value, typename Comparator >
bool Tree< Key, Value, Comparator >::Iterator::operator!=(const Iterator & rhs) const
{
  return !(node_ == rhs.node_);
}

template< typename Key, typename Value, typename Comparator >
bool Tree< Key, Value, Comparator >::Iterator::operator==(const Iterator & rhs) const
{
  return node_ == rhs.node_;
}

template< typename Key, typename Value, typename Comparator >
Tree< Key, Value, Comparator >::Tree():
  root_(nullptr),
  cmp_(Comparator()),
  size_(0)
{}

template< typename Key, typename Value, typename Comparator >
Tree< Key, Value, Comparator >::Tree(const Tree & otherTree):
  root_(nullptr),
  cmp_(otherTree.cmp_),
  size_(0)
{
  for (ConstIterator it = otherTree.cbegin(); it != otherTree.cend(); ++it)
  {
    insert(it->first, it->second);
  }
}

template< typename Key, typename Value, typename Comparator >
Tree< Key, Value, Comparator >::Tree(Tree && otherTree) :
  root_(otherTree.root_),
  cmp_(std::move(otherTree.cmp_)),
  size_(otherTree.size_)
{
  otherTree.root_ = nullptr;
  otherTree.size_ = 0;
}

template< typename Key, typename Value, typename Comparator >
template< class InputIt >
Tree< Key, Value, Comparator >::Tree(InputIt first, InputIt last):
  root_(nullptr),
  cmp_(Comparator()),
  size_(0)
{
  while (first != last)
  {
    insert(*first);
    first++;
  }
}

template< typename Key, typename Value, typename Comparator >
Tree< Key, Value, Comparator >::Tree(std::initializer_list< std::pair< const Key, Value > > init):
  root_(nullptr),
  cmp_(Comparator()),
  size_(0)
{
  std::pair< const Key, Value > * ptr = init.begin();
  while (ptr)
  {
    insert(*ptr);
    ptr++;
  }
}

template< typename Key, typename Value, typename Comparator >
Tree< Key, Value, Comparator > & Tree< Key, Value, Comparator >::operator=(const Tree & otherTree)
{
  if (this == &otherTree)
  {
    return *this;
  }
  clear();
  root_(otherTree.root_);
  return *this;
}

template< typename Key, typename Value, typename Comparator >
Tree< Key, Value, Comparator > & Tree< Key, Value, Comparator >::operator=(Tree&& otherTree)
{
  if (this == &otherTree)
  {
    return *this;
  }
  clear();
  root_ = otherTree.root_;
  otherTree.root_ = nullptr;
  return *this;
}

template< typename Key, typename Value, typename Comparator >
Tree< Key, Value, Comparator >::~Tree()
{
  clear(root_);
}

template< typename Key, typename Value, typename Comparator >
template< typename F >
F Tree< Key, Value, Comparator >::traverse_lnr(F f) const
{
  Stack< Node * > stack;
  Node * current = root_;
  while (current != nullptr or !stack.empty())
  {
    while (current != nullptr)
    {
      stack.push(current);
      current = current->left_;
    }
    current = stack.getValue();
    stack.pop();
    f(current->value_pair_);
    current = current->right_;
  }
  return f;
}

template< typename Key, typename Value, typename Comparator >
template< typename F >
F Tree< Key, Value, Comparator >::traverse_rnl(F f) const
{
  Stack< Node * > stack;
  Node * current = root_;
  while (current != nullptr or !stack.empty())
  {
    while (current != nullptr)
    {
      stack.push(current);
      current = current->right_;
    }
    current = stack.getValue();
    stack.pop();
    f(current->value_pair_);
    current = current->left_;
  }
  return f;
}

template<typename Key, typename Value, typename Comparator>
template<typename F>
F Tree<Key, Value, Comparator>::traverse_breadth(F f) const
{
  if (root_ == nullptr)
  {
    return f;
  }
  Queue< Node * > queue;
  queue.push(root_);
  while (!queue.empty())
  {
    Node * current = queue.getValue();
    queue.pop();
    f(current->value_pair_);
    if (current->left_ != nullptr)
    {
      queue.push(current->left_);
    }
    if (current->right_ != nullptr)
    {
      queue.push(current->right_);
    }
  }
  return f;
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::ConstIterator Tree< Key, Value, Comparator >::cbegin() const noexcept
{
  Node * node = root_;
  if (node)
  {
    while (node->left_)
    {
      node = node->left_;
    }
  }
  return ConstIterator(node, root_);
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::ConstIterator Tree< Key, Value, Comparator >::cend() const noexcept
{
  return ConstIterator(nullptr, root_);
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Iterator Tree< Key, Value, Comparator >::begin() noexcept
{
  Node * node = root_;
  if (node)
  {
    while (node->left_)
    {
      node = node->left_;
    }
  }
  return Iterator(node, root_);
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Iterator Tree< Key, Value, Comparator >::end() noexcept
{
  return Iterator(nullptr, root_);
}

template< typename Key, typename Value, typename Comparator >
void Tree< Key, Value, Comparator >::clear(Node * node)
{
  if (node != nullptr)
  {
    clear(node->left_);
    clear(node->right_);
    delete node;
  }
}

template< typename Key, typename Value, typename Comparator >
void Tree< Key, Value, Comparator >::swap(Tree & otherTree)
{
  std::swap(otherTree.root_, root_);
  std::swap(otherTree.cmp_, cmp_);
  std::swap(otherTree.size_, size_);
}

template< typename Key, typename Value, typename Comparator >
size_t Tree< Key, Value, Comparator >::getSize() const noexcept
{
  return size_;
}

template< typename Key, typename Value, typename Comparator >
bool Tree< Key, Value, Comparator >::isEmpty() const noexcept
{
  return getSize() == 0 ? true : false;
}

template< typename Key, typename Value, typename Comparator >
void Tree< Key, Value, Comparator >::updateHeight(Node * node)
{
  if (node)
  {
    node->height_ = std::max(height(node->left_), height(node->right_)) + 1;
  }
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Node * Tree< Key, Value, Comparator >::LLrotation(Node * turnNode)
{
  Node * newRoot = turnNode->right_;
  turnNode->right_ = newRoot->left_;
  if (newRoot->left_)
  {
    newRoot->left_->parent_ = turnNode;
  }
  newRoot->left_ = turnNode;
  newRoot->parent_ = turnNode->parent_;
  turnNode->parent_ = newRoot;
  updateHeight(turnNode);
  updateHeight(newRoot);
  return newRoot;
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Node * Tree< Key, Value, Comparator >::RRrotation(Node * turnNode)
{
  Node * newRoot = turnNode->left_;
  turnNode->left_ = newRoot->right_;
  if (newRoot->right_)
  {
    newRoot->right_->parent_ = turnNode;
  }
  newRoot->right_ = turnNode;
  newRoot->parent_ = turnNode->parent_;
  turnNode->parent_ = newRoot;
  updateHeight(turnNode);
  updateHeight(newRoot);
  return newRoot;
}

template< typename Key, typename Value, typename Comparator >
int Tree< Key, Value, Comparator >::height(Node * node)
{
    return node ? node->height_ : 0;
}

template< typename Key, typename Value, typename Comparator >
int Tree< Key, Value, Comparator >::getBalance(Node * node)
{
    return node ? height(node->left_) - height(node->right_) : 0;
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Node * Tree< Key, Value, Comparator >::balance(Node * node)
{
  updateHeight(node);
  int balanceFactor = getBalance(node);

  if (balanceFactor > 1)
  {
    if (getBalance(node->left_) < 0)
    {
      node->left_ = LLrotation(node->left_);
    }
    return RRrotation(node);
  }
  if (balanceFactor < -1)
  {
    if (getBalance(node->right_) > 0)
    {
      node->right_ = RRrotation(node->right_);
    }
    return LLrotation(node);
  }
  return node;
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Node * Tree< Key, Value, Comparator >::insert(Node * node, const Key & key,
  const Value & value, Node* parent)
{
  if (!node)
  {
    ++size_;
    Node * newNode = new Node(key, value);
    newNode->parent_ = parent;
    return newNode;
  }
  if (cmp_(key, node->value_pair_.first))
  {
    node->left_ = insert(node->left_, key, value, node);
  }
  else if (cmp_(node->value_pair_.first, key))
  {
    node->right_ = insert(node->right_, key, value, node);
  }
  return balance(node);
}

template< typename Key, typename Value, typename Comparator >
void Tree< Key, Value, Comparator >::insert(const Key & key, const Value & value)
{
  root_ = insert(root_, key, value, nullptr);
}

template< typename Key, typename Value, typename Comparator >
template< class InputIt >
void Tree< Key, Value, Comparator >::insert(InputIt first, InputIt last)
{
  while (first != last)
  {
    insert(*first);
    first++;
  }
}

template< typename Key, typename Value, typename Comparator >
Value & Tree< Key, Value, Comparator >::at(const Key & key)
{
  ConstIterator iter = cbegin();
  while (iter != cend())
  {
   if (find(key).node_ != nullptr)
   {
     return find(key).node_->value_pair_.second;
   }
   iter++;
  }
  throw std::out_of_range("no such key");
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::ConstIterator Tree< Key, Value, Comparator >::find(const Key & key) const
{
  Node * node = find(root_, key);
  return ConstIterator(node, root_);
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Node * Tree< Key, Value, Comparator >::find(Node * node,
  const Key & key) const
{
  while (node != nullptr)
  {
    if (cmp_(key, node->value_pair_.first))
    {
      node = node->left_;
    }
    else if (cmp_(node->value_pair_.first, key))
    {
      node = node->right_;
    }
    else
    {
      return node;
    }
  }
  return nullptr;
}

template< typename Key, typename Value, typename Comparator >
Value &  Tree< Key, Value, Comparator >::operator[](const Key & key)
{
  Value val;
  try
  {
    val = at(key);
  }
  catch (...)
  {
    throw std::out_of_range("no such key");
  }
  return val;
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Node * Tree< Key, Value, Comparator >::erase(Node * node, const Key & key)
{
  if (node == nullptr)
  {
    return node;
  }
  if (cmp_(key, node->value_pair_.first))
  {
    node->left_ = erase(node->left_, key);
  }
  else if (cmp_(node->value_pair_.first, key))
  {
    node->right_ = erase(node->right_, key);
  }
  else
  {
    if (node->left_ == nullptr)
    {
      Node * right = node->right_;
      delete node;
      --size_;
      return right;
    }
    else if (node->right_ == nullptr)
    {
      Node * left = node->left_;
      delete node;
      --size_;
      return left;
    }
    else
    {
      Node * minNode = node->right_;
      Node * minNodeParent = node;
      while (minNode->left_ != nullptr)
      {
        minNodeParent = minNode;
        minNode = minNode->left_;
      }
      if (minNodeParent != node)
      {
        minNodeParent->left_ = minNode->right_;
        minNode->right_ = node->right_;
      }
      minNode->left_ = node->left_;
      delete node;
      node = minNode;
    }
  }
  return balance(node);
}

template< typename Key, typename Value, typename Comparator >
void Tree< Key, Value, Comparator >::erase(Iterator position)
{
  if (position != end())
  {
    root_ = erase(root_, position->first);
  }
  else
  {
    throw std::logic_error("nothing to delete\n");
  }
}

template< typename Key, typename Value, typename Comparator >
template< class InputIt >
void Tree< Key, Value, Comparator >::erase(InputIt first, InputIt last)
{
  while (first != last)
  {
    erase(first);
    first++;
  }
}

template< typename Key, typename Value, typename Comparator >
size_t Tree< Key, Value, Comparator >::erase(const Key & key)
{
  size_t oldSize = size_;
  try
  {
    root_ = erase(root_, key);
  }
  catch (...)
  {
    return 0;
  }
  return oldSize - size_;
}

template< typename Key, typename Value, typename Comparator >
size_t Tree< Key, Value, Comparator >::count(const Key & key)
{
  return (find(key) == Iterator()) ? 1 : 0;
}

template< typename Key, typename Value, typename Comparator >
using iterPair = std::pair< typename Tree< Key, Value, Comparator >::Iterator,
  typename Tree< Key, Value, Comparator >::Iterator >;

template< typename Key, typename Value, typename Comparator >
iterPair< Key, Value, Comparator > Tree< Key, Value, Comparator >::equal_range(const Key & key) const
{
  Node * lb = lowerBoundNode(root_, key);
  Node * ub = upperBoundNode(root_, key);
  return std::make_pair(Iterator(lb), Iterator(ub));
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Iterator Tree< Key, Value, Comparator >::lower_bound(const Key & key)
{
  return Iterator(lowerBoundNode(root_, key));
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Iterator Tree< Key, Value, Comparator >::upper_bound(const Key & key)
{
  return Iterator(upperBoundNode(root_, key));
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Node * Tree< Key, Value, Comparator >::lowerBoundNode(Node * node,
  const Key & key) const
{
  if (node == nullptr)
  {
    return nullptr;
  }
  if (!cmp_(node->key_, key)) {
    Node * left = lowerBoundNode(node->left_, key);
    return (left != nullptr) ? left : node;
  }
  return lowerBoundNode(node->right_, key);
}

template< typename Key, typename Value, typename Comparator >
typename Tree< Key, Value, Comparator >::Node * Tree< Key, Value, Comparator >::upperBoundNode(Node * node,
  const Key & key) const
{
  if (node == nullptr)
  {
    return nullptr;
  }
  if (cmp_(key, node->key_))
  {
    Node * left = upperBoundNode(node->left_, key);
    return (left != nullptr) ? left : node;
  }
  return upperBoundNode(node->right_, key);
}

#endif
