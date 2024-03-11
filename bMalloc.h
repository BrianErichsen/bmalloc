#ifndef BMALLOC_H
#define BMALLOC_H
//author: Brian Erichsen Fagundes
//MSD - spring 2024
// Brian's_Malloc class represents my onw implementation of using system
//calls for allocating/deallocating virtual memory from the OS

#include <iostream>
#include "hashTable.h"

class B_Malloc {
public:
    //public constructors and destructors
    B_Malloc();
    ~B_Malloc();

    // void* operator new(std::size_t size);
    // void operator delete(void* ptr) noexcept;

    void* allocate(size_t bytesToAllocate);
    void deallocate(void* ptr);

private:
    // std::vector<HashEntry> hashTable;
    HashTable hashT;
    size_t hashFunction(void* address);
};//end of class bracket

#endif //BMALLOC_H