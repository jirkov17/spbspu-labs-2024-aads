#ifndef STACK_HPP
#define STACK_HPP
#include "list.hpp"

namespace redko
{
  template < typename T >
  class Stack {
  public:
    Stack() : container_(List< T >()) {}
    explicit Stack(const List< T > & cont);
    Stack(const Stack< T > & other);
    Stack(Stack< T > && other);
    ~Stack() = default;

    Stack & operator=(const Stack & other);
    Stack & operator=(Stack && other);

    T & top();
    const T & top() const;

    bool empty() const;
    size_t size() const;

    void push(const T & value);
    void push(T && value);
    void pop();
    void swap(Stack& other) noexcept;

  private:
    List< T > container_;
  };
}

template < typename T >
redko::Stack< T >::Stack(const List< T > & cont):
  container_(cont)
{}

template < typename T >
redko::Stack< T >::Stack(const Stack & other):
  container_(other.container_)
{}

template < typename T >
redko::Stack< T >::Stack(Stack && other):
  container_(std::move(other.container_))
{}

template < typename T >
redko::Stack< T > & redko::Stack< T >::operator=(const Stack & other)
{
  container_ = other.container_;
}

template < typename T >
redko::Stack< T > & redko::Stack< T >::operator=(Stack && other)
{
  container_ = std::move(other.container_);
}

template < typename T >
T & redko::Stack< T >::top()
{
  return container_.front();
}

template < typename T >
const T & redko::Stack< T >::top() const
{
  return container_.front();
}

template < typename T >
bool redko::Stack< T >::empty() const
{
  return container_.isEmpty();
}

template < typename T >
size_t redko::Stack< T >::size() const
{
  size_t size = 0;
  typename List< T >::iterator curr = container_.begin();
  while (curr != container_.end())
  {
    ++size;
    ++curr;
  }
  return size;
}

template < typename T >
void redko::Stack< T >::push(const T & value)
{
  container_.pushFront(value);
}

template < typename T >
void redko::Stack< T >::push(T && value)
{
  container_.pushFront(value);
}

template < typename T >
void redko::Stack< T >::pop()
{
  container_.popFront();
}

template < typename T >
void redko::Stack< T >::swap(Stack & other) noexcept
{
  container_.swap(other.container);
}

#endif
