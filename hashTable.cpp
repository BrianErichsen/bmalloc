#include "hashTable.h"

//implementation of hashTable linear probing class
//constructor that takes initial size
HashTable::HashTable(size_t initialSize) : currentSize(0) {
    table.resize(initialSize);
    for (size_t i = 0; i < initialSize; ++i) {
        table[i].address = nullptr;
        table[i].size = 0;
    }
}
//public destructor
HashTable::~HashTable() {
    //deallocates resources
}

size_t HashTable::hashFunction(void* address) {
    //reinterpret cast converts ptrs to ints and vice-versa
    return reinterpret_cast<size_t>(address) % table.size();
}

void HashTable::insert(void* address, size_t size) {
    //if table is more than half full then grow it
    if (currentSize * 2 > table.size()) {
        grow();
    }

    size_t index = hashFunction(address);

    while (table[index].address != nullptr &&
    table[index].address != address) {
        //does the linear probing to find the next available bucket
        index = (index + 1) % table.size();
    }
    //inserts address and size in the table at specific index
    table[index].address = address;
    table[index].size = size;
    currentSize++;
}

void HashTable::remove(void* address) {
    size_t index = find(address);

    if (index != EMPTY) {
        //performs the lazy delete my marking entry as empty
        table[index].address = nullptr;
        table[index].size = 0;
        currentSize--;
    }
}

size_t HashTable::find(void* address) {
    size_t index = hashFunction(address);

    while (table[index].address != nullptr) {
        if (table[index].address == address) {
            return index;
        }
        //linear probing to find the next bucket
        index = (index + 1) % table.size();
    }
    return EMPTY;//if reached here /// no address found
}

void HashTable::grow() {
    size_t newSize = table.size() * 2; // doubles the size of the table
    //has new size elements where each element is called the default
    //constructor of HashEntry
    std::vector<HashEntry> newTable(newSize, HashEntry());

    for (size_t i = 0; i < table.size(); ++i) {
        if (table[i].address != nullptr) {
            size_t newIndex = hashFunction(table[i].address);

            while (newTable[newIndex].address != nullptr) {
                newIndex = (newIndex + 1) % newSize;
            }
            //copies the entry to the new table
            newTable[newIndex] = table[i];
        }
    }
    //swaps the new table with the original one
    std::swap(table, newTable);
}
