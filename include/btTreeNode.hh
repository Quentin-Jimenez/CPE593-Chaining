/* Source code for b-tree found at https://www.geeksforgeeks.org/introduction-of-b-tree-2/
 * Code has been adapted and modifed for the use of our chain project
*/

#include <iostream>

using namespace std;

class Node 
{
    private:
        const int ORDER_OF_N = 4;
        int *keys;
        int minDegree;  
        bool isLeaf;  // Is node a leaf. If yes -> true
        int numKeys;
        Node **childArr; // Array of child ptrs

    public:

        //TODO:: May want to move some of this stuff to a C++ file for cleanliness :P
        Node(int minDegree, bool isLeaf) : minDegree(minDegree), isLeaf(isLeaf), numKeys(0)
        {
            keys = new int[ORDER_OF_N * minDegree - 1];
            childArr = new Node*[ORDER_OF_N * minDegree];
        }

        void traverseTree()
        {
            int treeIter;
            for(treeIter = 0; treeIter < numKeys; treeIter++)
            {
                if(false == isLeaf)
                {
                    childArr[treeIter]->traverseTree();
                }
            }

            //subtree of last child TODO:: Test with <= above so we dont have to do this
            if(false == isLeaf) childArr[treeIter]->traverseTree();
        };

        Node* searchTree(int lineNumber) // TODO:: Do we want to search by line number or word?
        {
            int treeIter;

            while( treeIter < numKeys && lineNumber > keys[treeIter]) treeIter++;

            // Key is found yay -> return the node
            if(keys[treeIter] == lineNumber) return this;

            // At a leaf so we couldn't fine it return null
            if(isLeaf) return nullptr;

            // Search the next child
            return childArr[treeIter]->searchTree(lineNumber);
        } 
                                         
        friend class Chain;
};

