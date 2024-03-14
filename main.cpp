//Author: Brian Erichsen Fagundes
//MSD - Spring of 2024
//Malloc replacement / implementation
#include <iostream>
#include <chrono>
#include "hashTable.h"
#include "bMalloc.h"
#include "test.h"

//what is lazy delete? from a hash table?
/* Lazy delete strategy is where an entry for deletion is not immedi-
ately removed from the table. Instead a special flag or marker is used
to indicate that entry is logically deleted but it remains in the table.

--To compile program - simple type on the terminal make malloc
using ./malloc will automatically run tests called in main - some
tests use assertion to make sure that is no overlap and that
program is allocating proper resources.
After done type make clean to clean up exe file and .o files
*/

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