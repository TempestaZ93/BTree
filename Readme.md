# Binary Tree

This binary tree implementation is designed to hold all kind of data that can be ordered.

## Build

This is a header only library which needs not to be built.

In case you want to build the example or the test do the following inside of the project's root directory.
```sh
mkdir -p build && cd build
cmake ..
make -j8
```

The example is build by default but the test needs to switched on manually with this flag:
```sh
cmake -DBUILD_TEST=ON ..
```


In case you do not want to build the example add the following cmake flag:
```sh
cmake -DBUILD_EXAMPLE=OFF ..
```

## Usage

You can simply copy the header `include/BTree.h` into you include directory.
This library uses a STB-like include system.
If you only want to use the header as a include file just include it normally.
If you want to use it as implementation add the following before its first include:
```c
#define BINARY_TREE_IMPLEMENTATION
```
