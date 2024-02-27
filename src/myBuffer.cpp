//
// Created by os on 7/24/22.
//

#include "../h/myBuffer.hpp"

myBuffer::myBuffer(int _cap) {
    //buffer = (char *)MemoryAllocator::malloc(MemoryAllocator::bytesToBlocks(sizeof(char) * _cap));
    buffer = (char*)SlabAllocator::allocBuff(sizeof(char*) * _cap);
    if(buffer == nullptr) return;
    Sem::open(&itemAvailable, 0);
    Sem::open(&spaceAvailable, _cap);
    cap = _cap + 1;
    head = tail = 0;
}

myBuffer::~myBuffer() {
    //MemoryAllocator::free(buffer);
    SlabAllocator::freeBuff(buffer);
    Sem::close(itemAvailable);
    Sem::close(spaceAvailable);
}

void myBuffer::put(char c) {
    Sem::wait(spaceAvailable);

    buffer[tail] = c;
    tail = (tail + 1) % cap;

    Sem::signal(itemAvailable);
}

char myBuffer::get() {
    Sem::wait(itemAvailable);

    char ret = buffer[head];
    head = (head + 1) % cap;

    Sem::signal(spaceAvailable);

    return ret;
}

int myBuffer::getCnt() {
    int ret;

    if (tail >= head) {
        ret = tail - head;
    } else {
        ret = cap - head + tail;
    }

    return ret;
}

myBuffer *myBuffer::createBuffer(int _cap) {
    //myBuffer* newBuf = (myBuffer*)MemoryAllocator::malloc(MemoryAllocator::bytesToBlocks(sizeof(myBuffer)));
    myBuffer* newBuf = (myBuffer*)SlabAllocator::allocMyBuffer();
    if(newBuf == nullptr) return nullptr;
    //newBuf->buffer = (char *)MemoryAllocator::malloc(MemoryAllocator::bytesToBlocks(sizeof(char) * _cap));
    newBuf->buffer = (char*)SlabAllocator::allocBuff(sizeof(char)*_cap);
    if(newBuf->buffer == nullptr){
        SlabAllocator::freeMyBuffer(newBuf);
        return nullptr;
    }
    Sem::open(&newBuf->itemAvailable, 0);
    Sem::open(&newBuf->spaceAvailable, _cap);
    newBuf->cap = _cap + 1;
    newBuf->head = newBuf->tail = 0;
    return newBuf;
}
