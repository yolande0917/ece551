#include <algorithm>
#include <exception>
#include <iostream>

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
 private:
  class Node {
   public:
    T data;
    Node * left;
    Node * right;
    Node() {
      left = NULL;
      right = NULL;
    }
    Node(const T & t_) : data(t_), left(NULL), right(NULL) {}
  };

  Node * root;

 public:
  BstSet() : root(NULL) {}

  Node * addhelper(Node * current, const T & data) {
    if (current == NULL) {
      return new Node(data);
    }
    T currentD = current->data;
    if (currentD == data) {
      return current;
    }
    else if (data < currentD) {
      current->left = addhelper(current->left, data);
    }
    else {
      current->right = addhelper(current->right, data);
    }
    return current;
  }

  virtual void add(const T & key) { root = addhelper(root, key); }

  virtual bool contains(const T & key) const {
    Node * current = root;
    while (current != NULL) {
      T currentK = current->data;
      if (key == currentK) {
        return true;
      }
      else if (key < currentK) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    return false;
  }

  virtual void remove(const T & key) {
    // find the node to remove
    Node ** current = &root;
    // Node ** parent;
    while (*current != NULL) {
      T currentKey = (*current)->data;
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

  virtual ~BstSet() { deleteNode(root); }

  void copyTree(BstSet<T> & tree, Node * node) {
    if (node != NULL) {
      tree.add(node->data);
      copyTree(tree, node->left);
      copyTree(tree, node->right);
    }
  }

  BstSet(const BstSet<T> & rhs) : root(NULL) { copyTree(*this, rhs.root); }

  BstSet & operator=(const BstSet<T> & rhs) {
    if (this != &rhs) {
      BstSet<T> temp(rhs);
      std::swap(root, temp.root);
    }

    return *this;
  }

  void printhelper(Node * node) {
    if (node != NULL) {
      printhelper(node->left);
      std::cout << node->data << " ";
      printhelper(node->right);
    }
  }

  void printTree() {
    printhelper(root);
    std::cout << std::endl;
  }
};
