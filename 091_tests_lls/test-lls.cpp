#include <cassert>

#include "il.h"

void testList(void) {
  IntList list1;
  assert(list1.size == 0 && list1.getSize() == 0 && list1.head == NULL &&
         list1.tail == NULL);
  IntList list2 = IntList(list1);
  assert(list2.size == 0 && list2.getSize() == 0 && list2.head == NULL &&
         list2.tail == NULL);
  IntList list3 = list1;
  assert(list3.size == 0 && list3.getSize() == 0 && list3.head == NULL &&
         list1.tail == NULL);

  list1.addFront(1);  // 1
  assert(list1.size == 1 && list1.getSize() == 1 && list1.head->data == 1 &&
         list1.tail->data == 1 && list1.head->next == NULL && list1.head->prev == NULL &&
         list1.tail->prev == NULL && list1.tail->next == NULL);
  assert(list1[0] == 1);
  assert(list1.find(2) == -1 && list1.find(1) == 0);
  list2.addBack(1);  // 1
  assert(list2.size == 1 && list2.getSize() == 1 && list2.head->data == 1 &&
         list2.tail->data == 1 && list2.head->next == NULL && list2.head->prev == NULL &&
         list2.tail->prev == NULL && list2.tail->next == NULL);
  list1.addBack(2);  // 1 2
  assert(list1.size == 2 && list1.getSize() == 2 && list1.head->data == 1 &&
         list1.tail->data == 2 && list1.head->next->data == 2 &&
         list1.head->prev == NULL && list1.tail->prev->data == 1 &&
         list1.tail->next == NULL);
  assert(list1[0] == 1 && list1[1] == 2);
  assert(list1.find(5) == -1 && list1.find(2) == 1 && list1.find(1) == 0);
  list2.addFront(2);  // 2 1
  assert(list2.find(1) == 1);
  assert(list2.size == 2 && list2.getSize() == 2 && list2.head->data == 2 &&
         list2.tail->data == 1 && list2.head->next->data == 1 &&
         list2.head->prev == NULL && list2.tail->prev->data == 2 &&
         list2.tail->next == NULL);
  list2.~IntList();
  // assert(list2.find(1) == -1);
  // assert(list2.remove(2) == false);
  // assert(list2==NULL);
  list1.addBack(3);
  list1.addFront(0);  // 0 1 2 3
  assert(list1.size == 4 && list1.getSize() == 4 && list1.head->data == 0 &&
         list1.tail->data == 3 && list1.head->next->data == 1 &&
         list1.head->prev == NULL && list1.tail->prev->data == 2 &&
         list1.tail->next == NULL);
  list1.addBack(2);
  list1.addBack(1);  // 0 1 2 3 2 1
  assert(list1.find(0) == 0 && list1.find(1) == 1 && list1.find(2) == 2 &&
         list1.find(3) == 3);
  list3 = list1;
  assert(list3.size == 6 && list3.getSize() == 6 && list3.head->data == 0 &&
         list3.tail->data == 1 && list3.head->next->data == 1 &&
         list3.head->prev == NULL && list3.tail->prev->data == 2 &&
         list3.tail->next == NULL);
  assert(list3[0] == 0 && list3[1] == 1 && list3[2] == 2 && list3[3] == 3 &&
         list3[4] == 2 && list3[5] == 1);

  assert(list3.remove(5) == false && list3.remove(1) == true);  // 0 2 3 2 1
  assert(list3.getSize() == 5 && list3[0] == 0 && list3[1] == 2 && list3[2] == 3 &&
         list3[3] == 2 && list3[4] == 1);
  assert(list3.head->next->data == 2);
  assert(list3.remove(0) == true);  // 2 3 2 1
  assert(list3.head->data == 2);
  assert(list3.remove(2) == true);  // 3 2 1
  assert(list3.getSize() == 3 && list3[0] == 3 && list3[1] == 2 && list3[2] == 1);
  assert(list3.remove(1) == true);  // 3 2
  assert(list3.getSize() == 2 && list3.size == 2 && list3.head->data == 3 &&
         list3.tail->data == 2);
  assert(list3.find(1) == -1);
  assert(list3.find(3) == 0);
  assert(list3.tail->data == 2);
  assert(list3[0] == 3 && list3[1] == 2);
  list3[0] = list3[1] + 4;  // 6 2
  assert(list3[0] == 6);
  assert(list3.tail->data == 2);
  assert(list3.tail->prev->data == 6);
  assert(list3.remove(3) == false);
  assert(list3.remove(2) == true);  // 6
  assert(list3.size == 1);
  assert(list3[0] == 6);
  assert(list3.head->next == NULL && list3.tail->data == 6 && list3.head->data == 6 &&
         list3.head->prev == NULL && list3.tail->prev == NULL &&
         list3.tail->next == NULL);
  assert(list3.remove(6) == true);  //
  assert(list3.size == 0 && list3.getSize() == 0 && list3.head == NULL &&
         list3.tail == NULL);
}

int main(void) {
  testList();
  return EXIT_SUCCESS;
}
