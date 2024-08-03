#ifndef LIST_HPP
#define LIST_HPP
#include <stdexcept>
#include <initializer_list>
#include <cstddef>

namespace nikiforov
{
  template < typename T >
  class List
  {
  public:
    class Iterator;
    class ConstIterator;

    List();
    explicit List(size_t count);
    List(size_t count, const T& value);
    List(Iterator begin, Iterator end, int value);
    List(const List& other);
    List(std::initializer_list< T > ilist);
    ~List();

    T& front();
    T& back();

    void assign(size_t count, const T& value);
    void assign(Iterator first, Iterator last);
    void assign(std::initializer_list<T> ilist);

    bool is_empty() noexcept;
    size_t getSize();

    void push_front(const T& data);
    void push_back(const T& data);
    void pop_front();
    void pop_back();
    Iterator insert(Iterator pos, const T& value);
    Iterator insert(Iterator pos, size_t count, const T& value);
    Iterator erase(Iterator pos);
    Iterator erase(Iterator first, Iterator last);
    void splice(Iterator pos, List< T >& other);
    void reverse();
    void swap(List< T >& other) noexcept;
    void clear();

    void remove(T value);
    template< class UnaryPredicate >
    void remove_if(UnaryPredicate p);

    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator begin() const noexcept;
    ConstIterator end() const noexcept;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;

    void advance(Iterator& pos, size_t count);
    void advance(Iterator& first, Iterator last);

  private:

    struct Node
    {
      T data;
      Node* pNext;
      Node(T data, Node* pNext = nullptr)
      {
        this->data = data;
        this->pNext = pNext;
      }
    };
    Node* head;
    size_t size_l;
  };
}

namespace nikiforov
{
  template< typename T >
  class List< T >::ConstIterator : public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    friend class List< T >;
    using this_t = ConstIterator;

    ConstIterator();
    ConstIterator(const this_t&) = default;
    ~ConstIterator() = default;

    this_t& operator=(const this_t&) = default;
    this_t& operator++();
    this_t operator++(int);

    const T& operator*() const;
    const T* operator->() const;

    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;

  private:
    Node* pNode;
    ConstIterator(Node*);
  };
}

template< typename T >
nikiforov::List< T >::ConstIterator::ConstIterator()
{
  this->pNode = nullptr;
}

template< typename T >
nikiforov::List< T >::ConstIterator::ConstIterator(Node* pNode)
{
  this->pNode = pNode;
}

template< typename T >
typename nikiforov::List< T >::ConstIterator& nikiforov::List< T >::ConstIterator::operator++()
{
  pNode = pNode->pNext;
  return *this;
}

template< typename T >
typename nikiforov::List< T >::ConstIterator nikiforov::List< T >::ConstIterator::operator++(int)
{
  ConstIterator iter = *this;
  ++(*this);
  return iter;
}

template< typename T >
const T& nikiforov::List< T >::ConstIterator::operator*() const
{
  return pNode->data;
}

template< typename T >
const T* nikiforov::List< T >::ConstIterator::operator->() const
{
  return &(pNode->data);
}

template< typename T >
bool nikiforov::List< T >::ConstIterator::operator!=(const this_t& lhs) const
{
  return !(*this == lhs);
}

template< typename T >
bool nikiforov::List< T >::ConstIterator::operator==(const this_t& lhs) const
{
  return pNode == lhs.pNode;
}

namespace nikiforov
{
  template< typename T >
  class List< T >::Iterator : public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    friend class List< T >;
    using this_t = Iterator;

    Iterator();
    Iterator(ConstIterator);
    Iterator(const this_t&) = default;
    ~Iterator() = default;

    this_t& operator=(const this_t&) = default;
    this_t& operator++();
    this_t operator++(int);

    T& operator*();
    T* operator->();
    const T& operator*() const;
    const T* operator->() const;

    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;

  private:
    ConstIterator iter_;
  };
}

template< typename T >
nikiforov::List< T >::Iterator::Iterator()
{
  this->iter_ = nullptr;
}

template< typename T >
nikiforov::List< T >::Iterator::Iterator(ConstIterator constIterator)
{
  this->iter_ = constIterator;
}

template< typename T >
typename nikiforov::List< T >::Iterator& nikiforov::List< T >::Iterator::operator++()
{
  ++iter_;
  return *this;
}

template< typename T >
typename nikiforov::List< T >::Iterator nikiforov::List< T >::Iterator::operator++(int)
{
  this_t iter = iter_;
  ++iter_;
  return iter;
}

template< typename T >
T& nikiforov::List< T >::Iterator::operator*()
{
  return iter_.pNode->data;
}

template< typename T >
T* nikiforov::List< T >::Iterator::operator->()
{
  return &(iter_.pNode->data);
}

template< typename T >
const T& nikiforov::List< T >::Iterator::operator*() const
{
  return iter_.pNode->data;
}

template< typename T >
const T* nikiforov::List< T >::Iterator::operator->() const
{
  return &(iter_.pNode->data);
}

template< typename T >
bool nikiforov::List< T >::Iterator::operator!=(const this_t& lhs) const
{
  return !(*this == lhs.iter_);
}

template< typename T >
bool nikiforov::List< T >::Iterator::operator==(const this_t& lhs) const
{
  return iter_ == lhs.iter_;
}

template< typename T >
nikiforov::List< T >::List()
{
  head = nullptr;
  size_l = 0;
}

template< typename T >
nikiforov::List< T >::List(size_t count)
{
  for (size_t i = 0; i < count; i++)
  {
    push_back(count);
  }
}

template< typename T >
nikiforov::List< T >::List(size_t count, const T& value)
{
  for (size_t i = 0; i < count; i++)
  {
    push_back(value);
  }
}

template< typename T >
nikiforov::List< T >::List(Iterator begin, Iterator end, int value)
{
  for (begin; begin != end; ++begin)
  {
    push_back(value);
  }
}

template< typename T >
nikiforov::List< T >::List(const nikiforov::List< T >& other)
{
  if (other.head == nullptr)
  {
    head = nullptr;
  }
  else
  {
    head = new Node(*other.head);
  }
  size_l = other.size_l;
}

template< typename T >
nikiforov::List< T >::List(std::initializer_list< T > ilist)
{
  assign(ilist);
}

template< typename T >
nikiforov::List< T >::~List()
{
  clear();
}

template< typename T >
T& nikiforov::List< T >::front()
{
  if (is_empty())
  {
    throw std::logic_error("Empty list!");
  }
  return head->data;
}

template< typename T >
T& nikiforov::List< T >::back()
{
  if (is_empty())
  {
    throw std::logic_error("Empty list!");
  }
  Node* actual = head;
  for (size_t i = 0; i < (size_l - 1); i++)
  {
    actual = actual->pNext;
  }
  return actual->data;
}

template< typename T >
void nikiforov::List< T >::assign(size_t count, const T& value)
{
  clear();
  for (size_t i = 0; i < count; i++)
  {
    push_back(value);
  }
}

template< typename T >
void nikiforov::List< T >::assign(Iterator first, Iterator last)
{
  clear();
  while (first != last)
  {
    push_back(*first);
    first++;
  }
}

template< typename T >
void nikiforov::List< T >::assign(std::initializer_list< T > ilist)
{
  clear();
  for (const T* iter = ilist.begin(); iter != ilist.end(); ++iter)
  {
    push_back(*iter);
  }
}

template< typename T >
bool nikiforov::List< T >::is_empty() noexcept
{
  return (head == nullptr) ? true : false;
}

template< typename T >
size_t nikiforov::List< T >::getSize()
{
  return size_l;
}

template< typename T >
void nikiforov::List< T >::push_front(const T& data)
{
  Node* nData = new Node(data);
  if (head == nullptr)
  {
    head = nData;
  }
  else
  {
    Node* actual = head;
    nData->pNext = actual;
    head = nData;
  }
  size_l++;
}

template< typename T >
void nikiforov::List< T >::push_back(const T& data)
{
  Node* nData = new Node(data);
  if (head == nullptr)
  {
    head = nData;
  }
  else
  {
    Node* actual = head;
    while (actual->pNext != nullptr)
    {
      actual = actual->pNext;
    }
    actual->pNext = nData;
  }
  size_l++;
}

template< typename T >
void nikiforov::List< T >::pop_front()
{
  if (is_empty())
  {
    throw std::logic_error("Empty list!");
  }
  Node* actual = head;
  head = head->pNext;
  delete actual;
  size_l--;
}

template< typename T >
void nikiforov::List< T >::pop_back()
{
  if (is_empty())
  {
    throw std::logic_error("Empty list!");
  }
  Node* actual = head;
  Node* todel = head;
  for (size_t i = 0; i < (size_l - 1); i++)
  {
    actual = todel;
    todel = actual->pNext;
  }
  actual->pNext = nullptr;
  delete todel;
  if (size_l == 1)
  {
    head = nullptr;
  }
  size_l--;
}

template< typename T >
typename nikiforov::List< T >::Iterator nikiforov::List< T >::insert(Iterator pos, const T& value)
{
  Iterator newPos = begin();
  if (pos == begin())
  {
    push_front(value);
    newPos = begin();
  }
  else
  {
    Node* nData = new Node(value);
    Node* actual = head;
    Node* before_actial = head;
    size_t count = 0;
    for (Iterator iter = begin(); iter != pos; ++iter)
    {
      before_actial = actual;
      actual = actual->pNext;
      count++;
    }
    before_actial->pNext = nData;
    nData->pNext = actual;
    size_l++;
    advance(newPos, count);
  }
  return Iterator(newPos);
}

template< typename T >
typename nikiforov::List< T >::Iterator nikiforov::List< T >::insert(Iterator pos, size_t count, const T& value)
{
  Iterator newPos = begin();
  for (size_t i = 0; i < count; i++)
  {
    newPos = insert(pos, value);
  }
  return Iterator(newPos);
}

template< typename T >
typename nikiforov::List< T >::Iterator nikiforov::List< T >::erase(Iterator pos)
{
  Iterator newPos = begin();
  if (pos == end())
  {
    newPos = end();
  }
  else if (pos == begin())
  {
    pop_front();
    newPos = begin();
  }
  else
  {
    Node* todel = head;
    Node* before_todel = head;
    size_t count = 0;
    for (Iterator iter = begin(); iter != pos; ++iter)
    {
      before_todel = todel;
      todel = todel->pNext;
      count++;
    }
    before_todel->pNext = todel->pNext;
    delete todel;
    size_l--;
    newPos = begin();
    advance(newPos, count);
  }
  return Iterator(newPos);
}

template< typename T >
typename nikiforov::List< T >::Iterator nikiforov::List< T >::erase(Iterator first, Iterator last)
{
  Iterator newPos = begin();
  if (first == last)
  {
    newPos = last;
  }
  else
  {
    for (first; first != last; ++first)
    {
      first = erase(first);
    }
    newPos = first;
  }
  return Iterator(newPos);
}

template< typename T >
void nikiforov::List< T >::splice(Iterator pos, List< T >& other)
{
  if (other.is_empty())
  {
    throw std::logic_error("Empty list!");
  }

  Node* actual = head;
  for (Iterator iter = begin(); iter != pos; ++iter)
  {
    actual = actual->pNext;
  }

  Node* other_end = other.head;
  for (size_t i = 0; i < (other.size() - 1); i++)
  {
    other_end = other_end->pNext;
  }

  Node* subhead = actual->pNext;
  actual->pNext = other.head;
  other_end->pNext = subhead;
}

template< typename T >
void nikiforov::List< T >::reverse()
{
  Iterator iter = begin();
  size_t count = getSize();
  size_t count_iter = getSize();
  for (size_t i = 0; i < count; i++)
  {
    advance(iter, count_iter);
    push_back(*iter);
    iter = begin();
    count_iter--;
  }
  for (size_t i = 0; i < count; i++)
  {
    pop_front();
  }
}

template< typename T >
void nikiforov::List< T >::swap(List< T >& other) noexcept
{
  Node* short_termH = this->head;
  head = other.head;
  other.head = short_termH;

  size_t short_termS = this->size_l;
  size_l = other.size_l;
  other.size_l = short_termS;
}

template< typename T >
void nikiforov::List< T >::clear()
{
  const size_t size = size_l;
  for (size_t i = 0; i < size; i++)
  {
    pop_front();
  }
}

template< typename T >
void nikiforov::List< T >::remove(T value)
{
  size_t count = 0;
  Node* actual = head;
  Node* todel = head;
  Iterator iter = begin();
  while (iter != end())
  {
    actual = head;
    todel = head;
    if (*iter == value)
    {
      if (iter == begin())
      {
        head = head->pNext;
        iter = begin();
        delete actual;
        size_l--;
        continue;
      }
      else
      {
        for (size_t i = 0; i < (count - 1); i++)
        {
          actual = actual->pNext;
        }
        todel = actual->pNext;
        actual->pNext = todel->pNext;
        iter++;
        delete todel;
        size_l--;
        continue;
      }
    }
    iter++;
    count++;
  }
}

template< typename T >
template< class UnaryPredicate >
void nikiforov::List< T >::remove_if(UnaryPredicate p)
{
  Node* actial = head;
  Node* before_actial = head;
  while (actial)
  {
    if ((p(actial->data)) && (actial == head))
    {
      pop_front();
      actial = head;
      before_actial = head;
      continue;
    }
    else if ((p(actial->data)) && (actial->pNext == nullptr))
    {
      pop_back();
      break;
    }
    else if ((p(actial->data)) && (actial != head))
    {
      before_actial->pNext = actial->pNext;
      delete actial;
      actial = before_actial;
      size_l--;
    }
    before_actial = actial;
    actial = before_actial->pNext;
  }
}

template< typename T >
typename nikiforov::List< T >::Iterator nikiforov::List< T >::begin() noexcept
{
  return Iterator(head);
}

template< typename T >
typename nikiforov::List< T >::Iterator nikiforov::List< T >::end() noexcept
{
  return Iterator(nullptr);
}

template< typename T >
typename nikiforov::List< T >::ConstIterator nikiforov::List< T >::begin() const noexcept
{
  return ConstIterator(head);
}

template< typename T >
typename nikiforov::List< T >::ConstIterator nikiforov::List< T >::end() const noexcept
{
  return ConstIterator(nullptr);
}

template< typename T >
typename nikiforov::List< T >::ConstIterator nikiforov::List< T >::cbegin() const noexcept
{
  return ConstIterator(head);
}

template< typename T >
typename nikiforov::List< T >::ConstIterator nikiforov::List< T >::cend() const noexcept
{
  return ConstIterator(nullptr);
}

template< typename T >
void nikiforov::List< T >::advance(Iterator& pos, size_t count)
{
  if (count < 0)
  {
    throw std::logic_error("Wrong input count!");
  }
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
void nikiforov::List<T>::advance(Iterator& first, Iterator last)
{
  for (T iter = first; iter != last; ++iter)
  {
    if (iter == end())
    {
      first = end();
      break;
    }
    first++;
  }
}

#endif
