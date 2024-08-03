#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <cassert>
#include <memory>
#include <initializer_list>
#include "Node.hpp"

namespace sukacheva {
  template < typename  T >
  class List
  {
  public:
    class Iterator;
    class ConstIterator;

    List();
    List(size_t count, const T& value);
    List(std::initializer_list< T > init);
    template< class InputIt >
    List(InputIt first, InputIt last);
    List(const List&);
    List(List&& other);
    ~List();

    Iterator operator[](size_t index);

    void pushFront(const T& data);
    void pushBack(const T& data);
    void popFront();
    void clean() noexcept;
    void swap(List& other) noexcept;
    bool empty() const noexcept;
    T& front() const noexcept;
    T& back() const noexcept;
    size_t getSize() noexcept;
    void reverse();
    void remove(const T& value);
    template< class UnaryPredicate >
    void remove_if(UnaryPredicate p);
    void assign(size_t count, const T& value);
    template< class InputIt >
    void assign(InputIt first, InputIt last);
    void assign(std::initializer_list< T > ilist);
    void splice(Iterator position, List& fwdlst);
    ConstIterator insert(ConstIterator position, const T& val);
    Iterator erase_after(ConstIterator pos);

    Iterator begin() const;
    Iterator end() const;

    ConstIterator cbegin() const;
    ConstIterator cend() const;

    List& operator=(const List& other) = default;
    List& operator=(List&& other) noexcept = default;
  private:

    details::Node< T >* head;
    details::Node< T >* tail;
    size_t listSize;
  };

  template < typename T >
  class List< T >::Iterator : public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    friend class List;
    Iterator();
    Iterator(sukacheva::details::Node< T >* node_);
    ~Iterator() = default;
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;

    Iterator& operator++();
    Iterator operator++(int);

    T& operator*();
    T* operator->();

    bool operator!=(const Iterator&) const;
    bool operator==(const Iterator&) const;
  private:
    sukacheva::details::Node< T >* node;
  };

  template < typename T >
  class List< T >::ConstIterator : public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    friend class List;
    ConstIterator();
    ConstIterator(sukacheva::details::Node< T >* node_);
    ~ConstIterator() = default;
    ConstIterator(const ConstIterator&) = default;
    ConstIterator& operator=(const ConstIterator&) = default;

    ConstIterator& operator++();
    ConstIterator operator++(int);

    const T& operator*() const;
    const T* operator->() const;

    bool operator!=(const ConstIterator& rhs) const;
    bool operator==(const ConstIterator& rhs) const;
  private:
    sukacheva::details::Node< T >* node;
  };
}

template< typename T >
const T& sukacheva::List< T >::ConstIterator::operator*() const
{
  assert(node != nullptr);
  return node->data;
}

template< typename T >
const T* sukacheva::List< T >::ConstIterator::operator->() const
{
  assert(node != nullptr);
  return std::addressof(node->data);
}

template< typename T >
size_t sukacheva::List< T >::getSize() noexcept
{
  return listSize;
}

template< typename T >
T& sukacheva::List< T >::back() const noexcept
{
  return tail->data;
}

template< typename T >
typename sukacheva::List< T >::Iterator sukacheva::List< T >::erase_after(ConstIterator pos)
{
  sukacheva::details::Node< T >* node = pos.node->next;
  Iterator it = node->next;
  pos.node->next = node->next;
  node->next = nullptr;
  return it;
}

template< typename T >
sukacheva::List< T >::Iterator::Iterator():
  node(nullptr)
{}

template< typename T >
sukacheva::List< T >::Iterator::Iterator(sukacheva::details::Node< T >* node_):
  node(node_)
{}

template< typename T >
sukacheva::List< T >::ConstIterator::ConstIterator():
  node(nullptr)
{}

template< typename T >
sukacheva::List< T >::ConstIterator::ConstIterator(sukacheva::details::Node< T >* node_):
  node(node_)
{}

template< typename T >
typename sukacheva::List< T >::ConstIterator sukacheva::List< T >::insert(ConstIterator position, const T& val)
{
  sukacheva::details::Node< T >* node = new sukacheva::details::Node< T >(val);
  ConstIterator constIt = node;
  node->next = position.node->next;
  position.node->next = node;
  return constIt++;
}

template< typename T >
sukacheva::List< T >::List():
  head(nullptr),
  tail(nullptr),
  listSize(0) {}

template< typename T >
void sukacheva::List< T >::splice(Iterator position, List& fwdlst)
{
  while (position.node)
  {
    insert(position, position.node->data);
  }
}

template< typename T >
void sukacheva::List< T >::assign(std::initializer_list<T> ilist)
{
  clean();
  Iterator it = ilist.begin();
  while (it) {
    pushBack(it.node->data);
    it++;
  }
}

template< typename T >
template< typename InputIt>
void sukacheva::List< T >::assign(InputIt first, InputIt last)
{
  clean();
  while (first != last) {
    pushBack(first);
    first++;
  }
}

template< typename T >
void sukacheva::List< T >::assign(size_t count, const T& value)
{
  clean();
  for (size_t i = 0; i != count; ++i) {
    pushBack(value);
  }
}

template< typename T >
template< typename UnaryPredicate>
void sukacheva::List< T >::remove_if(UnaryPredicate p)
{
  size_t index = 0;
  Iterator it = begin();
  while (it.node)
  {
    if (p(*it)) {
      if (it == begin()) {
        it++;
        head = this->operator[](index + 1).node;
        listSize--;
      }
      else {
        it++;
        this->operator[](index - 1).node->next = this->operator[](index + 1).node;
        listSize--;
      }
    }
    else {
      index++;
      it++;
    }
  }
}

template< typename T >
void sukacheva::List< T >::remove(const T& value)
{
  size_t index = 0;
  Iterator it = begin();
  while (it.node)
  {
    if (*it == value) {
      if (it == begin()) {
        it++;
        head = this->operator[](index + 1).node;
        listSize--;
      }
      else {
        it++;
        this->operator[](index - 1).node->next = this->operator[](index + 1).node;
        listSize--;
      }
    }
    else {
      index++;
      it++;
    }
  }
}

template< typename T >
void sukacheva::List< T >::reverse()
{
  size_t tempSize = listSize;
  for (size_t i = tempSize - 1; i != -1; i--)
  {
    pushBack(this->operator[](i));
  }
  for (size_t i = 0; i != tempSize; i++)
  {
    popFront();
  }
}

template< typename T >
T& sukacheva::List< T >::front() const noexcept
{
  return head->data;
}

template< typename T >
typename sukacheva::List< T >::Iterator sukacheva::List< T >::operator[](size_t index)
{
  Iterator it = begin();
  for (size_t i = 0; i != index; i++) {
    if (it == nullptr) {
      return nullptr;
    }
    it++;
  }
  return it.node;
}

template< typename T >
void sukacheva::List< T >::pushBack(const T& data)
{
  sukacheva::details::Node< T >* newNode = new sukacheva::details::Node< T >(data);
  if (empty()) {
    head = newNode;
    tail = newNode;
  }
  else {
    tail->next = newNode;
    tail = newNode;
  }
  listSize++;
}

template< typename T >
void sukacheva::List< T >::pushFront(const T& data)
{
  sukacheva::details::Node< T >* newNode = new sukacheva::details::Node< T >(data);
  if (empty()) {
    head = newNode;
    tail = newNode;
  }
  else {
    newNode->next = head;
    head = newNode;
  }
  listSize++;
}

template< typename T >
void sukacheva::List< T >::popFront() {
  sukacheva::details::Node< T >* front = head;
  Iterator it = begin();
  if (it != nullptr)
  {
    head = front->next;
  }
  else {
    head = nullptr;
    tail = nullptr;
  }
  delete front;
  listSize--;
}

template< typename T >
bool sukacheva::List< T >::empty() const noexcept
{
  return (head == nullptr);
}

template< typename T >
void sukacheva::List< T >::clean() noexcept
{
  while (head)
  {
    popFront();
  }
}

template< typename T >
void sukacheva::List< T >::swap(List& other) noexcept
{
  sukacheva::details::Node< T >* temp_head = head;
  sukacheva::details::Node< T >* temp_tail = tail;
  size_t tempSize = other.listSize;
  other.listSize = listSize;
  listSize = tempSize;
  head = other.head;
  tail = other.tail;
  other.head = temp_head;
  other.tail = temp_tail;
  delete temp_head;
  delete temp_tail;
}

template< typename T >
sukacheva::List< T >::~List()
{
  clean();
}

template< typename T >
sukacheva::List< T >::List(const List&) :
  head(nullptr),
  tail(nullptr),
  listSize(0)
{
  Iterator it = begin();
  while (it.node) {
    this->pushBack(it.node->data);
    ++it;
  }
}

template< typename T >
sukacheva::List< T >::List(List&& other):
  head(other.head),
  tail(other.tail),
  listSize(other.listSize)
{
  other.head = nullptr;
  other.tail = nullptr;
  other.listSize = 0;
}

template< typename T >
sukacheva::List< T >::List(size_t count, const T& value) : List()
{
  for (size_t i = 0; i != count; ++i) {
    pushBack(value);
  }
}

template< typename T >
sukacheva::List< T >::List(std::initializer_list<T> init) : List()
{
  Iterator it = init.begin();
  while (it) {
    pushBack(it.node->data);
    it++;
  }
}

template< typename T >
template< typename InputIt >
sukacheva::List< T >::List(InputIt first, InputIt last) : List()
{
  while (first != last) {
    pushBack(first);
    first++;
  }
}

template< typename T >
typename sukacheva::List< T >::Iterator sukacheva::List< T >::begin() const
{
  return Iterator(head);
}

template< typename T >
typename sukacheva::List< T >::Iterator sukacheva::List< T >::end() const
{
  return Iterator(nullptr);
}

template< typename T >
typename sukacheva::List< T >::ConstIterator sukacheva::List< T >::cbegin() const
{
  return ConstIterator(head);
}

template< typename T >
typename sukacheva::List< T >::ConstIterator sukacheva::List< T >::cend() const
{
  return ConstIterator(nullptr);
}

template< typename T >
typename sukacheva::List< T >::ConstIterator& sukacheva::List< T >::ConstIterator::operator++()
{
  node = node->next;
  return *this;
}

template< typename T >
typename sukacheva::List< T >::ConstIterator sukacheva::List< T >::ConstIterator::operator++(int)
{
  ConstIterator result(*this);
  ++(*this);
  return result;
}

template< typename T >
bool sukacheva::List< T >::ConstIterator::operator==(const ConstIterator& rhs) const {
  return node == rhs.node;
}

template< typename T >
bool sukacheva::List< T >::ConstIterator::operator!=(const ConstIterator& rhs) const {
  return !(rhs == *this);
}

template< typename T >
typename sukacheva::List< T >::Iterator& sukacheva::List< T >::Iterator::operator++()
{
  node = node->next;
  return *this;
}

template< typename T >
typename sukacheva::List< T >::Iterator sukacheva::List< T >::Iterator::operator++(int) {
  Iterator result(*this);
  ++(*this);
  return result;
}

template< typename T >
bool sukacheva::List< T >::Iterator::operator==(const Iterator& rhs) const {
  return node == rhs.node;
}

template< typename T >
bool sukacheva::List< T >::Iterator::operator!=(const Iterator& rhs) const {
  return !(rhs == *this);
}

template< typename T >
T& sukacheva::List< T >::Iterator::operator*()
{
  assert(node != nullptr);
  return node->data;
}

template< typename T >
T* sukacheva::List< T >::Iterator::operator->() {
  assert(node != nullptr);
  return std::addressof(node->data);
}

#endif
