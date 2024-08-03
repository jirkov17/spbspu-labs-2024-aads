#ifndef MYMAP_HPP
#define MYMAP_HPP

#include <iostream>
#include <utility>
#include <algorithm>
#include <stdexcept>

namespace sobolevsky
{
  template< typename Key, typename Value >
  class MyMap
  {
  public:
    class Iterator;
    class ConstIterator;

    MyMap();
    MyMap(const MyMap< Key, Value > &tree);
    MyMap(MyMap< Key, Value > &&rhs) noexcept;
    ~MyMap() = default;

    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;

    size_t size();
    bool empty();

    Value &operator[](const Key &key);
    Value &at(const Key &key);

    void insert(const std::pair< Key, Value > &pair);
    void erase(const Key &key);
    void erase(ConstIterator position);
    void clear();
    void swap(MyMap &x);

    Iterator find(const Key &key);
    size_t count(const Key &key);
    std::pair< Iterator, Iterator > equal_range(const Key &key);
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
class sobolevsky::MyMap< Key, Value >::Node
{
  friend class MyMap;
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

template< typename Key, typename Value >
sobolevsky::MyMap< Key, Value >::MyMap()
{
  root = nullptr;
  size_ = 0;
}

template< typename Key, typename Value >
sobolevsky::MyMap< Key, Value >::MyMap(const MyMap< Key, Value > &tree)
{
  root = tree.root;
  size_ = tree.size_;
}

template< typename Key, typename Value >
sobolevsky::MyMap< Key, Value >::MyMap(MyMap< Key, Value > &&rhs) noexcept
{
  root = rhs.root;
  size_ = std::move(rhs.size_);
}

template< typename Key, typename Value >
size_t sobolevsky::MyMap< Key, Value >::size()
{
  return size_;
}

template< typename Key, typename Value >
bool sobolevsky::MyMap< Key, Value >::empty()
{
  return size_ == 0;
}

template< typename Key, typename Value >
Value &sobolevsky::MyMap< Key, Value >::operator[](const Key &key)
{
  Iterator iter(find(key));
  if (iter == end())
  {
    insert(std::pair< Key, Value>(key, Value()));
    iter = find(key);
  }
  return iter->second;
}

template< typename Key, typename Value >
Value &sobolevsky::MyMap< Key, Value >::at(const Key &key)
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

template< typename Key, typename Value >
void sobolevsky::MyMap< Key, Value >::insert(const std::pair< Key, Value > &pair)
{
  root = push(pair.first, pair.second, root);
  size_++;
}

template< typename Key, typename Value >
typename sobolevsky::MyMap< Key, Value >::Node *sobolevsky::MyMap< Key, Value >::push
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

template< typename Key, typename Value >
typename sobolevsky::MyMap< Key, Value >::Node *sobolevsky::MyMap< Key, Value >::RightRotate(Node *node_)
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
typename sobolevsky::MyMap< Key, Value >::Node *sobolevsky::MyMap< Key, Value >::LeftRotate(Node *node_)
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
typename sobolevsky::MyMap< Key, Value >::Node *sobolevsky::MyMap< Key, Value >::LeftRightRotate(Node *node_)
{
  node_->left = LeftRotate(node_->left);
  return RightRotate(node_);
}

template< typename Key, typename Value >
typename sobolevsky::MyMap< Key, Value >::Node *sobolevsky::MyMap< Key, Value >::RightLeftRotate(Node *node_)
{
  node_->right = RightRotate(node_->right);
  return LeftRotate(node_);
}

template< typename Key, typename Value >
void sobolevsky::MyMap< Key, Value >::erase(const Key &key)
{
  root = delet(key, root);
  size_--;
}

template< typename Key, typename Value >
void sobolevsky::MyMap< Key, Value >::erase(ConstIterator position)
{
  root = delet(position->data.first, root);
  size_--;
}

template< typename Key, typename Value >
typename sobolevsky::MyMap< Key, Value >::Node *sobolevsky::MyMap< Key, Value >::delet(const Key &key, Node *node_)
{
  if (node_ == nullptr)
  {
    return nullptr;
  }
  else if (key < node_->data.first)
  {
    node_->left = delet(key, node_->left);
  }
  else if (key > node_->data.first)
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
    node_->right = delet(node_->data.first, node_->right);
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
size_t sobolevsky::MyMap< Key, Value >::height(Node *node_)
{
  return (node_ == nullptr ? 0 : node_->height);
}

template< typename Key, typename Value >
void sobolevsky::MyMap< Key, Value >::recurionDeleteAll(Node *node)
{
  if (node != nullptr)
  {
    recurionDeleteAll(node->left);
    recurionDeleteAll(node->right);
    delete node;
  }
}

template< typename Key, typename Value >
void sobolevsky::MyMap< Key, Value >::clear()
{
  recurionDeleteAll(root);
  root = nullptr;
  size_ = 0;
}

template< typename Key, typename Value >
void sobolevsky::MyMap< Key, Value >::swap(MyMap &x)
{
  std::swap(root, x.root);
  std::swap(size_, x.size_);
}

template< typename Key, typename Value >
size_t sobolevsky::MyMap< Key, Value >::count(const Key &key)
{
  if (find(key) == end())
  {
    return 0;
  }
  return 1;
}

template< typename Key, typename Value >
std::pair< typename sobolevsky::MyMap< Key, Value >::Iterator, typename sobolevsky::MyMap< Key, Value >::Iterator >
sobolevsky::MyMap< Key, Value >::equal_range(const Key &key)
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

template< typename Key, typename Value >
class sobolevsky::MyMap< Key, Value >::Iterator
{
  friend class MyMap;
public:
  Iterator();
  Iterator(Node *node);
  Iterator(const Iterator &iter);
  ~Iterator() = default;

  Iterator &operator=(const Iterator &iter);
  Iterator &operator=(Iterator &&rhs);
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

template< typename Key, typename Value >
sobolevsky::MyMap< Key, Value >::Iterator::Iterator()
{
  node_ = nullptr;
}

template< typename Key, typename Value >
sobolevsky::MyMap< Key, Value >::Iterator::Iterator(Node *node)
{
  node_ = node;
}

template< typename Key, typename Value >
sobolevsky::MyMap< Key, Value >::Iterator::Iterator(const Iterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value >
typename sobolevsky::MyMap< Key, Value >::Iterator &sobolevsky::MyMap< Key, Value >::Iterator::operator=(const Iterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value >
typename sobolevsky::MyMap< Key, Value >::Iterator &sobolevsky::MyMap< Key, Value >::Iterator::operator=(Iterator &&rhs)
{
  node_ = rhs.node_;
  return *this;
}

template< typename Key, typename Value >
std::pair< Key, Value > &sobolevsky::MyMap< Key, Value >::Iterator::operator*()
{
  return node_->data;
}

template< typename Key, typename Value >
std::pair< Key, Value > *sobolevsky::MyMap< Key, Value >::Iterator::operator->()
{
  return std::addressof(node_->data);
}

template< typename Key, typename Value >
typename sobolevsky::MyMap< Key, Value >::Iterator &sobolevsky::MyMap< Key, Value >::Iterator::operator++()
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
typename sobolevsky::MyMap< Key, Value >::Iterator sobolevsky::MyMap< Key, Value >::Iterator::operator++(int)
{
  Iterator temp(*this);
  ++(*this);
  return temp;
}

template< typename Key, typename Value >
typename sobolevsky::MyMap< Key, Value >::Iterator &sobolevsky::MyMap< Key, Value >::Iterator::operator--()
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
typename sobolevsky::MyMap< Key, Value >::Iterator sobolevsky::MyMap< Key, Value >::Iterator::operator--(int)
{
  Iterator temp(*this);
  --(*this);
  return temp;
}

template< typename Key, typename Value >
bool sobolevsky::MyMap< Key, Value >::Iterator::operator==(const Iterator &rhs) const
{
  return node_ == rhs.node_;
}

template< typename Key, typename Value >
bool sobolevsky::MyMap< Key, Value >::Iterator::operator!=(const Iterator &rhs) const
{
  return node_ != rhs.node_;
}

template< typename Key, typename Value >
typename sobolevsky::MyMap< Key, Value >::Iterator sobolevsky::MyMap< Key, Value >::begin() noexcept
{
  Node *temp = root;
  while (temp->left != nullptr)
  {
    temp = temp->left;
  }
  return Iterator(temp);
}

template< typename Key, typename Value >
typename sobolevsky::MyMap< Key, Value >::Iterator sobolevsky::MyMap< Key, Value >::end() noexcept
{
  return Iterator(nullptr);
}

template< typename Key, typename Value >
typename sobolevsky::MyMap< Key, Value >::ConstIterator sobolevsky::MyMap< Key, Value >::cbegin() const noexcept
{
  Node *temp = root;
  while (temp->left != nullptr)
  {
    temp = temp->left;
  }
  return ConstIterator(temp);
}

template< typename Key, typename Value >
typename sobolevsky::MyMap< Key, Value >::ConstIterator sobolevsky::MyMap< Key, Value >::cend() const noexcept
{
  return ConstIterator(nullptr);
}

template< typename Key, typename Value >
typename sobolevsky::MyMap< Key, Value >::Iterator sobolevsky::MyMap< Key, Value >::find(const Key &key)
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

template< typename Key, typename Value >
class sobolevsky::MyMap< Key, Value >::ConstIterator
{
  friend class MyMap;
public:
  ConstIterator();
  explicit ConstIterator(const Node *node);
  ConstIterator(const ConstIterator &iter);
  ~ConstIterator() = default;

  ConstIterator &operator=(const ConstIterator &iter);
  ConstIterator &operator=(ConstIterator &&rhs);
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

template< typename Key, typename Value >
sobolevsky::MyMap< Key, Value >::ConstIterator::ConstIterator()
{
  node_ = nullptr;
}

template< typename Key, typename Value >
sobolevsky::MyMap< Key, Value >::ConstIterator::ConstIterator(const Node *node)
{
  node_ = node;
}

template< typename Key, typename Value >
sobolevsky::MyMap< Key, Value >::ConstIterator::ConstIterator(const ConstIterator &iter)
{
  node_ = iter.node_;
}

template< typename Key, typename Value >
typename sobolevsky::MyMap< Key, Value >::ConstIterator &sobolevsky::MyMap< Key, Value >::ConstIterator::operator=
(const ConstIterator &iter)
{
  node_ = iter.node_;
  return *this;
}

template< typename Key, typename Value >
typename sobolevsky::MyMap< Key, Value >::ConstIterator &sobolevsky::MyMap< Key, Value >::ConstIterator::operator=
(ConstIterator &&rhs)
{
  node_(rhs.node_);
  return *this;
}

template< typename Key, typename Value >
const std::pair< Key, Value > &sobolevsky::MyMap< Key, Value >::ConstIterator::operator*() const
{
  return node_->data;
}

template< typename Key, typename Value >
const std::pair< Key, Value > *sobolevsky::MyMap< Key, Value >::ConstIterator::operator->() const
{
  return std::addressof(node_->data);
}

template< typename Key, typename Value >
typename sobolevsky::MyMap< Key, Value >::ConstIterator &sobolevsky::MyMap< Key, Value >::ConstIterator::operator++()
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
typename sobolevsky::MyMap< Key, Value >::ConstIterator sobolevsky::MyMap< Key, Value >::ConstIterator::operator++(int)
{
  ConstIterator temp(*this);
  ++(*this);
  return temp;
}

template< typename Key, typename Value >
typename sobolevsky::MyMap< Key, Value >::ConstIterator &sobolevsky::MyMap< Key, Value >::ConstIterator::operator--()
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
typename sobolevsky::MyMap< Key, Value >::ConstIterator sobolevsky::MyMap< Key, Value >::ConstIterator::operator--(int)
{
  ConstIterator temp(*this);
  --(*this);
  return temp;
}

template< typename Key, typename Value >
bool sobolevsky::MyMap< Key, Value >::ConstIterator::operator==(const ConstIterator &rhs) const
{
  return node_ == rhs.node_;
}

template< typename Key, typename Value >
bool sobolevsky::MyMap< Key, Value >::ConstIterator::operator!=(const ConstIterator &rhs) const
{
  return node_ != rhs.node_;
}

#endif
