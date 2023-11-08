//Author: Bomen Derick.....
/*The driver program of the kd-tree algorithm.. Please see the file: ReadMe.txt for requirements */

#include "kdTree.h"
#include <iostream>
#include <ctype.h>

#define abs(a) (a>0)? a : -(a) //return the magnitude of a number
using namespace std;

KdNode *root = nullptr; //Global variable to store nodes of the tree
//Enumeration for present and future available options to interact with the kd-tree
typedef enum Options{
    Insert_a_node = 1,
    Delete_a_node,
    search_a_node,
    traverse_kd_tree,
    traverse_kd_tree_in_2D,
    move_nodes_in_kd_tree,
    predict_node_position,
    Exit
}Options;

//utility function to return available options present in the enumeration
const char* option(Options n)
{
    switch(static_cast<int>(n))
    {
        case 1:
            return "Insert_a_node";
        case 2:
            return "Delete_a_node";
        case 3:
            return "Search_a_node";
        case 4:
            return "Traverse_kd_tree";
        case 5:
            return "Traverse_kd_tree_in_2D";
        case 6:
            return "Move_nodes_in_kd_tree";
        case 7:
            return "Predict_node_position";
        case 8:
            return "Exit";
        default:
            break;
    }
    return " ";
}

//Display list of available options
void displayOptions()
{
    for (int i = 1; i <= Exit; ++i) {
        auto n = (Options) i;
        cout<<i<<". "<<option(n)<<endl;
    }
    cout<<endl<<endl;
}

//function that listen to the user chosen option and return to the caller
int chooseOption()
{
    int p;
    char c;
    cout<<"choose an option number (eg 1 for insertion): "; //taking an ascii character
    cin>>c;
    p = c - '0'; //converting the ascii character to integer and return to the caller
    return p;
}

//execute the insert option to insert node. A wrapper over insertNode()
void exeInsert(int k)
{
    int n;
    //in case of multiple nodes to be inserted
    cout<<"Enter the number of nodes to insert: ";
    cin>>n;
    for (int i = 1; i <= n ; ++i)
    {
        KdNode node;
        double a[k];
        char obj;
        cout<<"Entering node number "<<i<<endl;
        for (int j = 0; j < k; ++j)
        {
            cout<<"Enter value of index "<<j<<": "; //collect points from the user
            cin>>a[j]; //store points in the array
        }
        cout<<"Enter object 'a char': ";
        cin>>obj;
        node = newKNode(a, obj, k); //allocate memory through newKNode() to insert the node
        root = insertNode(root, node, 0, k); //insert node and store in global root
    }
    cout<<endl;
}

//execute the delete option to delete a node. A wrapper over deleteNode()
void exeDelete(int k)
{
    KdNode *node;
    double a[k];
    char obj;
    cout<<"Enter node to delete: "<<endl;
    for (int i = 0; i < k; ++i)
    {
        cout<<"Enter value of index "<<i<<": ";
        cin>>a[i];
    }
    cout<<"Enter object 'a char': ";
    cin>>obj;
    node = newNode(a, obj, k); //allocate memory to hold user input so as to trace user input from the tree
    root = deleteNode(root, node, 0, k); //delete node and return resulting nodes in global root
    if (root == nullptr)
        cout<<"KD-Tree is still empty";
    cout<<endl<<endl;
}

//execute search option to search for a node. A wrapper over searchNode()
void exeSearch(int k)
{
    KdNode *node;
    double a[k];
    char obj;
    cout<<"Enter node to search: "<<endl;
    for (int i = 0; i < k; ++i)
    {
        cout<<"Enter value of index "<<i<<": "; //collect point to be search
        cin>>a[i]; //store point to be search
    }
    cout<<"Enter object 'a char': ";
    cin>>obj;
    node = newNode(a, obj, k); //allocate node to search in the tree
    //Respond to the search request..
    if(searchNode(root, node, 0, k))
        cout<<"Node Found!!!!"<<endl<<endl;
    else
        cout<<"Node NOT Found!!!!"<<endl<<endl;
}

//execute traverse option to traverse a kd-tree. A wrapper over traverseTree()
void exeTraverse(int k)
{
    traverseTree(root, k);
    cout<<endl<<endl;
}

//execute traverse_in_2d option to traverse in a 2-dimensional manner
void exeTraverse2D(int k)
{
    traverseIn2D(root, 0, k);
    cout<<endl<<endl;
}

//execute move option to change node positions in the tree. A wrapper over moveNodes()
void exeMove(int k)
{
    double t;
    cout<<"Enter time interval: ";
    cin>>t;
    //continuously changing nodes positions over time interval t
    for (int i = 1; i <= t; ++i) {
        moveNodes(root, i, k);
    }
    cout<<endl<<endl;
}

//execute prediction option to predict the future position of a node over a given time. A wrapper over predictNodePosition()
void exePrediction(int k)
{
    KdNode *node;
    double a[k];
    char obj;
    double t;
    cout<<"Enter node to predict position: "<<endl;
    for (int i = 0; i < k; ++i)
    {
        cout<<"Enter value of index "<<i<<": ";
        cin>>a[i];
    }
    cout<<"Enter object 'a char': ";
    cin>>obj;
    cout<<"Enter the time interval: ";
    cin>>t;
    node = newNode(a, obj, k);
    node = predictNodePosition(root, node, t, k);

    cout<<"Predicted node position is: ";
    cout<<"(";
    for (int j = 0; j < k; ++j)
    {
        cout<<" "<<node->point[j];
    }
    cout<<")";
    cout<<endl<<endl;
}

//default function to be executed in case of no valid option
void defaultAction()
{
    cout<<"Please choose a valid option!!"<<endl<<endl;
}

//driver function to test available functions on the available algorithm
int main()
{
    int d;
    //Get the dimension to work with
    cout<<"Enter the dimension of the workspace (Positive integer greater than zero (0)): ";
    cin>>d;
    //Ensuring we are working with a dimension greater than zero (0)
    //Keeping asking the dimension when the dimension entered is zero (0)
    while (d == 0)
    {
        int k;
        cout<<"Enter the Dimension.. MUST be greater than zero(0)..."<<endl;
        cin>>k;
        d = k;
    }
    d = abs(d); //return a positive dimension in case a negative dimension was accidentally entered
    cout<<endl;
    cout<<"Available Options......................"<<endl<<endl;
    displayOptions(); //display available options to be use
    //keep asking an option unless the exit option is entered
    cout<<endl;
    while (true)
    {
            Options choice = Delete_a_node; //local variable to define loop break
            //execute options depending on their numbering on the console returned by chooseOption()
            switch (chooseOption()) {
                case 1:
                    exeInsert(d);
                    displayOptions();
                    break;
                case 2:
                    exeDelete(d);
                    displayOptions();
                    break;
                case 3:
                    exeSearch(d);
                    displayOptions();
                    break;
                case 4:
                    exeTraverse(d);
                    displayOptions();
                    break;
                case 5:
                    exeTraverse2D(d);
                    displayOptions();
                    break;
                case 6:
                    exeMove(d);
                    displayOptions();
                    break;
                case 7:
                    exePrediction(d);
                    displayOptions();
                    break;
                case 8:
                    choice = Exit;
                    break;
                default:
                    defaultAction();
                    displayOptions();
                    break;
            }
            if (choice == Exit) //break out of the loop if Exit option is chosen
                break;
    }


    return 0;
}

