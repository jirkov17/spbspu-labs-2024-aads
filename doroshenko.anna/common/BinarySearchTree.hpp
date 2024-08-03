#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP
#include <iterator>
#include <cassert>
#include <functional>
#include <algorithm>
#include <stdexcept>
#include "queue.hpp"
#include "stack.hpp"

namespace doroshenko
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class BST
  {
  public:
    class Node;
    class ConstIterator;
    class Iterator;

    using keyValPair = std::pair< Key, Value >;
    using iterator = Iterator;
    using constIterator = ConstIterator;

    BST();
    BST(const BST& otherTree);
    BST(BST&& otherTree) noexcept;
    ~BST();
    bool isEmpty() noexcept;
    size_t getSize() noexcept;
    void clear();
    void swap(BST& other);
    ConstIterator constFind(const Key& key) const;
    Iterator find(const Key& key);
    Node* insert(const Key& key, const Value& value);
    void insert(const keyValPair& pair);
    keyValPair& at(const Key& key);
    const keyValPair& at(const Key& key) const;
    Iterator erase(Iterator position);
    size_t erase(const Key& key);
    std::pair< ConstIterator, ConstIterator > equalRange(const Key& key) const;
    std::pair< Iterator, Iterator > equalRange(const Key& key);
    size_t count(const Key& key) const;

    Iterator begin() const;
    Iterator end() const;

    ConstIterator cbegin() const;
    ConstIterator cend() const;

    template< typename F >
    F traverse_lnr(F f) const;
    template< typename F >
    F traverse_rnl(F f) const;
    template< typename F >
    F traverse_breadth(F f) const;
  private:
    Node* root_;
    Compare cmp_;

    void clear(Node* node);
    Node* balance(Node* node);
    Node* turnRight(Node* root);
    Node* turnLeft(Node* root);
    void updateHeight(Node* root);
    size_t getHeight(Node* root);
    size_t getBalance(Node* root);
    Node* eraseIfNoChildren(Node*);
    Node* eraseIfOnlyLeftChild(Node*);
    Node* eraseIfOnlyRightChild(Node*);
    Node* eraseIfTwoChildren(Node*);
  };
}
using namespace doroshenko;

template < typename Key, typename Value >
using keyValPair = std::pair< Key, Value >;

template< typename Key, typename Value, typename Compare >
using iterator = typename BST< Key, Value, Compare >::Iterator;

template< typename Key, typename Value, typename Compare >
using constIterator = typename BST< Key, Value, Compare >::ConstIterator;

template< typename Key, typename Value, typename Compare >
class doroshenko::BST< Key, Value, Compare >::Node
{
public:
  friend class BST< Key, Value, Compare >;
  explicit Node(keyValPair data, Node* parent = nullptr, Node* right = nullptr, Node* left = nullptr, size_t h = 0) :
    data_(data),
    parent_(parent),
    right_(right),
    left_(left),
    height_(h)
  {}
private:
  keyValPair data_;
  Node* parent_;
  Node* right_;
  Node* left_;
  size_t height_;
};

template< typename Key, typename Value, typename Compare >
class BST< Key, Value, Compare >::ConstIterator : public std::iterator< std::bidirectional_iterator_tag, keyValPair >
{
public:
  friend class BST< Key, Value, Compare >;
  ConstIterator();
  ConstIterator(Node* node, Node* root);
  ConstIterator(const ConstIterator&) = default;
  ~ConstIterator() = default;

  ConstIterator& operator=(const ConstIterator&) = default;
  ConstIterator& operator++();
  ConstIterator operator++(int);
  ConstIterator& operator--();
  ConstIterator operator--(int);

  const keyValPair& operator*() const;
  const keyValPair* operator->() const;

  bool operator!=(const ConstIterator& rhs) const;
  bool operator==(const ConstIterator& rhs) const;

private:
  Node* node_;
  Node* root_;
};

template< typename Key, typename Value, typename Compare >
BST< Key, Value, Compare >::ConstIterator::ConstIterator() :
  node_(nullptr),
  root_(nullptr)
{};

template< typename Key, typename Value, typename Compare >
BST< Key, Value, Compare >::ConstIterator::ConstIterator(Node* node, Node* root) :
  node_(node),
  root_(root)
{}

template< typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare >::ConstIterator& BST< Key, Value, Compare >::ConstIterator::operator++()
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
    Node* p = node_->parent_;
    while (p && node_ == p->right_)
    {
      node_ = p;
      p = p->parent_;
    }
    node_ = p;
  }
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare >::ConstIterator BST< Key, Value, Compare >::ConstIterator::operator++(int)
{
  assert(node_ != nullptr);
  ConstIterator result(*this);
  ++(*this);
  return result;
}

template< typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare >::ConstIterator& BST< Key, Value, Compare >::ConstIterator::operator--()
{
  if (node_ == nullptr)
  {
    node_ = root_;
    while (node_->right_)
    {
      node_ = node_->right_;
    }
  }
  else if (node_->left_)
  {
    node_ = node_->left_;
    while (node_->right_)
    {
      node_ = node_->right_;
    }
  }
  else
  {
    Node* p = node_->parent_;
    while (p && node_ == p->left_)
    {
      node_ = p;
      p = p->parent_;
    }
    node_ = p;
  }
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare >::ConstIterator BST< Key, Value, Compare >::ConstIterator::operator--(int)
{
  assert(node_ != nullptr);
  ConstIterator result(*this);
  --(*this);
  return result;
}

template< typename Key, typename Value, typename Compare >
const keyValPair< Key, Value >& BST< Key, Value, Compare >::ConstIterator::operator*() const
{
  assert(node_ != nullptr);
  return node_->data_;
}

template< typename Key, typename Value, typename Compare >
const keyValPair< Key, Value >* BST< Key, Value, Compare >::ConstIterator::operator->() const
{
  assert(node_ != nullptr);
  return std::addressof(node_->data_);
}

template< typename Key, typename Value, typename Compare >
bool BST< Key, Value, Compare >::ConstIterator::operator!=(const ConstIterator& rhs) const
{
  return !(rhs == *this);
}

template< typename Key, typename Value, typename Compare >
bool BST< Key, Value, Compare >::ConstIterator::operator==(const ConstIterator& rhs) const
{
  return node_ == rhs.node_;
}

template< typename Key, typename Value, typename Compare >
class BST< Key, Value, Compare >::Iterator : public std::iterator< std::bidirectional_iterator_tag, keyValPair >
{
public:
  friend class BST< Key, Value, Compare >;
  Iterator();
  Iterator(ConstIterator someIterator);
  ~Iterator() = default;
  Iterator(const Iterator&) = default;
  Iterator& operator=(const Iterator&) = default;
  Iterator operator++();
  Iterator operator++(int);
  Iterator operator--();
  Iterator operator--(int);
  keyValPair& operator*();
  keyValPair* operator->();
  bool operator!=(const Iterator& rhs) const;
  bool operator==(const Iterator& rhs) const;
private:
  ConstIterator iterator;
};

template< typename Key, typename Value, typename Compare >
BST< Key, Value, Compare >::Iterator::Iterator() :
  iterator(nullptr, nullptr)
{}

template< typename Key, typename Value, typename Compare >
BST< Key, Value, Compare >::Iterator::Iterator(ConstIterator someIterator) :
  iterator(someIterator)
{}

template< typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare >::Iterator::Iterator BST< Key, Value, Compare >::Iterator::operator++()
{
  assert(iterator.node_ != nullptr);
  iterator++;
  return iterator;
}

template< typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare >::Iterator::Iterator BST< Key, Value, Compare >::Iterator::operator++(int)
{
  ++iterator;
  return iterator;
}

template< typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare >::Iterator::Iterator BST< Key, Value, Compare >::Iterator::operator--()
{
  iterator--;
  return iterator;
}

template< typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare >::Iterator::Iterator BST< Key, Value, Compare >::Iterator::operator--(int)
{
  --iterator;
  return iterator;
}

template< typename Key, typename Value, typename Compare >
keyValPair< Key, Value >& BST< Key, Value, Compare >::Iterator::operator*()
{
  return iterator.node_->data_;
}
template< typename Key, typename Value, typename Compare >
keyValPair< Key, Value >* BST< Key, Value, Compare >::Iterator::operator->()
{
  return std::addressof(iterator.node_->data_);
}

template< typename Key, typename Value, typename Compare >
bool BST< Key, Value, Compare >::Iterator::operator!=(const Iterator& rhs) const
{
  return !(rhs == *this);
}

template< typename Key, typename Value, typename Compare >
bool BST< Key, Value, Compare >::Iterator::operator==(const Iterator& rhs) const
{
  return iterator == rhs.iterator;
}

template< typename Key, typename Value, typename Compare >
BST< Key, Value, Compare >::BST() :
  root_(nullptr),
  cmp_(Compare())
{};

template< typename Key, typename Value, typename Compare >
BST< Key, Value, Compare >::BST(const BST& otherTree)
{
  root_ = nullptr;
  cmp_ = otherTree.cmp_;
  ConstIterator iter = otherTree.cbegin();
  while (iter != cend())
  {
    insert(iter->first, iter->second);
    iter++;
  }
}

template< typename Key, typename Value, typename Compare >
BST< Key, Value, Compare >::BST(BST&& otherTree) noexcept :
  root_(otherTree.root_),
  cmp_(std::move(otherTree.cmp_))
{
  otherTree.root_ = nullptr;
}

template< typename Key, typename Value, typename Compare >
BST< Key, Value, Compare >::~BST()
{
  clear();
}

template< typename Key, typename Value, typename Compare >
bool BST< Key, Value, Compare >::isEmpty() noexcept
{
  return getSize() == 0 ? true : false;
}

template< typename Key, typename Value, typename Compare >
size_t BST< Key, Value, Compare >::getSize() noexcept
{
  ConstIterator iter = cbegin();
  size_t  size = 0;
  while (iter != cend())
  {
    size++;
    iter++;
  }
  return size;
}

template< typename Key, typename Value, typename Compare >
size_t BST< Key, Value, Compare >::getHeight(Node* root)
{
  if (root == nullptr)
  {
    return 0;
  }
  size_t leftH = getHeight(root->left_);
  size_t rightH = getHeight(root->right_);
  return leftH > rightH ? leftH + 1 : rightH + 1;
}

template< typename Key, typename Value, typename Compare >
size_t BST< Key, Value, Compare >::getBalance(Node* root)
{
  if (root != nullptr)
  {
    return getHeight(root->right_) - getHeight(root->left_);
  }
  else
  {
    throw std::logic_error("can't get balance");
  }
}

template< typename Key, typename Value, typename Compare >
void BST< Key, Value, Compare >::insert(const keyValPair& pair)
{
  insert(pair.first, pair.second);
}

template < typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare >::Node* BST< Key, Value, Compare >::insert(const Key& key, const Value& value)
{
  if (isEmpty())
  {
    root_ = new Node({ key, value });
    return root_;
  }
  Node* current = root_;
  Node* parent = nullptr;
  while (current)
  {
    parent = current;
    if (cmp_(key, current->data_.first))
    {
      current = current->left_;
    }
    else if (cmp_(current->data_.first, key))
    {
      current = current->right_;
    }
    else
    {
      return current;
    }
  }
  Node* newNode = new Node({ key, value }, parent);
  if (cmp_(key, parent->data_.first))
  {
    parent->left_ = newNode;
  }
  else
  {
    parent->right_ = newNode;
  }
  balance(newNode);
  return newNode;
}

template< typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare >::Iterator BST< Key, Value, Compare >::erase(Iterator position)
{
  Node* node = position.iterator.node_;
  if (!node)
  {
    return Iterator(ConstIterator(nullptr, root_));
  }
  if (!node->left_ && !node->right_)
  {
    return Iterator(ConstIterator(eraseIfNoChildren(node), root_));
  }
  else if (node->left_ && !node->right_)
  {
    return Iterator(ConstIterator(eraseIfOnlyLeftChild(node), root_));
  }
  else if (node->right_ && !node->left_)
  {
    return Iterator(ConstIterator(eraseIfOnlyRightChild(node), root_));
  }
  return Iterator(ConstIterator(eraseIfTwoChildren(node), root_));
}

template < typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare>::Node* BST< Key, Value, Compare >::eraseIfNoChildren(Node* node)
{
  if (node == root_)
  {
    delete root_;
    root_ = nullptr;
    return root_;
  }
  if (cmp_(node->data_.first, node->parent_->data_.first))
  {
    node->parent_->left_ = nullptr;
  }
  else
  {
    node->parent_->right_ = nullptr;
  }
  Node* temp = node->parent_;
  delete node;
  return temp;
}

template < typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare>::Node* BST< Key, Value, Compare >::eraseIfOnlyLeftChild(Node* node)
{
  if (node == root_)
  {
    root_ = root_->left_;
    root_->parent_ = nullptr;
    delete node;
    return root_;
  }
  if (cmp_(node->data_.first, node->parent_->data_.first))
  {
    node->parent_->left_ = node->left_;
  }
  else
  {
    node->parent_->right_ = node->left_;
  }
  node->left_->parent_ = node->parent_;
  Node* temp = node->parent_;
  delete node;
  return temp;
}

template < typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare>::Node* BST< Key, Value, Compare >::eraseIfOnlyRightChild(Node* node)
{
  if (node == root_)
  {
    root_ = root_->right_;
    root_->parent_ = nullptr;
    delete node;
    return root_;
  }
  if (cmp_(node->data_.first, node->parent_->data_.first))
  {
    node->parent_->left_ = node->right_;
  }
  else
  {
    node->parent_->right_ = node->right_;
  }
  node->right_->parent_ = node->parent_;
  Node* temp = node->parent_;
  delete node;
  return temp;
}

template < typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare>::Node* BST< Key, Value, Compare >::eraseIfTwoChildren(Node* node)
{
  Node* temp = node->right_;
  if (temp != nullptr)
  {
    while (temp->left_)
    {
      temp = temp->left_;
    }
  }
  Node* min = temp;
  if (min->right_ && (min->parent_ != node))
  {
    min->parent_->left_ = min->right_;
    min->right_->parent_ = min->parent_;
  }
  else if (min->parent_ != node)
  {
    min->parent_->left_ = nullptr;
  }
  min->right_ = (node->right_->left_) ? node->right_ : node->right_->right_;
  min->left_ = node->left_;
  if (node == root_)
  {
    min->parent_ = nullptr;
    delete root_;
    root_ = min;
    if (root_->left_)
    {
      root_->left_->parent_ = root_;
    }
    if (root_->right_)
    {
      root_->right_->parent_ = root_;
    }
    return root_;
  }
  min->parent_ = node->parent_;
  node->left_->parent_ = min;
  if (cmp_(min->data_.first, min->parent_->data_.first))
  {
    min->parent_->left_ = min;
  }
  else
  {
    min->parent_->right_ = min;
  }
  delete node;
  return min;
}

template < typename Key, typename Value, typename Compare >
size_t BST< Key, Value, Compare >::erase(const Key& key)
{
  Iterator iter = find(key);
  if (iter == ConstIterator())
  {
    return 0;
  }
  else
  {
    erase(iter);
    return 1;
  }
}

template < typename Key, typename Value, typename Compare >
void BST< Key, Value, Compare >::updateHeight(Node* node)
{
  node->height_ = getHeight(node);
}

template< typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare >::Node* BST< Key, Value, Compare >::balance(Node* node)
{
  int balanceFactor = getBalance(node);
  if (balanceFactor > 1)
  {
    if (getBalance(node->right_) > 0)
    {
      return turnLeft(node);
    }
    else
    {
      node->right_ = turnRight(node->right_);
      return turnLeft(node);
    }
  }
  else if (balanceFactor < -1)
  {
    if (getBalance(node->left_) > 0)
    {
      node->left_ = turnLeft(node->left_);
      return turnRight(node);
    }
    else
    {
      return turnRight(node);
    }
  }
  return node;
}

template< typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare >::Node* BST< Key, Value, Compare >::turnRight(Node* root)
{
  Node* leftSubtree = root->left_;
  Node* leftSubtreeRightSubtree = leftSubtree->right_;
  leftSubtree->right_ = root;
  root->left_ = leftSubtreeRightSubtree;
  root->parent_ = leftSubtree;
  if (leftSubtreeRightSubtree)
  {
    leftSubtreeRightSubtree->parent_ = root;
  }
  updateHeight(root);
  updateHeight(leftSubtree);
  return leftSubtree;
}

template< typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare >::Node* BST< Key, Value, Compare >::turnLeft(Node* root)
{
  Node* rightSubtree = root->right_;
  Node* rightSubtreeLeftSubtree = rightSubtree->left_;
  rightSubtree->left_ = root;
  root->right_ = rightSubtreeLeftSubtree;
  root->parent_ = rightSubtree;
  if (rightSubtreeLeftSubtree)
  {
    rightSubtreeLeftSubtree->parent_ = root;
  }
  updateHeight(root);
  updateHeight(rightSubtree);
  return rightSubtree;
}

template < typename Key, typename Value, typename Compare >
void BST< Key, Value, Compare >::clear(Node* node)
{
  if (node)
  {
    clear(node->left_);
    clear(node->right_);
  }
  delete node;
  return;
}

template < typename Key, typename Value, typename Compare >
void BST< Key, Value, Compare >::clear()
{
  clear(root_);
  root_ = nullptr;
}

template < typename Key, typename Value, typename Compare >
void BST< Key, Value, Compare >::swap(BST& other)
{
  std::swap(root_, other.root_);
  std::swap(cmp_, other.cmp_);
}

template < typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare >::ConstIterator BST< Key, Value, Compare >::constFind(const Key& key) const
{
  Node* current = root_;
  while (current)
  {
    if (cmp_(key, current->data_.first))
    {
      current = current->left_;
    }
    else if (cmp_(current->data_.first, key))
    {
      current = current->right_;
    }
    else
    {
      return ConstIterator(current, root_);
    }
  }
  return ConstIterator(nullptr, root_);
}

template < typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare >::Iterator BST< Key, Value, Compare >::find(const Key& key)
{
  Node* current = root_;
  while (current)
  {
    if (cmp_(key, current->data_.first))
    {
      current = current->left_;
    }
    else if (cmp_(current->data_.first, key))
    {
      current = current->right_;
    }
    else
    {
      return Iterator(ConstIterator(current, root_));
    }
  }
  return Iterator(ConstIterator(nullptr, root_));
}

template< typename Key, typename Value, typename Compare >
size_t BST< Key, Value, Compare >::count(const Key& key) const
{
  return find(key) != ConstIterator() ? 1 : 0;
}

template < typename Key, typename Value, typename Compare >
keyValPair< Key, Value >& BST< Key, Value, Compare >::at(const Key& key)
{
  Iterator iter = find(key);
  return *iter;
}

template < typename Key, typename Value, typename Compare >
const keyValPair< Key, Value >& BST< Key, Value, Compare >::at(const Key& key) const
{
  Iterator iter = find(key);
  return *iter;
}

template < typename Key, typename Value, typename Compare >
using constItPair = std::pair< constIterator< Key, Value, Compare >, constIterator< Key, Value, Compare > >;

template < typename Key, typename Value, typename Compare >
constItPair< Key, Value, Compare > BST< Key, Value, Compare >::equalRange(const Key& key) const
{
  Node* node = root_;
  ConstIterator first = begin();
  ConstIterator temp = begin();
  ConstIterator last = ++temp;
  while (first != end())
  {
    if (first->first == key)
    {
      return(std::make_pair(first, last));
    }
    else if (first->first < key)
    {
      first++;
      last++;
    }
    else
    {
      return(std::make_pair(first, first));
    }
  }
}

template < typename Key, typename Value, typename Compare >
using itPair = std::pair< iterator< Key, Value, Compare >, iterator< Key, Value, Compare > >;

template < typename Key, typename Value, typename Compare >
itPair< Key, Value, Compare > BST< Key, Value, Compare >::equalRange(const Key& key)
{
  Node* node = root_;
  Iterator firstit = begin();
  Iterator tempit = begin();
  Iterator lastit = ++tempit;
  while (firstit != end())
  {
    if (firstit->first == key)
    {
      return(std::make_pair(firstit, lastit));
    }
    else if (firstit->first < key)
    {
      firstit++;
      lastit++;
    }
    else
    {
      return(std::make_pair(firstit, firstit));
    }
  }
  return std::make_pair(Iterator(nullptr), Iterator(nullptr));
}

template < typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare >::ConstIterator BST< Key, Value, Compare >::cbegin() const
{
  Node* current = root_;
  if (current == nullptr)
  {
    return cend();
  }
  while (current->left_)
  {
    current = current->left_;
  }
  return ConstIterator(current, root_);
}

template < typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare >::ConstIterator BST< Key, Value, Compare >::cend() const
{
  return ConstIterator(nullptr, root_);
}

template < typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare >::Iterator BST< Key, Value, Compare >::begin() const
{
  return Iterator(cbegin());
}

template < typename Key, typename Value, typename Compare >
typename BST< Key, Value, Compare >::Iterator BST< Key, Value, Compare >::end() const
{
  return Iterator(cend());
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F BST< Key, Value, Compare >::traverse_lnr(F f) const
{
  Stack< Node* > stack;
  stack.push(root_);
  Node* current = root_;
  while (!stack.isEmpty())
  {
    while (current->left_)
    {
      stack.push(current->left_);
      current = current->left_;
    }
    current = stack.front();
    stack.drop();
    f(current->data_);
    if (current->right_)
    {
      current = current->right_;
      stack.push(current);
    }
  }
  return f;
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F BST< Key, Value, Compare >::traverse_rnl(F f) const
{
  Stack< Node* > stack;
  stack.push(root_);
  Node* current = root_;
  while (!stack.isEmpty())
  {
    while (current->right_)
    {
      stack.push(current->right_);
      current = current->right_;
    }
    current = stack.front();
    stack.drop();
    f(current->data_);
    if (current->left_)
    {
      current = current->left_;
      stack.push(current);
    }
  }
  return f;
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F BST< Key, Value, Compare >::traverse_breadth(F f) const
{
  Queue< Node* > queue;
  queue.push(root_);
  while (!queue.isEmpty())
  {
    Node* current = queue.front();
    queue.drop();
    f(current->data_);
    if (current->left_)
    {
      queue.push(current->left_);
    }
    if (current->right_)
    {
      queue.push(current->right_);
    }
  }
  return f;
}

#endif
