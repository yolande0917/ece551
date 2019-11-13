#include "node.h"

#include <cassert>

void buildMapHelper(Node * node, BitString b, std::map<unsigned, BitString> & theMap) {
  if (node->sym != NO_SYM) {
    assert(node->left == NULL && node->right == NULL);
    theMap.insert(std::pair<int, BitString>(node->sym, b));
  }
  else {
    BitString bl = b.plusZero();
    buildMapHelper(node->left, bl, theMap);
    BitString br = b.plusOne();
    buildMapHelper(node->right, br, theMap);
  }
}

void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  buildMapHelper(this, b, theMap);
}
