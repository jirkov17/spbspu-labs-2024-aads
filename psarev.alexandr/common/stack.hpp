#ifndef STACK_HPP
#define STACK_HPP
#include <list.hpp>

namespace psarev
{
  template < typename T >
  class Stack
  {
  public:
    Stack() = default;
    Stack(const Stack& other);
    explicit Stack(const List< T >& dep);
    ~Stack() = default;

    Stack< T >& operator=(const Stack& other);

    T& getTop() const;

    void push(const T& data);
    void push(T&& data);
    void pop();

    size_t getSize() const noexcept;
    bool isEmpty() const noexcept;
  private:
    List< T > depot;
  };
}

template < typename T >
psarev::Stack< T >::Stack(const Stack& other)
{
  depot = other.depot;
}

template < typename T >
psarev::Stack< T >::Stack(const List< T >& dep)
{
  depot(dep);
}

template < typename T >
psarev::Stack< T >& psarev::Stack< T >::operator=(const Stack& other)
{
  depot = other.dep;
}

template < typename T >
T& psarev::Stack< T >::getTop() const
{
  return depot.getFront();
}

template < typename T >
void psarev::Stack< T >::push(const T& data)
{
  depot.pushFront(data);
}

template < typename T >
void psarev::Stack< T >::push(T&& data)
{
  depot.pushFront(data);
}

template < typename T >
void psarev::Stack< T >::pop()
{
  depot.popFront();
}

template<typename T>
size_t psarev::Stack<T>::getSize() const noexcept
{
  return depot.getSize();
}

template < typename T >
bool psarev::Stack< T >::isEmpty() const noexcept
{
  return depot.empty();
}

#endif
