//Author: Brian Erichsen Fagundes
//MSD - Spring of 2024
//Malloc replacement / implementation
#include <iostream>
#include <chrono>
#include "hashTable.h"
#include "bMalloc.h"
#include "test.h"



int main () {
    //performs my custom testing for the hash class and BMalloc class
    test_hash_class();
    test_bMalloc();
    test_standard_new_delete();
        
//Time taken for 1000 allocations and deallocations: 0.000136417 seconds. std
// Time taken for 1000 allocations and deallocations: 0.00140958 seconds. mine

// if reached here // no issues found return with code 0 status
    return 0;
}