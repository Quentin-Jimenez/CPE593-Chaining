#include <stdint.h>
#include <string.h>

#include <iostream>

using namespace std;
const int M = 4;

class Chain {
 private:
  class LeafNode {
    uint32_t count;   // Number of leafs occupied
    string lines[M];  // Array of lines up to M

    friend class Chain;
  };

  class InternalNode {
    bool isLeafNode;     // Is this node pointed to a leaf
    int count[M] = {0};  // Tracks the number of leaves below

    InternalNode *nextNode[M];
    LeafNode *nextLeaf[M];  // These are all null unless a leaf node

    friend class Chain;
  };

 public:
  InternalNode *root;

  Chain() : root(nullptr){};  // Constructor
  ~Chain(){};                 // Destructor

  void printTree() {
    cout << root->nextLeaf[0]->lines[0];
    cout << root->nextLeaf[0]->lines[1];
    cout << root->nextLeaf[0]->lines[2];
    cout << root->nextLeaf[0]->lines[3];
    cout << endl;
    cout << root->nextLeaf[1]->lines[0];
    cout << root->nextLeaf[1]->lines[1];
    cout << root->nextLeaf[1]->lines[2];
    cout << root->nextLeaf[1]->lines[3];
    cout << endl;
    cout << root->nextLeaf[2]->lines[0];
    cout << root->nextLeaf[2]->lines[1];
    cout << root->nextLeaf[2]->lines[2];
    cout << root->nextLeaf[2]->lines[3];
    cout << endl;
    cout << root->nextLeaf[3]->lines[0];
    cout << root->nextLeaf[3]->lines[1];
    cout << root->nextLeaf[3]->lines[2];
    cout << root->nextLeaf[3]->lines[3];
    cout << endl;

    // cout << root->nextNode[0]->nextLeaf[0]->lines[0];
  }
  // Split internal node to M internal nodes
  void splitNode(InternalNode *node) {
    InternalNode *temp = new InternalNode();
    InternalNode *newNode;
    temp->isLeafNode = false;
    if (node->isLeafNode == true) {
      for (int i = 0; i < M; i++) {
        newNode = new InternalNode();
        temp->nextNode[i] = newNode;
      }
    }
    // Copy lines and update counts
    temp->nextNode[0] = node;
    node = temp;
  }
  void insertMiddle(string line, int pos) {
    InternalNode *currNode = root;
    LeafNode *currLeaf;
    int currNodeIndex;
    int tempCount = 0;  // keeps the count of the the roots
    for (int i = 0; i < M; i++) {
      tempCount += currNode->count[i];
      if (tempCount > pos) {
        // insert in this node
        currNodeIndex = i;
        break;
      }
    }
    if (currNode->isLeafNode == true) {
      currLeaf = currNode->nextLeaf[currNodeIndex];
    }
    int currLeafIndex = (pos % M) - 1;  // to adjust 0 index
    // Shift everything one place to the right
    // assuming last leafnode is empty
    for (int j = M - 2; j >= currLeafIndex; j--) {
      if (currLeaf->lines[j] != "") {
        currLeaf->lines[j + 1] = currLeaf->lines[j];
      }
    }
    currLeaf->lines[currLeafIndex] = line;
    currLeaf->count += 1;
  }

  // Inserts a value in the m-Way tree
  void insertEnd(string line) {
    string i;
    InternalNode *child, *n;
    int flag;

    setval(line, root, &i, &child);
  }

  // Sets the value in the node
  void setval(string line, InternalNode *node, string *p,
              InternalNode **child) {
    int k = 0;

    // if node is null
    if (node == NULL) {
      InternalNode *newRoot = new InternalNode();
      LeafNode *leafNode = new LeafNode();
      leafNode->lines[0] = line;
      leafNode->count = 1;
      newRoot->isLeafNode = true;
      newRoot->count[0] = 1;
      newRoot->nextLeaf[0] = leafNode;
      root = newRoot;
      return;
    } else {
      // Check if node points to leaf, if it doesn't recursively call and go to
      // last possible node
      if (node->isLeafNode) {
        int isNodeFull = true;
        for (int index = 0; index < M; index++) {
          if (node->count[index] < M) {
            if (node->nextLeaf[index] == nullptr) {
              LeafNode *newLeaf = new LeafNode();
              node->nextLeaf[index] = newLeaf;
              node->count[index] = 1;
              fillnode(line, node->nextLeaf[index], true);
              return;
            }

            fillnode(line, node->nextLeaf[index], false);
            node->count[index] += 1;
            return;
          }
        }

        if (isNodeFull) {
          cout << "In split" << endl;
          splitEnd(line, node);
          return;
        }
      } else {
        for (int index = M - 1; index >= 0; index--) {
          // Check for the last node that is populated and go to that node
          if (node->count[index] > 0) {
            setval(line, node->nextNode[index], p, child);
          }
        }
      }
    }
    return;
  }

  // Adjusts the value of the node
  void fillnode(string line, LeafNode *node, bool isNewLeaf) {
    // Update counter to add a leaf and insert line
    int leafIndex;
    if (isNewLeaf) {
      leafIndex = 0;
    } else {
      leafIndex = node->count;
    }

    cout << leafIndex << endl;

    node->lines[leafIndex] = line;
    node->count += 1;
  }

  void testSplit() {
    InternalNode *currNode = root;
    splitNode(root);
  }

  void deleteLeafNodes(InternalNode *node) {
    for (int i = 0; i < M; i++) {
      delete[] node->nextLeaf[i];
    }
  }

  // Splits the node
  void splitEnd(string line, InternalNode *head) {
    InternalNode *newNodeLeft = new InternalNode();
    InternalNode *newNodeRight = new InternalNode();
    InternalNode *tempHeadNode = new InternalNode();
    LeafNode *newLeaf = new LeafNode();

    // TODO hardcoded for M = 4. Will need to change this
    newNodeLeft = head;

    fillnode(line, newLeaf, true);
    newNodeRight->nextLeaf[0] = newLeaf;
    newNodeRight->isLeafNode = true;
    newNodeRight->count[0] = 1;

    tempHeadNode->isLeafNode = false;
    tempHeadNode->nextNode[0] = newNodeLeft;
    tempHeadNode->nextNode[1] = newNodeRight;

    deleteLeafNodes(tempHeadNode);

    head = tempHeadNode;
    cout << endl;
    cout << "Test" << head->nextNode[0]->nextLeaf[0]->lines[0] << endl;
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
  c.insertEnd(another);
  c.insertEnd(yetanother);
  c.insertEnd(str);
  c.insertEnd(another);

  c.insertMiddle("Hey", 5);
  c.insertMiddle("there", 5);
  c.testSplit();
  // c.insertEnd(other);
  // c.insertEnd(yetanother);
  // c.insertEnd(str);
  // c.insertEnd(another);
  // c.insertEnd(other);
  // c.insertEnd(yetanother);
  // c.insertEnd(str);
  // c.insertEnd(other);
  // c.insertEnd(another);
  // c.insertEnd(yetanother);

  // string thisNew = " Tryhing to split";
  // c.insertEnd(thisNew);

  // c.printTree();
  return 0;
}
