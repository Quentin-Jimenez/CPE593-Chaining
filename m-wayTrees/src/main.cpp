#include <stdint.h>
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
  /*class rootNode {
    internalNode* nextNode[M];
    uint32_t count[M] = {0};
    friend class Chain;
  };
  */
  internalNode* root;
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

  void showTree()
  {


  }

  void insertNonFull(string line)
  {
  }

  void splitChild()
  {
  }

  void traverse()
  {
  }


  void insertEnd(string line) {

      internalNode* temp = new internalNode();
      if (root == nullptr) {
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
              if (root->count[i] != 0) {
                  temp = root->nextNode[i];
                  break;
              }
          }


          uint32_t leafIndex = 0;
          bool insertComplete = false;


          internalNode* tmpInternalNode = new internalNode();

          while (!insertComplete) {
              if (temp->pointLeaf == true) {
                  // leafIndex = nextInternalNode->coun
                  for (int i = 0; i < M; i++) 
                  {
                      if (temp->count[i] < M) {
                          leafIndex = temp->count[i];
                          temp->nextLeaf[i]->lines[leafIndex] = line;
                          temp->nextLeaf[i]->isleaf = true;
                          temp->count[i] += 1;
                          leafIndex = 0;
                          insertComplete = true;
                          break;
                      }
                  }

              } else {
                  for (int i = M - 1; i >= 0; i--) {
                      if (temp->count[i] != 0) {
                          temp = temp->nextNode[i];
                          break;
                      }
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
    c.insertEnd(other);
    return 0;
}
