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


        






};
        


