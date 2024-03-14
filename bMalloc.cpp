//Author: Brian Erichsen Fagundes
//MSD - Spring of 2024
//Malloc replacement / implementation
#include "bMalloc.h"
#include "hashTable.h"
#include <unistd.h>
#include <sys/mman.h>
#include <vector>

//implementation of bMalloc class // see bMalloc.h for class description

//default constructor // sets hashTable initial size to 100
B_Malloc::B_Malloc() : hashT(100) {}

//default destructor
B_Malloc::~B_Malloc() {
    //cleanup and deallocate resources
}

//I had to change my configuration to Linux to support getpagesize
void* B_Malloc::allocate(size_t bytesToAllocate) {
    const size_t pageSize = getpagesize();//gets the page size
    //rounds up how many bytes to the next multiple of the page size
    bytesToAllocate = ((bytesToAllocate + pageSize - 1) / pageSize) *
    pageSize;
    //uses system call - request a block of memory size given # of bytes
    //anonymous and private flags make sure that mapping is private and
    //not associated with any file // -1 is the file descriptor param
    //0 as offset param
    //void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
    void * allocatedAddress = mmap(nullptr, bytesToAllocate, PROT_READ |
    PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    //if failed then displays error and returns a nullpointer
    if (allocatedAddress == MAP_FAILED) {
        std::cerr << "Allocation has failed!" << std::endl;
        return nullptr;
    }
    //inserts the returned pointer and allocation size in hash table
    hashT.insert(allocatedAddress, bytesToAllocate);

    return allocatedAddress;//returns new allocated address
}//end of allocate method bracket

//default deallocate method to free memory
void B_Malloc::deallocate(void* ptr) {
    //finds the index for given pointer to be removed from hash table
    size_t index = hashT.find(ptr);
    //for debugging reasons
    // std::cout << "Index: " << index << ", Size: " << hashT.getTableSize() <<
    // ", Address: " << hashT.getTableAddress(index) << std::endl;

    //if index is valid and equal to a address in hash table
    if (index != -1) {
        //removes entries of address and size
        hashT.remove(ptr);
        //https://linux.die.net/man/2/munmap
        //deallocates memory by using munmap sys call
        //int munmap(void *addr, size_t length);
        munmap(ptr, hashT.getTableEntrySize(index));
    } else {
        //only reaches here when given pointer was not found in hash table
        std::cerr << "Error: Invalid pointer for deallocation!" << std::endl;
    }
}//end of deallocate method bracket