#include "ExtensibleHashTable.h"
#include <iostream>
#include <cmath>
using namespace std;

// ExtensibleHashTable constructor
ExtensibleHashTable::ExtensibleHashTable() {
    globalDepth = 1;
    bucketSize = 4;
    directorySize = 2;
    directory = new Bucket * [directorySize];
    directory[0] = new Bucket();
    directory[1] = new Bucket();
}

// PARAM: int bSize is the size of the bucket
// ExtensibleHashTable constructor
ExtensibleHashTable::ExtensibleHashTable(int bSize) {
    this->globalDepth = 1;
    this->bucketSize = bSize;
    this->directorySize = 2;
    this->directory = new Bucket * [directorySize];
    directory[0] = new Bucket(bSize);
    directory[1] = new Bucket(bSize);
}

// ExtensibleHashTable destructor
ExtensibleHashTable::~ExtensibleHashTable() {
    delete[] directory;
}

// PARAM: int value is the value to be hashed
// POST: returns the hashed value
int ExtensibleHashTable::hash(int value) {
    int n = globalDepth;
    return value % int (pow(2, n));
}

// PARAM: int value is the value to be inserted
void ExtensibleHashTable::insert(int value) {
    int index = hash(value); // find hash value first
    if (directory[index]->getSize() == bucketSize) { // full bucket
        // i=j, double directory size and split the block
        if (globalDepth == directory[index]->getLocalDepth()) { 
            doubleDir();
            split(index, value);
        }
        // if not i=j, just split
        if (globalDepth > directory[index]->getLocalDepth()) {
            split(index, value);
        }
    }
    else{
        directory[index]->insert(value);
    }

}

// PARAM: int value is the value to be removed
// POST: returns a boolean, true if value is found and removed, false if not
// I adjusted the function from the instruction. Instead of using hash, I searched all buckets.
bool ExtensibleHashTable::remove(int value)
{
    bool found = false;
    for (int i = 0; i < directorySize; i++) {
        for (int j = 0; j < directory[i]->getSize(); j++) {
            if (directory[i]->getElements()[j] == value) {
                found = true;
                directory[i]->remove(value);
                j--;
            }
        }
    }
    return found;
}

// PARAM: int value is the value to be searched
// POST: returns a boolean, true if value is found.
bool ExtensibleHashTable::find(int value)
{
    bool found = false;
    int index = hash(value);
    for (int j = 0; j < directory[index]->getSize(); j++) {
        if (directory[index]->getElements()[j] == value) {
            found = true;
        }
    }
    return found;
}

// print the entire hash table as instructed
void ExtensibleHashTable::print()
{
    for (int i = 0; i < directorySize; i++) {
        
        for (int k = 0; k < i; k++) { // case where duplicate bucket found due to pointers.
            if (directory[k] == directory[i]) {
                cout << i << ": " << directory[i] << " -->"<< endl;
                i++;
                break;
            }
        }
        if (i >= directorySize) { // to stop crash
            return;
        }
        // otherwise print normally
        cout << i << ": "<< directory[i]<< " -->" << " [";
        for (int j = 0; j < directory[i]->getSize(); j++) {
            if (j+1 == directory[i]->getSize()) {
                cout << *(directory[i]->getElements() + j);
                break;
            }
            cout << *(directory[i]->getElements() + j) << ", ";
        }
        cout << "] (" << directory[i]->getLocalDepth() << ")" << endl;
    }
}

// helper function to double the directory
void ExtensibleHashTable::doubleDir()
{
    globalDepth = globalDepth + 1;
    int newSize = directorySize * 2;
    Bucket ** newDirectory = new Bucket * [newSize];

    // 2 for loops to adjust pointers
    for (int i = 0; i < directorySize; i++) {
        newDirectory[i] = directory[i];
    }
    for (int i = directorySize; i < newSize; i++) {
        newDirectory[i] = directory[i - directorySize];
    }
    directorySize = newSize;
    delete[] directory;
    directory = newDirectory;
}

// PARAM: int index and value are the passed in value from insertion
// helper function
void ExtensibleHashTable::split(int index, int value)
{
    int newindex = hash(value);
    // handling cases, try to find a directory that can be used to split if the passed in index and new hashed index are the same
    if (index == newindex) {
        for (int i = 0; i < directory[index]->getSize(); i++) {
            int oldValue = directory[index]->getElements()[i];
            if (hash(oldValue) != index) {
                newindex = hash(oldValue);
                break;
            }
        }
        // not possible to insert a value into the hash table
        try {
            if (index == newindex) {
                throw runtime_error("runtime_error exception: bucket filled with identical search key \n" );
            }
        }
        catch (exception const& e) {
            cout << e.what();
        }

    }

    // if new index is different, then just do the work.
    directory[newindex] = new Bucket();
    directory[index]->addLocalDepth();
    directory[newindex]->setLocalDepth(directory[index]->getLocalDepth());
    for (int i = 0; i < directory[index]->getSize(); i++)
    {
        int oldValue = directory[index]->getElements()[i];
        if (hash(oldValue) != index) {
            directory[index]->remove(oldValue);
            insert(oldValue);
            i--;
        }
    }
    insert(value);

}

