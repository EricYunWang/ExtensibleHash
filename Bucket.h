#ifndef BUCKET_H
#define BUCKET_H

using namespace std;

class Bucket {
private:
    int bucketSize;
    int* bucketArray;
    int size;
    int localDepth;

public:
    Bucket();
    ~Bucket();
    Bucket(int value);
    void insert(int value);
    void remove(int value);
    bool contains(int value);
    int* getElements();
    int getSize();
    int getLocalDepth();
    void setLocalDepth(int n);
    void addLocalDepth();
};

#endif  // BUCKET_H