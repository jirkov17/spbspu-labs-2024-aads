#ifndef LIST_HPP
#define LIST_HPP
#include <stddef.h>
#include <iostream>
#include <string>
#include <limits>

namespace mihalchenko
{
  template < typename T >
  class List
  {
  public:
    class ConstIterator;
    class Iterator;

    List();
    explicit List(size_t count);
    List(size_t count, const T &value);
    List(std::initializer_list< T > ilist);
    List(const List &copy);
    List(List &&move);
    ~List();

    List< T > &operator=(const List &copy);
    List< T > &operator=(List &&move);

    void swap(List< T > &other) noexcept;

    void push_front(const T &data);
    void push_back(const T &data);

    void pop_front();
    void pop_back();

    void insert(T value, size_t ind);
    void erase(size_t i);
    T &operator[](const size_t ind);
    void clear();
    bool empty() noexcept;

    T &front();

    size_t getSize();
    void setSize(const size_t size);
    T getT();

    void assign(size_t count, const T &value);
    void assign(ConstIterator first, ConstIterator last);
    void assign(std::initializer_list< T > ilist);

    Iterator insert_after(Iterator position, const T &value);
    Iterator insert_after(Iterator position, size_t count, const T &value);
    Iterator erase_after(Iterator position);
    Iterator erase_after(Iterator first, Iterator last);

    void splice(Iterator pos, List< T > &other);
    void reverse();

    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;
    Iterator begin() noexcept;
    Iterator end() noexcept;

    void eraseAfter(Iterator iterator);

    void remove(const T &iterValue);
    template < typename F >
    void remove_if(F functor);

    void advance(Iterator& pos, size_t count);
    void advance(Iterator& first, Iterator last);

  private:
    class Node
    {
    public:
      T data_;
      Node *pNext_;
      // Node(T value) : data_(value), pNext_(nullptr) {}
      // Node(T value, Node *pointer) : data_(value), pNext_(pointer) {}
      Node(T value = T(), Node * pNext = nullptr) : data_(value), pNext_(pNext) {}
    };
    Node *begin_;
    size_t size_ = 0;
  };
}

template < typename T >
class mihalchenko::List< T >::ConstIterator : public std::iterator< std::forward_iterator_tag, T >
{
public:
  friend class List< T >;
  ConstIterator();
  // ConstIterator(Node *ind);
  ConstIterator(const ConstIterator &) = default;
  ~ConstIterator() = default;

  ConstIterator & operator=(const ConstIterator &) = default;

  ConstIterator &operator++();
  ConstIterator operator++(int);
  const T &operator*() const;
  const T *operator->() const;
  bool operator!=(const ConstIterator &rhs) const;
  bool operator==(const ConstIterator &rhs) const;

private:
  Node *node_;
  ConstIterator(Node * node);
};

template < typename T >
class mihalchenko::List< T >::Iterator : public std::iterator< std::forward_iterator_tag, T >
{
public:
  friend class List< T >;
  Iterator();
  Iterator(ConstIterator value);
  Iterator(const Iterator &) = default;
  ~Iterator() = default;

  Iterator & operator=(const Iterator &) = default;

  Iterator &operator++();
  Iterator operator++(int);
  T &operator*();
  T *operator->();
  bool operator==(const Iterator &rhs) const;
  bool operator!=(const Iterator &rhs) const;
  List< T > &operator+(size_t num);

private:
  ConstIterator constIter_;
};

template < typename T >
mihalchenko::List< T >::ConstIterator::ConstIterator() : node_(nullptr)
{}

template < typename T >
mihalchenko::List< T >::ConstIterator::ConstIterator(Node *node) : node_(node)
{}

template < typename T >
typename mihalchenko::List< T >::ConstIterator &mihalchenko::List< T >::ConstIterator::operator++()
{
  node_ = node_->pNext_;
  return *this;
}

template < typename T >
typename mihalchenko::List< T >::ConstIterator mihalchenko::List< T >::ConstIterator::operator++(int)
{
  ConstIterator result(*this);
  ++(*this);
  return result;
}

template < typename T >
const T &mihalchenko::List< T >::ConstIterator::operator*() const
{
  return node_->data_;
}

template < typename T >
const T *mihalchenko::List< T >::ConstIterator::operator->() const
{
  return std::addressof(node_->data_);
}

template < typename T >
bool mihalchenko::List< T >::ConstIterator::operator==(const ConstIterator &rhs) const
{
  return node_ == rhs.node_;
}

template < typename T >
bool mihalchenko::List< T >::ConstIterator::operator!=(const ConstIterator &rhs) const
{
  return !(rhs == *this);
}

template < typename T >
mihalchenko::List< T >::Iterator::Iterator() : constIter_(nullptr)
{}

template < typename T >
mihalchenko::List< T >::Iterator::Iterator(ConstIterator value) : constIter_(value)
{}

template < typename T >
typename mihalchenko::List< T >::Iterator &mihalchenko::List< T >::Iterator::operator++()
{
  ++constIter_;
  return *this;
}

template < typename T >
typename mihalchenko::List< T >::Iterator mihalchenko::List< T >::Iterator::operator++(int)
{
  constIter_++;
  return *this;
}

template < typename T >
T &mihalchenko::List< T >::Iterator::operator*()
{
  return constIter_.node_->data_;
}

template < typename T >
T *mihalchenko::List< T >::Iterator::operator->()
{
  return std::addressof(constIter_.node_->data_);
}

template < typename T >
bool mihalchenko::List< T >::Iterator::operator==(const Iterator &rhs) const
{
  return constIter_ == rhs.constIter_;
}

template < typename T >
bool mihalchenko::List< T >::Iterator::operator!=(const Iterator &rhs) const
{
  return !(rhs.constIter_ == constIter_);
}

template < typename T >
mihalchenko::List< T > &mihalchenko::List< T >::Iterator::operator+(size_t num)
{
  for (size_t i = 0; i < num; i++)
  {
    (*this)++;
  }
  return *this;
}

template < typename T >
typename mihalchenko::List< T >::ConstIterator mihalchenko::List< T >::cbegin() const noexcept
{
  return ConstIterator(begin_);
}

template < typename T >
typename mihalchenko::List< T >::ConstIterator mihalchenko::List< T >::cend() const noexcept
{
  return ConstIterator(nullptr);
}

template < typename T >
typename mihalchenko::List< T >::Iterator mihalchenko::List< T >::begin() noexcept
{
  return Iterator(begin_);
}

template < typename T >
typename mihalchenko::List< T >::Iterator mihalchenko::List< T >::end() noexcept
{
  return Iterator(nullptr);
}

template < typename T >
mihalchenko::List< T >::List()
{
  this->size_ = 0;
  begin_ = nullptr;
}

template < typename T >
mihalchenko::List< T >::List(size_t num)
{
  for (size_t i = 0; i < num; i++)
  {
    push_back(num);
  }
}

template < typename T >
mihalchenko::List< T >::List(size_t num, const T &value) : begin_(nullptr)
{
  for (size_t i = 0; i < num; i++)
  {
    push_back(value);
  }
}

template < typename T >
mihalchenko::List< T >::List(std::initializer_list< T > init_list)
{
  assign(init_list);
}

template < typename T >
mihalchenko::List< T >::List(const List< T > &copy)
{
  if (copy.begin_ == nullptr)
  {
    begin_ = nullptr;
  }
  else
  {
    begin_ = new Node(*copy.begin_);
  }
  size_ = copy.size_;
}

template < typename T >
mihalchenko::List< T > &mihalchenko::List< T >::operator=(const List &copy)
{
  if (this == &copy)
  {
    return *this;
  }
  size_ = copy.size_;
  clear();
  Node *pointer = copy.begin_;
  while (pointer)
  {
    push_back(pointer->data_);
    pointer = pointer->pNext_;
  }
  return *this;
}

template < typename T >
mihalchenko::List< T >::List(List< T > &&move)
{
  this->begin_ = move.begin_;
  move.begin_ = nullptr;
  this->size_ = move.size_;
  move.size_ = 0;
}

template < typename T >
mihalchenko::List< T > &mihalchenko::List< T >::operator=(List &&move)
{
  if (this == &move)
  {
    move.clear();
    return *this;
  }
  clear();
  List< T > temp = std::move(move);
  swap(temp);
  move.clear();
  return *this;
}

template < typename T >
mihalchenko::List< T >::~List()
{
  clear();
}

template < typename T >
void mihalchenko::List< T >::swap(List< T > &other) noexcept
{
  Node *temp = begin_;
  begin_ = other.begin_;
  other.begin_ = temp;
  size_t tempSize = this->size_;
  this->size_ = other.size_;
  other.size_ = tempSize;
}

template < typename T >
void mihalchenko::List< T >::push_front(const T &data)
{
  Node *newNode = new Node(data, begin_);
  begin_ = newNode;
  size_++;
}

template < typename T >
void mihalchenko::List< T >::push_back(const T &data)
{
  if (begin_ == nullptr)
  {
    begin_ = new Node(data);
    // size_ = 0;
  }
  else
  {
    Node *actual = begin_;
    while (actual->pNext_ != nullptr)
    {
      actual = actual->pNext_;
    }
    actual->pNext_ = new Node(data);
  }
  size_++;
}

template < typename T >
void mihalchenko::List< T >::pop_front()
{
  if (empty())
  {
    throw std::logic_error("Empty list!");
  }
  Node *temp = begin_;
  begin_ = begin_->pNext_;
  temp->pNext_ = nullptr;
  delete temp;
  size_--;
}

template < typename T >
void mihalchenko::List< T >::pop_back()
{
  if (size_ > 0)
  {
    erase(size_ - 1);
  }
  else
  {
    std::cerr << "StackEmptyException!\n";
  }
}

template < typename T >
void mihalchenko::List< T >::insert(T data, size_t index)
{
  if (index == 0)
  {
    push_front(data);
  }
  else
  {
    Iterator *previous = this->begin_;
    for (size_t i = 0; i < index - 1; i++)
    {
      previous = previous->pNext_;
    }
    Iterator *newIterator = new Iterator(data, previous->pNext_);
    previous->pNext_ = newIterator;
    size_++;
  }
}

template < typename T >
void mihalchenko::List< T >::erase(size_t index)
{
  if (index == 0)
  {
    pop_front();
  }
  else
  {
    Node *pointer = begin_;
    for (size_t i = 0; i < index - 1; i++)
    {
      pointer = pointer->pNext_;
    }
    Node *delPointer = pointer->pNext_;
    pointer->pNext_ = delPointer->pNext_;
    delete delPointer;
    size_--;
  }
}

template < typename T >
T &mihalchenko::List< T >::operator[](const size_t index)
{
  size_t c = 0;
  Node *actual = begin_;
  while (actual != nullptr)
  {
    if (c == index)
    {
      return actual->data_;
    }
    actual = actual->pNext_;
    c++;
  }
  throw std::out_of_range("Index out of range");
}

template < typename T >
void mihalchenko::List< T >::clear()
{
  while (size_)
  {
    pop_front();
  }
}

template < typename T >
bool mihalchenko::List< T >::empty() noexcept
{
  return (begin_ == nullptr);
}

template < typename T >
T &mihalchenko::List< T >::front()
{
  if (empty())
  {
    throw std::logic_error("List is empty!");
  }
  return begin_->data_;
}

template < typename T >
void mihalchenko::List< T >::assign(size_t count, const T &value)
{
  clear();
  for (size_t i = 0; i < count; i++)
  {
    push_back(value);
  }
}

template < typename T >
void mihalchenko::List< T >::assign(ConstIterator first, ConstIterator last)
{
  clear();
  while (first != last)
  {
    push_back(*first);
    first++;
  }
}

template < typename T >
void mihalchenko::List< T >::assign(std::initializer_list< T > init_list)
{
  clear();
  for (auto iter = init_list.begin(); iter != init_list.end(); ++iter)
  {
    push_back(*iter);
  }
}

template < typename T >
typename mihalchenko::List< T >::Iterator mihalchenko::List< T >::insert_after(Iterator position, const T &value)
{
  Node *newPosition = position.constIter_.node_;
  if (position == begin())
  {
    push_front(value);
    return Iterator(newPosition);
  }
  else
  {
    Node *newNode = new Node(value);
    newNode->pNext_ = newPosition->pNext_;
    newPosition->pNext_ = newNode;
    size_++;
    return Iterator(newNode);
  }
}

template < typename T >
typename mihalchenko::List< T >::Iterator mihalchenko::List< T >::insert_after(Iterator position, size_t count, const T &value)
{
  if (count == 0)
  {
    return Iterator(position);
  }
  for (size_t i = 0; i < count; ++i)
  {
    position = insert_after(position, value);
  }
  return Iterator(position);
}

template < typename T >
typename mihalchenko::List< T >::Iterator mihalchenko::List< T >::erase_after(Iterator position)
{
  if (position.constIter_.node_->pNext_)
  {
    Node * delElem = position.constIter_.node_->pNext_;
    position.constIter_.node_->pNext_ = position.constIter_.node_->pNext_->pNext_;
    delete delElem;
    size_--;
    return Iterator(position.constIter_.node_->pNext_);
  }
  return end();
}

template < typename T >
typename mihalchenko::List< T >::Iterator mihalchenko::List< T >::erase_after(Iterator first, Iterator last)
{
  Iterator newPosition = begin();
  if (first == last)
  {
    newPosition = last;
  }
  else
  {
    for (newPosition; newPosition != last; ++newPosition)
    {
      erase_after(first);
    }
  }
  return Iterator(newPosition);
}

template < typename T >
void mihalchenko::List< T >::splice(Iterator position, List &other)
{
  if (other.empty() == false)
  {
    Iterator pointer = other.begin();
    for (pointer = other.begin(); pointer != other.end(); ++pointer)
    {
      insert_after(position, *pointer);
      position++;
    }
    other.clear();
  }
}

template < typename T >
void mihalchenko::List< T >::reverse()
{
  if (begin_ && begin_->pNext_)
  {
    if (begin_->pNext_->pNext_ == nullptr)
    {
      Node * newfirst = begin_->pNext_;
      newfirst->pNext_ = begin_;
      begin_->pNext_ = nullptr;
      begin_ = newfirst;
      return;
    }
    else
    {
      bool flag = false;
      Node * prevNode = begin_;
      Node * currNode = begin_->pNext_;
      Node * tempNode = begin_->pNext_;
      Node * newBegin = nullptr;
      while (currNode != begin_)
      {
        while (tempNode->pNext_ != nullptr)
        {
          tempNode = tempNode->pNext_;
          prevNode = prevNode->pNext_;
        }
        if (!flag)
        {
          newBegin = tempNode;
          flag = true;
        }
        tempNode->pNext_ = prevNode;
        prevNode->pNext_ = nullptr;
        currNode = prevNode;
        prevNode = begin_;
        tempNode = begin_->pNext_;
      }
      if (newBegin != nullptr)
      {
        begin_ = newBegin;
      }
    }
  }
  return;
}

template < typename T >
void mihalchenko::List< T >::eraseAfter(Iterator iterator)
{
  Node *valueBegin = iterator.data_;
  Node *valueDel = valueBegin->pNext_;
  valueBegin->pNext_ = valueDel->pNext_;
  delete valueDel;
  size_--;
  iterator = begin_;
}

template < typename T >
void mihalchenko::List< T >::remove(const T &iterValue)
{
  for (auto iterator = begin(); iterator != end(); ++iterator)
  {
    if (iterator->pNext_ == iterValue && iterator->pNext_ != this->end_)
    {
      erase_after(iterator);
    }
    else if (*iterator == iterValue && *iterator == *begin_)
    {
      pop_front();
      iterator = begin_;
    }
  }
}

template < typename T >
template < typename F >
void mihalchenko::List< T >::remove_if(F functor)
{
  for (auto iterator = begin(); iterator != end(); ++iterator)
  {
    if (functor(*(iterator)))
    {
      remove(*iterator);
      iterator = begin_;
    }
  }
}

template< typename T >
void mihalchenko::List< T >::advance(Iterator& pos, size_t count)
{
  for (size_t i = 0; i < count; i++)
  {
    if (pos == end())
    {
      pos = end();
      break;
    }
    pos++;
  }
}

template< typename T >
void mihalchenko::List<T>::advance(Iterator& first, Iterator last)
{
  for (Iterator iter = first; iter != last; ++iter)
  {
    if (iter == end())
    {
      first = end();
      break;
    }
    first++;
  }
}

template <typename T>
size_t mihalchenko::List< T >::getSize()
{
  return size_;
}

template <typename T>
void mihalchenko::List< T >::setSize(const size_t size)
{
  size_ = size;
}

template < typename T >
T mihalchenko::List< T >::getT()
{
  return begin_->data_;
}

#endif
