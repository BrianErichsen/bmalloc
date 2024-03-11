#include "test.h"
#include "hashTable.h"
#include <iostream>
#include "bMalloc.h"


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
    B_Malloc allocator;

    //test 1: Allocate and deallocate small blocks
    int* block1 = static_cast<int*>(allocator.allocate(sizeof(int)));
    if (block1) {
        *block1 = 42;
        std::cout << *block1 << std::endl;
        allocator.deallocate(block1);
    }
    //Test 2: Allocate multiples blocks and ensures they don't overlap
    int* block2 = static_cast<int*>(allocator.allocate(sizeof(int)));
    int* block3 = static_cast<int*>(allocator.allocate(sizeof(char)));

    if (block2 == block3 || block2 + 1 == reinterpret_cast<int*>(block3)) {
        std::cerr << "Error: Overlapping allocations detected!" << std::endl;
    }

    //clean up
    allocator.deallocate(block2);
    allocator.deallocate(block3);
}//end of test allocation for B Malloc class bracket