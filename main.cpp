//Author: Brian Erichsen Fagundes
//MSD - Spring of 2024
//Malloc replacement / implementation
#include <iostream>
#include <chrono>
#include "hashTable.h"
#include "bMalloc.h"
#include "test.h"

//global object for allocating and deallocating - for now
// B_Malloc brians_malloc;
//overload global new to allocate memory resources through my class object
// void* operator new(std::size_t size) {
//     return brians_malloc.allocate(size);
// }

// //overload global delete to deallocate memory resources through my class object
// void operator delete(void* ptr) {
//     brians_malloc.deallocate(ptr);
// }

int main () {
    //performs my custom testing for the hash class and BMalloc class
    test_hash_class();
    test_bMalloc();
    //allocates a large number of small memory objects
    const int smallObjectCount = 1000;
    for (int i = 0; i < smallObjectCount; ++i) {
        int* smallObject = new int;
        *smallObject = i;
        delete smallObject;
    }

    //creates more objects and verifies that the data stays valid
    int* dynamicInt = new int(42);
    std::cout << "Dynamic int value: " << *dynamicInt << std::endl;
    
    //Allocates a large number of large memory objects
    const int largeObjectCount = 100;
    for (int i = 0; i < largeObjectCount; ++i) {
        char* largeObject = new char[1000];
        delete[] largeObject;
    }

    //Deallocates objects and verifies B_Malloc / Hash_Table are correct
    int* obj1 = new int;
    int* obj2 = new int;
    delete obj1;
    delete obj2;

    //Allocates small and large blocks of memory
    int* smallBlock = new int;
    char* largeBlock = new char[1000];
    delete smallBlock;
    delete[] largeBlock;

    //times how long it takes to malloc() and free() memory
    //Returns a time point representing the current point in time
    //https://en.cppreference.com/w/cpp/chrono/high_resolution_clock/now
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        int* temp = new int;
        delete temp;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Time taken for 1000 allocations and deallocations: " <<
    duration.count() << " seconds." << std::endl;
    // Malloc and free -- timing output:
    // Time taken for 1000 allocations and deallocations: 7.0959e-05 seconds.

    // Time taken for 1000 allocations and deallocations: 7.0916e-05 seconds.

    // libraries
    // Time taken for 1000 allocations and deallocations: 4.5042e-05 seconds.

    // if reached here // no issues found return with code 0 status
    return 0;
}