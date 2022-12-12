#include <stdint.h>
#include <string.h>

#include <iostream>
#include <cmath>

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
    InternalNode *parentNode;   //keeps track of previous node, used to update count
    LeafNode *nextLeaf[M];  // These are all null unless a leaf node

    friend class Chain;
  };

 public:
  InternalNode *root;

  Chain() : root(nullptr){};  // Constructor
  ~Chain(){};                 // Destructor

  void printTree() {

      for(int q = 0; q < M; q++)
        cout << root->count[q] << endl;

      cout << "Leaf Count" << root->nextNode[1]->count[0] << endl;
      cout << "Leaf Count" << root->nextNode[1]->count[1] << endl;

      
      for(int k = 0; k < M; k++)
      {
          cout << "Node: " << k << endl;
          cout << "Top node count " << root->count[k] << endl;
          for(int m = 0; m < M; m++)
          {
              cout << "Leaf Node: " << m << endl;
              cout << "Count " << root->nextNode[k]->count[m] << endl;
              for(int i = 0; i < M; i++)
              {
                  cout << root->nextNode[k]->nextLeaf[m]->lines[i];
              }
              cout << endl;
          }
          cout << endl;
      }
      

      cout << endl;
  }

  InternalNode * countBacktrace(InternalNode * node, int index)
  {
      int newCount = 0; 
      int firstBack = true;

      while(1)
      {
          if(node->parentNode == nullptr)
          {
              break;
          }

          
          if(node->isLeafNode)
          {
              for(int i = 0; i < M; i++)
              {
                  if(node->nextLeaf[i] != nullptr)
                  {
                      newCount += node->nextLeaf[i]->count;
                  }
              }
          }
          else
          {
              if(firstBack != true)
              {
                index = 3;
              }
              else
              {
                  firstBack = false;
              }

              for(int i = 0; i < M; i++)
              {
                  newCount += node->count[i];
              }
          }

          node = node->parentNode;
          for(int j = index; j < M; j++)
          {
              cout << " J " << j << endl;
              // Update the entire count array
              if( j == 0)
              {
                  node->count[j] = newCount;
                  break;
              }

              // Count[i] equals how many lines are in the node plus the previous nodes count
              node->count[j] = newCount + node->count[j-1];

              // Only need to update the next few nodes if they are not zero
              if( j != 3 && node->count[j+1] == 0)
              {
                  break;
              }
          }
          newCount = 0;
      }

      return node;
  }
 
  // Adjusts the value of the node
  LeafNode* fillnode(string line, LeafNode *node, bool isNewLeaf) {
      // Update counter to add a leaf and insert line
      int leafIndex;
      if (isNewLeaf) {
          leafIndex = 0;
      } else {
          leafIndex = node->count;
      }

      node->lines[leafIndex] = line;
      node->count += 1;

      return node;
  }

  void deleteLeafNodes(InternalNode *node) {
      for (int i = 0; i < M; i++) {
          delete[] node->nextLeaf[i];
      }
  }

  // Inserts a value in the m-Way tree
  void insertEnd(string line)
  {
      setval(line, root, nullptr, false, 0);
  }

  // Sets the value in the node
  void setval(string line, InternalNode *node, InternalNode **prevNode, bool isPrevSet, int prevIndex) 
  {

      // if node is null
      if (node == NULL) {
          InternalNode *newRoot = new InternalNode();
          LeafNode *leafNode = new LeafNode();
          leafNode->lines[0] = line;
          leafNode->count = 1;
          newRoot->isLeafNode = true;
          newRoot->count[0] = 1;
          newRoot->parentNode = nullptr;
          newRoot->nextLeaf[0] = leafNode;
          root = newRoot;
      }
      else {

          //Check if node points to leaf, if it doesn't recursively call and go to last possible node

          if(!isPrevSet)
          {
              prevNode = &root;
              isPrevSet = true;
          }

          if(node->isLeafNode)
          {
              int isNodeFull = true;
              for(int index = 0; index < M; index++)
              {
                  if(node->count[index] < M)
                  {

                      cout << "Previous index" << prevIndex <<endl;
                      if(node->nextLeaf[index] == nullptr)
                      {
                          LeafNode *newLeaf = new LeafNode();
                          newLeaf = fillnode(line, newLeaf, true );
                          node->nextLeaf[index] = newLeaf;
                          node->count[index] = 1;
                          countBacktrace(node, prevIndex);
                          return;
                      }

                      node->nextLeaf[index] = fillnode(line, node->nextLeaf[index], false);
                      countBacktrace(node, prevIndex);

                      node->count[index] += 1;

                      return;
                  }
              }

              if(isNodeFull)
              {
                  splitEnd(line, &node);
                  countBacktrace(node->nextNode[0], 0);
                  countBacktrace(node->nextNode[1], 1);
                  *prevNode = node;

                  return;
              }
          }
          else {

              // keep track of last node
              *prevNode = node;

              for(int nodeIndex = 0; nodeIndex < M;  nodeIndex++)
              {
                  // Check for the last node that is populated and go to that node
                  cout << "Node count check " << node->count[nodeIndex] << endl;
                  if(node->count[nodeIndex] % 16 > 0 || node->count[nodeIndex] == 0)
                  {
                      //TODO may need to pass index to this
                      cout << "Index is " << nodeIndex<< endl; 
                      setval(line, node->nextNode[nodeIndex], prevNode, isPrevSet, nodeIndex);
                      return;
                  }
              }

              // Only reaches this point if all nodes are full. We then go down to next level from the last node
              // This only works for insert end
              setval(line, node->nextNode[3], prevNode, isPrevSet, 3);
              return;

          }
      }
  }


  // Splits the node
  void splitEnd(string line, InternalNode **head)
  {

      InternalNode *newNodeOne = new InternalNode();
      InternalNode *newNodeTwo = new InternalNode();
      InternalNode *newNodeThree = new InternalNode();
      InternalNode *newNodeFour = new InternalNode();


      InternalNode *tempHeadNode = new InternalNode();
      LeafNode *newLeaf = new LeafNode();

      //TODO hardcoded for M = 4. Will need to change this
      newNodeOne = *head;
      newNodeOne->isLeafNode = true;

      fillnode(line, newLeaf, true);
      newNodeTwo->nextLeaf[0] = newLeaf;
      newNodeTwo->isLeafNode = true;
      newNodeTwo->count[0] = 1;
      newNodeTwo->parentNode = tempHeadNode;

      newNodeThree->isLeafNode = true;
      newNodeThree->parentNode = tempHeadNode;
      newNodeFour->isLeafNode = true;
      newNodeFour->parentNode = tempHeadNode;

      tempHeadNode->isLeafNode = false;
      tempHeadNode->nextNode[0] = newNodeOne;
      tempHeadNode->count[0] = 16;
      tempHeadNode->nextNode[1] = newNodeTwo;
      tempHeadNode->count[1] = 1;
      tempHeadNode->nextNode[2] = newNodeThree;
      tempHeadNode->nextNode[3] = newNodeFour;

      *head = tempHeadNode;

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
    c.insertEnd(other);
    c.insertEnd(another);
    c.insertEnd(yetanother);
    c.insertEnd(str);
    c.insertEnd(other);
    c.insertEnd(another);
    c.insertEnd(yetanother);
    c.insertEnd(str);
    c.insertEnd(other);
    c.insertEnd(another);
    c.insertEnd(yetanother);

    
    string thisNew = " Tryhing to split";
    c.insertEnd(thisNew);
    string extrastring = "Please work";
    c.insertEnd(extrastring);
    c.insertEnd(str);

    
    for(int i = 0; i < 43; i++)
    {
        c.insertEnd(extrastring);
    }
    c.insertEnd(another);
    c.insertEnd(yetanother);
    
    c.printTree();
    return 0;
}
