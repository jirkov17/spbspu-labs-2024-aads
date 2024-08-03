#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <algorithm>
#include <cassert>
#include <exception>
#include <functional>
#include <iterator>
#include <memory>
#include <utility>
#include "queue.hpp"
#include "stack.hpp"

namespace kovshikov
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class Tree
  {
  public:

    Tree();
    Tree(const Tree& tree);
    Tree(Tree&& tree);

    ~Tree();

    class Node;
    class Iterator;
    class ConstIterator;

    using Pair = std::pair< Key, Value >;
    using Range = std::pair< Iterator, Iterator >;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

    Iterator find(const Key& key) const;
    size_t count(const Key& key) const;
    Range getEqualRange(const Key& key) const;

    void insert(const Key& key, const Value& value);
    void insert(Pair& pair);
    Value& operator[](const Key& key);
    Value& at(const Key& key);

    const Value& at(const Key& key) const;

    void clear();
    size_t erase(const Key& key);
    Iterator erase(Iterator iterator);

    void swap(Tree& other);

    Iterator end() const noexcept;
    Iterator begin() const noexcept;

    ConstIterator cend() const noexcept;
    ConstIterator cbegin() const noexcept;

    template< typename F >
    F traverse_lnr(F f) const;

    template< typename F >
    F traverse_rnl(F f) const;

    template< typename F >
    F traverse_breadth(F f) const;

  private:
    Node* root_;
    Compare comp;

    size_t getHeight(Node* node);
    long long getDifference(Node* node);
    void RightRight(Node* node);
    void LeftLeft(Node* node);

    Node* checkBalance(Node* node);
    void balance(Node* node);

    void clear(Node* node);
  };
}

template< typename Key, typename Value, typename Compare >
class kovshikov::Tree< Key, Value, Compare >::Node
{
public:
  friend class Tree< Key, Value, Compare >;
  Node(Key key, Value value, Node* father = nullptr, Node* left = nullptr, Node* right = nullptr);

private:
  Node* left_;
  Node* right_;
  Node* father_;
  Pair element_;
};

template< typename Key, typename Value, typename Compare >
kovshikov::Tree< Key, Value, Compare >::Node::Node(Key key, Value value, Node* father, Node* left, Node* right):
  left_(left),
  right_(right),
  father_(father),
  element_(std::make_pair(key, value))
{};

template< typename Key, typename Value, typename Compare >
class kovshikov::Tree< Key, Value, Compare >::Iterator : public std::iterator< std::bidirectional_iterator_tag, Pair >
{
public:

  friend class Tree< Key, Value, Compare >;
  using this_t = Iterator;

  Iterator(): node_(nullptr), root_(nullptr) {};
  Iterator(Node* node, Node* root): node_(node), root_(root) {};
  Iterator(const this_t&) = default;
  ~Iterator() = default;

  this_t& operator=(const this_t&) = default;

  this_t& operator++();
  this_t operator++(int);

  this_t& operator--();
  this_t operator--(int);

  bool operator==(const this_t& other) const;
  bool operator!=(const this_t& other) const;

  Pair& operator*() const;
  Pair* operator->() const;

private:
  Node* node_;
  Node* root_;
};

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Iterator::this_t& kovshikov::Tree< Key, Value, Compare >::Iterator::operator++()
{
  assert(node_ != nullptr);
  Node* current = node_;
  if(current -> right_)
  {
    current = current -> right_;
    while(current -> left_)
    {
      current = current -> left_;
    }
  }
  else
  {
    Node* currentFather = current -> father_;
    while(currentFather && current == currentFather -> right_)
    {
      current = currentFather;
      currentFather = currentFather -> father_;
    }
    current = currentFather;
  }
  node_ = current;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Iterator::this_t kovshikov::Tree< Key, Value, Compare >::Iterator::operator++(int)
{
  assert(node_ != nullptr);
  this_t currentIterator = *this;
  ++(*this);
  return currentIterator;
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Iterator::this_t& kovshikov::Tree< Key, Value, Compare >::Iterator::operator--()
{
  assert(node_ != nullptr);
  Node* current = node_;
  if(current -> left)
  {
    current = current -> left;
    while(current -> right)
    {
      current = current -> right;
    }
  }
  else
  {
    Node* currentFather = current -> father;
    while(currentFather && current == currentFather -> left)
    {
      current = currentFather;
      currentFather = currentFather -> father;
    }
    current = currentFather;
  }
  node_ = current;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Iterator::this_t kovshikov::Tree< Key, Value, Compare >::Iterator::operator--(int)
{
  assert(node_ != nullptr);
  this_t currentIterator = *this;
  --(*this);
  return currentIterator;
}

template< typename Key, typename Value, typename Compare >
bool kovshikov::Tree< Key, Value, Compare >::Iterator::operator==(const this_t& other) const
{
  return node_ == other.node_;
}

template< typename Key, typename Value, typename Compare >
bool kovshikov::Tree< Key, Value, Compare >::Iterator::operator!=(const this_t& other) const
{
  return !(*this == other);
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Pair& kovshikov::Tree< Key, Value, Compare >::Iterator::operator*() const
{
  assert(node_ != nullptr);
  return node_ -> element_;
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Pair* kovshikov::Tree< Key, Value, Compare >::Iterator::operator->() const
{
  assert(node_ != nullptr);
  return std::addressof(node_ -> element_);
}

template< typename Key, typename Value, typename Compare >
class kovshikov::Tree< Key, Value, Compare >::ConstIterator : public std::iterator< std::bidirectional_iterator_tag, Pair >
{
public:

  friend class Tree< Key, Value, Compare >;
  using this_t = ConstIterator;

  ConstIterator(): iterator_(Iterator()) {};
  ConstIterator(Iterator iterator): iterator_(iterator) {};
  ConstIterator(const this_t&) = default;
  ~ConstIterator() = default;

  this_t& operator=(const this_t&) = default;

  this_t& operator++();
  this_t operator++(int);

  this_t& operator--();
  this_t operator--(int);

  bool operator==(const this_t& other) const;
  bool operator!=(const this_t& other) const;

  const Pair& operator*() const;
  const Pair* operator->() const;

private:
  Iterator iterator_;
};

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::ConstIterator& kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator++()
{
  assert(iterator_.node_ != nullptr);
  iterator_++;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::ConstIterator kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator++(int)
{
  assert(iterator_.node_ != nullptr);
  ++iterator_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::ConstIterator& kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator--()
{
  assert(iterator_.node_ != nullptr);
  iterator_--;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::ConstIterator kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator--(int)
{
  assert(iterator_.node_ != nullptr);
  --iterator_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
bool kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator==(const this_t& other) const
{
  return iterator_ == other.iterator_;
}

template< typename Key, typename Value, typename Compare >
bool kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator!=(const this_t& other) const
{
  return !(*this == other);
}

template< typename Key, typename Value, typename Compare >
const typename kovshikov::Tree< Key, Value, Compare >::Pair& kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator*() const
{
  assert(iterator_.node_ != nullptr);
  return iterator_.node_ -> element_;
}

template< typename Key, typename Value, typename Compare >
const typename kovshikov::Tree< Key, Value, Compare >::Pair* kovshikov::Tree< Key, Value, Compare >::ConstIterator::operator->() const
{
  assert(iterator_.node_ != nullptr);
  return std::addressof(iterator_.node_ -> element_);
}

template< typename Key, typename Value, typename Compare >
kovshikov::Tree< Key, Value, Compare >::Tree():
  root_(nullptr),
  comp(Compare())
{};

template< typename Key, typename Value, typename Compare >
kovshikov::Tree< Key, Value, Compare >::Tree(const Tree& tree)
{
  root_ = nullptr;
  comp = tree.comp;
  Iterator iterator = tree.begin();
  while(iterator != tree.end())
  {
    insert(iterator -> first, iterator -> second);
    iterator++;
  }
}

template< typename Key, typename Value, typename Compare >
kovshikov::Tree< Key, Value, Compare >::Tree(Tree&& tree):
  root_(tree.root_),
  comp(std::move(tree.comp))
{
  tree.root_ = nullptr;
}

template< typename Key, typename Value, typename Compare >
kovshikov::Tree< Key, Value, Compare >::~Tree()
{
  clear();
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Iterator kovshikov::Tree< Key, Value, Compare >::end() const noexcept
{
  Node* current = root_;
  if(current == nullptr)
  {
    return Iterator(nullptr, nullptr);
  }
  while(current != nullptr)
  {
    current = current -> right_;
  }
  return Iterator(current, root_);
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Iterator kovshikov::Tree< Key, Value, Compare >::begin() const noexcept
{
  Node* current = root_;
  Node* returned = nullptr;
  if(current == nullptr)
  {
    return end();
  }
  while(current != nullptr)
  {
    returned = current;
    current = current -> left_;
  }
  return Iterator(returned, root_);
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::ConstIterator kovshikov::Tree< Key, Value, Compare >::cend() const noexcept
{
  Iterator iterator = this->end();
  return ConstIterator(iterator);
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::ConstIterator kovshikov::Tree< Key, Value, Compare >::cbegin() const noexcept
{
  Iterator iterator = this->begin();
  return ConstIterator(iterator);
}

template< typename Key, typename Value, typename Compare >
bool kovshikov::Tree< Key, Value, Compare >::isEmpty() const noexcept
{
  return (root_ == nullptr) ? true : false;
}

template< typename Key, typename Value, typename Compare >
bool kovshikov::Tree< Key, Value, Compare >::empty() const noexcept
{
  return isEmpty();
}

template< typename Key, typename Value, typename Compare >
size_t kovshikov::Tree< Key, Value, Compare >::getSize() const noexcept
{
  Iterator cstart = begin();
  Iterator cfinish = end();
  size_t size = 0;
  while(cstart != cfinish)
  {
    size += 1;
    cstart++;
  }
  return size;
}


template< typename Key, typename Value, typename Compare >
size_t kovshikov::Tree< Key, Value, Compare >::size() const noexcept
{
  return getSize();
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Iterator kovshikov::Tree< Key, Value, Compare >::find(const Key& key) const
{
  Node* current = root_;
  while(current != nullptr)
  {
    if(current -> element_.first == key)
    {
      return Iterator(current, root_);
    }
    else if(comp(key, current -> element_.first))
    {
      current = current -> left_;
    }
    else
    {
      current = current -> right_;
    }
  }
  return end();
}

template< typename Key, typename Value, typename Compare >
size_t kovshikov::Tree< Key, Value, Compare >::count(const Key& key) const
{
  if(find(key) == end())
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Range kovshikov::Tree< Key, Value, Compare >::getEqualRange(const Key& key) const
{
  if(find(key) != begin())
  {
    Iterator start = find(key);
    Iterator finish = start + 1;
    return std::make_pair(start, finish);
  }
  else
  {
    return std::make_pair(end(), end());
  }
}

template< typename Key, typename Value, typename Compare >
size_t kovshikov::Tree< Key, Value, Compare >::getHeight(Node* node)
{
  if(node == nullptr)
  {
    return 0;
  }
  return std::max(getHeight(node -> left_), getHeight(node -> right_)) + 1;
}

template< typename Key, typename Value, typename Compare >
long long kovshikov::Tree< Key, Value, Compare >::getDifference(Node* node)
{
  return getHeight(node -> left_) - getHeight(node -> right_);
}

template< typename Key, typename Value, typename Compare >
void kovshikov::Tree< Key, Value, Compare >::RightRight(Node* node)
{
  Node* bigFather = node -> father_;
  Node* newFather = node -> left_;
  Node* lastRight = newFather -> right_;

  node -> father_ = newFather;
  if(bigFather != nullptr)
  {
    if(comp(node -> element_.first, bigFather -> element_.first))
    {
      bigFather -> left_ = newFather;
    }
    else
    {
      bigFather -> right_ = newFather;
    }
  }
  else
  {
    root_ = newFather;
  }
  newFather -> father_ = bigFather;
  newFather -> right_ = node;
  node ->left_ = lastRight;
  if(lastRight != nullptr)
  {
    lastRight -> father_ = node;
  }
}

template< typename Key, typename Value, typename Compare >
void kovshikov::Tree< Key, Value, Compare >::LeftLeft(Node* node)
{
  Node* bigFather = node -> father_;
  Node* newFather = node -> right_;
  Node* lastLeft = newFather -> left_;

  node -> father_ = newFather;
  if(bigFather != nullptr)
  {
    if(comp(node -> element_.first, bigFather -> element_.first))
    {
      bigFather -> left_ = newFather;
    }
    else
    {
      bigFather -> right_ = newFather;
    }
  }
  else
  {
    root_ = newFather;
  }

  newFather -> father_ = bigFather;
  newFather -> left_ = node;
  node -> right_ = lastLeft;
  if(lastLeft != nullptr)
  {
    lastLeft -> father_ = node;
  }
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Node* kovshikov::Tree< Key, Value, Compare >::checkBalance(Node* node)
{
  while(node != nullptr)
  {
    if(std::abs(getDifference(node)) > 1)
    {
      return node;
    }
    else
    {
      node = node -> father_;
    }
  }
  return node;
}

template< typename Key, typename Value, typename Compare >
void kovshikov::Tree< Key, Value, Compare >::balance(Node* node)
{
  Node* toBalance = node;
  bool isBalance = false;
  while(isBalance == false)
  {
    toBalance = checkBalance(toBalance);
    if(toBalance == nullptr)
    {
      isBalance = true;
    }
    else
    {
      if(getDifference(toBalance) < -1 && getDifference(toBalance -> right_) <= 0)
      {
        LeftLeft(toBalance);
      }
      else if(getDifference(toBalance) > 1 && getDifference(toBalance -> left_) >= 0)
      {
        RightRight(toBalance);
      }
      else if(getDifference(toBalance) < -1 && getDifference(toBalance -> right_) > 0)
      {
        RightRight(toBalance -> right_);
        LeftLeft(toBalance);
      }
      else if(getDifference(toBalance) > 1 && getDifference(toBalance -> left_) < 0)
      {
        LeftLeft(toBalance -> left_);
        RightRight(toBalance);
      }
      toBalance = toBalance -> father_;
    }
  }
}

template< typename Key, typename Value, typename Compare >
void kovshikov::Tree< Key, Value, Compare >::insert(const Key& key, const Value& value)
{
  if(find(key) != end())
  {
    erase(key);
  }
  Node* newNode = new Node(key, value);
  if(isEmpty())
  {
    root_ = newNode;
  }
  else
  {
    Node* current = root_;
    Node* father = nullptr;
    while(current != nullptr)
    {
      father = current;
      if(comp(key, current -> element_.first))
      {
        current = current -> left_;
      }
      else
      {
        current = current -> right_;
      }
    }
    newNode -> father_ = father;
    if(comp(key, father -> element_.first))
    {
      father -> left_ = newNode;
    }
    else
    {
      father -> right_ = newNode;
    }
  }
  balance(newNode);
}

template< typename Key, typename Value, typename Compare >
void kovshikov::Tree< Key, Value, Compare >::insert(Pair& pair)
{
  insert(pair.first, pair.second);
}

template< typename Key, typename Value, typename Compare >
Value& kovshikov::Tree< Key, Value, Compare >::operator[](const Key& key)
{
  if(find(key) == end())
  {
    insert(key, Value());
    return find(key).node_ -> element_.second;
  }
  else
  {
    return find(key).node_ -> element_.second;
  }
}

template< typename Key, typename Value, typename Compare >
Value& kovshikov::Tree< Key, Value, Compare >::at(const Key& key)
{
  if(find(key) == end())
  {
    throw std::out_of_range("out_of_range");
  }
  else
  {
    return find(key) -> second;
  }
}

template< typename Key, typename Value, typename Compare >
const Value& kovshikov::Tree< Key, Value, Compare >::at(const Key& key) const
{
  if(find(key) == end())
  {
    throw std::out_of_range("out_of_range");
  }
  else
  {
    return find(key) -> second;
  }
}

template< typename Key, typename Value, typename Compare >
void kovshikov::Tree< Key, Value, Compare >::clear(Node* node)
{
  if(node != nullptr)
  {
    clear(node -> left_);
    clear(node -> right_);
    delete node;
  }
}

template< typename Key, typename Value, typename Compare >
void kovshikov::Tree< Key, Value, Compare >::clear()
{
  if(!isEmpty())
  {
    clear(root_);
  }
  root_ = nullptr;
}

template< typename Key, typename Value, typename Compare >
void kovshikov::Tree< Key, Value, Compare >::swap(Tree& other)
{
  std::swap(comp, other.comp);
  std::swap(root_, other.root_);
}

template< typename Key, typename Value, typename Compare >
typename kovshikov::Tree< Key, Value, Compare >::Iterator kovshikov::Tree< Key, Value, Compare >::erase(Iterator iterator)
{
  Node* toDelete = iterator.node_;
  Node* bigFather = toDelete -> father_;
  Node* changer = nullptr;
  Node* temp = nullptr;
  Node* toBalance = nullptr;
  if(toDelete == nullptr)
  {
    return end();
  }
  if(toDelete -> left_ == nullptr && toDelete -> right_ == nullptr)
  {
    if(bigFather != nullptr)
    {
      if(comp(toDelete -> element_.first, bigFather -> element_.first))
      {
        bigFather -> left_ = nullptr;
      }
      else
      {
        bigFather -> right_ = nullptr;
      }
      delete toDelete;
      balance(bigFather);
      return Iterator(bigFather, root_);
    }
    else
    {
      delete toDelete;
      return end();
    }
  }
  else if(toDelete -> left_ == nullptr && toDelete -> right_ != nullptr)
  {
    changer = toDelete -> right_;
    temp = changer -> left_;
    while(temp != nullptr)
    {
      changer = temp;
      temp = temp -> left_;
    }
    toBalance = changer -> father_;
    if(toBalance != toDelete)
    {
      toBalance -> left_ = nullptr;
    }
  }
  else
  {
    changer = toDelete -> left_;
    temp = changer -> right_;
    while(temp != nullptr)
    {
      changer = temp;
      temp = temp -> right_;
    }
    toBalance = changer -> father_;
    if(toBalance != toDelete)
    {
      toBalance -> right_ = nullptr;
    }
  }
  if(bigFather != nullptr)
  {
    if(comp(toDelete -> element_.first, bigFather -> element_.first))
    {
      bigFather -> left_ = changer;
    }
    else
    {
      bigFather -> right_ = changer;
    }
  }
  changer -> father_ = bigFather;
  if(toDelete -> left_ != nullptr && changer != toDelete -> left_)
  {
    changer -> left_ = toDelete -> left_;
    toDelete -> left_ -> father_ = changer;
  }
  if(toDelete -> right_ != nullptr && changer != toDelete -> right_)
  {
    changer -> right_ = toDelete -> right_;
    toDelete -> right_ -> father_ = changer;
  }

  if(toBalance != toDelete)
  {
    delete toDelete;
    balance(toBalance);
  }
  else
  {
    delete toDelete;
    balance(changer);
  }
  if(bigFather == nullptr)
  {
    root_ = changer;
  }
  return Iterator(changer, root_);
}

template< typename Key, typename Value, typename Compare >
size_t kovshikov::Tree< Key, Value, Compare >::erase(const Key& key)
{
  Iterator iterator = find(key);
  if(iterator == end())
  {
    return 0;
  }
  else
  {
    erase(iterator);
    return 1;
  }
}

template< typename Key, typename Value, typename Compare >
template< typename F >
F kovshikov::Tree< Key, Value, Compare >::traverse_lnr(F f) const
{
  Stack < Node* > stack;
  Node* current = root_;
  while(current != nullptr || !stack.isEmpty())
  {
    while(current != nullptr)
    {
      stack.push(current);
      current = current -> left_;
    }
    current = stack.top();
    f(current -> element_);
    stack.pop();
    current = current -> right_;
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
template< typename F >
F kovshikov::Tree< Key, Value, Compare >::traverse_rnl(F f) const
{
  Stack< Node* > stack;
  Node* current = root_;
  while(current != nullptr || !stack.isEmpty())
  {
    while(current != nullptr)
    {
      stack.push(current);
      current = current -> right_;
    }
    current = stack.top();
    f(current -> element_);
    stack.pop();
    current = current -> left_;
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
template< typename F >
F kovshikov::Tree< Key, Value, Compare >::traverse_breadth(F f) const
{
  if(!isEmpty())
  {
    Queue< Node* > queue;
    queue.push(root_);
    while (!queue.isEmpty())
    {
      Node* current = queue.front();
      queue.pop();
      f(current -> element_);
      if (current -> left_)
      {
        queue.push(current -> left_);
      }
      if (current -> right_)
      {
        queue.push(current -> right_);
      }
    }
  }
  return f;
}

#endif
