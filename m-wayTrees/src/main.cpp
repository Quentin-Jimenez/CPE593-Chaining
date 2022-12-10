#include <string.h>

#include <algorithm>
#include <iostream>

using namespace std;
const int M = 4;

class Chain {
 private:
  class leafNode {
    string lines[M];
    bool isleaf;
    friend class Chain;
  };
  class internalNode {
    leafNode* nextLeaf[M];
    internalNode* nextNode[M];
    uint32_t count[M];
    bool pointLeaf;
    // int flag;
    friend class Chain;
  };

  internalNode* root;
  // leafNode

 public:
  Chain() {
    for (int i = 0; i < M; i++) {
      root->nextLeaf[i] = nullptr;
      root->nextNode[i] = nullptr;
      root->count[i] = 0;
      root->pointLeaf = true;
    }
  }

  void insertEnd(string line) {
    if (root == nullptr) {
      leafNode* leaf = new leafNode();
      leaf->isleaf = true;
      leaf->lines[0] = line;
      root->nextNode[0] = nullptr;
      root->nextLeaf[0] = leaf;
      root->count[0] += 1;
    } else {
      for (int i = 0; i < M; i++) {
        while (root->nextNode[i] != nullptr)
          if (root->count[i] < M) {
          }
      }
    }
  }
};

int main() {
  Chain c;
  string str = "Hello, World!";
  string other = "Welcome aboard:";
  string another = "Lets go to LaLaLand.";
  c.insertEnd(str);
  return 0;
}