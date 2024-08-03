#ifndef MAINEARRAY_HPP
#define MAINEARRAY_HPP

#include <iostream>

namespace kaseev {
  template< class T >
  class List {
  public:
    class Iterator;
    class ConstIterator;

    List();
    ~List();
    explicit List(size_t count);
    List(size_t count, const T& value);
    List(std::initializer_list< T > ilist);
    List(const List& other);

    T& front();

    void pushBack(const T &value);
    void push_front(const T& data);
    void pop_front();
    void pop_back();
    void pop(int index);
    void clear();
    void swap(List &other) noexcept;

    bool empty() const noexcept;
    int size() const;

    void remove(const T &value);
    template< class UnaryPredicate >
    void remove_if(UnaryPredicate p);

    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator begin() const noexcept;
    ConstIterator end() const noexcept;

    const T &operator[](int index) const;
    List< T >& operator=(const List< T >& other);

  private:
    int ArrSize;
    template < class N >
    class Node {
    public:
      N data;
      Node< N >* next;

      explicit Node(const N& value) : data(value), next(nullptr) {}
    };

    Node< T > *head;
  };

  template< class T >
  List< T >::~List()
  {
    clear();
  }

  template< class T >
  List< T >::List()
  {
    ArrSize = 0;
    head = nullptr;
  }

  template< class T >
  void List< T >::pushBack(const T &value)
  {
    Node< T > *newNode = new Node< T >(value);
    if (head == nullptr)
    {
      head = newNode;
    }
    else
    {
      Node< T > *current = head;
      while (current->next != nullptr)
      {
        current = current->next;
      }
      current->next = newNode;
    }
    ArrSize++;
  }

  template< class T >
  bool List< T >::empty() const noexcept
  {
    return head == nullptr;
  }

  template< class T >
  int List< T >::size() const
  {
    return ArrSize;
  }

  template< class T >
  void List< T >::pop_front()
  {
    if (head == nullptr)
    {
      ArrSize = 0;
      throw std::logic_error("empty list");
    }
    Node< T > *temp = head;
    head = head->next;
    temp->next = nullptr;
    delete temp;
    ArrSize--;
  }

  template< class T >
  void List< T >::clear()
  {
    while (head != nullptr)
    {
      pop_front();
    }
  }

  template< class T >
  void List< T >::pop(int index)
  {
    if (index < 0 || index >= ArrSize)
    {
      throw std::out_of_range("Index out of range");
    }
    Node< T > *current = head;
    Node< T > *prev = nullptr;
    for (int i = 0; i < index; ++i)
    {
      prev = current;
      current = current->next;
    }
    if (prev != nullptr)
    {
      prev->next = current->next;
    }
    else
    {
      head = current->next;
    }
    delete current;
    ArrSize--;
  }

  template< class T >
  void List< T >::remove(const T &value)
  {
    Node< T > *prev = nullptr;
    Node< T > *current = head;
    while (current != nullptr)
    {
      if (current->data == value)
      {
        if (prev == nullptr)
        {
          pop_front();
          current = head;
        }
        else
        {
          prev->next = current->next;
          delete current;
          current = prev->next;
          ArrSize--;
        }
      }
      else
      {
        prev = current;
        current = current->next;
      }
    }
  }

  template< class T >
  T& List< T >::front()
  {
    if (empty())
    {
      throw std::logic_error("List is empty");
    }
    return head->data;
  }

  template< class T >
  template< class UnaryPredicate >
  void List< T >::remove_if(UnaryPredicate p)
  {
    while (!empty() && p(front()))
    {
      pop_front();
    }
    Node< T >* prev = nullptr;
    Node< T >* current = head;
    while (current != nullptr)
    {
      if (p(current->data))
      {
        if (prev == nullptr)
        {
          pop_front();
          current = head;
        }
        else
        {
          prev->next = current->next;
          delete current;
          current = prev->next;
          ArrSize--;
        }
      }
      else
      {
        prev = current;
        current = current->next;
      }
    }
  }

  template< class T >
  void List< T >::swap(List &other) noexcept
  {
    std::swap(head, other.head);
    std::swap(ArrSize, other.ArrSize);
  }

  template< class T >
  void List< T >::push_front(const T& data)
  {
    pushBack(data);
    for (int i = size() - 1; i > 0; --i)
    {
      std::swap((*this)[i], (*this)[i - 1]);
    }
  }

  template< class T >
  void List< T >::pop_back()
  {
    if (empty())
    {
      throw std::logic_error("empty list");
    }
    pop(size() - 1);
  }

  template< class T >
  const T &List< T >::operator[](int index) const
  {
    if (index >= ArrSize)
    {
      throw std::out_of_range("Index out of range");
    }
    Node< T > *current = head;
    for (int i = 0; i < index; ++i)
    {
      current = current->next;
    }
    return current->data;
  }

  template< class T >
  List< T >::List(const List& other) : ArrSize(0), head(nullptr)
  {
    Node< T >* current = other.head;
    while (current != nullptr)
    {
      pushBack(current->data);
      current = current->next;
    }
  }

  template< class T >
  List< T >& List< T >::operator=(const List< T >& other)
  {
    if (this != &other)
    {
      clear();
      Node< T >* current = other.head;
      while (current != nullptr)
      {
        pushBack(current->data);
        current = current->next;
      }
    }
    return *this;
  }

  template< class T >
  List< T >::List(size_t count) : ArrSize(0), head(nullptr)
  {
    for (size_t i = 0; i < count; ++i)
    {
      pushBack(T());
    }
  }

  template< class T >
  List< T >::List(size_t count, const T& value) : ArrSize(0), head(nullptr)
  {
    for (size_t i = 0; i < count; ++i)
    {
      pushBack(value);
    }
  }

  template< class T >
  List< T >::List(std::initializer_list< T > ilist) : ArrSize(0), head(nullptr)
  {
    for (const auto& elem: ilist)
    {
      pushBack(elem);
    }
  }

  template< typename T >
  class kaseev::List< T >::Iterator {
  public:
    List< T >* Node;
    using this_t = Iterator;

    Iterator();
    ~Iterator() = default;
    Iterator(const this_t &) = default;
    this_t& operator=(const this_t &) = default;

    this_t& operator++();
    this_t operator++(int);

    T& operator*();
    T* operator->();

    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;
  };

  template< typename T >
  kaseev::List< T >::Iterator::Iterator() : Node(nullptr)
  {}

  template< typename T >
  typename kaseev::List< T >::Iterator& List< T >::Iterator::operator++()
  {
    if (Node != nullptr)
    {
      Node = Node->next;
    }
    return *this;
  }

  template< typename T >
  typename kaseev::List< T >::Iterator List< T >::Iterator::operator++(int)
  {
    Iterator temp = *this;
    ++(*this);
    return temp;
  }

  template< typename T >
  T& kaseev::List< T >::Iterator::operator*()
  {
    if (Node != nullptr)
    {
      return Node->data;
    }
  }

  template< typename T >
  T* kaseev::List< T >::Iterator::operator->()
  {
    return std::addressof(Node->data);
  }

  template< typename T >
  bool List< T >::Iterator::operator!=(const Iterator& other) const
  {
    return Node != other.Node;
  }

  template< typename T >
  bool List< T >::Iterator::operator==(const Iterator& other) const
  {
    return Node == other.Node;
  }

  template< typename T >
  class List< T >::ConstIterator {
  public:
    const List< T > *Node;
    using this_t = ConstIterator;

    ConstIterator();
    ~ConstIterator() = default;
    ConstIterator(const this_t &) = default;
    this_t &operator=(const this_t &) = default;

    this_t& operator++();
    this_t operator++(int);

    const T& operator*() const;
    const T* operator->() const;

    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;
  };

  template< typename T >
  List< T >::ConstIterator::ConstIterator() : Node(nullptr)
  {}

  template< typename T >
  typename List< T >::ConstIterator& List< T >::ConstIterator::operator++()
  {
    Node = Node->next;
    return *this;
  }

  template< typename T >
  typename List< T >::ConstIterator List< T >::ConstIterator::operator++(int)
  {
    ConstIterator temp(*this);
    ++(*this);
    return temp;
  }

  template< typename T >
  const T& List< T >::ConstIterator::operator*() const
  {
    return *(Node->data);
  }

  template< typename T >
  const T* List< T >::ConstIterator::operator->() const
  {
    return std::addressof(Node->data);
  }

  template< typename T >
  bool List< T >::ConstIterator::operator!=(const ConstIterator& other) const
  {
    return Node != other.Node;
  }

  template< typename T >
  bool List< T >::ConstIterator::operator==(const ConstIterator& other) const
  {
    return Node == other.Node;
  }

  template< typename T >
  typename List< T >::Iterator List< T >::begin() noexcept
  {
    Iterator it;
    it.Node = head;
    return it;
  }

  template< typename T >
  typename List< T >::Iterator List< T >::end() noexcept
  {
    Iterator it;
    it.Node = nullptr;
    return it;
  }

  template< typename T >
  typename List< T >::ConstIterator List< T >::begin() const noexcept
  {
    ConstIterator it;
    it.Node = head;
    return it;
  }

  template< typename T >
  typename List< T >::ConstIterator List< T >::end() const noexcept
  {
    ConstIterator it;
    it.Node = nullptr;
    return it;
  }

}

#endif
