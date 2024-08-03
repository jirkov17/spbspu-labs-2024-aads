#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <iostream>
#include <memory>

namespace miheev
{
  template< typename T >
  class List
  {
  public:
    using value_type = T;
    struct ConstIterator;
    struct Iterator;

    List();
    List(T data);
    List(const List& toCopy);
    List(List&& rhs);
    List(size_t count, const T& value);
    ~List();
    List& operator=(const List& list);

    bool empty() const;

    T& front();
    const T& front() const;

    size_t size() const;
    bool contains(const T&) const;

    void assign (size_t n, const T& val);
    void pushFront(const T& data);
    void push_front(const T& data);
    void popFront();
    void pushBack(const T& data);
    void push_back(const T& data);
    void popBack();
    void eraseAfter(Iterator iter);
    void swap(List& aList);
    void clear();

    void print(std::ostream& stream = std::cout, const char& splitter = ' ') const;

    void remove(T data);
    template < class P >
    void removeIf(P functor);

    Iterator begin();
    Iterator end();
    ConstIterator cbegin() const;
    ConstIterator cend() const;

  private:
    T data_;
    List* next_;
    bool isEmpty_;

    T& operator[](size_t i);
    void takeAndDrop(List** rhs);
  };
}

template< typename T >
struct miheev::List< T >::ConstIterator: public std::iterator<std::forward_iterator_tag, T>
{
public:
  friend class List< T >;
  ConstIterator(const List< T >*);
  ConstIterator(const ConstIterator&) = default;
  ~ConstIterator() = default;
  ConstIterator& operator=(const ConstIterator&) = default;

  ConstIterator& operator++();
  ConstIterator operator++(int);

  const T& operator*() const;
  const T* operator->() const;

  bool operator!=(const ConstIterator& rhs) const;
  bool operator==(const ConstIterator& rhs) const;

private:
  const List< T >* cur_;
};

template< typename T >
struct miheev::List< T >::Iterator: public std::iterator<std::forward_iterator_tag, T>
{

  using this_t = List< T >::Iterator;

  Iterator();
  Iterator(List< T >* head);
  Iterator(const this_t&) = default;
  this_t& operator=(const this_t&) = default;
  List<T>& operator+(size_t n);
  T& operator*();
  T* operator->();
  explicit operator bool() const;
  this_t& operator++();
  this_t operator++(int);
  bool operator!=(const this_t & rhs) const;
  bool operator==(const this_t & rhs) const;

private:
  List<T>* cur;

  void eraseAfter();
  bool empty() const;
  this_t next();

  friend class List< T >;
};

template< typename T >
typename miheev::List< T >::ConstIterator miheev::List< T >::cbegin() const
{
  return this;
}

template< typename T >
typename miheev::List< T >::ConstIterator miheev::List< T >::cend() const
{
  return nullptr;
}

template< typename T >
typename miheev::List< T >::Iterator miheev::List< T >::begin()
{
  return this;
}

template< typename T >
typename miheev::List< T >::Iterator miheev::List< T >::end()
{
  return nullptr;
}

template< typename T >
miheev::List< T >::ConstIterator::ConstIterator(const miheev::List< T >* ptr):
  cur_(ptr)
{}

template< typename T >
typename miheev::List< T >::ConstIterator& miheev::List< T >::ConstIterator::operator++()
{
  cur_ = cur_->next_;
  return *this;
}

template< typename T >
typename miheev::List< T >::ConstIterator miheev::List< T >::ConstIterator::operator++(int)
{
  ConstIterator temp(*this);
  ++(*this);
  return temp;
}

template< typename T >
const T& miheev::List< T >::ConstIterator::operator*() const
{
  return cur_->data_;
}

template< typename T >
const T* miheev::List< T >::ConstIterator::operator->() const
{
  return std::addressof(cur_->data_);
}

template< typename T >
bool miheev::List< T >::ConstIterator::operator!=(const miheev::List< T >::ConstIterator& rhs) const
{
  return rhs.cur_ != this->cur_;
}

template< typename T >
bool miheev::List< T >::ConstIterator::operator==(const miheev::List< T >::ConstIterator& rhs) const
{
  return rhs.cur_ == this->cur_;
}

template< typename T >
miheev::List< T >::Iterator::Iterator():
  cur(nullptr)
{}

template< typename T >
miheev::List< T >::Iterator::Iterator(List < T >* head):
  cur(head)
{}

template< typename T >
miheev::List< T >& miheev::List< T >::Iterator::operator+(size_t n)
{
  List< T >* temp = cur;
  for (; n > 0; n--)
  {
    temp++;
  }
  return *temp;
}

template< typename T >
T& miheev::List< T >::Iterator::operator*()
{
  return cur->data_;
}

template< typename T >
T* miheev::List< T >::Iterator::operator->()
{
  return std::addressof(cur->data_);
}

template< typename T >
miheev::List< T >::Iterator::operator bool() const
{
  return cur->next_ != nullptr;
}

template< typename T >
bool miheev::List< T >::Iterator::empty() const
{
  return cur->isEmpty_;
}

template< typename T >
typename miheev::List< T >::Iterator::this_t& miheev::List< T >::Iterator::operator++()
{
  cur = cur->next_;
  return *this;
}

template< typename T >
typename miheev::List< T >::Iterator::this_t miheev::List< T >::Iterator::operator++(int)
{
  this_t copy(*this);
  cur = cur->next_;
  return copy;
}

template< typename T >
typename miheev::List< T >::Iterator::this_t miheev::List< T >::Iterator::next()
{
  return this_t(this->cur->next_);
}

template< typename T >
bool miheev::List< T >::Iterator::operator!=(const this_t & rhs) const
{
  return cur != rhs.cur;
}

template< typename T >
bool miheev::List< T >::Iterator::operator==(const this_t & rhs) const
{
return cur == rhs.cur;
}

template< typename T >
void miheev::List< T >::Iterator::eraseAfter()
{
  List< T >* temp = cur->next_;
  cur->next_ = temp->next_;
  temp->next_ = nullptr;
  delete temp;
}

template< typename T >
miheev::List< T >::List():
  data_(T()),
  next_(nullptr),
  isEmpty_(true)
{}

template< typename T >
miheev::List< T >::List(T data):
  data_(data),
  next_(nullptr),
  isEmpty_(false)
{}

template< typename T >
miheev::List< T >::List(const List& toCopy)
{
  data_ = toCopy.data_;
  isEmpty_ = toCopy.isEmpty_;
  if (toCopy.next_)
  {
    next_ = new List< T >(*toCopy.next_);
  }
  else
  {
    next_ = nullptr;
  }
}

template< typename T >
void miheev::List< T >::takeAndDrop(List< T >** rhs)
{
  data_ = (*rhs)->data_;
  next_ = (*rhs)->next_;
  isEmpty_ = (*rhs)->isEmpty_;
  (*rhs)->next_ = nullptr;
  delete *rhs;
}

template< typename T >
miheev::List< T >::List(List&& rhs):
  next_{nullptr},
  isEmpty_{true}
{
  ConstIterator rhsIter(rhs.cbegin());
  List< T >* node = this;
  while (node != nullptr && rhsIter != nullptr)
  {
    node->data_ = *rhsIter;
    rhsIter++;
    if (rhsIter != nullptr)
    {
      node->next_ = new List< T >(*rhsIter);
    }
    node = node->next_;
  }
}

template< typename T >
miheev::List< T >::List(size_t count, const T& value):
  next_(nullptr),
  isEmpty_(true)
{
  if (count == 0)
  {
    return;
  }
  data_ = value;
  isEmpty_ = false;
  List< T >* node = this;
  for (size_t i = 1; i < count; i++)
  {
    node->next_ = new List< T >(value);
    node = node->next_;
  }
}

template< typename T >
miheev::List< T >& miheev::List< T >::operator=(const miheev::List< T >& list)
{
  data_ = list.data_;
  isEmpty_ = list.isEmpty_;
  if (next_)
  {
    List< T >* old = next_;
    next_ = nullptr;
    delete old;
  }
  if (list.next_)
  {
    next_ = new List< T >(*(list.next_));
  }
  return *this;
}

template< typename T >
miheev::List< T >::~List()
{
  if (next_)
  {
    delete next_;
  }
}

template< typename T >
bool miheev::List< T >::empty() const
{
  return isEmpty_;
}

template < typename T >
void miheev::List< T >::swap(List< T >& aList)
{
  List< T > temp = *this;
  clear();
  while (!aList.empty())
  {
    pushBack(aList.front());
    aList.popFront();
  }
  aList.clear();
  while (!temp.empty())
  {
    aList.pushBack(temp.front());
    temp.popFront();
  }
}

template < typename T >
T& miheev::List< T >::operator[](size_t i)
{
  List < T >* node = this;
  while (i > 0)
  {
    if (node->next_)
    {
      node = node->next_;
    }
    i--;
  }
  return node->data_;
}

template < typename T >
void miheev::List< T >::clear()
{
  if (next_ != nullptr)
  {
    List< T >* temp = next_;
    next_ = nullptr;
    delete temp;
  }
  isEmpty_ = true;
}

template < typename T >
size_t miheev::List< T >::size() const
{
  if (isEmpty_)
  {
    return 0;
  }
  if (!next_)
  {
    return 1;
  }
  return 1 + next_->size();
}

template < typename T >
T& miheev::List< T >::front()
{
  return data_;
}

template < typename T >
const T& miheev::List< T >::front() const
{
  return data_;
}

template < typename T >
void miheev::List< T >::pushFront(const T& data)
{
  if (!isEmpty_)
  {
    List< T >* temp = next_;
    next_ = new List< T >(data_);
    next_->next_ = temp;
  }
  data_ = data;
  isEmpty_ = false;
}

template < typename T >
void miheev::List< T >::push_front(const T& data)
{
  pushFront(data);
}

template < typename T >
void miheev::List< T >::popFront()
{
  if (!next_)
  {
    isEmpty_ = true;
  }
  if (isEmpty_)
  {
    return;
  }
  List< T >* temp = next_;
  data_ = next_->data_;
  next_ = next_->next_;
  temp->next_ = nullptr;
  delete temp;
}

template < typename T >
void miheev::List< T >::pushBack(const T& data)
{
  if (isEmpty_)
  {
    data_ = data;
  }
  else
  {
    if (next_ == nullptr)
    {
      next_ = new List< T >(data);
    }
    else
    {
      next_->pushBack(data);
    }
  }
  isEmpty_ = false;
}

template < typename T >
void miheev::List< T >::push_back(const T& data)
{
  pushBack(data);
}

template < typename T >
void miheev::List< T >::eraseAfter(miheev::List< T >::Iterator iter)
{
  iter.eraseAfter();
}

template < typename T >
void miheev::List< T >::remove(T data)
{
  Iterator iter(begin());
  while(iter != nullptr)
  {
    if (iter.next() != nullptr && *(iter.next()) == data)
    {
      iter.eraseAfter();
    }
    iter++;
  }
  if (data_ == data)
  {
    popFront();
  }
}

template < typename T >
void miheev::List< T >::print(std::ostream& stream, const char& splitter) const
{
  stream << data_;
  if (next_)
  {
    stream << splitter;
    next_->print(stream, splitter);
  }
  else
  {
    std::cout << '\n';
  }
}

template < typename T >
template < typename P >
void miheev::List< T >::removeIf(P functor)
{
  Iterator iter(begin());

  while (functor(*iter))
  {
    popFront();
  }

  while (iter)
  {
    if (functor(*(iter.next())))
    {
      iter.eraseAfter();
    }
    if (iter)
    {
      iter++;
    }
  }
}

template < typename T >
void miheev::List< T >::assign(size_t n, const T& val)
{
  clear();
  List< T >* temp = new List< T >(n, val);
  takeAndDrop(&temp);
}

template < typename T >
void miheev::List< T >::popBack()
{
  if (!next_)
  {
    isEmpty_ = true;
  }
  else
  {
    Iterator iter(begin());
    for (size_t i = 0; i < size() - 2; i++)
    {
      iter++;
    }
    eraseAfter(iter);
  }
}

template < typename T >
bool miheev::List< T >::contains(const T& value) const
{
  if (data_ == value)
  {
    return true;
  }
  if (next_)
  {
    return next_->contains(value);
  }
  return false;
}

#endif
