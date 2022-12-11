#include <stdint.h>
#include <string.h>
#include <iostream>

using namespace std;
const int M = 4;

class Chain 
{
    private:
    class LeafNode {
        uint32_t count;  // Number of leafs occupied
        string lines[M]; //Array of lines up to M
        
        friend class Chain;
    };

    class InternalNode {
        bool isLeafNode;  // Is this node pointed to a leaf
        int count[M];  // Tracks the number of leaves below 

        InternalNode *nextNode[M];
        LeafNode *nextLeaf[M];   // These are all null unless a leaf node

        friend class Chain;
    };

    public:

    InternalNode *root;

    Chain() : root(nullptr) {};  //Constructor
    ~Chain() {};                //Destructor

    // Searches value in the node
    /*struct node* search(int val, InternalNode *root, int* pos)
    {

        // if root is Null then return
        if (root == NULL)
            return NULL;
        else {

            // if node is found
            if (searchnode(val, root, pos))
                return root;

            // if not then search in child nodes
            else
                return search(val,
                        root->child[*pos],
                        pos);
        }
    }

    // Searches the node
    int searchnode(int val,
            struct node* n,
            int* pos)
    {
        // if val is less than node->value[1]
        if (val < n->value[1]) {
            *pos = 0;
            return 0;
        }

        // if the val is greater
        else {
            *pos = n->count;

            // check in the child array
            // for correct position
            while ((val < n->value[*pos])
                    && *pos > 1)
                (*pos)--;
            if (val == n->value[*pos])
                return 1;
            else
                return 0;
        }
    }
    */

    // Inserts a value in the m-Way tree
    void insertEnd(string line)
    {
        string i;
        InternalNode *child, *n;
        int flag;

        // Function setval() is called which
        // returns a value 0 if the new value
        // is inserted in the tree, otherwise
        // it returns a value 1
        flag = setval(line, root, &i, &child);
    }

    // Sets the value in the node
    int setval(string line, InternalNode* node, string *p, InternalNode **child)
    {
        int k = 0;

        // if node is null
        if (node == NULL) {
            *p = line;
            *child = NULL;
            return 1;
        }
        else {

            //Check if node points to leaf, if it doesn't recursively call and go to last possible node
            if(node->isLeafNode)
            {
                
                int isNodeFull = true;
                for(int index = 0; index < M; index++)
                {
                    if(node->count[index] < M)
                    {
                        fillnode(line, node->nextLeaf[index]);
                        return 1;
                        
                    }
                }

                if(isNodeFull)
                {
                    //split(*p, *child, node, k, p, child);
                    return 0;
                }
                
            }
            else {
                
                for(int index = M - 1; index >= 0;  index--)
                {
                    // Check for the last node that is populated and go to that node
                    if(node->count[index] > 0)
                    {
                        setval(line, node->nextNode[index], p, child);
                    }
                }
            }
        }
        return 0;
    }

    // Adjusts the value of the node
    void fillnode(string line, LeafNode* node)
    {

        // Update counter to add a leaf and insert line
        int leafIndex = node->count;
        node->lines[leafIndex] = line;
        node->count += 1;
    }

    // Splits the node
    /*void split(int val,
            struct node* c,
            struct node* n,
            int k, int* y,
            struct node** newnode)
    {
        int i, mid;
        if (k <= MIN)
            mid = MIN;
        else
            mid = MIN + 1;

        // Allocating the memory for a new node
        *newnode = new node();

        for (i = mid + 1; i <= MAX; i++) {
            (*newnode)->value[i - mid] = n->value[i];
            (*newnode)->child[i - mid] = n->child[i];
        }

        (*newnode)->count = MAX - mid;
        n->count = mid;

        // it checks whether the new value
        // that is to be inserted is inserted
        // at a position less than or equal
        // to minimum values required in a node
        if (k <= MIN)
            fillnode(val, c, n, k);
        else
            fillnode(val, c, *newnode, k - mid);

        *y = n->value[n->count];
        (*newnode)->child[0] = n->child[n->count];
        n->count--;
    }
    */

};

int main() {
    Chain c;
    string str = "Hello, World!";
    string other = "Welcome aboard:";
    string another = "Lets go to LaLaLand.";
    string yetanother = "Lets go to LaLaLand, again";


    c.insertEnd(str);
    cout << "Here" << endl;
    c.insertEnd(other);
    c.insertEnd(another);
    c.insertEnd(yetanother);
    c.insertEnd(str);
    c.insertEnd(another);
    return 0;
}

