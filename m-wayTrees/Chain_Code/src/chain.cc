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


    for(int q = 0; q < M; q++)
    {
        cout << root->count[q] << endl;
        for(int i = 0; i < M; i++)
        {
            cout << root->nextLeaf[q]->lines[i] << endl;
        }
    }

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

    cout << root->nextNode[3]->nextNode[0]->nextLeaf[0]->lines[0];

    cout << endl;
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

void Chain::deleteLeafNodes(InternalNode **node) {
    for (int i = 0; i < M; i++) {
        delete[] (*node)->nextLeaf[i];
    }
}

// Working on this again. 
void Chain::insertBeginning(string line)
{

}


// Inserts a value in the m-Way tree
void Chain::insertEnd(string line)
{
    root = setval(line, this->root);
    //cout << "Testing" << this->root->nextNode[3]->nextNode[0]->nextLeaf[0]->lines[0] << endl;
}

// Sets the value in the node
Chain::InternalNode * Chain::setval(string line, InternalNode *node)
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
                    countBacktrace(node);

                    node->count[index] += 1;

                    return node;
                }
            }

            if(isNodeFull)
            {
                if(node->parentNode != nullptr)
                {

                    cout << node->parentNode->count[0] << endl;
                    cout << node->parentNode->count[1] << endl;
                    cout << node->parentNode->count[2] << endl;
                    cout << node->parentNode->count[3] << endl;

                }
                node = splitEnd(line, node);
                cout << node->nextNode[1]->nextLeaf[0]->lines[0] << endl;
                countBacktrace(node->nextNode[0]);
                countBacktrace(node->nextNode[1]);
                cout << node->nextNode[1]->nextLeaf[0]->lines[0] << endl;

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
                    cout << "Index is " << nodeIndex<< endl; 
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
    cout << "In split" << endl;
    cout << line << endl;


    InternalNode *newNodeOne = new InternalNode();
    InternalNode *newNodeTwo = new InternalNode();
    InternalNode *newNodeThree = new InternalNode();
    InternalNode *newNodeFour = new InternalNode();

    InternalNode *tempHeadNode = new InternalNode();
    LeafNode *newLeaf = new LeafNode();

    //TODO hardcoded for M = 4. Will need to change this
    newNodeOne = head;
    newNodeOne->isLeafNode = true;
    newNodeOne->nodeIndexFlag = 0;

    fillnode(line, newLeaf, true);
    newNodeTwo->nextLeaf[0] = newLeaf;
    newNodeTwo->isLeafNode = true;
    newNodeTwo->count[0] = 1;
    newNodeTwo->nodeIndexFlag = 1;

    newNodeThree->isLeafNode = true;
    newNodeThree->nodeIndexFlag = 2;

    newNodeFour->isLeafNode = true;
    newNodeFour->nodeIndexFlag = 3;

    tempHeadNode->nodeIndexFlag = 3;
    tempHeadNode->isLeafNode = false;
    tempHeadNode->count[0] = 16;
    tempHeadNode->count[1] = 1;
    tempHeadNode->nextNode[0] = newNodeOne;
    tempHeadNode->nextNode[1] = newNodeTwo;
    tempHeadNode->nextNode[2] = newNodeThree;
    tempHeadNode->nextNode[3] = newNodeFour;
    tempHeadNode->parentNode = head->parentNode;
    deleteLeafNodes(&tempHeadNode);

    newNodeOne->parentNode = tempHeadNode;
    newNodeTwo->parentNode = tempHeadNode;
    newNodeThree->parentNode = tempHeadNode;
    newNodeFour->parentNode = tempHeadNode;

    head = tempHeadNode;
    return head;
}

