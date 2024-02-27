//
// Created by os on 2/1/23.
//

#ifndef OS2V1_BUDDYALLOCATOR_HPP
#define OS2V1_BUDDYALLOCATOR_HPP

#include "../lib/hw.h"


class BuddyAllocator {
public:
    static BuddyAllocator* getInstance();
    void* alloc (int size); //returns 2^size block
    void free(void* addr, size_t sz);
    void NOfBlocks() const;
    static int fromSizeToExpOf2(size_t sz);
protected:
    int getFreeBlock (int size) const;
    void setBlock (int size, int block, bool a) { bucket[size][block] = a; }
    void* getBlockAddr(int size, int block) const;


private:
    BuddyAllocator ();
    const void* start;
    static const int BUCKET_SIZE = 12;
    static const int MAX_BLOCKS = 1<<11;
    bool bucket[BUCKET_SIZE][MAX_BLOCKS];
    int numOfBlocks[BUCKET_SIZE];
};


#endif //OS2V1_BUDDYALLOCATOR_HPP
