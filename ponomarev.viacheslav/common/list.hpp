#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <initializer_list>
#include <iterator>

namespace ponomarev
{
  template < typename T >
  class List
  {
  public:
    class ConstIterator;
    class Iterator;

    using const_iterator = ConstIterator;
    using iterator = Iterator;

    List();
    explicit List(size_t count);
    List(size_t count, const T& data);
    List(iterator first, iterator last);
    List(std::initializer_list< T > dataList);
    ~List();

    void popFront();
    void pushBack(T& data);
    void pushBack(T&& data);
    void pushFront(const T& data);
    size_t getSize() const noexcept;
    T& getFront() const;

    void clear();

    bool isEmpty() const noexcept;

    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    iterator begin() noexcept;
    iterator end() noexcept;

  private:
    class ListNode
    {
      friend class List< T >;
      T data;
      ListNode* next;
      ListNode* prev;
      ListNode(T data, ListNode* next = nullptr, ListNode* prev = nullptr):
        data(data),
        next(next),
        prev(prev)
      {}
    };

    ListNode* head;
    ListNode* tail;
    size_t size;
  };
}

template < typename T >
class ponomarev::List< T >::ConstIterator : public std::iterator< std::bidirectional_iterator_tag, T >
{
public:
  friend class List< T >;
  using this_t = ConstIterator;

  ConstIterator();
  ConstIterator(ListNode* ptr);
  ConstIterator(const this_t&) = default;
  ~ConstIterator() = default;

  this_t& operator=(const this_t&) = default;

  this_t& operator++();
  this_t operator++(int);
  this_t& operator--();
  this_t operator--(int);

  const T& operator*() const;
  const T* operator->() const;

  bool operator==(const this_t&) const;
  bool operator!=(const this_t&) const;

private:
  ListNode* node_;
};

template < typename T >
ponomarev::List< T >::ConstIterator::ConstIterator():
  node_(nullptr)
{}

template < typename T >
ponomarev::List< T >::ConstIterator::ConstIterator(ListNode* data):
  node_(data)
{}

template < typename T >
typename ponomarev::List< T >::ConstIterator& ponomarev::List< T >::ConstIterator::operator++()
{
  node_ = node_->next;
  return *this;
};

template < typename T >
typename ponomarev::List< T >::ConstIterator ponomarev::List< T >::ConstIterator::operator++(int)
{
  ConstIterator temp(*this);
  ++(*this);
  return temp;
}

template < typename T >
typename ponomarev::List< T >::ConstIterator& ponomarev::List< T >::ConstIterator::operator--()
{
  node_ = node_->prev;
  return *this;
}

template < typename T >
typename ponomarev::List< T >::ConstIterator ponomarev::List< T >::ConstIterator::operator--(int)
{
  ConstIterator temp(*this);
  --(*this);
  return temp;
}

template < typename T >
const T& ponomarev::List< T >::ConstIterator::operator*() const
{
  return node_->data;
}

template < typename T >
const T* ponomarev::List< T >::ConstIterator::operator->() const
{
  return &(node_->data);
}

template < typename T >
bool ponomarev::List< T >::ConstIterator::operator==(const this_t& that) const
{
  return node_ == that.node_;
}

template < typename T >
bool ponomarev::List< T >::ConstIterator::operator!=(const this_t& that) const
{
  return !(that == *this);
}

template < typename T >
class ponomarev::List< T >::Iterator : public std::iterator< std::bidirectional_iterator_tag, T >
{
public:
  friend class List< T >;
  using this_t = Iterator;

  Iterator();
  Iterator(ListNode* ptr);
  Iterator(ConstIterator const_iterator);
  Iterator(const this_t&) = default;
  ~Iterator() = default;

  this_t& operator=(const this_t&) = default;
  this_t& operator++();
  this_t operator++(int);
  this_t& operator--();
  this_t operator--(int);
  this_t operator+(size_t index);

  T& operator*();
  T* operator->();
  const T& operator*() const;
  const T* operator->() const;

  bool operator==(const this_t&) const;
  bool operator!=(const this_t&) const;

private:
  ConstIterator iterator_;
};

template < typename T >
ponomarev::List< T >::Iterator::Iterator():
  iterator_(ConstIterator())
{}

template < typename T >
ponomarev::List< T >::Iterator::Iterator(ListNode* data):
  iterator_(ConstIterator(data))
{}

template < typename T >
ponomarev::List< T >::Iterator::Iterator(ConstIterator const_iterator):
  iterator_(const_iterator)
{}

template < typename T >
typename ponomarev::List< T >::Iterator& ponomarev::List< T >::Iterator::operator++()
{
  iterator_++;
  return iterator_;
};

template < typename T >
typename ponomarev::List< T >::Iterator ponomarev::List< T >::Iterator::operator++(int)
{
  ++iterator_;
  return iterator_;
}

template < typename T >
typename ponomarev::List< T >::Iterator& ponomarev::List< T >::Iterator::operator--()
{
  iterator_--;
  return iterator_;
}

template < typename T >
typename ponomarev::List< T >::Iterator ponomarev::List< T >::Iterator::operator--(int)
{
  --iterator_;
  return iterator_;
}

template < typename T >
typename ponomarev::List< T >::Iterator ponomarev::List< T >::Iterator::operator+(size_t index)
{
  for (size_t i = 0; i < index; i++)
  {
    (*this)++;
  }
  return *this;
}

template < typename T >
T& ponomarev::List< T >::Iterator::operator*()
{
  return iterator_.node_->data;
}

template < typename T >
T* ponomarev::List< T >::Iterator::operator->()
{
  return &(iterator_.node_->data);
}

template < typename T >
const T& ponomarev::List< T >::Iterator::operator*() const
{
  return iterator_.node_->data;
}

template < typename T >
const T* ponomarev::List< T >::Iterator::operator->() const
{
  return &(iterator_.node_->data);
}

template < typename T >
bool ponomarev::List< T >::Iterator::operator==(const this_t& that) const
{
  return iterator_ == that.iterator_;
}

template < typename T >
bool ponomarev::List< T >::Iterator::operator!=(const this_t& that) const
{
  return !(that == *this);
}

template < typename T >
ponomarev::List< T >::List()
{
  size = 0;
  head = nullptr;
  tail = nullptr;
}

template < typename T >
ponomarev::List< T >::List(size_t count)
{
  size = 0;
  for (int i = 1; i <= count; i++)
  {
    pushBack(T());
  }
}

template < typename T >
ponomarev::List< T >::List(size_t count, const T& data)
{
  size = 0;
  for (int i = 0; i <= count; i++)
  {
    pushBack(data);
  }
}

template < typename T >
ponomarev::List< T >::List(iterator first, iterator last)
{
  size = 0;
  while (first != last)
  {
    pushBack(*first);
    first++;
  }
}

template <typename T>
ponomarev::List<T>::List(std::initializer_list<T> dataList)
{
  size = 0;
  for (T data : dataList)
  {
    pushBack(data);
  }
}

template < typename T >
ponomarev::List< T >::~List()
{
  clear();
}

template < typename T >
void ponomarev::List< T >::popFront()
{
  ListNode* temp = head;
  head = head->next;
  delete temp;
  --size;
}

template < typename T >
void ponomarev::List< T >::pushBack(T& data)
{
  if (head == nullptr)
  {
    head = new ListNode(data);
    tail = head;
  }
  else
  {
    ListNode* temp = new ListNode(data, nullptr, tail);
    tail->next = temp;
    tail = temp;
  }
  size++;
}

template<typename T>
void ponomarev::List<T>::pushBack(T&& data)
{
  if (head == nullptr)
  {
    head = new ListNode(data);
    tail = head;
  }
  else
  {
    ListNode* adListNode = new ListNode(data, nullptr, tail);
    tail->next = adListNode;
    tail = adListNode;
  }
  size++;
}

template< typename T >
void ponomarev::List< T >::pushFront(const T& data)
{
  head = new ListNode(data, head);
  if (size != 0)
  {
    head->next->prev = head;
  }
  size++;
}

template < typename T >
size_t ponomarev::List< T >::getSize() const noexcept
{
  return size;
}

template< typename T >
T& ponomarev::List< T >::getFront() const
{
  return head->data;
}

template < typename T >
void ponomarev::List< T >::clear()
{
  while (size != 0)
  {
    popFront();
  }
}

template < typename T >
bool ponomarev::List< T >::isEmpty() const noexcept
{
  return this->getSize() == 0;
}

template < typename T >
typename ponomarev::List< T >::ConstIterator ponomarev::List< T >::cbegin() const noexcept
{
  return ConstIterator(head);
}

template < typename T >
typename ponomarev::List< T >::ConstIterator ponomarev::List< T >::cend() const noexcept
{
  return ConstIterator(tail->next);
}

template < typename T >
typename ponomarev::List< T >::ConstIterator ponomarev::List< T >::begin() const noexcept
{
  return ConstIterator(head);
}

template < typename T >
typename ponomarev::List< T >::ConstIterator ponomarev::List< T >::end() const noexcept
{
  return ConstIterator(tail->next);
}

template < typename T >
typename ponomarev::List< T >::Iterator ponomarev::List< T >::begin() noexcept
{
  return Iterator(head);
}

template < typename T >
typename ponomarev::List< T >::Iterator ponomarev::List< T >::end() noexcept
{
  return Iterator(tail->next);
}

#endif
