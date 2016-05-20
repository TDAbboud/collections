Collections
===========

This is a library of data-structures and algorithms to use in C

## Installation

* make
* sudo make install

To uninstall
* sudo make uninstall
* make clean

## Usage

Static linking:
* Compile the program linking in the static library
    gcc -static example.c -lcollections

Dynamic Linking:
* Set the LD_LIBRARY_PATH env variable
    LD_LIBRARY_PATH=/usr/local/lib
    export LD_LIBRARY_PATH
* compile the program
    gcc example.c -lcollections


## Testing
Compile and run all unit tests
* make tests

