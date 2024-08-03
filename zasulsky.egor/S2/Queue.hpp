#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <ForwardList.hpp>

namespace zasulsky
{
  template < class T >
  class Queue
  {
  public:

    Queue() :
      forwardList(ForwardList< T >())
    {}

    Queue(const Queue& other) :
      forwardList(other.forwardList)
    {}

    Queue(Queue&& other) :
      forwardList(std::move(other.forwardList))
    {}

    ~Queue() = default;

    Queue& operator=(const Queue& rhs)
    {
      if (this == std::addressof(rhs))
      {
        return *this;
      }
      forwardList = rhs.forwardList;
      return *this;
    }

    Queue& operator=(Queue&& rhs)
    {
      if (this == std::addressof(rhs))
      {
        return *this;
      }
      forwardList = std::move(rhs.forwardList);
      return *this;
    }

    bool isEmpty() noexcept
    {
      return forwardList.empty();
    }

    void enqueue(const T & data)
    {
      if (this->isEmpty())
      {
        forwardList.insert_after(forwardList.cbeforeBegin(), data);
      }
      else
      {
        detail::Node< T >* temp = forwardList.head();
        while (temp->next != nullptr)
        {
          temp = temp->next;
        }
        constIterator< T > it(temp);
        forwardList.insert_after(it, data);
      }
    }

    const T & peek()
    {
      if (forwardList.head() != nullptr)
      {
        return forwardList.head()->data;
      }
      else
      {
        throw std::logic_error("empty container");
      }
    }

    void dequeue()
    {
      if (this->isEmpty())
      {
        throw std::logic_error("The list is empty!!");
      }
      else
      {
        forwardList.erase_after(forwardList.cbeforeBegin());
      }
    }

  private:

    ForwardList< T > forwardList;

  };
}

#endif
