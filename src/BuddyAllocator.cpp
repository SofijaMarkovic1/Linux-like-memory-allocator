//
// Created by os on 2/1/23.
//

#include "../h/BuddyAllocator.hpp"
#include "../test/printing.hpp"

BuddyAllocator::BuddyAllocator() {
    start = HEAP_START_ADDR;
    for (int i=BUCKET_SIZE-1, nblks = 1; i >= 0; i--, nblks*=2) {
        numOfBlocks[i] = nblks;
        for (int j=0; j<nblks; j++)
            bucket[i][j] = false;
    }
    bucket[BUCKET_SIZE-1][0] = true;
}
inline int BuddyAllocator::getFreeBlock(int size) const {
    for (int i=0; i<numOfBlocks[size]; i++)
        if (bucket[size][i]) return i;
    return -1;
}

void *BuddyAllocator::alloc(int size) {
    if(size>=24) return nullptr; //Not enough memory
    if (size<12) size = 12; // Exception
    size -= 12;
    int block = -1, current= size;
    for (; block<0 && current<BUCKET_SIZE; current++)
        block = getFreeBlock(current);
    if (block<0) return nullptr; // No available memory
    setBlock(--current,block, false);
    while (--current>=size) {
        block *= 2;
        setBlock(current,block+1,true);
    }
    return getBlockAddr(size + 12,block);
}

int BuddyAllocator::fromSizeToExpOf2(size_t sz) {
    size_t i=1;
    int x = 0;
    while (i < sz){
        i <<= 1;
        x++;
    }
    return x;
}

void *BuddyAllocator::getBlockAddr(int size, int block) const {
    return (void*)((char*)start + (size_t)(block*(1<<size)));
}

BuddyAllocator* BuddyAllocator::getInstance() {
    static BuddyAllocator instance;
    return &instance;
}

void BuddyAllocator::NOfBlocks() const {
    for(int i=BUCKET_SIZE-1; i>=0; i--){
        printString("Velicina 2^");
        printInt(12+i);
        printString(": ");
        int x=0;
        for(int j=0; j<numOfBlocks[i]; j++) {
            if (bucket[i][j]) x++;
        }
        printInt(x);
        printString("\n");
    }
}

void BuddyAllocator::free(void *addr, size_t sz) {
    int s = fromSizeToExpOf2(sz);
    int block = (int)((char*)addr - (char*)start)/(1<<s);
    s-=6;
    bucket[s][block] = true;
    block = block % 2 ? block-1 : block;
    while (bucket[s][block] && bucket[s][block + 1] && s < BUCKET_SIZE - 1){
        bucket[s][block] = false;
        bucket[s][block+1] = false;
        bucket[s+1][block/2] = true;
        block = block/2;
        block = block % 2 ? block-1 : block;
        s++;
    }
}
