#include "../inc/chain.hh"

// Constructor just sets root node to being null
Chain::Chain() : root(nullptr){};

// Delete tree
// TODO:: Need to iterate tree and delete each node
Chain::~Chain()
{
    delete [] root;
}

void Chain::readFile(ifstream &fileName)
{
    string fileString;
    if ( fileName.is_open() )
    {
        while(fileName)
        {
            //TODO :: Fix this because it reads words at a time
            fileName >> fileString;
            insertEnd(fileString);
        }
    }
}

// Function used to print trees and thier contents
// This is sort of hard coded sadly but it did its job for testing
// Can test for no splits (16 lines), one split (up to 64 lines) and a third split for insertEnd
void Chain::printTree() {

    /*
    
       int totallines = 0;
       for(int i=0; i < M; i++){
       totallines += root->count[i];
       }
       for(int i = 0; i < totallines; i++){
       if(i%M == 0)
       cout << endl << i/M << " : ";
       cout << root->nextLeaf[i/M]->lines[i%M] << " ";
       }
       cout << endl << endl;
       */
       


    if(root->count[3] > 64)
    {

        for(int k = 0; k < M - 1; k++)
        {
            cout << "Node: " << k << endl;
            cout << "Top node count " << root->count[k] << endl;
            for(int m = 0; m < M; m++)
            {
                cout << "Leaf Node: " << m << endl;
                cout << "Count " << root->nextNode[k]->count[m] << endl;
                for(int i = 0; i < M; i++)
                {
                    if(root->nextNode[k]->nextLeaf[m] != nullptr)
                        cout << root->nextNode[k]->nextLeaf[m]->lines[i] << endl;
                }
                cout << endl;
            }
        }

        cout << "Node: 3" << endl;

        for(int i = 0; i < M;  i++)
        {
            cout << "Inner Node: " << i << endl;
            for(int j = 0; j < M; j++)
            {
                cout << "Leaf Node: " << j << endl;
                cout << "Count " << root->nextNode[3]->nextNode[i]->count[j] << endl;

                for(int m = 0; m < M; m++)
                {
                    if(root->nextNode[3]->nextNode[i]->nextLeaf[j] != nullptr)
                        cout << root->nextNode[3]->nextNode[i]->nextLeaf[j]->lines[m] << endl;
                }
            }
        }
    }
    else if(root->count[3] <= 64 && root->count[3] > 16)
    {
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
                    if(root->nextNode[k]->nextLeaf[m] != nullptr)
                        cout << root->nextNode[k]->nextLeaf[m]->lines[i] << endl;

                }
                cout << endl;
            }
        }
    }
    else    {

        for(int m = 0; m < M; m++)
        {
            cout << "Leaf Node: " << m << endl;
            cout << "Count " << root->count[m] << endl;
            for(int i = 0; i < M; i++)
            {
                if(root->nextLeaf[m] != nullptr)
                    cout << root->nextLeaf[m]->lines[i] << endl;
            }
            cout << endl;
        }
    }
}

Chain::InternalNode * Chain::countBacktrace(InternalNode * node)
{
    int newCount = 0; 
    int oldCount = 0;
    int parentIndex = 0;

    while(1)
    {
        if(node->parentNode == nullptr)
        {
            break;
        }


        parentIndex = node->nodeIndexFlag;

        if(node->isLeafNode)
        {
            for(int i = 0; i < M; i++)
            {
                if(node->nextLeaf[i] != nullptr)
                    newCount += node->nextLeaf[i]->count;
            }

            node = node->parentNode;

            for(int i = parentIndex; i < M; i++)
            {
                if(i == 0)
                {
                    node->count[0] = newCount;
                }
                else
                {
                    node->count[i] = newCount + node->count[i-1];
                }

                if(node->count[i + 1] == 0)
                {
                    break;
                }
            }
        }
        else
        {
            oldCount = node->count[parentIndex];

            node = node->parentNode;

            for(int i = parentIndex; i < M; i++)
            {
                newCount += node->count[i];
            }

            // In the case of a non leaf node --> we need to get the difference
            newCount = newCount - oldCount;

            for(int i = parentIndex; i < M; i++)
            {
                if(i == 0)
                {
                    node->count[0] = node->count[0] + newCount;
                }
                else
                {
                    node->count[i] = newCount + node->count[i-1];
                }

                if(node->count[i + 1] == 0)
                {
                    break;
                }
            }
        }

        newCount = 0;
    }
    return node;
}


void Chain::remove(int pos){

    int totallines = 0;
    for(int i=0; i < M; i++){
        totallines += root->count[i];
    }

    root->nextLeaf[pos/M]->lines[pos%M] = ""; // Erase requested line
    pos++;

    // Update position of other lines
    string hold = "";
    for(int i = pos; i < totallines; i++){
        root->nextLeaf[(i-1)/M]->lines[(i-1)%M] = root->nextLeaf[i/M]->lines[i%M];
    }

    // Clear final line and update count
    root->nextLeaf[(totallines-1)/M]->lines[(totallines-1)%M] = "";
    root->count[(totallines-1)/M]--;
    root->nextLeaf[(totallines-1)/M]->count--;

}

// Adjusts the value of the node
Chain::LeafNode* Chain::fillnode(string line, LeafNode *node, bool isNewLeaf) {
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

// Used to delete leaves from an internal node 
void Chain::deleteLeafNodes(InternalNode **node) {
    for (int i = 0; i < M; i++) {
        //LeafNode *tmp = (*node)->nextLeaf[i];
        //free(tmp);
        delete [] (*node)->nextLeaf[i];
    }
}

// Working on this again. 
void Chain::insertBeginning(string line)
{

}


// Inserts a value in the end position of the m-Way tree
void Chain::insertEnd(string line)
{
    root = setval(line, this->root);
}

// Sets the value in the node --> this function is exclusivley for insert end
Chain::InternalNode * Chain::setval(string line, InternalNode *node)
{

    // if node is null
    // In this case we create a new interal node root. This points to four leafNodes
    // Parent node is set to nullptr
    // Insert into postion 0 and thats it
    if (node == NULL) {
        InternalNode *newRoot = new InternalNode();
        LeafNode *leafNode = new LeafNode();
        leafNode->lines[0] = line;
        leafNode->count = 1;
        newRoot->isLeafNode = true;
        newRoot->count[0] = 1;
        newRoot->parentNode = nullptr;
        newRoot->nodeIndexFlag = 0;
        newRoot->nextLeaf[0] = leafNode;
        node = newRoot;
        return node;
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

                    // If nextLeaf does not exist. Allocate and insert line in newLeaf
                    if(node->nextLeaf[index] == nullptr)
                    {
                        LeafNode *newLeaf = new LeafNode();
                        newLeaf = fillnode(line, newLeaf, true );
                        node->nextLeaf[index] = newLeaf;
                        node->count[index] = 1;
                        countBacktrace(node);
                        return node;
                    }

                    node->nextLeaf[index] = fillnode(line, node->nextLeaf[index], false);
                    countBacktrace(node); // Call to update the count

                    node->count[index] += 1;

                    return node;
                }
            }

            if(isNodeFull)
            {
                //If node is full we need to split and create four more nodes
                node = splitEnd(line, node);

               
                //Call the coutBacktrace function on both of the newly created nodes to update the counts
                //up until the root of the tree

                countBacktrace(node->nextNode[0]);
                countBacktrace(node->nextNode[1]);

                return node;
            }
        }
        else {

            for(int nodeIndex = 0; nodeIndex < M;  nodeIndex++)
            {
                // Check for the last node that is populated and go to that node
                // cout << "Node count check " << node->count[nodeIndex] << endl;
                if(node->count[nodeIndex] % 16 > 0 || node->count[nodeIndex] == 0)
                {
                    setval(line, node->nextNode[nodeIndex]);
                    return node;
                }
            }

            // Only reaches this point if all nodes are full. We then go down to next level from the last node
            // This only works for insert end
            setval(line, node->nextNode[3]);
        }
    }
    return node;  // Doesnt hit here but throws error
}

// Split internal node to M internal nodes
void Chain::splitNode(InternalNode *node) {
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

void Chain::insertMiddle(string line, int pos) {
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

// Splits the node
Chain::InternalNode * Chain::splitEnd(string line, InternalNode *head)
{

    //Create four new internal nodes
    InternalNode *newNodeOne = new InternalNode();
    InternalNode *newNodeTwo = new InternalNode();
    InternalNode *newNodeThree = new InternalNode();
    InternalNode *newNodeFour = new InternalNode();

    LeafNode *newLeaf = new LeafNode();

    //TODO hardcoded for M = 4. Will need to change this
    
    //First new node is set to the original node
    for(int i = 0; i < M; i++)
    {
        newNodeOne->nextLeaf[i] = head->nextLeaf[i];
        newNodeOne->count[i] = 4;
        head->nextLeaf[i] = nullptr;
    }
    newNodeOne->isLeafNode = true;
    newNodeOne->nodeIndexFlag = 0;
    

    //Since this funciton is for splitting to the end. The new value will be inserted into the second node
    //in position 0
    fillnode(line, newLeaf, true);
    newNodeTwo->nextLeaf[0] = newLeaf;
    newNodeTwo->isLeafNode = true;
    newNodeTwo->count[0] = 1;
    newNodeTwo->nodeIndexFlag = 1;


    //Rest of the nodes are empty so we just do basic initialization
    newNodeThree->isLeafNode = true;
    newNodeThree->nodeIndexFlag = 2;

    newNodeFour->isLeafNode = true;
    newNodeFour->nodeIndexFlag = 3;

    // Create a new head node where this replaces the input node in the tree
    head->nodeIndexFlag = 3;
    head->isLeafNode = false;
    // Update the counts, first node full, second node one with new element
    head->count[0] = 16;
    head->count[1] = 1;
    head->count[2] = 0;
    head->count[3] = 0;
    head->nextNode[0] = newNodeOne;
    head->nextNode[1] = newNodeTwo;
    head->nextNode[2] = newNodeThree;
    head->nextNode[3] = newNodeFour;

    //All four new nodes point to the new head
    newNodeOne->parentNode = head;
    newNodeTwo->parentNode = head;
    newNodeThree->parentNode = head;
    newNodeFour->parentNode = head;


    return head;
}

