#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <limits>
#include <stdexcept>

namespace anikanov {
  template< typename T >
  class List {
  public:
    class Node;
    class Iterator;
    class ConstIterator;

    List();
    List(const List &other);
    List(List &&other) noexcept;
    List(const T &value, size_t count);
    List(std::initializer_list< T > init);
    List(Iterator first, Iterator last);
    ~List();

    void push_back(const T &value);
    void pop(size_t n = std::numeric_limits< size_t >::max());
    bool empty() const;
    size_t size() const;
    void clear();
    void swap(const List &other) noexcept;
    void remove(const T &value);
    void remove_if(bool(*pred)(T));
    void reverse();
    void splice(Iterator position, List< T > &other, Iterator first, Iterator last);
    Iterator insert(Iterator pos, const T &value);
    Iterator erase(Iterator pos);
    Iterator erase(Iterator begin, Iterator end);
    void assign(size_t count, const T &value);
    void assign(Iterator first, Iterator last);
    void assign(std::initializer_list< T > ilist);
    List< T > copy();

    T &operator[](size_t index);
    List< T > &operator=(List< T > &&other) noexcept;
    List< T > &operator=(const List< T > &other);

    Iterator back();
    Iterator begin();
    ConstIterator begin() const;
    Iterator end() noexcept;
    ConstIterator end() const noexcept;
    template<typename Compare = std::less<T> >
    void sort(Compare comp = Compare());

  private:
    template<typename Compare >
    Iterator merge(Iterator first, Iterator second, Compare comp);
    template<typename Compare >
    Iterator mergeSort(Iterator start, Iterator end, Compare comp);
    std::shared_ptr< List::Node > head, tail;
    size_t list_size;
  };
}

template< typename T >
class anikanov::List< T >::Node {
public:
  T data;
  std::shared_ptr< List::Node > prev, next;

  explicit Node(T val) : data(val), prev(nullptr), next(nullptr)
  {
  }

  Node(const Node &other) : data(other.data), prev(other.prev), next(other.next)
  {
  }
};

template< typename T >
class anikanov::List< T >::Iterator {
public:
  using node_t = Node;
  using this_t = Iterator;

  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T*;
  using reference = T&;
  using iterator_category = std::bidirectional_iterator_tag;

  Iterator();
  explicit Iterator(std::shared_ptr< node_t > node_ptr) : node(node_ptr)
  {
  }
  Iterator(const this_t &other) : node(other.node)
  {
  }
  ~Iterator() = default;

  std::shared_ptr< Node > get_node() const;
  this_t &operator=(const this_t &);
  Iterator operator+(int n) const;
  Iterator operator-(int n) const;
  std::ptrdiff_t operator-(const this_t &other) const;
  Iterator &operator+=(int n);
  Iterator &operator-=(int n);
  this_t &operator++();
  this_t operator++(int);
  this_t &operator--();
  this_t operator--(int);
  T &operator*();
  T *operator->();
  const T &operator*() const;
  const T *operator->() const;
  bool operator!=(const this_t &other) const;
  bool operator==(const this_t &other) const;
  bool operator<(const this_t &other) const {
    return node->data < other.node->data;
  }

private:
  std::shared_ptr< node_t > node;
};

template< typename T >
class anikanov::List< T >::ConstIterator {
public:
  using node_t = Node;
  using this_t = ConstIterator;
  using iterator_t = typename List< T >::Iterator;

  ConstIterator();
  explicit ConstIterator(std::shared_ptr< node_t > node_ptr) : itr(Iterator(node_ptr))
  {
  }
  explicit ConstIterator(const iterator_t &itr) : itr(itr)
  {
  }
  ConstIterator(const this_t &other) : itr(other.itr)
  {
  }
  ~ConstIterator() = default;

  this_t &operator=(const this_t &other);
  ConstIterator operator+(int n) const;
  ConstIterator operator-(int n) const;
  ConstIterator &operator+=(int n);
  ConstIterator &operator-=(int n);
  this_t &operator++();
  this_t operator++(int);
  this_t &operator--();
  this_t operator--(int);
  const T &operator*() const;
  const T *operator->() const;
  bool operator!=(const this_t &other) const;
  bool operator==(const this_t &other) const;
private:
  std::shared_ptr< Node > get_node() const;
  iterator_t itr;
};

template<typename T>
template<typename Compare >
typename anikanov::List< T >::Iterator anikanov::List< T >::merge(Iterator first, Iterator second, Compare comp) {
  List< T > result;
  Iterator it1 = first;
  Iterator it2 = second;

  while (it1 != end() && it2 != end()) {
    if (comp(*it1, *it2)) {
      result.push_back(*it1);
      ++it1;
    } else {
      result.push_back(*it2);
      ++it2;
    }
  }

  while (it1 != end()) {
    result.push_back(*it1);
    ++it1;
  }

  while (it2 != end()) {
    result.push_back(*it2);
    ++it2;
  }

  return result.begin();
}

template< typename T >
template<typename Compare >
typename anikanov::List< T >::Iterator anikanov::List< T >::mergeSort(Iterator start, Iterator end, Compare comp) {
  if (start == end || std::next(start) == end) {
    return start;
  }

  Iterator middle = start;
  Iterator temp = start;
  while (temp != end && std::next(temp) != end) {
    ++middle;
    ++temp;
    ++temp;
  }

  Iterator left = mergeSort(start, middle, comp);
  Iterator right = mergeSort(middle, end, comp);

  return merge(left, right, comp);
}

template< typename T >
template< typename Compare >
void anikanov::List<T>::sort(Compare comp) {
  if (!empty()) {
    mergeSort(begin(), end(), comp);
  }
}


template< typename T >
bool anikanov::List< T >::ConstIterator::operator==(const List< T >::ConstIterator &other) const
{
  return itr == other.itr;
}

template< typename T >
bool anikanov::List< T >::ConstIterator::operator!=(const List< T >::ConstIterator &other) const
{
  return itr != other.itr;
}

template< typename T >
const T *anikanov::List< T >::ConstIterator::operator->() const
{
  return itr.operator->();
}

template< typename T >
const T &anikanov::List< T >::ConstIterator::operator*() const
{
  return *itr;
}

template< typename T >
typename anikanov::List< T >::ConstIterator anikanov::List< T >::ConstIterator::operator--(int)
{
  auto tmp = *this;
  itr--;
  return tmp;
}

template< typename T >
typename anikanov::List< T >::ConstIterator &anikanov::List< T >::ConstIterator::operator--()
{
  --itr;
  return *this;
}

template< typename T >
typename anikanov::List< T >::ConstIterator anikanov::List< T >::ConstIterator::operator++(int)
{
  auto tmp = *this;
  itr++;
  return tmp;
}

template< typename T >
typename anikanov::List< T >::ConstIterator &anikanov::List< T >::ConstIterator::operator++()
{
  ++itr;
  return *this;
}

template< typename T >
typename anikanov::List< T >::ConstIterator &anikanov::List< T >::ConstIterator::operator-=(int n)
{
  itr -= n;
  return *this;
}

template< typename T >
typename anikanov::List< T >::ConstIterator &anikanov::List< T >::ConstIterator::operator+=(int n)
{
  itr += n;
  return *this;
}

template< typename T >
typename anikanov::List< T >::ConstIterator anikanov::List< T >::ConstIterator::operator-(int n) const
{
  return itr - n;
}

template< typename T >
typename anikanov::List< T >::ConstIterator anikanov::List< T >::ConstIterator::operator+(int n) const
{
  return itr + n;
}

template< typename T >
typename anikanov::List< T >::ConstIterator
&anikanov::List< T >::ConstIterator::operator=(const anikanov::List< T >::ConstIterator &other)
{
  itr = other.itr;
  return *this;
}

template< typename T >
std::shared_ptr< typename anikanov::List< T >::Node > anikanov::List< T >::ConstIterator::get_node() const
{
  return itr.get_node();
}

template< typename T >
anikanov::List< T >::ConstIterator::ConstIterator()
{
  itr = nullptr;
}

template< typename T >
anikanov::List< T >::Iterator::Iterator()
{
  node = nullptr;
}

template< typename T >
std::shared_ptr< typename anikanov::List< T >::Node > anikanov::List< T >::Iterator::get_node() const
{
  return node;
}

template< typename T >
typename anikanov::List< T >::Iterator &anikanov::List< T >::Iterator::operator=(const typename Iterator::this_t &other)
{
  node = other.node;
  return *this;
}

template< typename T >
typename anikanov::List< T >::Iterator anikanov::List< T >::Iterator::operator+(int n) const
{
  anikanov::List< T >::Iterator tmp = *this;
  for (int i = 0; i < n && tmp.node != nullptr; ++i) {
    ++tmp;
  }
  return tmp;
}

template< typename T >
typename anikanov::List< T >::Iterator anikanov::List< T >::Iterator::operator-(int n) const
{
  anikanov::List< T >::Iterator tmp = *this;
  for (int i = 0; i < n && tmp.node != nullptr; ++i) {
    --tmp;
  }
  return tmp;
}

template< typename T >
typename std::ptrdiff_t anikanov::List< T >::Iterator::operator-(const this_t &other) const
{
  std::ptrdiff_t count = 0;
  auto current = other.node;
  while (current != node) {
    current = current->next;
    ++count;
  }
  return count;
}

template< typename T >
typename anikanov::List< T >::Iterator &anikanov::List< T >::Iterator::operator+=(int n)
{
  for (int i = 0; i < n && this->node != nullptr; ++i) {
    ++(*this);
  }
  return *this;
}

template< typename T >
typename anikanov::List< T >::Iterator &anikanov::List< T >::Iterator::operator-=(int n)
{
  for (int i = 0; i < n && this->node != nullptr; ++i) {
    --(*this);
  }
  return *this;
}

template< typename T >
typename anikanov::List< T >::Iterator::this_t &anikanov::List< T >::Iterator::operator++()
{
  if (node) {
    node = node->next;
  }
  return *this;
}

template< typename T >
typename anikanov::List< T >::Iterator::this_t anikanov::List< T >::Iterator::operator++(int)
{
  this_t tmp = *this;
  ++(*this);
  return tmp;
}

template< typename T >
typename anikanov::List< T >::Iterator::this_t &anikanov::List< T >::Iterator::operator--()
{
  if (node) {
    node = node->prev;
  }
  return *this;
}

template< typename T >
typename anikanov::List< T >::Iterator::this_t anikanov::List< T >::Iterator::operator--(int)
{
  this_t tmp = *this;
  --(*this);
  return tmp;
}

template< typename T >
T &anikanov::List< T >::Iterator::operator*()
{
  return node->data;
}

template< typename T >
const T &anikanov::List< T >::Iterator::operator*() const
{
  return node->data;
}

template< typename T >
T *anikanov::List< T >::Iterator::operator->()
{
  return &(node->data);
}

template< typename T >
const T *anikanov::List< T >::Iterator::operator->() const
{
  return &(node->data);
}

template< typename T >
bool anikanov::List< T >::Iterator::operator!=(const this_t &other) const
{
  return node != other.node;
}

template< typename T >
bool anikanov::List< T >::Iterator::operator==(const this_t &other) const
{
  return node == other.node;
}

template< typename T >
anikanov::List< T > &anikanov::List< T >::operator=(const List< T > &other)
{
  if (this == &other) {
    return *this;
  }

  clear();
  for (auto elem: other) {
    push_back(elem);
  }
  return *this;
}

template< typename T >
anikanov::List< T > &anikanov::List< T >::operator=(List< T > &&other) noexcept
{
  if (this != &other) {
    clear();

    head = other.head;
    tail = other.tail;

    other.head = nullptr;
    other.tail = nullptr;
  }
  return *this;
}

template< typename T >
anikanov::List< T >::List() : head(nullptr), tail(nullptr), list_size(0)
{
}

template< typename T >
anikanov::List< T >::List(const List &other): head(nullptr), tail(nullptr), list_size(0)
{
  auto current = other.head;
  while (current != nullptr) {
    (*this).push_back(current->data);
    current = current->next;
  }
}

template< typename T >
anikanov::List< T >::List(List &&other) noexcept
{
  head = std::move(other.head);
  tail = std::move(other.tail);
  list_size = other.list_size;
  other.head = nullptr;
  other.tail = nullptr;
  other.list_size = 0;
}

template< typename T >
anikanov::List< T >::List(const T &value, size_t count): head(nullptr), tail(nullptr), list_size(0)
{
  for (size_t i = 0; i < count; ++i) {
    push_back(value);
  }
}

template< typename T >
anikanov::List< T >::List(std::initializer_list< T > init): head(nullptr), tail(nullptr), list_size(0)
{
  for (auto &element: init) {
    push_back(element);
  }
}

template< typename T >
anikanov::List< T >::List(List::Iterator first, List::Iterator last): head(nullptr), tail(nullptr), list_size(0)
{
  for (; first != last; ++first) {
    push_back(*first);
  }
}

template< typename T >
anikanov::List< T >::~List()
{
  this->clear();
}

template< typename T >
void anikanov::List< T >::push_back(const T &value)
{
  auto newNode = std::make_shared< List::Node >(value);
  if (head == nullptr) {
    head = newNode;
    tail = newNode;
  } else {
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
  }
  list_size++;
}

template< typename T >
void anikanov::List< T >::pop(size_t n)
{
  if (list_size == 0) {
    throw std::out_of_range("List is empty");
  }

  if (n == std::numeric_limits< size_t >::max()) {
    n = list_size - 1;
  }

  if (n >= list_size) {
    throw std::out_of_range("Index out of range");
  }
  auto current = head;
  for (size_t i = 0; i < n; ++i) {
    current = current->next;
  }

  if (current->prev != nullptr) {
    current->prev->next = current->next;
  } else {
    head = current->next;
  }

  if (current->next != nullptr) {
    current->next->prev = current->prev;
  } else {
    tail = current->prev;
  }

  --list_size;
}

template< typename T >
bool anikanov::List< T >::empty() const
{
  if (head == nullptr) {
    return true;
  }
  return false;
}

template< typename T >
size_t anikanov::List< T >::size() const
{
  return list_size;
}

template< typename T >
void anikanov::List< T >::clear()
{
  auto current = tail;
  while (current != nullptr) {
    auto prev = current->prev;
    current->next = nullptr;
    current->prev = nullptr;
    current = prev;
    list_size--;
  }
  head = nullptr;
  tail = nullptr;
}

template< typename T >
void anikanov::List< T >::swap(const List &other) noexcept
{
  head = std::move(other.head);
  tail = std::move(other.tail);
}

template< typename T >
void anikanov::List< T >::remove(const T &value)
{
  remove_if([value](T &other) {
    return value == other;
  });
}

template< typename T >
void anikanov::List< T >::remove_if(bool(*pred)(T))
{
  auto current = head;
  while (current != nullptr) {
    if (pred(current->data)) {
      auto toDelete = current;
      if (current->prev != nullptr) {
        current->prev->next = current->next;
      } else {
        head = current->next;
      }
      if (current->next != nullptr) {
        current->next->prev = current->prev;
      } else {
        tail = current->prev;
      }
      current = current->next;
      delete toDelete;
      --list_size;
    } else {
      current = current->next;
    }
  }
}

template< typename T >
void anikanov::List< T >::reverse()
{
  List< T > new_list;
  for (int i = list_size - 1; i > -1; --i) {
    new_list.push_back((*this)[i]);
  }
  (*this).clear();
  for (int i = 0; i < new_list.size(); ++i) {
    (*this).push_back(new_list[i]);
  }
}

template< typename T >
void anikanov::List< T >::splice(List::Iterator position, List< T > &other, List::Iterator first, List::Iterator last)
{
  if (first == last || &other == this) {
    return;
  }

  auto current = first;
  bool extra = false;
  if (list_size == 0) {
    (*this).push_back(0);
    extra = true;
    position = (*this).begin();
  }

  while (current != last) {
    position = insert(position, *current);
    position++;
    current = other.erase(current);
  }
  if (extra) {
    (*this).pop();
  }
}

template< typename T >
typename anikanov::List< T >::Iterator anikanov::List< T >::insert(List::Iterator pos, const T &value)
{
  auto newNode = std::make_shared< Node >(value);
  auto posNode = pos.get_node();
  if (pos == (*this).begin()) {
    newNode->next = head;
    if (head) {
      head->prev = newNode;
    } else {
      tail = newNode;
    }
    head = newNode;
  } else {
    auto prevNode = posNode->prev;
    newNode->next = posNode;
    newNode->prev = prevNode;
    posNode->prev = newNode;
    if (prevNode) {
      prevNode->next = newNode;
    }
  }
  ++list_size;
  return Iterator(newNode);
}

template< typename T >
typename anikanov::List< T >::Iterator anikanov::List< T >::erase(List::Iterator pos)
{
  auto posNode = pos.get_node();
  if (posNode->prev) {
    posNode->prev->next = posNode->next;
  }
  if (posNode->next) {
    posNode->next->prev = posNode->prev;
  }
  return Iterator(posNode->next);
}

template< typename T >
typename anikanov::List< T >::Iterator anikanov::List< T >::erase(List::Iterator begin, List::Iterator end)
{
  Iterator it = begin;

  while (it != end) {
    Iterator next = it;
    ++next;
    auto current_node = it.get_node();
    if (current_node->prev != nullptr) {
      current_node->prev->next = current_node->next;
    } else {
      head = current_node->next;
    }

    if (current_node->next != nullptr) {
      current_node->next->prev = current_node->prev;
    } else {
      tail = current_node->prev;
    }

    it = next;
  }

  return end;
}

template< typename T >
void anikanov::List< T >::assign(size_t count, const T &value)
{
  clear();
  for (size_t i = 0; i < count; ++i) {
    push_back(value);
  }
}

template< typename T >
void anikanov::List< T >::assign(std::initializer_list< T > ilist)
{
  for (auto &element: ilist) {
    push_back(element);
  }
}

template< typename T >
void anikanov::List< T >::assign(List::Iterator first, List::Iterator last)
{
  (*this).clear();
  for (auto cur = first; cur != last; ++cur) {
    (*this).push_back(*cur);
  }
}

template< typename T >
anikanov::List< T > anikanov::List< T >::copy()
{
  List< T > newList;

  std::shared_ptr< Node >
      current = head;
  while (current != nullptr) {
    newList.push_back(current->data);
    current = current->next;
  }

  return newList;
}

template< typename T >
T &anikanov::List< T >::operator[](size_t index)
{
  if (index >= list_size) {
    throw std::out_of_range("Index out of range");
  }

  auto current = head;
  for (size_t i = 0; i < index; ++i) {
    current = current->next;
  }

  return current->data;
}

template< typename T >
typename anikanov::List< T >::Iterator anikanov::List< T >::back()
{
  return Iterator(tail);
}

template< typename T >
typename anikanov::List< T >::Iterator anikanov::List< T >::begin()
{
  return Iterator(head);
}

template< typename T >
typename anikanov::List< T >::ConstIterator anikanov::List< T >::begin() const
{
  return ConstIterator(head);
}

template< typename T >
typename anikanov::List< T >::Iterator anikanov::List< T >::end() noexcept
{
  return Iterator(nullptr);
}

template< typename T >
typename anikanov::List< T >::ConstIterator anikanov::List< T >::end() const noexcept
{
  return ConstIterator(nullptr);
}

#endif
