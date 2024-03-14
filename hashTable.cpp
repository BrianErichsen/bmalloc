//Author: Brian Erichsen Fagundes
//MSD - Spring of 2024
//Malloc replacement / implementation
#include "hashTable.h"
#include <sys/mman.h>

//implementation of hashTable linear probing class
//constructor that takes initial size
HashTable::HashTable(size_t initialSize) : currentSize(0) {
    this->initialSize = initialSize;
    //allocates enough resources for table[] of hashEntries to be born
    table = (HashEntry*) mmap(nullptr, initialSize * sizeof(HashEntry), PROT_READ |
    PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    //sets hashentries addresses and sizes to 0
    for (size_t i = 0; i < initialSize; ++i) {
        table[i].address = nullptr;
        table[i].size = 0; //redunctant
    }
}
//public destructor
HashTable::~HashTable() {
    //deallocates resources
}
//hashfunction to convert an address into a index in the table
size_t HashTable::hashFunction(void* address) {
    //reinterpret cast converts ptrs to ints and vice-versa
    //removes the offset bits per address modulated over table size
    return (reinterpret_cast<size_t>(address) >> 12) % initialSize;
}
//method for inserting entries in the table
void HashTable::insert(void* address, size_t size) {
    //if table is more than half full then grow it
    if (currentSize * 2 > initialSize) {
        grow();
    }
    //hashes the address
    size_t index = hashFunction(address);
    //follows linear probing logic
    while (table[index].address != nullptr &&
    table[index].address != address) {
        //does the linear probing to find the next available bucket
        index = (index + 1) % initialSize;
    }
    //inserts address and size in the table at specific index
    table[index].address = address;
    table[index].size = size;
    currentSize++;//increments its size
}
//removes entries from table
void HashTable::remove(void* address) {
    size_t index = find(address);
    // size_t index = hashFunction(address);
    //performs the lazy deleting -- by setting size and address to 0
    /* One form of laziness in VMS is demand zeroing of pages
    */
   //
    if (index != EMPTY && table[index].address != nullptr) {
        //performs the lazy delete my marking entry as empty
        table[index].address = nullptr;
        table[index].size = EMPTY;
        currentSize--;
    }
}

// I am not implememting the proposed finds method in the assignment
//Assignment says private methods that can make the hash table ... finds

//mine find method works by getting an address as param and finds
//which index of the table that address is stored if there
size_t HashTable::find(void* address) {
    //hashes the address to see the first proposed index
    size_t index = hashFunction(address);
    //follows the linear probing logic
    while (table[index].address != nullptr) {
        //only returns if at that index the address stored in same as param
        if (table[index].address == address) {
            return index;
        }
        //linear probing to find the next bucket
        index = (index + 1) % initialSize;
    }
    //should return
    return EMPTY;//if reached here - no address is found in the table
    //I use the empty key word -- is size_t -1 for invalid deallocations
}
//method that doubles table size and allocate proper resources when called
void HashTable::grow() {
    //doubles table's size
    size_t newSize = initialSize * 2;
    //allocate enough resources for creating new table
    HashEntry* newTable = (HashEntry*) mmap(nullptr, newSize  * sizeof(HashEntry), PROT_READ |
    PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    //iterates through table size and copies information when
    //address is different than null and when that slot has not been
    //used before // using empty in size as safe guard when resources
    //for that index have deallocated
    for (size_t i = 0; i < initialSize; ++i) {
        if (table[i].address != nullptr || table[i].size != EMPTY) {
            //finds new index using hashfunction
            size_t newIndex = hashFunction(table[i].address);
            //follows linear probing logic
            while (newTable[newIndex].address != nullptr &&
            newTable[newIndex].size != EMPTY) {
                newIndex = (newIndex + 1) % newSize;
            }
            //copies the entry to the new table -- deep copy
            newTable[newIndex].address = table[i].address;
            newTable[newIndex].size = table[i].size;
        }
    }
    //swaps the new table with the original one
    std::swap(table, newTable);
    //updates the initial size
    initialSize = newSize;
    //deallocate resource of memory from temp table
    munmap(newTable, initialSize * sizeof(HashEntry));
}
