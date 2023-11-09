# K-Dimensional tree implementation

> NOTE: to interact with the algorithm, a g++ compiler is needed or any
> c++ compiler so as to produce appropriate executable files depending on
> the operating system of the working platform. executables in this
> package are generated using a LINUX UBUNTU 18.04 PLATFORM BASE, so can
> run only linux platform, reason to have an appropriate compiler to
> produce appropriate executables if working on a platform different from
> the above mentioned.

### LINUX platform 
The file `TestTimeAndSpaceOnTerminal.cpp` can easily be use for multiple input size and together determine the time and space used by each input size through algorithms various operations.
Assuming in the package directory (the directory of the opened package with available files)
- compile...
```sh 
g++ kdTree.h kdTree.cpp TestTimeAndSpaceOnTerminal.cpp -o "name of executable file that will be produced e.g. test"
```
- run...
> for an input size ranging from 10 to 50 with a step of 10(which can be modified as needed)
```sh
for i in {10..50..10}; do ./test $i; done
```

### Windows platform
The file `test1.cpp` can be use for random generation of input points with an input size specified in the file `test1.cpp` through the constant `INPUT_SIZE`. However if need of manual input arise, then the file `main.cpp` can be used for a step by step interaction with the algorithm.

> See the `input file.txt` for a sample input and `output file.txt` for the corresponding output..

#### Knowledge
`C` `C++` `Data Structure and Algorithm`
> Please leave a star if you find it helpful. Thanks.

