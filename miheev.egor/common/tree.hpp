#ifndef TREE_HPP
#define TREE_HPP

#include <utility>
#include <cstddef>
#include <iostream>
#include <functional>
#include <stack.hpp>
#include <queue.hpp>

namespace miheev
{
  template< typename Key, typename Value, typename Comparator = std::less< Key > >
  class Tree
  {
  public:
    using kv_pair = std::pair< Key, Value >;
    class LnRIterator;
    class RnLIterator;
    class Iterator;
    class ConstIterator;

    using iter_pair = std::pair< Iterator, Iterator >;
    using const_iter_pair = std::pair< ConstIterator, ConstIterator >;

    Tree();
    Tree(const Key& key, const Value& value);
    Tree(const Tree&);
    ~Tree();

    Tree& operator=(const Tree&);

    void printKeys(std::ostream& = std::cout) const;
    void printValues(std::ostream& = std::cout) const;

    Value& operator[](const Key&);
    const Value& operator[](const Key&) const;
    Value& at(const Key&);
    const Value& at (const Key&) const;

    size_t size() const;
    bool empty() const noexcept;

    void insert(const Key&, const Value&);
    void insert(const std::pair< Key, Value >& pair);
    void erase(const Key&);
    void erase(Iterator);
    void erase(ConstIterator);
    void clear();
    void swap(Tree&);

    Iterator find(const Key&);
    ConstIterator find(const Key&) const;
    bool contains(const Key&) const;
    std::pair< Iterator, Iterator > equalRange(const Key&);
    std::pair< ConstIterator, ConstIterator > equalRange(const Key&) const;

    template < typename PairPred >
    PairPred ctraverseLnR(PairPred) const;
    template < typename PairPred >
    PairPred ctraverseRnL(PairPred) const;
    template < typename PairPred >
    PairPred traverseLnR(PairPred);
    template < typename PairPred >
    PairPred traverseRnL(PairPred);
    template < typename PairPred >
    PairPred ctraverseBreadth(PairPred) const;
    template < typename PairPred >
    PairPred traverseBreadth(PairPred);

    Iterator begin();
    Iterator end();
    ConstIterator cbegin() const;
    ConstIterator cend() const;

  private:
    kv_pair* pair_;

    size_t height_;
    bool isEmpty_;

    Tree* left_;
    Tree* right_;

    Tree* parrent_;

    Tree* findNextNode(const Key&) const;

    size_t getHeight() const;
    void rebalanceSelf();
    bool isBalanced() const;
    int getDiff() const;
    void swapNodes(Tree*, Tree*);
    void updateHeight();
    void updateParrentsLocally();

    Tree* getMaxNode();
    const Tree* getMaxNode() const;
    Tree* getMinNode();
    const Tree* getMinNode() const;
    Tree* getRoot();
    const Tree* getRoot() const;

    void safeInsert(const Key&, const Value&, Tree* ptr);
    void rawInsert(const Key&, const Value&);
    void rawDelete(const Key&);
    void rawDeleteSelf();

    void replacePair(const kv_pair&);

    void rotateRR();
    void rotateLL();
  };
}

template< typename Key, typename Value, typename Comparator >
class miheev::Tree< Key, Value, Comparator >::Iterator
{
public:
  Iterator();
  Iterator(Tree*);
  explicit Iterator(LnRIterator);
  explicit Iterator(RnLIterator);
  Iterator(const Iterator&) = default;
  ~Iterator() = default;

  Iterator& operator=(const Iterator&) = default;
  Iterator& operator++();
  Iterator operator++(int);
  Iterator& operator--();
  Iterator operator--(int);

  kv_pair& operator*() const;
  kv_pair* operator->() const;

  bool operator!=(const Iterator&) const;
  bool operator==(const Iterator&) const;

private:
  friend class Tree;
  Tree* cur_;
  Tree* max_;

  Iterator(Tree* cur, Tree* max);
  void erase();

  bool weAreOnRight();
};

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >::Iterator::Iterator():
  cur_(nullptr),
  max_(nullptr)
{}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >::Iterator::Iterator(Tree* init):
  cur_(init),
  max_(nullptr)
{
  if (!init)
  {
    return;
  }
  Tree* top = init;
  if (!weAreOnRight())
  {
    while (top->parrent_)
    {
      top = top->parrent_;
    }
  }
  max_ = top->getMaxNode();
}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >::Iterator::Iterator(LnRIterator rhs)
{
  *this = Iterator(rhs.cur_);
}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >::Iterator::Iterator(RnLIterator rhs)
{
  *this = Iterator(rhs.cur_);
}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >::Iterator::Iterator(Tree* init, Tree* max):
  cur_(init),
  max_(max)
{}

template< typename Key, typename Value, typename Comparator >
bool miheev::Tree< Key, Value, Comparator >::Iterator::weAreOnRight()
{
  Comparator comparator;
  if (!cur_->parrent_)
  {
    return false;
  }
  return comparator(cur_->parrent_->pair_->first, cur_->pair_->first);
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::Iterator& miheev::Tree< Key, Value, Comparator >::Iterator::operator++()
{
  if (!cur_)
  {
    throw std::out_of_range("iterator is out of range");
  }
  if (cur_->right_)
  {
    cur_ = cur_->right_->getMinNode();
  }
  else
  {
    while (cur_->parrent_ && weAreOnRight())
    {
      cur_ = cur_->parrent_;
    }
    cur_ = cur_->parrent_;
  }
  return *this;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::Iterator miheev::Tree< Key, Value, Comparator >::Iterator::operator++(int)
{
  Iterator iter(*this);
  ++(*this);
  return iter;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::Iterator& miheev::Tree< Key, Value, Comparator >::Iterator::operator--()
{
  if (!cur_)
  {
    cur_ = max_;
  }
  else if (cur_->left_)
  {
    cur_ = cur_->left_->getMaxNode();
  }
  else
  {
    while (cur_->parrent_ && !weAreOnRight())
    {
      cur_ = cur_->parrent_;
    }
    if (cur_->parrent_)
    {
      cur_ = cur_->parrent_;
    }
  }
  return *this;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::Iterator miheev::Tree< Key, Value, Comparator >::Iterator::operator--(int)
{
  Iterator iter(*this);
  --(*this);
  return iter;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::kv_pair& miheev::Tree< Key, Value, Comparator >::Iterator::operator*() const
{
  if (!cur_)
  {
    throw std::out_of_range("dereferencing end ptr");
  }
  return *cur_->pair_;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::kv_pair* miheev::Tree< Key, Value, Comparator >::Iterator::operator->() const
{
  if (!cur_)
  {
    throw std::out_of_range("dereferencing end ptr");
  }
  return std::addressof(*cur_->pair_);
}

template< typename Key, typename Value, typename Comparator >
bool miheev::Tree< Key, Value, Comparator >::Iterator::operator==(const Iterator& rhs) const
{
  return cur_ == rhs.cur_;
}

template< typename Key, typename Value, typename Comparator >
bool miheev::Tree< Key, Value, Comparator >::Iterator::operator!=(const Iterator& rhs) const
{
  return !(*this == rhs);
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator >::Iterator::erase()
{
  Tree* top = cur_->getRoot();
  cur_->rawDeleteSelf();
  top->rebalanceSelf();
  max_ = top->getMaxNode();
}

template< typename Key, typename Value, typename Comparator >
class miheev::Tree< Key, Value, Comparator >::ConstIterator
{
public:

  ConstIterator();
  ConstIterator(Iterator);
  explicit ConstIterator(LnRIterator);
  explicit ConstIterator(RnLIterator);
  ConstIterator(const ConstIterator&) = default;
  ~ConstIterator() = default;

  ConstIterator& operator=(const ConstIterator&) = default;
  ConstIterator& operator++();
  ConstIterator operator++(int);
  ConstIterator& operator--();
  ConstIterator operator--(int);

  const kv_pair& operator*() const;
  const kv_pair* operator->() const;

  bool operator!=(const ConstIterator&) const;
  bool operator==(const ConstIterator&) const;

private:
  Iterator iter_;
  void erase();
};

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >::ConstIterator::ConstIterator():
  iter_(Iterator())
{}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >::ConstIterator::ConstIterator(Iterator iter):
  iter_(iter)
{}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >::ConstIterator::ConstIterator(LnRIterator rhs):
  iter_(Iterator(rhs.cur_))
{}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >::ConstIterator::ConstIterator(RnLIterator rhs):
  iter_(Iterator(rhs.cur_))
{}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::ConstIterator& miheev::Tree< Key, Value, Comparator >::ConstIterator::operator++()
{
  ++iter_;
  return *this;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::ConstIterator miheev::Tree< Key, Value, Comparator >::ConstIterator::operator++(int)
{
  return iter_++;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::ConstIterator& miheev::Tree< Key, Value, Comparator >::ConstIterator::operator--()
{
  return --iter_;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::ConstIterator miheev::Tree< Key, Value, Comparator >::ConstIterator::operator--(int)
{
  return iter_--;
}

template< typename Key, typename Value, typename Comparator >
bool miheev::Tree< Key, Value, Comparator >::ConstIterator::operator==(const ConstIterator& rhs) const
{
  return this->iter_ == rhs.iter_;
}

template< typename Key, typename Value, typename Comparator >
bool miheev::Tree< Key, Value, Comparator >::ConstIterator::operator!=(const ConstIterator& rhs) const
{
  return this->iter_ != rhs.iter_;
}

template< typename Key, typename Value, typename Comparator >
const typename miheev::Tree< Key, Value, Comparator >::kv_pair& miheev::Tree< Key, Value, Comparator >::ConstIterator::operator*() const
{
  return *iter_;
}

template< typename Key, typename Value, typename Comparator >
const typename miheev::Tree< Key, Value, Comparator >::kv_pair* miheev::Tree< Key, Value, Comparator >::ConstIterator::operator->() const
{
  return std::addressof(*iter_);
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator >::ConstIterator::erase()
{
  iter_->erase();
}

template< typename Key, typename Value, typename Comparator >
class miheev::Tree< Key, Value, Comparator >::LnRIterator
{
public:
  LnRIterator();
  explicit LnRIterator(Tree* ptr);
  LnRIterator(const LnRIterator&) = default;
  ~LnRIterator() = default;

  LnRIterator& operator=(const LnRIterator&) = default;
  LnRIterator& operator++();
  LnRIterator operator++(int);

  kv_pair& operator*();
  kv_pair* operator->();
  const kv_pair& operator*() const;
  const kv_pair* operator->() const;

  bool operator!=(const LnRIterator&) const;
  bool operator==(const LnRIterator&) const;

private:
  Tree* cur_;
  Tree* temp_;
  Stack< Tree* > stack_;

  void goDownLeft();
  void dropToCurFromStack();
};

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >::LnRIterator::LnRIterator():
  cur_(nullptr),
  temp_(nullptr),
  stack_(Stack< Tree* >())
{}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >::LnRIterator::LnRIterator(Tree* ptr):
  cur_(ptr),
  temp_(nullptr),
  stack_(Stack< Tree* >())
{
  goDownLeft();
  dropToCurFromStack();
  temp_ = cur_->right_;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::LnRIterator& miheev::Tree< Key, Value, Comparator >::LnRIterator::operator++()
{
  if (!cur_ && stack_.empty())
  {
    throw std::runtime_error("LnR iterator already reached the end of the tree");
  }
  cur_ = temp_;
  goDownLeft();
  dropToCurFromStack();
  temp_ = cur_->right_;
  return *this;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::LnRIterator miheev::Tree< Key, Value, Comparator >::LnRIterator::operator++(int)
{
  LnRIterator temp = *this;
  (*this)++;
  return temp;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::kv_pair& miheev::Tree< Key, Value, Comparator >::LnRIterator::operator*()
{
  return *cur_->pair_;
}

template< typename Key, typename Value, typename Comparator >
const typename miheev::Tree< Key, Value, Comparator >::kv_pair& miheev::Tree< Key, Value, Comparator >::LnRIterator::operator*() const
{
  return *cur_->pair_;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::kv_pair* miheev::Tree< Key, Value, Comparator >::LnRIterator::operator->()
{
  return std::addressof(*cur_->pair_);
}

template< typename Key, typename Value, typename Comparator >
const typename miheev::Tree< Key, Value, Comparator >::kv_pair* miheev::Tree< Key, Value, Comparator >::LnRIterator::operator->() const
{
  return std::addressof(*cur_->pair_);
}

template< typename Key, typename Value, typename Comparator >
bool miheev::Tree< Key, Value, Comparator >::LnRIterator::operator!=(const LnRIterator& rhs) const
{
  return cur_ != rhs.cur_;
}

template< typename Key, typename Value, typename Comparator >
bool miheev::Tree< Key, Value, Comparator >::LnRIterator::operator==(const LnRIterator& rhs) const
{
  return cur_ == rhs.cur_;
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator >::LnRIterator::goDownLeft()
{
  while (cur_)
  {
    stack_.push(cur_);
    cur_ = cur_->left_;
  }
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator >::LnRIterator::dropToCurFromStack()
{
  cur_ = stack_.top();
  stack_.pop();
}

template< typename Key, typename Value, typename Comparator >
class miheev::Tree< Key, Value, Comparator >::RnLIterator
{
public:
  RnLIterator();
  explicit RnLIterator(Tree* ptr);
  RnLIterator(const RnLIterator&) = default;
  ~RnLIterator() = default;

  RnLIterator& operator=(const RnLIterator&) = default;
  RnLIterator& operator++();
  RnLIterator operator++(int);

  kv_pair& operator*();
  kv_pair* operator->();
  const kv_pair& operator*() const;
  const kv_pair* operator->() const;

  bool operator!=(const RnLIterator&) const;
  bool operator==(const RnLIterator&) const;

private:
  Tree* cur_;
  Tree* temp_;
  Stack< Tree* > stack_;

  void goDownRight();
  void dropToCurFromStack();

  friend class Iterator;
  friend class ConstIterator;
};

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >::RnLIterator::RnLIterator():
  cur_(nullptr),
  temp_(nullptr),
  stack_(Stack< Tree* >())
{}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >::RnLIterator::RnLIterator(Tree* ptr):
  cur_(ptr),
  temp_(nullptr),
  stack_(Stack< Tree* >())
{
  goDownRight();
  dropToCurFromStack();
  temp_ = cur_->left_;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::RnLIterator& miheev::Tree< Key, Value, Comparator >::RnLIterator::operator++()
{
  if (!cur_ && stack_.empty())
  {
    throw std::runtime_error("RnL iterator already reached the end of the tree");
  }
  cur_ = temp_;
  goDownRight();
  dropToCurFromStack();
  temp_ = cur_->left_;
  return *this;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::RnLIterator miheev::Tree< Key, Value, Comparator >::RnLIterator::operator++(int)
{
  RnLIterator temp = *this;
  (*this)++;
  return temp;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::kv_pair& miheev::Tree< Key, Value, Comparator >::RnLIterator::operator*()
{
  return *cur_->pair_;
}

template< typename Key, typename Value, typename Comparator >
const typename miheev::Tree< Key, Value, Comparator >::kv_pair& miheev::Tree< Key, Value, Comparator >::RnLIterator::operator*() const
{
  return *cur_->pair_;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::kv_pair* miheev::Tree< Key, Value, Comparator >::RnLIterator::operator->()
{
  return std::addressof(*cur_->pair_);
}

template< typename Key, typename Value, typename Comparator >
const typename miheev::Tree< Key, Value, Comparator >::kv_pair* miheev::Tree< Key, Value, Comparator >::RnLIterator::operator->() const
{
  return std::addressof(*cur_->pair_);
}

template< typename Key, typename Value, typename Comparator >
bool miheev::Tree< Key, Value, Comparator >::RnLIterator::operator!=(const RnLIterator& rhs) const
{
  return cur_ != rhs.cur_;
}

template< typename Key, typename Value, typename Comparator >
bool miheev::Tree< Key, Value, Comparator >::RnLIterator::operator==(const RnLIterator& rhs) const
{
  return cur_ == rhs.cur_;
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator >::RnLIterator::goDownRight()
{
  while (cur_)
  {
    stack_.push(cur_);
    cur_ = cur_->right_;
  }
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator >::RnLIterator::dropToCurFromStack()
{
  cur_ = stack_.top();
  stack_.pop();
}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >::~Tree()
{
  clear();
}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator>::Tree():
  pair_(nullptr),
  height_(0),
  isEmpty_(true),
  left_(nullptr),
  right_(nullptr),
  parrent_(nullptr)
{}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator>::Tree(const Key& key, const Value& value):
  pair_(new kv_pair(key, value)),
  height_(1),
  isEmpty_(false),
  left_(nullptr),
  right_(nullptr),
  parrent_(nullptr)
{}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator>::Tree(const miheev::Tree< Key, Value, Comparator >& rhs):
  pair_(nullptr),
  height_(rhs.height_),
  isEmpty_(rhs.isEmpty_),
  left_(nullptr),
  right_(nullptr),
  parrent_(nullptr)
{
  pair_ = rhs.pair_ ? new kv_pair(*rhs.pair_) : nullptr;
  if (rhs.left_)
  {
    left_ = new Tree(*rhs.left_);
  }
  if (rhs.right_)
  {
    right_ = new Tree(*rhs.right_);
  }
  updateParrentsLocally();
}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >& miheev::Tree< Key, Value, Comparator>::operator=(const miheev::Tree< Key, Value, Comparator >& rhs)
{
  clear();
  pair_ = rhs.pair_ ? new kv_pair(*rhs.pair_) : nullptr;
  height_ = rhs.height_;
  isEmpty_ = rhs.isEmpty_;
  if (rhs.left_)
  {
    left_ = new Tree(*rhs.left_);
  }
  if (rhs.right_)
  {
    right_ = new Tree(*rhs.right_);
  }
  updateParrentsLocally();
  return *this;
}

template< typename Key, typename Value, typename Comparator >
Value& miheev::Tree< Key, Value, Comparator>::at(const Key& key)
{
  Comparator comparator;
  if (key == pair_->first)
  {
    return pair_->second;
  }
  if (comparator(pair_->first, key))
  {
    if (!right_)
    {
      throw std::out_of_range("No key");
    }
    return right_->at(key);
  }
  else
  {
    if (!left_)
    {
      throw std::out_of_range("No key");
    }
    return left_->at(key);
  }
}

template< typename Key, typename Value, typename Comparator >
const Value& miheev::Tree< Key, Value, Comparator>::at(const Key& key) const
{
  Comparator comparator;
  if (key == pair_->first)
  {
    return pair_->second;
  }
  if (comparator(pair_->first, key))
  {
    if (!right_)
    {
      throw std::out_of_range("No key");
    }
    return right_->at(key);
  }
  else
  {
    if (!left_)
    {
      throw std::out_of_range("No key");
    }
    return left_->at(key);
  }
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::clear()
{
  if (left_)
  {
    delete left_;
    left_ = nullptr;
  }
  if (right_)
  {
    delete right_;
    right_ = nullptr;
  }
  kv_pair* temp = pair_;
  pair_ = nullptr;
  delete temp;
  parrent_ = nullptr;
  isEmpty_ = true;
  height_ = 0;
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::insert(const Key& key, const Value& value)
{
  rawInsert(key, value);
  updateHeight();
  updateParrentsLocally();
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::insert(const std::pair< Key, Value >& pair)
{
  insert(pair.first, pair.second);
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::swap(Tree& tree)
{
  Tree temp = tree;
  temp = *this;
  *this = temp;
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::printKeys(std::ostream& out) const
{
  if (isEmpty_)
  {
    return;
  }
  if (left_)
  left_->printKeys(out);
  out << pair_->first << ' ';
  if (right_)
  right_->printKeys(out);
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::printValues(std::ostream& out) const
{
  if (isEmpty_)
  {
    return;
  }
  if (left_)
  left_->printValues(out);
  out << pair_->second << ' ';
  if (right_)
  right_->printValues(out);
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::rawInsert(const Key& key, const Value& value)
{
  Comparator comparator;
  if (isEmpty_)
  {
    Tree temp(key, value);
    *this = temp;
    return;
  }
  if(comparator(key, pair_->first))
  {
    if (left_)
    {
      left_->rawInsert(key, value);
    }
    else
    {
      left_ = new Tree(key, value);
    }
  }
  else
  {
    if (right_)
    {
      right_->rawInsert(key, value);
    }
    else
    {
      right_ = new Tree(key, value);
    }
  }
  updateHeight();
  rebalanceSelf();
  updateParrentsLocally();
}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >* miheev::Tree< Key, Value, Comparator>::getMaxNode()
{
  return right_ ? right_->getMaxNode() : this;
}

template< typename Key, typename Value, typename Comparator >
const miheev::Tree< Key, Value, Comparator >* miheev::Tree< Key, Value, Comparator>::getMaxNode() const
{
  return right_ ? right_->getMaxNode() : this;
}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >* miheev::Tree< Key, Value, Comparator>::getMinNode()
{
  return left_ ? left_->getMinNode() : this;
}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >* miheev::Tree< Key, Value, Comparator>::getRoot()
{
  Tree* temp = this;
  while (temp->parrent_)
  {
    temp = temp->parrent_;
  }
  return temp;
}

template< typename Key, typename Value, typename Comparator >
const miheev::Tree< Key, Value, Comparator >* miheev::Tree< Key, Value, Comparator>::getRoot() const
{
  Tree* temp = this;
  while (temp->parrent_)
  {
    temp = temp->parrent_;
  }
  return temp;
}

template< typename Key, typename Value, typename Comparator >
const miheev::Tree< Key, Value, Comparator >* miheev::Tree< Key, Value, Comparator>::getMinNode() const
{
  return left_ ? left_->getMinNode() : this;
}

template< typename Key, typename Value, typename Comparator >
bool miheev::Tree< Key, Value, Comparator>::empty() const noexcept
{
  return isEmpty_;
}

template< typename Key, typename Value, typename Comparator >
size_t miheev::Tree< Key, Value, Comparator>::size() const
{
  size_t leftSize = left_ ? left_->size() : 0;
  size_t rightSize = right_ ? right_->size() : 0;
  return leftSize + rightSize + 1;
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::erase(const Key& key)
{
  rawDelete(key);
  updateHeight();
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator >::erase(Iterator iter)
{
  iter->erase();
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator >::erase(ConstIterator citer)
{
  citer->erase();
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::rawDelete(const Key& key)
{
  Comparator comparator;
  if (isEmpty_)
  {
    return;
  }
  if (key == pair_->first)
  {
    rawDeleteSelf();
  }
  else
  {
    if (comparator(key, pair_->first) && left_)
    {
      left_->rawDelete(key);
      if (left_->empty())
      {
        Tree* temp = left_;
        left_ = nullptr;
        delete temp;
      }
    }
    else if (!comparator(key, pair_->first) && right_)
    {
      right_->rawDelete(key);
      if (right_->empty())
      {
        Tree* temp = right_;
        right_ = nullptr;
        delete temp;
      }
    }
  }
  updateHeight();
  rebalanceSelf();
  updateParrentsLocally();
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::rawDeleteSelf()
{
  if (!left_ && !right_)
  {
    clear();
  }
  else if (!left_ && right_)
  {
    Tree temp = *right_;
    *this = temp;
  }
  else if (left_ && !right_)
  {
    Tree temp = *left_;
    *this = temp;
  }
  else
  {
    Tree temp = *right_->getMinNode();
    rawDelete(temp.pair_->first);
    replacePair(*temp.pair_);
  }
  updateParrentsLocally();
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::rebalanceSelf()
{
  if (left_)
  {
    left_->rebalanceSelf();
  }
  if (right_)
  {
    right_->rebalanceSelf();
  }
  int diff = getDiff();
  if (diff == -2)
  {
    if (left_->getDiff() == 1)
    {
      left_->rotateLL();
    }
    rotateRR();
  }
  else if (diff == 2)
  {
    if (right_->getDiff() == -1)
    {
      right_->rotateRR();
    }
    rotateLL();
  }
  updateParrentsLocally();
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::updateParrentsLocally()
{
  if (left_)
  {
    left_->parrent_ = this;
  }
  if (right_)
  {
    right_->parrent_ = this;
  }
}

template< typename Key, typename Value, typename Comparator >
miheev::Tree< Key, Value, Comparator >* miheev::Tree< Key, Value, Comparator>::findNextNode(const Key& key) const
{
  Comparator comparator;
  if (comparator(pair_->first, key))
  {
    return right_;
  }
  else
  {
    return left_;
  }
}

template< typename Key, typename Value, typename Comparator >
size_t miheev::Tree< Key, Value, Comparator>::getHeight() const
{
  return height_;
}

template< typename Key, typename Value, typename Comparator >
int miheev::Tree< Key, Value, Comparator>::getDiff() const
{
  int leftHeight = left_ ? left_->getHeight() : 0;
  int rightHeight = right_ ? right_->getHeight() : 0;
  return rightHeight - leftHeight;
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::updateHeight()
{
  size_t leftHeight = left_ ? left_->getHeight() : 0;
  size_t rightHeight = right_ ? right_->getHeight() : 0;
  height_ = std::max(leftHeight, rightHeight) + 1;
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::swapNodes(Tree* lhs, Tree* rhs)
{
  kv_pair temp = kv_pair(*lhs->pair_);
  lhs->replacePair(*rhs->pair_);
  rhs->replacePair(temp);
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::rotateRR()
{
  swapNodes(left_, this);
  Tree* buff = right_;
  right_ = left_;
  left_ = right_->left_;
  right_->left_ = right_->right_;
  right_->right_ = buff;
  right_->updateHeight();
  updateHeight();
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator>::rotateLL()
{
  swapNodes(right_, this);
  Tree* buff = left_;
  left_ = right_;
  right_ = left_->right_;
  left_->right_ = left_->left_;
  left_->left_ = buff;
  left_->updateHeight();
  updateHeight();
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::Iterator miheev::Tree< Key, Value, Comparator >::begin()
{
  return getMinNode();
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::Iterator miheev::Tree< Key, Value, Comparator >::end()
{
  return Iterator(nullptr, getMaxNode());
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::Iterator miheev::Tree< Key, Value, Comparator >::find(const Key& key)
{
  if (isEmpty_)
  {
    throw std::out_of_range("Searching in empty tree");
  }
  if (key == pair_->first)
  {
    return this;
  }
  Tree* next = findNextNode(key);
  if (next)
  {
    return next->find(key);
  }
  else
  {
    throw std::out_of_range("No such key in list");
  }
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::ConstIterator miheev::Tree< Key, Value, Comparator >::find(const Key& key) const
{
  if (isEmpty_)
  {
    throw std::out_of_range("Searching in empty tree");
  }
  if (key == pair_->first)
  {
    return Iterator(const_cast< Tree* >(this));
  }
  Tree* next = findNextNode(key);
  if (next)
  {
    return next->find(key);
  }
  else
  {
    throw std::out_of_range("No such key in list");
  }
}

template< typename Key, typename Value, typename Comparator >
bool miheev::Tree< Key, Value, Comparator >::contains(const Key& key) const
{
  if (isEmpty_)
  {
    return false;
  }
  if (key == pair_->first)
  {
    return true;
  }
  const Tree* next = findNextNode(key);
  if (next)
  {
    return next->contains(key);
  }
  else
  {
    return false;
  }
}

template< typename Key, typename Value, typename Comparator >
Value& miheev::Tree< Key, Value, Comparator >::operator[](const Key& key)
{
  try
  {
    return find(key)->second;
  }
  catch (const std::out_of_range&)
  {
    insert(key, Value());
    return find(key)->second;
  }
}

template< typename Key, typename Value, typename Comparator >
const Value& miheev::Tree< Key, Value, Comparator >::operator[](const Key& key) const
{
  try
  {
    return find(key)->second;
  }
  catch (const std::out_of_range&)
  {
    return Value();
  }
}

template< typename Key, typename Value, typename Comparator >
void miheev::Tree< Key, Value, Comparator >::replacePair(const kv_pair& substitution)
{
  kv_pair* temp = pair_;
  pair_ = new kv_pair(substitution);
  delete temp;
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::ConstIterator miheev::Tree< Key, Value, Comparator >::cbegin() const
{
  return isEmpty_ ? Iterator (nullptr) : Iterator(const_cast< Tree* >(getMinNode()));
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::ConstIterator miheev::Tree< Key, Value, Comparator >::cend() const
{
  return Iterator(nullptr, const_cast< Tree* >(getMaxNode()));
}


template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::iter_pair miheev::Tree< Key, Value, Comparator >::equalRange(const Key& key)
{
  Iterator start = find(key);
  Iterator end = start;
  for (; end->first == key; end++)
  {}
  return iter_pair(start, end);
}

template< typename Key, typename Value, typename Comparator >
typename miheev::Tree< Key, Value, Comparator >::const_iter_pair miheev::Tree< Key, Value, Comparator >::equalRange(const Key& key) const
{
  ConstIterator start = find(key);
  ConstIterator end = start;
  for (; end->first == key; end++)
  {}
  return const_iter_pair(start, end);
}

template< typename Key, typename Value, typename Comparator >
template< typename PairPred >
PairPred miheev::Tree< Key, Value, Comparator >::ctraverseLnR(PairPred p) const
{
  Stack< const Tree* > stack;
  const Tree* current = this;
  while (current || !stack.empty())
  {
    while (current)
    {
      stack.push(current);
      current = current->left_;
    }
    current = stack.top();
    stack.pop();
    p(*current->pair_);
    current = current->right_;
  }
  return p;
}

template< typename Key, typename Value, typename Comparator >
template< typename PairPred >
PairPred miheev::Tree< Key, Value, Comparator >::traverseLnR(PairPred p)
{
  Stack< Tree* > stack;
  Tree* current = this;
  while (current || !stack.empty())
  {
    while (current)
    {
      stack.push(current);
      current = current->left_;
    }
    current = stack.top();
    stack.pop();
    p(*current->pair_);
    current = current->right_;
  }
  return p;
}

template< typename Key, typename Value, typename Comparator >
template< typename PairPred >
PairPred miheev::Tree< Key, Value, Comparator >::ctraverseRnL(PairPred p) const
{
  Stack< const Tree* > stack;
  const Tree* current = this;
  while (current || !stack.empty())
  {
    while (current)
    {
      stack.push(current);
      current = current->right_;
    }
    current = stack.top();
    stack.pop();
    p(*current->pair_);
    current = current->left_;
  }
  return p;
}

template< typename Key, typename Value, typename Comparator >
template< typename PairPred >
PairPred miheev::Tree< Key, Value, Comparator >::traverseRnL(PairPred p)
{
  Stack< Tree* > stack;
  Tree* current = this;
  while (current || !stack.empty())
  {
    while (current)
    {
      stack.push(current);
      current = current->right_;
    }
    current = stack.top();
    stack.pop();
    p(*current->pair_);
    current = current->left_;
  }
  return p;
}

template< typename Key, typename Value, typename Comparator >
template< typename PairPred >
PairPred miheev::Tree< Key, Value, Comparator >::ctraverseBreadth(PairPred p) const
{
  Queue< Tree * > queue;
  const Tree* current = this;
  while (current || !queue.empty())
  {
    if (current->left_)
    {
      queue.push(current->left_);
    }
    if (current->right_)
    {
      queue.push(current->right_);
    }
    p(*current->pair_);
    current = queue.empty() ? nullptr : queue.front();
    queue.pop();
  }
  return p;
}

template< typename Key, typename Value, typename Comparator >
template< typename PairPred >
PairPred miheev::Tree< Key, Value, Comparator >::traverseBreadth(PairPred p)
{
  Queue< Tree * > queue;
  Tree* current = this;
  while (current || !queue.empty())
  {
    if (current->left_)
    {
      queue.push(current->left_);
    }
    if (current->right_)
    {
      queue.push(current->right_);
    }
    p(*current->pair_);
    current = queue.empty() ? nullptr : queue.front();
    queue.pop();
  }
  return p;
}

#endif
