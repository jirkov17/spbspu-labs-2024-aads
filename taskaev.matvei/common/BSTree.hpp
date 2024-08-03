#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <utility>
#include <cstddef>
#include <stdexcept>
#include <iterator>
#include <cassert>
#include <functional>
#include <algorithm>
#include "Queue.hpp"
#include "Stack.hpp"

namespace taskaev
{
  template< typename Key, typename Value, typename Comparator = std::less< Key > >
  class BSTree
  {
  public:
    class ConstIterator;
    class Iterator;
    using value_t = std::pair< Key, Value >;

    BSTree();
    BSTree(const BSTree& rhs);
    BSTree(BSTree&& rhs) noexcept;
    ~BSTree();

    Value& at(const Key& key);
    bool empty() const  noexcept;
    size_t size() const noexcept;
    void swap(BSTree& rhs) noexcept;

    void insert(const value_t& pair);
    void insert(const Key& key, const Value& value);

    void erase(const Key& key);

    Value& operator[](const Key& key);

    ConstIterator find(const Key& key) const;
    void clear();

    Iterator begin();
    Iterator end();

    ConstIterator cbegin() const;
    ConstIterator cend() const;

    template < typename F >
    F traverse_lnr(F f);

    template < typename F >
    F traverse_rnl(F f);

    template < typename F >
    F traverse_breadth(F f);

  private:
    class Node
    {
    public:
      friend class BSTree;
      Node(value_t data, Node* parent = nullptr, Node* right = nullptr, Node* left = nullptr, size_t h = 0) :
        data_(data),
        parent_(parent),
        right_(right),
        left_(left),
        height_(h)
      {}
    private:
      value_t data_;
      Node* parent_;
      Node* right_;
      Node* left_;
      size_t height_;
    };

    Node* root_;
    Comparator comp_;
    size_t size_;

    Node* balance(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    void updHeight(Node* node) noexcept;
    size_t getHeight(const Node* root) const noexcept ;
    size_t height(Node* node);

    void free(Node* node);
  };
}

namespace taskaev
{
  template < typename Key, typename Value >
  using value_t = std::pair< Key, Value >;

  template< typename Key, typename Value, typename Comparator >
  class BSTree< Key, Value, Comparator >::ConstIterator : public std::iterator< std::bidirectional_iterator_tag, value_t >
  {
  public:
    friend class BSTree< Key, Value, Comparator >;
    ConstIterator();
    ConstIterator(Node* node, Node* root);
    ConstIterator(const ConstIterator&) = default;
    ~ConstIterator() = default;

    ConstIterator& operator=(const ConstIterator&) = default;
    ConstIterator& operator++();
    ConstIterator operator++(int);
    ConstIterator& operator--();
    ConstIterator operator--(int);

    const value_t& operator*() const;
    const value_t* operator->() const;

    bool operator!=(const ConstIterator& rhs) const;
    bool operator==(const ConstIterator& rhs) const;

  private:
    Node* node_;
    Node* root_;
  };

  template< typename Key, typename Value, typename Comparator >
  BSTree< Key, Value, Comparator >::ConstIterator::ConstIterator() :
    node_(nullptr),
    root_(nullptr)
  {};

  template< typename Key, typename Value, typename Comparator >
  BSTree< Key, Value, Comparator >::ConstIterator::ConstIterator(Node* node, Node* root) :
    node_(node),
    root_(root)
  {}

  template< typename Key, typename Value, typename Comparator >
  typename BSTree< Key, Value, Comparator >::ConstIterator& BSTree< Key, Value, Comparator >::ConstIterator::operator++()
  {
    assert(node_ != nullptr);
    if (node_->right_)
    {
      node_ = node_->right_;
      while (node_->left_)
      {
        node_ = node_->left_;
      }
    }
    else
    {
      Node* nodes = node_->parent_;
      while (nodes && node_ == nodes->right_)
      {
        node_ = nodes;
        nodes = nodes->parent_;
      }
      node_ = nodes;
    }
    return *this;
  }

  template< typename Key, typename Value, typename Comparator >
  typename BSTree< Key, Value, Comparator >::ConstIterator BSTree< Key, Value, Comparator >::ConstIterator::operator++(int)
  {
    assert(node_ != nullptr);
    ConstIterator result(*this);
    ++(*this);
    return result;
  }

  template< typename Key, typename Value, typename Comparator >
  typename BSTree< Key, Value, Comparator >::ConstIterator& BSTree< Key, Value, Comparator >::ConstIterator::operator--()
  {
    if (node_ == nullptr)
    {
      node_ = root_;
      while (node_->right_)
      {
        node_ = node_->right_;
      }
    }
    else if (node_->left_)
    {
      node_ = node_->left_;
      while (node_->right_)
      {
        node_ = node_->right_;
      }
    }
    else
    {
      Node* nodes = node_->parent_;
      while (nodes && node_ == nodes->left_)
      {
        node_ = nodes;
        nodes = nodes->parent_;
      }
      node_ = nodes;
    }
    return *this;
  }

  template< typename Key, typename Value, typename Comparator >
  typename BSTree< Key, Value, Comparator >::ConstIterator BSTree< Key, Value, Comparator >::ConstIterator::operator--(int)
  {
    assert(node_ != nullptr);
    ConstIterator result(*this);
    --(*this);
    return result;
  }

  template< typename Key, typename Value, typename Comparator >
  const value_t< Key, Value >& BSTree< Key, Value, Comparator >::ConstIterator::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data_;
  }
  template< typename Key, typename Value, typename Comparator >
  const value_t< Key, Value >* BSTree< Key, Value, Comparator >::ConstIterator::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template< typename Key, typename Value, typename Comparator >
  bool BSTree< Key, Value, Comparator >::ConstIterator::operator!=(const ConstIterator& rhs) const
  {
    return !(rhs == *this);
  }

  template< typename Key, typename Value, typename Comparator >
  bool BSTree< Key, Value, Comparator >::ConstIterator::operator==(const ConstIterator& rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename Key, typename Value, typename Comparator >
  class BSTree< Key, Value, Comparator >::Iterator : public std::iterator< std::bidirectional_iterator_tag, value_t >
  {
  public:
    friend class BSTree< Key, Value, Comparator >;
    Iterator();
    Iterator(ConstIterator someIterator);
    ~Iterator() = default;
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;

    Iterator operator++();
    Iterator operator++(int);
    Iterator operator--();
    Iterator operator--(int);

    value_t& operator*();
    value_t* operator->();

    bool operator!=(const Iterator& rhs) const;
    bool operator==(const Iterator& rhs) const;
  private:
    ConstIterator iterator_;
  };

  template< typename Key, typename Value, typename Comparator >
  BSTree< Key, Value, Comparator >::Iterator::Iterator() :
    iterator_(nullptr, nullptr)
  {}

  template< typename Key, typename Value, typename Comparator >
  BSTree< Key, Value, Comparator >::Iterator::Iterator(ConstIterator someIterator) :
    iterator_(someIterator)
  {}

  template< typename Key, typename Value, typename Comparator >
  typename BSTree< Key, Value, Comparator >::Iterator::Iterator BSTree< Key, Value, Comparator >::Iterator::operator++()
  {
    assert(iterator_.node_ != nullptr);
    iterator_++;
    return iterator_;
  }

  template< typename Key, typename Value, typename Comparator >
  typename BSTree< Key, Value, Comparator >::Iterator::Iterator BSTree< Key, Value, Comparator >::Iterator::operator++(int)
  {
    ++iterator_;
    return iterator_;
  }

  template< typename Key, typename Value, typename Comparator >
  typename BSTree< Key, Value, Comparator >::Iterator::Iterator BSTree< Key, Value, Comparator >::Iterator::operator--()
  {
    iterator_--;
    return iterator_;
  }

  template< typename Key, typename Value, typename Comparator >
  typename BSTree< Key, Value, Comparator >::Iterator::Iterator BSTree< Key, Value, Comparator >::Iterator::operator--(int)
  {
    --iterator_;
    return iterator_;
  }

  template< typename Key, typename Value, typename Comparator >
  value_t< Key, Value >& BSTree< Key, Value, Comparator >::Iterator::operator*()
  {
    return iterator_.node_->data_;
  }
  template< typename Key, typename Value, typename Comparator >
  value_t< Key, Value >* BSTree< Key, Value, Comparator >::Iterator::operator->()
  {
    return std::addressof(iterator_.node_->data_);
  }

  template< typename Key, typename Value, typename Compare >
  bool BSTree< Key, Value, Compare >::Iterator::operator!=(const Iterator& rhs) const
  {
    return !(rhs == *this);
  }

  template< typename Key, typename Value, typename Comparator >
  bool BSTree< Key, Value, Comparator >::Iterator::operator==(const Iterator& rhs) const
  {
    return iterator_ == rhs.iterator_;
  }

  template< typename Key, typename Value, typename Comparator >
  BSTree< Key, Value, Comparator >::BSTree():
    root_(nullptr),
    comp_(Comparator()),
    size_(0)
  {};


  template< typename Key, typename Value, typename Comparator >
  BSTree< Key, Value, Comparator >::BSTree(const BSTree& rhs) :
    root_(nullptr),
    comp_(rhs.comp_),
    size_(rhs.size_)
  {
    for (auto it = rhs.cbegin(); it != rhs.cend(); ++it)
    {
      insert(it->first, it->second);
    }
  }

  template< typename Key, typename Value, typename Comparator >
  BSTree< Key, Value, Comparator >::BSTree(BSTree&& rhs) noexcept :
    root_(rhs.root_),
    comp_(rhs.comp_),
    size_(rhs.size_)
  {
    rhs.root_ = nullptr;
    rhs.size_ = 0;
  }

  template< typename Key, typename Value, typename Comparator >
  BSTree< Key, Value, Comparator >::~BSTree()
  {
    clear();
  }

  template< typename Key, typename Value, typename Comparator >
  Value& BSTree< Key, Value, Comparator >::at(const Key& key)
  {
    ConstIterator it = find(key);
    if (it != ConstIterator(nullptr, root_))
    {
      return const_cast< Value& >(it->second);
    }
    else
    {
      throw std::out_of_range("Error:\n");
    }
  }

  template< typename Key, typename Value, typename Comparator >
  bool BSTree< Key, Value, Comparator >::empty() const noexcept
  {
    return root_ == nullptr;
  }

  template< typename Key, typename Value, typename Comparator >
  size_t BSTree< Key, Value, Comparator >::size() const noexcept
  {
    return size_;
  }
  template< typename Key, typename Value, typename Comparator >
  void BSTree< Key, Value, Comparator >::swap(BSTree& rhs) noexcept
  {
    std::swap(root_, rhs.root_);
    std::swap(comp_, rhs.comp_);
    size_ = rhs.size_;
  }

  template< typename Key, typename Value, typename Compare >
  void BSTree< Key, Value, Compare >::updHeight(Node* node) noexcept
  {
    node->height_ = std::max(getHeight(node->left_), getHeight(node->right_)) + 1;
  }

  template< typename Key, typename Value, typename Compare >
  size_t BSTree< Key, Value, Compare >::getHeight(const Node* node) const noexcept
  {
    return (node == nullptr) ? 0 : node->height_;
  }

  template< typename Key, typename Value, typename Compare >
  size_t BSTree< Key, Value, Compare >::height(Node* node)
  {
    return ((node->left_ != nullptr) ? node->left_->height_ : 0) - ((node->right_ != nullptr) ? node->right_->height_ : 0);
  }

  template< typename Key, typename Value, typename Comparator >
  void BSTree< Key, Value, Comparator >::insert(const value_t& val)
  {
    insert(val.first, val.second);
  }

  template < typename Key, typename Value, typename Comparator >
  void BSTree< Key, Value, Comparator >::insert(const Key& key, const Value& val)
  {
    if (!empty())
    {
      Node* newRoot = root_;
      Node* nodes = nullptr;
      while (newRoot)
      {
        nodes = newRoot;
        if (key < newRoot->data_.first)
        {
          newRoot = newRoot->left_;
        }
        else if (key > newRoot->data_.first)
        {
          newRoot = newRoot->right_;
        }
        else
        {
          return;
        }
      }
      Node* newNodes = new Node({ key, val }, nodes);
      if (key > nodes->data_.first)
      {
        nodes->right_ = newNodes;
      }
      else
      {
        nodes->left_ = newNodes;
      }
      balance(newNodes);
      size_++;
    }
    else
    {
      root_ = new Node({ key, val });
      size_++;
      return;
    }
  }

  template< typename Key, typename Value, typename Comparator >
  void BSTree< Key, Value, Comparator >::erase(const Key& key)
  {
    Iterator it = find(key);
    Node* nodes = it.iterator_.node_;
    if (!nodes)
    {
      return;
    }
    if (!nodes->left_ && !nodes->right_)
    {
      if (nodes == root_)
      {
        delete root_;
        root_ = nullptr;
        size_--;
        return;
      }
      if (nodes->data_.first > nodes->parent_->data_.first)
      {
        nodes->parent_->right_ = nullptr;
      }
      else
      {
        nodes->parent_->left_ = nullptr;
      }
      delete nodes;
      size_--;
      return;
    }
    else if (nodes->left_ && !nodes->right_)
    {
      if (nodes == root_)
      {
        root_ = root_->left_;
        root_->parent_ = nullptr;
        delete nodes;
        return;
      }
      if (nodes->data_.first > nodes->parent_->data_.first)
      {
        nodes->parent_->right_ = nodes->left_;
      }
      else
      {
        nodes->parent_->left_ = nodes->left_;
      }
      nodes->left_->parent_ = nodes->parent_;
      delete nodes;
      return;
    }
    else if (nodes->right_ && !nodes->left_)
    {
      if (nodes == root_)
      {
        root_ = root_->right_;
        root_->parent_ = nullptr;
        delete nodes;
        size_--;
        return;
      }
      if (nodes->data_.first > nodes->parent_->data_.first)
      {
        nodes->parent_->right_ = nodes->right_;
      }
      else
      {
        nodes->parent_->left_ = nodes->right_;
      }
      nodes->right_->parent_ = nodes->parent_;
      delete nodes;
      size_--;
      return;
    }
    Node* temp = nodes->right_;
    if (temp != nullptr)
    {
      while (temp->left_)
      {
        temp = temp->left_;
      }
    }
    Node* min = temp;
    if (min->right_ && (min->parent_ != nodes))
    {
      min->parent_->left_ = min->right_;
      min->right_->parent_ = min->parent_;
    }
    else if (min->parent_ != nodes)
    {
      min->parent_->left_ = nullptr;
    }
    min->right_ = (nodes->right_->left_) ? nodes->right_ : nodes->right_->right_;
    min->left_ = nodes->left_;
    if (nodes == root_)
    {
      min->parent_ = nullptr;
      delete root_;
      root_ = min;
      if (root_->left_)
      {
        root_->left_->parent_ = root_;
      }
      if (root_->right_)
      {
        root_->right_->parent_ = root_;
      }
      size_--;
      return;
    }
    min->parent_ = nodes->parent_;
    nodes->left_->parent_ = min;
    if (min->data_.first > min->parent_->data_.first)
    {
      min->parent_->right_ = min;
    }
    else
    {
      min->parent_->left_ = min;
    }
    delete nodes;
    size_--;
    return;
  }

  template< typename Key, typename Value, typename Comparator >
  typename BSTree< Key, Value, Comparator >::Node* BSTree< Key, Value, Comparator >::balance(Node* node)
  {
    updHeight(node);
    int flag = height(node);
    if (flag > 1)
    {
      if (height(node->left_) < 0)
      {
        node->left_ = rotateLeft(node->left_);
      }
      return rotateRight(node);
    }
    else if (flag < -1)
    {
      if (height(node->right_) > 0)
      {
        node->right_ = rotateRight(node->right_);
      }
      return rotateLeft(node);
    }
    return node;
  }

  template< typename Key, typename Value, typename Comparator >
  typename BSTree< Key, Value, Comparator >::Node* BSTree< Key, Value, Comparator >::rotateRight(Node* node)
  {
    if (node == nullptr)
    {
      return nullptr;
    }
    Node* newRoot = node->left_;
    if (newRoot == nullptr)
    {
      return node;
    }
    node->left_ = newRoot->right_;
    if (node->left_ != nullptr)
    {
      node->left_->parent_ = node;
    }
    newRoot->parent_ = node->parent_;
    if (node->parent_ == nullptr)
    {
      root_ = newRoot;
    }
    else if (node == node->parent_->left_)
    {
      node->parent_->left_ = newRoot;
    }
    else
    {
      node->parent_->right_ = newRoot;
    }
    newRoot->right_ = node;
    node->parent_ = newRoot;
    updHeight(node);
    updHeight(newRoot);
    return newRoot;
  }

  template< typename Key, typename Value, typename Comparator >
  typename BSTree< Key, Value, Comparator >::Node* BSTree< Key, Value, Comparator >::rotateLeft(Node* node)
  {
    if (node == nullptr)
    {
      return nullptr;
    }
    Node* newRoot = node->right_;
    if (newRoot == nullptr)
    {
      return node;
    }
    node->right_ = newRoot->left_;
    if (node->right_ != nullptr)
    {
      node->right_->parent_ = node;
    }
    newRoot->parent_ = node->parent_;
    if (node->parent_ == nullptr)
    {
      root_ = newRoot;
    }
    else
    {
      if (node == node->parent_->left_)
      {
        node->parent_->left_ = newRoot;
      }
      else
      {
        node->parent_->right_ = newRoot;
      }
    }
    newRoot->left_ = node;
    node->parent_ = newRoot;
    updHeight(node);
    updHeight(newRoot);
    return newRoot;
  }

  template < typename Key, typename Value, typename Comparator >
  void BSTree< Key, Value, Comparator >::clear()
  {
    free(root_);
    root_ = nullptr;
  }

  template < typename Key, typename Value, typename Comparator >
  void BSTree< Key, Value, Comparator >::free(Node* node)
  {
    if (node == nullptr)
    {
      return;
    }
    if (node->left_)
    {
      free(node->left_);
      node->left_ = nullptr;
    }
    if (node->right_)
    {
      free(node->right_);
      node->right_ = nullptr;
    }
    delete node;
  }

  template < typename Key, typename Value, typename Comparator >
  typename BSTree< Key, Value, Comparator >::ConstIterator BSTree< Key, Value, Comparator >::find(const Key& key) const
  {
    Node* newRoot = root_;
    while (newRoot != nullptr)
    {
      if (key == newRoot->data_.first)
      {
        return ConstIterator(newRoot, root_);
      }
      else if (comp_(key, newRoot->data_.first))
      {
        newRoot = newRoot->left_;
      }
      else
      {
        newRoot = newRoot->right_;
      }
    }
    return ConstIterator(nullptr, root_);
  }

  template< typename Key, typename Value, typename Comparator >
  Value& BSTree< Key, Value, Comparator >::operator[](const Key& key)
  {
    if (find(key) == cend())
    {
      insert(key, Value());
      return find(key).node_->data_.second;
    }
    else
    {
      return find(key).node_->data_.second;
    }
  }

  template < typename Key, typename Value, typename Comparator >
  typename BSTree< Key, Value, Comparator >::ConstIterator BSTree< Key, Value, Comparator >::cbegin() const
  {
    if (root_ == nullptr)
    {
      return cend();
    }
    Node* newRoot = root_;
    while (newRoot->left_)
    {
      newRoot = newRoot->left_;
    }
    return ConstIterator(newRoot, root_);
  }

  template < typename Key, typename Value, typename Comparator >
  typename BSTree< Key, Value, Comparator >::ConstIterator BSTree< Key, Value, Comparator >::cend() const
  {
    return ConstIterator(nullptr, root_);
  }

  template < typename Key, typename Value, typename Comparator >
  typename BSTree< Key, Value, Comparator >::Iterator BSTree< Key, Value, Comparator >::begin()
  {
    return Iterator(cbegin());
  }

  template < typename Key, typename Value, typename Comparator >
  typename BSTree< Key, Value, Comparator>::Iterator BSTree< Key, Value, Comparator >::end()
  {
    return Iterator(cend());
  }

  template < typename Key, typename Value, typename Comparator >
  template < typename F >
  F BSTree< Key, Value, Comparator >::traverse_lnr(F f)
  {
    Stack< Node* > stack;
    Node* nodes = root_;
    if (!nodes)
    {
      return f;
    }

    while (!stack.isEmpty() || nodes)
    {
      if (nodes)
      {
        stack.push(nodes);
        nodes = nodes->left_;
      }
      else
      {
        nodes = stack.top();
        stack.pop();
        f(nodes->data_);
        nodes = nodes->right_;
      }
    }
    return f;
  }

  template < typename Key, typename Value, typename Comparator >
  template < typename F >
  F BSTree< Key, Value, Comparator >::traverse_rnl(F f)
  {
    Stack< Node* > stack;
    Node* nodes = root_;
    if (!nodes)
    {
      return f;
    }

    while (!stack.isEmpty() || nodes)
    {
      if (nodes)
      {
        stack.push(nodes);
        nodes = nodes->right_;
      }
      else
      {
        nodes = stack.top();
        stack.pop();
        f(nodes->data_);
        nodes = nodes->left_;
      }
    }
    return f;

  }
  template < typename Key, typename Value, typename Comparator >
  template < typename F >
  F BSTree< Key, Value, Comparator >::traverse_breadth(F f)
  {
    Queue< Node* > queue;
    if (root_ == nullptr)
    {
      return f;
    }
    queue.push(root_);
    while (!queue.isEmpty())
    {
      Node* nodes = queue.front();
      queue.pop();
      f(nodes->data_);
      if (nodes->left_)
      {
        queue.push(nodes->left_);
      }
      if (nodes->right_)
      {
        queue.push(nodes->right_);
      }
    }
    return f;
  }
}
#endif
