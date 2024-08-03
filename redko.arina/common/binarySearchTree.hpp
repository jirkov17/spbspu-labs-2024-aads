#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <utility>
#include <stdexcept>
#include "stack.hpp"
#include "queue.hpp"

namespace redko
{
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class BSTree
  {
  public:

    class Iterator;
    class ConstIterator;

    class LnRIterator;
    class RnLIterator;
    class BreadthIterator;

    using value_t = typename std::pair< Key, Value >;

    using iterator = Iterator;
    using const_iterator = ConstIterator;

    BSTree();
    BSTree(const BSTree & other);
    BSTree(BSTree && other);
    template< class InputIt >
    BSTree(InputIt first, InputIt last);
    BSTree(std::initializer_list< value_t > init);
    ~BSTree();

    BSTree & operator=(const BSTree & other);
    BSTree & operator=(BSTree && other);

    Value & at(const Key & key);
    const Value & at(const Key & key) const;
    Value & operator[](const Key & key);
    Value & operator[](Key && key);

    bool empty() const noexcept;
    size_t size() const noexcept;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    void clear();
    iterator insert(const value_t & value);
    iterator insert(value_t && value);
    size_t erase(const Key & key);
    template< class... Args >
    iterator emplace(Args&&... args);

    void swap(BSTree & other) noexcept;

    iterator find(const Key & key);
    const_iterator find(const Key & key) const;
    std::pair<iterator, iterator> equalRange(const Key & key);
    std::pair<const_iterator, const_iterator> equalRange(const Key & key) const;
    iterator lowerBound(const Key & key);
    const_iterator lowerBound(const Key & key) const;
    iterator upperBound(const Key & key);
    const_iterator upperBound(const Key & key) const;

    template< typename F >
    F ctraverseLR(F func) const;
    template< typename F >
    F traverseLR(F func);
    template< typename F >
    F ctraverseRL(F func) const;
    template< typename F >
    F traverseRL(F func);
    template< typename F >
    F ctraverseBreadth(F func) const;
    template< typename F >
    F traverseBreadth(F func);

  private:
    struct Node
    {
      explicit Node(value_t value, Node * p = nullptr, Node * r = nullptr, Node * l = nullptr):
        elem(value),
        parent(p),
        right(r),
        left(l)
      {}

      value_t elem;
      Node * parent;
      Node * right;
      Node * left;
    };

    Node * root_;
    Compare cmp_;

    void deleteSubtree(Node * root);

    size_t getCountNode(Node * root) const;
    size_t getHeight(Node * node);
    int getDiff(Node * node);

    Node * rotateRR(Node * node);
    Node * rotateLL(Node * node);
    Node * rotateRL(Node * node);
    Node * rotateLR(Node * node);
    Node * insertTo(Node * node, const value_t & value);
    Node * insertTo(Node * node, value_t && value);
    Node * deleteFrom(Node * node, const Key & key);
  };
}

template < typename Key, typename Value, typename Compare >
class redko::BSTree< Key, Value, Compare >::Iterator: public std::iterator< std::bidirectional_iterator_tag, value_t >
{
  friend class BSTree;
public:

  using this_t = Iterator;

  Iterator();
  Iterator(ConstIterator);
  Iterator(LnRIterator);
  Iterator(RnLIterator);
  Iterator(BreadthIterator);
  Iterator(const this_t &) = default;
  ~Iterator() = default;

  this_t & operator=(const this_t &) = default;
  this_t & operator++();
  this_t operator++(int);
  this_t & operator--();
  this_t operator--(int);

  value_t & operator*();
  value_t * operator->();
  const value_t & operator*() const;
  const value_t * operator->() const;

  bool operator==(const this_t &) const;
  bool operator!=(const this_t &) const;

private:
  Node * node_;
  Node * treeRoot_;
  Iterator(Node * ptr, Node * rootPtr);
};

template < typename Key, typename Value, typename Compare >
using iterator = typename redko::BSTree< Key, Value, Compare >::Iterator;

template < typename Key, typename Value >
using value_t = typename std::pair< Key, Value >;

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::Iterator::Iterator():
  node_(nullptr),
  treeRoot_(nullptr)
{}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::Iterator::Iterator(ConstIterator iter):
  node_(iter.iter_.node_),
  treeRoot_(iter.iter_.treeRoot_)
{}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::Iterator::Iterator(LnRIterator iter):
  node_(iter.curr_),
  treeRoot_(iter.curr_)
{}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::Iterator::Iterator(RnLIterator iter):
  node_(iter.curr_),
  treeRoot_(iter.curr_)
{}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::Iterator::Iterator(BreadthIterator iter):
  node_(iter.node_),
  treeRoot_(iter.node_)
{}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::Iterator::Iterator(Node * ptr, Node * rootPtr):
  node_(ptr),
  treeRoot_(rootPtr)
{}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::Iterator & redko::BSTree< Key, Value, Compare >::Iterator::operator++()
{
  if (node_ == nullptr)
  {
    throw std::logic_error("Error: unable to increment");
  }
  if (node_->right != nullptr)
  {
    node_ = node_->right;
    while (node_->left != nullptr)
    {
      node_ = node_->left;
    }
  }
  else
  {
    while (node_->parent != nullptr && node_ == node_->parent->right)
    {
      node_ = node_->parent;
    }
    node_ = node_->parent;
  }
  return *this;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::Iterator redko::BSTree< Key, Value, Compare >::Iterator::operator++(int)
{
  Iterator result(*this);
  ++(*this);
  return result;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::Iterator & redko::BSTree< Key, Value, Compare >::Iterator::operator--()
{
  if (node_ == nullptr)
  {
    node_ = treeRoot_;
    while (node_->right != nullptr)
    {
      node_ = node_->right;
    }
  }
  else if (node_->left != nullptr)
  {
    node_ = node_->left;
    while (node_->right != nullptr)
    {
      node_ = node_->right;
    }
  }
  else
  {
    while (node_->parent != nullptr && node_ == node_->parent->left)
    {
      node_ = node_->parent;
    }
    node_ = node_->parent;
  }
  return *this;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::Iterator redko::BSTree< Key, Value, Compare >::Iterator::operator--(int)
{
  Iterator result(*this);
  --(*this);
  return result;
}

template < typename Key, typename Value, typename Compare >
value_t< Key, Value > & redko::BSTree< Key, Value, Compare >::Iterator::operator*()
{
  return node_->elem;
}

template < typename Key, typename Value, typename Compare >
value_t< Key, Value > * redko::BSTree< Key, Value, Compare >::Iterator::operator->()
{
  return std::addressof(node_->elem);
}

template < typename Key, typename Value, typename Compare >
const value_t< Key, Value > & redko::BSTree< Key, Value, Compare >::Iterator::operator*() const
{
  return node_->elem;
}

template < typename Key, typename Value, typename Compare >
const value_t< Key, Value > * redko::BSTree< Key, Value, Compare >::Iterator::operator->() const
{
  return std::addressof(node_->elem);
}

template < typename Key, typename Value, typename Compare >
bool redko::BSTree< Key, Value, Compare >::Iterator::operator==(const this_t & rhs) const
{
  return node_ == rhs.node_;
}

template < typename Key, typename Value, typename Compare >
bool redko::BSTree< Key, Value, Compare >::Iterator::operator!=(const this_t & rhs) const
{
  return !(rhs == *this);
}

template < typename Key, typename Value, typename Compare >
class redko::BSTree< Key, Value, Compare >::ConstIterator: public std::iterator< std::bidirectional_iterator_tag, value_t >
{
  friend class BSTree;
public:

  using this_t = ConstIterator;

  ConstIterator();
  ConstIterator(Iterator);
  ConstIterator(const this_t &) = default;
  ~ConstIterator() = default;

  this_t & operator=(const this_t &) = default;
  this_t & operator++();
  this_t operator++(int);
  this_t & operator--();
  this_t operator--(int);

  const value_t & operator*() const;
  const value_t * operator->() const;

  bool operator==(const this_t &) const;
  bool operator!=(const this_t &) const;

private:
  Iterator iter_;
};

template < typename Key, typename Value, typename Compare >
using const_iterator = typename redko::BSTree< Key, Value, Compare >::ConstIterator;

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::ConstIterator::ConstIterator():
  iter_(Iterator())
{}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::ConstIterator::ConstIterator(Iterator iter):
  iter_(iter)
{}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::ConstIterator & redko::BSTree< Key, Value, Compare >::ConstIterator::operator++()
{
  ++iter_;
  return *this;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::ConstIterator redko::BSTree< Key, Value, Compare >::ConstIterator::operator++(int)
{
  ConstIterator result(iter_);
  ++(iter_);
  return result;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::ConstIterator & redko::BSTree< Key, Value, Compare >::ConstIterator::operator--()
{
  --iter_;
  return *this;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::ConstIterator redko::BSTree< Key, Value, Compare >::ConstIterator::operator--(int)
{
  ConstIterator result(iter_);
  --(iter_);
  return result;
}

template < typename Key, typename Value, typename Compare >
const value_t< Key, Value > & redko::BSTree< Key, Value, Compare >::ConstIterator::operator*() const
{
  return *iter_;
}

template < typename Key, typename Value, typename Compare >
const value_t< Key, Value > * redko::BSTree< Key, Value, Compare >::ConstIterator::operator->() const
{
  return std::addressof(iter_.node_->elem);
}

template < typename Key, typename Value, typename Compare >
bool redko::BSTree< Key, Value, Compare >::ConstIterator::operator==(const this_t & rhs) const
{
  return iter_.node_ == rhs.iter_.node_;
}

template < typename Key, typename Value, typename Compare >
bool redko::BSTree< Key, Value, Compare >::ConstIterator::operator!=(const this_t & rhs) const
{
  return !(rhs == *this);
}

template < typename Key, typename Value, typename Compare >
class redko::BSTree< Key, Value, Compare >::LnRIterator: public std::iterator< std::forward_iterator_tag, value_t >
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
  Node * curr_;
  Stack< Node * > stack_;
  explicit LnRIterator(Node * ptr);
};

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::LnRIterator::LnRIterator():
  node_(nullptr),
  curr_(nullptr),
  stack_(Stack< Node * >())
{}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::LnRIterator::LnRIterator(Node * ptr):
  node_(ptr),
  curr_(nullptr),
  stack_(Stack< Node * >())
{}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::LnRIterator & redko::BSTree< Key, Value, Compare >::LnRIterator::operator++()
{
  if (node_ != nullptr || !stack_.empty())
  {
    while (node_ != nullptr)
    {
      stack_.push(node_);
      node_ = node_->left;
    }
    curr_ = stack_.top();
    stack_.pop();
    node_ = curr_->right;
  }
  else
  {
    throw std::out_of_range("Error: unable to increment");
  }
  return *this;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::LnRIterator redko::BSTree< Key, Value, Compare >::LnRIterator::operator++(int)
{
  LnRIterator result(*this);
  ++(*this);
  return result;
}

template < typename Key, typename Value, typename Compare >
value_t< Key, Value > & redko::BSTree< Key, Value, Compare >::LnRIterator::operator*()
{
  return curr_->elem;
}

template < typename Key, typename Value, typename Compare >
value_t< Key, Value > * redko::BSTree< Key, Value, Compare >::LnRIterator::operator->()
{
  return std::addressof(curr_->elem);
}

template < typename Key, typename Value, typename Compare >
const value_t< Key, Value > & redko::BSTree< Key, Value, Compare >::LnRIterator::operator*() const
{
  return curr_->elem;
}

template < typename Key, typename Value, typename Compare >
const value_t< Key, Value > * redko::BSTree< Key, Value, Compare >::LnRIterator::operator->() const
{
  return std::addressof(curr_->elem);
}

template < typename Key, typename Value, typename Compare >
bool redko::BSTree< Key, Value, Compare >::LnRIterator::operator==(const this_t & rhs) const
{
  return curr_ == rhs.curr_;
}

template < typename Key, typename Value, typename Compare >
bool redko::BSTree< Key, Value, Compare >::LnRIterator::operator!=(const this_t & rhs) const
{
  return !(rhs == *this);
}

template < typename Key, typename Value, typename Compare >
class redko::BSTree< Key, Value, Compare >::RnLIterator: public std::iterator< std::forward_iterator_tag, value_t >
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
  Node * curr_;
  Stack< Node * > stack_;
  explicit RnLIterator(Node * ptr);
};

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::RnLIterator::RnLIterator():
  node_(nullptr),
  curr_(nullptr),
  stack_(Stack< Node * >())
{}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::RnLIterator::RnLIterator(Node * ptr):
  node_(ptr),
  curr_(nullptr),
  stack_(Stack< Node * >())
{}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::RnLIterator & redko::BSTree< Key, Value, Compare >::RnLIterator::operator++()
{
  if (node_ != nullptr || !stack_.empty())
  {
    while (node_ != nullptr)
    {
      stack_.push(node_);
      node_ = node_->right;
    }
    curr_ = stack_.top();
    stack_.pop();
    node_ = curr_->left;
  }
  else
  {
    throw std::out_of_range("Error: unable to increment");
  }
  return *this;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::RnLIterator redko::BSTree< Key, Value, Compare >::RnLIterator::operator++(int)
{
  RnLIterator result(*this);
  ++(*this);
  return result;
}

template < typename Key, typename Value, typename Compare >
value_t< Key, Value > & redko::BSTree< Key, Value, Compare >::RnLIterator::operator*()
{
  return curr_->elem;
}

template < typename Key, typename Value, typename Compare >
value_t< Key, Value > * redko::BSTree< Key, Value, Compare >::RnLIterator::operator->()
{
  return std::addressof(curr_->elem);
}

template < typename Key, typename Value, typename Compare >
const value_t< Key, Value > & redko::BSTree< Key, Value, Compare >::RnLIterator::operator*() const
{
  return curr_->elem;
}

template < typename Key, typename Value, typename Compare >
const value_t< Key, Value > * redko::BSTree< Key, Value, Compare >::RnLIterator::operator->() const
{
  return std::addressof(curr_->elem);
}

template < typename Key, typename Value, typename Compare >
bool redko::BSTree< Key, Value, Compare >::RnLIterator::operator==(const this_t & rhs) const
{
  return curr_ == rhs.curr_;
}

template < typename Key, typename Value, typename Compare >
bool redko::BSTree< Key, Value, Compare >::RnLIterator::operator!=(const this_t & rhs) const
{
  return !(rhs == *this);
}
template < typename Key, typename Value, typename Compare >
class redko::BSTree< Key, Value, Compare >::BreadthIterator: public std::iterator< std::forward_iterator_tag, value_t >
{
  friend class BSTree;
public:
  using this_t = BreadthIterator;
  BreadthIterator();
  BreadthIterator(const this_t &) = default;
  ~BreadthIterator() = default;

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
  Queue< Node * > queue_;
  explicit BreadthIterator(Node * ptr);
};

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::BreadthIterator::BreadthIterator():
  node_(nullptr),
  queue_(Queue< Node * >())
{}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::BreadthIterator::BreadthIterator(Node * ptr):
  node_(ptr),
  queue_({ptr})
{}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::BreadthIterator & redko::BSTree< Key, Value, Compare >::BreadthIterator::operator++()
{
  if (!queue_.empty())
  {
    node_ = queue_.front();
    queue_.pop();
    if (node_->left != nullptr)
    {
      queue_.push(node_->left);
    }
    if (node_->right != nullptr)
    {
      queue_.push(node_->right);
    }
  }
  else
  {
    throw std::out_of_range("Error: unable to increment");
  }
  return *this;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::BreadthIterator redko::BSTree< Key, Value, Compare >::BreadthIterator::operator++(int)
{
  BreadthIterator result(*this);
  ++(*this);
  return result;
}

template < typename Key, typename Value, typename Compare >
value_t< Key, Value > & redko::BSTree< Key, Value, Compare >::BreadthIterator::operator*()
{
  return node_->elem;
}

template < typename Key, typename Value, typename Compare >
value_t< Key, Value > * redko::BSTree< Key, Value, Compare >::BreadthIterator::operator->()
{
  return std::addressof(node_->elem);
}

template < typename Key, typename Value, typename Compare >
const value_t< Key, Value > & redko::BSTree< Key, Value, Compare >::BreadthIterator::operator*() const
{
  return node_->elem;
}

template < typename Key, typename Value, typename Compare >
const value_t< Key, Value > * redko::BSTree< Key, Value, Compare >::BreadthIterator::operator->() const
{
  return std::addressof(node_->elem);
}

template < typename Key, typename Value, typename Compare >
bool redko::BSTree< Key, Value, Compare >::BreadthIterator::operator==(const this_t & rhs) const
{
  return node_ == rhs.node_();
}

template < typename Key, typename Value, typename Compare >
bool redko::BSTree< Key, Value, Compare >::BreadthIterator::operator!=(const this_t & rhs) const
{
  return !(rhs == *this);
}


template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::BSTree():
  root_(nullptr),
  cmp_(Compare())
{}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::BSTree(const BSTree & other):
  root_(nullptr),
  cmp_(other.cmp_)
{
  for (iterator it = other.begin(); it != end(); ++it)
  {
    insert(*it);
  }
}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::BSTree(BSTree && other):
  root_(std::move(other.root_)),
  cmp_(std::move(other.cmp_))
{
  other.root_ = nullptr;
}

template < typename Key, typename Value, typename Compare >
template< class InputIt >
redko::BSTree< Key, Value, Compare >::BSTree(InputIt first, InputIt last):
  root_(nullptr),
  cmp_(Compare())
{
  for (; first != last; ++first)
  {
    insert(*first);
  }
}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::BSTree(std::initializer_list< value_t > init)
{
  for (auto value : init)
  {
    insert(value);
  }
}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare >::~BSTree()
{
  clear();
}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare > & redko::BSTree< Key, Value, Compare >::operator=(const BSTree & other)
{
  if (&other != this)
  {
    clear();
    for (iterator it = other.begin(); it != end(); ++it)
    {
      insert(*it);
    }
  }
  return *this;
}

template < typename Key, typename Value, typename Compare >
redko::BSTree< Key, Value, Compare > & redko::BSTree< Key, Value, Compare >::operator=(BSTree && other)
{
  if (&other != this)
  {
    clear();
    root_ = std::move(other.root_);
    other.root_ = nullptr;
  }
  return *this;
}

template < typename Key, typename Value, typename Compare >
Value & redko::BSTree< Key, Value, Compare >::at(const Key & key)
{
  Node * curr = root_;
  while (curr != nullptr)
  {
    if (cmp_(curr->elem.first, key))
    {
      curr = curr->right;
    }
    else if (cmp_(key, curr->elem.first))
    {
      curr = curr->left;
    }
    else
    {
      return curr->elem.second;
    }
  }
  throw std::out_of_range("Error: no such element exists");
}

template < typename Key, typename Value, typename Compare >
const Value & redko::BSTree< Key, Value, Compare >::at(const Key & key) const
{
  Node * curr = root_;
  while (curr != nullptr)
  {
    if (cmp_(curr->elem.first, key))
    {
      curr = curr->right;
    }
    else if (cmp_(key, curr->elem.first))
    {
      curr = curr->left;
    }
    else
    {
      return curr->elem.second;
    }
  }
  throw std::out_of_range("Error: no such element exists");
}

template < typename Key, typename Value, typename Compare >
Value & redko::BSTree< Key, Value, Compare >::operator[](const Key & key)
{
  Node * curr = root_;
  while (curr != nullptr)
  {
    if (cmp_(curr->elem.first, key))
    {
      curr = curr->right;
    }
    else if (cmp_(key, curr->elem.first))
    {
      curr = curr->left;
    }
    else
    {
      return curr->elem.second;
    }
  }
  throw std::out_of_range("Error: no such element exists");
}

template < typename Key, typename Value, typename Compare >
Value & redko::BSTree< Key, Value, Compare >::operator[](Key && key)
{
  Node * curr = root_;
  while (curr != nullptr)
  {
    if (cmp_(curr->elem.first, key))
    {
      curr = curr->right;
    }
    else if (cmp_(key, curr->elem.first))
    {
      curr = curr->left;
    }
    else
    {
      return curr->elem.second;
    }
  }
  throw std::out_of_range("Error: no such element exists");
}

template < typename Key, typename Value, typename Compare >
bool redko::BSTree< Key, Value, Compare >::empty() const noexcept
{
  return (root_ == nullptr);
}

template < typename Key, typename Value, typename Compare >
size_t redko::BSTree< Key, Value, Compare >::size() const noexcept
{
  return getCountNode(root_);
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::iterator redko::BSTree< Key, Value, Compare >::begin() noexcept
{
  Node * curr = root_;
  while (curr != nullptr && curr->left != nullptr)
  {
    curr = curr->left;
  }
  return Iterator(curr, root_);
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::const_iterator redko::BSTree< Key, Value, Compare >::begin() const noexcept
{
  Node * curr = root_;
  while (curr != nullptr && curr->left != nullptr)
  {
    curr = curr->left;
  }
  return Iterator(curr, root_);
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::const_iterator redko::BSTree< Key, Value, Compare >::cbegin() const noexcept
{
  Node * curr = root_;
  while (curr != nullptr)
  {
    curr = curr->left;
  }
  return Iterator(curr, root_);
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::iterator redko::BSTree< Key, Value, Compare >::end() noexcept
{
  return Iterator(nullptr, root_);
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::const_iterator redko::BSTree< Key, Value, Compare >::end() const noexcept
{
  return Iterator(nullptr, root_);
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::const_iterator redko::BSTree< Key, Value, Compare >::cend() const noexcept
{
  return Iterator(nullptr, root_);
}

template < typename Key, typename Value, typename Compare >
void redko::BSTree< Key, Value, Compare >::clear()
{
  deleteSubtree(root_);
  root_ = nullptr;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::iterator redko::BSTree< Key, Value, Compare >::insert(const value_t & value)
{
  root_ = insertTo(root_, value);
  return find(value.first);
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::iterator redko::BSTree< Key, Value, Compare >::insert(value_t && value)
{
  root_ = insertTo(root_, std::move(value));
  return find(value.first);
}

template < typename Key, typename Value, typename Compare >
size_t redko::BSTree< Key, Value, Compare >::erase(const Key & key)
{
  if (find(key) != end())
  {
    root_ = deleteFrom(root_, key);
    return 1;
  }
  return 0;
}

template < typename Key, typename Value, typename Compare >
template< class... Args >
typename redko::BSTree< Key, Value, Compare >::iterator redko::BSTree< Key, Value, Compare >::emplace(Args &&... args)
{
  root_ = insertTo(root_, value_t(std::forward< Args >(args)...));
  return find(value_t(std::forward< Args >(args)...).first);
}

template < typename Key, typename Value, typename Compare >
void redko::BSTree< Key, Value, Compare >::swap(BSTree & other) noexcept
{
  Node * tmp = root_;
  root_ = other.root_;
  other.root_ = tmp;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::iterator redko::BSTree< Key, Value, Compare >::find(const Key & key)
{
  Node * curr = root_;
  while (curr != nullptr)
  {
    if (cmp_(curr->elem.first, key))
    {
      curr = curr->right;
    }
    else if (cmp_(key, curr->elem.first))
    {
      curr = curr->left;
    }
    else
    {
      return ConstIterator(Iterator(curr, root_));
    }
  }
  return end();
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::const_iterator redko::BSTree< Key, Value, Compare >::find(const Key & key) const
{
  Node * curr = root_;
  while (curr != nullptr)
  {
    if (cmp_(curr->elem.first, key))
    {
      curr = curr->right;
    }
    else if (cmp_(key, curr->elem.first))
    {
      curr = curr->left;
    }
    else
    {
      return ConstIterator(Iterator(curr, root_));
    }
  }
  return cend();
}

template < typename Key, typename Value, typename Compare >
using range = std::pair< iterator< Key, Value, Compare >, iterator< Key, Value, Compare > >;

template < typename Key, typename Value, typename Compare >
range< Key, Value, Compare > redko::BSTree< Key, Value, Compare >::equalRange(const Key & key)
{
  return { lowerBound(), upperBound() };
}

template < typename Key, typename Value, typename Compare >
using const_range = std::pair< const_iterator< Key, Value, Compare >, const_iterator< Key, Value, Compare > >;

template < typename Key, typename Value, typename Compare >
const_range< Key, Value, Compare > redko::BSTree< Key, Value, Compare >::equalRange(const Key & key) const
{
  return { lowerBound(), upperBound() };
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::iterator redko::BSTree< Key, Value, Compare >::lowerBound(const Key & key)
{
  for (iterator curr = begin(); curr != end(); ++curr)
  {
    if (!cmp_(curr->first, key))
    {
      return curr;
    }
  }
  return end();
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::const_iterator redko::BSTree< Key, Value, Compare >::lowerBound(const Key & key) const
{
  for (const_iterator curr = cbegin(); curr != cend(); ++curr)
  {
    if (!cmp_(curr->first, key))
    {
      return curr;
    }
  }
  return cend();
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::iterator redko::BSTree< Key, Value, Compare >::upperBound(const Key & key)
{
  for (iterator curr = begin(); curr != end(); ++curr)
  {
    if (cmp_(key, curr->first))
    {
      return curr;
    }
  }
  return end();
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::const_iterator redko::BSTree< Key, Value, Compare >::upperBound(const Key & key) const
{
  for (const_iterator curr = cbegin(); curr != cend(); ++curr)
  {
    if (cmp_(key, curr->first))
    {
      return curr;
    }
  }
  return cend();
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F redko::BSTree< Key, Value, Compare >::ctraverseLR(F func) const
{
  Stack< Node * > stack;
  Node * curr = root_;
  while (curr != nullptr || !stack.empty())
  {
    while (curr != nullptr)
    {
      stack.push(curr);
      curr = curr->left;
    }
    curr = stack.top();
    stack.pop();
    func(curr->elem);
    curr = curr->right;
  }
  return func;
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F redko::BSTree< Key, Value, Compare >::traverseLR(F func)
{
  Stack< Node * > stack;
  Node * curr = root_;
  while (curr != nullptr || !stack.empty())
  {
    while (curr != nullptr)
    {
      stack.push(curr);
      curr = curr->left;
    }
    curr = stack.top();
    stack.pop();
    func(curr->elem);
    curr = curr->right;
  }
  return func;
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F redko::BSTree< Key, Value, Compare >::ctraverseRL(F func) const
{
  Stack< Node * > stack;
  Node * curr = root_;
  while (curr != nullptr || !stack.empty())
  {
    while (curr != nullptr)
    {
      stack.push(curr);
      curr = curr->right;
    }
    curr = stack.top();
    stack.pop();
    func(curr->elem);
    curr = curr->left;
  }
  return func;
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F redko::BSTree< Key, Value, Compare >::traverseRL(F func)
{
  Stack< Node * > stack;
  Node * curr = root_;
  while (curr != nullptr || !stack.empty())
  {
    while (curr != nullptr)
    {
      stack.push(curr);
      curr = curr->right;
    }
    curr = stack.top();
    stack.pop();
    func(curr->elem);
    curr = curr->left;
  }
  return func;
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F redko::BSTree< Key, Value, Compare >::ctraverseBreadth(F func) const
{
  if (empty())
  {
     return func;
  }
  Queue< Node * > queue;
  queue.push(root_);

  while (!queue.empty())
  {
    Node * node = queue.front();
    func(node->elem);
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
F redko::BSTree< Key, Value, Compare >::traverseBreadth(F func)
{
  if (empty())
  {
     return func;
  }
  Queue< Node * > queue;
  queue.push(root_);

  while (!queue.empty())
  {
    Node * node = queue.front();
    func(node->elem);
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
void redko::BSTree< Key, Value, Compare >::deleteSubtree(Node * root)
{
  if (root != nullptr)
  {
    deleteSubtree(root->left);
    deleteSubtree(root->right);
    delete root;
    root = nullptr;
  }
}

template < typename Key, typename Value, typename Compare >
size_t redko::BSTree< Key, Value, Compare >::getCountNode(Node * root) const
{
  if (root == nullptr)
  {
    return 0;
  }
  return (1 + getCountNode(root->left) + getCountNode(root->right));
}

template < typename Key, typename Value, typename Compare >
size_t redko::BSTree< Key, Value, Compare >::getHeight(Node * node)
{
  size_t height = 0;
  if (node != nullptr)
  {
    size_t lHeight = getHeight(node->left);
    size_t rHeight = getHeight(node->right);
    height = std::max(lHeight, rHeight) + 1;
  }
  return height;
}

template < typename Key, typename Value, typename Compare >
int redko::BSTree< Key, Value, Compare >::getDiff(Node * node)
{
  if (node == nullptr)
  {
    return 0;
  }
  return getHeight(node->left) - getHeight(node->right);
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::Node * redko::BSTree< Key, Value, Compare >::rotateLL(Node * node)
{
  Node * tmp = node->right;
  Node * parent = node->parent;
  node->right = tmp->left;
  if (node->right != nullptr)
  {
    node->right->parent = node;
  }
  tmp->left = node;
  tmp->left->parent = tmp;
  tmp->parent = parent;
  return tmp;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::Node * redko::BSTree< Key, Value, Compare >::rotateRR(Node * node)
{
  Node * tmp = node->left;
  Node * parent = node->parent;
  node->left = tmp->right;
  if (node->left != nullptr)
  {
    node->left->parent = node;
  }
  tmp->right = node;
  tmp->right->parent = tmp;
  tmp->parent = parent;
  return tmp;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::Node * redko::BSTree< Key, Value, Compare >::rotateRL(Node * node)
{
  node->right = rotateRR(node->right);
  return rotateLL(node);
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::Node * redko::BSTree< Key, Value, Compare >::rotateLR(Node * node)
{
  node->left = rotateLL(node->left);
  return rotateRR(node);
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::Node * redko::BSTree< Key, Value, Compare >::insertTo(Node * node, const value_t & value)
{
  if (node == nullptr)
  {
    node = new Node(value);
    return node;
  }
  else
  {
    if (cmp_(value.first, node->elem.first))
    {
      node->left = insertTo(node->left, value);
      node->left->parent = node;
    }
    else if (cmp_(node->elem.first, value.first))
    {
      node->right = insertTo(node->right, value);
      node->right->parent = node;
    }
  }

  int bFactor = getDiff(node);
  if (bFactor == 2)
  {
    if (getDiff(node->left) > 0)
    {
      node = rotateRR(node);
    }
    else
    {
      node = rotateLR(node);
    }
  }
  else if (bFactor == -2)
  {
    if (getDiff(node->right) > 0)
    {
      node = rotateRL(node);
    }
    else
    {
      node = rotateLL(node);
    }
  }
  return node;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::Node * redko::BSTree< Key, Value, Compare >::insertTo(Node * node, value_t && value)
{
  if (node == nullptr)
  {
    node = new Node(std::move(value));
    return node;
  }
  else
  {
    if (cmp_(value.first, node->elem.first))
    {
      node->left = insertTo(node->left, std::move(value));
      node->left->parent = node;
    }
    else if (cmp_(node->elem.first, value.first))
    {
      node->right = insertTo(node->right, std::move(value));
      node->right->parent = node;
    }
  }

  int bFactor = getDiff(node);
  if (bFactor == 2)
  {
    if (getDiff(node->left) > 0)
    {
      node = rotateRR(node);
    }
    else
    {
      node = rotateLR(node);
    }
  }
  else if (bFactor == -2)
  {
    if (getDiff(node->right) > 0)
    {
      node = rotateRL(node);
    }
    else
    {
      node = rotateLL(node);
    }
  }
  return node;
}

template < typename Key, typename Value, typename Compare >
typename redko::BSTree< Key, Value, Compare >::Node * redko::BSTree< Key, Value, Compare >::deleteFrom(Node * node, const Key & key)
{
  if (node == nullptr)
  {
    return node;
  }

  if (cmp_(key, node->elem.first))
  {
    node->left = deleteFrom(node->left, key);
  }
  else if (cmp_(node->elem.first, key))
  {
    node->right = deleteFrom(node->right, key);
  }
  else
  {
    Node * tmp = nullptr;
    if (node->left == nullptr && node->right == nullptr)
    {
      delete node;
      return nullptr;
    }
    else if (node->right == nullptr)
    {
      tmp = node->left;
      *node = *tmp;
      delete tmp;
    }
    else if (node->left == nullptr)
    {
      tmp = node->right;
      *node = *tmp;
      delete tmp;
    }
    else
    {
      tmp = node->right;
      while (tmp->left != nullptr)
      {
        tmp = tmp->left;
      }
      node->elem = tmp->elem;
      node->right = deleteFrom(node->right, tmp->elem.first);
    }
  }

  int bFactor = getDiff(node);
  if (bFactor == 2)
  {
    if (getDiff(node->left) >= 0)
    {
      node = rotateRR(node);
    }
    else
    {
      node = rotateLR(node);
    }
  }
  else if (bFactor == -2)
  {
    if (getDiff(node->right) <= 0)
    {
      node = rotateLL(node);
    }
    else
    {
      node = rotateRL(node);
    }
  }
  return node;
}

#endif
