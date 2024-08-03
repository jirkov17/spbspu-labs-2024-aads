#ifndef LIST_HPP
#define LIST_HPP
#include <node.hpp>
#include <cstddef>

namespace sobolevsky
{

  template< typename T >
  class List
  {
  public:
    Node< T > * head;
    Node< T > * tail;

    List();
    List(size_t n, const T & val);
    ~List();

    void pushFront(const T data, std::string nameIn);
    void pushBack(const T data, std::string nameIn);
    void popFront();
    void popBack();
    void clear();
    void swap(List * list1, List * list2);
    void remove(T val);
    template< typename Predicate >
    void remove_if(Predicate pred);
    void assign(size_t n, const T & val);
    bool empty();
    size_t getSize();
    Node< T > * getAt(size_t index);
    Node< T > * operator [] (size_t index);
  private:
    size_t size = 0;
  };
}

template< typename T >
sobolevsky::List< T >::List()
{
  head = nullptr;
  tail = nullptr;
}

template< typename T >
sobolevsky::List< T >::List(size_t n, const T & val)
{
  for (size_t i = 0; i < n; i++)
  {
    pushBack(val);
  }
}

template< typename T >
sobolevsky::List< T >::~List()
{
  clear();
}

template< typename T >
void sobolevsky::List< T >::pushFront(const T data, std::string nameIn)
{
  Node< T > * ptr = new sobolevsky::Node< T >(data, nameIn);
  ptr->next = head;
  if (head != nullptr)
  {
    head->prev = ptr;
  }
  if (tail == nullptr)
  {
    tail = ptr;
  }
  head = ptr;
  size++;
}

template< typename T >
void sobolevsky::List< T >::pushBack(const T data, std::string nameIn)
{
  Node< T > * ptr = new Node< T >(data, nameIn);
  ptr->prev = tail;
  if (tail != nullptr)
  {
    tail->next = ptr;
  }
  if (head == nullptr)
  {
    head = ptr;
  }
  tail = ptr;
  size++;
}

template< typename T >
void sobolevsky::List< T >::popFront()
{
  if (head == nullptr)
  {
    return;
  }

  Node< T > * ptr = head->next;
  if (ptr == nullptr)
  {
    tail = nullptr;
  }
  else
  {
    ptr->prev = nullptr;
  }

  delete head;
  size--;
  head = ptr;
}

template< typename T >
void sobolevsky::List< T >::popBack()
{
  if (tail == nullptr)
  {
    return;
  }

  Node< T > * ptr = tail->prev;
  if (ptr == nullptr)
  {
    head = nullptr;
  }
  else
  {
    ptr->next = nullptr;
  }

  delete tail;
  size--;
  tail = ptr;
}

template< typename T >
void sobolevsky::List< T >::clear()
{
  while (head != nullptr)
  {
    popFront();
  }
}

template< typename T >
void sobolevsky::List< T >::swap(List * list1, List * list2)
{
  if (list1 != nullptr && list2 != nullptr)
  {
    Node< T > * tempHead;
    Node< T > * tempTail;
    size_t tempSize;

    tempHead = list1->head;
    tempTail = list1->tail;
    tempSize = list1->size;

    list1->head = list2->head;
    list1->tail = list2->tail;
    list1->size = list2->size;

    list2->head = tempHead->head;
    list2->tail = tempTail->tail;
    list2->size = tempSize;

    delete tempHead;
    delete tempTail;
  }
}

template< typename T >
void sobolevsky::List< T >::remove(T val)
{
  Node< T > * ptr = head;
  Node< T > * tempPtr = nullptr;
  while (ptr != nullptr)
  {
    tempPtr = ptr.next;
    if (ptr->data == val)
    {
      if (ptr->prev == nullptr)
      {
        ptr->next.prev = ptr->prev;
        delete ptr;
      }
      else if (ptr->next == nullptr)
      {
        ptr->prev.next = ptr->next;
        delete ptr;
      }
      else
      {
        ptr->prev.next = ptr->next;
        ptr->next.prev = ptr->prev;
        delete ptr;
      }
    }
    ptr = tempPtr;
    size--;
  }
}

template< typename T >
template< typename Predicate >
void sobolevsky::List< T >::remove_if(Predicate pred)
{
  Node< T > * ptr = head;
  Node< T > * tempPtr = nullptr;
  while (ptr != nullptr)
  {
    tempPtr = ptr.next;
    if (pred(ptr))
    {
      if (ptr->prev == nullptr)
      {
        ptr->next.prev = ptr->prev;
        delete ptr;
      }
      else if (ptr->next == nullptr)
      {
        ptr->prev.next = ptr->next;
        delete ptr;
      }
      else
      {
        ptr->prev.next = ptr->next;
        ptr->next.prev = ptr->prev;
        delete ptr;
      }
    }
    ptr = tempPtr;
    size--;
  }
}

template< typename T >
void sobolevsky::List< T >::assign(size_t n, const T & val)
{
  clear();
  for (size_t i = 0; i < n; i++)
  {
    pushBack(val);
  }
}

template< typename T >
bool sobolevsky::List< T >::empty()
{
  return (size == 0);
}

template< typename T >
size_t sobolevsky::List< T >::getSize()
{
  return size;
}

template< typename T >
sobolevsky::Node< T > * sobolevsky::List< T >::getAt(size_t index)
{
  sobolevsky::Node< T > * ptr = head;
  size_t n = 0;

  while(n != index)
  {
    if (ptr == nullptr)
    {
      return ptr;
    }
    ptr = ptr->next;
    n++;
  }

  return ptr;
}

template< typename T >
sobolevsky::Node< T > * sobolevsky::List< T >::operator [] (size_t index)
{
  return getAt(index);
}

#endif
