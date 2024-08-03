#ifndef BINARY_SEARCH_TREE_AVL_HPP
#define BINARY_SEARCH_TREE_AVL_HPP

#include <utility>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include "stack.hpp"
#include "queue.hpp"

namespace ponomarev
{
  template< typename Key, typename Value, typename Compare >
  class BSTree
  {
  public:
    class Iterator;
    class ConstIterator;
    class LnRIterator;
    class RnLIterator;

    using value_t = typename std::pair< Key, Value >;

    BSTree();
    BSTree(const BSTree & tree);
    BSTree(BSTree && tree) noexcept;
    ~BSTree() = default;

    BSTree & operator=(BSTree other);
    BSTree & operator=(BSTree && other);

    size_t getSize() const noexcept;
    bool isEmpty() const noexcept;

    Value & operator[](const Key & key);
    Value & operator[](Key && key);
    Value & at(const Key & key);
    const Value & at(const Key & key) const;

    void insert(const value_t & pair);
    void insert(value_t && pair);
    Iterator erase(Iterator pos);
    size_t erase(const Key & key);

    void clear();
    void swap(BSTree & other) noexcept;

    Iterator find(const Key & key);
    std::pair< Iterator, Iterator > equal_range(const Key & key);

    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;

    template< typename F >
    F constTraverseLR(F func) const;
    template< typename F >
    F traverseLR(F func);
    template< typename F >
    F constTraverseRL(F func) const;
    template< typename F >
    F traverseRL(F func);
    template< typename F >
    F constTraverseBreadth(F func) const;
    template< typename F >
    F traverseBreadth(F func);

  private:
    class Node;

    Node * push(const Key & key, const Value & value, Node * node_);
    Node * rightRotate(Node * node_);
    Node * leftRotate(Node * node_);
    Node * leftRightRotate(Node * node_);
    Node * rightLeftRotate(Node * node_);

    size_t getHight(Node * node_);
    void deleteAll(Node * node);

    Node * root_;
    size_t size_;
  };
}

using namespace ponomarev;

template < typename Key, typename Value >
using value_t = typename std::pair< Key, Value >;

template< typename Key, typename Value, typename Compare >
class BSTree< Key, Value, Compare >::Iterator : public std::iterator< std::input_iterator_tag, Key, Value, Compare >
{
  friend class BSTree;
public:
  Iterator();
  Iterator(Node * node);
  Iterator(const Iterator & iter);
  ~Iterator() = default;

  Iterator & operator=(const Iterator & iter);
  Iterator & operator=(Iterator && rhs);
  value_t & operator*();
  value_t * operator->();
  Iterator & operator++();
  Iterator operator++(int);
  Iterator & operator--();
  Iterator operator--(int);
  bool operator==(const Iterator & rhs) const;
  bool operator!=(const Iterator & rhs) const;
private:
  Node * node_;
};

template< typename Key, typename Value, typename Compare >
BSTree< Key, Value, Compare >::Iterator::Iterator()
{
  node_(nullptr);
}

template< typename Key, typename Value, typename Compare >
BSTree< Key, Value, Compare >::Iterator::Iterator(Node * node)
{
  node_ = node;
}

template< typename Key, typename Value, typename Compare >
BSTree< Key, Value, Compare >::Iterator::Iterator(const Iterator & iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::Iterator & BSTree< Key, Value, Compare >::Iterator::operator=(const Iterator & iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::Iterator & BSTree< Key, Value, Compare >::Iterator::operator=(Iterator && rhs)
{
  node_ = rhs.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value > & BSTree< Key, Value, Compare >::Iterator::operator*()
{
  return node_->data;
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value > * BSTree< Key, Value, Compare >::Iterator::operator->()
{
  return std::addressof(node_->data);
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::Iterator & BSTree< Key, Value, Compare >::Iterator::operator++()
{
  if (node_ == nullptr)
  {
    return *this;
  }
  else if (node_->right == nullptr)
  {
    Node * temp = node_->parent;
    while (temp != nullptr && node_ == temp->right)
    {
      node_ = temp;
      temp = node_->parent;
    }
    node_ = temp;
    return *this;
  }
  else
  {
    node_ = node_->right;
    if (node_->left == nullptr)
    {
      return *this;
    }
    while (node_->left != nullptr)
    {
      node_ = node_->left;
    }
    return *this;
  }
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::Iterator BSTree< Key, Value, Compare >::Iterator::operator++(int)
{
  Iterator temp(*this);
  ++(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::Iterator & BSTree< Key, Value, Compare >::Iterator::operator--()
{
  if (node_ == nullptr)
  {
    return *this;
  }
  else if (node_->left == nullptr)
  {
    Node * temp = node_->parent;
    while (temp != nullptr && node_ == temp->left)
    {
      node_ = temp;
      temp = node_->parent;
    }
    node_ = temp;
    return *this;
  }
  else
  {
    node_ = node_->left;
    while (node_->right != nullptr)
    {
      node_ = node_->right;
    }
    return *this;
  }
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::Iterator BSTree< Key, Value, Compare >::Iterator::operator--(int)
{
  Iterator temp(*this);
  --(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
bool BSTree< Key, Value, Compare >::Iterator::operator==(const Iterator & rhs) const
{
  return node_ == rhs.node_;
}

template< typename Key, typename Value, typename Compare >
bool BSTree< Key, Value, Compare >::Iterator::operator!=(const Iterator & rhs) const
{
  return node_ != rhs.node_;
}

template< typename Key, typename Value, typename Compare >
class BSTree< Key, Value, Compare >::ConstIterator : public std::iterator< std::input_iterator_tag, Key, Value, Compare >
{
  friend class BSTree;
public:
  ConstIterator();
  explicit ConstIterator(const Node * node);
  ConstIterator(const ConstIterator & iter);
  ~ConstIterator() = default;

  ConstIterator & operator=(const ConstIterator & iter);
  ConstIterator & operator=(ConstIterator && rhs);
  const value_t & operator*() const;
  const value_t * operator->() const;
  ConstIterator & operator++();
  ConstIterator operator++(int);
  ConstIterator & operator--();
  ConstIterator operator--(int);
  bool operator==(const ConstIterator & rhs) const;
  bool operator!=(const ConstIterator & rhs) const;
private:
  const Node * node_;
};

template< typename Key, typename Value, typename Compare >
BSTree< Key, Value, Compare >::ConstIterator::ConstIterator()
{
  node_(nullptr);
}

template< typename Key, typename Value, typename Compare >
BSTree< Key, Value, Compare >::ConstIterator::ConstIterator(const Node * node)
{
  node_ = node;
}

template< typename Key, typename Value, typename Compare >
BSTree< Key, Value, Compare >::ConstIterator::ConstIterator(const ConstIterator & iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::ConstIterator & BSTree< Key, Value, Compare >::ConstIterator::operator=(const ConstIterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::ConstIterator & BSTree< Key, Value, Compare >::ConstIterator::operator=(ConstIterator && rhs)
{
  node_(rhs.node_);
  return *this;
}

template< typename Key, typename Value, typename Compare >
const std::pair< Key, Value > & BSTree< Key, Value, Compare >::ConstIterator::operator*() const
{
  return node_->data;
}

template< typename Key, typename Value, typename Compare >
const std::pair< Key, Value > * BSTree< Key, Value, Compare >::ConstIterator::operator->() const
{
  return std::addressof(node_->data);
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::ConstIterator & BSTree< Key, Value, Compare >::ConstIterator::operator++()
{
  if (node_ == nullptr)
  {
    return *this;
  }
  else if (node_->right == nullptr)
  {
    Node * temp = node_->parent;
    while (temp != nullptr && node_ == temp->right)
    {
      node_ = temp;
      temp = node_->parent;
    }
    node_ = temp;
    return *this;
  }
  else
  {
    node_ = node_->right;
    if (node_->left == nullptr)
    {
      return *this;
    }
    while (node_->left != nullptr)
    {
      node_ = node_->left;
    }
    return *this;
  }
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::ConstIterator BSTree< Key, Value, Compare >::ConstIterator::operator++(int)
{
  ConstIterator temp(*this);
  ++(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::ConstIterator & BSTree< Key, Value, Compare >::ConstIterator::operator--()
{
  if (node_ == nullptr)
  {
    return *this;
  }
  else if (node_->left == nullptr)
  {
    Node * temp = node_->parent;
    while (temp != nullptr && node_ == temp->left)
    {
      node_ = temp;
      temp = node_->parent;
    }
    node_ = temp;
    return *this;
  }
  else
  {
    node_ = node_->left;
    while (node_->right != nullptr)
    {
      node_ = node_->right;
    }
    return *this;
  }
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::ConstIterator BSTree< Key, Value, Compare >::ConstIterator::operator--(int)
{
  ConstIterator temp(*this);
  --(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
bool BSTree< Key, Value, Compare >::ConstIterator::operator==(const ConstIterator & rhs) const
{
  return node_ == rhs.node_;
}

template< typename Key, typename Value, typename Compare >
bool BSTree< Key, Value, Compare >::ConstIterator::operator!=(const ConstIterator & rhs) const
{
  return node_ != rhs.node_;
}

template < typename Key, typename Value, typename Compare >
class ponomarev::BSTree< Key, Value, Compare >::LnRIterator: public std::iterator< std::forward_iterator_tag, value_t >
{
  friend class BSTree;
public:
  using this_t = LnRIterator;
  LnRIterator();
  LnRIterator(const this_t &) = default;
  ~LnRIterator() = default;

  this_t & operator=(const this_t &) = default;
  this_t & operator++();
  this_t operator++(int);

  value_t & operator*();
  value_t * operator->();
  const value_t & operator*() const;
  const value_t * operator->() const;

  bool operator!=(const this_t &) const;
  bool operator==(const this_t &) const;

private:
  Node * node_;
  Node * el_;
  Stack< Node * > stack_;
};

template < typename Key, typename Value, typename Compare >
ponomarev::BSTree< Key, Value, Compare >::LnRIterator::LnRIterator():
  node_(nullptr),
  el_(nullptr),
  stack_(Stack< Node * >())
{}

template < typename Key, typename Value, typename Compare >
typename ponomarev::BSTree< Key, Value, Compare >::LnRIterator & ponomarev::BSTree< Key, Value, Compare >::LnRIterator::operator++()
{
  if (node_ != nullptr || !stack_.isEmpty())
  {
    while (node_ != nullptr)
    {
      stack_.push(node_);
      node_ = node_->left;
    }
    el_ = stack_.getUp();
    stack_.pop();
    node_ = el_->right;
  }
  else
  {
    throw std::out_of_range("wrong increment");
  }
  return *this;
}

template < typename Key, typename Value, typename Compare >
typename ponomarev::BSTree< Key, Value, Compare >::LnRIterator ponomarev::BSTree< Key, Value, Compare >::LnRIterator::operator++(int)
{
  LnRIterator result(*this);
  ++(*this);
  return result;
}

template < typename Key, typename Value, typename Compare >
value_t< Key, Value > & ponomarev::BSTree< Key, Value, Compare >::LnRIterator::operator*()
{
  return el_->elem;
}

template < typename Key, typename Value, typename Compare >
value_t< Key, Value > * ponomarev::BSTree< Key, Value, Compare >::LnRIterator::operator->()
{
  return std::addressof(el_->elem);
}

template < typename Key, typename Value, typename Compare >
const value_t< Key, Value > & ponomarev::BSTree< Key, Value, Compare >::LnRIterator::operator*() const
{
  return el_->elem;
}

template < typename Key, typename Value, typename Compare >
const value_t< Key, Value > * ponomarev::BSTree< Key, Value, Compare >::LnRIterator::operator->() const
{
  return std::addressof(el_->elem);
}

template < typename Key, typename Value, typename Compare >
bool ponomarev::BSTree< Key, Value, Compare >::LnRIterator::operator==(const this_t & rhs) const
{
  return el_ == rhs.el_;
}

template < typename Key, typename Value, typename Compare >
bool ponomarev::BSTree< Key, Value, Compare >::LnRIterator::operator!=(const this_t & rhs) const
{
  return !(rhs == *this);
}

template < typename Key, typename Value, typename Compare >
class ponomarev::BSTree< Key, Value, Compare >::RnLIterator: public std::iterator< std::forward_iterator_tag, value_t >
{
  friend class BSTree;
public:
  using this_t = RnLIterator;
  RnLIterator();
  RnLIterator(const this_t &) = default;
  ~RnLIterator() = default;

  this_t & operator=(const this_t &) = default;
  this_t & operator++();
  this_t operator++(int);

  value_t & operator*();
  value_t * operator->();
  const value_t & operator*() const;
  const value_t * operator->() const;

  bool operator!=(const this_t &) const;
  bool operator==(const this_t &) const;

private:
  Node * node_;
  Node * el_;
  Stack< Node * > stack_;
};

template < typename Key, typename Value, typename Compare >
ponomarev::BSTree< Key, Value, Compare >::RnLIterator::RnLIterator():
  node_(nullptr),
  el_(nullptr),
  stack_(Stack< Node * >())
{}

template < typename Key, typename Value, typename Compare >
typename ponomarev::BSTree< Key, Value, Compare >::RnLIterator & ponomarev::BSTree< Key, Value, Compare >::RnLIterator::operator++()
{
  if (node_ != nullptr || !stack_.isEmpty())
  {
    while (node_ != nullptr)
    {
      stack_.push(node_);
      node_ = node_->right;
    }
    el_ = stack_.getUp();
    stack_.pop();
    node_ = el_->left;
  }
  else
  {
    throw std::out_of_range("can't increment");
  }
  return *this;
}

template < typename Key, typename Value, typename Compare >
typename ponomarev::BSTree< Key, Value, Compare >::RnLIterator ponomarev::BSTree< Key, Value, Compare >::RnLIterator::operator++(int)
{
  RnLIterator result(*this);
  ++(*this);
  return result;
}

template < typename Key, typename Value, typename Compare >
value_t< Key, Value > & ponomarev::BSTree< Key, Value, Compare >::RnLIterator::operator*()
{
  return el_->elem;
}

template < typename Key, typename Value, typename Compare >
value_t< Key, Value > * ponomarev::BSTree< Key, Value, Compare >::RnLIterator::operator->()
{
  return std::addressof(el_->elem);
}

template < typename Key, typename Value, typename Compare >
const value_t< Key, Value > & ponomarev::BSTree< Key, Value, Compare >::RnLIterator::operator*() const
{
  return el_->elem;
}

template < typename Key, typename Value, typename Compare >
const value_t< Key, Value > * ponomarev::BSTree< Key, Value, Compare >::RnLIterator::operator->() const
{
  return std::addressof(el_->elem);
}

template < typename Key, typename Value, typename Compare >
bool ponomarev::BSTree< Key, Value, Compare >::RnLIterator::operator==(const this_t & rhs) const
{
  return el_ == rhs.el_;
}

template < typename Key, typename Value, typename Compare >
bool ponomarev::BSTree< Key, Value, Compare >::RnLIterator::operator!=(const this_t & rhs) const
{
  return !(rhs == *this);
}

template< typename Key, typename Value, typename Compare >
class BSTree< Key, Value, Compare >::Node
{
  friend class BSTree;
public:
  Node(const Key key, const Value value):
    left(nullptr),
    right(nullptr),
    parent(nullptr),
    hight(1),
    data(value_t(key, value))
  {}
private:
  Node * left;
  Node * right;
  Node * parent;
  size_t hight;
  value_t data;
};

template< typename Key, typename Value, typename Compare >
BSTree< Key, Value, Compare >::BSTree()
{
  root_ = nullptr;
  size_ = 0;
}

template< typename Key, typename Value, typename Compare >
BSTree< Key, Value, Compare >::BSTree(const BSTree< Key, Value, Compare > & tree)
{
  root_ = tree.root_;
  size_ = tree.size_;
}

template< typename Key, typename Value, typename Compare >
BSTree< Key, Value, Compare >::BSTree(BSTree< Key, Value, Compare > && tree) noexcept
{
  root_ = tree.root_;
  size_ = std::move(tree.size_);
}

template < typename Key, typename Value, typename Compare >
BSTree< Key, Value, Compare > & BSTree< Key, Value, Compare >::operator=(BSTree other)
{
  swap(*this, other);
  return *this;
}

template < typename Key, typename Value, typename Compare >
BSTree< Key, Value, Compare > & BSTree< Key, Value, Compare >::operator=(BSTree && other)
{
  if (&other != this)
  {
    clear();
    root_ = std::move(other.root_);
    other.root_ = nullptr;
  }
  return *this;
}

template< typename Key, typename Value, typename Compare >
size_t BSTree< Key, Value, Compare >::getSize() const noexcept
{
  return size_;
}

template< typename Key, typename Value, typename Compare >
bool BSTree< Key, Value, Compare >::isEmpty() const noexcept
{
  return size_ == 0;
}

template< typename Key, typename Value, typename Compare >
Value & BSTree< Key, Value, Compare >::operator[](const Key & key)
{
  Iterator iter(find(key));
  if (iter == end())
  {
    insert(std::pair< Key, Value>(key, Value()));
    iter = find(key);
  }
  return iter->second;
}

template< typename Key, typename Value, typename Compare >
Value & BSTree< Key, Value, Compare >::operator[](Key && key)
{
  Iterator iter(find(key));
  if (iter == end())
  {
    insert(std::pair< Key, Value>(key, Value()));
    iter = find(key);
  }
  return iter->second;
}

template< typename Key, typename Value, typename Compare >
Value & BSTree< Key, Value, Compare >::at(const Key & key)
{
  if (find(key) == end())
  {
    throw std::out_of_range("The element does not exist\n");
  }
  else
  {
    return (find(key))->second;
  }
}

template< typename Key, typename Value, typename Compare >
const Value & BSTree< Key, Value, Compare >::at(const Key & key) const
{
  if (find(key) == end())
  {
    throw std::out_of_range("The element does not exist\n");
  }
  else
  {
    return (find(key))->second;
  }
}

template< typename Key, typename Value, typename Compare >
void BSTree< Key, Value, Compare >::insert(const value_t & pair)
{
  root_ = push(pair.first, pair.second, root_);
  size_++;
}

template< typename Key, typename Value, typename Compare >
void BSTree< Key, Value, Compare >::insert(value_t && pair)
{
  root_ = push(pair.first, pair.second, root_);
  size_++;
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::Node * BSTree< Key, Value, Compare >::push(const Key & key, const Value & value, Node * node_)
{
  if (node_ == nullptr)
  {
    node_ = new Node(key, value);
  }
  else if (key < node_->data.first)
  {
    node_->left = push(key, value, node_->left);
    node_->left->parent = node_;
    node_->hight++;
    if (getHight(node_->left) - getHight(node_->right) > 1)
    {
      if (node_->right == nullptr || key < node_->left->data.first)
      {
        node_ = rightRotate(node_);
      }
      else
      {
        node_ = leftRightRotate(node_);
      }
    }
  }
  else if (key > node_->data.first)
  {
    node_->right = push(key, value, node_->right);
    node_->right->parent = node_;
    node_->hight++;
    if ((getHight(node_->right) - getHight(node_->left)) > 1)
    {
      if (node_->left == nullptr || key > node_->right->data.first)
      {
        node_ = leftRotate(node_);
      }
      else
      {
        node_ = rightLeftRotate(node_);
      }
    }
  }
  return node_;
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::Node * BSTree< Key, Value, Compare >::rightRotate(Node * node_)
{
  Node * temp = node_->left;
  node_->left = temp->right;
  if (node_->left != nullptr)
  {
    node_->left->parent = node_;
  }
  temp->parent = node_->parent;
  node_->parent = temp;
  temp->right = node_;
  node_->hight = std::max(getHight(node_->left), getHight(node_->right)) + 1;
  temp->hight = std::max(node_->hight, getHight(temp->left)) + 1;
  return temp;
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::Node * BSTree< Key, Value, Compare >::leftRotate(Node * node_)
{
  Node * temp = node_->right;
  node_->right = temp->left;
  if (node_->right != nullptr)
  {
    node_->right->parent = node_;
  }
  temp->parent = node_->parent;
  node_->parent = temp;
  temp->left = node_;
  node_->hight = std::max(getHight(node_->left), getHight(node_->right)) + 1;
  temp->hight = std::max(node_->hight, getHight(temp->right)) + 1;
  return temp;
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::Node * BSTree< Key, Value, Compare >::leftRightRotate(Node * node_)
{
  node_->left = leftRotate(node_->left);
  return rightRotate(node_);
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::Node * BSTree< Key, Value, Compare >::rightLeftRotate(Node * node_)
{
  node_->right = rightRotate(node_->right);
  return leftRotate(node_);
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::Iterator BSTree< Key, Value, Compare >::erase(Iterator pos)
{
  if (pos == ConstIterator(nullptr, root_))
  {
    return end();
  }
  Node * temp = pos.Iterator.node_;
  Node * parent = temp->parent_;
  Node * next = nullptr;
  if (temp->left_ && temp->right_)
  {
    next = temp->right_;
    while (next->left_)
    {
      next = next->left_;
    }
    temp = next;
    parent = next->parent_;
  }
  Node* child = temp->left_ ? temp->left_ : temp->right_;
  if (child)
  {
    child->parent_ = parent;
  }
  if (!parent)
  {
    root_ = child;
  }
  else if (temp == parent->left_)
  {
    parent->left_ = child;
  }
  else
  {
    parent->right_ = child;
  }
  while (parent)
  {
    getHight(parent);
    parent = balance(parent);
    parent = parent->parent_;
  }
  delete temp;
  return Iterator(ConstIterator(child ? child : parent, root_));
}

template < typename Key, typename Value, typename Compare >
size_t BSTree< Key, Value, Compare >::erase(const Key & key)
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

template< typename Key, typename Value, typename Compare >
size_t BSTree< Key, Value, Compare >::getHight(Node * node_)
{
  return (node_ == nullptr ? 0 : node_->hight);
}

template< typename Key, typename Value, typename Compare >
void BSTree< Key, Value, Compare >::deleteAll(Node * node_)
{
  if (node_ != nullptr)
  {
    deleteAll(node_->left);
    deleteAll(node_->right);
    delete node_;
  }
}

template< typename Key, typename Value, typename Compare >
void BSTree< Key, Value, Compare >::clear()
{
  deleteAll(root_);
  root_ = nullptr;
  size_ = 0;
}

template< typename Key, typename Value, typename Compare >
void BSTree< Key, Value, Compare >::swap(BSTree & el) noexcept
{
  Node * temp = el.root_;
  el.root_ = root_;
  root_ = temp;
  size_t tempSize = el.size_;
  el.size_ = size_;
  size_ = tempSize;
}

template< typename Key, typename Value, typename Compare >
std::pair< typename BSTree< Key, Value, Compare >::Iterator,
           typename BSTree< Key, Value, Compare >::Iterator > BSTree< Key, Value, Compare >::equal_range(const Key & key)
{
  if (find(key) == end())
  {
    Iterator iter(begin());
    while (iter != end())
    {
      if ((*iter).first > key)
      {
        break;
      }
      iter++;
    }
    return std::make_pair(iter, iter);
  }
  else
  {
    return std::make_pair(find(key), find(key)++);
  }
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::Iterator BSTree< Key, Value, Compare >::begin() noexcept
{
  Node * temp = root_;
  while (temp->left != nullptr)
  {
    temp = temp->left;
  }
  return Iterator(temp);
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::Iterator BSTree< Key, Value, Compare >::end() noexcept
{
  return Iterator(nullptr);
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::ConstIterator BSTree< Key, Value, Compare >::cbegin() const noexcept
{
  Node * temp = root_;
  while (temp->left != nullptr)
  {
    temp = temp->left;
  }
  return ConstIterator(temp);
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::ConstIterator BSTree< Key, Value, Compare >::cend() const noexcept
{
  return ConstIterator(nullptr);
}

template< typename Key, typename Value, typename Compare >
typename BSTree< Key, Value, Compare >::Iterator BSTree< Key, Value, Compare >::find(const Key & key)
{
  Node * temp = root_;
  while (temp)
  {
    if (temp->data.first == key)
    {
      return Iterator(temp);
    }
    else if (key > temp->data.first)
    {
      temp = temp->right;
    }
    else if (key < temp->data.first)
    {
      temp = temp->left;
    }
  }
  return end();
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F ponomarev::BSTree< Key, Value, Compare >::constTraverseLR(F func) const
{
  Stack< Node * > stack;
  Node * temp = root_;
  while ((temp != nullptr) || (!stack.isEmpty()))
  {
    while (temp != nullptr)
    {
      stack.push(temp);
      temp = temp->left;
    }
    temp = stack.getUp();
    stack.pop();
    func(temp->elem);
    temp = temp->right;
  }

  return func;
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F ponomarev::BSTree< Key, Value, Compare >::traverseLR(F func)
{
  Stack< Node * > stack;
  Node * temp = root_;
  while ((temp != nullptr) || (!stack.isEmpty()))
  {
    while (temp != nullptr)
    {
      stack.push(temp);
      temp = temp->left;
    }
    temp = stack.getUp();
    stack.pop();
    func(temp->data);
    temp = temp->right;
  }

  return func;
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F ponomarev::BSTree< Key, Value, Compare >::constTraverseRL(F func) const
{
  Stack< Node * > stack;
  Node * temp = root_;
  while ((temp != nullptr) || (!stack.isEmpty()))
  {
    while (temp != nullptr)
    {
      stack.push(temp);
      temp = temp->right;
    }
    temp = stack.getUp();
    stack.pop();
    func(temp->data);
    temp = temp->left;
  }

  return func;
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F ponomarev::BSTree< Key, Value, Compare >::traverseRL(F func)
{
  Stack< Node * > stack;
  Node * temp = root_;
  while ((temp != nullptr) || (!stack.isEmpty()))
  {
    while (temp != nullptr)
    {
      stack.push(temp);
      temp = temp->right;
    }
    temp = stack.getUp();
    stack.pop();
    func(temp->data);
    temp = temp->left;
  }
  return func;
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F ponomarev::BSTree< Key, Value, Compare >::constTraverseBreadth(F func) const
{
  if (isEmpty())
  {
     return func;
  }
  Queue< Node * > queue;
  queue.push(root_);

  while (!queue.isEmpty())
  {
    Node * node = queue.getElem();
    func(node->data);
    queue.pop();
    if (node->left != nullptr)
    {
      queue.push(node->left);
    }
    if (node->right != nullptr)
    {
      queue.push(node->right);
    }
  }

  return func;
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F ponomarev::BSTree< Key, Value, Compare >::traverseBreadth(F func)
{
  if (isEmpty())
  {
     return func;
  }
  Queue< Node * > queue;
  queue.push(root_);

  while (!queue.isEmpty())
  {
    Node * node = queue.getElem();
    func(node->data);
    queue.pop();
    if (node->left != nullptr)
    {
      queue.push(node->left);
    }
    if (node->right != nullptr)
    {
      queue.push(node->right);
    }
  }

  return func;
}

#endif
