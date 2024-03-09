#include "bMalloc.h"
#include "hashTable.h"
#include <unistd.h>
#include <sys/mman.h>

//implementation of bMalloc class // see bMalloc.h for class description

//default constructor
B_Malloc::B_Malloc() {
    const size_t initialSize = 16;//size is arbitrary
    hashTable.resize(initialSize);//sets the hashtable to initial size
    //iterates through whole hash table
    for (size_t i = 0; i < initialSize; ++i) {
        hashTable[i].address = nullptr;//sets all addresses to null
        hashTable[i].size = 0;// sets all sizes to 0
    }
}

//default destructor
B_Malloc::~B_Malloc() {
    //cleanup and deallocate resources
}

//I had to change my configuration to Linux to support getpagesize
void* B_Malloc::allocate(size_t bytesToAllocate) {
    const size_t pageSize = getpagesize();

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
    hashTable[hashFunction(allocatedAddress)].address = allocatedAddress;
    hashTable[hashFunction(allocatedAddress)].size = bytesToAllocate;

    return allocatedAddress;//returns new allocated address
}//end of allocate method bracket

//default deallocate method to free memory
void B_Malloc::deallocate(void* ptr) {
    //finds the index for given pointer to be removed from hash table
    size_t index = hashFunction(ptr);

    //if index is valid and equal to a address in hash table
    if (index != hashTable.size() && hashTable[index].address == ptr) {
        //performs the lazy delete
        hashTable[index].address = nullptr;
        hashTable[index].size = 0;

        //https://linux.die.net/man/2/munmap
        //deallocates memory by using munmap sys call
        //int munmap(void *addr, size_t length);
        munmap(ptr, hashTable[index].size);
    } else {
        //only reaches here when given pointer was not found in hash table
        std::cerr << "Error: Invalid pointer for deallocation!" << std::endl;
    }
}//end of deallocate method bracket

size_t B_Malloc::hashFunction(void* address) {
    return reinterpret_cast<size_t>(address) & hashTable.size();
}

//this creates a temp instance
void* B_Malloc::operator new(std::size_t size) {
    return B_Malloc().allocate(size);
}

//creates temp instance
void B_Malloc::operator delete(void* ptr) noexcept {
    B_Malloc().deallocate(ptr);
}