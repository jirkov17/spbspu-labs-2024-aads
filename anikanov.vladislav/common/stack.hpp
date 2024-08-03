#ifndef STACK_HPP
#define STACK_HPP

#include <cassert>
#include <list.hpp>

namespace anikanov {

  template< typename T >
  class Stack {
  public:
    Stack() = default;
    Stack(const Stack &rhs);
    Stack(const Stack &&rhs) noexcept;
    ~Stack() = default;

    T &top() noexcept;
    const T &top() const noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const;

    void push(const T &value);
    void pop();
  private:
    List< T > list;
  };
}

template< typename T >
anikanov::Stack< T >::Stack(const Stack &rhs)
{
  list = rhs.list;
}

template< typename T >
anikanov::Stack< T >::Stack(const Stack &&rhs) noexcept
{
  list = std::move(rhs.list);
}

template< typename T >
T &anikanov::Stack< T >::top() noexcept
{
  assert(!list.empty());
  return list[list.size() - 1];
}

template< typename T >
const T &anikanov::Stack< T >::top() const noexcept
{
  assert(!list.empty());
  return list[list.size() - 1];
}

template< typename T >
bool anikanov::Stack< T >::isEmpty() const noexcept
{
  return list.empty();
}

template< typename T >
size_t anikanov::Stack< T >::getSize() const
{
  return list.size();
}

template< typename T >
void anikanov::Stack< T >::push(const T &value)
{
  list.push_back(value);
}

template< typename T >
void anikanov::Stack< T >::pop()
{
  assert(!list.empty());
  list.pop();
}

#endif
