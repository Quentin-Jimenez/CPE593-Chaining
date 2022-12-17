# Source Code

## inc
Includes chain.hh 

## src
Containes chain.cc file and chain_main.cc file used for testing

# How to Run

Utilized make to compile build.

Just just make and then execute with ./chain_main.exe
```
make
```

Created a few tests to show the capabilites of our chain and how far we got.
The ouput when running ./chain_main.exe is separated by ouput statements which tell what 
actions the main is running. 

The first test is inserting to the end. First it shows a few inserts before a split. Then more than 
64 lines are inserted to show that it can handle more than a singular split.

The next test inserts to the end about 5 lines. Then inserts into the second position using insertMiddle.

The last test. Inserts 16 lines then removes positions 3-5. 

All of these tests are shown in the outputs with the indexed nodes, the index leafs, and the lines.

# Main Classes

## Leaf Node
The first type of node is a Leaf Node. A leaf
node consists of a count and an array of M lines.
M is a constant positive integer determines how
many lines can be held in each leaf node, or more
generally speaking how many children each node
can have. The count is used to keep track of how
many lines are present in the node. This number
may range from 1 to M. A leaf node cannot be
the root of the tree and is may only be pointed to
from an Internal node.

## Internal Node

An Internal Node makes up the brunt of the
Chain structure. The root of the Chain is always
an Internal node and it may point up to M num-
ber of Internal Nodes or M number of Leaf Nodes.
Each Internal node also keeps track of its par-
ent node as well as its index in the parent node
for back-tracing purposes that will be mentioned
later. The Boolean isLeafNode is utilized to help
traverse down the Chain to reach an InternalNode
that points to leaf nodes

# Algorithms

This section below will also be added to the drawings readme as the descriptions are depicted in them.

## InsertEnd
Implementation complete. Did not test how many lines it can add. But it should work for atleast 200 
insertions from tests so far. 

To insert at the end, the last non-full node needs to be found. It starts at the root node check-
ing from position 0 to position M. f End Insertion is the very first insertion into the Chain, the root node would be a
single InternalNode that has M=4 leaf nodes and its parentNode is set to nullptr. The leaf nodes
contain up to four lines each thus at most one InternalNode contains 16 lines. If all of slots are
full, a split operation would then take place at the Mth position (due to end insert). In the case
of splitting for an end insertion, four new internal nodes are created with the node being split
set as the head. The first node farthest to the left maintains the values of the head node and its
parentNode is set to be equal to the head. The second node has the new line inserted into nextN-
ode[0] and the parentNode is also pointed towards the new head. The third and fourth internalNodes
are created but left empty with their parentNode being set to head. An important step in this split
is to also set the indexFlag for all of the nodes in which this flag is the nodes position from the head
node. InternalNode node1 would be give the index of 0, node2 1, and so on. Setting the parentN-
ode and setting the index is especially important to the chain structure. This is because after the
split of the node and the insertion of the line, a backtrace needs to be done from the newly added
nodes back to the top of the tree. This is done to update the counts of each node up until the top.
This gives the data structure an accurate count of full leaf nodes in the tree and the ability to access
specific line numbers.

## Insert Beginning
Implementation not complete. Would be very similary to insertEnd but of course the opposite

Insertion at the beginning of the tree is achieved by checking for the count in the root
node. If the root node count at the first place (index = 0) is equal to M raised to (h1), it im-
plies that the first of the M segments is full. To create additional space, the internal node
at level h-1 is split into M sub-internal nodes. The values are then copied to the next right
index of the leaf nodes. M has been set to 4, yielding M internal nodes from the root node namely internal1, internal2,
internal3, and internal4. We start with the root node and traverse to the last layer of internal 
node i.e internal1. As internal1 is full, we split internal1
into internal11 and internal12. It is to be noted here that setting M=4 enables us to have four
internal nodes originating from internal1. After creating the new internal nodes, the values in
the leaf nodes are copied one place to the right beginning from the last value in the leaf nod.
This creates a leaf node at the first position of internal11 pointing to nullptr. The new value
is then inserted at the first leaf node. Insertion at the beginning is of the complexity O(logn+
M2). For large text files M2 is negligible, hence the overall amortized complexity is O(logn).

## Insert Middle

The process is started by looking through the root node with the position to insert. As 
discussed above, the root node carries the cumulative count of full leaf nodes. Since 25 is greater 
than 16 and less than 32, it indexes into the second internal node internal2. The program then looks 
for empty leaf nodes within internal2. Since there are none, internal2 is split into internal21 and internal22
using the split node function. 
After creating the new internal nodes, the values in the leaf nodes are copied one place to the right 
beginning from the last value in the leaf node. This process creates an empty leaf node at the first location 
of internal21. The new values are then inserted into the newly emptied leaf node. The same process is repeated ten 
times to insert all strings into position 25.

## Split

Another core function in our tree structure. If the leafnodes are full. Essentially we are taking the internalNode that points to the leaves and creating a new node from that that points to four new internalNodes. In the case of InsertEnd. All of the lines that were in the original node are put into internalNode1, and the new line is inserted into internalNode2. InternalNode 3 and 4 are initalized but left empty.
InsertMiddle Split is similar to this, but instead splits it depending on the insert position.

## Remove
Traverse to the postion using the internalNode count[]. Find line number, remove, and shift everything else left.

