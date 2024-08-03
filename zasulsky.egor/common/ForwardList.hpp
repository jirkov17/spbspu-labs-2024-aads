#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

#include <iterator>
#include <stdexcept>
#include "Node.hpp"

namespace zasulsky
{
  template < typename T >
  class iterator;

  template < typename T >
  class constIterator;

  template < class T >
  class ForwardList
  {
   public:
    using iter = iterator< T >;
    using constIter = constIterator< T >;

    ForwardList() :
      fakeNode_(nullptr)
    {}

    explicit ForwardList(detail::Node< T >* head) :
      fakeNode_(new detail::Node< T >)
    {
      fakeNode_->next = head;
    }

    ForwardList(const ForwardList& other) :
      fakeNode_(new detail::Node< T >)
    {
      fakeNode_->next = nullptr;
      insert_after(other.cbegin(), other.cend(), cbeforeBegin());
    }

    ForwardList(ForwardList&& other) :
      ForwardList(other.head())
    {
      other.head() = nullptr;
    }

    ~ForwardList()
    {
      clear();
      operator delete(fakeNode_, sizeof(detail::Node<T>));
    }

    ForwardList& operator=(const ForwardList& rhs)
    {
      if (this == std::addressof(rhs))
      {
        return *this;
      }
      try
      {
        clear();
        insert_after(rhs.cbegin(), rhs.cend(), cbeforeBegin());
      }
      catch (const std::bad_alloc&)
      {
        clear();
        throw;
      }
      return *this;
    }

    ForwardList& operator=(ForwardList&& rhs)
    {
      if (this == std::addressof(rhs))
      {
        return *this;
      }
      clear();
      head() = rhs.head();
      rhs.head() = nullptr;
      return *this;
    }

    iter begin()
    {
      if (fakeNode_ != nullptr)
      {
        return iter(fakeNode_->next);
      }
      return iter(nullptr);
    }

    iter beforeBegin()
    {
      return iter(fakeNode_);
    }

    iter end()
    {
      return iter(nullptr);
    }

    constIter cbegin() const
    {
      if (fakeNode_ != nullptr)
      {
        return constIter(fakeNode_->next);
      }
      return constIter(nullptr);
    }

    constIter cbeforeBegin() const
    {
      return constIter(fakeNode_);
    }

    constIter cend() const
    {
      return constIter();
    }

    iter insert_after(constIter it, T  data)
    {
      constIter res;
      checkFakeNode(it);
      checkIt(it);
      iter noConstIt(it);
      auto temp = noConstIt.current_->next;
      noConstIt.current_->next = new detail::Node< T >(data, temp);
      return ++noConstIt;
    }

    template < class inpIt >
    iter insert_after(inpIt begin, inpIt end, constIter beforeBegin)
    {
      iter noConstIt(beforeBegin);
      while (begin != end)
      {
        insert_after(noConstIt, *begin);
        begin++;
      }
      return ++noConstIt;
    }

    iter erase_after(constIter it)
    {
      checkIt(it);
      iter noConstIt(it);
      auto temp = noConstIt.current_->next;
      if (temp)
      {
        noConstIt.current_->next = temp->next;
        delete temp;
        return noConstIt++;
      }
      else
      {
        throw std::runtime_error("error");
      }
    }

    void pushFront(T value)
    {
      insert_after(cbeforeBegin(), value);
    }

    void popFront()
    {
      if (empty())
      {
        throw std::logic_error("ForwardList is empty");
      }
      erase_after(cbeforeBegin());
    }

    bool empty() const noexcept
    {
      if (fakeNode_ != nullptr)
      {
        return fakeNode_->next == nullptr;
      }
      else
      {
        return true;
      }
    }

    void clear()
    {
      if (fakeNode_ != nullptr)
      {
        while (!empty())
        {
          popFront();
        }
      }
    }

    T& front()
    {
      if (empty())
      {
        throw std::logic_error("ForwardList is empty");
      }
      return *begin();
    }

    T& back()
    {
      if (empty())
      {
        throw std::out_of_range("List is empty");
      }
      detail::Node< T >* current = fakeNode_->next;
      while (current->next)
      {
        current = current->next;
      }
      return current->data;
    }

    detail::Node< T >** getPtrHead()
    {
      return  fakeNode_ ? std::addressof(fakeNode_->next) : nullptr;
    }

    detail::Node< T >*& head()
    {
      return fakeNode_->next;
    }

    T& getHead()
    {
      if (fakeNode_->next != nullptr)
      {
        return fakeNode_->next->data;
      }
      else
      {
        throw std::logic_error("you can't got data from empty list");
      }
    }
    int size()
    {
      int count = 0;
      constIter it = cbegin();
      while (it != cend())
      {
        ++it;
        ++count;
      }
      return count;
    }

    void SpliceAfter(constIter it, ForwardList& fl)
    {
      detail::Node< T >* next = const_cast<detail::Node< T >* >(it.current_)->next;
      const_cast< detail::Node< T >* >(it.current_)->next = fl.head();
      while (it.current_->next)
      {
        ++it;
      }
      const_cast< detail::Node< T >* >(it.current_)->next = next;
      fl.head() = nullptr;
    }

  private:

    detail::Node< T >* fakeNode_;

    void checkIt(constIter it)
    {
      if (it.current_ == nullptr)
      {
        throw std::runtime_error("iterator is empty");
      }
    }

    void checkFakeNode(constIter & it)
    {
      if (fakeNode_ == nullptr)
      {
        fakeNode_ = new detail::Node<T>;
        constIter iter(fakeNode_);
        it = iter;
      }
    }
  };

  template < typename T >
  class iterator : public std::iterator < std::forward_iterator_tag, T >
  {
  public:
    friend ForwardList< T >;
    friend constIterator< T >;

    iterator() :
      current_(nullptr)
    {}

    iterator(detail::Node<T>* start) :
      current_(start)
    {}

    bool operator==(const iterator& other) const
    {
      return current_ == other.current_;
    }

    bool operator!=(const iterator& other) const
    {
      return !(*this == other);
    }

    T& operator*()
    {
      return current_->data;
    }

    T* operator->()
    {
      if (current_ == nullptr)
      {
        throw std::logic_error("uncorrect argument");
      }
      return std::addressof(current_->data);
    }

    iterator& operator++()
    {
      if (current_)
      {
        current_ = current_->next;
      }
      return *this;
    }

    iterator operator++(int)
    {
      iterator< T > temp = *this;
      ++(*this);
      return temp;
    }

    detail::Node < T >*& getCur()
    {
      return current_;
    }

  private:
    detail::Node< T >* current_;

    iterator(const constIterator<T>& other) :
      current_(const_cast<detail::Node <T>*> (other.current_))
    {}
  };

  template < class T >
  class constIterator : public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    friend ForwardList < T >;
    friend iterator < T >;

    constIterator() :
      current_(nullptr)
    {}

    constIterator(detail::Node< T >* start) :
      current_(start)
    {}

    constIterator(const iterator< T > other) noexcept :
      current_(other.current_)
    {}

    bool operator==(const constIterator& other) const
    {
      return current_ == other.current_;
    }

    bool operator!=(const constIterator& other) const
    {
      return !(*this == other);
    }

    const T& operator*() const
    {
      return current_->data;
    }

    const T* operator->() const
    {
      if (current_ == nullptr)
      {
        throw std::logic_error("->");
      }
      return std::addressof(current_->data);
    }

    constIterator& operator++()
    {
      if (current_)
      {
        current_ = current_->next;
      }
      return *this;
    }

    constIterator operator++(int)
    {
      constIterator< T > temp = *this;
      ++(*this);
      return temp;
    }

    detail::Node < T >*& getCur()
    {
      return current_;
    }

  private:
    detail::Node< T >* current_;
  };
}

#endif
