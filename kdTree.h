//Author: Bomen Derick.....
/* Header file of the kd-tree algorithm */

#ifndef KD_TREE_KDTREE_H
#define KD_TREE_KDTREE_H

// A structure to represent node of kd tree
typedef struct KdNode
{
    int object; //to represent a k dimensional point
    double *point; // To store k dimensional point
    struct KdNode *left, *right; //branching
}KdNode;


KdNode *make_tree(KdNode *t, int length, int i, int dim);
KdNode* find_median(KdNode *start, KdNode *end, int idx);
void swap(KdNode *x, KdNode *y);

/*--methods takes a last parameter for the dimension of the workspace--------*/

// methods to create a KD tree node with respect to the given dimension
KdNode *newNode(double arr[], int , int dimension);
KdNode newKNode(double a[], int, int dimension);

// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison
KdNode *insertNode(KdNode *root, KdNode node, unsigned depth, int dimension);

// a wrapper over insertNode function
KdNode* insert(KdNode *root, KdNode node, int dimension);

// A utility function to find minimum of three points
KdNode *minNode(KdNode *, KdNode *, KdNode *, int dimension);

// Recursively finds minimum of d'th dimension in KD tree
// The parameter depth is used to determine current axis.
KdNode *findMinNode(KdNode* root, unsigned d, unsigned depth, int dimension);

// A wrapper over findMinNode(). Returns minimum of d'th dimension
KdNode *findMin(KdNode* root, int d, int dimension);

// A utility method to determine if two Points are same
// in K Dimensional space
bool arePointsSame(KdNode *node1, KdNode *node2, int dimension);

// Copies point node2 to node1
void copyNode(KdNode *node1, KdNode *node2, int dimension);

// Searches a node in the Kd-tree.
// The parameter depth is used to determine current axis.
bool searchNode(KdNode* root, KdNode *node, unsigned depth, int dimension);

// a wrapper on the searchNode() to search for a given node in the kd-tree
bool search(KdNode* root, KdNode *node, int dimension);

// Function to delete a given node from the tree
// depth is current depth and passed as 0 initially.
// Returns root of the modified tree.
KdNode *deleteNode(KdNode *root, KdNode *node, int depth, int dimension);

// wrapper function to delete a given node from kd-Tree with 'root'
KdNode* deleteNode(KdNode *root, KdNode *node, int dimension);

//function to traverse the tree's nodes in an in-order traversal(right-root-left)
void traverseTree(KdNode *root, int dimension);

//in-order traversal and display nodes in 2-dimensional view
void traverseIn2D(KdNode *root, int space, int dimension);

//moveNodes() changes nodes position after a given time
void moveNodes(KdNode *root, double time, int dimension);

//function predict the next position of a given node in the tree after a given time
KdNode *predictNodePosition(KdNode *root, KdNode *node, double tim, int dimension);

#endif //KD_TREE_KDTREE_H
