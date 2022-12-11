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
    uint32_t count[M] = {0};
    bool pointLeaf;
    // int flag;
    friend class Chain;
  };
  class rootNode {
    internalNode* nextNode[M];
    uint32_t count[M] = {0};
    friend class Chain;
  };
  rootNode* root;
  // leafNode

 public:
  Chain() : root(nullptr) {}

  void setLeaf(string line, int pos, leafNode* leaf) {
    leaf->isleaf = true;
    leaf->lines[pos] = line;
  }

  void setInternalNodePointingNode(internalNode* inode) {
    if (inode->nextNode != nullptr) {
      inode->pointLeaf = false;
    }
  }
  void setInternalNodePointingLeaf(internalNode* inode) {
    if (inode->nextNode == nullptr) {
      inode->pointLeaf = true;
    }
  }

  void insertEnd(string line) {
    // internalNode* temp = new internalNode;
    if (root == nullptr) {
      rootNode* temp = new rootNode();
      internalNode* inode = new internalNode();
      leafNode* leaf = new leafNode();
      setLeaf(line, 0, leaf);
      // leaf->isleaf = true;
      // leaf->lines[0] = line;
      temp->nextNode[0] = inode;
      inode->nextLeaf[0] = leaf;
      inode->pointLeaf = true;
      temp->count[0] += 1;
      inode->count[0] += 1;
      root = temp;
    } else {
      // to get hold of the last available block
      for (int i = M - 1; i >= 0; i--) {
        while (root->nextNode[i] != nullptr)
          if (root->count[i] < M) {
            for (int j = 0; j < M; j++) {
            }
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
  string yetanother = "Lets go to LaLaLand, again";

  c.insertEnd(str);
  return 0;
}