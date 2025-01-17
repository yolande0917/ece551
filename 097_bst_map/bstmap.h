#include <algorithm>
#include <exception>
#include <iostream>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node() {
      left = NULL;
      right = NULL;
    }
    Node(const K & k_, const V & v_) : key(k_), value(v_), left(NULL), right(NULL) {}
  };

  Node * root;

 public:
  BstMap() : root(NULL) {}
  //explicit BstMap<K, V>(Node * n) : root(n) {}

  Node * addhelper(Node * current, const K & key, const V & value) {
    if (current == NULL) {
      return new Node(key, value);
    }
    K currentKey = current->key;
    if (currentKey == key) {
      current->value = value;
      return current;
    }
    else if (key < currentKey) {
      current->left = addhelper(current->left, key, value);
    }
    else {
      current->right = addhelper(current->right, key, value);
    }
    return current;
  }

  virtual void add(const K & key, const V & value) { root = addhelper(root, key, value); }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * current = root;
    while (current != NULL) {
      K currentKey = current->key;
      if (key == currentKey) {
        return current->value;
      }
      else if (key < currentKey) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    throw std::invalid_argument("No key found in map");
  }

  virtual void remove(const K & key) {
    // find the node to remove
    Node ** current = &root;
    // Node ** parent;
    while (*current != NULL) {
      K currentKey = (*current)->key;
      if (key == currentKey) {
        break;
      }
      else if (key < currentKey) {
        current = &(*current)->left;
      }
      else {
        current = &(*current)->right;
      }
    }
    if (*current == NULL) {
      return;
    }

    // remove node
    Node * temp;
    if ((*current)->left == NULL) {
      temp = *current;
      *current = (*current)->right;
      delete temp;
    }
    else if ((*current)->right == NULL) {
      temp = *current;
      *current = (*current)->left;
      delete temp;
    }
    else {
      // TODO
      temp = *current;
      Node ** node = current;
      current = &(*current)->right;
      while ((*current)->left != NULL && (*current)->right != NULL) {
        current = &(*current)->left;
      }
      Node * tomove = *current;
      if ((*current)->left == NULL) {
        *current = (*current)->right;
      }
      else {
        *current = (*current)->left;
      }

      *node = tomove;
      (*node)->left = temp->left;
      (*node)->right = temp->right;

      delete temp;
    }
  }

  void deleteNode(Node * current) {
    if (current == NULL) {
      return;
    }
    if (current->left == NULL && current->right == NULL) {
      delete current;
      return;
    }
    deleteNode(current->left);
    deleteNode(current->right);
    delete current;
  }

  virtual ~BstMap() { deleteNode(root); }

  void copyTree(BstMap<K, V> & tree, Node * node) {
    if (node != NULL) {
      tree.add(node->key, node->value);
      copyTree(tree, node->left);
      copyTree(tree, node->right);
    }
  }

  BstMap(const BstMap<K, V> & rhs) : root(NULL) { copyTree(*this, rhs.root); }

  BstMap & operator=(const BstMap<K, V> & rhs) {
    if (this != &rhs) {
      BstMap<K, V> temp(rhs);
      std::swap(root, temp.root);
    }

    return *this;
  }

  void printhelper(Node * node) {
    if (node != NULL) {
      printhelper(node->left);
      std::cout << node->key << ":" << node->value << " ";
      printhelper(node->right);
    }
  }

  void printTree() {
    printhelper(root);
    std::cout << std::endl;
  }
};
