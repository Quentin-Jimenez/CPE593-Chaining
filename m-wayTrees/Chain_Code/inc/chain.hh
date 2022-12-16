#include <stdint.h>
#include <string.h>
#include <fstream>

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
            int nodeIndexFlag;   // Keep track this nodes index--> for backtrace

            InternalNode *nextNode[M];
            InternalNode *parentNode;   //keeps track of previous node, used to update count
            LeafNode *nextLeaf[M];  // These are all null unless a leaf node

            friend class Chain;
        };

    public:
        InternalNode *root;

        Chain();  // Constructor
        ~Chain();                 // Destructor

        void readFile(ifstream &fileName);
        
        void printTree(); 

        InternalNode * countBacktrace(InternalNode * node);
        
        void remove(int pos);


        // Adjusts the value of the node
        LeafNode* fillnode(string line, LeafNode *node, bool isNewLeaf);
           
        void deleteLeafNodes(InternalNode **node);
        void insertBeginning(string line);



        // Inserts a value in the m-Way tree
        void insertEnd(string line);

        // Sets the value in the node
        InternalNode * setval(string line, InternalNode *node);

        // Split internal node to M internal nodes
        void splitNode(InternalNode *node);

        // Insert in the middle based on input position
        void insertMiddle(string line, int pos);
           
        // Splits the node
        InternalNode * splitEnd(string line, InternalNode *head);
};
          

