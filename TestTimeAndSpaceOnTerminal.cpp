//
//Author: Bomen
//

#include <chrono>
#include "kdTree.h"
#include <iostream>
#include <sys/time.h>
#include <sys/resource.h>

#define DIMENSION 3     //working dimension
#define RANDOM_MAX 99999999     //defined maximum random number
#define RAND_PT() (rand()/(int) RANDOM_MAX)     //define random function to generate points
using namespace std;
using namespace std::chrono;


//main() takes the input size of the data (number of nodes)from the terminal to be populated
int main(int argc, char **argv) {

    //useful local variables
    KdNode *rootNode = nullptr;  //initial root of the tree
    struct rusage space{}, ru{};    //rusage variables, ru to record time in seconds and space to record memory used in kilo-bytes
    struct timeval i1{}, i2{}, i3{}, i4{}, i5{}, i6{};  //useful variables to calculate time

    int input = atoi(argv[1]);  //main input converted to integer
    double b[input][DIMENSION]; //two dimensional array to hold generated points
    KdNode nodes[input];     //array to store generated nodes
    //generate nodes with respect to the given input size
    for (int i = 0; i < input; ++i) {
        double c[DIMENSION];
        for (int j = 0; j < DIMENSION; ++j) {
            b[i][j] = RAND_PT();
            c[j] = b[i][j];
        }
        nodes[i] = *(newNode(c, i, DIMENSION));
    }

    getrusage(RUSAGE_SELF, &ru);
    i1 = ru.ru_utime;   //recording the current cpu time with using rusage structure
    high_resolution_clock::time_point t1 = high_resolution_clock::now();    //recording the current cpu time using chrono library
    for (auto & node : nodes) {
        rootNode = insertNode(rootNode, node, 0, DIMENSION); //inserting generated nodes
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();    //recording the current cpu time using chrono library
    auto duration1 = duration_cast<microseconds>( t2 - t1 ).count();    //taken time difference scale to microseconds after insertion is complete
    getrusage(RUSAGE_SELF, &ru);
    i2 = ru.ru_utime;   //recording the current cpu time with using rusage structure
    getrusage(RUSAGE_SELF, &space);
    long size = space.ru_maxrss;    //taking memory used by inertion scale to kilo-bytes after insertion is complete

    double time0 = 2;     //time for dynamic data (time to change nodes' position in the tree)
    getrusage(RUSAGE_SELF, &ru);
    i3 = ru.ru_utime;
    high_resolution_clock::time_point t3 = high_resolution_clock::now();
    for (auto & node : nodes) {
        moveNodes(rootNode, time0, DIMENSION);   //changing nodes' position with respect to the given time
        searchNode(rootNode, &node, 0, DIMENSION);
        time0++;
    }
    high_resolution_clock::time_point t4 = high_resolution_clock::now();
    getrusage(RUSAGE_SELF, &ru);
    i4 = ru.ru_utime;
    auto duration2 = duration_cast<microseconds>( t4 - t3 ).count();    //taken time difference scale to microseconds after insertion is complete

    getrusage(RUSAGE_SELF, &ru);
    i5 = ru.ru_utime;
    high_resolution_clock::time_point t5 = high_resolution_clock::now();
    for (auto &node : nodes) {
        moveNodes(rootNode, time0, DIMENSION);
        rootNode = deleteNode(rootNode, &node, DIMENSION);
        time0++;
    }
    high_resolution_clock::time_point t6 = high_resolution_clock::now();
    getrusage(RUSAGE_SELF, &ru);
    i6 = ru.ru_utime;
    auto duration3 = duration_cast<microseconds>( t6 - t5 ).count();    //taken time difference scale to microseconds after insertion is complete

    //display appropriate information
    cout<<"Input size: "<<input<<endl
        //<<"Space used: "<<size<<" KB"<<endl
       // <<"Insert duration: "<<duration1<<" micro_s   "<<(i2.tv_sec - i1.tv_sec)<<"s"<<endl
        <<"Search duration: "<<duration2<<" micro_s   "<<(i4.tv_sec - i3.tv_sec)<<"s"<<endl
        <<"Delete duration: "<<duration3<<" micro_s   "<<(i6.tv_sec - i5.tv_sec)<<"s"<<endl<<endl;

    //traverseTree(rootNode, DIMENSION);  //display generated points    return 0;

    return 0;
}
