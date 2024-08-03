#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP
#include <utility>
#include <algorithm>
#include <functional>
#include <stack.hpp>
#include <queue.hpp>

namespace psarev
{
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class avlTree
  {
  public:
    class ConstIterator;
    class Iterator;

    class LnRIterator;
    class RnLIterator;

    using cIter = ConstIterator;
    using iter = Iterator;
    using dataType = std::pair< Key, Value >;

    avlTree();
    avlTree(const avlTree& that);
    avlTree(size_t& initSize, dataType& initData);
    avlTree(std::initializer_list< dataType > inList);
    ~avlTree();

    void swap(avlTree& first, avlTree& second) noexcept;
    avlTree& operator=(avlTree that);
    avlTree& operator=(avlTree&& that);

    void clear();

    iter begin() noexcept;
    cIter cbegin() const noexcept;
    iter end() noexcept;
    cIter cend() const noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;

    Value& at(const Key& key);
    const Value& at(const Key& key) const;
    Value& operator[](const Key& key);
    Value& operator[](Key&& key);

    std::pair< Iterator, Iterator > equalRange(const Key& key);

    iter find(const Key& key);
    iter insert(dataType& data);
    iter insert(dataType&& data);
    bool erase(const Key& key);

    template < typename F >
    F traverseLnR(F f) const;
    template < typename F >
    F traverseRnL(F f) const;
    template < typename F >
    F traverseBre(F f) const;

    template < typename F >
    F traverseLnR(F f);
    template < typename F >
    F traverseRnL(F f);
    template < typename F >
    F traverseBre(F f);

  private:

    struct Unit
    {
      dataType data;
      Unit* ancest;
      Unit* left;
      Unit* right;

      Unit(dataType data_, Unit* ancest_ = nullptr, Unit* left_ = nullptr, Unit* right_ = nullptr) :
        data(data_),
        ancest(ancest_),
        left(left_),
        right(right_)
      {}
    };

    Unit* treeRoot;

    size_t getSize(Unit* unit) const;
    void undercut(Unit* unit);
    Unit* delUnit(Unit* unit, const Key& key);

    Unit* makeBal(Unit* unit);
    int getFact(Unit* unit);

    int getHeight(Unit* unit);

    Unit* lTurn(Unit* moveU);
    Unit* rTurn(Unit* moveU);

    Unit* updData(Unit* unit, const dataType& data);
    Unit* updData(Unit* unit, dataType&& data);
  };
}

template < typename Key, typename Value, typename Compare >
class psarev::avlTree< Key, Value, Compare >::ConstIterator : public std::iterator< std::bidirectional_iterator_tag, dataType >
{
public:
  friend class avlTree< Key, Value, Compare >;
  using this_t = ConstIterator;

  ConstIterator();
  ConstIterator(Iterator that);
  ConstIterator(const this_t&) = default;
  ~ConstIterator() = default;

  this_t& operator=(const this_t&) = default;

  this_t& operator++();
  this_t operator++(int);
  this_t& operator--();
  this_t operator--(int);

  const dataType& operator*() const;
  const dataType* operator->() const;

  bool operator==(const this_t& rhs) const;
  bool operator!=(const this_t& rhs) const;

private:
  Unit* unit;
  Unit* root;
  ConstIterator(Unit* unit_, Unit* root_);
};

template < typename Key, typename Value, typename Compare >
psarev::avlTree< Key, Value, Compare >::ConstIterator::ConstIterator() :
  unit(nullptr),
  root(nullptr)
{}

template < typename Key, typename Value, typename Compare >
psarev::avlTree< Key, Value, Compare >::ConstIterator::ConstIterator(Iterator that) :
  unit(that.imIter.unit),
  root(that.imIter.root)
{}

template< typename Key, typename Value, typename Compare >
psarev::avlTree< Key, Value, Compare >::ConstIterator::ConstIterator(Unit* unit_, Unit* root_) :
  unit(unit_), root(root_)
{}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::ConstIterator& psarev::avlTree< Key, Value, Compare >::ConstIterator::operator++()
{
  if (unit->right)
  {
    unit = unit->right;
    while (unit->left)
    {
      unit = unit->left;
    }
  }
  else
  {
    Unit* tAncest = unit->ancest;
    while (tAncest && unit == tAncest->right)
    {
      unit = tAncest;
      tAncest = unit->ancest;
    }
    unit = tAncest;
  }
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::ConstIterator psarev::avlTree< Key, Value, Compare >::ConstIterator::operator++(int)
{
  this_t inked(*this);
  ++(*this);
  return inked;
}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::ConstIterator& psarev::avlTree< Key, Value, Compare >::ConstIterator::operator--()
{
  if (unit == nullptr)
  {
    unit = root;
    while (unit->right != nullptr)
    {
      unit = unit->right;
    }
  }
  else if (unit->left != nullptr)
  {
    unit = unit->left;
    while (unit->right != nullptr)
    {
      unit = unit->right;
    }
  }
  else
  {
    while ((unit == unit->ancest->left) && (unit->ancest != nullptr))
    {
      unit = unit->ancest;
    }
    unit = unit->ancest;
  }
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::ConstIterator psarev::avlTree< Key, Value, Compare >::ConstIterator::operator--(int)
{
  this_t deked(*this);
  --(*this);
  return deked;
}

template < typename Key, typename Value, typename Compare >
const typename psarev::avlTree< Key, Value, Compare >::dataType& psarev::avlTree< Key, Value, Compare >::ConstIterator::operator*() const
{
  return unit->data;
}

template < typename Key, typename Value, typename Compare >
const typename psarev::avlTree< Key, Value, Compare >::dataType* psarev::avlTree< Key, Value, Compare >::ConstIterator::operator->() const
{
  return &(unit->data);
}

template < typename Key, typename Value, typename Compare >
bool psarev::avlTree< Key, Value, Compare >::ConstIterator::operator==(const this_t& that) const
{
  return unit == that.unit;
}

template < typename Key, typename Value, typename Compare >
bool psarev::avlTree< Key, Value, Compare >::ConstIterator::operator!=(const this_t& that) const
{
  return !(that == *this);
}

template< typename Key, typename Value, typename Compare >
class psarev::avlTree< Key, Value, Compare >::Iterator : public std::iterator< std::bidirectional_iterator_tag, dataType >
{
public:
  friend class avlTree< Key, Value, Compare >;
  using this_t = Iterator;
  Iterator();
  Iterator(ConstIterator constIter);
  Iterator(const this_t&) = default;
  ~Iterator() = default;

  this_t& operator=(const this_t&) = default;
  this_t& operator++();
  this_t operator++(int);
  this_t& operator--();
  this_t operator--(int);

  dataType& operator*();
  dataType* operator->();
  const dataType& operator*() const;
  const dataType* operator->() const;

  bool operator==(const this_t&) const;
  bool operator!=(const this_t&) const;

private:
  ConstIterator imIter;
};

template < typename Key, typename Value, typename Compare >
psarev::avlTree< Key, Value, Compare >::Iterator::Iterator() :
  imIter(ConstIterator())
{}

template < typename Key, typename Value, typename Compare >
psarev::avlTree< Key, Value, Compare >::Iterator::Iterator(ConstIterator that) :
  imIter(that)
{}

template< typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::Iterator& psarev::avlTree< Key, Value, Compare >::Iterator::operator++()
{
  assert(imIter != ConstIterator());
  imIter++;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::Iterator psarev::avlTree< Key, Value, Compare >::Iterator::operator++(int)
{
  ++imIter;
  return imIter;
}

template< typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::Iterator& psarev::avlTree< Key, Value, Compare >::Iterator::operator--()
{
  assert(imIter != nullptr);
  --imIter;
  return imIter;
}

template< typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::Iterator psarev::avlTree< Key, Value, Compare >::Iterator::operator--(int)
{
  --imIter;
  return imIter;
}

template< typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::dataType& psarev::avlTree< Key, Value, Compare >::Iterator::operator*()
{
  return imIter.unit->data;
}

template< typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::dataType* psarev::avlTree< Key, Value, Compare >::Iterator::operator->()
{
  return &(imIter.unit->data);
}

template< typename Key, typename Value, typename Compare >
const typename psarev::avlTree< Key, Value, Compare >::dataType& psarev::avlTree< Key, Value, Compare >::Iterator::operator*() const
{
  return imIter.node_->data;
}

template< typename Key, typename Value, typename Compare >
const typename psarev::avlTree< Key, Value, Compare >::dataType* psarev::avlTree< Key, Value, Compare >::Iterator::operator->() const
{
  return &(imIter.unit->data);
}

template< typename Key, typename Value, typename Compare >
bool psarev::avlTree< Key, Value, Compare >::Iterator::operator==(const this_t& that) const
{
  return imIter == that.imIter;
}

template< typename Key, typename Value, typename Compare >
bool psarev::avlTree< Key, Value, Compare >::Iterator::operator!=(const this_t& that) const
{
  return !(that == *this);
}

template < typename Key, typename Value, typename Compare >
class psarev::avlTree< Key, Value, Compare >::LnRIterator : public std::iterator< std::bidirectional_iterator_tag, dataType >
{
public:
  friend class avlTree;
  using this_t = LnRIterator;
  LnRIterator();
  LnRIterator(Unit* unit_);
  LnRIterator(const this_t&) = default;
  ~LnRIterator() = default;

  this_t& operator++();
  this_t operator++(int);
  this_t& operator--();
  this_t operator--(int);

  dataType& operator*();
  dataType* operator->();
  const dataType& operator*() const;
  const dataType* operator->() const;

  bool operator==(const this_t&) const;
  bool operator!=(const this_t&) const;

private:
  Unit* unit;
};

template < typename Key, typename Value, typename Compare >
psarev::avlTree< Key, Value, Compare >::LnRIterator::LnRIterator() :
  unit(nullptr)
{}

template < typename Key, typename Value, typename Compare >
psarev::avlTree< Key, Value, Compare >::LnRIterator::LnRIterator(Unit* unit_) :
  unit(unit_)
{}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::LnRIterator& psarev::avlTree< Key, Value, Compare >::LnRIterator::operator++()
{
  if (unit == nullptr)
  {
    return *this;
  }

  if (unit->right != nullptr)
  {
    unit = unit->right;
    while (unit->left != nullptr)
    {
      unit = unit->left;
    }
  }
  else
  {
    Unit* prev = unit;
    unit = unit->ancest;

    while (prev == unit->right && unit != nullptr)
    {
      prev = unit;
      unit = unit->ancest;
    }
  }

  return *this;
}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::LnRIterator psarev::avlTree< Key, Value, Compare >::LnRIterator::operator++(int)
{
  this_t tempo = *this;
  ++(*this);
  return tempo;
}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::LnRIterator& psarev::avlTree< Key, Value, Compare >::LnRIterator::operator--()
{
  if (unit == nullptr)
  {
    unit = treeRoot;
    while (unit->right != nullptr)
    {
      unit = unit->right;
    }
  }
  else if (unit->left != nullptr)
  {
    unit = unit->left;
    while (unit->right != nullptr)
    {
      unit = unit->right;
    }
  }
  else
  {
    Unit* prev = unit;
    unit = unit->ancest;

    while (prev == unit->left && unit != nullptr)
    {
      prev = unit;
      unit = unit->ancest;
    }
  }

  return *this;
}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::LnRIterator psarev::avlTree< Key, Value, Compare >::LnRIterator::operator--(int)
{
  this_t tempo = *this;
  --(*this);
  return tempo;
}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::dataType& psarev::avlTree< Key, Value, Compare >::LnRIterator::operator*()
{
  return unit->data;
}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::dataType*
psarev::avlTree< Key, Value, Compare >::LnRIterator::operator->()
{
  return &(unit->data);
}

template < typename Key, typename Value, typename Compare >
const typename psarev::avlTree< Key, Value, Compare >::dataType& psarev::avlTree< Key, Value, Compare >::LnRIterator::operator*() const
{
  return unit->data;
}

template < typename Key, typename Value, typename Compare >
const typename psarev::avlTree< Key, Value, Compare >::dataType* psarev::avlTree< Key, Value, Compare >::LnRIterator::operator->() const
{
  return &(unit->data);
}

template < typename Key, typename Value, typename Compare >
bool psarev::avlTree< Key, Value, Compare >::LnRIterator::operator==(const this_t& that) const
{
  return unit == that.unit;
}

template < typename Key, typename Value, typename Compare >
bool psarev::avlTree< Key, Value, Compare >::LnRIterator::operator!=(const this_t& that) const
{
  return !(*this == that);
}

template < typename Key, typename Value, typename Compare >
class psarev::avlTree< Key, Value, Compare >::RnLIterator : public std::iterator< std::bidirectional_iterator_tag, dataType >
{
public:
  friend class avlTree;
  using this_t = RnLIterator;
  RnLIterator();
  RnLIterator(Unit* unit_);
  RnLIterator(const this_t&) = default;
  ~RnLIterator() = default;

  this_t& operator++();
  this_t operator++(int);
  this_t& operator--();
  this_t operator--(int);

  dataType& operator*();
  dataType* operator->();
  const dataType& operator*() const;
  const dataType* operator->() const;

  bool operator==(const this_t&) const;
  bool operator!=(const this_t&) const;

private:
  Unit* unit;
};

template < typename Key, typename Value, typename Compare >
psarev::avlTree< Key, Value, Compare >::RnLIterator::RnLIterator() :
  unit(nullptr)
{}

template < typename Key, typename Value, typename Compare >
psarev::avlTree< Key, Value, Compare >::RnLIterator::RnLIterator(Unit* unit_) :
  unit(unit_)
{}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::RnLIterator& psarev::avlTree< Key, Value, Compare >::RnLIterator::operator++()
{
  if (unit == nullptr)
  {
    return *this;
  }

  if (unit->left != nullptr)
  {
    unit = unit->left;
    while (unit->right != nullptr)
    {
      unit = unit->right;
    }
  }
  else
  {
    Unit* prev = unit;
    unit = unit->ancest;

    while (prev == unit->left && unit != nullptr)
    {
      prev = unit;
      unit = unit->ancest;
    }
  }

  return *this;
}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::RnLIterator psarev::avlTree< Key, Value, Compare >::RnLIterator::operator++(int)
{
  this_t tempo = *this;
  ++(*this);
  return tempo;
}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::RnLIterator& psarev::avlTree< Key, Value, Compare >::RnLIterator::operator--()
{
  if (unit == nullptr)
  {
    unit = treeRoot;
    while (unit->right != nullptr)
    {
      unit = unit->right;
    }
  }
  else if (unit->right != nullptr)
  {
    unit = unit->right;
    while (unit->left != nullptr)
    {
      unit = unit->left;
    }
  }
  else
  {
    Unit* prev = unit;
    unit = unit->ancest;

    while (prev == unit->right && unit != nullptr)
    {
      prev = unit;
      unit = unit->ancest;
    }
  }

  return *this;
}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::RnLIterator psarev::avlTree< Key, Value, Compare >::RnLIterator::operator--(int)
{
  this_t tempo = *this;
  --(*this);
  return tempo;
}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::dataType& psarev::avlTree< Key, Value, Compare >::RnLIterator::operator*()
{
  return unit->data;
}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::dataType*
psarev::avlTree< Key, Value, Compare >::RnLIterator::operator->()
{
  return &(unit->data);
}

template < typename Key, typename Value, typename Compare >
const typename psarev::avlTree< Key, Value, Compare >::dataType& psarev::avlTree< Key, Value, Compare >::RnLIterator::operator*() const
{
  return unit->data;
}

template < typename Key, typename Value, typename Compare >
const typename psarev::avlTree< Key, Value, Compare >::dataType* psarev::avlTree< Key, Value, Compare >::RnLIterator::operator->() const
{
  return &(unit->data);
}

template < typename Key, typename Value, typename Compare >
bool psarev::avlTree< Key, Value, Compare >::RnLIterator::operator==(const this_t& that) const
{
  return unit == that.unit;
}

template < typename Key, typename Value, typename Compare >
bool psarev::avlTree< Key, Value, Compare >::RnLIterator::operator!=(const this_t& that) const
{
  return !(*this == that);
}

template< typename Key, typename Value, typename Compare >
psarev::avlTree< Key, Value, Compare >::avlTree() :
  treeRoot(nullptr)
{}

template<typename Key, typename Value, typename Compare>
psarev::avlTree< Key, Value, Compare >::avlTree(const avlTree& that) :
  treeRoot(nullptr)
{
  for (Iterator iter = that.cbegin(); iter != cend(); ++iter)
  {
    insert(*iter);
  }
}

template<typename Key, typename Value, typename Compare>
psarev::avlTree< Key, Value, Compare >::avlTree(size_t& initSize, dataType& initData)
{
  treeRoot = nullptr;
  for (size_t i = 0; i < initSize; ++i)
  {
    insert(initData);
  }
}

template<typename Key, typename Value, typename Compare>
psarev::avlTree< Key, Value, Compare >::avlTree(std::initializer_list< dataType > inList)
{
  for (auto data : inList)
  {
    insert(data);
  }
}

template< typename Key, typename Value, typename Compare >
psarev::avlTree< Key, Value, Compare >::~avlTree()
{
  clear();
}

template< typename Key, typename Value, typename Compare >
void psarev::avlTree< Key, Value, Compare >::swap(avlTree& first, avlTree& second) noexcept
{
  std::swap(first.treeRoot, second.treeRoot);
}

template< typename Key, typename Value, typename Compare >
psarev::avlTree< Key, Value, Compare >& psarev::avlTree< Key, Value, Compare >::operator=(avlTree that)
{
  swap(*this, that);
  return *this;
}

template< typename Key, typename Value, typename Compare >
psarev::avlTree< Key, Value, Compare >& psarev::avlTree< Key, Value, Compare >::operator=(avlTree&& that)
{
  if (&that != this)
  {
    clear();
    treeRoot = std::move(that.treeRoot);
    that.treeRoot = nullptr;
  }
  return *this;
}

template<typename Key, typename Value, typename Compare>
void psarev::avlTree< Key, Value, Compare >::clear()
{
  undercut(treeRoot);
  treeRoot = nullptr;
}

template<typename Key, typename Value, typename Compare>
typename psarev::avlTree< Key, Value, Compare >::Iterator psarev::avlTree< Key, Value, Compare >::begin() noexcept
{
  if (isEmpty())
  {
    return cend();
  }
  Unit* tempo = treeRoot;
  while (tempo->left != nullptr)
  {
    tempo = tempo->left;
  }
  return Iterator(ConstIterator(tempo, treeRoot));
}

template<typename Key, typename Value, typename Compare>
typename psarev::avlTree< Key, Value, Compare >::ConstIterator psarev::avlTree<Key, Value, Compare>::cbegin() const noexcept
{
  if (isEmpty())
  {
    return cend();
  }
  Unit* tempo = treeRoot;
  while (tempo->left != nullptr)
  {
    tempo = tempo->left;
  }
  return ConstIterator(tempo, treeRoot);
}

template<typename Key, typename Value, typename Compare>
typename psarev::avlTree< Key, Value, Compare >::Iterator psarev::avlTree<Key, Value, Compare>::end() noexcept
{
  return Iterator(ConstIterator(nullptr, treeRoot));
}

template<typename Key, typename Value, typename Compare>
typename psarev::avlTree< Key, Value, Compare >::ConstIterator psarev::avlTree<Key, Value, Compare>::cend() const noexcept
{
  return ConstIterator(nullptr, treeRoot);
}

template< typename Key, typename Value, typename Compare >
bool psarev::avlTree< Key, Value, Compare >::isEmpty() const noexcept
{
  return (treeRoot == nullptr);
}

template<typename Key, typename Value, typename Compare>
size_t psarev::avlTree< Key, Value, Compare >::getSize() const noexcept
{
  return getSize(treeRoot);
}

template<typename Key, typename Value, typename Compare>
Value& psarev::avlTree<Key, Value, Compare>::at(const Key& key)
{
  Unit* curr = treeRoot;
  Compare compare;

  while (curr != nullptr)
  {
    if (compare(curr->data.first, key))
    {
      curr = curr->right;
    }
    else if (compare(key, curr->data.first))
    {
      curr = curr->left;
    }
    else
    {
      return curr->data.second;
    }
  }
  throw std::out_of_range("Error: No such element exists!");
}

template<typename Key, typename Value, typename Compare>
const Value& psarev::avlTree<Key, Value, Compare>::at(const Key& key) const
{
  Unit* curr = treeRoot;
  Compare compare;

  while (curr != nullptr)
  {
    if (compare(curr->data.first, key))
    {
      curr = curr->right;
    }
    else if (compare(key, curr->data.first))
    {
      curr = curr->left;
    }
    else
    {
      return curr->data.second;
    }
  }
  throw std::out_of_range("Error: No such element exists!");
}

template<typename Key, typename Value, typename Compare>
Value& psarev::avlTree<Key, Value, Compare>::operator[](const Key& key)
{
  Unit* curr = treeRoot;
  Compare compare;

  while (curr != nullptr)
  {
    if (compare(curr->data.first, key))
    {
      curr = curr->right;
    }
    else if (compare(key, curr->data.first))
    {
      curr = curr->left;
    }
    else
    {
      return curr->data.second;
    }
  }
  throw std::out_of_range("Error: No such element exists!");
}

template<typename Key, typename Value, typename Compare>
Value& psarev::avlTree<Key, Value, Compare>::operator[](Key&& key)
{
  Unit* curr = treeRoot;
  Compare compare;

  while (curr != nullptr)
  {
    if (compare(curr->data.first, key))
    {
      curr = curr->right;
    }
    else if (compare(key, curr->data.first))
    {
      curr = curr->left;
    }
    else
    {
      return curr->data.second;
    }
  }
  throw std::out_of_range("Error: No such element exists!");
}

template < typename Key, typename Value, typename Compare >
using it = typename psarev::avlTree< Key, Value, Compare >::Iterator;

template < typename Key, typename Value, typename Compare >
using iterPair = std::pair< it< Key, Value, Compare >, it< Key, Value, Compare > >;

template<typename Key, typename Value, typename Compare>
iterPair< Key, Value, Compare > psarev::avlTree<Key, Value, Compare>::equalRange(const Key& key)
{
  Unit* unit = treeRoot;
  Iterator startIt = begin();
  Iterator tempo = begin();
  Iterator finIt = ++tempo;
  while (startIt != end())
  {
    if (startIt->first == key)
    {
      return(std::make_pair(startIt, finIt));
    }
    else if (startIt->first < key)
    {
      startIt++;
      finIt++;
    }
    else
    {
      return(std::make_pair(startIt, startIt));
    }
  }
  return std::make_pair(Iterator(nullptr), Iterator(nullptr));
}

template<typename Key, typename Value, typename Compare>
typename psarev::avlTree< Key, Value, Compare >::Iterator psarev::avlTree< Key, Value, Compare >::find(const Key& key)
{
  Compare compare;
  Unit* tempo = treeRoot;

  while (tempo != nullptr)
  {
    if (compare(key, tempo->data.first))
    {
      tempo = tempo->left;
    }
    else if (compare(tempo->data.first, key))
    {
      tempo = tempo->right;
    }
    else
    {
      return Iterator(ConstIterator(tempo, treeRoot));
    }
  }
  return end();
}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::Iterator psarev::avlTree< Key, Value, Compare >::insert(dataType& data)
{
  treeRoot = updData(treeRoot, data);
  return find(data.first);
}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::Iterator psarev::avlTree< Key, Value, Compare >::insert(dataType&& data)
{
  treeRoot = updData(treeRoot, std::move(data));
  return find(data.first);
}

template< typename Key, typename Value, typename Compare >
bool psarev::avlTree<Key, Value, Compare>::erase(const Key& key)
{
  if (find(key) != end())
  {
    treeRoot = delUnit(treeRoot, key);
    return true;
  }
  return false;
}

template< typename Key, typename Value, typename Compare >
template< typename F >
F psarev::avlTree<Key, Value, Compare>::traverseLnR(F f) const
{
  Stack< const Unit* > ancestors;
  const Unit* wayP = treeRoot;

  while (!ancestors.isEmpty() || wayP != nullptr)
  {
    while (wayP != nullptr)
    {
      ancestors.push(wayP);
      wayP = wayP->left;
    }

    if (!ancestors.isEmpty())
    {
      wayP = ancestors.getTop();
      ancestors.pop();

      f(wayP->data);
      wayP = wayP->right;
    }
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
template< typename F >
F psarev::avlTree<Key, Value, Compare>::traverseRnL(F f) const
{
  Stack< const Unit* > ancestors;
  const Unit* wayP = treeRoot;

  while (!ancestors.isEmpty() || wayP != nullptr)
  {
    while (wayP != nullptr)
    {
      ancestors.push(wayP);
      wayP = wayP->right;
    }

    if (!ancestors.isEmpty())
    {
      wayP = ancestors.getTop();
      ancestors.pop();

      f(wayP->data);
      wayP = wayP->left;
    }
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
template< typename F >
F psarev::avlTree<Key, Value, Compare>::traverseBre(F f) const
{
  if (isEmpty())
  {
    return f;
  }
  Queue< const Unit* > stage;

  stage.push(treeRoot);
  while (!stage.isEmpty())
  {
    const Unit* unit = stage.getFront();
    f(unit->data);
    stage.pop();

    if (unit->left != nullptr)
    {
      stage.push(unit->left);
    }

    if (unit->right != nullptr)
    {
      stage.push(unit->right);
    }
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
template< typename F >
F psarev::avlTree<Key, Value, Compare>::traverseLnR(F f)
{
  Stack< Unit* > ancestors;
  Unit* wayP = treeRoot;

  while (!ancestors.isEmpty() || wayP != nullptr)
  {
    while (wayP != nullptr)
    {
      ancestors.push(wayP);
      wayP = wayP->left;
    }

    if (!ancestors.isEmpty())
    {
      wayP = ancestors.getTop();
      ancestors.pop();

      f(wayP->data);
      wayP = wayP->right;
    }
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
template< typename F >
F psarev::avlTree<Key, Value, Compare>::traverseRnL(F f)
{
  Stack< Unit* > ancestors;
  Unit* wayP = treeRoot;

  while (!ancestors.isEmpty() || wayP != nullptr)
  {
    while (wayP != nullptr)
    {
      ancestors.push(wayP);
      wayP = wayP->right;
    }

    if (!ancestors.isEmpty())
    {
      wayP = ancestors.getTop();
      ancestors.pop();

      f(wayP->data);
      wayP = wayP->left;
    }
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
template< typename F >
F psarev::avlTree<Key, Value, Compare>::traverseBre(F f)
{
  if (isEmpty())
  {
    return f;
  }
  Queue< Unit* > stage;

  stage.push(treeRoot);
  while (!stage.isEmpty())
  {
    Unit* unit = stage.getFront();
    f(unit->data);
    stage.pop();

    if (unit->left != nullptr)
    {
      stage.push(unit->left);
    }

    if (unit->right != nullptr)
    {
      stage.push(unit->right);
    }
  }
  return f;
}

template<typename Key, typename Value, typename Compare>
size_t psarev::avlTree<Key, Value, Compare>::getSize(Unit* unit) const
{
  if (unit == nullptr)
  {
    return 0;
  }
  size_t res = getSize(unit->left) + getSize(unit->right) + 1;
  return res;
}

template<typename Key, typename Value, typename Compare>
void psarev::avlTree<Key, Value, Compare>::undercut(Unit* unit)
{
  if (unit != nullptr)
  {
    undercut(unit->left);
    undercut(unit->right);
    delete unit;
    unit = nullptr;
  }
}

template<typename Key, typename Value, typename Compare>
typename psarev::avlTree< Key, Value, Compare >::Unit* psarev::avlTree< Key, Value, Compare >::delUnit(Unit* unit, const Key& key)
{
  Compare compare;
  if (unit == nullptr)
  {
    return unit;
  }

  if (compare(key, unit->data.first))
  {
    unit->left = delUnit(unit->left, key);
  }
  else if (compare(unit->data.first, key))
  {
    unit->right = delUnit(unit->right, key);
  }
  else
  {
    Unit* tempo = nullptr;
    if (unit->left == nullptr && unit->right == nullptr)
    {
      delete unit;
      return nullptr;
    }
    else if (unit->right == nullptr)
    {
      tempo = unit->left;
      *unit = *tempo;
      delete tempo;
    }
    else if (unit->left == nullptr)
    {
      tempo = unit->right;
      *unit = *tempo;
      delete tempo;
    }
    else
    {
      tempo = unit->right;
      while (tempo->left != nullptr)
      {
        tempo = tempo->left;
      }
      unit->data = tempo->data;
      unit->right = delUnit(unit->right, tempo->data.first);
    }
  }

  unit = makeBal(unit);
  return unit;
}

template<typename Key, typename Value, typename Compare>
typename psarev::avlTree< Key, Value, Compare >::Unit* psarev::avlTree<Key, Value, Compare>::makeBal(Unit* unit)
{
  int balFact = getFact(unit);
  if (balFact == 2)
  {
    if (getFact(unit->left) >= 0)
    {
      unit = rTurn(unit);
    }
    else
    {
      unit->left = lTurn(unit->left);
      unit = rTurn(unit);
    }
  }
  else if (balFact == -2)
  {
    if (getFact(unit->right) <= 0)
    {
      unit = lTurn(unit);
    }
    else
    {
      unit->right = rTurn(unit->right);
      unit = lTurn(unit);
    }
  }

  return unit;
}

template<typename Key, typename Value, typename Compare>
int psarev::avlTree<Key, Value, Compare>::getFact(Unit* unit)
{
  if (unit == nullptr)
  {
    return 0;
  }
  return getHeight(unit->left) - getHeight(unit->right);
}

template < typename Key, typename Value, typename Compare >
int psarev::avlTree< Key, Value, Compare >::getHeight(Unit* unit)
{
  if (unit == nullptr)
  {
    return 0;
  }
  int leftHeight = getHeight(unit->left);
  int rightHeight = getHeight(unit->right);
  return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

template< typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::Unit* psarev::avlTree<Key, Value, Compare>::lTurn(Unit* moveU)
{
  Unit* tempo = moveU->right;
  Unit* ancest = moveU->ancest;
  moveU->right = tempo->left;

  if (moveU->right != nullptr)
  {
    moveU->right->ancest = moveU;
  }

  tempo->left = moveU;
  tempo->left->ancest = tempo;
  tempo->ancest = ancest;
  return tempo;
}

template<typename Key, typename Value, typename Compare>
typename psarev::avlTree< Key, Value, Compare >::Unit* psarev::avlTree<Key, Value, Compare>::rTurn(Unit* moveU)
{
  Unit* tempo = moveU->left;
  Unit* ancest = moveU->ancest;
  moveU->left = tempo->right;

  if (moveU->left != nullptr)
  {
    moveU->left->ancest = moveU;
  }

  tempo->right = moveU;
  tempo->right->ancest = tempo;
  tempo->ancest = ancest;
  return tempo;
}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::Unit* psarev::avlTree< Key, Value, Compare >::updData(Unit* unit, const dataType& newData)
{
  Compare compare;
  if (unit == nullptr)
  {
    unit = new Unit(newData);
    return unit;
  }
  else
  {
    if (compare(newData.first, unit->data.first))
    {
      unit->left = updData(unit->left, newData);
      unit->left->ancest = unit;
    }
    else if (compare(unit->data.first, newData.first))
    {
      unit->right = updData(unit->right, newData);
      unit->right->ancest = unit;
    }
  }

  unit = makeBal(unit);
  return unit;
}

template < typename Key, typename Value, typename Compare >
typename psarev::avlTree< Key, Value, Compare >::Unit* psarev::avlTree< Key, Value, Compare >::updData(Unit* unit, dataType&& newData)
{
  Compare compare;
  if (unit == nullptr)
  {
    unit = new Unit(std::move(newData));
    return unit;
  }
  else
  {
    if (compare(newData.first, unit->data.first))
    {
      unit->left = updData(unit->left, std::move(newData));
      unit->left->ancest = unit;
    }
    else if (compare(unit->data.first, newData.first))
    {
      unit->right = updData(unit->right, std::move(newData));
      unit->right->ancest = unit;
    }
  }

  unit = makeBal(unit);
  return unit;
}

#endif
