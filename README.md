# Team Members:
1. Quentin Jimenez
2. Noah Malhi
3. Prashant Kumar

# Chaining

Write the implementation of chain, and write a quick comparison using strings demonstrating how much faster the tree-based approach is at large sizes, n=100kB, 1MB, 10MB, and 100MB. YOu should be able to load in a file, manipulate it (insert characters, insert lines of text, remove lines of text, etc.) and save it out to disk. Implement a quick string-based version as a basis of comparison.

Chain is an efficient tree data structure used to represent extremely large text files. Chaining implementation utilizes a m-ways-tree structure as well as a memorypool for faster access. It reads in a textfile and inserts each line into the tree leafNodes. The m-ways-tree is split into two main node classes called InternalNode and Leafnode. The internal nodes are used for the general strucutre of the tree and provide a way to index into the tree and find/insert/remove specific lines. The root node (an Internal Node) has up to M number of nodes it can point to. In this Chain representation M was set to 4, thus it was a four-way tree. Each internal node in the tree may point to four internal nodes or they can point to four leaf nodes. Leaf nodes are nodes that populate the base of the tree. They are the nodes that actually contain the lines. Each leafnode containers four lines. Thus an InternalNode that points to leafNodes can hold up to 16 lines. If an internal node has 16 lines and needs to insert a new line, the node is then split. A new head is designated and four more internal nodes are created. The original InternalNode is the new head and no longer points to leafNodes, instead it points to the new internalnodes. For an internalNode that points to other internalNodes, a count is kept to keep track of the number of lines that have been inserted below them. As it goes up the tree from the leafNode, the internal nodes keeps track of this number. Thus at the top of the tree in the root node, the number of lines for each of the root nodes internalNodes is kept. 

```C++
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
```

For example, if there was a root node with four internal nodes, the root node contains an array count[] which would be populated with something simlar to the following [16, 32, 48, 52]. If a number was needed to be inserted into the 17th position, it would check count[0] to count[M]. Since 16 < 17 it would iterate to count[1]. 17 < 32 thus it traverses down to the next node at root->nextNode[1]. From there it would check if that internalNode was pointing to leafNodes or more Internal nodes by a boolean value that is set (isLeafPointer). If it was another internalNode it would do the same process as mentioned above and search for the correct position to traverse down. If it was pointed to leaves then it would find the correct position in the leafNodes lines[] array. If there was a slot avaialble it would insert in the position and the operation would be complete. If the leafNode was full, the aforementioned split operation would take place. After both scenarios a backtract up to the root of the tree would occur, and the counts would then be updated according to the change in the number of leaves (whether a removal or insertion occured).

Chain allows for an overall smaller tree structure than Rope (its competitor). Rope would have nodes for every word in a line, whereas Chain would have a node for just the lines. Also in our implementation we used an m-ways-tree which also drastically reduce the depth. This allows for fast insertions and deletions. This however is at the code of word manipulation; however this is outside of our scope.

## Code Directory

### Final Paper
Located in the doc/ directory as instructed.

### Source Code
Located in m-way-trees/Chain_Code
The file main file is located in the src directory and is named chain_main.cc. In the src folder the functions source code is also located, and the include dir has the chain header file.
[m-way-trees/Chain_Code]( https://github.com/Quentin-Jimenez/CPE593-Chaining/tree/main/m-wayTrees/Chain_Code )

Also located in this directory is other files used for development and a testfile to be read in and inserted into the chain structure.
Includes README file on how to run the code and the main functions utilized.

### Chain Operations Diagrams
Located in m-way-tree/drawings
Two main directorys. One holds svg files of the drawings while the other holds the png versions.
Insertion in different positions included as well as removals.
[m-way-trees/drawings]( https://github.com/Quentin-Jimenez/CPE593-Chaining/tree/main/m-wayTrees/drawings )

### Old work
This includes all the work done for our previous implementation of Chain. This work was incorrect and down the wrong path, but left it to show former efforts.
[btrees_oldwork]( https://github.com/Quentin-Jimenez/CPE593-Chaining/tree/main/b-trees_oldwork )

## Main Chain Structure
![Alt text](structure1.png?raw=true "Chain Example")

## Link to Overleaf Document
[OverLeaf]( https://www.overleaf.com/project/63619b45345cef2f8b52957e )
