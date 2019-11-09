#include <cstdlib>
#include <iostream>

#include "bstmap.h"
#include "map.h"

int main(void) {
  BstMap<int, int> tree;
  tree.add(20, 120);
  tree.add(10, 110);
  tree.add(31, 131);
  tree.add(4, 14);
  tree.add(1, 11);
  tree.add(7, 17);
  tree.add(16, 160);
  tree.add(22, 122);
  tree.add(28, 128);
  tree.add(12, 112);
  tree.add(40, 140);
  tree.add(35, 135);
  tree.add(42, 142);
  std::cout << "Testing add\n";
  std::cout << "Expected: 1 4 7 10 12 16 20 22 28 31 35 40 42\n";
  tree.printTree();

  BstMap<int, int> tree1(tree);
  std::cout << "Testing copy constructor\n";
  tree1.printTree();

  std::cout << "Testing lookup\n";
  std::cout << "Key: 4, "
            << "Value: " << tree.lookup(4) << std::endl;
  std::cout << "Key: 22, "
            << "Value: " << tree.lookup(22) << std::endl;
  std::cout << "Key: 20, "
            << "Value: " << tree.lookup(20) << std::endl;
  std::cout << "Key: 12, "
            << "Value: " << tree.lookup(12) << std::endl;
  //std::cout << "Key: 8, "
  //       << "Value: " << tree.lookup(8) << std::endl;

  std::cout << "Testing remove\n";
  tree.remove(1);
  std::cout << "Remove 1\n";
  tree.printTree();
  tree.remove(16);
  std::cout << "Remove 16\n";
  tree.printTree();
  tree.remove(4);
  std::cout << "Remove 4\n";
  tree.printTree();
  tree.remove(31);
  std::cout << "Remove 31\n";
  tree.printTree();
  tree.remove(20);
  std::cout << "Remove 20\n";
  tree.printTree();

  std::cout << "Testing assignment\n";
  tree1 = tree;
  tree1.printTree();
  return EXIT_SUCCESS;
}
