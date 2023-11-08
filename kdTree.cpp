//Author: Bomen Derick......
/* Implementation file of the kd-tree algorithm.. Please see the file: ReadMe.txt for more info */

#include "kdTree.h"
#include <iostream>
#include <stdlib.h>


using namespace std;

// A method to create KD tree node and return a pointer to kd tree node
KdNode *newNode( double arr[], int c, int k)
{
    auto *temp = new KdNode; //create new node
    temp->point = (double *)malloc(k * sizeof(double)); //dynamic allocation of memory with respect to the given dimension k to store points... C way
    //temp->point = new double[k]; //same as above but C++ way
    for (int i=0; i<k; i++)
        temp->point[i] = arr[i]; //store given array to allocated memory
    temp->object = c; //store node object as a character
    temp->left = temp->right = nullptr; //initialise pointer to null
    return temp; //return created node
}


//function swap to swap between nodes using a temporal memory
void swap(KdNode *x, KdNode *y) {
    KdNode *tmp = nullptr;
    tmp->point = x->point;
    x->point = y->point;
    y->point = tmp->point;
}

KdNode* find_median(KdNode *start, KdNode *end, int idx)
{
    if (end <= start) return NULL; //returns empty tree if no nodes exist
    if (end == start + 1)
        return start; //returns node as root node if one node exist
    KdNode *p, *store, *md = start + (end - start) / 2;
    double pivot;//variable to hold the median point
    while (1) {
        pivot = md->point[idx];
//store the median point and store all points less than the median points as the left sub-tree
        swap(md, end - 1);
        for (store = p = start; p < end; p++) {
            if (p->point[idx] < pivot) {
                if (p != store)
                    swap(p, store);
                store++;
            }
        }
        swap(store, end - 1);
//in case median has duplicate values in different location, retains only the one in (md)
        if (store->point[idx] == md->point[idx])
            return md;
//if nodes stored is greater than (md), store the nodes as end or store as start otherwise
        if (store > md) end = store;
        else
            start = store;
    }
}

//function make_tree to construct the kd-tree
KdNode *make_tree(KdNode *t, int length, int i, int dim)
{
    KdNode *n;//temporal node for tree partition
    if (!length) return 0;//if no length, returns 0, consiquently no nodes are present
//determining the median node and keep it as (n)
    if ((n = find_median(t, t + length, i))) {
        i = (i + 1) % dim;//constantly changing the initial index
        n->left = make_tree(t, n - t, i, dim);//a recursive call to construct the left sub-tree
        n->right = make_tree(n + 1, t + length - (n + 1), i, dim);//a recursive call to construct the right sub-tree
    }
    return n;//returns already partitioned nodes as kd-tree
}


// A method to create KD tree node and return kd tree node
KdNode newKNode(double a[], int c, int k)
{
    KdNode temp; //create new node
    temp.point = (double *)malloc(k * sizeof(double)); //dynamic allocation of memory with respect to the given dimension k to store points ... C way
    //temp.point = new double[k]; //same as above but C++ way
    for (int i=0; i<k; i++)
        temp.point[i] = a[i]; //store given array to allocated memory
    temp.object = c; //store node object as a character
    temp.left = temp.right = nullptr; //initialise pointer to null
    return temp; //return created node
}

// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison
KdNode *insertNode(KdNode *root, KdNode node, unsigned depth, int k)
{
    // if tree is empty return node as root
    if (root == nullptr)
        return newNode(node.point, node.object, k);

    // Calculate current dimension(cd) of comparison
    unsigned cd = depth % k;

    // Compare the new node with root on current dimension 'cd'
    // and decide the left or right subtree
    if (node.point[cd] < (root->point[cd]))
        root->left = insertNode(root->left, node, depth + 1, k);
    else
        root->right = insertNode(root->right, node, depth + 1, k);

    return root;
}

// a wrapper over insertNode function
KdNode* insert(KdNode *root, KdNode node, int k)
{
    return insertNode(root, node, 0, k);
}

// A utility function to find minimum of three points
KdNode *minNode(KdNode *x, KdNode *y, KdNode *z, int d)
{
    KdNode *res = x;
    if (y != nullptr && y->point[d] < res->point[d])
        res = y;
    if (z != nullptr && z->point[d] < res->point[d])
        res = z;
    return res;
}

// Recursively finds minimum of d'th dimension in KD tree
// The parameter depth is used to determine current axis.
KdNode *findMinNode( KdNode* root, unsigned d, unsigned depth, int k)
{
    // Base cases
    if (root == nullptr)
        return nullptr;

    // Current dimension is computed using current depth and total
    // dimensions (k)
    unsigned cd = depth % k;

    // Compare point with root with respect to cd
    if (cd == d)
    {
        if (root->left == nullptr)
            return root;
        return findMinNode(root->left, d, depth+1, k);
    }

    // If current dimension is different then minimum can be anywhere in the subtree
    return minNode(root, findMinNode(root->left, d, depth+1, k), findMinNode(root->right, d, depth+1, k), d);
}

// A wrapper over findMinNode(). Returns minimum of d'th dimension
KdNode *findMin(KdNode* root, int d, int k)
{
    // set initial level or depth as 0
    return findMinNode(root, static_cast<unsigned int>(d), 0, k);
}

// A utility method to determine if two Points are same
// in K Dimensional space
bool arePointsSame(KdNode *node1, KdNode *nodeptr, int k)
{
    // Compare individual pointing values
    for (int i = 0; i < k; ++i)
        if (node1->point[i] != nodeptr->point[i])
            return false;

    return true;
}

// Copies point node2 to node1
void copyNode(KdNode *nodeptr1, KdNode *nodeptr2, int k)
{
    for (int i=0; i<k; i++)
        nodeptr1->point[i] = nodeptr2->point[i];
    nodeptr1->object = nodeptr2->object;
}

// Searches a node in the Kd-tree.
// The parameter depth is used to determine current axis.
bool searchNode(KdNode* root, KdNode *nodeptr, unsigned depth, int k)
{
    // Base cases
    if (root == nullptr)
        return false;
    if (arePointsSame(root, nodeptr, k) && (root->object == nodeptr->object))
        return true;

    // Current dimension is computed using current depth and total
    // dimensions (k)
    unsigned cd = depth % k;

    // Compare point with root with respect to cd (Current dimension)
    if (nodeptr->point[cd] < root->point[cd])
        return searchNode(root->left, nodeptr, depth + 1, k);

    return searchNode(root->right, nodeptr, depth + 1, k);
}

// a wrapper on the searchNode() to search for a given node in the kd-tree
bool search(KdNode* root, KdNode *nodeptr, int k)
{
    // Pass current depth as 0
    return searchNode(root, nodeptr, 0, k);
}

// Function to delete a given node from the tree
// depth is current depth and passed as 0 initially.
// Returns root of the modified tree.
KdNode *deleteNode(KdNode *root, KdNode *nodeptr, int depth, int k)
{
    // Given node is not present
    if (root == nullptr)
        return nullptr;

    // Find dimension of current node
    auto cd = static_cast<unsigned int>(depth % k);

    // If the node to be deleted is present at root
    //look for the smallest node in the current dimension to replace as root node
    if (arePointsSame(root, nodeptr, k) && (root->object == nodeptr->object))
    {
        // If right child is not NULL
        if (root->right != nullptr)
        {
            // Find minimum of root's dimension in right subtree
            KdNode *min = findMin(root->right, cd, k);

            // Copy the minimum to root
            copyNode(root, min, k);

            // Recursively delete the minimum
            //delete min;
            root->right = deleteNode(root->right, min, depth+1, k);
        }
        else if (root->left != nullptr) // same as above
        {
            KdNode *min = findMin(root->left, cd, k);
            copyNode(root, min, k);
            //delete min;
            root->left = deleteNode(root->left, min, depth+1, k);
        }

        else // If node to be deleted is leaf node
        {
            delete root;
            return nullptr;
        }
        return root;
    }

    //else if(arePointsSame(root, node) && (root->object != node->object))
    //  root->right = deleteNode(root->right, node, depth + 1);

    // If current node doesn't contain point, search downward
    if (nodeptr->point[cd] < root->point[cd])
        root->left = deleteNode(root->left, nodeptr, depth+1, k);
    else
        root->right = deleteNode(root->right, nodeptr, depth+1, k);
    return root;

    //else if(!(search(root, node)))
    //  return NULL;
}

// wrapper function to delete a given node from kd-Tree with 'root'
KdNode* deleteNode(KdNode *root, KdNode *nodeptr, int k)
{
// set initial depth to 0
    return deleteNode(root, nodeptr, 0, k);
}

//function to traverse the tree's nodes in an in-order traversal(right-root-left)
void traverseTree(KdNode *root, int k)
{
    if(root == nullptr)
        return;
    traverseTree(root->right, k);
    cout<<root->object<<"(";
    for(int i=0; i<k; i++)
    {
        cout<<root->point[i];
        if(i < (k - 1) )
            cout<<" , ";
    }
    cout<<")"<<"  ";
    traverseTree(root->left, k);
}

const int COUNT = 10;
void traverseIn2D(KdNode *root, int space, int k) //in-order traversal and display nodes in 2-dimensional view
{
    if(root == nullptr)
        return;
    space += COUNT;
    traverseIn2D(root->right, space, k);
    printf("\n");
    for(int i = COUNT; i < space; i++)
        printf(" ");
    cout<<root->object<<"(";
    for(int i=0; i<k; i++)
    {
        cout<<root->point[i];
        if(i < (k - 1) )
            cout<<" , ";
    }
    cout<<")"<<"  ";
    //printf("%c(%g, %g)\n", root->object, root->point[0], root->point[1]);
    traverseIn2D(root->left, space, k);
}

//moveNodes() changes nodes position after a given time
void moveNodes(KdNode *root, double time, int k)
{
    if(root == nullptr)
        return;
    moveNodes(root->right, time, k);
    for (int i = 0; i<k; i++)
        root->point[i] *= time;
    moveNodes(root->left, time, k);
}

//function predict the next position of a given node in the tree after a given time
KdNode *predictNodePosition(KdNode *root, KdNode *nodeptr, double tim, int k)
{
    //computes the next position of the node if it is present in the tree
    if(search(root, nodeptr, k))
    {
        for (int i = 0; i<k; i++)
            nodeptr->point[i] *= tim; //multiply each value by the given time
        return nodeptr;
    }
    else
        return nodeptr; //returns the node current position if the node is not found in the tree

}
