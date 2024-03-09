#ifndef BMALLOC_H
#define BMALLOC_H
//author: Brian Erichsen Fagundes
//MSD - spring 2024
// Brian's_Malloc class represents my onw implementation of using system
//calls for allocating/deallocating virtual memory from the OS

#include <iostream>

class B_Malloc {
public:
    //public constructors and destructors
    B_Malloc();
    ~B_Malloc();

    void* operator new(std::size_t size);
    void operator delete(void* ptr) noexcept;

    void* allocate(size_t bytesToAllocate);
    void deallocate(void* ptr);

private:
    struct HashEntry { //represents each entry or bucket
        void* address;//stores address of allocated memory
        size_t size;//and size of allocated memory block
        //default constructor
        HashEntry() : address(nullptr), size(0) {}
        //constructor that takes arguments
        HashEntry(void* addr, size_t s) : address(addr), size(s) {}
    };
    std::vector<HashEntry> hashTable;
    size_t hashFunction(void* address);
    void growHashTable();
    void* roundUptoPageSize(void* address, size_t pageSize);

};//end of class bracket

#endif //BMALLOC_H