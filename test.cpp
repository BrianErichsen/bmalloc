//Author: Brian Erichsen Fagundes
//MSD - Spring of 2024
//Malloc replacement / implementation
#include "test.h"
#include "hashTable.h"
#include <iostream>
#include "bMalloc.h"
#include <chrono>
#include <cassert>
#include <iomanip>

//function for testing my insertion - deletion and hash class methods
void test_hash_class() {
    HashTable hashTable(10);

    void* address1 = reinterpret_cast<void*>(0x1000);
    size_t size1 = 100;

    void* address2 = reinterpret_cast<void*>(0x2000);
    size_t size2 = 150;

    hashTable.insert(address1, size1);
    hashTable.insert(address2, size2);

    size_t index = hashTable.find(address1);
    if (index != hashTable.EMPTY) {
        std::cout << "Address 1 found at index: " << index << std::endl;
    } else {
        std::cout << "Address 1 not found" << std::endl;
    }

    hashTable.remove(address1);

    index = hashTable.find(address1);
    if (index == hashTable.EMPTY) {
        std::cout << "Address 1 removed from the hash table" << std::endl;
    } else {
        std::cout << "Failed to remove address" << std::endl;
    }
}//end of function to test hash table class methods

//function to test allocation and deallocation
void test_bMalloc() {
    B_Malloc b;//creates a object for allocation and deallocation

    //allocates a large number of small memory objects
    const int smallObjectCount = 100;
    for (int i = 0; i < smallObjectCount; ++i) {
        void* smallObject = b.allocate(sizeof(int));
        b.deallocate(smallObject);
    }
    
    //Allocates a large number of large memory objects
    const int largeObjectCount = 10000000;
    for (int i = 0; i < largeObjectCount; ++i) {
        void* charObject = b.allocate(sizeof(char));
        b.deallocate(charObject);
    }

    // //Deallocates objects and verifies B_Malloc / Hash_Table are correct
    void* obj1 = b.allocate(sizeof(int));
    void* obj2 = b.allocate(sizeof(int));
    b.deallocate(obj1);
    b.deallocate(obj2);

    // //Allocates small and large blocks of memory
    void* smallBlock = b.allocate(sizeof(int));
    void* largeBlock = b.allocate(sizeof(char));
    b.deallocate(smallBlock);
    b.deallocate(largeBlock);

    // //allocates memory for dynamic int and assign a value to be stored
    // //in the memory space
    int* dynamicInt = (int*) b.allocate(sizeof(int));
    *dynamicInt = 69;
    //asserts that dynamicInt holds the value given to that specific address
    assert(*dynamicInt == 69);
    std::cout << "Dynamic int value from B_Malloc: " << *dynamicInt << std::endl;
    b.deallocate(dynamicInt);

    //Performs the benchmark timing -----------
    // //times how long it takes to malloc() and free() memory
    // //Returns a time point representing the current point in time
    // //https://en.cppreference.com/w/cpp/chrono/high_resolution_clock/now
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        void* temp = b.allocate(sizeof(int));
        b.deallocate(temp);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Time taken for 1000 allocations and deallocations: " <<
    std::fixed << std::setprecision(9) << duration.count() << " seconds." << std::endl;

    // performs testing for overlapping
    int* int1 = (int*) b.allocate(sizeof(int));
    *int1 = 70;

    int* int2 = (int*) b.allocate(sizeof(int));
    *int2 = 71;

    //asserts
    assert(*int1 == 70);
    assert(*int2 == 71);

    b.deallocate(int1);
    b.deallocate(int2);
    //-- second part of checking for overlap
    const int count = 400;
    int* allocatedIntegers[count];//creates an array of ints
    //iterates over count amount and allocates resource for each index
    for (int i = 0; i < count; ++i) {
        allocatedIntegers[i] = static_cast<int*>(b.allocate(sizeof(int)));
        *allocatedIntegers[i] = i;//stores a value to that address
    }
    //asserts that no overlaps happened and each int has it's own
    //supposed value
    for (int i = 0; i < count; ++i) {
        assert(*allocatedIntegers[i] == i);
    }
}//end of test allocation for B Malloc class bracket

//function to test and time the standard library using new and delete
    void test_standard_new_delete() {
        
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
    std::fixed << std::setprecision(9) << duration.count() << " seconds." << std::endl;
    }//end of bracket for testing new and delete standard library