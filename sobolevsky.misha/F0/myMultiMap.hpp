#ifndef MYMULTIMAP_HPP
#define MYMULTIMAP_HPP

#include <iostream>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include "myList.hpp"

namespace sobolevsky
{
  template< typename Key, typename Value >
  class MyMultiMap
  {
  public:
    class Iterator;
    class ConstIterator;

    MyMultiMap();
    MyMultiMap(const MyMultiMap< Key, Value > &tree);
    MyMultiMap(MyMultiMap< Key, Value > &&rhs) noexcept;
    ~MyMultiMap() = default;

    Iterator begin() noexcept;
    Iterator end() noexcept;
    Iterator rbegin() noexcept;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;

    size_t size();
    bool empty();

    List< Value > &operator[](const Key &key);
    List< Value > &at(const Key &key);

    void insert(const std::pair< Key, Value > &pair);
    void erase(const Key &key);
    void erase(ConstIterator position);
    void clear();
    void swap(MyMultiMap &x);

    Iterator find(const Key &key);
    size_t count(const Key &key);
  private:
    class Node;

    Node *push(const Key &key, const Value &value, Node *node_);
    Node *RightRotate(Node *node_);
    Node *LeftRotate(Node *node_);
    Node *LeftRightRotate(Node *node_);
    Node *RightLeftRotate(Node *node_);
    Node *delet(const Key &key, Node *node_);
    size_t height(Node *node_);
    void recurionDeleteAll(Node *node);

    Node *root;
    size_t size_;
  };
}

template< typename Key, typename Value >
class sobolevsky::MyMultiMap< Key, Value >::Node
{
  friend class MyMultiMap;
public:
  Node(const Key key, const Value value)
  {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    height = 1;
    key_ = key;
    data.pushBack(value);
  }
private:
  Node *left;
  Node *right;
  Node *parent;
  size_t height;
  Key key_;
  List< Value > data;
};

template< typename Key, typename Value >
sobolevsky::MyMultiMap< Key, Value >::MyMultiMap()
{
  root = nullptr;
  size_ = 0;
}

template< typename Key, typename Value >
sobolevsky::MyMultiMap< Key, Value >::MyMultiMap(const MyMultiMap< Key, Value > &tree)
{
  root = tree.root;
  size_ = tree.size_;
}

template< typename Key, typename Value >
sobolevsky::MyMultiMap< Key, Value >::MyMultiMap(MyMultiMap< Key, Value > &&rhs) noexcept
{
  root = rhs.root;
  size_ = std::move(rhs.size_);
}

template< typename Key, typename Value >
size_t sobolevsky::MyMultiMap< Key, Value >::size()
{
  return size_;
}

template< typename Key, typename Value >
bool sobolevsky::MyMultiMap< Key, Value >::empty()
{
  return size_ == 0;
}

template< typename Key, typename Value >
typename sobolevsky::List< Value > &sobolevsky::MyMultiMap< Key, Value >::operator[](const Key &key)
{
  Iterator iter(find(key));
  if (iter == end())
  {
    insert(std::pair< Key, Value>(key, Value()));
    iter = find(key);
  }
  return iter->data;
}

template< typename Key, typename Value >
typename sobolevsky::List< Value > &sobolevsky::MyMultiMap< Key, Value >::at(const Key &key)
{
  if (find(key) == end())
  {
    throw std::out_of_range("Such key does not exist\n");
  }
  else
  {
    return (find(key));
  }
}

template< typename Key, typename Value >
void sobolevsky::MyMultiMap< Key, Value >::insert(const std::pair< Key, Value > &pair)
{
  if (find(pair.first) != end())
  {
    find(pair.first)->pushBack(pair.second);
    size_++;
  }
  else
  {
    root = push(pair.first, pair.second, root);
    size_++;
  }
}

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::Node *sobolevsky::MyMultiMap< Key, Value >::push
(const Key &key, const Value &value, Node *node_)
{
  if (node_ == nullptr)
  {
    node_ = new Node(key, value);
  }
  else if (key < node_->key_)
  {
    node_->left = push(key, value, node_->left);
    node_->left->parent = node_;
    node_->height++;
    if (height(node_->left) - height(node_->right) > 1)
    {
      if (node_->right == nullptr || key < node_->left->key_)
      {
        node_ = RightRotate(node_);
      }
      else
      {
        node_ = LeftRightRotate(node_);
      }
    }
  }
  else if (key > node_->key_)
  {
    node_->right = push(key, value, node_->right);
    node_->right->parent = node_;
    node_->height++;
    if ((height(node_->right) - height(node_->left)) > 1)
    {
      if (node_->left == nullptr || key > node_->right->key_)
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

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::Node *sobolevsky::MyMultiMap< Key, Value >::RightRotate(Node *node_)
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


template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::Node *sobolevsky::MyMultiMap< Key, Value >::LeftRotate(Node *node_)
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

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::Node *sobolevsky::MyMultiMap< Key, Value >::LeftRightRotate(Node *node_)
{
  node_->left = LeftRotate(node_->left);
  return RightRotate(node_);
}

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::Node *sobolevsky::MyMultiMap< Key, Value >::RightLeftRotate(Node *node_)
{
  node_->right = RightRotate(node_->right);
  return LeftRotate(node_);
}

template< typename Key, typename Value >
void sobolevsky::MyMultiMap< Key, Value >::erase(const Key &key)
{
  root = delet(key, root);
  size_--;
}

template< typename Key, typename Value >
void sobolevsky::MyMultiMap< Key, Value >::erase(ConstIterator position)
{
  root = delet(position->key_, root);
  size_--;
}

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::Node *sobolevsky::MyMultiMap< Key, Value >::delet(const Key &key, Node *node_)
{
  if (node_ == nullptr)
  {
    return nullptr;
  }
  else if (key < node_->key_)
  {
    node_->left = delet(key, node_->left);
  }
  else if (key > node_->key_)
  {
    node_->right = delet(key, node_->right);
  }
  else if (node_->left && node_->right)
  {
    Node *temp = node_->right;
    while (temp->left != nullptr)
    {
      temp = temp->left;
    }
    node_->data = temp->data;
    node_->right = delet(node_->key_, node_->right);
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

template< typename Key, typename Value >
size_t sobolevsky::MyMultiMap< Key, Value >::height(Node *node_)
{
  return (node_ == nullptr ? 0 : node_->height);
}

template< typename Key, typename Value >
void sobolevsky::MyMultiMap< Key, Value >::recurionDeleteAll(Node *node)
{
  if (node != nullptr)
  {
    recurionDeleteAll(node->left);
    recurionDeleteAll(node->right);
    node->data.clear();
    delete node;
  }
}

template< typename Key, typename Value >
void sobolevsky::MyMultiMap< Key, Value >::clear()
{
  recurionDeleteAll(root);
  root = nullptr;
  size_ = 0;
}

template< typename Key, typename Value >
void sobolevsky::MyMultiMap< Key, Value >::swap(MyMultiMap &x)
{
  std::swap(root, x.root);
  std::swap(size_, x.size_);
}

template< typename Key, typename Value >
size_t sobolevsky::MyMultiMap< Key, Value >::count(const Key &key)
{
  if (find(key) == end())
  {
    return 0;
  }
  return find(key)->data.size();
}

template< typename Key, typename Value >
class sobolevsky::MyMultiMap< Key, Value >::Iterator
{
  friend class MyMultiMap;
public:
  Iterator();
  Iterator(Node *node);
  Iterator(const Iterator &iter);
  ~Iterator() = default;

  Iterator &operator=(const Iterator &iter);
  Iterator &operator=(Iterator &&rhs);
  List< Value > &operator*();
  List< Value > *operator->();
  Iterator &operator++();
  Iterator operator++(int);
  Iterator &operator--();
  Iterator operator--(int);
  bool operator==(const Iterator &rhs) const;
  bool operator!=(const Iterator &rhs) const;
  Key getKey();
private:
  Node *node_;
};

template< typename Key, typename Value >
sobolevsky::MyMultiMap< Key, Value >::Iterator::Iterator()
{
  node_ = nullptr;
}

template< typename Key, typename Value >
sobolevsky::MyMultiMap< Key, Value >::Iterator::Iterator(Node *node)
{
  node_ = node;
}

template< typename Key, typename Value >
sobolevsky::MyMultiMap< Key, Value >::Iterator::Iterator(const Iterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::Iterator &sobolevsky::MyMultiMap< Key, Value >::Iterator::operator=(const Iterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::Iterator &sobolevsky::MyMultiMap< Key, Value >::Iterator::operator=(Iterator &&rhs)
{
  node_ = rhs.node_;
  return *this;
}

template< typename Key, typename Value >
sobolevsky::List< Value > &sobolevsky::MyMultiMap< Key, Value >::Iterator::operator*()
{
  return node_->data;
}

template< typename Key, typename Value >
sobolevsky::List< Value > *sobolevsky::MyMultiMap< Key, Value >::Iterator::operator->()
{
  return std::addressof(node_->data);
}

template< typename Key, typename Value >
Key sobolevsky::MyMultiMap< Key, Value >::Iterator::getKey()
{
  return node_->key_;
}

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::Iterator &sobolevsky::MyMultiMap< Key, Value >::Iterator::operator++()
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

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::Iterator sobolevsky::MyMultiMap< Key, Value >::Iterator::operator++(int)
{
  Iterator temp(*this);
  ++(*this);
  return temp;
}

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::Iterator &sobolevsky::MyMultiMap< Key, Value >::Iterator::operator--()
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

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::Iterator sobolevsky::MyMultiMap< Key, Value >::Iterator::operator--(int)
{
  Iterator temp(*this);
  --(*this);
  return temp;
}

template< typename Key, typename Value >
bool sobolevsky::MyMultiMap< Key, Value >::Iterator::operator==(const Iterator &rhs) const
{
  return node_ == rhs.node_;
}

template< typename Key, typename Value >
bool sobolevsky::MyMultiMap< Key, Value >::Iterator::operator!=(const Iterator &rhs) const
{
  return node_ != rhs.node_;
}

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::Iterator sobolevsky::MyMultiMap< Key, Value >::begin() noexcept
{
  Node *temp = root;
  while (temp->left != nullptr)
  {
    temp = temp->left;
  }
  return Iterator(temp);
}

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::Iterator sobolevsky::MyMultiMap< Key, Value >::end() noexcept
{
  return Iterator(nullptr);
}

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::Iterator sobolevsky::MyMultiMap< Key, Value >::rbegin() noexcept
{
  Node *temp = root;
  while (temp->right != nullptr)
  {
    temp = temp->right;
  }
  return Iterator(temp);
}

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::ConstIterator sobolevsky::MyMultiMap< Key, Value >::cbegin() const noexcept
{
  Node *temp = root;
  while (temp->left != nullptr)
  {
    temp = temp->left;
  }
  return ConstIterator(temp);
}

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::ConstIterator sobolevsky::MyMultiMap< Key, Value >::cend() const noexcept
{
  return ConstIterator(nullptr);
}

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::Iterator sobolevsky::MyMultiMap< Key, Value >::find(const Key &key)
{
  Node *temp = root;
  while (temp)
  {
    if (temp->key_ == key)
    {
      return Iterator(temp);
    }
    else if (key > temp->key_)
    {
      temp = temp->right;
    }
    else if (key < temp->key_)
    {
      temp = temp->left;
    }
  }
  return end();
}

template< typename Key, typename Value >
class sobolevsky::MyMultiMap< Key, Value >::ConstIterator
{
  friend class MyMultiMap;
public:
  ConstIterator();
  explicit ConstIterator(const Node *node);
  ConstIterator(const ConstIterator &iter);
  ~ConstIterator() = default;

  ConstIterator &operator=(const ConstIterator &iter);
  ConstIterator &operator=(ConstIterator &&rhs);
  const List < Value > &operator*() const;
  const List < Value > *operator->() const;
  ConstIterator &operator++();
  ConstIterator operator++(int);
  ConstIterator &operator--();
  ConstIterator operator--(int);
  bool operator==(const ConstIterator &rhs) const;
  bool operator!=(const ConstIterator &rhs) const;
private:
  const Node *node_;
};

template< typename Key, typename Value >
sobolevsky::MyMultiMap< Key, Value >::ConstIterator::ConstIterator()
{
  node_(nullptr);
}

template< typename Key, typename Value >
sobolevsky::MyMultiMap< Key, Value >::ConstIterator::ConstIterator(const Node *node)
{
  node_ = node;
}

template< typename Key, typename Value >
sobolevsky::MyMultiMap< Key, Value >::ConstIterator::ConstIterator(const ConstIterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::ConstIterator &sobolevsky::MyMultiMap< Key, Value >::ConstIterator::operator=
(const ConstIterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::ConstIterator &sobolevsky::MyMultiMap< Key, Value >::ConstIterator::operator=
(ConstIterator &&rhs)
{
  node_(rhs.node_);
  return *this;
}

template< typename Key, typename Value >
const sobolevsky::List < Value > &sobolevsky::MyMultiMap< Key, Value >::ConstIterator::operator*() const
{
  return node_->data;
}

template< typename Key, typename Value >
const sobolevsky::List < Value > *sobolevsky::MyMultiMap< Key, Value >::ConstIterator::operator->() const
{
  return std::addressof(node_->data);
}

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::ConstIterator &sobolevsky::MyMultiMap< Key, Value >::ConstIterator::operator++()
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

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::ConstIterator sobolevsky::MyMultiMap< Key, Value >::ConstIterator::operator++(int)
{
  ConstIterator temp(*this);
  ++(*this);
  return temp;
}

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::ConstIterator &sobolevsky::MyMultiMap< Key, Value >::ConstIterator::operator--()
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

template< typename Key, typename Value >
typename sobolevsky::MyMultiMap< Key, Value >::ConstIterator sobolevsky::MyMultiMap< Key, Value >::ConstIterator::operator--(int)
{
  ConstIterator temp(*this);
  --(*this);
  return temp;
}

template< typename Key, typename Value >
bool sobolevsky::MyMultiMap< Key, Value >::ConstIterator::operator==(const ConstIterator &rhs) const
{
  return node_ == rhs.node_;
}

template< typename Key, typename Value >
bool sobolevsky::MyMultiMap< Key, Value >::ConstIterator::operator!=(const ConstIterator &rhs) const
{
  return node_ != rhs.node_;
}

#endif
