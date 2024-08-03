#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <list.hpp>

namespace psarev
{
  template < typename T >
  class Queue
  {
  public:
    Queue() = default;
    Queue(const Queue& other);
    explicit Queue(const List< T >& dep);
    ~Queue() = default;

    Queue< T >& operator=(const Queue& other);

    T& getFront() const;
    T& getBack() const;

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
psarev::Queue< T >::Queue(const Queue& other)
{
  depot = other.depot;
}

template < typename T >
psarev::Queue< T >::Queue(const psarev::List< T >& dep)
{
  depot(dep);
}

template < typename T >
psarev::Queue< T >& psarev::Queue< T >::operator=(const Queue& other)
{
  depot = other.dep;
}

template < typename T >
T& psarev::Queue< T >::getFront() const
{
  return depot.getFront();
}

template < typename T >
T& psarev::Queue< T >::getBack() const
{
  return depot.getBack();
}

template < typename T >
void psarev::Queue< T >::push(const T& data)
{
  depot.pushBack(data);
}

template < typename T >
void psarev::Queue< T >::push(T&& data)
{
  depot.pushBack(data);
}

template < typename T >
void psarev::Queue< T >::pop()
{
  depot.popFront();
}

template<typename T>
size_t psarev::Queue<T>::getSize() const noexcept
{
  return depot.getSize();
}

template < typename T >
bool psarev::Queue< T >::isEmpty() const noexcept
{
  return depot.empty();
}

#endif
