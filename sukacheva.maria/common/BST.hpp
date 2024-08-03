#ifndef BST_HPP
#define BST_HPP
#include <cassert>
#include <utility>
#include <functional>
#include <stdexcept>
#include "TreeNode.hpp"
#include "Stack.hpp"
#include "Queue.hpp"

namespace sukacheva
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class BST
  {
  public:
    class Iterator;
    class ConstIterator;

    using TreeNode = details::TreeNode< Value, Key >;

    BST();
    BST(const BST& other) noexcept;
    BST(BST&& other) noexcept;
    ~BST();

    void insert(Key k, Value v);
    Value at(const Key& k) const;
    size_t getHeight(TreeNode* node) const noexcept;
    bool empty() const noexcept;
    size_t size() const noexcept;
    Iterator find(const Key& k) const noexcept;
    Iterator erase(Iterator& pos) noexcept;
    void erase(const Key& k) noexcept;
    size_t count(const Key& k) const noexcept;
    void clear() noexcept;
    void clear(TreeNode* node);
    std::pair< Iterator, Iterator > equalRange(const Key& key) const noexcept;
    Iterator lowerBound(const Key& key) const noexcept;
    Iterator upperBound(const Key& key) const noexcept;

    Iterator begin() const;
    Iterator end() const;

    ConstIterator cbegin() const;
    ConstIterator cend() const;

    Value& operator[](Key k) const;
    BST& operator=(const BST& other);
    BST& operator=(BST&& other) noexcept;

    template< typename F >
    F traverse_lnr(F& f) const;
    template< typename F >
    F traverse_rnl(F& f) const;
    template< typename F >
    F traverse_breadth(F& f) const;
  private:
    TreeNode* root;
    Compare cmp;

    TreeNode* findMin(TreeNode* node) const;
    TreeNode* findMax(TreeNode* node) const;
    TreeNode* pushNode(TreeNode* node, Key k, Value v, TreeNode* parent);
    TreeNode* balance(TreeNode* node);
    TreeNode* rotateRight(TreeNode* node);
    TreeNode* rotateLeft(TreeNode* node);
    TreeNode* deleteNode(TreeNode* node, const Key& k);
    void updateHeight(TreeNode* node);
    int getBalanceFactor(TreeNode* node);
    TreeNode* copy(TreeNode* node);
  };

  template < typename Key, typename Value, typename Compare >
  class BST< Key, Value, Compare >::Iterator
  {
  public:
    friend class BST;
    Iterator();
    Iterator(TreeNode* node_);
    ~Iterator() = default;
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;

    Iterator& operator++();
    Iterator operator++(int);

    std::pair< Key, Value >& operator*();
    std::pair< Key, Value >* operator->();

    bool operator!=(const Iterator&) const;
    bool operator==(const Iterator&) const;

  private:
    TreeNode* findMin(TreeNode* node);
    TreeNode* node;
  };

  template < typename Key, typename Value, typename Compare >
  class BST< Key, Value, Compare >::ConstIterator
  {
  public:
    friend class BST;
    ConstIterator();
    ConstIterator(TreeNode* node_);
    ~ConstIterator() = default;
    ConstIterator(const ConstIterator&) = default;
    ConstIterator& operator=(const ConstIterator&) = default;

    ConstIterator& operator++();
    ConstIterator operator++(int);

    const std::pair< Key, Value >& operator*() const;
    const std::pair< Key, Value >* operator->() const;

    bool operator!=(const ConstIterator&) const;
    bool operator==(const ConstIterator&) const;

  private:
    TreeNode* findMin(TreeNode* node);
    TreeNode* node;
  };

  template< typename Key, typename Value, typename Compare >
  using iterator = typename BST< Key, Value, Compare >::Iterator;

  template< typename Key, typename Value, typename Compare >
  using constIterator = typename BST< Key, Value, Compare >::ConstIterator;

  template< typename Key, typename Value, typename Compare >
  using iteratorsPair = std::pair< iterator< Key, Value, Compare >, iterator< Key, Value, Compare > >;

  template< typename Key, typename Value, typename Compare >
  void BST< Key, Value, Compare >::clear() noexcept
  {
    clear(root);
  }

  template< typename Key, typename Value, typename Compare >
  template< typename F >
  F BST< Key, Value, Compare >::traverse_lnr(F& f) const
  {
    if (!root)
    {
      return f;
    }
    Stack< TreeNode* > stack;
    TreeNode* applicant = root;
    while (!stack.empty() || applicant)
    {
      if (applicant)
      {
        stack.push(applicant);
        applicant = applicant->left;
      }
      else
      {
        applicant = stack.top();
        stack.pop();
        f(applicant->data);
        applicant = applicant->right;
      }
    }
    return f;
  }

  template< typename Key, typename Value, typename Compare >
  template< typename F >
  F BST< Key, Value, Compare >::traverse_rnl(F& f) const
  {
    if (!root)
    {
      return f;
    }
    Stack< TreeNode* > stack;
    TreeNode* applicant = root;
    while (!stack.empty() || applicant)
    {
      if (applicant)
      {
        stack.push(applicant);
        applicant = applicant->right;
      }
      else
      {
        applicant = stack.top();
        stack.pop();
        f(applicant->data);
        applicant = applicant->left;
      }
    }
    return f;
  }

  template< typename Key, typename Value, typename Compare >
  template< typename F >
  F BST< Key, Value, Compare >::traverse_breadth(F& f) const
  {
    if (!root)
    {
      return f;
    }
    Queue< TreeNode* > queue;
    queue.push(root);
    while (!queue.empty())
    {
      TreeNode* applicant = queue.front();
      queue.pop();
      f(applicant->data);
      if (applicant->left)
      {
        queue.push(applicant->left);
      }
      if (applicant->right)
      {
        queue.push(applicant->right);
      }
    }
    return f;
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::TreeNode* BST< Key, Value, Compare >::copy(TreeNode* node)
  {
    if (!node)
    {
      return nullptr;
    }
    TreeNode* newNode = new TreeNode(node->data);
    newNode->left = copy(node->left);
    newNode->right = copy(node->right);
    return newNode;
  }

  template< typename Key, typename Value, typename Compare >
  BST< Key, Value, Compare >& BST< Key, Value, Compare >::operator=(const BST& other)
  {
    if (this == &other)
    {
      return *this;
    }
    BST< Key, Value, Compare > temp;
    temp.root = other.root;
    if (temp.size() == other.size())
    {
      clear(root);
      root = temp.root;
      cmp = other.cmp;
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  BST< Key, Value, Compare >& BST< Key, Value, Compare >::operator=(BST&& other) noexcept
  {
    if (this != &other)
    {
      clear(root);
      root = other.root;
      cmp = std::move(other.cmp);
      other.root = nullptr;
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  BST< Key, Value, Compare >::BST(const BST& other) noexcept
  {
    root = nullptr;
    cmp = other.cmp;
    Iterator it;
    for (it = other.begin(); it != other.end(); it++)
    {
      insert(it->first, it->second);
    }
  }

  template< typename Key, typename Value, typename Compare >
  BST< Key, Value, Compare >::BST(BST&& other) noexcept :
    root(other.root),
    cmp(std::move(other.cmp))
  {
    other.root = nullptr;
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Iterator BST< Key, Value, Compare >::lowerBound(const Key& key) const noexcept
  {
    TreeNode* current = root;
    TreeNode* result = nullptr;
    while (current != nullptr)
    {
      if (!cmp(current->data.first, key))
      {
        result = current;
        current = current->left;
      }
      else
      {
        current = current->right;
      }
    }
    return Iterator(result);
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Iterator BST< Key, Value, Compare >::upperBound(const Key& key) const noexcept
  {
    TreeNode* current = root;
    TreeNode* result = nullptr;
    while (current != nullptr)
    {
      if (cmp(key, current->data.first))
      {
        result = current;
        current = current->left;
      }
      else
      {
        current = current->right;
      }
    }

    return Iterator(result);
  }

  template< typename Key, typename Value, typename Compare >
  iteratorsPair< Key, Value, Compare > BST< Key, Value, Compare >::equalRange(const Key& key) const noexcept
  {
    return std::make_pair(lower_bound(key), upper_bound(key));
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Iterator BST< Key, Value, Compare >::find(const Key& k) const noexcept
  {
    using iterator = typename BST< Key, Value >::Iterator;
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
  typename BST< Key, Value, Compare >::Iterator BST< Key, Value, Compare >::erase(Iterator& pos) noexcept
  {
    using iterator = typename BST< Key, Value >::Iterator;
    iterator it = pos;
    root = deleteNode(root, it->first);
    return it++;
  }

  template< typename Key, typename Value, typename Compare >
  size_t BST< Key, Value, Compare >::count(const Key& k) const noexcept
  {
    size_t counter = 0;
    using iterator = typename BST< Key, Value >::Iterator;
    for (iterator it = begin(); it != end(); it++)
    {
      if (it->first == k)
      {
        counter++;
      }
    }
    return counter;
  }

  template< typename Key, typename Value, typename Compare >
  Value BST< Key, Value, Compare >::at(const Key& k) const
  {
    using iterator = typename BST< Key, Value >::Iterator;
    for (iterator it = begin(); it != end(); it++)
    {
      if (it->first == k)
      {
        return it->second;
      }
    }
    throw std::runtime_error("Key not found");
  }

  template< typename Key, typename Value, typename Compare >
  Value& BST< Key, Value, Compare >::operator[](Key k) const
  {
    Value val = at(k);
    Value &valRef{val};
    return valRef;
  }

  template< typename Key, typename Value, typename Compare >
  BST< Key, Value, Compare >::BST():
    root(nullptr),
    cmp(Compare())
  {}

  template< typename Key, typename Value, typename Compare >
  BST< Key, Value, Compare >::~BST()
  {
    clear(root);
  }

  template< typename Key, typename Value, typename Compare >
  void BST< Key, Value, Compare >::clear(TreeNode* node)
  {
    if (node)
    {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  template< typename Key, typename Value, typename Compare >
  size_t BST< Key, Value, Compare >::size() const noexcept
  {
    size_t size = 0;
    typename BST< Key, Value >::Iterator it = begin();
    while (it != end())
    {
      size++;
      it++;
    }
    return size;
  }

  template< typename Key, typename Value, typename Compare >
  bool BST< Key, Value, Compare >::empty() const noexcept
  {
    return size() > 0 ? false : true;
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Iterator BST< Key, Value, Compare >::begin() const
  {
    return Iterator(findMin(root));
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Iterator BST< Key, Value, Compare >::end() const
  {
    return Iterator(nullptr);
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::ConstIterator BST< Key, Value, Compare >::cbegin() const
  {
    return ConstIterator(findMin(root));
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::ConstIterator BST< Key, Value, Compare >::cend() const
  {
    return ConstIterator(nullptr);
  }

  template< typename Key, typename Value, typename Compare >
  BST< Key, Value, Compare >::ConstIterator::ConstIterator():
    node(nullptr)
  {}

  template< typename Key, typename Value, typename Compare >
  BST< Key, Value, Compare >::ConstIterator::ConstIterator(TreeNode* node_) :
    node(node_)
  {}

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::ConstIterator& BST< Key, Value, Compare >::ConstIterator::operator++()
  {
    assert(node != nullptr);
    if (node->right != nullptr)
    {
      node = findMin(node->right);
    }
    else
    {
      while (node->parent != nullptr && node == node->parent->right)
      {
        node = node->parent;
      }
      node = node->parent;
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::ConstIterator BST< Key, Value, Compare >::ConstIterator::operator++(int)
  {
    ConstIterator temp = *this;
    ++(*this);
    return temp;
  }

  template< typename Key, typename Value, typename Compare >
  const std::pair< Key, Value >& BST< Key, Value, Compare >::ConstIterator::operator*() const
  {
    return node->data;
  }

  template< typename Key, typename Value, typename Compare >
  const std::pair< Key, Value >* BST< Key, Value, Compare >::ConstIterator::operator->() const
  {
    return std::addressof(node->data);
  }

  template< typename Key, typename Value, typename Compare >
  bool BST< Key, Value, Compare >::ConstIterator::operator!=(const ConstIterator& other) const
  {
    return node != other.node;
  }

  template< typename Key, typename Value, typename Compare >
  bool BST< Key, Value, Compare >::ConstIterator::operator==(const ConstIterator& other) const
  {
    return node == other.node;
  }

  template< typename Key, typename Value, typename Compare >
  BST< Key, Value, Compare >::Iterator::Iterator():
    node(nullptr)
  {}

  template< typename Key, typename Value, typename Compare >
  BST< Key, Value, Compare >::Iterator::Iterator(TreeNode* node_):
    node(node_)
  {}

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Iterator& BST< Key, Value, Compare >::Iterator::operator++()
  {
    assert(node != nullptr);
    if (node->right != nullptr)
    {
      node = findMin(node->right);
    }
    else
    {
      while (node->parent != nullptr && node == node->parent->right)
      {
        node = node->parent;
      }
      node = node->parent;
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::Iterator BST< Key, Value, Compare >::Iterator::operator++(int)
  {
    Iterator temp = *this;
    ++(*this);
    return temp;
  }

  template< typename Key, typename Value, typename Compare >
  std::pair< Key, Value >& BST< Key, Value, Compare >::Iterator::operator*()
  {
    return node->data;
  }

  template< typename Key, typename Value, typename Compare >
  std::pair< Key, Value >* BST< Key, Value, Compare >::Iterator::operator->()
  {
    return std::addressof(node->data);
  }

  template< typename Key, typename Value, typename Compare >
  bool BST< Key, Value, Compare >::Iterator::operator!=(const Iterator& other) const
  {
    return node != other.node;
  }

  template< typename Key, typename Value, typename Compare >
  bool BST< Key, Value, Compare >::Iterator::operator==(const Iterator& other) const
  {
    return node == other.node;
  }

  template < typename Key, typename Value, typename Compare >
  size_t BST< Key, Value, Compare >::getHeight(TreeNode* node) const noexcept
  {
    if (node == nullptr)
    {
      return 0;
    }
    return node->height;
  }

  template < typename Key, typename Value, typename Compare >
  void BST< Key, Value, Compare >::updateHeight(TreeNode* node)
  {
    if (node != nullptr)
    {
      node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
  }

  template < typename Key, typename Value, typename Compare >
  int BST< Key, Value, Compare >::getBalanceFactor(TreeNode* node)
  {
    if (node == nullptr)
    {
      return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::TreeNode* BST< Key, Value, Compare >::Iterator::findMin(TreeNode* node)
  {
    while (node && node->left != nullptr)
    {
      node = node->left;
    }
    return node;
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::TreeNode* BST< Key, Value, Compare >::ConstIterator::findMin(TreeNode* node)
  {
    while (node && node->left != nullptr)
    {
      node = node->left;
    }
    return node;
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::TreeNode* BST< Key, Value, Compare >::findMax(TreeNode* node) const
  {
    while (node && node->right != nullptr)
    {
      node = node->right;
    }
    return node;
  }

  template< typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::TreeNode* BST< Key, Value, Compare >::findMin(TreeNode* node) const
  {
    while (node && node->left != nullptr)
    {
      node = node->left;
    }
    return node;
  }

  template < typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::TreeNode* BST< Key, Value, Compare >::rotateLeft(TreeNode* node)
  {
    TreeNode* newRoot = node->right;
    node->right = newRoot->left;
    if (newRoot->left != nullptr)
    {
      newRoot->left->parent = node;
    }
    newRoot->parent = node->parent;
    if (node->parent == nullptr)
    {
      root = newRoot;
    }
    else if (node == node->parent->left)
    {
      node->parent->left = newRoot;
    }
    else
    {
      node->parent->right = newRoot;
    }
    newRoot->left = node;
    node->parent = newRoot;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
  }

  template < typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::TreeNode* BST< Key, Value, Compare >::rotateRight(TreeNode* node)
  {
    TreeNode* newRoot = node->left;
    node->left = newRoot->right;
    if (newRoot->right != nullptr)
    {
      newRoot->right->parent = node;
    }
    newRoot->parent = node->parent;
    if (node->parent == nullptr)
    {
      root = newRoot;
    }
    else if (node == node->parent->right)
    {
      node->parent->right = newRoot;
    }
    else
    {
      node->parent->left = newRoot;
    }
    newRoot->right = node;
    node->parent = newRoot;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
  }

  template < typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::TreeNode* BST< Key, Value, Compare >::balance(TreeNode* node)
  {
    updateHeight(node);
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1)
    {
      if (getBalanceFactor(node->left) < 0)
      {
        node->left = rotateLeft(node->left);
      }
      return rotateRight(node);
    }
    if (balanceFactor < -1)
    {
      if (getBalanceFactor(node->right) > 0)
      {
        node->right = rotateRight(node->right);
      }
      return rotateLeft(node);
    }
    return node;
  }

  template < typename Key, typename Value, typename Compare >
  void BST< Key, Value, Compare >::insert(Key k, Value v)
  {
    root = pushNode(root, k, v, nullptr);
  }

  template < typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::TreeNode* BST< Key, Value, Compare >::pushNode(TreeNode* node, Key k, Value v, TreeNode* parent)
  {
    if (node == nullptr)
    {
      return new TreeNode(k, v, parent);
    }
    if (cmp(k, node->data.first))
    {
      node->left = pushNode(node->left, k, v, node);
    }
    else if (cmp(node->data.first, k))
    {
      node->right = pushNode(node->right, k, v, node);
    }
    return balance(node);
  }

  template < typename Key, typename Value, typename Compare >
  void BST< Key, Value, Compare >::erase(const Key& k) noexcept
  {
    root = deleteNode(root, k);
  }

  template < typename Key, typename Value, typename Compare >
  typename BST< Key, Value, Compare >::TreeNode* BST< Key, Value, Compare >::deleteNode(TreeNode* node, const Key& k)
  {
    if (node == nullptr)
    {
      return node;
    }
    if (cmp(k, node->data.first))
    {
      node->left = deleteNode(node->left, k);
    }
    else if (cmp(node->data.first, k))
    {
      node->right = deleteNode(node->right, k);
    }
    else
    {
      if (!node->left && !node->right)
      {
        delete node;
        return nullptr;
      }
      else if (!node->left || !node->right)
      {
        TreeNode* temp = node->left ? node->left : node->right;
        temp->parent = node->parent;
        delete node;
        return temp;
      }
      else
      {
        TreeNode* successor = findMin(node->right);
        node->data = successor->data;
        node->right = deleteNode(node->right, successor->data.first);
      }
    }
    return balance(node);
  }
}

#endif
