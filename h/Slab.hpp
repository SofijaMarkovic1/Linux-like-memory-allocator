//
// Created by os on 2/4/23.
//

#ifndef MOJPROJEKAT_SLAB_HPP
#define MOJPROJEKAT_SLAB_HPP
#include "../lib/hw.h"
#include "../h/BuddyAllocator.hpp"


class Slab {
private:
    using Function = void (*)(void*);
    Function constructor;
    Function destructor;

    unsigned numOfEntries;
    unsigned numOfFullEntries;
    size_t szOfObject;
    Slab* next;
    bool* bitMap; //is entry free

    void* mem; //entries
public:
    static Slab* createSlab(unsigned num, size_t sz, Function ctor, Function dtor);
    static void destroySlab(Slab* s);
    bool isEmpty() const { return numOfFullEntries == 0;}
    bool isFull() const { return numOfFullEntries == numOfEntries;}
    bool isObjectInThisSlub(const char* adrOfObject);
    char* getPlaceForObject();
    int freeObject(char* adrOfObject);
    void setNext(Slab* nxt){ next = nxt;}
    Slab* getNext(){ return next;}
    //void setPrev(Slab* prv){ prev = prv;}
    //Slab* getPrev(){ return prev;}

};


#endif //MOJPROJEKAT_SLAB_HPP
