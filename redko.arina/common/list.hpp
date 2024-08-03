#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <stdexcept>
#include <memory>
#include <cassert>
#include <iterator>

namespace redko
{
  template< typename T >
  class List
  {
  public:
    class Iterator;
    class ConstIterator;

    using iterator = Iterator;
    using const_iterator = ConstIterator;

    List(): head_() {};
    List(size_t count, const T & value);
    List(size_t count);
    List(iterator first, iterator last);
    List(const List & other);
    List(List && other) noexcept;
    List(std::initializer_list< T > ilist);
    ~List();

    List< T > & operator=(const List & other);
    List< T > & operator=(List && other);

    void assign(size_t count, const T & value);
    void assign(iterator first, iterator last);
    void assign(std::initializer_list< T > ilist);

    T & front();

    iterator beforeBegin() noexcept;
    const_iterator beforeBegin() const noexcept;
    const_iterator cbeforeBegin() const noexcept;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    bool isEmpty() const noexcept;

    void clear();
    iterator insertAfter(const_iterator pos, const T & value);
    iterator insertAfter(const_iterator pos, T && value);
    template< class... Args >
    iterator emplaceAfter(const_iterator pos, Args &&... args);
    iterator eraseAfter(const_iterator pos);
    void pushFront(const T & value);
    void pushFront(T && value);
    void pushBack(const T & value);
    void pushBack(T && value);
    void popFront();
    void swap(List & other) noexcept;

    void merge(List & other);
    void merge(List && other);
    void spliceAfter(iterator pos, List & other);
    void spliceAfter(iterator pos, List && other);
    size_t remove(const T & value);
    template< typename UnaryPredicate >
    size_t removeIf(UnaryPredicate pred);
    void reverse() noexcept;
    size_t unique();
    void sort();

    bool operator==(const List & rhs);
    bool operator!=(const List & rhs);
    bool operator<(const List & rhs);
    bool operator<=(const List & rhs);
    bool operator>(const List & rhs);
    bool operator>=(const List & rhs);

  private:
    struct ListElem
    {
      ListElem():
        data(),
        next(nullptr)
      {}
      explicit ListElem(const T & d):
        data(d),
        next(nullptr)
      {}
      T data;
      ListElem * next;
    };
    ListElem head_;
  };
}

template< typename T >
class redko::List< T >::Iterator: public std::iterator< std::forward_iterator_tag, T >
{
public:
  friend class List< T >;
  using this_t = Iterator;
  Iterator();
  Iterator(ConstIterator);
  Iterator(const this_t &) = default;
  ~Iterator() = default;

  this_t & operator=(const this_t &) = default;
  this_t & operator++();
  this_t operator++(int);

  T & operator*();
  T * operator->();
  const T & operator*() const;
  const T * operator->() const;

  bool operator!=(const this_t &) const;
  bool operator==(const this_t &) const;

private:
  ListElem * node_;
  Iterator(ListElem * ptr);
};

template< typename T >
redko::List< T >::Iterator::Iterator():
  node_(nullptr)
{}
template< typename T >
redko::List< T >::Iterator::Iterator(ConstIterator iter):
  node_(iter.iter_.node_)
{}
template< typename T >
redko::List< T >::Iterator::Iterator(ListElem * ptr):
  node_(ptr)
{}
template< typename T >
typename redko::List< T >::Iterator & redko::List< T >::Iterator::operator++()
{
  assert(node_ != nullptr);
  node_ = node_->next;
  return *this;
}
template< typename T >
typename redko::List< T >::Iterator redko::List< T >::Iterator::operator++(int)
{
  assert(node_ != nullptr);
  Iterator result(*this);
  ++(*this);
  return result;
}
template< typename T >
T & redko::List< T >::Iterator::operator*()
{
  return node_->data;
}
template< typename T >
const T & redko::List< T >::Iterator::operator*() const
{
  return node_->data;
}
template< typename T >
T * redko::List< T >::Iterator::operator->()
{
  return std::addressof(node_->data);
}
template< typename T >
const T * redko::List< T >::Iterator::operator->() const
{
  return std::addressof(node_->data);
}
template< typename T >
bool redko::List< T >::Iterator::operator==(const this_t & rhs) const
{
  return node_ == rhs.node_;
}
template< typename T >
bool redko::List< T >::Iterator::operator!=(const this_t & rhs) const
{
  return !(rhs == *this);
}

template< typename T >
class redko::List< T >::ConstIterator: public std::iterator< std::forward_iterator_tag, T >
{
public:
  friend class List< T >;
  using this_t = ConstIterator;

  ConstIterator();
  ConstIterator(Iterator);
  ConstIterator(const this_t &) = default;
  ~ConstIterator() = default;

  this_t & operator=(const this_t &) = default;
  this_t & operator++();
  this_t operator++(int);

  const T & operator*() const;
  const T * operator->() const;

  bool operator==(const this_t &) const;
  bool operator!=(const this_t &) const;

private:
  Iterator iter_;
};

template< typename T >
redko::List< T >::ConstIterator::ConstIterator():
  iter_(Iterator())
{}
template< typename T >
redko::List< T >::ConstIterator::ConstIterator(Iterator iter):
  iter_(iter)
{}
template< typename T >
typename redko::List< T >::ConstIterator & redko::List< T >::ConstIterator::operator++()
{
  ++iter_;
  return *this;
}
template< typename T >
typename redko::List< T >::ConstIterator redko::List< T >::ConstIterator::operator++(int)
{
  ConstIterator result(iter_);
  ++(iter_);
  return result;
}
template< typename T >
const T & redko::List< T >::ConstIterator::operator*() const
{
  return *iter_;
}
template< typename T >
const T * redko::List< T >::ConstIterator::operator->() const
{
  return std::addressof(iter_.node_->data);
}
template< typename T >
bool redko::List< T >::ConstIterator::operator==(const this_t & rhs) const
{
  return iter_.node_ == rhs.iter_.node_;
}
template< typename T >
bool redko::List< T >::ConstIterator::operator!=(const this_t & rhs) const
{
  return !(rhs == *this);
}

template< typename T >
redko::List< T >::List(size_t count, const T & value)
{
  for (int i = 0; i < count; i++)
  {
    pushBack(value);
  }
}
template< typename T >
redko::List< T >::List(size_t count)
{
  if (count < 1)
  {
    throw std::logic_error("non-positive number");
  }
  head_.next = new ListElem();
  ListElem * curr = head_.next->next;
  for (int i = 1; i < count; i++)
  {
    curr = new ListElem();
    curr = curr->next;
  }
}
template< typename T >
redko::List< T >::List(iterator first, iterator last)
{
  while (first != last)
  {
    pushBack(*first);
    first++;
  }
}
template< typename T >
redko::List< T >::List(const List & other)
{
  ListElem * othrElem = other.head_.next;
  while (othrElem != nullptr)
  {
    pushBack(othrElem->data);
    othrElem = othrElem->next;
  }
}
template< typename T >
redko::List< T >::List(List && other) noexcept
{
  head_.next = std::move(other.head_.next);
  other.head_.next = nullptr;
}
template< typename T >
redko::List< T >::~List()
{
  clear();
}
template< typename T >
redko::List< T >::List(std::initializer_list< T > ilist)
{
  for (auto value : ilist)
  {
    pushBack(value);
  }
}

template< typename T >
redko::List< T > & redko::List< T >::operator=(const List & other)
{
  if (&other != this)
  {
    clear();
    ListElem * othrElem = other.head_.next;
    while (othrElem != nullptr)
    {
      pushBack(othrElem->data);
      othrElem = othrElem->next;
    }
  }
  return *this;
}
template< typename T >
redko::List< T > & redko::List< T >::operator=(List && other)
{
  if (&other != this)
  {
    clear();
    head_.next = std::move(other.head_.next);
    other.head_.next = nullptr;
  }
  return *this;
}

template< typename T >
void redko::List< T >::assign(size_t count, const T & value)
{
  clear();
  for (int i = 0; i < count; i++)
  {
    pushBack(value);
  }
}
template< typename T >
void redko::List< T >::assign(iterator first, iterator last)
{
  clear();
  while (first != last)
  {
    pushBack(*first);
    first++;
  }
}
template< typename T >
void redko::List< T >::assign(std::initializer_list< T > ilist)
{
  clear();
  for (auto value : ilist)
  {
    pushBack(value);
  }
}

template< typename T >
T & redko::List< T >::front()
{
  if (isEmpty())
  {
    throw std::logic_error("calling from empty list");
  }
  return head_.next->data;
}

template< typename T >
typename redko::List< T >::iterator redko::List< T >::beforeBegin() noexcept
{
  return Iterator(&head_);
}
template< typename T >
typename redko::List< T >::const_iterator redko::List< T >::beforeBegin() const noexcept
{
  return ConstIterator(&head_);
}
template< typename T >
typename redko::List< T >::const_iterator redko::List< T >::cbeforeBegin() const noexcept
{
  return ConstIterator(&head_);
}

template< typename T >
typename redko::List< T >::iterator redko::List< T >::begin() noexcept
{
  return Iterator(head_.next);
}
template< typename T >
typename redko::List< T >::const_iterator redko::List< T >::begin() const noexcept
{
  return ConstIterator(head_.next);
}
template< typename T >
typename redko::List< T >::const_iterator redko::List< T >::cbegin() const noexcept
{
  return ConstIterator(head_.next);
}

template< typename T >
typename redko::List< T >::iterator redko::List< T >::end() noexcept
{
  return Iterator(nullptr);
}
template< typename T >
typename redko::List< T >::const_iterator redko::List< T >::end() const noexcept
{
  return ConstIterator(nullptr);
}
template< typename T >
typename redko::List< T >::const_iterator redko::List< T >::cend() const noexcept
{
  return ConstIterator(nullptr);
}

template< typename T >
bool redko::List< T >::isEmpty() const noexcept
{
  return head_.next == nullptr;
}

template< typename T >
void redko::List< T >::clear()
{
  while (begin() != end())
  {
    popFront();
  }
}
template< typename T >
typename redko::List< T >::iterator redko::List< T >::insertAfter(const_iterator pos, const T & value)
{
  ListElem * newElem = new ListElem(value);
  newElem->next = pos.iter_.node_->next;
  pos.iter_.node_->next = newElem;
  return pos++;
}
template< typename T >
typename redko::List< T >::iterator redko::List< T >::insertAfter(const_iterator pos, T && value)
{
  ListElem * newElem = new ListElem(std::move(value));
  newElem->next = pos.iter_.node_->next;
  pos.iter_.node_->next = newElem;
  return pos++;
}
template< typename T >
template< class... Args >
typename redko::List< T >::iterator redko::List< T >::emplaceAfter(const_iterator pos, Args &&... args)
{
  ListElem * newElem = new ListElem(std::forward< Args >(args)...);
  newElem->next = pos.iter_.node_->next;
  pos.iter_.node_->next = newElem;
  return pos++;
}
template< typename T >
typename redko::List< T >::iterator redko::List< T >::eraseAfter(const_iterator pos)
{
  ListElem * p = pos.iter_.node_->next;
  if (p != nullptr)
  {
    pos.iter_.node_->next = p->next;
    delete p;
  }
  return pos++;
}
template< typename T >
void redko::List< T >::pushFront(const T & value)
{
  ListElem * tmp = head_.next;
  head_.next = new ListElem(value);
  head_.next->next = tmp;
}
template< typename T >
void redko::List< T >::pushFront(T && value)
{
  ListElem * tmp = head_.next;
  head_.next = new ListElem(value);
  head_.next->next = tmp;
}
template< typename T >
void redko::List< T >::pushBack(const T & value)
{
  ListElem * tmp = new ListElem(value);
  if (head_.next == nullptr)
  {
    head_.next = tmp;
  }
  else
  {
    iterator curr = begin();
    while (curr.node_->next != nullptr)
    {
      curr++;
    }
    curr.node_->next = tmp;
  }
}
template< typename T >
void redko::List< T >::pushBack(T && value)
{
  ListElem * tmp = new ListElem(std::move(value));
  if (head_.next == nullptr)
  {
    head_.next = tmp;
  }
  else
  {
    iterator curr = begin();
    while (curr.node_->next != nullptr)
    {
      curr++;
    }
    curr.node_->next = tmp;
  }
}
template< typename T >
void redko::List< T >::popFront()
{
  eraseAfter(beforeBegin());
}
template< typename T >
void redko::List< T >::swap(List & other) noexcept
{
  ListElem tmp = other.head_;
  other.head_ = head_;
  head_ = tmp;
}

template< typename T >
void redko::List< T >::merge(List & other)
{
  if (&other != this)
  {
    ListElem * thisElem = head_.next;
    if (thisElem != nullptr)
    {
      while (other.head_.next != nullptr)
      {
        if (thisElem->next != nullptr)
        {
          if (other.head_.next->data >= thisElem->data && other.head_.next->data < thisElem->next->data)
          {
            ListElem * tmp = thisElem->next;
            thisElem->next = other.head_.next;
            other.head_.next = other.head_.next->next;
            thisElem->next->next = tmp;
          }
          thisElem = thisElem->next;
        }
        else
        {
          if (other.head_.next->data >= thisElem->data)
          {
            thisElem->next = other.head_.next;
            other.head_.next = other.head_.next->next;
            thisElem->next->next = nullptr;
            thisElem = thisElem->next;
          }
          else
          {
            ListElem * tmp = head_.next;
            head_.next = other.head_.next;
            other.head_.next = other.head_.next->next;
            head_.next->next = tmp;
            thisElem = head_.next;
          }
        }
      }
    }
    else
    {
      *this = other;
    }
  }
}
template< typename T >
void redko::List< T >::merge(List && other)
{
  if (&other != this)
  {
    ListElem * thisElem = head_.next;
    if (thisElem != nullptr)
    {
      while (other.head_.next != nullptr)
      {
        if (thisElem->next != nullptr)
        {
          if (other.head_.next->data >= thisElem->data && other.head_.next->data < thisElem->next->data)
          {
            ListElem * tmp = thisElem->next;
            thisElem->next = other.head_.next;
            other.head_.next = other.head_.next->next;
            thisElem->next->next = tmp;
          }
          thisElem = thisElem->next;
        }
        else
        {
          if (other.head_.next->data >= thisElem->data)
          {
            thisElem->next = other.head_.next;
            other.head_.next = other.head_.next->next;
            thisElem->next->next = nullptr;
            thisElem = thisElem->next;
          }
          else
          {
            ListElem * tmp = head_.next;
            head_.next = other.head_.next;
            other.head_.next = other.head_.next->next;
            head_.next->next = tmp;
            thisElem = head_.next;
          }
        }
      }
    }
    else
    {
      *this = other;
    }
  }
}
template< typename T >
void redko::List< T >::spliceAfter(iterator pos, List & other)
{
  if (!other.isEmpty())
  {
    iterator otherElem = other.begin();
    while (otherElem != other.end())
    {
      insertAfter(pos, *otherElem);
      pos++;
      otherElem++;
    }
    other.clear();
  }
}
template< typename T >
void redko::List< T >::spliceAfter(iterator pos, List && other)
{
  if (!other.isEmpty())
  {
    iterator otherElem = other.begin();
    while (otherElem != other.end())
    {
      insertAfter(pos, std::move(*otherElem));
      pos++;
      otherElem++;
    }
    other.clear();
  }
}
template< typename T >
size_t redko::List< T >::remove(const T & value)
{
  size_t count = 0;
  iterator prevIt = beforeBegin();
  iterator currIt = begin();
  while (currIt != end())
  {
    if (*currIt == value)
    {
      currIt = eraseAfter(prevIt);
      count++;
    }
    currIt++;
    prevIt++;
  }
  return count;
}
template< typename T >
template< typename UnaryPredicate >
size_t redko::List< T >::removeIf(UnaryPredicate pred)
{
  size_t count = 0;
  iterator prevIt = beforeBegin();
  iterator currIt = begin();
  while (currIt != end())
  {
    if (pred(*currIt))
    {
      currIt = eraseAfter(prevIt);
      count++;
    }
    currIt++;
    prevIt++;
  }
  return count;
}
template< typename T >
void redko::List< T >::reverse() noexcept
{
  if (!isEmpty() && head_.next->next != nullptr)
  {
    ListElem * prevNode = head_.next;
    ListElem * tmpNode = head_.next->next;
    while (tmpNode->next != nullptr)
    {
      tmpNode = tmpNode->next;
      prevNode = prevNode->next;
    }
    tmpNode->next = prevNode;
    ListElem * currNode = prevNode;
    while (currNode != head_.next)
    {
      prevNode = head_.next;
      while (prevNode->next != currNode)
      {
        prevNode = prevNode->next;
      }
      currNode->next = prevNode;
      currNode = prevNode;
    }
    currNode->next = nullptr;
    head_.next = tmpNode;
  }
}
template< typename T >
size_t redko::List< T >::unique()
{
  size_t res = 0;
  if (!isEmpty() && head_.next->next != nullptr)
  {
    iterator nextElem(head_.next->next);
    iterator currElem(head_.next);
    while (nextElem != end())
    {
      if (*currElem == *nextElem)
      {
        res++;
        nextElem = eraseAfter((currElem));
        nextElem++;
      }
      else
      {
        currElem++;
        nextElem++;
      }
    }
  }
  return res;
}
template< typename T >
void redko::List< T >::sort()
{
  if (!isEmpty())
  {
    ListElem * currElem = nullptr;
    ListElem * nextElem = nullptr;
    bool wasEdited = true;
    while (wasEdited)
    {
      wasEdited = false;
      currElem = head_.next;
      nextElem = head_.next->next;
      while (nextElem != nullptr)
      {
        if (currElem->data > nextElem->data)
        {
          wasEdited = true;
          T tmp = currElem->data;
          currElem->data = nextElem->data;
          nextElem->data = tmp;
        }
        currElem = nextElem;
        nextElem = nextElem->next;
      }
    }
  }
}

template< typename T >
bool redko::List< T >::operator==(const List & rhs)
{
  if (this != &rhs)
  {
    ListElem * lCurr = head_.next;
    ListElem * rCurr = rhs.head_.next;
    while (lCurr != nullptr && rCurr != nullptr)
    {
      if (lCurr->data != rCurr->data)
      {
        return false;
      }
      lCurr = lCurr->next;
      rCurr = rCurr->next;
    }
    if (lCurr != nullptr || rCurr != nullptr)
    {
      return false;
    }
  }
  return true;
}
template< typename T >
bool redko::List< T >::operator!=(const List & rhs)
{
  return !(*this == rhs);
}
template< typename T >
bool redko::List< T >::operator<(const List & rhs)
{
  if (this != &rhs)
  {
    ListElem * lCurr = head_.next;
    ListElem * rCurr = rhs.head_.next;
    while (rCurr != nullptr)
    {
      if (lCurr == nullptr || lCurr->data < rCurr->data)
      {
        return true;
      }
      else if (lCurr->data > rCurr->data)
      {
        return false;
      }
      lCurr = lCurr->next;
      rCurr = rCurr->next;
    }
  }
  return false;
}
template< typename T >
bool redko::List< T >::operator<=(const List & rhs)
{
  return !(*this > rhs);
}
template< typename T >
bool redko::List< T >::operator>(const List & rhs)
{
  if (this != &rhs)
  {
    ListElem * lCurr = head_.next;
    ListElem * rCurr = rhs.head_.next;
    while (lCurr != nullptr)
    {
      if (rCurr == nullptr || lCurr->data > rCurr->data)
      {
        return true;
      }
      else if (lCurr->data < rCurr->data)
      {
        return false;
      }
      lCurr = lCurr->next;
      rCurr = rCurr->next;
    }
  }
  return false;
}
template< typename T >
bool redko::List< T >::operator>=(const List & rhs)
{
  return !(*this < rhs);
}

#endif
