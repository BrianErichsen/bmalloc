#include "hashTable.h"
#include <sys/mman.h>

//implementation of hashTable linear probing class
//constructor that takes initial size
HashTable::HashTable(size_t initialSize) : currentSize(0) {
    this->initialSize = initialSize;

    table = (HashEntry*) mmap(nullptr, initialSize * sizeof(HashEntry), PROT_READ |
    PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    for (size_t i = 0; i < initialSize; ++i) {
        table[i].address = nullptr;
        table[i].size = 0; //redunctant
    }
}
//public destructor
HashTable::~HashTable() {
    //deallocates resources
}

size_t HashTable::hashFunction(void* address) {
    //reinterpret cast converts ptrs to ints and vice-versa
    return (reinterpret_cast<size_t>(address) >> 12) % initialSize;
    //removing offset bits - 12 //
}

void HashTable::insert(void* address, size_t size) {
    //if table is more than half full then grow it
    if (currentSize * 2 > initialSize) {
        grow();
    }

    size_t index = hashFunction(address);

    while (table[index].address != nullptr &&
    table[index].address != address) {
        //does the linear probing to find the next available bucket
        index = (index + 1) % initialSize;
    }
    //inserts address and size in the table at specific index
    table[index].address = address;
    table[index].size = size;
    currentSize++;
}

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
//should return address of entry // finds
//finds means the index where given address where address is
size_t HashTable::find(void* address) {
    size_t index = hashFunction(address);

    while (table[index].address != nullptr) {
        if (table[index].address == address) {
            return index;
        }
        //linear probing to find the next bucket
        index = (index + 1) % initialSize;
    }
    //should return
    return EMPTY;//if reached here /// no address found
}

void HashTable::grow() {
    //get size from hashTable
    // size_t newSize = table.si * 2; // doubles the size of the table
    //has new size elements where each element is called the default
    size_t newSize = initialSize * 2;
    HashEntry* newTable = (HashEntry*) mmap(nullptr, newSize  * sizeof(HashEntry), PROT_READ |
    PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    //
    for (size_t i = 0; i < initialSize; ++i) {
        if (table[i].address != nullptr || table[i].address != (void*) EMPTY) {
            size_t newIndex = hashFunction(table[i].address);

            while (newTable[newIndex].address != nullptr &&
            newTable[newIndex].size != EMPTY) {
                newIndex = (newIndex + 1) % newSize;
            }
            //copies the entry to the new table
            newTable[newIndex].address = table[i].address;
            newTable[newIndex].size = table[i].size;
        }
    }
    //swaps the new table with the original one
    std::swap(table, newTable);
    //updates the initial size
    initialSize = newSize;

    munmap(newTable, initialSize * sizeof(HashEntry));
}
