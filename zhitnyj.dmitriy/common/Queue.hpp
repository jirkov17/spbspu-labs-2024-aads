#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <stdexcept>
#include <List.hpp>

namespace zhitnyj {
  template< typename T >
  class Queue {
  public:
    Queue() = default;
    ~Queue() = default;
    Queue(const Queue &other) noexcept;
    Queue(Queue &&other) noexcept;
    Queue &operator=(const Queue &other);
    Queue &operator=(Queue &&other) noexcept;

    void push(const T &value) noexcept;
    void pop() noexcept;
    void clear() noexcept;
    bool empty() const noexcept;
    size_t size() const noexcept;

    T &front();
    T &front() const;

  private:
    List <T> list;
  };

  template< typename T >
  void Queue< T >::pop() noexcept {
    list.pop();
  }

  template< typename T >
  void Queue< T >::clear() noexcept {
    list.clear();
  }

  template< typename T >
  Queue< T >::Queue(const Queue &other) noexcept: list(other.list) {
  }

  template< typename T >
  Queue< T >::Queue(Queue &&other) noexcept : list(std::move(other.list)) {
  }

  template< typename T >
  Queue< T > &Queue< T >::operator=(const Queue &other) {
    if (this != &other) {
      list = other.list;
    }
    return *this;
  }

  template< typename T >
  Queue< T > &Queue< T >::operator=(Queue &&other) noexcept {
    if (this != &other) {
      list = std::move(other.list);
    }
    return *this;
  }

  template< typename T >
  bool Queue< T >::empty() const noexcept {
    return list.empty();
  }

  template< typename T >
  void Queue< T >::push(const T &value) noexcept {
    list.push_back(value);
  }

  template< typename T >
  size_t Queue< T >::size() const noexcept {
    return list.size();
  }

  template< typename T >
  T &Queue< T >::front() {
    if (list.empty()) {
      throw std::out_of_range("Queue is empty");
    }
    return list[0];
  }

  template< typename T >
  T &Queue< T >::front() const {
    if (list.empty()) {
      throw std::out_of_range("Queue is empty");
    }
    return list[0];
  }
}

#endif
