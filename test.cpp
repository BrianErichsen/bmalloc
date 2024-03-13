#include "test.h"
#include "hashTable.h"
#include <iostream>
#include "bMalloc.h"
#include <chrono>


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
    B_Malloc b;

    //allocates a large number of small memory objects
    const int smallObjectCount = 100;
    for (int i = 0; i < smallObjectCount; ++i) {
        void* smallObject = b.allocate(sizeof(int));
        b.deallocate(smallObject);
    }
    
    //Allocates a large number of large memory objects
    const int largeObjectCount = 100;
    for (int i = 0; i < largeObjectCount; ++i) {
        void* largeObject = b.allocate(sizeof(char));
        b.deallocate(largeObject);
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
    //asserts
    std::cout << "Dynamic int value from B_Malloc: " << *dynamicInt << std::endl;
    b.deallocate(dynamicInt);

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
    duration.count() << " seconds." << std::endl;

    // //----

    // const int allocationCount = 100;
    // for (int i = 0; i < allocationCount; ++i) {
    //     // Allocate
    //     void* allocatedMemory = b.allocate(sizeof(int));

    //     // Check for memory overlap
    //     // Fill the allocated memory with a known pattern
    //     int pattern = 0xDEADBEEF;
    //     std::fill(static_cast<int*>(allocatedMemory), static_cast<int*>(allocatedMemory) + sizeof(int), pattern);

    //     // Deallocate
    //     b.deallocate(allocatedMemory);
    //     //allocate -- fill 0 - 1000

    //     // Check if the content of the deallocated memory is still the expected pattern
    //     int* deallocatedMemoryContent = static_cast<int*>(allocatedMemory);
    //     if (*deallocatedMemoryContent != pattern) {
    //         std::cerr << "Memory overlap or corruption detected!" << std::endl;
    //     }
    // }
}//end of test allocation for B Malloc class bracket

//function to test and time the standard library using new and delete
    void test_standard_new_delete() {
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
    }//end of bracket for testing new and delete standard library