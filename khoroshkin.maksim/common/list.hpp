#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <stdexcept>
#include <initializer_list>
#include <limits>
#include <memory>
#include <iterator>

namespace khoroshkin
{
  template< typename T >
  class List
  {
  public:
    class Iterator;
    class ConstIterator;

    using iterator = Iterator;
    using const_iterator = ConstIterator;

    List();
    List(size_t count, const T & value);
    template< typename Iter >
    List(Iter begin, Iter end);
    List(std::initializer_list< T > init);
    List(const List & obj);
    List(List && obj);
    ~List();

    List< T > & operator=(const List & obj);
    List< T > & operator=(List && obj);

    void push_back(const T & data);
    void push_front(const T & data);
    void pop_front();
    void clear();
    void swap(List< T > & other);
    void assign(size_t count, const T & value);
    void assign(const_iterator first, const_iterator last);
    void assign(std::initializer_list< T > ilist);
    iterator insert_after(iterator pos, const T & value);
    iterator insert_after(iterator pos, size_t count, const T & value);
    iterator erase_after(iterator pos);
    iterator erase_after(iterator first, iterator last);
    template< class... Args >
    iterator emplace_after(iterator pos, Args &&... args);

    T & front();
    size_t getSize() const;
    bool isEmpty() const;
    T & operator[](const size_t index);
    void reverse();
    void splice_after(iterator pos, List< T > & other);
    void remove(const T & value, bool onlyFirst = false);
    template< typename UnaryPredicate >
    void remove_if(UnaryPredicate p);
    void unique();
    void sort();
    void merge(List< T > & other);

    bool operator==(List< T > & rhs);
    bool operator!=(List< T > & rhs);
    bool operator<(List< T > & rhs);
    bool operator>(List< T > & rhs);
    bool operator<=(List< T > & rhs);
    bool operator>=(List< T > & rhs);

    iterator begin() const noexcept;
    iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    iterator next(iterator it);
  private:
    size_t size;
    class Node
    {
    public:
      friend class List< T >;
      Node(T data = T(), Node * pNext = nullptr) :
        data(data), pNext(pNext)
      {}
    private:
      T data;
      Node * pNext;
    };
    Node * head;
  };
}

template< typename T >
class khoroshkin::List< T >::ConstIterator : public std::iterator<std::forward_iterator_tag, T>
{
  public:
    friend class List< T >;
    using this_t = ConstIterator;

    ConstIterator();
    ConstIterator(const this_t&) = default;
    ~ConstIterator() = default;

    this_t & operator=(const this_t &) = default;
    this_t & operator++();
    this_t operator++(int);

    const T & operator*() const;
    const T * operator->() const;

    bool operator!=(const this_t & rhs) const;
    bool operator==(const this_t & rhs) const;

  private:
    Node * node_;
    ConstIterator(Node * node);
};

template< typename T >
khoroshkin::List< T >::ConstIterator::ConstIterator() :
  node_(nullptr)
{}

template< typename T >
khoroshkin::List< T >::ConstIterator::ConstIterator(Node * node) :
  node_(node)
{}

template< typename T >
typename khoroshkin::List< T >::ConstIterator::this_t & khoroshkin::List< T >::ConstIterator::operator++()
{
  node_ = node_->pNext;
  return *this;
}

template< typename T >
typename khoroshkin::List< T >::ConstIterator::this_t khoroshkin::List< T >::ConstIterator::operator++(int)
{
  this_t result(*this);
  ++(*this);
  return result;
}

template< typename T >
const T & khoroshkin::List< T >::ConstIterator::operator*() const
{
  return node_->data;
}

template< typename T >
const T * khoroshkin::List< T >::ConstIterator::operator->() const
{
  return std::addressof(node_->data);
}

template< typename T >
bool khoroshkin::List< T >::ConstIterator::operator!=(const this_t & rhs) const
{
  return !(rhs == *this);
}

template< typename T >
bool khoroshkin::List< T >::ConstIterator::operator==(const this_t & rhs) const
{
  return node_ == rhs.node_;
}

template< typename T >
class khoroshkin::List< T >::Iterator : public std::iterator<std::forward_iterator_tag, T>
{
  public:
    friend class List< T >;
    using this_t = Iterator;
    Iterator();
    Iterator(ConstIterator iter);
    Iterator(const this_t &) = default;
    ~Iterator() = default;

    this_t & operator=(const this_t &) = default;
    this_t & operator++();
    this_t operator++(int);

    T & operator*();
    T * operator->();
    const T & operator*() const;
    const T * operator->() const;

    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;

  private:
    ConstIterator iter_;
};

template< typename T >
khoroshkin::List< T >::Iterator::Iterator() :
  iter_(ConstIterator())
{}

template< typename T >
khoroshkin::List< T >::Iterator::Iterator(ConstIterator iter) :
  iter_(iter)
{}

template< typename T >
typename khoroshkin::List< T >::Iterator::this_t & khoroshkin::List< T >::Iterator::operator++()
{
  ++iter_;
  return *this;
}

template< typename T >
typename khoroshkin::List< T >::Iterator::this_t khoroshkin::List< T >::Iterator::operator++(int)
{
  this_t result = iter_;
  ++iter_;
  return result;
}

template< typename T >
T & khoroshkin::List< T >::Iterator::operator*()
{
  return iter_.node_->data;
}

template< typename T >
T * khoroshkin::List< T >::Iterator::operator->()
{
  return std::addressof(iter_.node_->data);
}

template< typename T >
const T & khoroshkin::List< T >::Iterator::operator*() const
{
  return iter_.node_->data;
}

template< typename T >
const T * khoroshkin::List< T >::Iterator::operator->() const
{
  return std::addressof(iter_.node_->data);
}

template< typename T >
bool khoroshkin::List< T >::Iterator::operator!=(const this_t & rhs) const
{
  return !(rhs == *this);
}

template< typename T >
bool khoroshkin::List< T >::Iterator::operator==(const this_t & rhs) const
{
  return iter_ == rhs.iter_;
}

template< typename T >
khoroshkin::List< T >::List() :
  size(0), head(nullptr)
{}

template< typename T >
khoroshkin::List< T >::List(size_t count, const T & value)
{
  for (size_t i = 0; i < count; ++i)
  {
    this->push_back(value);
  }
}

template< typename T >
template< typename Iter >
khoroshkin::List< T >::List(Iter begin, Iter end) :
  size(0), head(nullptr)
{
  for (;begin != end; begin++)
  {
    push_back(*begin);
  }
}

template< typename T >
khoroshkin::List< T >::List(std::initializer_list< T > init)
{
  for (auto it = init.begin(); it != init.end(); ++it)
  {
    this->push_back(*it);
  }
}

template< typename T >
khoroshkin::List< T >::List(const khoroshkin::List< T > & obj)
{
  if (obj.head == nullptr)
  {
    head = nullptr;
  }
  else
  {
    for (auto it = obj.begin(); it != obj.end(); it++)
    {
      push_back(*it);
    }
  }
  size = obj.size;
}

template< typename T >
khoroshkin::List< T > & khoroshkin::List< T >::operator=(const List & obj)
{
  if (this != &obj)
  {
    clear();
    Node * temp = obj.head;
    while (temp)
    {
      push_back(temp->data);
      temp = temp->pNext;
    }
  }
  return *this;
}

template< typename T >
khoroshkin::List< T >::List(khoroshkin::List< T > && obj)
{
  size = std::move(obj.size);
  head = std::move(obj.head);
  obj.head = nullptr;
  obj.size = 0;
}

template< typename T >
khoroshkin::List< T > & khoroshkin::List< T >::operator=(List && obj)
{
  if (this != &obj)
  {
    clear();
    Node * temp = obj.head;
    while (temp)
    {
      push_back(obj.head->data);
      temp = temp->pNext;
    }
  }
  this->size = obj.size;
  obj.clear();
  return *this;
}

template< typename T >
void khoroshkin::List< T >::assign(size_t count, const T & value)
{
  this->clear();
  for (size_t i = 0; i < count; ++i)
  {
    this->push_back(value);
  }
}

template< typename T >
void khoroshkin::List< T >::assign(const_iterator first, const_iterator last)
{
  this->clear();
  while (first != last)
  {
    this->push_back(*first);
    first++;
  }
}

template< typename T >
void khoroshkin::List< T >::assign(std::initializer_list< T > ilist)
{
  this->clear();
  for (auto it = ilist.begin(); it != ilist.end(); ++it)
  {
    this->push_back(*it);
  }
}

template< typename T >
void khoroshkin::List< T >::push_back(const T & data)
{
  if (head == nullptr)
  {
      head = new Node(data);
  }
  else
  {
    Node * current = this->head;
    while (current->pNext != nullptr)
    {
      current = current->pNext;
    }
    current->pNext = new Node(data);
  }
  size++;
}

template< typename T >
void khoroshkin::List< T >::push_front(const T & data)
{
  if (head == nullptr)
  {
      head = new Node(data);
  }
  else
  {
    Node * current = new Node(data);
    current->pNext = head;
    head = current;
  }
  size++;
}

template< typename T >
typename khoroshkin::List< T >::iterator khoroshkin::List< T >::next(iterator it)
{
  return ++it;
}

template< typename T >
T & khoroshkin::List< T >::operator[](const size_t index)
{
  size_t counter = 0;
  Node * current = this->head;
  while (current != nullptr)
  {
    if (counter == index)
    {
      return current->data;
    }
    current = current->pNext;
    counter++;
  }
  throw std::out_of_range("Index out of range");
}

template< typename T >
void khoroshkin::List< T >::pop_front()
{
  Node * temp = head;
  head = head->pNext;
  delete temp;
  size--;
}

template< typename T >
T & khoroshkin::List< T >::front()
{
  return head->data;
}

template< typename T >
void khoroshkin::List< T >::clear()
{
  while (size)
  {
    pop_front();
  }
}

template < typename T >
size_t khoroshkin::List< T >::getSize() const
{
  return size;
}

template< typename T >
bool khoroshkin::List< T >::isEmpty() const
{
  return !head;
}

template < typename T >
khoroshkin::List< T >::~List()
{
  clear();
}

template< typename T >
void khoroshkin::List< T >::swap(khoroshkin::List< T > & other)
{
  Node * tempH = this->head;
  this->head = other.head;
  other.head = tempH;

  size_t tempS = this->size;
  this->size = other.size;
  other.size = tempS;
}

template< typename T >
typename khoroshkin::List< T >::iterator khoroshkin::List< T >::begin() const noexcept
{
  if (isEmpty())
  {
    return end();
  }
  return ConstIterator(this->head);
}

template< typename T >
typename khoroshkin::List< T >::iterator khoroshkin::List< T >::end() const noexcept
{
  return ConstIterator(nullptr);
}

template< typename T >
typename khoroshkin::List< T >::const_iterator khoroshkin::List< T >::cbegin() const noexcept
{
  if (isEmpty())
  {
    return end();
  }
  return ConstIterator(this->head);
}

template< typename T >
typename khoroshkin::List< T >::const_iterator khoroshkin::List< T >::cend() const noexcept
{
  return ConstIterator(nullptr);
}

template< typename T >
void khoroshkin::List< T >::remove(const T & value, bool onlyFirst)
{
  for (auto it = this->begin(); it != this->end(); ++it)
  {
    if (*it == value && *it == *this->begin())
    {
      this->pop_front();
      it = this->begin();
      if (onlyFirst)
      {
        break;
      }
    }
    else if (next(it) != this->end() && *next(it) == value)
    {
      Node * subhead = it.iter_.node_;
      Node * todelete = subhead->pNext;
      subhead->pNext = todelete->pNext;
      delete todelete;
      this->size--;
      it = this->begin();
      if (onlyFirst)
      {
        break;
      }
    }
  }
}

template< typename T >
template< typename UnaryPredicate >
void khoroshkin::List< T >::remove_if(UnaryPredicate p)
{
  for (auto it = this->begin(); it != this->end(); ++it)
  {
    if (p(*it))
    {
      remove(*it);
      it = this->begin();
    }
  }
}

template< typename T >
typename khoroshkin::List< T >::iterator khoroshkin::List< T >::insert_after(iterator pos, const T & value)
{
  Node * subhead = pos.iter_.node_;
  Node * newNode = new Node(value);
  newNode->pNext = subhead->pNext;
  subhead->pNext = newNode;
  size++;
  return newNode;
}

template< typename T >
typename khoroshkin::List< T >::iterator khoroshkin::List< T >::insert_after(iterator pos, size_t count, const T & value)
{
  if (count == 0)
  {
    return pos;
  }
  for (size_t i = 0; i < count; ++i)
  {
    pos = insert_after(pos, value);
  }
  return pos;
}

template< typename T >
typename khoroshkin::List< T >::iterator khoroshkin::List< T >::erase_after(iterator pos)
{
  if (pos.iter_.node_->pNext)
  {
    Node * todelete = pos.iter_.node_->pNext;
    pos.iter_.node_->pNext = pos.iter_.node_->pNext->pNext;
    delete todelete;
    size--;
    return Iterator(pos.iter_.node_->pNext);
  }
  else
  {
    pop_front();
  }
  return this->end();
}

template< typename T >
typename khoroshkin::List< T >::iterator khoroshkin::List< T >::erase_after(iterator first, iterator last)
{
  while (next(first) != last)
  {
    erase_after(first);
  }
  return last;
}

template< typename T >
void khoroshkin::List< T >::reverse()
{
  List< T > temp;
  auto it = this->begin();
  while (it != this->end())
  {
    if (this->next(it) != this->end() && next(it).node->pNext == nullptr)
    {
      temp.push_back(*next(it));
      this->erase_after(it);
      if (this->getSize() != 1)
      {
        it = this->begin();
      }
    }
    if (this->getSize() == 1)
    {
      temp.push_back(*(this->begin()));
    }
    if (this->getSize() != 2)
    {
      it++;
    }
  }
  this->assign(temp.begin(), temp.end());
}

template< typename T >
void khoroshkin::List< T >::splice_after(iterator pos, khoroshkin::List< T > & other)
{
  for (auto it = other.begin(); it != other.end(); ++it)
  {
    this->insert_after(pos, *it);
    pos++;
  }
}

template< typename T >
void khoroshkin::List< T >::unique()
{
  auto it = this->begin();
  while (it != this->end())
  {
    if (next(it) != this->end() && *next(it) == *it)
    {
      this->erase_after(it);
      it = this->begin();
    }
    it++;
  }
}

template< typename T >
bool khoroshkin::List< T >::operator==(khoroshkin::List< T > & rhs)
{
  if (this->getSize() != rhs.getSize())
  {
    return false;
  }
  auto itThis = this->begin();
  auto itRhs = rhs.begin();
  while (itThis != this->end())
  {
    if (*itThis != *itRhs)
    {
      return false;
    }
    itThis++;
    itRhs++;
  }
  return true;
}

template< typename T >
bool khoroshkin::List< T >::operator!=(khoroshkin::List< T > & rhs)
{
  return !(*this == rhs);
}

template< typename T >
bool khoroshkin::List< T >::operator<(khoroshkin::List< T > & rhs)
{
  auto itThis = this->begin();
  auto itRhs = rhs.begin();
  while (itThis != this->end() && itRhs != rhs.end())
  {
    if (*itThis < *itRhs)
    {
      return true;
    }
    itThis++;
    itRhs++;
  }
  if (this->getSize() < rhs.getSize())
  {
    return true;
  }
  return false;
}

template< typename T >
bool khoroshkin::List< T >::operator>(khoroshkin::List< T > & rhs)
{
  auto itThis = this->begin();
  auto itRhs = rhs.begin();
  while (itThis != this->end() && itRhs != rhs.end())
  {
    if (*itThis > *itRhs)
    {
      return true;
    }
    itThis++;
    itRhs++;
  }
  if (this->getSize() > rhs.getSize())
  {
    return true;
  }
  return false;
}

template< typename T >
bool khoroshkin::List< T >::operator>=(khoroshkin::List< T > & rhs)
{
  return !(*this < rhs);
}

template< typename T >
bool khoroshkin::List< T >::operator<=(khoroshkin::List< T > & rhs)
{
  return !(*this > rhs);
}

template< typename T >
void khoroshkin::List< T >::sort()
{
  List< T > temp;
  while (this->getSize())
  {
    T minValue = std::numeric_limits< T >::max();
    for (auto it = this->begin(); it != this->end(); ++it)
    {
      if (*it < minValue)
      {
        minValue = *it;
      }
    }
    temp.push_back(minValue);
    this->remove(minValue, true);
  }
  this->assign(temp.begin(), temp.end());
}

template< typename T >
void khoroshkin::List< T >::merge(khoroshkin::List< T > & other)
{
  if (*this == other)
  {
    return;
  }
  for (auto it = other.begin(); it != other.end(); ++it)
  {
    this->push_back(*it);
  }
  this->sort();
  other.clear();
}

template< typename T >
template< class... Args >
typename khoroshkin::List< T >::iterator khoroshkin::List< T >::emplace_after(iterator pos, Args &&... args)
{
  return insert_after(pos, std::forward< Args >(args)...);
}

#endif
