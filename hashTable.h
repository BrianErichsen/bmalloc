#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <vector>
//this class represents a linear probing hash table class where
//it stores addresses and the associated size of memory allocated to that
//address

class HashTable {
public:
    HashTable(size_t initialSize);//constructor with initial size
    ~HashTable();//destructor

    void insert(void* address, size_t size);
    void remove(void* address);
    size_t find(void* address);
    const size_t EMPTY = static_cast<size_t>(-1);
    
    size_t getTableSize() const {
        return currentSize;
    }
    void* getTableAddress(size_t index) const {
        if (index < currentSize) {
            return table[index].address;
        } else
        return nullptr;
    }
    
    size_t getTableEntrySize(size_t index) {
        if (index < currentSize) {
            return table[index].size;
        } else
            return 0;
    }

private:
    struct HashEntry { //represents each entry or bucket
        void* address;//stores address of allocated memory
        size_t size;//and size of allocated memory block
        //default constructor
        HashEntry() : address(nullptr), size(0) {}
        //constructor that takes arguments
        HashEntry(void* addr, size_t s) : address(addr), size(s) {}
    };//end of struct bracket

    // std::vector<HashEntry> table;
    HashEntry* table;
    size_t currentSize;
    size_t initialSize;

    size_t hashFunction(void* address);
    void grow();

};//end of class bracket

#endif // HASH_TABLE_H