#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>
#include <utility>

//YOUR CODE GOES HERE
template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    explicit Node(T d) : data(d), next(NULL), prev(NULL) {}
    Node(T d, Node * n, Node * p) : data(d), next(n), prev(p) {}
  };

  Node * head;
  Node * tail;
  int size;

  class IndexException : public std::exception {
    const char * what() { return "Index out of bound"; }
  };

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}

  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
  }

  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    size++;
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
  }

  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    size++;
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
  }

  bool remove(const T & item) {
    Node * curr = head;
    while (curr != NULL) {
      if (curr->data == item) {
        // remove

        // if is head
        if (curr->prev == NULL) {
          head = curr->next;
        }
        else {
          curr->prev->next = curr->next;
        }
        // if is tail
        if (curr->next == NULL) {
          tail = curr->prev;
        }
        else {
          curr->next->prev = curr->prev;
        }

        delete curr;

        size--;
        return true;
      }
      curr = curr->next;
    }
    return false;
  }

  T & operator[](int index) {
    if (index < 0 || (index > size - 1)) {
      throw IndexException();
    }
    Node * curr = head;
    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }
    return curr->data;
  }

  const T & operator[](int index) const {
    if (index < 0 || (index > size - 1)) {
      throw IndexException();
    }
    Node * curr = head;
    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }
    return curr->data;
  }

  int find(const T & item) const {
    Node * curr = head;
    int ind = -1;
    while (curr != NULL) {
      ind++;
      if (curr->data == item) {
        return ind;
      }
      curr = curr->next;
    }
    return -1;
  }

  int getSize() const { return size; }

  LinkedList(const LinkedList<T> & rhs) : head(NULL), tail(NULL), size(0) {
    int n = rhs.getSize();
    while (n > 0) {
      addFront(rhs[n - 1]);
      n--;
    }
  }

  LinkedList & operator=(const LinkedList<T> & rhs) {
    if (this != &rhs) {
      LinkedList<T> temp(rhs);

      // swap
      std::swap(head, temp.head);
      std::swap(tail, temp.tail);
      int n = size;
      size = temp.size;
      temp.size = n;
    }

    /******
    while (head != NULL) {
      Node * t = head->next;
      delete head;
      head = t;
    }

    int n = rhs.getSize();
    while (n > 0) {
      addFront(rhs[size - 1]);
      n--;
    }
    *******/
    return *this;
  }

  friend void testList(void);
};

#endif
