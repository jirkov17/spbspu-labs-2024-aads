#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <memory>
#include "node.hpp"

namespace zheleznyakov
{
  template < typename T >
  class List
  {
  public:
    class Iterator;
    class ConstIterator;

    List();
    List(const List< T > &other);
    List(List &&other) noexcept;
    List(const size_t count, const T &value);
    ~List();
    List & operator=(const List< T >&other);
    void pushFront(const T &value);
    void pushBack(const T &value);
    size_t getSize() const noexcept;
    void popFront();
    void popBack();
    void clear();
    void swap(size_t index1, size_t index2) const;
    bool isEmpty() const noexcept;
    void assign(const size_t count, const T &value);
    void remove(size_t i);
    bool has(const T &value) const;
    template < typename UnaryPredicate >
    void removeIf(UnaryPredicate predicate);
    T &operator[](const size_t index) const;
    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator cBegin() const noexcept;
    ConstIterator cEnd() const noexcept;

  private:
    size_t size;
    details::Node< T > *head;
    details::Node< T > *tail;
  };

  template < typename T >
  class List< T >::Iterator
  {
  public:
    Iterator(details::Node< T > *list = nullptr);
    Iterator(const Iterator&) = default;
    ~Iterator() = default;

    Iterator &operator=(const Iterator&);

    Iterator &operator++();
    Iterator operator++(int);

    Iterator &operator--();
    Iterator operator--(int);

    T &operator*();
    T *operator->();

    bool operator!=(const Iterator &rhs) const;
    bool operator==(const Iterator &rhs) const;

  private:
    details::Node< T > *node_;
  };

  template < typename T >
  class List< T >::ConstIterator
  {
  public:
    ConstIterator(const details::Node< T > *list = nullptr);
    ConstIterator(const ConstIterator&) = default;
    ~ConstIterator() = default;

    ConstIterator &operator=(const Iterator&) const;

    ConstIterator &operator++();
    ConstIterator operator++(int);

    ConstIterator &operator--();
    ConstIterator operator--(int);

    T &operator*() const;
    T *operator->() const;

    bool operator!=(const ConstIterator &rhs) const;
    bool operator==(const ConstIterator &rhs) const;

  private:
    details::Node< T > *node_;
  };
};

template < typename T >
zheleznyakov::List< T >::List() : size(0), head(nullptr), tail(nullptr)
{
}

template < typename T >
zheleznyakov::List< T >::List(const List< T >&other) : size(other.size), head(nullptr), tail(nullptr)
{
  if (other.size > 0)
  {
    head = new details::Node< T >(other.head->value);
    tail = head;
    details::Node< T >*current = other.head;
    while (current->next != nullptr)
    {
      tail->next = new details::Node< T >(current->next->value);
      tail = tail->next;
      current = current->next;
    }
  }
}

template < typename T >
zheleznyakov::List< T > & zheleznyakov::List< T >::operator=(const List< T >&other)
{
  clear();
  if (other.size > 0)
  {
    head = new details::Node< T >(other.head->value);
    tail = head;
    details::Node< T >*current = other.head;
    while (current->next != nullptr)
    {
      tail->next = new details::Node< T >(current->next->value);
      tail = tail->next;
      current = current->next;
    }
  }
  return *this;
}

template < typename T >
zheleznyakov::List< T >::List(const size_t count, const T &value) : size(0), head(nullptr), tail(nullptr)
{
  for (size_t i = 0; i < count; i++)
  {
    pushBack(value);
  }
}

template < typename T >
zheleznyakov::List< T >::List(List &&other) noexcept:
  size{other.size},
  head{other.head},
  tail{other.tail}
{
  other.size = 0;
  other.head = nullptr;
  other.tail = nullptr;
}

template < typename T >
zheleznyakov::List< T >::~List()
{
  clear();
}

template < typename T >
size_t zheleznyakov::List< T >::getSize() const noexcept
{
  return size;
}

template < typename T >
void zheleznyakov::List< T >::pushFront(const T &value)
{
  details::Node< T >*newNode = new zheleznyakov::details::Node< T >(value);
  size++;
  if (head == nullptr)
  {
    head = newNode;
    tail = newNode;
    return;
  }
  newNode->next = this->head;
  head->prev = newNode;
  head = newNode;
}

template < typename T >
void zheleznyakov::List< T >::pushBack(const T &value)
{
  details::Node< T >*newNode = new zheleznyakov::details::Node< T >(value);
  size++;
  if (head == nullptr)
  {
    head = newNode;
    tail = newNode;
    return;
  }
  newNode->prev = this->tail;
  this->tail->next = newNode;
  this->tail = newNode;
}

template < typename T >
void zheleznyakov::List< T >::popFront()
{
  details::Node< T >*current = head;
  head = head->next;
  delete current;
  size--;
}

template < typename T >
void zheleznyakov::List< T >::popBack()
{
  details::Node< T >*current = tail;
  tail = tail->prev;
  delete current;
  size--;
}

template < typename T >
T &zheleznyakov::List< T >::operator[](const size_t index) const
{
  details::Node< T >*currentElement = head;
  size_t currentIndex = 0;
  while (currentElement != nullptr)
  {
    if (currentIndex == index)
    {
      return currentElement->value;
    }
    currentElement = currentElement->next;
    currentIndex++;
  }
  throw std::out_of_range("Out of range");
}

template < typename T >
void zheleznyakov::List< T >::clear()
{
  while (size != 0)
  {
    popFront();
  }
}

template < typename T >
bool zheleznyakov::List< T >::isEmpty() const noexcept
{
  return size == 0;
}

template < typename T >
void zheleznyakov::List< T >::swap(size_t index1, size_t index2) const
{
  zheleznyakov::details::Node< T > *currentItem1 = this->head;
  size_t currentIndex1 = 0;
  while (currentIndex1 < index1)
  {
    currentItem1 = currentItem1->next;
    ++currentIndex1;
  }
  zheleznyakov::details::Node< T > *currentItem2 = this->head;
  size_t currentIndex2 = 0;
  while (currentIndex2 < index2)
  {
    currentItem2 = currentItem2->next;
    ++currentIndex2;
  }
  std::swap(currentItem1, currentItem2);
}

template < typename T >
void zheleznyakov::List< T >::assign(const size_t count, const T &value)
{
  clear();
  for (size_t i = 0; i < count; i++)
  {
    pushBack(value);
  }
}

template < typename T >
void zheleznyakov::List< T >::remove(size_t i)
{
  details::Node< T >*current = head;
  for (size_t j = 0; j < i; j++)
  {
    current = current->next;
  }

  if (current->prev)
  {
    current->prev->next = current->next;
  }
  else
  {
    head = current->next;
  }

  if (current->next)
  {
    current->next->prev = current->prev;
  }
  else
  {
    tail = current->prev;
  }
}

template < typename T >
template < typename UnaryPredicate >
void zheleznyakov::List< T >::removeIf(UnaryPredicate predicate)
{
  details::Node< T >*current = head;
  while (current != nullptr)
  {
    details::Node< T >*next = current->next;
    if (predicate(current->value))
    {
      if (current->prev)
      {
        current->prev->next = current->next;
      }
      else
      {
        head = current->next;
      }

      if (current->next)
      {
        current->next->prev = current->prev;
      }
      else
      {
        tail = current->prev;
      }

      delete current;
      size--;
    }
    current = next;
  }
}

template < typename T >
zheleznyakov::List< T >::Iterator::Iterator(zheleznyakov::details::Node< T > *node):
  node_(node)
{};

template < typename T >
typename zheleznyakov::List< T >::Iterator &zheleznyakov::List< T >::Iterator::operator++()
{
  node_ = node_->next;
  return (*this);
}

template < typename T >
typename zheleznyakov::List< T >::Iterator zheleznyakov::List< T >::Iterator::operator++(int)
{
  List< T >::Iterator result(*this);
  ++(*this);
  return result;
}

template < typename T >
typename zheleznyakov::List< T >::Iterator &zheleznyakov::List< T >::Iterator::operator--()
{
  node_ = node_->prev;
  return (*this);
}

template < typename T >
typename zheleznyakov::List< T >::Iterator zheleznyakov::List< T >::Iterator::operator--(int)
{
  List< T >::Iterator result(*this);
  --(*this);
  return result;
}

template < typename T >
bool zheleznyakov::List< T >::Iterator::operator==(const List< T >::Iterator &rhs) const
{
  return node_ == rhs.node_;
}

template < typename T >
bool zheleznyakov::List< T >::Iterator::operator!=(const List< T >::Iterator &rhs) const
{
  return !(rhs == *this);
}

template < typename T >
T &zheleznyakov::List< T >::Iterator::operator*()
{
  return node_->value;
}

template < typename T >
T *zheleznyakov::List< T >::Iterator::operator->()
{
  return std::addressof(node_->data);
}

template< typename T >
typename zheleznyakov::List< T >::Iterator zheleznyakov::List< T >::begin() noexcept
{
  return this->head;
}

template< typename T >
typename zheleznyakov::List< T >::Iterator zheleznyakov::List< T >::end() noexcept
{
  return nullptr;
}


template < typename T >
zheleznyakov::List< T >::ConstIterator::ConstIterator(const zheleznyakov::details::Node< T > *node):
  node_(node)
{};

template < typename T >
typename zheleznyakov::List< T >::ConstIterator &zheleznyakov::List< T >::ConstIterator::operator++()
{
  node_ = node_->next;
  return (*this);
}

template < typename T >
typename zheleznyakov::List< T >::ConstIterator zheleznyakov::List< T >::ConstIterator::operator++(int)
{
  List< T >::Iterator result(*this);
  ++(*this);
  return result;
}

template < typename T >
typename zheleznyakov::List< T >::ConstIterator &zheleznyakov::List< T >::ConstIterator::operator--()
{
  node_ = node_->prev;
  return (*this);
}

template < typename T >
typename zheleznyakov::List< T >::ConstIterator zheleznyakov::List< T >::ConstIterator::operator--(int)
{
  List< T >::Iterator result(*this);
  --(*this);
  return result;
}

template < typename T >
bool zheleznyakov::List< T >::ConstIterator::operator==(const List< T >::ConstIterator &rhs) const
{
  return node_ == rhs.node_;
}

template < typename T >
bool zheleznyakov::List< T >::ConstIterator::operator!=(const List< T >::ConstIterator &rhs) const
{
  return !(rhs == *this);
}

template < typename T >
T &zheleznyakov::List< T >::ConstIterator::operator*() const
{
  return node_->value;
}

template < typename T >
T *zheleznyakov::List< T >::ConstIterator::operator->() const
{
  return std::addressof(node_->data);
}

template< typename T >
typename zheleznyakov::List< T >::ConstIterator zheleznyakov::List< T >::cBegin() const noexcept
{
  return this->head;
}

template< typename T >
typename zheleznyakov::List< T >::ConstIterator zheleznyakov::List< T >::cEnd() const noexcept
{
  return nullptr;
}

template <typename T>
bool zheleznyakov::List<T>::has(const T& value) const
{
  for (auto it = cBegin(); it != cEnd(); ++it) {
    if (*it == value) {
      return true;
    }
  }
  return false;
}
#endif
