/* Source code for b-tree found at https://www.geeksforgeeks.org/introduction-of-b-tree-2/
 * Code has been adapted and modifed for the use of our chain project
*/

#include <algorithm>
#include <iostream>

using namespace std;


class Node 
{
        public:

        class LineKey
        {
            int key;       // Key to insert into tree TBD maybe linenumber or pointer
            char* line;    // Char * is a line from the text
            int offset;    // Offset in mempool

            friend class Node;
        };

        //TODO:: asusming key is going to be lineNumber, this will most likely change and will have to replace all
        //TODO:: May want to move some of this stuff to a C++ file for cleanliness :P
        Node(int minDegree, bool isLeaf) : minDegree(minDegree), isLeaf(isLeaf), numKeys(0)
        {
            keys = new LineKey[ORDER_OF_N * minDegree - 1];  //TODO:: Check allocation
            childArr = new Node*[ORDER_OF_N * minDegree];
        }

        void setLineKey(Node *node, int index, int lineNumber, int offset, char *line)
        {
            node->keys[index].key = lineNumber;
            //node->keys[index].line = string;
            //node->keys[index].offset = offest;
        }

        int getKey(Node *node, int index)
        {
            return node->keys[index].key;
        }

        int getLine(Node *node, int index, int lineNumber)
        {
        }

        int getOffset(Node *node, int index)
        {
            return node->keys[index].offset;
        }

        void insertNonFull(int lineNumber)
        {
            int index = numKeys - 1;

            if(true == isLeaf)
            {   
                // Search for position to insert key
                while(index >= 0 && keys[index].key > lineNumber)
                {
                    keys[index + 1] = keys[index];
                    index--;
                }

                // Add key to the node
                keys[index + 1].key = lineNumber; 
                numKeys += 1;
            }
            else
            {
                while(index >= 0 && keys[index].key > lineNumber) index--;
                
                // Check if the cild is full
                if(childArr[index + 1]->numKeys == 2*minDegree - 1)
                {
                    splitChild(index + 1, childArr[index + 1]);
                }

                if(keys[index + 1].key < lineNumber) index++;

                childArr[index + 1]->insertNonFull(lineNumber, line);
            }
        };

        // Split child of parameter node in case more space is needed
        void splitChild(int index, Node *node)
        {
            Node *newNode = new Node(node->minDegree, node->isLeaf);
            newNode->numKeys = minDegree - 1;

            for(int iter = 0; iter < minDegree - 1; iter++) newNode->keys[iter] = node->keys[iter + minDegree];

            if(!node->isLeaf)
            {
                for(int iter = 0; iter < minDegree; iter++) newNode->childArr[iter] = node->childArr[iter + minDegree];
            }

            node->numKeys = minDegree - 1;

            for(int iter = numKeys; iter >= index + 1; iter--) childArr[index + 1] = childArr[iter];

            childArr[index + 1] = newNode;

            for(int iter = numKeys - 1; iter >= index; iter--) keys[iter + 1] = keys[iter];

            keys[index] = node->keys[minDegree - 1];

            numKeys = numKeys + 1;
        };


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

            while( treeIter < numKeys && lineNumber > keys[treeIter].key) treeIter++;

            // Key is found yay -> return the node
            if(keys[treeIter].key == lineNumber) return this;

            // At a leaf so we couldn't fine it return null
            if(isLeaf) return nullptr;

            // Search the next child
            return childArr[treeIter]->searchTree(lineNumber);
        } 

        private:
        
        const int ORDER_OF_N = 4;
        LineKey *keys;
        int minDegree;  
        bool isLeaf;  // Is node a leaf. If yes -> true
        int numKeys;
        Node **childArr; // Array of child ptrs
                                         
        friend class Chain;
};

