#ifndef EXTENSIBLEHASHTABLE_H
#define EXTENSIBLEHASHTABLE_H

#include <iostream>
#include "Bucket.h"

class ExtensibleHashTable {
private:
    Bucket** directory;
    int globalDepth;
    int bucketSize;
    int directorySize;

    int hash(int value);

public:
    ExtensibleHashTable();
    ExtensibleHashTable(int bSize);
    ~ExtensibleHashTable();

    void insert(int value);
    bool remove(int value);
    bool find(int value);
    void print();
    void doubleDir();
    void split(int index, int value);
};

#endif  // EXTENSIBLEHASHTABLE_H