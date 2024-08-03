#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <Queue.hpp>
#include <Stack.hpp>

namespace zhitnyj {
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class BSTree {
  public:
    class Iterator;

    class ConstIterator;

    using kvPair = std::pair< Key, Value >;

    BSTree();
    BSTree(const BSTree &other);
    BSTree(BSTree &&other) noexcept;
    ~BSTree();

    BSTree &operator=(const BSTree &other);
    BSTree &operator=(BSTree &&other) noexcept;

    void push(Key k, Value v);
    Value get(Key k) const;
    Value drop(Key k);

    bool empty() const noexcept;
    size_t size() const;
    void clear() noexcept;
    void swap(BSTree &other) noexcept;

    ConstIterator begin() const;
    ConstIterator end() const;

    Iterator begin();
    Iterator end();

    ConstIterator find(const Key &k) const;
    Iterator find(const Key &k);

    std::pair< Iterator, bool > insert(const std::pair< Key, Value > &kv);
    void insert(const Key &k, const Value &v);
    void erase(Iterator pos, const Key &k);

    std::pair< ConstIterator, ConstIterator > equal_range(const Key &k) const;
    std::pair< Iterator, Iterator > equal_range(const Key &k);
    size_t count(const Key &k) const;

    template< typename F >
    F traverse_lnr(F f) const;

    template< typename F >
    F traverse_rnl(F f) const;

    template< typename F >
    F traverse_breadth(F f) const;

  private:
    struct Node {
      std::pair< Key, Value > data;
      Node *left;
      Node *right;
      Node *parent;

      Node(Key k, Value v, Node *p = nullptr) :
        data(std::make_pair(k, v)),
        left(nullptr),
        right(nullptr),
        parent(p) {
      }
    };

    Node *root;
    Compare comp;
    size_t node_count;

    void push(Node *&node, Key k, Value v, Node *parent);
    Value get(Node *node, Key k) const;
    Node *drop(Node *&node, Key k);
    void deleteTree(Node *node);
    Node *findMin(Node *node) const;
    Node *removeMin(Node *node);
    Node *copyTree(Node *node, Node *parent) const;
  };

  template< typename Key, typename Value >
  using kvPair = std::pair< Key, Value >;

  template< typename Key, typename Value, typename Compare >
  class BSTree< Key, Value, Compare >::ConstIterator : public std::iterator< std::bidirectional_iterator_tag, kvPair > {
  public:
    friend class BSTree< Key, Value, Compare >;

    ConstIterator();
    explicit ConstIterator(Node *node);
    const kvPair &operator*() const;
    const kvPair *operator->() const;
    ConstIterator &operator++();
    ConstIterator operator++(int);
    ConstIterator &operator--();
    ConstIterator operator--(int);
    bool operator==(const ConstIterator &other) const;
    bool operator!=(const ConstIterator &other) const;

  private:
    Node *current;

    Node *findNext(Node *node) const;
    Node *findPrev(Node *node) const;
  };

  template< typename Key, typename Value, typename Compare >
  BSTree< Key, Value, Compare >::ConstIterator::ConstIterator() : current(nullptr) {
  }

  template< typename Key, typename Value, typename Compare >
  BSTree< Key, Value, Compare >::ConstIterator::ConstIterator(Node *node) : current(node) {
  }

  template< typename Key, typename Value, typename Compare >
  const kvPair< Key, Value > &BSTree< Key, Value, Compare >::ConstIterator::operator*() const {
    return current->data;
  }

  template< typename Key, typename Value, typename Compare >
  const kvPair< Key, Value > *BSTree< Key, Value, Compare >::ConstIterator::operator->() const {
    return std::addressof(current->data);
  }

  template< typename Key, typename Value, typename Compare >
  typename BSTree< Key, Value, Compare >::ConstIterator &
  BSTree< Key, Value, Compare >::ConstIterator::operator++() {
    current = findNext(current);
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  typename BSTree< Key, Value, Compare >::ConstIterator
  BSTree< Key, Value, Compare >::ConstIterator::operator++(int) {
    ConstIterator temp = *this;
    ++(*this);
    return temp;
  }

  template< typename Key, typename Value, typename Compare >
  typename BSTree< Key, Value, Compare >::ConstIterator &
  BSTree< Key, Value, Compare >::ConstIterator::operator--() {
    current = findPrev(current);
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  typename BSTree< Key, Value, Compare >::ConstIterator
  BSTree< Key, Value, Compare >::ConstIterator::operator--(int) {
    ConstIterator temp = *this;
    --(*this);
    return temp;
  }

  template< typename Key, typename Value, typename Compare >
  bool BSTree< Key, Value, Compare >::ConstIterator::operator==(const ConstIterator &other) const {
    return current == other.current;
  }

  template< typename Key, typename Value, typename Compare >
  bool BSTree< Key, Value, Compare >::ConstIterator::operator!=(const ConstIterator &other) const {
    return current != other.current;
  }

  template< typename Key, typename Value, typename Compare >
  typename BSTree< Key, Value, Compare >::Node *
  BSTree< Key, Value, Compare >::ConstIterator::findNext(Node *node) const {
    if (node == nullptr) {
      return nullptr;
    }
    if (node->right) {
      node = node->right;
      while (node->left) {
        node = node->left;
      }
      return node;
    }
    while (node->parent && node->parent->right == node) {
      node = node->parent;
    }
    return node->parent;
  }

  template< typename Key, typename Value, typename Compare >
  typename BSTree< Key, Value, Compare >::Node *
  BSTree< Key, Value, Compare >::ConstIterator::findPrev(Node *node) const {
    if (node == nullptr) {
      return nullptr;
    }
    if (node->left) {
      node = node->left;
      while (node->right) {
        node = node->right;
      }
      return node;
    }
    while (node->parent && node->parent->left == node) {
      node = node->parent;
    }
    return node->parent;
  }

  template< typename Key, typename Value, typename Compare >
  class BSTree< Key, Value, Compare >::Iterator : public std::iterator< std::bidirectional_iterator_tag, kvPair > {
  public:
    friend class BSTree< Key, Value, Compare >;

    Iterator();
    explicit Iterator(ConstIterator constIter);

    kvPair &operator*() const;
    kvPair *operator->() const;
    Iterator &operator++();
    Iterator operator++(int);
    Iterator &operator--();
    Iterator operator--(int);

    bool operator==(const Iterator &other) const;
    bool operator!=(const Iterator &other) const;

  private:
    ConstIterator constIter_;
  };

  template< typename Key, typename Value, typename Compare >
  BSTree< Key, Value, Compare >::Iterator::Iterator() : constIter_() {
  }

  template< typename Key, typename Value, typename Compare >
  BSTree< Key, Value, Compare >::Iterator::Iterator(ConstIterator constIter) : constIter_(constIter) {
  }

  template< typename Key, typename Value, typename Compare >
  kvPair< Key, Value > &BSTree< Key, Value, Compare >::Iterator::operator*() const {
    return constIter_.current->data;
  }

  template< typename Key, typename Value, typename Compare >
  kvPair< Key, Value > *BSTree< Key, Value, Compare >::Iterator::operator->() const {
    return std::addressof(constIter_.current->data);
  }

  template< typename Key, typename Value, typename Compare >
  typename BSTree< Key, Value, Compare >::Iterator &
  BSTree< Key, Value, Compare >::Iterator::operator++() {
    ++constIter_;
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  typename BSTree< Key, Value, Compare >::Iterator
  BSTree< Key, Value, Compare >::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
  }

  template< typename Key, typename Value, typename Compare >
  typename BSTree< Key, Value, Compare >::Iterator &
  BSTree< Key, Value, Compare >::Iterator::operator--() {
    --constIter_;
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  typename BSTree< Key, Value, Compare >::Iterator
  BSTree< Key, Value, Compare >::Iterator::operator--(int) {
    Iterator temp = *this;
    --(*this);
    return temp;
  }

  template< typename Key, typename Value, typename Compare >
  bool BSTree< Key, Value, Compare >::Iterator::operator==(const Iterator &other) const {
    return constIter_ == other.constIter_;
  }

  template< typename Key, typename Value, typename Compare >
  bool BSTree< Key, Value, Compare >::Iterator::operator!=(const Iterator &other) const {
    return !(*this == other);
  }

  template< typename Key, typename Value, typename Compare >
  BSTree< Key, Value, Compare >::BSTree() :
    root(nullptr),
    node_count(0) {
  }

  template< typename Key, typename Value, typename Compare >
  BSTree< Key, Value, Compare >::BSTree(const BSTree &other) :
    root(copyTree(other.root, nullptr)),
    node_count(other.node_count) {
  }

  template< typename Key, typename Value, typename Compare >
  BSTree< Key, Value, Compare >::BSTree(BSTree &&other) noexcept :
    root(other.root),
    node_count(other.node_count) {
    other.root = nullptr;
    other.node_count = 0;
  }

  template< typename Key, typename Value, typename Compare >
  BSTree< Key, Value, Compare >::~BSTree() {
    deleteTree(root);
  }

  template< typename Key, typename Value, typename Compare >
  BSTree< Key, Value, Compare > &BSTree< Key, Value, Compare >::operator=(const BSTree &other) {
    if (this != &other) {
      deleteTree(root);
      root = copyTree(other.root, nullptr);
      node_count = other.node_count;
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  BSTree< Key, Value, Compare > &BSTree< Key, Value, Compare >::operator=(BSTree &&other) noexcept {
    if (this != &other) {
      deleteTree(root);
      root = other.root;
      node_count = other.node_count;
      other.root = nullptr;
      other.node_count = 0;
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  void BSTree< Key, Value, Compare >::push(Node *&node, Key k, Value v, Node *parent) {
    if (node == nullptr) {
      node = new Node(k, v, parent);
      ++node_count;
    }
    else if (comp(k, node->data.first)) {
      push(node->left, k, v, node);
    }
    else if (comp(node->data.first, k)) {
      push(node->right, k, v, node);
    }
    else {
      node->data.second = v;
    }
  }

  template< typename Key, typename Value, typename Compare >
  void BSTree< Key, Value, Compare >::push(Key k, Value v) {
    push(root, k, v, nullptr);
  }

  template< typename Key, typename Value, typename Compare >
  Value BSTree< Key, Value, Compare >::get(Node *node, Key k) const {
    if (node == nullptr) {
      return Value();
    }
    else if (comp(k, node->data.first)) {
      return get(node->left, k);
    }
    else if (comp(node->data.first, k)) {
      return get(node->right, k);
    }
    else {
      return node->data.second;
    }
  }

  template< typename Key, typename Value, typename Compare >
  Value BSTree< Key, Value, Compare >::get(Key k) const {
    return get(root, k);
  }

  template< typename Key, typename Value, typename Compare >
  typename BSTree< Key, Value, Compare >::Node *
  BSTree< Key, Value, Compare >::findMin(Node *node) const {
    return node->left ? findMin(node->left) : node;
  }

  template< typename Key, typename Value, typename Compare >
  typename BSTree< Key, Value, Compare >::Node *
  BSTree< Key, Value, Compare >::removeMin(Node *node) {
    if (node->left == nullptr) {
      return node->right;
    }
    node->left = removeMin(node->left);
    return node;
  }

  template< typename Key, typename Value, typename Compare >
  typename BSTree< Key, Value, Compare >::Node *
  BSTree< Key, Value, Compare >::drop(Node *&node, Key k) {
    if (node == nullptr) {
      return nullptr;
    }
    if (comp(k, node->data.first)) {
      node->left = drop(node->left, k);
    }
    else if (comp(node->data.first, k)) {
      node->right = drop(node->right, k);
    }
    else {
      Node *left = node->left;
      Node *right = node->right;
      delete node;
      --node_count;
      if (!right) {
        return left;
      }
      Node *min = findMin(right);
      min->right = removeMin(right);
      min->left = left;
      return min;
    }
    return node;
  }

  template< typename Key, typename Value, typename Compare >
  Value BSTree< Key, Value, Compare >::drop(Key k) {
    Value value_ = get(k);
    root = drop(root, k);
    return value_;
  }

  template< typename Key, typename Value, typename Compare >
  void BSTree< Key, Value, Compare >::deleteTree(Node *node) {
    if (node == nullptr) {
      return;
    }
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
  }

  template< typename Key, typename Value, typename Compare >
  typename BSTree< Key, Value, Compare >::Node *
  BSTree< Key, Value, Compare >::copyTree(Node *node, Node *parent) const {
    if (node == nullptr) {
      return nullptr;
    }
    Node *newNode = new Node(node->data.first, node->data.second, parent);
    newNode->left = copyTree(node->left, newNode);
    newNode->right = copyTree(node->right, newNode);
    return newNode;
  }

  template< typename Key, typename Value, typename Compare >
  bool BSTree< Key, Value, Compare >::empty() const noexcept {
    return node_count == 0;
  }

  template< typename Key, typename Value, typename Compare >
  size_t BSTree< Key, Value, Compare >::size() const {
    return node_count;
  }

  template< typename Key, typename Value, typename Compare >
  void BSTree< Key, Value, Compare >::clear() noexcept {
    deleteTree(root);
    root = nullptr;
    node_count = 0;
  }

  template< typename Key, typename Value, typename Compare >
  void BSTree< Key, Value, Compare >::swap(BSTree &other) noexcept {
    Node *tempRoot = root;
    root = other.root;
    other.root = tempRoot;

    size_t tempCount = node_count;
    node_count = other.node_count;
    other.node_count = tempCount;
  }

  template< typename Key, typename Value, typename Compare >
  typename BSTree< Key, Value, Compare >::ConstIterator
  BSTree< Key, Value, Compare >::begin() const {
    if (root == nullptr) {
      return end();
    }
    Node *root_ = root;
    while (root_->left) {
      root_ = root_->left;
    }
    return ConstIterator(root_);
  }

  template< typename Key, typename Value, typename Compare >
  typename BSTree< Key, Value, Compare >::ConstIterator
  BSTree< Key, Value, Compare >::end() const {
    return ConstIterator();
  }

  template< typename Key, typename Value, typename Compare >
  typename BSTree< Key, Value, Compare >::Iterator
  BSTree< Key, Value, Compare >::begin() {
    if (root == nullptr) {
      return end();
    }
    Node *root_ = root;
    while (root_->left) {
      root_ = root_->left;
    }
    return Iterator(ConstIterator(root_));
  }

  template< typename Key, typename Value, typename Compare >
  typename BSTree< Key, Value, Compare >::Iterator
  BSTree< Key, Value, Compare >::end() {
    return Iterator(ConstIterator());
  }

  template< typename Key, typename Value, typename Compare >
  typename BSTree< Key, Value, Compare >::ConstIterator
  BSTree< Key, Value, Compare >::find(const Key &k) const {
    Node *current = root;
    while (current) {
      if (comp(k, current->data.first)) {
        current = current->left;
      }
      else if (comp(current->data.first, k)) {
        current = current->right;
      }
      else {
        return ConstIterator(current);
      }
    }
    return end();
  }

  template< typename Key, typename Value, typename Compare >
  typename BSTree< Key, Value, Compare >::Iterator
  BSTree< Key, Value, Compare >::find(const Key &k) {
    Node *current = root;
    while (current) {
      if (comp(k, current->data.first)) {
        current = current->left;
      }
      else if (comp(current->data.first, k)) {
        current = current->right;
      }
      else {
        return Iterator(ConstIterator(current));
      }
    }
    return end();
  }

  template< typename Key, typename Value, typename Compare >
  std::pair< typename BSTree< Key, Value, Compare >::Iterator, bool >
  BSTree< Key, Value, Compare >::insert(const std::pair< Key, Value > &kv) {
    Node *parent = nullptr;
    Node *current = root;
    bool isLeftChild = false;

    while (current) {
      parent = current;
      if (comp(kv.first, current->data.first)) {
        current = current->left;
        isLeftChild = true;
      }
      else if (comp(current->data.first, kv.first)) {
        current = current->right;
        isLeftChild = false;
      }
      else {
        return std::make_pair(Iterator(ConstIterator(current)), false);
      }
    }

    Node *newNode = new Node(kv.first, kv.second, parent);
    if (parent == nullptr) {
      root = newNode;
    }
    else if (isLeftChild) {
      parent->left = newNode;
    }
    else {
      parent->right = newNode;
    }

    ++node_count;
    return std::make_pair(Iterator(ConstIterator(newNode)), true);
  }

  template< typename Key, typename Value, typename Compare >
  void BSTree< Key, Value, Compare >::insert(const Key &k, const Value &v) {
    insert(std::make_pair(k, v));
  }

  template< typename Key, typename Value, typename Compare >
  void BSTree< Key, Value, Compare >::erase(Iterator pos, const Key &k) {
    if (pos == end() || pos.constIter_.current == nullptr || pos.constIter_.current->data.first != k) {
      return;
    }
    root = drop(root, k);
  }

  template< typename Key, typename Value, typename Compare >
  std::pair< typename BSTree< Key, Value, Compare >::ConstIterator, typename BSTree< Key, Value, Compare >::ConstIterator >
  BSTree< Key, Value, Compare >::equal_range(const Key &k) const {
    ConstIterator it = find(k);
    if (it == end()) {
      return std::make_pair(end(), end());
    }
    ConstIterator next = it;
    ++next;
    return std::make_pair(it, next);
  }

  template< typename Key, typename Value, typename Compare >
  std::pair< typename BSTree< Key, Value, Compare >::Iterator, typename BSTree< Key, Value, Compare >::Iterator >
  BSTree< Key, Value, Compare >::equal_range(const Key &k) {
    Iterator it = find(k);
    if (it == end()) {
      return std::make_pair(end(), end());
    }
    Iterator next = it;
    ++next;
    return std::make_pair(it, next);
  }

  template< typename Key, typename Value, typename Compare >
  size_t BSTree< Key, Value, Compare >::count(const Key &k) const {
    return find(k) != end() ? 1 : 0;
  }

  template< typename Key, typename Value, typename Compare >
  template< typename F >
  F BSTree< Key, Value, Compare >::traverse_lnr(F f) const {
    if (!root) {
      return f;
    }

    Stack < Node * > stack;
    Node *current = root;

    while (!stack.empty() || current) {
      while (current) {
        stack.push(current);
        current = current->left;
      }
      current = stack.top();
      stack.pop();
      f(current->data);
      current = current->right;
    }

    return f;
  }

  template< typename Key, typename Value, typename Compare >
  template< typename F >
  F BSTree< Key, Value, Compare >::traverse_rnl(F f) const {
    if (!root) {
      return f;
    }

    Stack < Node * > stack;
    Node *current = root;

    while (!stack.empty() || current) {
      while (current) {
        stack.push(current);
        current = current->right;
      }
      current = stack.top();
      stack.pop();
      f(current->data);
      current = current->left;
    }

    return f;
  }

  template< typename Key, typename Value, typename Compare >
  template< typename F >
  F BSTree< Key, Value, Compare >::traverse_breadth(F f) const {
    if (!root) {
      return f;
    }

    Queue < Node * > queue;
    queue.push(root);

    while (!queue.empty()) {
      Node *current = queue.front();
      queue.pop();
      f(current->data);

      if (current->left) {
        queue.push(current->left);
      }
      if (current->right) {
        queue.push(current->right);
      }
    }

    return f;
  }
}

#endif
