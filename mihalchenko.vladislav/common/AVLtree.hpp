#ifndef AVLTREE_HPP
#define AVLTREE_HPP
#include <utility>
#include <iterator>
#include <initializer_list>
#include <functional>
#include <iostream>
#include "stack.hpp"
#include "queue.hpp"

namespace mihalchenko
{
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class AVLTree
  {
  public:
    class ConstIterator;
    class Iterator;

    AVLTree();

    template < class InputIt >
    AVLTree(InputIt start, InputIt stop);

    using pair_t = std::pair< const Key, Value >;
    AVLTree(size_t count, pair_t &pairKeyVal);
    AVLTree(std::initializer_list< pair_t > initAVL);
    AVLTree(const AVLTree &copy);
    AVLTree(AVLTree &&move);
    ~AVLTree();

    AVLTree &operator=(AVLTree other);

    void insert(const Key &key, const Value &value);
    void insert(const pair_t &pairKeyVal);
    bool empty() const noexcept;
    size_t getSize() const noexcept;
    size_t erase(const Key &key);
    void erase(Iterator pos);
    void clear();
    void swap(AVLTree &) noexcept;

    Value &at(const Key &);
    const Value &at(const Key &key) const;

    Value &operator[](const Key &key);
    const Value &operator[](const Key &) const;
    Iterator find(const Key &);
    ConstIterator find(const Key &) const;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;
    Iterator begin() noexcept;
    Iterator end() noexcept;

    template< typename F >
    F constTraverseLR(F stackFunc) const;
    template< typename F >
    F traverseLR(F stackFunc);
    template< typename F >
    F constTraverseRL(F stackFunc) const;
    template< typename F >
    F traverseRL(F stackFunc);
    template< typename F >
    F constTraverseBreadth(F stackFunc) const;
    template< typename F >
    F traverseBreadth(F stackFunc);

  private:
    class Node
    {
    public:
      friend class AVLTree;
      Node(Key key, Value data, int height = 0, Node *left = nullptr, Node *right = nullptr, Node *previous = nullptr);

    private:
      pair_t pairOfKeyVal_;
      int height_;
      Node *left_;
      Node *right_;
      Node *previous_;
    };

    Node *insertNode(const Key &key, const Value &val, Node *node);
    Iterator findNode(const Key &key, Node *node);
    ConstIterator findNode(const Key &key, Node *node) const;
    Node *eraseNode(const Key &key);

    int calcHeight(Node *node);
    void balancingTree(Node *overweight);
    void leftrightSpin(Node *node);
    void rightleftSpin(Node *node);
    void leftSpin(Node *node);
    void rightSpin(Node *node);

    int getHeight(Node *node);
    Node *getRoot();
    const Node *getRoot() const;

    Node *copyTree(Node *node, Node *previous);
    void clear(Node *node);

    Node *root_;
    size_t size_ = 0;
  };
}

template < typename Key, typename Value, typename Compare >
class mihalchenko::AVLTree< Key, Value, Compare >::ConstIterator :
  public std::iterator< std::bidirectional_iterator_tag, std::pair< const Key, Value > >
{
public:
  friend class AVLTree< Key, Value, Compare >;
  ConstIterator();
  ConstIterator(Node *node, Node *root);
  ConstIterator(const ConstIterator &) = default;
  ~ConstIterator() = default;

  ConstIterator &operator++();
  ConstIterator operator++(int);
  ConstIterator &operator--();
  ConstIterator operator--(int);
  const pair_t &operator*() const;
  const pair_t *operator->() const;
  bool operator!=(const ConstIterator &rhs) const;
  bool operator==(const ConstIterator &rhs) const;
  ConstIterator &operator=(const ConstIterator &) = default;

private:
  Node *node_;
  Node *root_;
};

template < typename Key, typename Value, typename Compare >
class mihalchenko::AVLTree< Key, Value, Compare >::Iterator :
  public std::iterator< std::bidirectional_iterator_tag, Key, Value, Compare >
{
public:
  friend class AVLTree< Key, Value, Compare >;
  Iterator();
  Iterator(ConstIterator iter);
  Iterator(const Iterator &) = default;
  ~Iterator() = default;

  Iterator &operator++();
  Iterator operator++(int);
  Iterator &operator--();
  Iterator operator--(int);
  Iterator &operator=(const Iterator &) = default;
  pair_t &operator*();
  pair_t *operator->();
  const pair_t &operator*() const;
  const pair_t *operator->() const;
  bool operator!=(const Iterator &rhs) const;
  bool operator==(const Iterator &rhs) const;

private:
  ConstIterator constIter_;
};

template < typename Key, typename Value, typename Compare >
mihalchenko::AVLTree< Key, Value, Compare >::Node::Node(Key key, Value data, int height, Node *left, Node *right, Node *previous) :
  pairOfKeyVal_(std::make_pair(key, data)),
  height_(height),
  left_(left),
  right_(right),
  previous_(previous)
{}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::Node
  *mihalchenko::AVLTree< Key, Value, Compare >::insertNode(const Key &key, const Value &val, Node *node)
{
  Node *newNode = new Node(key, val, 0, nullptr, nullptr, nullptr);
  if (!node)
  {
    root_ = newNode;
    size_++;
    return root_;
  }
  if ((node) && (key == node->pairOfKeyVal_.first))
  {
    delete newNode;
    return nullptr;
  }
  bool existNode = true;
  while (existNode)
  {
    if (key < node->pairOfKeyVal_.first)
    {
      if (!node->left_)
      {
        node->left_ = newNode;
        newNode->previous_ = node;
        size_++;
        existNode = false;
      }
      node = node->left_;
    }
    else
    {
      if (!node->right_)
      {
        node->right_ = newNode;
        newNode->previous_ = node;
        size_++;
        existNode = false;
      }
      node = node->right_;
    }
  }
  return newNode;
}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::Node
  *mihalchenko::AVLTree< Key, Value, Compare >::eraseNode(const Key &key)
{
  Node *deletedNode = find(key).constIter_.node_;
  Node *prevDelNode = deletedNode->previous_;
  Node *workerNode = deletedNode;
  Node *firstRightNode = nullptr;
  Node *tempNode = nullptr;
  if ((deletedNode->left_ == nullptr) && (deletedNode->right_ == nullptr))
  {
    if (prevDelNode)
    {
      if (prevDelNode->left_)
      {
        (prevDelNode->left_ == deletedNode) ? prevDelNode->left_ = nullptr : prevDelNode->right_ = nullptr;
      }
      else
      {
        (prevDelNode->right_ == deletedNode) ? prevDelNode->right_ = nullptr : prevDelNode->left_ = nullptr;
      }
    }
    else
    {
      root_ = nullptr;
    }
    tempNode = deletedNode;
    delete deletedNode;
  }
  else if (!(deletedNode->left_ == nullptr) && !(deletedNode->right_ == nullptr))
  {
    workerNode = deletedNode->right_;
    while (workerNode->left_)
    {
      workerNode = workerNode->left_;
    }
    firstRightNode = workerNode;

    workerNode = deletedNode->left_;
    workerNode->previous_ = firstRightNode;
    firstRightNode->left_ = workerNode;
    if (deletedNode == root_)
    {
      root_ = firstRightNode;
    }
    tempNode = deletedNode;
    delete deletedNode;
  }
  else
  {
    if (prevDelNode)
    {
      if (prevDelNode->left_ == deletedNode)
      {
        if (!(deletedNode->left_ = nullptr))
        {
          deletedNode->left_->previous_ = prevDelNode;
          prevDelNode->left_ = deletedNode->left_;
        }
        else
        {
          deletedNode->right_->previous_ = prevDelNode;
          prevDelNode->left_ = deletedNode->right_;
        }
      }
      else
      {
        if (!(deletedNode->right_ = nullptr))
        {
          deletedNode->left_->previous_ = prevDelNode;
          prevDelNode->right_ = deletedNode->left_;
        }
        else
        {
          deletedNode->right_->previous_ = prevDelNode;
          prevDelNode->right_ = deletedNode->right_;
        }
      }
    }
    else
    {
      (deletedNode->right_) ? root_ = deletedNode->right_ : root_ = deletedNode->left_;
    }
    tempNode = deletedNode;
    delete deletedNode;
  }
  size_--;
  return tempNode;
}

template < typename Key, typename Value, typename Compare >
mihalchenko::AVLTree< Key, Value, Compare >::AVLTree()
{
  root_ = nullptr;
  size_ = 0;
}

template < typename Key, typename Value, typename Compare >
mihalchenko::AVLTree< Key, Value, Compare >::AVLTree(size_t count, pair_t &pairKeyVal)
{
  root_ = nullptr;
  size_ = 0;
  for (size_t i = 0; i < count; ++i)
  {
    insert(pairKeyVal);
    size_++;
  }
}

template < typename Key, typename Value, typename Compare >
template < class InputIt >
  mihalchenko::AVLTree< Key, Value, Compare >::AVLTree(InputIt start, InputIt stop)
{
  root_ = nullptr;
  size_ = 0;
  for (InputIt it = start; it != stop; ++it)
  {
    insert(*it);
    size_++;
  }
}

template < typename Key, typename Value, typename Compare >
mihalchenko::AVLTree< Key, Value, Compare >::AVLTree(std::initializer_list< pair_t > initAVL)
{
  root_ = nullptr;
  size_ = 0;
  for (auto it = initAVL.begin(); it != initAVL.end(); ++it)
  {
    insert(*it);
    size_++;
  }
}

template < typename Key, typename Value, typename Compare >
mihalchenko::AVLTree< Key, Value, Compare >::AVLTree(const AVLTree &copy)
{
  root_ = copyTree(copy.root_, nullptr);
}

template < typename Key, typename Value, typename Compare >
mihalchenko::AVLTree< Key, Value, Compare >::AVLTree(AVLTree &&move)
{
  root_ = copyTree(std::move(move.root_), nullptr);
  move.clear();
  move.root_ = nullptr;
  move.size_ = 0;
}

template < typename Key, typename Value, typename Compare >
mihalchenko::AVLTree< Key, Value, Compare >::~AVLTree()
{
  clear();
  root_ = nullptr;
}

template< typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::AVLTree
  &mihalchenko::AVLTree< Key, Value, Compare >::operator=(AVLTree other)
{
  clear();
  swap(other);
  return *this;
}

template < typename Key, typename Value, typename Compare >
void mihalchenko::AVLTree< Key, Value, Compare >::insert(const pair_t &pair)
{
  insert(pair.first, pair.second);
}

template < typename Key, typename Value, typename Compare >
void mihalchenko::AVLTree< Key, Value, Compare >::insert(const Key &key, const Value &value)
{
  insertNode(key, value, root_);
}

template < typename Key, typename Value, typename Compare >
size_t mihalchenko::AVLTree< Key, Value, Compare >::erase(const Key &key)
{
  if (find(key) == end())
  {
    return 0;
  }
  eraseNode(key);
  return 0;
}

template< typename Key, typename Value, typename Compare >
void mihalchenko::AVLTree< Key, Value, Compare >::erase(Iterator pos)
{
  if (pos != end())
  {
    Key key = pos.constIter_.node_->pairOfKeyVal_.first;
    eraseNode(key);
  }
}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::Iterator
  mihalchenko::AVLTree< Key, Value, Compare >::find(const Key &key)
{
  return findNode(key, root_);
}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::ConstIterator
  mihalchenko::AVLTree< Key, Value, Compare >::find(const Key &key) const
{
  return findNode(key, root_);
}

template < typename Key, typename Value, typename Compare >
Value &mihalchenko::AVLTree< Key, Value, Compare >::at(const Key &key)
{
  if (find(key) == end())
  {
    throw std::out_of_range("This element doesn't exist\n");
  }
  return (*find(key)).second;
}

template < typename Key, typename Value, typename Compare >
const Value &mihalchenko::AVLTree< Key, Value, Compare >::at(const Key &key) const
{
  if (find(key) == end())
  {
    throw std::out_of_range("This element doesn't exist\n");
  }
  return (*find(key)).second;
}

template < typename Key, typename Value, typename Compare >
Value &mihalchenko::AVLTree< Key, Value, Compare >::operator[](const Key &key)
{
  if (find(key) == end())
  {
    insert(key, Value());
  }
  return (*find(key)).second;
}

template < typename Key, typename Value, typename Compare >
const Value &mihalchenko::AVLTree< Key, Value, Compare >::operator[](const Key &key) const
{
  if (find(key) == end())
  {
    insert(key, Value());
  }
  return (*find(key)).second;
}

template < typename Key, typename Value, typename Compare >
void mihalchenko::AVLTree< Key, Value, Compare >::clear()
{
  clear(root_);
}

template < typename Key, typename Value, typename Compare >
void mihalchenko::AVLTree< Key, Value, Compare >::swap(AVLTree &other) noexcept
{
  std::swap(root_, other.root_);
}

template < typename Key, typename Value, typename Compare >
bool mihalchenko::AVLTree< Key, Value, Compare >::empty() const noexcept
{
  return root_ == nullptr;
}

template < typename Key, typename Value, typename Compare >
size_t mihalchenko::AVLTree< Key, Value, Compare >::getSize() const noexcept
{
  return size_;
}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::Iterator
  mihalchenko::AVLTree< Key, Value, Compare >::begin() noexcept
{
  if (empty())
  {
    return cend();
  }
  Node *temp = root_;
  while (temp->left_ != nullptr)
  {
    temp = temp->left_;
  }
  return Iterator(ConstIterator(temp, root_));
}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::Iterator
  mihalchenko::AVLTree< Key, Value, Compare >::end() noexcept
{
  return ConstIterator(nullptr, root_);
}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::ConstIterator
  mihalchenko::AVLTree< Key, Value, Compare >::cbegin() const noexcept
{
  if (empty())
  {
    return cend();
  }
  Node *temp = root_;
  while (temp->left != nullptr)
  {
    temp = temp->left;
  }
  return ConstIterator(temp, root_);
}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::ConstIterator
  mihalchenko::AVLTree< Key, Value, Compare >::cend() const noexcept
{
  return ConstIterator(nullptr, root_);
}

template < typename Key, typename Value, typename Compare >
int mihalchenko::AVLTree< Key, Value, Compare >::calcHeight(Node *node)
{
  if ((root_ == nullptr) || (node == nullptr))
  {
    return 0;
  }
  int weightLeftNode = (node->left_) ? calcHeight(node->left_) : 0;
  int weightRightNode = (node->right_) ? calcHeight(node->right_) : 0;
  int temp = (weightRightNode > weightLeftNode) ? weightRightNode - weightLeftNode + 1 : weightLeftNode - weightRightNode + 1;
  node->height_ = temp;
  return temp;
}

template < typename Key, typename Value, typename Compare >
void mihalchenko::AVLTree< Key, Value, Compare >::balancingTree(Node *node)
{
  Node *temp = node;
  while (temp)
  {
    int finalWeight = (temp) ? calcHeight(temp->right_) - calcHeight(temp->left_) : 0;
    if (std::abs(finalWeight) >= 2)
    {
      if ((temp->right_) && (temp->right_->height_ == 2) && (finalWeight < 0))
      {
        rightleftSpin(temp->right_);
      }
      else if ((temp->left_) && (temp->left_->height_ == 2) && (finalWeight > 0))
      {
        leftrightSpin(temp->left_);
      }
      else if ((temp->right_) && (temp->right_->height_ == 1) && (finalWeight < 0))
      {
        rightSpin(temp);
      }
      else if ((temp->left_) && (temp->left_->height_ == 2) && (finalWeight > 0))
      {
        leftSpin(temp);
      }
    }
    temp = temp->previous_;
  }
  return;
}

template < typename Key, typename Value, typename Compare >
void mihalchenko::AVLTree< Key, Value, Compare >::leftSpin(Node *nodeP)
{
  Node *nodeQ = nodeP->left_;
  if ((nodeQ->left_) && (nodeQ->right_))
  {
    if (nodeQ->right_->height_ - nodeQ->left_->height_ >= 2)
    {
      nodeP->previous_ = nodeQ;
      nodeP->left_ = nodeQ->right_;
      nodeQ->previous_ = nullptr;
      nodeQ->right_ = nodeP;
    }
  }
  else
  {
    nodeP->previous_ = nodeQ;
    nodeP->left_ = nullptr;
    nodeQ->previous_ = nullptr;
    nodeQ->right_ = nodeP;
  }
  if (nodeP == root_)
  {
    root_ = nodeQ;
  }
}

template < typename Key, typename Value, typename Compare >
void mihalchenko::AVLTree< Key, Value, Compare >::rightSpin(Node *nodeP)
{
  Node *nodeQ = nodeP->right_;
  if ((nodeQ->left_) && (nodeQ->right_))
  {
    if (nodeQ->left_->height_ - nodeQ->right_->height_ >= 2)
    {
      nodeP->previous_ = nodeQ;
      nodeP->right_ = nodeQ->left_;
      nodeQ->previous_ = nullptr;
      nodeQ->left_ = nodeP;
    }
  }
  else
  {
    nodeP->previous_ = nodeQ;
    nodeP->right_ = nullptr;
    nodeQ->previous_ = nullptr;
    nodeQ->left_ = nodeP;
  }
  if (nodeP == root_)
  {
    root_ = nodeQ;
  }
}

template < typename Key, typename Value, typename Compare >
void mihalchenko::AVLTree< Key, Value, Compare >::leftrightSpin(Node *nodeP)
{
  leftSpin(nodeP->left_);
  rightSpin(nodeP);
}

template < typename Key, typename Value, typename Compare >
void mihalchenko::AVLTree< Key, Value, Compare >::rightleftSpin(Node *nodeP)
{
  rightSpin(nodeP->right_);
  leftSpin(nodeP);
}

template < typename Key, typename Value, typename Compare >
int mihalchenko::AVLTree< Key, Value, Compare >::getHeight(Node *node)
{
  return (node) ? node->height_ : 0;
}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::Node
  *mihalchenko::AVLTree< Key, Value, Compare >::getRoot()
{
  Node *temp = this;
  while (temp->previous_ != root_)
  {
    temp = temp->previous_;
  }
  return temp->previous_;
}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::Node
  const *mihalchenko::AVLTree< Key, Value, Compare >::getRoot() const
{
  Node *temp = this;
  while (temp->previous_ != root_)
  {
    temp = temp->previous_;
  }
  return temp->previous_;
}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::Node
  *mihalchenko::AVLTree< Key, Value, Compare >::copyTree(Node *node, Node *previous)
{
  if (node == nullptr)
  {
    return nullptr;
  }
  Node *newnode = new Node(node->pairOfKeyVal_.first, node->pairOfKeyVal_.second, node->height_, nullptr, nullptr, previous);
  newnode->left_ = copyTree(node->left_, newnode);
  newnode->right_ = copyTree(node->right_, newnode);
  return newnode;
}

template < typename Key, typename Value, typename Compare >
mihalchenko::AVLTree< Key, Value, Compare >::ConstIterator::ConstIterator()
{
  node_ = nullptr;
  root_ = nullptr;
}

template < typename Key, typename Value, typename Compare >
mihalchenko::AVLTree< Key, Value, Compare >::ConstIterator::ConstIterator(Node *node, Node *root)
{
  node_ = node;
  root_ = root;
}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::ConstIterator
  &mihalchenko::AVLTree< Key, Value, Compare >::ConstIterator::operator++()
{
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
    Node *tempNode = node_->previous_;
    while (tempNode && node_ == tempNode->right_)
    {
      node_ = tempNode;
      tempNode = node_->previous_;
    }
    node_ = tempNode;
  }
  return *this;
}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::ConstIterator
  mihalchenko::AVLTree< Key, Value, Compare >::ConstIterator::operator++(int)
{
  ConstIterator result(*this);
  ++(*this);
  return result;
}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::ConstIterator
  &mihalchenko::AVLTree< Key, Value, Compare >::ConstIterator::operator--()
{
  if (node_ == nullptr)
  {
    node_ = root_;
    while (node_->right_)
    {
      node_ = node_->right_;
    }
  }
  else
  {
    if (node_->left_)
    {
      node_ = node_->left_;
      while (node_->right_)
      {
        node_ = node_->right_;
      }
    }
    else
    {
      Node *tempNode = node_->previous_;
      while (tempNode && node_ == tempNode->left_)
      {
        node_ = tempNode;
        tempNode = node_->previous_;
      }
      node_ = tempNode;
    }
  }
  return *this;
}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::ConstIterator
  mihalchenko::AVLTree< Key, Value, Compare >::ConstIterator::operator--(int)
{
  ConstIterator result(*this);
  --(*this);
  return result;
}

template < typename Key, typename Value, typename Compare >
const typename mihalchenko::AVLTree< Key, Value, Compare >::pair_t
  &mihalchenko::AVLTree< Key, Value, Compare >::ConstIterator::operator*() const
{
  return node_->pairOfKeyVal_;
}

template < typename Key, typename Value, typename Compare >
const typename mihalchenko::AVLTree< Key, Value, Compare >::pair_t
  *mihalchenko::AVLTree< Key, Value, Compare >::ConstIterator::operator->() const
{
  return std::addressof(node_->pairOfKeyVal_);
}

template < typename Key, typename Value, typename Compare >
bool mihalchenko::AVLTree< Key, Value, Compare >::ConstIterator::operator==(const ConstIterator &rhs) const
{
  return node_ == rhs.node_;
}

template < typename Key, typename Value, typename Compare >
bool mihalchenko::AVLTree< Key, Value, Compare >::ConstIterator::operator!=(const ConstIterator &rhs) const
{
  return !(*this == rhs);
}

template < typename Key, typename Value, typename Compare >
mihalchenko::AVLTree< Key, Value, Compare >::Iterator::Iterator() : constIter_(ConstIterator())
{}

template < typename Key, typename Value, typename Compare >
mihalchenko::AVLTree< Key, Value, Compare >::Iterator::Iterator(ConstIterator iter) : constIter_(iter)
{}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::Iterator
  &mihalchenko::AVLTree< Key, Value, Compare >::Iterator::operator++()
{
  ++constIter_;
  return *this;
}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::Iterator
  mihalchenko::AVLTree< Key, Value, Compare >::Iterator::operator++(int)
{
  Iterator result = constIter_;
  ++constIter_;
  return result;
}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::Iterator
  &mihalchenko::AVLTree< Key, Value, Compare >::Iterator::operator--()
{
  --constIter_;
  return *this;
}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::Iterator
  mihalchenko::AVLTree< Key, Value, Compare >::Iterator::operator--(int)
{
  Iterator result = constIter_;
  --constIter_;
  return result;
}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::pair_t
  &mihalchenko::AVLTree< Key, Value, Compare >::Iterator::operator*()
{
  return constIter_.node_->pairOfKeyVal_;
}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::pair_t
  *mihalchenko::AVLTree< Key, Value, Compare >::Iterator::operator->()
{
  return std::addressof(constIter_.node_->pairOfKeyVal_);
}

template < typename Key, typename Value, typename Compare >
bool mihalchenko::AVLTree< Key, Value, Compare >::Iterator::operator!=(const Iterator &rhs) const
{
  return !(rhs == *this);
}

template < typename Key, typename Value, typename Compare >
bool mihalchenko::AVLTree< Key, Value, Compare >::Iterator::operator==(const Iterator &rhs) const
{
  return constIter_ == rhs.constIter_;
}

template <typename Key, typename Value, typename Compare>
typename mihalchenko::AVLTree< Key, Value, Compare >::Iterator
  mihalchenko::AVLTree< Key, Value, Compare >::findNode(const Key &key, Node *node)
{
  if (node == nullptr)
  {
    return end();
  }
  if (node->pairOfKeyVal_.first == key)
  {
    return Iterator(ConstIterator(node, root_));
  }
  if (key < node->pairOfKeyVal_.first)
  {
    return findNode(key, node->left_);
  }
  if (key > node->pairOfKeyVal_.first)
  {
    return findNode(key, node->right_);
  }
  return end();
}

template < typename Key, typename Value, typename Compare >
typename mihalchenko::AVLTree< Key, Value, Compare >::ConstIterator
  mihalchenko::AVLTree< Key, Value, Compare >::findNode(const Key &key, Node *node) const
{
  Compare compare;
  if (node == nullptr)
  {
    return end();
  }
  if (node->pairOfKeyVal_.first == key)
  {
    return ConstIterator(node, root_);
  }
  else if (compare(key, node->pairOfKeyVal_.first))
  {
    return findNode(key, node->left_);
  }
  else if (!compare(key, node->pairOfKeyVal_.first))
  {
    return findNode(key, node->right_);
  }
  return end();
}

template < typename Key, typename Value, typename Compare >
void mihalchenko::AVLTree< Key, Value, Compare >::clear(Node *node)
{
  if (node == nullptr)
  {
    return;
  }
  clear(node->left_);
  clear(node->right_);
  node->left_ = nullptr;
  node->right_ = nullptr;
  node->previous_ = nullptr;
  if (node == root_)
  {
    root_ = nullptr;
  }
  delete node;
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F mihalchenko::AVLTree< Key, Value, Compare >::constTraverseLR(F stackFunc) const
{
  Stack< Node * > stack;
  Node * temp = root_;
  while ((temp != nullptr) || (!stack.isEmpty()))
  {
    while (temp != nullptr)
    {
      stack.push(temp);
      temp = temp->left_;
    }
    temp = stack.getElem();
    // stack.pop();
    stackFunc(temp->elem_);
    temp = temp->right_;
    stack.pop();
  }
  return stackFunc;
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F mihalchenko::AVLTree< Key, Value, Compare >::traverseLR(F stackFunc)
{
  Stack< Node * > stack;
  Node * temp = root_;
  while ((temp != nullptr) || (!stack.isEmpty()))
  {
    while (temp != nullptr)
    {
      stack.push(temp);
      temp = temp->left_;
    }
    temp = stack.getElem();
    // stack.pop();
    stackFunc(temp->pairOfKeyVal_);
    temp = temp->right_;
    stack.pop();
  }
  return stackFunc;
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F mihalchenko::AVLTree< Key, Value, Compare >::constTraverseRL(F stackFunc) const
{
  Stack< Node * > stack;
  Node * temp = root_;
  while ((temp != nullptr) || (!stack.isEmpty()))
  {
    while (temp != nullptr)
    {
      stack.push(temp);
      temp = temp->right_;
    }
    temp = stack.getElem();
    // stack.pop();
    stackFunc(temp->data_);
    temp = temp->left_;
    stack.pop();
  }
  return stackFunc;
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F mihalchenko::AVLTree< Key, Value, Compare >::traverseRL(F stackFunc)
{
  Stack< Node * > stack;
  Node * temp = root_;
  while ((temp != nullptr) || (!stack.isEmpty()))
  {
    while (temp != nullptr)
    {
      stack.push(temp);
      temp = temp->right_;
    }
    temp = stack.getElem();
    // stack.pop();
    stackFunc(temp->pairOfKeyVal_);
    temp = temp->left_;
    stack.pop();
  }
  return stackFunc;
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F mihalchenko::AVLTree< Key, Value, Compare >::constTraverseBreadth(F queueFunc) const
{
  if (empty())
  {
    return queueFunc;
  }
  Queue< Node * > queueBreadfh;
  queueBreadfh.push(root_);

  while (!queueBreadfh.isEmpty())
  {
    Node * node = queueBreadfh.getElem();
    queueFunc(node->data);
    queueBreadfh.pop();
    if (node->left != nullptr)
    {
      queueBreadfh.push(node->left);
    }
    if (node->right != nullptr)
    {
      queueBreadfh.push(node->right);
    }
  }
  return queueFunc;
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F mihalchenko::AVLTree< Key, Value, Compare >::traverseBreadth(F queueFunc)
{
  if (empty())
  {
    return queueFunc;
  }
  Queue< Node * > queueBreadfh;
  queueBreadfh.push(root_);

  while (!queueBreadfh.isEmpty())
  {
    Node * node = queueBreadfh.getElem();
    queueFunc(node->pairOfKeyVal_);
    queueBreadfh.pop();
    if (node->left_ != nullptr)
    {
      queueBreadfh.push(node->left_);
    }
    if (node->right_ != nullptr)
    {
      queueBreadfh.push(node->right_);
    }
  }
  return queueFunc;
}

#endif
