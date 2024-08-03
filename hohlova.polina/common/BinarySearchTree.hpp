#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <stack.hpp>
#include <queue.hpp>
#include <functional>

template < typename Key, typename Value, typename Compare = std::less< Key > >
class BinarySearchTree
{
public:
  class Node;
  class Iterator;
  class ConstIterator;

  BinarySearchTree();
  ~BinarySearchTree();
  void push(const Key& k, const Value& v);
  bool empty() const noexcept;
  size_t size() const noexcept;
  void swap(BinarySearchTree& other);
  Value at(const Key& k) const;
  Value get(const Key& k);
  bool contains(const Key& k);
  Value drop(const Key& k);
  Iterator find(const Key& k) const noexcept;

  Iterator begin();
  Iterator end();

  ConstIterator cbegin() const;
  ConstIterator cend() const;

  Value& operator[](Key k) const;

  template< typename F >
  F traverse_lnr(F f) const;

  template< typename F >
  F traverse_rnr(F f) const;

  template< typename F >
  F traverse_breadth(F f) const;

private:
  Node* root;
  Compare comp;

  void clear(Node* node);
  Node* insert(Node* node, const Key& k, const Value& v);
  Node* find(Node* node, const Key& k);
  Node* remove(Node*& node, const Key& k);
  Node* findMin(Node* node);
};

template< typename Key, typename Value, typename Compare >
class BinarySearchTree< Key, Value, Compare >::Node
{
public:
  friend class BinarySearchTree< Key, Value, Compare >;
  explicit Node(const Key& k, const Value& v) : key(k), value(v), left(nullptr), right(nullptr) {}
private:
  Key key;
  Value value;
  Node* left;
  Node* right;
};

template< typename Key, typename Value, typename Compare >
class BinarySearchTree< Key, Value, Compare >::ConstIterator :
  public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > >
{
public:
  friend class BinarySearchTree< Key, Value, Compare >;
  ConstIterator() {}
  ConstIterator(Node* node);

  bool operator!=(const ConstIterator& other) const;
  ConstIterator& operator++();
  std::pair< const Key&, const Value& > operator*() const;
private:
  hohlova::Stack< Node* > stack;
};

template< typename Key, typename Value, typename Compare >
BinarySearchTree< Key, Value, Compare >::ConstIterator::ConstIterator(Node* node)
{
  if (node)
  {
    pushLeftBranch(node);
  }
}

template< typename Key, typename Value, typename Compare >
bool BinarySearchTree< Key, Value, Compare >::ConstIterator::operator!=(const ConstIterator& other) const
{
  return !stack.empty() || !other.stack.empty();
}

template< typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::ConstIterator& BinarySearchTree< Key, Value, Compare >::ConstIterator::operator++()
{
  Node* current = stack.top();
  stack.pop();
  pushLeftBranch(current->right);
  return *this;
}

template< typename Key, typename Value, typename Compare >
std::pair< const Key&, const Value& > BinarySearchTree< Key, Value, Compare >::ConstIterator::operator*() const
{
  if (stack.empty())
  {
    throw std::runtime_error("Dereferencing end iterator");
  }
  return std::make_pair(std::cref(stack.top()->key), std::cref(stack.top()->value));
}

template< typename Key, typename Value, typename Compare >
class BinarySearchTree< Key, Value, Compare >::Iterator :
  public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > >
{
public:
  friend class BinarySearchTree< Key, Value, Compare >;
  Iterator() {}
  Iterator(Node* node);

  bool operator!=(const Iterator& other);
  Iterator& operator++();
  std::pair< const Key&, const Value& > operator*();
private:
  void pushLeftBranch(Node* node);
  hohlova::Stack< Node* > stack;
};

template< typename Key, typename Value, typename Compare >
BinarySearchTree< Key, Value, Compare >::Iterator::Iterator(Node* node)
{
  if (node)
  {
    pushLeftBranch(node);
  }
}

template< typename Key, typename Value, typename Compare >
bool BinarySearchTree< Key, Value, Compare >::Iterator::operator!=(const Iterator& other)
{
  return !stack.empty() || !other.stack.empty();
}

template< typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::Iterator& BinarySearchTree< Key, Value, Compare >::Iterator::operator++()
{
  Node* current = stack.top();
  stack.pop();
  pushLeftBranch(current->right);
  return *this;
}

template< typename Key, typename Value, typename Compare >
std::pair< const Key&, const Value& > BinarySearchTree< Key, Value, Compare >::Iterator::operator*()
{
  if (stack.empty())
  {
    throw std::runtime_error("Dereferencing end iterator");
  }
  return std::make_pair(std::cref(stack.top()->key), std::cref(stack.top()->value));
}

template< typename Key, typename Value, typename Compare >
void  BinarySearchTree< Key, Value, Compare >::Iterator::pushLeftBranch(Node* node)
{
  while (node)
  {
    stack.push(node);
    node = node->left;
  }
}

template< typename Key, typename Value, typename Compare >
BinarySearchTree< Key, Value, Compare >::BinarySearchTree() :
  root(nullptr),
  comp(Compare())
{}

template< typename Key, typename Value, typename Compare >
BinarySearchTree< Key, Value, Compare >::~BinarySearchTree()
{
  clear(root);
}

template< typename Key, typename Value, typename Compare >
void BinarySearchTree< Key, Value, Compare >::push(const Key& k, const Value& v)
{
  root = insert(root, k, v);
}

template< typename Key, typename Value, typename Compare >
bool BinarySearchTree< Key, Value, Compare >::empty() const noexcept
{
  return root == nullptr ? true : false;
}

template< typename Key, typename Value, typename Compare >
size_t BinarySearchTree< Key, Value, Compare >::size() const noexcept
{
  size_t size = 0;
  typename BinarySearchTree< Key, Value >::Iterator it = begin();
  while (it != end())
  {
    size++;
    it++;
  }
  return size;
}

template < typename Key, typename Value, typename Compare >
void BinarySearchTree< Key, Value, Compare >::swap(BinarySearchTree& other)
{
  std::swap(root, other.root);
  std::swap(comp, other.comp);
}

template< typename Key, typename Value, typename Compare >
Value BinarySearchTree< Key, Value, Compare >::at(const Key& k) const
{
  using iterator = typename BinarySearchTree< Key, Value >::Iterator;
  for (iterator it = begin(); it != end(); it++)
  {
    if (it->first == k)
    {
      return it->second;
    }
  }
  throw std::runtime_error("Key not found\n");
}

template< typename Key, typename Value, typename Compare >
Value BinarySearchTree< Key, Value, Compare >::get(const Key& k)
{
  Node* node = find(root, k);
  if (node)
  {
    return node->value;
  }
  return nullptr;
}

template< typename Key, typename Value, typename Compare >
bool BinarySearchTree< Key, Value, Compare >::contains(const Key& k)
{
  Node* node = find(root, k);
  if (node)
  {
    return true;
  }
  return false;
}

template< typename Key, typename Value, typename Compare >
Value BinarySearchTree< Key, Value, Compare >::drop(const Key& k)
{
  Node* node = remove(root, k);
  if (node)
  {
    if (root == nullptr)
    {
      root = node;
    }
    Value val = node->value;
    return val;
  }
  throw std::out_of_range("Key not found");
}

template< typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::Iterator BinarySearchTree< Key, Value, Compare >::find(const Key& k) const noexcept
{
  using iterator = typename BinarySearchTree< Key, Value >::Iterator;
  for (iterator it = begin(); it != end(); it++)
  {
    if (it->first == k)
    {
      return it;
    }
  }
  return nullptr;
}

template< typename Key, typename Value, typename Compare >
void BinarySearchTree< Key, Value, Compare >::clear(Node* node)
{
  if (node)
  {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

template < typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::Node*
BinarySearchTree< Key, Value, Compare >::insert(Node* node, const Key& k, const Value& v)
{
  if (!node)
  {
    return new Node(k, v);
  }

  if (comp(k, node->key))
  {
    node->left = insert(node->left, k, v);
  }
  else if (comp(node->key, k))
  {
    node->right = insert(node->right, k, v);
  }
  else
  {
    node->value = v;
  }
  return node;
}

template < typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::Node* BinarySearchTree< Key, Value, Compare >::find(Node* node, const Key& k)
{
  if (!node)
  {
    return nullptr;
  }

  if (comp(k, node->key))
  {
    return find(node->left, k);
  }
  else if (comp(node->key, k))
  {
    return find(node->right, k);
  }
  else
  {
    return node;
  }
}

template < typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::Node* BinarySearchTree< Key, Value, Compare >::remove(Node*& node, const Key& k)
{
  if (!node)
  {
    return nullptr;
  }

  if (comp(k, node->key))
  {
    node->left = remove(node->left, k);
  }
  else if (comp(node->key, k))
  {
    node->right = remove(node->right, k);
  }
  else
  {
    if (!node->left)
    {
      Node* temp = node->right;
      delete node;
      node = nullptr;
      return temp;
    }
    else if (!node->right)
    {
      Node* temp = node->left;
      delete node;
      node = nullptr;
      return temp;
    }

    Node* minRight = findMin(node->right);
    node->key = minRight->key;
    node->value = minRight->value;
    node->right = remove(node->right, minRight->key);
  }
  return node;
}

template < typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::Node* BinarySearchTree< Key, Value, Compare >::findMin(Node* node)
{
  while (node->left)
  {
    node = node->left;
  }
  return node;
}

template< typename Key, typename Value, typename Compare >
Value& BinarySearchTree< Key, Value, Compare >::operator[](Key k) const
{
  Value val = at(k);
  Value& valRef{ val };
  return valRef;
}

template < typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::ConstIterator BinarySearchTree< Key, Value, Compare >::cbegin() const
{
  return ConstIterator(root);
}

template < typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::ConstIterator BinarySearchTree< Key, Value, Compare >::cend() const
{
  return ConstIterator();
}

template < typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::Iterator BinarySearchTree< Key, Value, Compare >::begin()
{
  return Iterator(root);
}

template < typename Key, typename Value, typename Compare >
typename BinarySearchTree< Key, Value, Compare >::Iterator BinarySearchTree< Key, Value, Compare >::end()
{
  return Iterator();
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F BinarySearchTree< Key, Value, Compare >::traverse_lnr(F f) const
{
  if (!root)
  {
    std::cout << "<EMPTY>\n";
    return f;
  }
  hohlova::Stack< Node* > s;
  Node* current = root;
  while (current != NULL || !s.empty())
  {
    while (current != NULL)
    {
      s.push(current);
      current = current->left;
    }
    current = s.top();
    s.pop();
    std::pair< Key, Value > myPair = std::make_pair(current->key, current->value);
    f(myPair);
    current = current->right;
  }
  return f;
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F BinarySearchTree< Key, Value, Compare >::traverse_rnr(F f) const
{
  if (!root)
  {
    std::cout << "<EMPTY>\n";
    return f;
  }
  hohlova::Stack< Node* > s;
  Node* current = root;

  while (current != NULL || !s.empty())
  {
    while (current != NULL)
    {
      s.push(current);
      current = current->right;
    }
    current = s.top();
    s.pop();
    std::pair< Key, Value > myPair = std::make_pair(current->key, current->value);
    f(myPair);
    current = current->left;
  }
  return f;
}

template < typename Key, typename Value, typename Compare >
template< typename F >
F BinarySearchTree< Key, Value, Compare >::traverse_breadth(F f) const
{
  if (!root)
  {
    std::cout << "<EMPTY>\n";
    return f;
  }
  hohlova::Queue< Node* > q;
  q.push(root);
  while (!q.empty())
  {
    Node* curr = q.front();
    q.pop();
    std::pair< Key, Value > myPair(curr->key, curr->value);
    f(myPair);
    if (curr->left)
    {
      q.push(curr->left);
    }
    if (curr->right)
    {
      q.push(curr->right);
    }
  }
    return f;
}

#endif
