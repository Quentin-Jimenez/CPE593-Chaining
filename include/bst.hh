/* Source code for b-tree found at https://www.geeksforgeeks.org/introduction-of-b-tree-2/
 * Code has been adapted and modifed for the use of our chain project
 *
*/

#include "btTreeNode.hh"

using namespace std;

class Chain // Chain is implemented using a b-tree
{
    private:
        Node *root; 
        int minDegree;

    public:

        Chain(int minDegree) : root(nullptr), minDegree(minDegree){};
        //TODO:: Chain(unsigned int, const string&)
        //TODO:: Chain(unsighned int, const Rope&)

        ~Chain(void) {} ; //TODO:; Implement destructor


        Node *searchTree(int lineNumber) // TODO:: Need to figure out what we search by
        {
            if(nullptr == root) 
            {
                return nullptr;   //Key was not found
            }
            else
            {
                root->searchTree(lineNumber); // Keep searching
            }
        }

        /* All this function is dooing is going from node to node until reaching the end of tree */
        void traverseTree()
        {
            if( nullptr != root) { root->traverseTree();}
        }


        //TODO: implmenet insert for string type
        /* void insert(int lineNumber, const string&)
        {
            if(nullptr == root)
            {
                int offset = 0;
                char * line = "hello";
                int index = 0;
                root = new Node(minDegree, true);
                root->setLineKey(root, index, lineNumber, offset, string);
                //root->keys[0].key = lineNumber;
                root->numKeys = 1;
            }
            else
            {
                if(root->numKeys == 2*minDegree - 1)
                {
                    Node *newRoot = new Node(minDegree, false);
                    newRoot->childArr[0] = root;
                    newRoot->splitChild(0, root);

                    int index = 0;
                    if(newRoot->getKey(newRoot, index) < lineNumber) index++;

                    newRoot->childArr[index]->insertNonFull(lineNumber);

                    root = newRoot;
                }
                else
                {
                    root->insertNonFull(lineNumber);
                }
            }
        } */

        void insert(int lineNumber, const char* line)
        {
            if(nullptr == root)
            {
                int offset = 0;
                int index = 0;
                root = new Node(minDegree, true);
                root->setLineKey(root, index, lineNumber, offset, line);
                root->numKeys = 1;
            }
            else
            {
                if(root->numKeys == 2*minDegree - 1)
                {
                    Node *newRoot = new Node(minDegree, false);
                    newRoot->childArr[0] = root;
                    newRoot->splitChild(0, root);

                    int index = 0;
                    if(newRoot->getKey(newRoot, index) < lineNumber) index++;

                    newRoot->childArr[index]->insertNonFull(lineNumber, line);

                    root = newRoot;
                }
                else
                {
                    root->insertNonFull(lineNumber, line);
                }
            }
        }
};
        


