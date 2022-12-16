/* Source code for b-tree found at
 * https://www.geeksforgeeks.org/introduction-of-b-tree-2/ Code has been adapted
 * and modifed for the use of our chain project
 */

#include <string.h>

#include <algorithm>
#include <iostream>

using namespace std;

class Node {
 public:
  class LineKeyChar {
    int key;  // Key to insert into tree TBD maybe linenumber or pointer
    const char *line;  // Char * is a line from the text
    int offset;        // Offset in mempool

    friend class Node;
  };

  class LineKeyString {
    int key;
    string line;
    int offset;

    friend class Node;
  };

  // TODO:: asusming key is going to be lineNumber, this will most likely change
  // and will have to replace all
  // TODO:: May want to move some of this stuff to a C++ file for cleanliness :P
  Node(int minDegree, bool isLeaf)
      : minDegree(minDegree), isLeaf(isLeaf), numKeys(0) {
    keys =
        new LineKeyChar[ORDER_OF_N * minDegree - 1];  // TODO:: Check allocation
    childArr = new Node *[ORDER_OF_N * minDegree];
  }

  /* SETTERS AND GETTERS
   * ****************************************************************/
  void setLineKey(Node *node, int index, int lineNumber, int offset,
                  const char *line) {
    node->keys[index].key = lineNumber;
    node->keys[index].line = line;
    node->keys[index].offset = offset;
  }

  // void setLineKey(Node *node, int index, int lineNumber, int offset,
  //                 const string &) {
  //   // node->keys[index].key = lineNumber;
  //   // node->keys[index].line = string;
  // }
  void setLineKey(Node *node, int index, int lineNumber, int offset,
                  const string s) {
    node->keys[index].key = lineNumber;
    node->keys[index].line = s.c_str();
  }

  int getKey(Node *node, int index) { return node->keys[index].key; }

  const char *getLine(Node *node, int index) { return node->keys[index].line; }

  int getOffset(Node *node, int index) { return node->keys[index].offset; }

  /* FUNCTION CALLS
   * ********************************************************************/
  /* Once again these functions are from
   * https://www.geeksforgeeks.org/delete-operation-in-b-tree/ Some of the
   * functions are the same for the main b-tree functionalities. While others
   * are altered for the purpose of chain
   */

  int findKey(int lineNumber) {
    int pos = 0;
    while (pos < numKeys && keys[pos].key < lineNumber) ++pos;
    return pos;
  }

  void remove(int lineNumber) {
    int pos = findKey(lineNumber);

    if (pos < numKeys && keys[pos].key == lineNumber) {
      if (isLeaf) {
        removeFromLeaf(pos);
      } else {
        removeFromNonLeaf(pos);
      }

    } else {
      if (isLeaf)  // No key here
      {
        cout << "The key " << lineNumber << "  does not exist in the tree\n";
        return;
      }

      bool isKeyPresent = ((pos == numKeys) ? true : false);

      // Add to node if it has room where the key should be
      if (childArr[pos]->numKeys < minDegree) {
        fillChildNode(pos);
      }

      if (isKeyPresent && pos > numKeys) {
        childArr[pos - 1]->remove(lineNumber);
      } else {
        childArr[pos]->remove(lineNumber);
      }
    }
    return;
  }

  void removeFromLeaf(int pos) {
    for (int i = pos + 1; i < numKeys; ++i) {
      keys[i - 1] = keys[i];
    }

    numKeys--;
    return;
  }

  void removeFromNonLeaf(int pos) {
    int lineNumber = keys[pos].key;

    if (childArr[pos]->numKeys >= minDegree) {
      int prev = getPrevKey(pos);
      keys[pos].key = prev;
      keys[pos].line = getPrevLine(pos);
      childArr[pos]->remove(prev);
    } else if (childArr[pos + 1]->numKeys >= minDegree) {
      int next = getNextKey(pos);
      keys[pos].key = next;
      keys[pos].line = getNextLine(pos);
      childArr[pos + 1]->remove(next);
    } else {
      merge(pos);
      childArr[pos]->remove(lineNumber);
    }
    return;
  }

  // A function to get previous position
  int getPrevKey(int pos) {
    // Keep moving to the right most node until we reach a leaf
    Node *curNode = childArr[pos];

    // Indexing until isLeaf == true
    while (!curNode->isLeaf) {
      curNode = curNode->childArr[curNode->numKeys];
    }
    // Return the last key of the leaf
    return curNode->keys[curNode->numKeys - 1].key;
  }

  // Return line
  const char *getPrevLine(int pos) {
    // Keep moving to the right most node until we reach a leaf
    Node *curNode = childArr[pos];

    // Indexing until isLeaf == true
    while (!curNode->isLeaf) {
      curNode = curNode->childArr[curNode->numKeys];
    }
    // Return the last key of the leaf
    return curNode->keys[curNode->numKeys - 1].line;
  }

  int getNextKey(int pos) {
    // Keep moving the left most node starting from childArr[pos + 1] until we
    // reach a leaf
    Node *curNode = childArr[pos + 1];

    // Indexing left until isLeaf == true
    while (!curNode->isLeaf) {
      curNode = curNode->childArr[0];
    }
    // Return the first key of the leaf
    return curNode->keys[0].key;
  }

  // Return line
  const char *getNextLine(int pos) {
    // Keep moving the left most node starting from childArr[pos + 1] until we
    // reach a leaf
    Node *curNode = childArr[pos + 1];

    // Indexing left until isLeaf == true
    while (!curNode->isLeaf) {
      curNode = curNode->childArr[0];
    }
    // Return the first key of the leaf
    return curNode->keys[0].line;
  }

  void fillChildNode(int pos) {
    if (0 != pos && childArr[pos - 1]->numKeys >= minDegree) {
      borrowFromPrev(pos);
    } else if (numKeys != pos && childArr[pos + 1]->numKeys >= minDegree) {
      borrowFromNext(pos);
    } else {
      if (numKeys != pos) {
        merge(pos);
      } else {
        merge(pos - 1);
      }
    }
    return;
  }

  void borrowFromPrev(int pos) {
    Node *child = childArr[pos];
    Node *sibling = childArr[pos - 1];

    for (int i = child->numKeys - 1; i >= 0; i--)
      child->keys[i + 1] = child->keys[i];

    // If C[pos] is not a leaf, move all its child pointers one step ahead
    if (!child->isLeaf) {
      for (int i = child->numKeys; i >= 0; --i)
        child->childArr[i + 1] = child->childArr[i];
    }

    // Setting child's first key equal to keys[pos-1] from the current node
    child->keys[0] = keys[pos - 1];

    // Moving sibling's last child as C[pos]'s first child
    if (!child->isLeaf)
      child->childArr[0] = sibling->childArr[sibling->numKeys];

    // Moving the key from the sibling to the parent
    // This reduces the number of keys in the sibling
    keys[pos - 1] = sibling->keys[sibling->numKeys - 1];

    child->numKeys += 1;
    sibling->numKeys -= 1;

    return;
  }

  void borrowFromNext(int pos) {
    Node *child = childArr[pos];
    Node *sibling = childArr[pos + 1];

    // keys[pos] is inserted as the last key in C[pos]
    child->keys[(child->numKeys)] = keys[pos];

    // Sibling's first child is inserted as the last child
    // into C[pos]
    if (!(child->isLeaf))
      child->childArr[(child->numKeys) + 1] = sibling->childArr[0];

    // The first key from sibling is inserted into keys[pos]
    keys[pos] = sibling->keys[0];

    // Moving all keys in sibling one step behind
    for (int i = 1; i < sibling->numKeys; i++)
      sibling->keys[i - 1] = sibling->keys[i];

    // Moving the child pointers one step behind
    if (!sibling->isLeaf) {
      for (int i = 1; i <= sibling->numKeys; i++)
        sibling->childArr[i - 1] = sibling->childArr[i];
    }

    // Increasing and decreasing the key count of C[pos] and C[pos+1]
    // respectively
    child->numKeys += 1;
    sibling->numKeys -= 1;
    return;
  }

  // A function to merge childArr[pos] with childArr[pos + 1]
  // childArr[pos + 1] is freed after merging
  void merge(int pos) {
    Node *child = childArr[pos];
    Node *sibling = childArr[pos + 1];

    child->keys[minDegree - 1] = keys[pos];

    // Copying the keys from C[pos+1] to C[pos] at the end
    for (int i = 0; i < sibling->numKeys; ++i)
      child->keys[i + minDegree] = sibling->keys[i];

    // Copying the child pointers from C[pos+1] to C[pos]
    if (!child->isLeaf) {
      for (int i = 0; i <= sibling->numKeys; ++i)
        child->childArr[i + minDegree] = sibling->childArr[i];
    }

    for (int i = pos + 1; i < numKeys; ++i) keys[i - 1] = keys[i];

    // Moving the child pointers after (pos+1) in the current node one
    // step before
    for (int i = pos + 2; i <= numKeys; ++i) childArr[i - 1] = childArr[i];

    // Updating the key count of child and the current node
    child->numKeys += sibling->numKeys + 1;
    numKeys--;

    // Freeing the memory occupied by sibling
    delete (sibling);
    return;
  }

  void insertNonFull(int lineNumber, const char *line) {
    int index = numKeys - 1;

    if (true == isLeaf) {
      // Search for position to insert key
      while (index >= 0 && keys[index].key > lineNumber) {
        keys[index + 1] = keys[index];
        index--;
      }

      // Add key to the node
      keys[index + 1].key = lineNumber;
      keys[index + 1].line = line;
      numKeys += 1;
    } else {
      while (index >= 0 && keys[index].key > lineNumber) index--;

      // Check if the cild is full
      if (childArr[index + 1]->numKeys == 2 * minDegree - 1) {
        splitChild(index + 1, childArr[index + 1]);

        if (keys[index + 1].key < lineNumber) index++;
      }

      childArr[index + 1]->insertNonFull(lineNumber, line);
    }
  };

  // Split child of parameter node in case more space is needed
  void splitChild(int index, Node *node) {
    Node *newNode = new Node(node->minDegree, node->isLeaf);
    newNode->numKeys = minDegree - 1;

    for (int iter = 0; iter < minDegree - 1; iter++)
      newNode->keys[iter] = node->keys[iter + minDegree];

    if (!node->isLeaf) {
      for (int iter = 0; iter < minDegree; iter++)
        newNode->childArr[iter] = node->childArr[iter + minDegree];
    }

    node->numKeys = minDegree - 1;

    for (int iter = numKeys; iter >= index + 1; iter--)
      childArr[index + 1] = childArr[iter];

    childArr[index + 1] = newNode;

    for (int iter = numKeys - 1; iter >= index; iter--)
      keys[iter + 1] = keys[iter];

    keys[index] = node->keys[minDegree - 1];

    numKeys = numKeys + 1;
  };

  void traverseTree() {
    int treeIter;
    for (treeIter = 0; treeIter < numKeys; treeIter++) {
      if (false == isLeaf) {
        childArr[treeIter]->traverseTree();
      }
      // cout << " " << keys[treeIter].key << '\n';
      cout << " " << keys[treeIter].key << "->" << keys[treeIter].line << '\n';
    }

    // subtree of last child TODO:: Test with <= above so we dont have to do
    // this
    if (false == isLeaf) childArr[treeIter]->traverseTree();
  };

  Node *searchTree(int lineNumber)
  // TODO:: Do we want to search by line number or word?
  {
    int treeIter = 0;

    while (treeIter < numKeys && lineNumber > keys[treeIter].key) treeIter++;

    // Key is found yay -> return the node
    if (keys[treeIter].key == lineNumber) return this;

    // At a leaf so we couldn't fine it return null
    if (isLeaf) return nullptr;

    // Search the next child
    return childArr[treeIter]->searchTree(lineNumber);
  }

 private:
  const int ORDER_OF_N = 2;
  LineKeyChar *keys;
  int minDegree;
  bool isLeaf;  // Is node a leaf. If yes -> true
  int numKeys;
  Node **childArr;  // Array of child ptrs

  friend class Chain;
};
