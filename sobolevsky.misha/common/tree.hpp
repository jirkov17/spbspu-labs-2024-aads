#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <queue.hpp>
#include <stack.hpp>

namespace sobolevsky
{
  template< typename Key, typename Value, typename Compare >
  class AVLtree
  {
  public:
    class Iterator;
    class ConstIterator;
    class LNRIterator;
    class LNRConstIterator;
    class RNLIterator;
    class RNLConstIterator;

    AVLtree();
    AVLtree(const AVLtree< Key, Value, Compare > &tree);
    AVLtree(AVLtree< Key, Value, Compare > &&rhs) noexcept;
    ~AVLtree() = default;

    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;

    size_t getSize() const noexcept;
    bool isEmpty() const noexcept;

    Value &operator[](const Key &key);
    Value &at(const Key &key);

    void insert(const std::pair< Key, Value > &pair);
    void erase(const Key &key);
    void erase(ConstIterator position);
    void clear();
    void swap(AVLtree &x) noexcept;

    Iterator find(const Key &key);
    size_t count(const Key &key);
    std::pair< Iterator, Iterator > equal_range(const Key &key);

    template< typename F >
    F traverse_lnr(F f) const;
    template< typename F >
    F traverse_rnl(F f) const;
    template< typename F >
    F traverse_breadth(F f) const;
    template< typename F >
    F traverse_lnr(F f);
    template< typename F >
    F traverse_rnl(F f);
    template< typename F >
    F traverse_breadth(F f);
  private:
    class Node;

    Node *push(const Key &key, const Value &value, Node *node_);
    Node *RightRotate(Node *node_);
    Node *LeftRotate(Node *node_);
    Node *LeftRightRotate(Node *node_);
    Node *RightLeftRotate(Node *node_);
    Node *remove(const Key &key, Node *node_);
    size_t height(Node *node_);
    void recurionDeleteAll(Node *node);

    Node *root;
    size_t size_;
  };
}

template< typename Key, typename Value, typename Compare >
class sobolevsky::AVLtree< Key, Value, Compare >::Node
{
  friend class AVLtree;
public:
  Node(const Key key, const Value value):
    left(nullptr),
    right(nullptr),
    parent(nullptr),
    height(1),
    data(std::pair< Key, Value >(key, value))
  {}
private:
  Node *left;
  Node *right;
  Node *parent;
  size_t height;
  std::pair< Key, Value > data;
};

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::AVLtree()
{
  root = nullptr;
  size_ = 0;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::AVLtree(const AVLtree< Key, Value, Compare > &tree)
{
  root = tree.root;
  size_ = tree.size_;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::AVLtree(AVLtree< Key, Value, Compare > &&rhs) noexcept
{
  root = rhs.root;
  size_ = std::move(rhs.size_);
}

template< typename Key, typename Value, typename Compare >
size_t sobolevsky::AVLtree< Key, Value, Compare >::getSize() const noexcept
{
  return size_;
}

template< typename Key, typename Value, typename Compare >
bool sobolevsky::AVLtree< Key, Value, Compare >::isEmpty() const noexcept
{
  return size_ == 0;
}

template< typename Key, typename Value, typename Compare >
Value &sobolevsky::AVLtree< Key, Value, Compare >::operator[](const Key &key)
{
  Iterator iter(find(key));
  if (iter == end())
  {
    insert(std::pair< Key, Value>(key, Value()));
    iter = find(key);
  }
  return iter->second;
}

template< typename Key, typename Value, typename Compare >
Value &sobolevsky::AVLtree< Key, Value, Compare >::at(const Key &key)
{
  if (find(key) == end())
  {
    throw std::out_of_range("Such key does not exist\n");
  }
  else
  {
    return (find(key))->second;
  }
}

template< typename Key, typename Value, typename Compare >
void sobolevsky::AVLtree< Key, Value, Compare >::insert(const std::pair< Key, Value > &pair)
{
  root = push(pair.first, pair.second, root);
  size_++;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Node *sobolevsky::AVLtree< Key, Value, Compare >::push
(const Key &key, const Value &value, Node *node_)
{
  if (node_ == nullptr)
  {
    node_ = new Node(key, value);
  }
  else if (key < node_->data.first)
  {
    node_->left = push(key, value, node_->left);
    node_->left->parent = node_;
    node_->height++;
    if (height(node_->left) - height(node_->right) > 1)
    {
      if (node_->right == nullptr || key < node_->left->data.first)
      {
        node_ = RightRotate(node_);
      }
      else
      {
        node_ = LeftRightRotate(node_);
      }
    }
  }
  else if (key > node_->data.first)
  {
    node_->right = push(key, value, node_->right);
    node_->right->parent = node_;
    node_->height++;
    if ((height(node_->right) - height(node_->left)) > 1)
    {
      if (node_->left == nullptr || key > node_->right->data.first)
      {
        node_ = LeftRotate(node_);
      }
      else
      {
        node_ = RightLeftRotate(node_);
      }
    }
  }
  return node_;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Node *sobolevsky::AVLtree< Key, Value, Compare >::RightRotate(Node *node_)
{
  Node *temp = node_->left;
  node_->left = temp->right;
  if (node_->left != nullptr)
  {
    node_->left->parent = node_;
  }
  temp->parent = node_->parent;
  node_->parent = temp;
  temp->right = node_;
  node_->height = std::max(height(node_->left), height(node_->right)) + 1;
  temp->height = std::max(node_->height, height(temp->left)) + 1;
  return temp;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Node *sobolevsky::AVLtree< Key, Value, Compare >::LeftRotate(Node *node_)
{
  Node *temp = node_->right;
  node_->right = temp->left;
  if (node_->right != nullptr)
  {
    node_->right->parent = node_;
  }
  temp->parent = node_->parent;
  node_->parent = temp;
  temp->left = node_;
  node_->height = std::max(height(node_->left), height(node_->right)) + 1;
  temp->height = std::max(node_->height, height(temp->right)) + 1;
  return temp;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Node *sobolevsky::AVLtree< Key, Value, Compare >::LeftRightRotate(Node *node_)
{
  node_->left = LeftRotate(node_->left);
  return RightRotate(node_);
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Node *sobolevsky::AVLtree< Key, Value, Compare >::RightLeftRotate(Node *node_)
{
  node_->right = RightRotate(node_->right);
  return LeftRotate(node_);
}

template< typename Key, typename Value, typename Compare >
void sobolevsky::AVLtree< Key, Value, Compare >::erase(const Key &key)
{
  root = remove(key, root);
  size_--;
}

template< typename Key, typename Value, typename Compare >
void sobolevsky::AVLtree< Key, Value, Compare >::erase(ConstIterator position)
{
  root = remove(position->data.first, root);
  size_--;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Node *sobolevsky::AVLtree< Key, Value, Compare >::remove
(const Key &key, Node *node_)
{
  if (node_ == nullptr)
  {
    return nullptr;
  }
  else if (key < node_->data.first)
  {
    node_->left = remove(key, node_->left);
  }
  else if (key > node_->data.first)
  {
    node_->right = remove(key, node_->right);
  }
  else if (node_->left && node_->right)
  {
    Node *temp = node_->right;
    while (temp->left != nullptr)
    {
      temp = temp->left;
    }
    node_->data = temp->data;
    node_->right = remove(node_->data.first, node_->right);
  }
  else
  {
    Node *temp = node_;
    if (node_->left == nullptr)
    {
      node_ = node_->right;
    }
    else if (node_->right== nullptr)
    {
      node_ = node_->left;
    }
  }

  if (node_ == nullptr)
  {
    return nullptr;
  }

  node_->height = std::max(height(node_->left), height(node_->right)) + 1;

  if (height(node_->left) - height(node_->right) > 1 && (node_->right != nullptr) && (node_->left != nullptr))
  {
    if (height(node_->left->left) - height(node_->left->right) > 0)
    {
      return LeftRotate(node_);
    }
    else if (node_->right != nullptr)
    {
      return RightLeftRotate(node_);
    }
  }
  else if (height(node_->right) - height(node_->left) > 1 && (node_->right != nullptr) && (node_->left != nullptr))
  {
    if (height(node_->right->right) - height(node_->right->left) > 0)
    {
      return RightRotate(node_);
    }
    else if (node_->left != nullptr)
    {
      return LeftRightRotate(node_);
    }
  }
  return node_;
}

template< typename Key, typename Value, typename Compare >
size_t sobolevsky::AVLtree< Key, Value, Compare >::height(Node *node_)
{
  return (node_ == nullptr ? 0 : node_->height);
}

template< typename Key, typename Value, typename Compare >
void sobolevsky::AVLtree< Key, Value, Compare >::recurionDeleteAll(Node *node)
{
  if (node != nullptr)
  {
    recurionDeleteAll(node->left);
    recurionDeleteAll(node->right);
    delete node;
  }
}

template< typename Key, typename Value, typename Compare >
void sobolevsky::AVLtree< Key, Value, Compare >::clear()
{
  recurionDeleteAll(root);
  root = nullptr;
  size_ = 0;
}

template< typename Key, typename Value, typename Compare >
void sobolevsky::AVLtree< Key, Value, Compare >::swap(AVLtree &x) noexcept
{
  Node *temp = x.root;
  x.root = root;
  root = temp;
  size_t tempSize = x.size_;
  x.size_ = size_;
  size_ = tempSize;
}

template< typename Key, typename Value, typename Compare >
size_t sobolevsky::AVLtree< Key, Value, Compare >::count(const Key &key)
{
  if (find(key) == end())
  {
    return 0;
  }
  return 1;
}

template< typename Key, typename Value, typename Compare >
std::pair< typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator, typename sobolevsky::AVLtree< Key, Value,
Compare >::Iterator > sobolevsky::AVLtree< Key, Value, Compare >::equal_range(const Key &key)
{
  if (find(key) == end())
  {
    Iterator iter(begin());
    while (iter != end())
    {
      if ((*iter).first > key)
      {
        break;
      }
      iter++;
    }
    return std::make_pair(iter, iter);
  }
  else
  {
    return std::make_pair(find(key), find(key)++);
  }
}

template< typename Key, typename Value, typename Compare >
class sobolevsky::AVLtree< Key, Value, Compare >::Iterator : public std::iterator< std::input_iterator_tag, Key, Value, Compare >
{
  friend class AVLtree;
public:
  Iterator();
  Iterator(Node *node);
  Iterator(const Iterator &iter);
  Iterator(const LNRIterator &iter);
  Iterator(const RNLIterator &iter);
  ~Iterator() = default;

  Iterator &operator=(const Iterator &iter);
  Iterator &operator=(Iterator &&rhs);
  Iterator &operator=(const LNRIterator &iter);
  Iterator &operator=(LNRIterator &&rhs);
  Iterator &operator=(const RNLIterator &iter);
  Iterator &operator=(RNLIterator &&rhs);
  std::pair< Key, Value > &operator*();
  std::pair< Key, Value > *operator->();
  Iterator &operator++();
  Iterator operator++(int);
  Iterator &operator--();
  Iterator operator--(int);
  bool operator==(const Iterator &rhs) const;
  bool operator!=(const Iterator &rhs) const;
private:
  Node *node_;
};

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::Iterator::Iterator()
{
  node_(nullptr);
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::Iterator::Iterator(Node *node)
{
  node_ = node;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::Iterator::Iterator(const Iterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::Iterator::Iterator(const LNRIterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::Iterator::Iterator(const RNLIterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator &sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator=
(const Iterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator &sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator=
(Iterator &&rhs)
{
  node_ = rhs.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator &sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator=
(const LNRIterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator &sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator=
(LNRIterator &&rhs)
{
  node_ = rhs.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator &sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator=
(const RNLIterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator &sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator=
(RNLIterator &&rhs)
{
  node_ = rhs.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value > &sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator*()
{
  return node_->data;
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value > *sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator->()
{
  return std::addressof(node_->data);
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator &sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator++()
{
  if (node_ == nullptr)
  {
    return *this;
  }
  else if (node_->right == nullptr)
  {
    Node *temp = node_->parent;
    while (temp != nullptr && node_ == temp->right)
    {
      node_ = temp;
      temp = node_->parent;
    }
    node_ = temp;
    return *this;
  }
  else
  {
    node_ = node_->right;
    if (node_->left == nullptr)
    {
      return *this;
    }
    while (node_->left != nullptr)
    {
      node_ = node_->left;
    }
    return *this;
  }
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator++(int)
{
  Iterator temp(*this);
  ++(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator &sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator--()
{
  if (node_ == nullptr)
  {
    return *this;
  }
  else if (node_->left == nullptr)
  {
    Node *temp = node_->parent;
    while (temp != nullptr && node_ == temp->left)
    {
      node_ = temp;
      temp = node_->parent;
    }
    node_ = temp;
    return *this;
  }
  else
  {
    node_ = node_->left;
    while (node_->right != nullptr)
    {
      node_ = node_->right;
    }
    return *this;
  }
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator--(int)
{
  Iterator temp(*this);
  --(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
bool sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator==(const Iterator &rhs) const
{
  return node_ == rhs.node_;
}

template< typename Key, typename Value, typename Compare >
bool sobolevsky::AVLtree< Key, Value, Compare >::Iterator::operator!=(const Iterator &rhs) const
{
  return node_ != rhs.node_;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator sobolevsky::AVLtree< Key, Value, Compare >::begin() noexcept
{
  Node *temp = root;
  while (temp->left != nullptr)
  {
    temp = temp->left;
  }
  return Iterator(temp);
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator sobolevsky::AVLtree< Key, Value, Compare >::end() noexcept
{
  return Iterator(nullptr);
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator sobolevsky::AVLtree< Key, Value, Compare >::cbegin()
const noexcept
{
  Node *temp = root;
  while (temp->left != nullptr)
  {
    temp = temp->left;
  }
  return ConstIterator(temp);
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator sobolevsky::AVLtree< Key, Value, Compare >::cend() const noexcept
{
  return ConstIterator(nullptr);
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::Iterator sobolevsky::AVLtree< Key, Value, Compare >::find(const Key &key)
{
  Node *temp = root;
  while (temp)
  {
    if (temp->data.first == key)
    {
      return Iterator(temp);
    }
    else if (key > temp->data.first)
    {
      temp = temp->right;
    }
    else if (key < temp->data.first)
    {
      temp = temp->left;
    }
  }
  return end();
}

template< typename Key, typename Value, typename Compare >
class sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator : public std::iterator< std::input_iterator_tag, Key, Value, Compare >
{
  friend class AVLtree;
public:
  ConstIterator();
  explicit ConstIterator(const Node *node);
  ConstIterator(const ConstIterator &iter);
  ConstIterator(const LNRConstIterator &iter);
  ConstIterator(const RNLConstIterator &iter);
  ~ConstIterator() = default;

  ConstIterator &operator=(const ConstIterator &iter);
  ConstIterator &operator=(ConstIterator &&rhs);
  ConstIterator &operator=(const LNRConstIterator &iter);
  ConstIterator &operator=(LNRConstIterator &&rhs);
  ConstIterator &operator=(const RNLConstIterator &iter);
  ConstIterator &operator=(RNLConstIterator &&rhs);
  const std::pair< Key, Value > &operator*() const;
  const std::pair< Key, Value > *operator->() const;
  ConstIterator &operator++();
  ConstIterator operator++(int);
  ConstIterator &operator--();
  ConstIterator operator--(int);
  bool operator==(const ConstIterator &rhs) const;
  bool operator!=(const ConstIterator &rhs) const;
private:
  const Node *node_;
};

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::ConstIterator()
{
  node_(nullptr);
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::ConstIterator(const Node *node)
{
  node_ = node;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::ConstIterator(const ConstIterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::ConstIterator(const LNRConstIterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::ConstIterator(const RNLConstIterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator &sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator=
(const ConstIterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator &sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator=
(ConstIterator &&rhs)
{
  node_(rhs.node_);
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator &sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator=
(const LNRConstIterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator &sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator=
(LNRConstIterator &&rhs)
{
  node_(rhs.node_);
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator &sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator=
(const RNLConstIterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator &sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator=
(RNLConstIterator &&rhs)
{
  node_(rhs.node_);
  return *this;
}

template< typename Key, typename Value, typename Compare >
const std::pair< Key, Value > &sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator*() const
{
  return node_->data;
}

template< typename Key, typename Value, typename Compare >
const std::pair< Key, Value > *sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator->() const
{
  return std::addressof(node_->data);
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator
&sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator++()
{
  if (node_ == nullptr)
  {
    return *this;
  }
  else if (node_->right == nullptr)
  {
    Node *temp = node_->parent;
    while (temp != nullptr && node_ == temp->right)
    {
      node_ = temp;
      temp = node_->parent;
    }
    node_ = temp;
    return *this;
  }
  else
  {
    node_ = node_->right;
    if (node_->left == nullptr)
    {
      return *this;
    }
    while (node_->left != nullptr)
    {
      node_ = node_->left;
    }
    return *this;
  }
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator sobolevsky::AVLtree< Key, Value,
Compare >::ConstIterator::operator++(int)
{
  ConstIterator temp(*this);
  ++(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator
&sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator--()
{
  if (node_ == nullptr)
  {
    return *this;
  }
  else if (node_->left == nullptr)
  {
    Node *temp = node_->parent;
    while (temp != nullptr && node_ == temp->left)
    {
      node_ = temp;
      temp = node_->parent;
    }
    node_ = temp;
    return *this;
  }
  else
  {
    node_ = node_->left;
    while (node_->right != nullptr)
    {
      node_ = node_->right;
    }
    return *this;
  }
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator sobolevsky::AVLtree< Key, Value,
Compare >::ConstIterator::operator--(int)
{
  ConstIterator temp(*this);
  --(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
bool sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator==(const ConstIterator &rhs) const
{
  return node_ == rhs.node_;
}

template< typename Key, typename Value, typename Compare >
bool sobolevsky::AVLtree< Key, Value, Compare >::ConstIterator::operator!=(const ConstIterator &rhs) const
{
  return node_ != rhs.node_;
}

template< typename Key, typename Value, typename Compare >
template< typename F >
F sobolevsky::AVLtree< Key, Value, Compare >::traverse_lnr(F f) const
{
  Stack< const Node* > stack;
  const Node * temp = root;
  while (!(stack.empty()) || temp != nullptr)
  {
    while (temp != nullptr)
    {
      stack.push(temp);
      temp = temp->left;
    }
    temp = stack.top();
    stack.pop();
    f(temp->data);
    temp = temp->right;
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
template< typename F >
F sobolevsky::AVLtree< Key, Value, Compare >::traverse_rnl(F f) const
{
  Stack< const Node* > stack;
  const Node * temp = root;
  while (!(stack.empty()) || temp != nullptr)
  {
    while (temp != nullptr)
    {
      stack.push(temp);
      temp = temp->right;
    }
    temp = stack.top();
    stack.pop();
    f(temp->data);
    temp = temp->left;
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
template< typename F >
F sobolevsky::AVLtree< Key, Value, Compare >::traverse_breadth(F f) const
{
  Queue< const Node* > queue;
  queue.push(root);
  while (!(queue.empty()))
  {
    const Node *temp = queue.back();
    queue.pop();
    if (temp->left != nullptr)
    {
      queue.push(temp->left);
    }
    if (temp->right != nullptr)
    {
      queue.push(temp->right);
    }
    f(temp->data);
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
template< typename F >
F sobolevsky::AVLtree< Key, Value, Compare >::traverse_lnr(F f)
{
  Stack< Node* > stack;
  Node * temp = root;
  while (!(stack.empty()) || temp != nullptr)
  {
    while (temp != nullptr)
    {
      stack.push(temp);
      temp = temp->left;
    }
    temp = stack.top();
    stack.pop();
    f(temp->data);
    temp = temp->right;
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
template< typename F >
F sobolevsky::AVLtree< Key, Value, Compare >::traverse_rnl(F f)
{
  Stack< Node* > stack;
  Node * temp = root;
  while (!(stack.empty()) || temp != nullptr)
  {
    while (temp != nullptr)
    {
      stack.push(temp);
      temp = temp->right;
    }
    temp = stack.top();
    stack.pop();
    f(temp->data);
    temp = temp->left;
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
template< typename F >
F sobolevsky::AVLtree< Key, Value, Compare >::traverse_breadth(F f)
{
  Queue< Node* > queue;
  queue.push(root);
  while (!(queue.empty()))
  {
    Node *temp = queue.back();
    queue.pop();
    if (temp->left != nullptr)
    {
      queue.push(temp->left);
    }
    if (temp->right != nullptr)
    {
      queue.push(temp->right);
    }
    f(temp->data);
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
class sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator : public std::iterator< std::input_iterator_tag, Key, Value, Compare >
{
  friend class AVLtree;
public:
  LNRIterator();
  LNRIterator(Node *node);
  LNRIterator(const LNRIterator &iter);
  LNRIterator(const Iterator &iter);
  ~LNRIterator() = default;

  LNRIterator &operator=(const LNRIterator &iter);
  LNRIterator &operator=(LNRIterator &&rhs);
  LNRIterator &operator=(const Iterator &iter);
  LNRIterator &operator=(Iterator &&rhs);
  std::pair< Key, Value > &operator*();
  std::pair< Key, Value > *operator->();
  LNRIterator &operator++();
  LNRIterator operator++(int);
  LNRIterator &operator--();
  LNRIterator operator--(int);
  bool operator==(const LNRIterator &rhs) const;
  bool operator!=(const LNRIterator &rhs) const;
private:
  Node *node_;
};

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator::LNRIterator()
{
  node_ = nullptr;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator::LNRIterator(Node *node)
{
  node_ = node;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator::LNRIterator(const LNRIterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator::LNRIterator(const Iterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator &sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator::operator=
(const LNRIterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator &sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator::operator=
(LNRIterator &&rhs)
{
  node_ = rhs.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator &sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator::operator=
(const Iterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator &sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator::operator=
(Iterator &&rhs)
{
  node_ = rhs.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value > &sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator::operator*()
{
  return node_->data;
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value > *sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator::operator->()
{
  return std::addressof(node_->data);
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator &sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator::operator++()
{
  if (node_ == nullptr)
  {
    return *this;
  }
  else if (node_->right == nullptr)
  {
    Node *temp = node_->parent;
    while (temp != nullptr && node_ == temp->right)
    {
      node_ = temp;
      temp = node_->parent;
    }
    node_ = temp;
    return *this;
  }
  else
  {
    node_ = node_->right;
    if (node_->left == nullptr)
    {
      return *this;
    }
    while (node_->left != nullptr)
    {
      node_ = node_->left;
    }
    return *this;
  }
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator::operator++(int)
{
  LNRIterator temp(*this);
  ++(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator &sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator::operator--()
{
  if (node_ == nullptr)
  {
    return *this;
  }
  else if (node_->left == nullptr)
  {
    Node *temp = node_->parent;
    while (temp != nullptr && node_ == temp->left)
    {
      node_ = temp;
      temp = node_->parent;
    }
    node_ = temp;
    return *this;
  }
  else
  {
    node_ = node_->left;
    while (node_->right != nullptr)
    {
      node_ = node_->right;
    }
    return *this;
  }
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator::operator--(int)
{
  LNRIterator temp(*this);
  --(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
bool sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator::operator==(const LNRIterator &rhs) const
{
  return node_ == rhs.node_;
}

template< typename Key, typename Value, typename Compare >
bool sobolevsky::AVLtree< Key, Value, Compare >::LNRIterator::operator!=(const LNRIterator &rhs) const
{
  return node_ != rhs.node_;
}

template< typename Key, typename Value, typename Compare >
class sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator : public std::iterator< std::input_iterator_tag, Key, Value, Compare >
{
  friend class AVLtree;
public:
  LNRConstIterator();
  explicit LNRConstIterator(const Node *node);
  LNRConstIterator(const LNRConstIterator &iter);
  LNRConstIterator(const ConstIterator &iter);
  LNRConstIterator(const RNLConstIterator &iter);
  ~LNRConstIterator() = default;

  LNRConstIterator &operator=(const LNRConstIterator &iter);
  LNRConstIterator &operator=(LNRConstIterator &&rhs);
  LNRConstIterator &operator=(const ConstIterator &iter);
  LNRConstIterator &operator=(ConstIterator &&rhs);
  LNRConstIterator &operator=(const RNLConstIterator &iter);
  LNRConstIterator &operator=(RNLConstIterator &&rhs);
  const std::pair< Key, Value > &operator*() const;
  const std::pair< Key, Value > *operator->() const;
  LNRConstIterator &operator++();
  LNRConstIterator operator++(int);
  LNRConstIterator &operator--();
  LNRConstIterator operator--(int);
  bool operator==(const LNRConstIterator &rhs) const;
  bool operator!=(const LNRConstIterator &rhs) const;
private:
  const Node *node_;
};

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator::LNRConstIterator()
{
  node_(nullptr);
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator::LNRConstIterator(const Node *node)
{
  node_ = node;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator::LNRConstIterator(const LNRConstIterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator::LNRConstIterator(const ConstIterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator::LNRConstIterator(const RNLConstIterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator &sobolevsky::AVLtree< Key, Value,
Compare >::LNRConstIterator::operator=(const LNRConstIterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator &sobolevsky::AVLtree< Key, Value,
Compare >::LNRConstIterator::operator=(LNRConstIterator &&rhs)
{
  node_(rhs.node_);
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator &sobolevsky::AVLtree< Key, Value,
Compare >::LNRConstIterator::operator=(const ConstIterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator &sobolevsky::AVLtree< Key, Value,
Compare >::LNRConstIterator::operator=(ConstIterator &&rhs)
{
  node_(rhs.node_);
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator &sobolevsky::AVLtree< Key, Value,
Compare >::LNRConstIterator::operator=(const RNLConstIterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator &sobolevsky::AVLtree< Key, Value,
Compare >::LNRConstIterator::operator=(RNLConstIterator &&rhs)
{
  node_(rhs.node_);
  return *this;
}

template< typename Key, typename Value, typename Compare >
const std::pair< Key, Value > &sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator::operator*() const
{
  return node_->data;
}

template< typename Key, typename Value, typename Compare >
const std::pair< Key, Value > *sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator::operator->() const
{
  return std::addressof(node_->data);
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator
&sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator::operator++()
{
  if (node_ == nullptr)
  {
    return *this;
  }
  else if (node_->right == nullptr)
  {
    Node *temp = node_->parent;
    while (temp != nullptr && node_ == temp->right)
    {
      node_ = temp;
      temp = node_->parent;
    }
    node_ = temp;
    return *this;
  }
  else
  {
    node_ = node_->right;
    if (node_->left == nullptr)
    {
      return *this;
    }
    while (node_->left != nullptr)
    {
      node_ = node_->left;
    }
    return *this;
  }
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator sobolevsky::AVLtree< Key, Value,
Compare >::LNRConstIterator::operator++(int)
{
  LNRConstIterator temp(*this);
  ++(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator
&sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator::operator--()
{
  if (node_ == nullptr)
  {
    return *this;
  }
  else if (node_->left == nullptr)
  {
    Node *temp = node_->parent;
    while (temp != nullptr && node_ == temp->left)
    {
      node_ = temp;
      temp = node_->parent;
    }
    node_ = temp;
    return *this;
  }
  else
  {
    node_ = node_->left;
    while (node_->right != nullptr)
    {
      node_ = node_->right;
    }
    return *this;
  }
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator sobolevsky::AVLtree< Key, Value,
Compare >::LNRConstIterator::operator--(int)
{
  LNRConstIterator temp(*this);
  --(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
bool sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator::operator==(const LNRConstIterator &rhs) const
{
  return node_ == rhs.node_;
}

template< typename Key, typename Value, typename Compare >
bool sobolevsky::AVLtree< Key, Value, Compare >::LNRConstIterator::operator!=(const LNRConstIterator &rhs) const
{
  return node_ != rhs.node_;
}

template< typename Key, typename Value, typename Compare >
class sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator : public std::iterator< std::input_iterator_tag, Key, Value, Compare >
{
  friend class AVLtree;
public:
  RNLIterator();
  RNLIterator(Node *node);
  RNLIterator(const RNLIterator &iter);
  RNLIterator(const Iterator &iter);
  ~RNLIterator() = default;

  RNLIterator &operator=(const RNLIterator &iter);
  RNLIterator &operator=(RNLIterator &&rhs);
  RNLIterator &operator=(const Iterator &iter);
  RNLIterator &operator=(Iterator &&rhs);
  std::pair< Key, Value > &operator*();
  std::pair< Key, Value > *operator->();
  RNLIterator &operator++();
  RNLIterator operator++(int);
  RNLIterator &operator--();
  RNLIterator operator--(int);
  bool operator==(const RNLIterator &rhs) const;
  bool operator!=(const RNLIterator &rhs) const;
private:
  Node *node_;
};

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator::RNLIterator()
{
  node_ = nullptr;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator::RNLIterator(Node *node)
{
  node_ = node;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator::RNLIterator(const RNLIterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator::RNLIterator(const Iterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator &sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator::operator=
(const RNLIterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator &sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator::operator=
(RNLIterator &&rhs)
{
  node_ = rhs.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator &sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator::operator=
(const Iterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator &sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator::operator=
(Iterator &&rhs)
{
  node_ = rhs.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value > &sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator::operator*()
{
  return node_->data;
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value > *sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator::operator->()
{
  return std::addressof(node_->data);
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator &sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator::operator++()
{
  if (node_ == nullptr)
  {
    return *this;
  }
  else if (node_->left == nullptr)
  {
    Node *temp = node_->parent;
    while (temp != nullptr && node_ == temp->left)
    {
      node_ = temp;
      temp = node_->parent;
    }
    node_ = temp;
    return *this;
  }
  else
  {
    node_ = node_->left;
    while (node_->right != nullptr)
    {
      node_ = node_->right;
    }
    return *this;
  }
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator::operator++(int)
{
  RNLIterator temp(*this);
  ++(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator &sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator::operator--()
{
  if (node_ == nullptr)
  {
    return *this;
  }
  else if (node_->right == nullptr)
  {
    Node *temp = node_->parent;
    while (temp != nullptr && node_ == temp->right)
    {
      node_ = temp;
      temp = node_->parent;
    }
    node_ = temp;
    return *this;
  }
  else
  {
    node_ = node_->right;
    if (node_->left == nullptr)
    {
      return *this;
    }
    while (node_->left != nullptr)
    {
      node_ = node_->left;
    }
    return *this;
  }
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator::operator--(int)
{
  RNLIterator temp(*this);
  --(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
bool sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator::operator==(const RNLIterator &rhs) const
{
  return node_ == rhs.node_;
}

template< typename Key, typename Value, typename Compare >
bool sobolevsky::AVLtree< Key, Value, Compare >::RNLIterator::operator!=(const RNLIterator &rhs) const
{
  return node_ != rhs.node_;
}

template< typename Key, typename Value, typename Compare >
class sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator : public std::iterator< std::input_iterator_tag, Key, Value, Compare >
{
  friend class AVLtree;
public:
  RNLConstIterator();
  explicit RNLConstIterator(const Node *node);
  RNLConstIterator(const RNLConstIterator &iter);
  RNLConstIterator(const ConstIterator &iter);
  RNLConstIterator(const LNRConstIterator &iter);
  ~RNLConstIterator() = default;

  RNLConstIterator &operator=(const RNLConstIterator &iter);
  RNLConstIterator &operator=(RNLConstIterator &&rhs);
  RNLConstIterator &operator=(const ConstIterator &iter);
  RNLConstIterator &operator=(ConstIterator &&rhs);
  RNLConstIterator &operator=(const LNRConstIterator &iter);
  RNLConstIterator &operator=(LNRConstIterator &&rhs);
  const std::pair< Key, Value > &operator*() const;
  const std::pair< Key, Value > *operator->() const;
  RNLConstIterator &operator++();
  RNLConstIterator operator++(int);
  RNLConstIterator &operator--();
  RNLConstIterator operator--(int);
  bool operator==(const RNLConstIterator &rhs) const;
  bool operator!=(const RNLConstIterator &rhs) const;
private:
  const Node *node_;
};

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator::RNLConstIterator()
{
  node_(nullptr);
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator::RNLConstIterator(const Node *node)
{
  node_ = node;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator::RNLConstIterator(const RNLConstIterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator::RNLConstIterator(const ConstIterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value, typename Compare >
sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator::RNLConstIterator(const LNRConstIterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator &sobolevsky::AVLtree< Key, Value,
Compare >::RNLConstIterator::operator=(const RNLConstIterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator &sobolevsky::AVLtree< Key, Value,
Compare >::RNLConstIterator::operator=(RNLConstIterator &&rhs)
{
  node_(rhs.node_);
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator &sobolevsky::AVLtree< Key, Value,
Compare >::RNLConstIterator::operator=(const ConstIterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator &sobolevsky::AVLtree< Key, Value,
Compare >::RNLConstIterator::operator=(ConstIterator &&rhs)
{
  node_(rhs.node_);
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator &sobolevsky::AVLtree< Key, Value,
Compare >::RNLConstIterator::operator=(const LNRConstIterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator &sobolevsky::AVLtree< Key, Value,
Compare >::RNLConstIterator::operator=(LNRConstIterator &&rhs)
{
  node_(rhs.node_);
  return *this;
}

template< typename Key, typename Value, typename Compare >
const std::pair< Key, Value > &sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator::operator*() const
{
  return node_->data;
}

template< typename Key, typename Value, typename Compare >
const std::pair< Key, Value > *sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator::operator->() const
{
  return std::addressof(node_->data);
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator
&sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator::operator++()
{
  if (node_ == nullptr)
  {
    return *this;
  }
  else if (node_->left == nullptr)
  {
    Node *temp = node_->parent;
    while (temp != nullptr && node_ == temp->left)
    {
      node_ = temp;
      temp = node_->parent;
    }
    node_ = temp;
    return *this;
  }
  else
  {
    node_ = node_->left;
    while (node_->right != nullptr)
    {
      node_ = node_->right;
    }
    return *this;
  }
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator sobolevsky::AVLtree< Key, Value,
Compare >::RNLConstIterator::operator++(int)
{
  RNLConstIterator temp(*this);
  ++(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator
&sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator::operator--()
{
  if (node_ == nullptr)
  {
    return *this;
  }
  else if (node_->right == nullptr)
  {
    Node *temp = node_->parent;
    while (temp != nullptr && node_ == temp->right)
    {
      node_ = temp;
      temp = node_->parent;
    }
    node_ = temp;
    return *this;
  }
  else
  {
    node_ = node_->right;
    if (node_->left == nullptr)
    {
      return *this;
    }
    while (node_->left != nullptr)
    {
      node_ = node_->left;
    }
    return *this;
  }
}

template< typename Key, typename Value, typename Compare >
typename sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator sobolevsky::AVLtree< Key, Value,
Compare >::RNLConstIterator::operator--(int)
{
  RNLConstIterator temp(*this);
  --(*this);
  return temp;
}

template< typename Key, typename Value, typename Compare >
bool sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator::operator==(const RNLConstIterator &rhs) const
{
  return node_ == rhs.node_;
}

template< typename Key, typename Value, typename Compare >
bool sobolevsky::AVLtree< Key, Value, Compare >::RNLConstIterator::operator!=(const RNLConstIterator &rhs) const
{
  return node_ != rhs.node_;
}

#endif
