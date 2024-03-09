#include "test.h"
#include "hashTable.h"
#include <iostream>


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