#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <memory>
#include <iterator>
#include <cassert>

namespace taskaev
{
  template< typename T >
  class List
  {
  public:
    class ConstIterator;
    class Iterator;

    List();
    List(size_t n, const T& value);
    List(const List< T >& other);
    List(List<T>&& other) noexcept;
    ~List();

    void assign(const T& value);
    void pushFront(const T& value);
    void pushBack(const T& value);
    void popFront();
    bool isEmpty() const noexcept;
    void clear();
    void reverse();
    size_t getSize();
    void swap(List< T >& other) const noexcept;
    void remove(const T& value) noexcept;
    template< typename predicate >
    void remove_if(predicate p) noexcept;

    T& front() const;

    Iterator begin() noexcept;
    Iterator end() noexcept;

    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;

  private:
    struct Node
    {
      T data;
      Node* next;
      explicit Node(T value) : data(value), next(nullptr) {}
    };
   Node* head_;
  };
}

template< typename T >
class taskaev::List< T >::ConstIterator : public std::iterator < std::forward_iterator_tag, T >
{
public:
  friend class List< T >;

  using this_t = ConstIterator;
  ConstIterator();
  ConstIterator(Node* point);
  ConstIterator(const this_t&) = default;
  ~ConstIterator() = default;

  this_t& operator=(const this_t&) = default;
  this_t& operator++();
  this_t operator++(int);

  this_t operator--();
  this_t operator--(int);

  const T& operator*() const;
  const T* operator->() const;

  bool operator!=(const this_t&) const;
  bool operator==(const this_t&) const;
private:
  Node* node;
};

template< typename T >
taskaev::List< T >::ConstIterator::ConstIterator() :
  node(nullptr)
{}

template< typename T>
taskaev::List< T >::ConstIterator::ConstIterator(Node* point) :
  node(point)
{}

template< typename T >
typename taskaev::List< T >::ConstIterator& taskaev::List< T >::ConstIterator::operator++()
{
  assert(node != nullptr);
  node = node->next;
  return *this;
}
template< typename T >
typename taskaev::List< T >::ConstIterator taskaev::List< T >::ConstIterator::operator++(int)
{
  assert(node != nullptr);
  ConstIterator result(*this);
  ++(*this);
  return result;
}

template< typename T >
typename taskaev::List< T >::ConstIterator taskaev::List< T >::ConstIterator::operator--()
{
  assert(node != nullptr);
  Node* prev = nullptr;
  Node* curr = node;
  while (curr->next != node)
  {
   prev = curr;
   curr = curr->next;
  }
  node = prev ? prev : curr;
  return *this;
}

template< typename T >
typename taskaev::List< T >::ConstIterator taskaev::List< T >::ConstIterator::operator--(int)
{
  assert(node != nullptr);
  ConstIterator result(*this);
  --(*this);
  return result;
}

template< typename T >
const T& taskaev::List< T >::ConstIterator::operator*() const
{
  assert(node != nullptr);
  return node->data;
}

template< typename T >
const T* taskaev::List< T >::ConstIterator::operator->() const
{
  assert(node != nullptr);
  return std::addressof(node->data);
}

template< typename T >
bool taskaev::List< T >::ConstIterator::operator==(const this_t& rhs) const
{
  return node == rhs.node;
}
template< typename T >
bool taskaev::List< T >::ConstIterator::operator!=(const this_t& rhs) const
{
  return !(rhs == *this);
}

template< typename T >
class taskaev::List< T >::Iterator : public std::iterator < std::forward_iterator_tag, T >
{
public:
  friend class List< T >;
  using this_t = Iterator;
  Iterator();
  explicit Iterator(ConstIterator val);
  Iterator(const this_t&) = default;
  ~Iterator() = default;

  this_t& operator=(const this_t&) = default;
  this_t& operator++();
  this_t operator++(int);

  this_t operator--();
  this_t operator--(int);

  T& operator*();
  T* operator->();

  bool operator!=(const this_t&) const;
  bool operator==(const this_t&) const;

private:
  ConstIterator iter;
};

template< typename T >
taskaev::List< T >::Iterator::Iterator() :
  iter(nullptr)
{}

template< typename T>
taskaev::List< T >::Iterator::Iterator(ConstIterator val) :
  iter(val)
{}

template< typename T >
typename taskaev::List< T >::Iterator& taskaev::List< T >::Iterator::operator++()
{
  assert(iter != nullptr);
  iter++;
  return *this;
}

template< typename T >
typename taskaev::List< T >::Iterator taskaev::List< T >::Iterator::operator++(int)
{
  assert(iter != nullptr);
  iter++;
  return *this;
}

template< typename T >
typename taskaev::List< T >::Iterator taskaev::List< T >::Iterator::operator--()
{
  assert(iter != nullptr);
  iter--;
  return *this;
}

template< typename T >
typename taskaev::List< T >::Iterator taskaev::List< T >::Iterator::operator--(int)
{
  assert(iter != nullptr);
  iter--;
  return *this;
}

template< typename T >
T& taskaev::List< T >::Iterator::operator*()
{
  assert(iter != nullptr);
  return iter.node->data;
}

template< typename T >
T* taskaev::List< T >::Iterator::operator->()
{
  assert(iter != nullptr);
  return std::addressof(iter.node->data);
}

template< typename T >
bool taskaev::List< T >::Iterator::operator==(const this_t& rhs) const
{
  return iter == rhs.iter;
}
template< typename T >
bool taskaev::List< T >::Iterator::operator!=(const this_t& rhs) const
{
  return !(rhs.iter == iter);
}

template< typename T >
taskaev::List< T >::List() :
  head_(nullptr)
{}

template< typename T >
taskaev::List< T >::List(size_t n, const T& value) :
  head_(nullptr)
{
  for (size_t i = 0; i < n; i++)
  {
    pushBack(value);
  }
}

template< typename T >
taskaev::List< T >::List(const List< T >& other)
{
  head_ = nullptr;
  Node* head = other.head_;
  while (head)
  {
    pushBack(head->data);
    head = head->next;
  }
}

template< typename T >
taskaev::List< T >::List(List< T >&& other) noexcept :
  head_(other.head_)
{
  other.head_ = nullptr;
}


template< typename T >
taskaev::List< T >::~List()
{
  clear();
}

template< typename T>
void taskaev::List< T >::assign(const T& value)
{
  Node* newNode = head_;
  while (newNode != nullptr)
  {
    newNode->data = value;
    newNode = newNode->next;
  }
}

template< typename T >
void taskaev::List< T >::pushFront(const T& value)
{
  Node* node = new Node(value);
  node->next = head_;
  head_ = node;
}

template< typename T >
void taskaev::List< T >::pushBack(const T& value)
{
  Node* node = new Node(value);
  if (isEmpty())
  {
    head_ = node;
  }
  else
  {
    Node* temp = head_;
    while (temp->next)
    {
      temp = temp->next;
    }
    temp->next = node;
  }
}
template< typename T >
void taskaev::List< T >::popFront()
{
  if (head_ != nullptr)
  {
    Node* newNode = head_;
    head_ = head_->next;
    delete newNode;
  }
}

template< typename T >
bool taskaev::List< T >::isEmpty() const noexcept
{
  return head_ == nullptr ? true : false;
}

template< typename T >
void taskaev::List< T >::clear()
{
  while (head_)
  {
    popFront();
  }
}

template< typename T >
void taskaev::List< T >::reverse()
{
  Node* newNode = head_;
  Node* temp = head_->next;
  newNode->next = nullptr;
  while (temp)
  {
    Node* am = temp->next;
    temp->next = newNode;
    newNode = temp;
    temp = am;
  }
  head_ = newNode;
}

template< typename T >
size_t taskaev::List< T >::getSize()
{
  size_t count = 0;
  ConstIterator it = cbegin();
  while (it != cend())
  {
    ++it;
    ++count;
  }
  return count;
}

template< typename T>
void taskaev::List< T >::swap(List< T >& other) const noexcept
{
  std::swap(head_, other.head_);
}

template< typename T >
void taskaev::List< T >::remove(const T& value) noexcept
{
  ConstIterator newNode = cbegin();
  ConstIterator temp = cend();
  while (newNode != nullptr)
  {
    if (newNode->data == value)
    {
      if (temp == value)
      {
        head_ = newNode->next;
      }
      else
      {
        temp->next = newNode->next;
      }
      delete newNode;
      newNode = (temp == nullptr) ? head_ : temp->next;
    }
    else
    {
      temp = newNode;
      newNode = newNode->next;
    }
  }
}
template< typename T >
template< typename predicate >
void taskaev::List< T >::remove_if(predicate p) noexcept
{
  ConstIterator newNode = cbegin();
  ConstIterator temp = cend();
  while (newNode != nullptr)
  {
    if (p(newNode->data))
    {
      if (newNode == head_)
      {
        head_ = newNode->next;
        delete newNode;
        newNode = head_;
      }
      else
      {
        temp->next = newNode->next;
        delete newNode;
        newNode = temp->next;
      }

    }
    else
    {
      temp = newNode;
      newNode = newNode->next;
    }
  }
}

template< typename T >
T& taskaev::List< T >::front() const
{
  return head_->data;
}

template< typename T >
typename taskaev::List< T >::Iterator taskaev::List< T >::begin() noexcept
{
  return Iterator(head_);
}

template< typename T >
typename taskaev::List< T >::Iterator taskaev::List< T >::end() noexcept
{
  return Iterator();
}

template< typename T >
typename taskaev::List< T >::ConstIterator taskaev::List< T >::cbegin() const noexcept
{
  return ConstIterator(head_);
}

template< typename T >
typename taskaev::List< T >::ConstIterator taskaev::List< T >::cend() const noexcept
{
  return ConstIterator();
}

#endif
