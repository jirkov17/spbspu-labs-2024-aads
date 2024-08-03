#ifndef TREE_HPP
#define TREE_HPP
#include <utility>
#include <stdexcept>
#include <functional>
#include <stack.hpp>
#include <queue.hpp>

namespace zheleznyakov
{
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class Tree
  {
  public:
    class Iterator;
    class ConstIterator;

    class LnRIterator;
    class ConstLnRIterator;
    class RnLIterator;
    class ConstRnLIterator;

    using data_t = typename std::pair< Key, Value >;

    Tree();
    Tree(const Tree &);
    Tree(Tree &&) noexcept;
    ~Tree();

    Tree & operator=(const Tree &);

    size_t getSize() const;
    bool empty() const noexcept;
    size_t count(const Key &) const;

    Value at(const Key &);
    void insert(const Key &, const Value &);
    void erase(const Key &);

    Value & operator[](const Key &);
    const Value & operator[](const Key &) const;

    void swap(Tree &) noexcept;
    void clear();

    Iterator begin() noexcept;
    Iterator end() noexcept;

    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;

    Iterator find(const Key &);
    ConstIterator find(const Key &) const;

    std::pair< Iterator, Iterator > equalRange(const Key &, const Key &);

    template< typename Functor >
    Functor ctraverseLnR(Functor f) const;
    template< typename Functor >
    Functor ctraverseRnL(Functor f) const;
    template< typename Functor >
    Functor ctraverseBreadth(Functor f) const;
    template< typename Functor >
    Functor traverseLnR(Functor f);
    template< typename Functor >
    Functor traverseRnL(Functor f);
    template< typename Functor >
    Functor traverseBreadth(Functor f);

  private:
    struct Node
    {
      Node(
        Node * newParent = nullptr,
        Node * newLeft = nullptr,
        Node * newRight = nullptr
      ):
        parent(newParent),
        left(newLeft),
        right(newRight),
        height(1)
      {}
      ~Node() = default;

      data_t data;
      Node * parent;
      Node * left;
      Node * right;
      size_t height;
    };

    Node * root_;

    size_t size(Node *) const;
    void clear(Node *);
    size_t getHeight(Node *);
    int getBalance(Node *);
    Node * rotateRight(Node *);
    Node * rotateLeft(Node *);
    Node * balance(Node *);
    Node * eraseNode(Node *, const Key &);
    Node * minValueNode(Node *);
    Iterator find(const Key &, const Key &);
    ConstIterator find(const Key &, const Key &) const;
    std::pair< Iterator, Iterator > equalRangeSearch(Node *, const Key &, const Key &);
  };
}

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::Tree():
  root_{nullptr}
{}

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::Tree(const Tree & other):
  root_(nullptr)
{
  Node * node_ = other.root_;
  while (node_ != nullptr && node_->left != nullptr)
  {
    node_ = node_->left;
  }
  while (node_ != nullptr)
  {
    insert(node_->data.first, node_->data.second);
    if (node_->right != nullptr)
    {
      node_ = node_->right;
      while (node_->left != nullptr)
      {
        node_ = node_->left;
      }
    }
    else
    {
      while (node_->parent != nullptr && node_ == node_->parent->right)
      {
        node_ = node_->parent;
      }
      node_ = node_->parent;
    }
  }
}

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::Tree(Tree&& other) noexcept:
  root_(other.root_)
{
  other.root_ = nullptr;
}

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare > & zheleznyakov::Tree< Key, Value, Compare >::operator=(const Tree & other)
{
  if (&other != this)
  {
    clear(root_);
    Node * node_ = other.root_;
    while (node_ != nullptr)
    {
      insert(node_->data.first, node_->data.second);
      if (node_->right != nullptr)
      {
        node_ = node_->right;
        while (node_->left != nullptr)
        {
          node_ = node_->left;
        }
      }
      else
      {
        while (node_->parent != nullptr && node_ == node_->parent->right)
        {
          node_ = node_->parent;
        }
        node_ = node_->parent;
      }
    }
  }
  return *this;
}

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::~Tree()
{
  clear(root_);
}

template < typename Key, typename Value, typename Compare >
class zheleznyakov::Tree< Key, Value, Compare >::Iterator
{
friend class ConstIterator;
public:
  Iterator();
  Iterator(Node *);
  Iterator(const Iterator&) = default;
  ~Iterator() = default;

  Iterator & operator++();
  Iterator operator++(int);
  Iterator & operator--();
  Iterator operator--(int);

  bool operator==(const Iterator &) const;
  bool operator!=(const Iterator &) const;

  data_t & operator*();
  data_t * operator->();
private:
  Node * currentIter_;
};

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::Iterator::Iterator():
  currentIter_(nullptr)
{}

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::Iterator::Iterator(Node * newCurrent):
  currentIter_(newCurrent)
{}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::Iterator & zheleznyakov::Tree< Key, Value, Compare >::Iterator::operator++()
{
  if (currentIter_ == nullptr)
  {
    return *this;
  }
  if (currentIter_->right != nullptr)
  {
    currentIter_ = currentIter_->right;
    while (currentIter_->left != nullptr)
    {
      currentIter_ = currentIter_->left;
    }
  } else {
    Node * parent = currentIter_->parent;
    while (parent != nullptr && currentIter_ == parent->right)
    {
      currentIter_ = parent;
      parent = parent->parent;
    }
    currentIter_ = parent;
  }
  return *this;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::Iterator zheleznyakov::Tree< Key, Value, Compare >::Iterator::operator++(int)
{
  Iterator temp = *this;
  ++(*this);
  return temp;
}

template <typename Key, typename Value, typename Compare>
typename zheleznyakov::Tree<Key, Value, Compare>::Iterator& zheleznyakov::Tree<Key, Value, Compare>::Iterator::operator--()
{
  if (currentIter_ == nullptr)
  {
    return *this;
  }

  if (currentIter_->left != nullptr)
  {
    currentIter_ = currentIter_->left;
    while (currentIter_->right != nullptr)
    {
      currentIter_ = currentIter_->right;
    }
  }
  else
  {
    Node * parent = currentIter_->parent;
    while (parent != nullptr && currentIter_ == parent->left)
    {
      currentIter_ = parent;
      parent = parent->parent;
    }
    currentIter_ = parent;
  }

  return *this;
}

template <typename Key, typename Value, typename Compare>
typename zheleznyakov::Tree<Key, Value, Compare>::Iterator zheleznyakov::Tree<Key, Value, Compare>::Iterator::operator--(int)
{
  Iterator temp = *this;
  --(*this);
  return temp;
}

template < typename Key, typename Value, typename Compare >
bool zheleznyakov::Tree< Key, Value, Compare >::Iterator::operator==(const Iterator &other) const
{
  return currentIter_ == other.currentIter_;
}

template < typename Key, typename Value, typename Compare >
bool zheleznyakov::Tree< Key, Value, Compare >::Iterator::operator!=(const Iterator &other) const
{
  return currentIter_ != other.currentIter_;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::data_t & zheleznyakov::Tree< Key, Value, Compare >::Iterator::operator*()
{
  return currentIter_->data;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::data_t * zheleznyakov::Tree< Key, Value, Compare >::Iterator::operator->()
{
  return &currentIter_->data;
}

template < typename Key, typename Value, typename Compare >
class zheleznyakov::Tree< Key, Value, Compare >::ConstIterator
{
public:
  ConstIterator();
  ConstIterator(Iterator);
  ConstIterator(const ConstIterator&) = default;
  ~ConstIterator() = default;

  ConstIterator & operator++();
  ConstIterator operator++(int);
  ConstIterator & operator--();
  ConstIterator operator--(int);

  bool operator==(const ConstIterator &) const;
  bool operator!=(const ConstIterator &) const;

  data_t & operator*();
  data_t * operator->();
private:
  Iterator iter_;
};

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::ConstIterator::ConstIterator():
  iter_(Iterator())
{}

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::ConstIterator::ConstIterator(Iterator newIterator):
  iter_(newIterator)
{}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::ConstIterator & zheleznyakov::Tree< Key, Value, Compare >::ConstIterator::operator++()
{
  ++iter_;
  return *this;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::ConstIterator zheleznyakov::Tree< Key, Value, Compare >::ConstIterator::operator++(int)
{
  ConstIterator temp(iter_);
  ++iter_;
  return temp;
}

template <typename Key, typename Value, typename Compare>
typename zheleznyakov::Tree<Key, Value, Compare>::ConstIterator& zheleznyakov::Tree<Key, Value, Compare>::ConstIterator::operator--()
{
  --iter_;
  return *this;
}

template <typename Key, typename Value, typename Compare>
typename zheleznyakov::Tree<Key, Value, Compare>::ConstIterator zheleznyakov::Tree<Key, Value, Compare>::ConstIterator::operator--(int)
{
  ConstIterator temp(iter_);
  --iter_;
  return *this;
}

template < typename Key, typename Value, typename Compare >
bool zheleznyakov::Tree< Key, Value, Compare >::ConstIterator::operator==(const ConstIterator &other) const
{
  return iter_.currentIter_ == other.iter_.currentIter_;
}

template < typename Key, typename Value, typename Compare >
bool zheleznyakov::Tree< Key, Value, Compare >::ConstIterator::operator!=(const ConstIterator &other) const
{
  return !(other == *this);
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::data_t & zheleznyakov::Tree< Key, Value, Compare >::ConstIterator::operator*()
{
  return *iter_;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::data_t * zheleznyakov::Tree< Key, Value, Compare >::ConstIterator::operator->()
{
  return &iter_.currentIter_->data;
}

template < typename Key, typename Value, typename Compare >
size_t zheleznyakov::Tree< Key, Value, Compare >::size(Node* node) const
{
  return node != nullptr ? 1 + size(node->left) + size(node->right) : 0;
}

template < typename Key, typename Value, typename Compare >
size_t zheleznyakov::Tree< Key, Value, Compare >::getSize() const
{
  return size(root_);
}

template < typename Key, typename Value, typename Compare >
bool zheleznyakov::Tree< Key, Value, Compare >::empty() const noexcept
{
  return root_ == nullptr;
}

template < typename Key, typename Value, typename Compare >
size_t zheleznyakov::Tree< Key, Value, Compare >::count(const Key & key) const
{
  return find(key) != cend() ? 1 : 0;
}

template < typename Key, typename Value, typename Compare >
Value& zheleznyakov::Tree< Key, Value, Compare >::operator[](const Key& key)
{
  Node* current = root_;
  Node* parent = nullptr;

  while (current != nullptr)
  {
    parent = current;
    if (key == current->data.first)
    {
      return current->data.second;
    }
    else if (key < current->data.first)
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }

  current = new Node(parent, nullptr, nullptr);
  current->data.first = key;
  Value val;
  current->data.second = val;
  if (parent == nullptr)
  {
      root_ = current;
  }
  else if (key < parent->data.first)
  {
      parent->left = current;
  }
  else
  {
      parent->right = current;
  }

  return current->data.second;
}

template < typename Key, typename Value, typename Compare >
const Value & zheleznyakov::Tree< Key, Value, Compare >::operator[](const Key& key) const
{
  Node * current = root_;
  while (current != nullptr)
  {
    if (key == current->data.first)
    {
      return current->data.second;
    }
    else if (key < current->data.first)
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }
  throw std::out_of_range("No such key");
}

template < typename Key, typename Value, typename Compare >
Value zheleznyakov::Tree< Key, Value, Compare >::at(const Key & k)
{
  Node * current = root_;
  Compare cmp;

  while (current != nullptr)
  {
    if (cmp(current->data.first, k))
    {
      current = current->right;
    }
    else if (cmp(k, current->data.first))
    {
      current = current->left;
    }
    else
    {
      return current->data.second;
    }
  }
  throw std::out_of_range("No such key");
}

template < typename Key, typename Value, typename Compare >
void zheleznyakov::Tree< Key, Value, Compare >::insert(const Key& k, const Value& v)
{
  Node* new_node = new Node();
  new_node->data = std::make_pair(k, v);

  Compare cmp;

  if (root_ == nullptr)
  {
    root_ = new_node;
    return;
  }

  Node* current = root_;
  Node* parent = nullptr;

  while (current != nullptr)
  {
    parent = current;
    if (cmp(k, current->data.first))
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }

  new_node->parent = parent;
  if (cmp(k, parent->data.first))
  {
    parent->left = new_node;
  }
  else
  {
    parent->right = new_node;
  }

  root_ = balance(root_);
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::Iterator zheleznyakov::Tree< Key, Value, Compare >::find(const Key & key)
{
  Node * current = root_;
  Compare cmp;

  while (current != nullptr)
  {
    if (cmp(current->data.first, key))
    {
      current = current->right;
    }
    else if (cmp(key, current->data.first))
    {
      current = current->left;
    }
    else
    {
      return Iterator(current);
    }
  }

  return Iterator(nullptr);
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::ConstIterator zheleznyakov::Tree< Key, Value, Compare >::find(const Key & key) const
{
  Node * current = root_;
  Compare cmp;

  while (current != nullptr)
  {
    if (cmp(current->data.first, key))
    {
      current = current->right;
    }
    else if (cmp(key, current->data.first))
    {
      current = current->left;
    }
    else
    {
      return ConstIterator(current);
    }
  }

  return ConstIterator(nullptr);
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::Iterator
zheleznyakov::Tree< Key, Value, Compare >::find(const Key & low, const Key & high)
{
  Node * current = root_;
  while (current != nullptr)
  {
    if (low < current->data.first && high > current->data.first)
    {
      return Iterator(current);
    }
    else if (high <= current->data.first)
    {
      return Iterator(nullptr);
    }
    else
    {
      current = current->right;
    }
  }
  return end();
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::ConstIterator
zheleznyakov::Tree< Key, Value, Compare >::find(const Key & low, const Key & high) const
{
  Node * current = root_;
  while (current != nullptr)
  {
    if (low < current->data.first && high > current->data.first)
    {
      return ConstIterator(current);
    }
    else if (high <= current->data.first)
    {
      return end();
    }
    else
    {
      current = current->right;
    }
  }
  return end();
}

template < typename Key, typename Value, typename Compare >
std::pair< typename zheleznyakov::Tree< Key, Value, Compare >::Iterator, typename zheleznyakov::Tree< Key, Value, Compare >::Iterator >
zheleznyakov::Tree< Key, Value, Compare >::equalRangeSearch(Node * node, const Key & low, const Key & high)
{
  if (node == nullptr)
  {
    return std::make_pair(end(), end());
  }

  if (low <= node->data.first && high >= node->data.first)
  {
    if (node->left != nullptr)
    {
      auto leftResult = equalRangeSearch(node->left, low, high);
      return std::make_pair(leftResult.second, Iterator(node));
    }
    else
    {
      return std::make_pair(Iterator(node), end());
    }
  }
  else if (high <= node->data.first)
  {
    if (node->left != nullptr)
    {
      return equalRangeSearch(node->left, low, high);
    }
    else
    {
      return std::make_pair(end(), end());
    }
  }
  else
  {
    return equalRangeSearch(node->right, low, high);
  }
}

template < typename Key, typename Value, typename Compare >
std::pair< typename zheleznyakov::Tree< Key, Value, Compare >::Iterator, typename zheleznyakov::Tree< Key, Value, Compare >::Iterator >
zheleznyakov::Tree<Key, Value, Compare>::equalRange(const Key & low, const Key & high)
{
  return equalRangeSearch(root_, low, high);
}

template < typename Key, typename Value, typename Compare >
void zheleznyakov::Tree< Key, Value, Compare>::clear()
{
  if (!empty())
  {
    clear(root_);
  }
}

template < typename Key, typename Value, typename Compare >
void zheleznyakov::Tree< Key, Value, Compare >::clear(Node * node)
{
  if (!node)
  {
    return;
  }
  clear(node->left);
  clear(node->right);
  delete node;
}

template < typename Key, typename Value, typename Compare >
size_t zheleznyakov::Tree< Key, Value, Compare >::getHeight(Node* node)
{
  return node == nullptr ? 0 : node->height;
}

template < typename Key, typename Value, typename Compare >
int zheleznyakov::Tree< Key, Value, Compare >::getBalance(Node* node)
{
  return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::Node * zheleznyakov::Tree< Key, Value, Compare >::rotateRight(Node * y)
{
  Node* x = y->left;
  Node* T = x->right;
  x->right = y;
  y->left = T;
  y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
  x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
  return x;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::Node * zheleznyakov::Tree< Key, Value, Compare >::rotateLeft(Node * x)
{
  Node* y = x->right;
  Node* T = y->left;
  y->left = x;
  x->right = T;
  x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
  y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
  return y;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::Node* zheleznyakov::Tree< Key, Value, Compare >::balance(Node * node)
{
  if (node == nullptr)
  {
    return node;
  }
  int balance = getBalance(node);
  if (balance > 1 && getBalance(node->left) >= 0)
  {
    return rotateRight(node);
  }
  if (balance < -1 && getBalance(node->right) <= 0)
  {
    return rotateLeft(node);
  }
  if (balance > 1 && getBalance(node->left) < 0)
  {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }
  if (balance < -1 && getBalance(node->right) > 0)
  {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }
  return node;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::Iterator zheleznyakov::Tree< Key, Value, Compare >::begin() noexcept
{
  Node* current = root_;
  while (current != nullptr && current->left != nullptr)
  {
    current = current->left;
  }
  return Iterator(current);
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::Iterator zheleznyakov::Tree< Key, Value, Compare >::end() noexcept
{
  return Iterator(nullptr);
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::ConstIterator zheleznyakov::Tree< Key, Value, Compare >::cbegin() const noexcept
{
  Node* current = root_;
  while (current != nullptr && current->left != nullptr)
  {
    current = current->left;
  }
  return Iterator(current);
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::ConstIterator zheleznyakov::Tree< Key, Value, Compare >::cend() const noexcept
{
  return Iterator(nullptr);
}

template < typename Key, typename Value, typename Compare >
void zheleznyakov::Tree< Key, Value, Compare >::swap(Tree & other) noexcept
{
  Node* temp = root_;
  root_ = other.root_;
  other.root_ = temp;
}

template < typename Key, typename Value, typename Compare >
void zheleznyakov::Tree<Key, Value, Compare>::erase(const Key & key)
{
  root_ = eraseNode(root_, key);
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree<Key, Value, Compare>::Node * zheleznyakov::Tree<Key, Value, Compare>::eraseNode(Node* node, const Key& key)
{
  if (node == nullptr)
  {
    return node;
  }

  if (key < node->data.first)
  {
    node->left = eraseNode(node->left, key);
  }
  else if (key > node->data.first)
  {
    node->right = eraseNode(node->right, key);
  }
  else
  {
    if (node->left == nullptr)
    {
      Node* temp = node->right;
      delete node;
      return temp;
    }
    else if (node->right == nullptr)
    {
      Node* temp = node->left;
      delete node;
      return temp;
    }

    Node* temp = minValueNode(node->right);
    node->data = temp->data;
    node->right = eraseNode(node->right, temp->data.first);
  }

  return node;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree<Key, Value, Compare>::Node * zheleznyakov::Tree<Key, Value, Compare>::minValueNode(Node * node)
{
  Node * current = node;
  while (current->left != nullptr)
  {
    current = current->left;
  }
  return current;
}

template< typename Key, typename Value, typename Compare >
template< typename Functor >
Functor zheleznyakov::Tree< Key, Value, Compare >::ctraverseLnR(Functor f) const
{
  Stack< const Node * > nodesStack;
  const Node * current = root_;
  while (current != nullptr || !nodesStack.empty())
  {
    while (current != nullptr)
    {
      nodesStack.push(current);
      current = current->left;
    }
    current = nodesStack.top();
    nodesStack.pop();
    f(current->data);
    current = current->right;
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
template< typename Functor >
Functor zheleznyakov::Tree< Key, Value, Compare >::ctraverseRnL(Functor f) const
{
  Stack< const Node * > nodesStack;
  const Node * current = root_;
  while (current != nullptr || !nodesStack.empty())
  {
    while (current != nullptr)
    {
      nodesStack.push(current);
      current = current->right;
    }
    current = nodesStack.top();
    nodesStack.pop();
    f(current->data);
    current = current->left;
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
template< typename Functor >
Functor zheleznyakov::Tree< Key, Value, Compare >::traverseLnR(Functor f)
{
  Stack< Node * > nodesStack;
  Node * current = root_;
  while (current != nullptr || !nodesStack.empty())
  {
    while (current != nullptr)
    {
      nodesStack.push(current);
      current = current->left;
    }
    current = nodesStack.top();
    nodesStack.pop();
    f(current->data);
    current = current->right;
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
template< typename Functor >
Functor zheleznyakov::Tree< Key, Value, Compare >::traverseRnL(Functor f)
{
  Stack< Node * > nodesStack;
  Node * current = root_;
  while (current != nullptr || !nodesStack.empty())
  {
    while (current != nullptr)
    {
      nodesStack.push(current);
      current = current->right;
    }
    current = nodesStack.top();
    nodesStack.pop();
    f(current->data);
    current = current->left;
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
template< typename Functor >
Functor zheleznyakov::Tree< Key, Value, Compare >::traverseBreadth(Functor f)
{
  if (!root_)
  {
    return f;
  }

  Queue< Node * > q;
  q.push(root_);
  while (!q.empty()) {
    Node* current = q.front();
    q.pop();
    f(current->data);
    if (current->left)
    {
      q.push(current->left);
    }
    if (current->right)
    {
      q.push(current->right);
    }
  }

  return f;
}

template< typename Key, typename Value, typename Compare >
template< typename Functor >
Functor zheleznyakov::Tree< Key, Value, Compare >::ctraverseBreadth(Functor f) const
{
  if (!root_)
  {
    return f;
  }

  Queue< const Node * > q;
  q.push(root_);
  while (!q.empty())
  {
    const Node * current = q.front();
    q.pop();
    f(current->data);
    if (current->left)
    {
      q.push(current->left);
    }
    if (current->right)
    {
      q.push(current->right);
    }
  }

  return f;
}

template < typename Key, typename Value, typename Compare >
class zheleznyakov::Tree<Key, Value, Compare>::LnRIterator
{
  friend class Tree;
public:
  LnRIterator();
  LnRIterator(Node *);
  LnRIterator(const LnRIterator &) = default;
  ~LnRIterator() = default;

  LnRIterator & operator++();
  LnRIterator operator++(int);
  LnRIterator & operator--();
  LnRIterator operator--(int);

  bool operator==(const LnRIterator &) const;
  bool operator!=(const LnRIterator &) const;

  data_t & operator*();
  data_t * operator->();

private:
  Node * current_;
};

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::LnRIterator::LnRIterator():
  current_{nullptr}
{}

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::LnRIterator::LnRIterator(Node * newNode):
  current_{newNode}
{}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::LnRIterator &
zheleznyakov::Tree< Key, Value, Compare >::LnRIterator::operator++()
{
  if (current_ == nullptr)
  {
    return *this;
  }

  if (current_->right != nullptr)
  {
    current_ = current_->right;
    while (current_->left != nullptr)
    {
      current_ = current_->left;
    }
  }
  else
  {
    Node * prev = current_;
    current_ = current_->parent;
    while (current_ != nullptr && prev == current_->right)
    {
      prev = current_;
      current_ = current_->parent;
    }
  }

  return *this;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::LnRIterator
zheleznyakov::Tree< Key, Value, Compare >::LnRIterator::operator++(int)
{
  LnRIterator temp = *this;
  ++(*this);
  return temp;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::LnRIterator &
zheleznyakov::Tree< Key, Value, Compare >::LnRIterator::operator--()
{
  if (current_ == nullptr)
  {
    current_ = root_;
    while (current_->right != nullptr)
    {
      current_ = current_->right;
    }
  }
  else if (current_->left != nullptr)
  {
    current_ = current_->left;
    while (current_->right != nullptr)
    {
      current_ = current_->right;
    }
  }
  else
  {
    Node * prev = current_;
    current_ = current_->parent;
    while (current_ != nullptr && prev == current_->left)
    {
      prev = current_;
      current_ = current_->parent;
    }
  }

  return *this;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::LnRIterator
zheleznyakov::Tree< Key, Value, Compare >::LnRIterator::operator--(int)
{
  LnRIterator temp = *this;
  --(*this);
  return temp;
}

template < typename Key, typename Value, typename Compare >
bool zheleznyakov::Tree< Key, Value, Compare >::LnRIterator::operator==(const LnRIterator & other) const
{
  return current_ == other.current_;
}

template < typename Key, typename Value, typename Compare >
bool zheleznyakov::Tree< Key, Value, Compare >::LnRIterator::operator!=(const LnRIterator & other) const
{
  return !(*this == other);
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::data_t &
zheleznyakov::Tree< Key, Value, Compare >::LnRIterator::operator*()
{
  return current_->data;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::data_t *
zheleznyakov::Tree< Key, Value, Compare >::LnRIterator::operator->()
{
  return &(current_->data);
}

template < typename Key, typename Value, typename Compare >
class zheleznyakov::Tree<Key, Value, Compare>::ConstLnRIterator
{
  friend class Tree;
public:
  ConstLnRIterator();
  ConstLnRIterator(Iterator);
  ConstLnRIterator(const ConstLnRIterator &) = default;
  ~ConstLnRIterator() = default;

  ConstLnRIterator & operator++();
  ConstLnRIterator operator++(int);
  ConstLnRIterator & operator--();
  ConstLnRIterator operator--(int);

  bool operator==(const ConstLnRIterator &) const;
  bool operator!=(const ConstLnRIterator &) const;

  data_t & operator*();
  data_t * operator->();

private:
  LnRIterator iter_;
};

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::ConstLnRIterator::ConstLnRIterator():
  iter_{Iterator()}
{}

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::ConstLnRIterator::ConstLnRIterator(Iterator newIterator):
  iter_{newIterator}
{}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::ConstLnRIterator &
zheleznyakov::Tree< Key, Value, Compare >::ConstLnRIterator::operator++()
{
  ++iter_;
  return *this;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::ConstLnRIterator
zheleznyakov::Tree< Key, Value, Compare >::ConstLnRIterator::operator++(int)
{
  ConstIterator temp(iter_);
  ++iter_;
  return temp;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::ConstLnRIterator &
zheleznyakov::Tree< Key, Value, Compare >::ConstLnRIterator::operator--()
{
  --iter_;
  return *this;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::ConstLnRIterator
zheleznyakov::Tree< Key, Value, Compare >::ConstLnRIterator::operator--(int)
{
  ConstIterator temp(iter_);
  --(*this);
  return temp;
}

template < typename Key, typename Value, typename Compare >
bool zheleznyakov::Tree< Key, Value, Compare >::ConstLnRIterator::operator==(const ConstLnRIterator & other) const
{
  return iter_.currentIter_ == other.iter_.currentIter_;
}

template < typename Key, typename Value, typename Compare >
bool zheleznyakov::Tree< Key, Value, Compare >::ConstLnRIterator::operator!=(const ConstLnRIterator & other) const
{
  return !(other == *this);
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::data_t &
zheleznyakov::Tree< Key, Value, Compare >::ConstLnRIterator::operator*()
{
  return *iter_;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::data_t *
zheleznyakov::Tree< Key, Value, Compare >::ConstLnRIterator::operator->()
{
  return &iter_.currentIter_->data;
}

template < typename Key, typename Value, typename Compare >
class zheleznyakov::Tree<Key, Value, Compare>::RnLIterator
{
  friend class Tree;
public:
  RnLIterator();
  RnLIterator(Node *);
  RnLIterator(const RnLIterator &) = default;
  ~RnLIterator() = default;

  RnLIterator & operator++();
  RnLIterator operator++(int);
  RnLIterator & operator--();
  RnLIterator operator--(int);

  bool operator==(const RnLIterator &) const;
  bool operator!=(const RnLIterator &) const;

  data_t & operator*();
  data_t * operator->();

private:
  Node * current_;
};

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::RnLIterator::RnLIterator():
  current_{nullptr}
{}

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::RnLIterator::RnLIterator(Node * newNode):
  current_{newNode}
{}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::RnLIterator &
zheleznyakov::Tree< Key, Value, Compare >::RnLIterator::operator++()
{
  if (current_ == nullptr)
  {
    return *this;
  }

  if (current_->left != nullptr)
  {
    current_ = current_->left;
    while (current_->right != nullptr)
    {
      current_ = current_->right;
    }
  }
  else
  {
    Node *prev = current_;
    current_ = current_->parent;
    while (current_ != nullptr && prev == current_->left)
    {
      prev = current_;
      current_ = current_->parent;
    }
  }

  return *this;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::RnLIterator
zheleznyakov::Tree< Key, Value, Compare >::RnLIterator::operator++(int)
{
  RnLIterator temp = *this;
  ++(*this);
  return temp;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::RnLIterator &
zheleznyakov::Tree< Key, Value, Compare >::RnLIterator::operator--()
{
  if (current_ == nullptr)
  {
    current_ = root_;
    while (current_->right != nullptr)
    {
      current_ = current_->right;
    }
  }
  else if (current_->right != nullptr)
  {
    current_ = current_->right;
    while (current_->left != nullptr)
    {
      current_ = current_->left;
    }
  }
  else
  {
    Node *prev = current_;
    current_ = current_->parent;
    while (current_ != nullptr && prev == current_->right)
    {
      prev = current_;
      current_ = current_->parent;
    }
  }

  return *this;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::RnLIterator
zheleznyakov::Tree< Key, Value, Compare >::RnLIterator::operator--(int)
{
  RnLIterator temp = *this;
  --(*this);
  return temp;
}

template < typename Key, typename Value, typename Compare >
bool zheleznyakov::Tree< Key, Value, Compare >::RnLIterator::operator==(const RnLIterator & other) const
{
  return current_ == other.current_;
}

template < typename Key, typename Value, typename Compare >
bool zheleznyakov::Tree< Key, Value, Compare >::RnLIterator::operator!=(const RnLIterator & other) const
{
  return !(*this == other);
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::data_t &
zheleznyakov::Tree< Key, Value, Compare >::RnLIterator::operator*()
{
  return current_->data;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::data_t *
zheleznyakov::Tree< Key, Value, Compare >::RnLIterator::operator->()
{
  return &(current_->data);
}

template < typename Key, typename Value, typename Compare >
class zheleznyakov::Tree<Key, Value, Compare>::ConstRnLIterator
{
  friend class Tree;
public:
  ConstRnLIterator();
  ConstRnLIterator(Iterator);
  ConstRnLIterator(const ConstRnLIterator &) = default;
  ~ConstRnLIterator() = default;

  ConstRnLIterator & operator++();
  ConstRnLIterator operator++(int);
  ConstRnLIterator & operator--();
  ConstRnLIterator operator--(int);

  bool operator==(const ConstRnLIterator &) const;
  bool operator!=(const ConstRnLIterator &) const;

  data_t & operator*();
  data_t * operator->();

private:
  RnLIterator iter_;
};

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::ConstRnLIterator::ConstRnLIterator():
  iter_{Iterator()}
{}

template < typename Key, typename Value, typename Compare >
zheleznyakov::Tree< Key, Value, Compare >::ConstRnLIterator::ConstRnLIterator(Iterator newIterator):
  iter_{newIterator}
{}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::ConstRnLIterator &
zheleznyakov::Tree< Key, Value, Compare >::ConstRnLIterator::operator++()
{
  ++iter_;
  return *this;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::ConstRnLIterator
zheleznyakov::Tree< Key, Value, Compare >::ConstRnLIterator::operator++(int)
{
  ConstRnLIterator temp(iter_);
  ++temp;
  return temp;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::ConstRnLIterator &
zheleznyakov::Tree< Key, Value, Compare >::ConstRnLIterator::operator--()
{
  --iter_;
  return *this;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::ConstRnLIterator
zheleznyakov::Tree< Key, Value, Compare >::ConstRnLIterator::operator--(int)
{
  ConstRnLIterator temp(iter_);
  --(temp);
  return temp;
}

template < typename Key, typename Value, typename Compare >
bool zheleznyakov::Tree< Key, Value, Compare >::ConstRnLIterator::operator==(const ConstRnLIterator & other) const
{
  return iter_.currentIter_ == other.iter_.currentIter_;
}

template < typename Key, typename Value, typename Compare >
bool zheleznyakov::Tree< Key, Value, Compare >::ConstRnLIterator::operator!=(const ConstRnLIterator & other) const
{
  return !(other == *this);
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::data_t &
zheleznyakov::Tree< Key, Value, Compare >::ConstRnLIterator::operator*()
{
  return *iter_;
}

template < typename Key, typename Value, typename Compare >
typename zheleznyakov::Tree< Key, Value, Compare >::data_t *
zheleznyakov::Tree< Key, Value, Compare >::ConstRnLIterator::operator->()
{
  return &iter_.currentIter_->data;
}
#endif
