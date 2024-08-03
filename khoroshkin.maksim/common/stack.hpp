#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"

namespace khoroshkin
{
  template< typename T >
  class Stack
  {
  public:
    Stack();
    Stack(const Stack & rhs);
    Stack(Stack && rhs);
    ~Stack();

    Stack< T > & operator=(const Stack & rhs);
    Stack< T > & operator=(Stack && rhs);

    T & top() noexcept;
    const T & top() const noexcept;

    bool isEmpty() const;
    size_t getSize() const;

    void push(const T & value);
    void pop();
  private:
    List< T > stack;
  };
}

template< typename T >
khoroshkin::Stack< T >::Stack() :
  stack(List< T >())
{}

template< typename T >
khoroshkin::Stack< T >::Stack(const Stack & rhs)
{
  stack = rhs.stack;
}

template< typename T >
khoroshkin::Stack< T >::Stack(Stack && rhs) :
  stack(std::move(rhs.stack))
{}

template< typename T >
khoroshkin::Stack< T > & khoroshkin::Stack< T >::operator=(const Stack & rhs)
{
  stack = rhs.stack;
  return *this;
}

template< typename T >
khoroshkin::Stack< T > & khoroshkin::Stack< T >::operator=(Stack && rhs)
{
  stack = std::move(rhs.stack);
  return *this;
}

template< typename T >
khoroshkin::Stack< T >::~Stack()
{
  stack.clear();
}

template< typename T >
T & khoroshkin::Stack< T >::top() noexcept
{
  for (auto it = stack.begin(); it != stack.end(); it++)
  {
    if (next(it) == stack.end())
    {
      return *it;
    }
  }
  return *stack.begin();
}

template< typename T >
const T & khoroshkin::Stack< T >::top() const noexcept
{
  for (auto it = stack.begin(); it != stack.end(); it++)
  {
    if (next(it) == stack.end())
    {
      return *it;
    }
  }
  return *stack.begin();
}

template< typename T >
bool khoroshkin::Stack< T >::isEmpty() const
{
  return stack.isEmpty();
}

template< typename T >
size_t khoroshkin::Stack< T >::getSize() const
{
  return stack.getSize();
}

template< typename T >
void khoroshkin::Stack< T >::push(const T & value)
{
  try
  {
    stack.push_back(value);
  }
  catch(const std::bad_alloc & e)
  {
    stack.clear();
    throw e;
  }
}

template< typename T >
void khoroshkin::Stack< T >::pop()
{
  if (stack.isEmpty())
  {
    throw std::logic_error("stack is empty");
  }
  auto it_before = stack.begin();
  auto it = stack.begin();
  while (it != stack.end())
  {
    if (next(it) == stack.end())
    {
      break;
    }
    it_before = it;
    ++it;
  }
  stack.erase_after(it_before);
}

#endif
