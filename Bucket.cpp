#include "Bucket.h"

#include <iostream>
using namespace std;

// Bucket constructor
Bucket::Bucket() {
    size = 0;
    localDepth = 1;
    this->bucketSize = 4;
    bucketArray = new int[bucketSize];
}

// Bucket destructor 
Bucket::~Bucket() {
    delete[] bucketArray;
}

// PARAM: int value is the size of the bucket
// Bucket constructor
Bucket::Bucket(int value) {
    size = 0;
    localDepth = 1;
    bucketSize = value;
    bucketArray = new int[bucketSize];
}

// PARAM: int value is the value to be inserted into the bucket
void Bucket::insert(int value) {
    if (size == bucketSize) {
        cout << "full" << endl;
        return;
    }
    bucketArray[size] = value;
    size++;

}

// PARAM: int value is the value to be removed from the bucket
void Bucket::remove(int value) {
    for (int i = 0; i < size; i++) {
        if (bucketArray[i] == value) {
            bucketArray[i] = bucketArray[size - 1];
            size--;
            return;
        }
    }
}

// PARAM: int value is the value to be checked from the bucket
// POST: Returns boolean, true if found, false if not
bool Bucket::contains(int value) {
    for (int i = 0; i < size; i++) {
        if (bucketArray[i] == value) {
            return true;
        }
    }
    return false;
}

// POST: Returns the bucket array
int* Bucket::getElements() {
    return bucketArray;
}

// POST: Returns the current size of the bucket
int Bucket::getSize() {
    return size;
}

// POST: Returns the current localDepth of the bucket
int Bucket::getLocalDepth()
{
    return localDepth;
}

// PARAM: set the current local depth of the bucket
void Bucket::setLocalDepth(int n)
{
    localDepth = n;
}

// increment the local depth by 1
void Bucket::addLocalDepth()
{
    localDepth++;
}
