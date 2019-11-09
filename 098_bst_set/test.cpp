#include <cstdlib>
#include <iostream>

#include "bstset.h"
#include "set.h"

int main(void) {
  BstSet<int> tree;
  tree.add(20);
  tree.add(10);
  tree.add(31);
  tree.add(4);
  tree.add(1);
  tree.add(7);
  tree.add(16);
  tree.add(22);
  tree.add(28);
  tree.add(12);
  tree.add(40);
  tree.add(35);
  tree.add(42);
  std::cout << "Testing add\n";
  std::cout << "Expected: 1 4 7 10 12 16 20 22 28 31 35 40 42\n";
  tree.printTree();

  BstSet<int> tree1(tree);
  std::cout << "Testing copy constructor\n";
  tree1.printTree();

  std::cout << "Testing lookup\n";
  std::cout << "Key: 4, "
            << "Value: " << tree.contains(4) << std::endl;
  std::cout << "Key: 22, "
            << "Value: " << tree.contains(22) << std::endl;
  std::cout << "Key: 20, "
            << "Value: " << tree.contains(20) << std::endl;
  std::cout << "Key: 12, "
            << "Value: " << tree.contains(12) << std::endl;
  std::cout << "Key: 8, "
            << "Value: " << tree.contains(8) << std::endl;

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
