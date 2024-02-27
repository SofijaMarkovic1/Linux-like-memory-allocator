//
// Created by os on 2/4/23.
//

#ifndef MOJPROJEKAT_CACHE_HPP
#define MOJPROJEKAT_CACHE_HPP
#include "../h/Slab.hpp"
class Cache {
private:
    //main info
    char* name;
    size_t sizeOfObject;
    unsigned numOfEntriesInSlabs;
    unsigned numOfSlabs;
    unsigned numOfObjects;
    size_t sizeOfOneSlab;
    //bool doShrink; //TODO

    //constructor and destructor
    using Function = void (*)(void*);
    Function constructor;
    Function destructor;

    //lists of slabs
    Slab* emptyHead, *emptyTail;
    Slab* fullHead, *fullTail;
    Slab* halfFullHead, *halfFullTail;

    enum Error{NO_ERROR, CANT_ALLOCATE_NEW_SLAB, CANT_ALLOCATE_OBJECT, DEALLOCATION_FROM_EMPTY_CACHE, NULLPTR_OBJECT, OBJECT_NOT_IN_CACHE};
    Error e;
    Cache* next;
    static unsigned calculateBestNumOfEntries(size_t szOfObject); //sz - sizeOfObject, done
    int addSlab(); //done
public:
    static Cache* createCache(char* name, size_t size, Function ctor, Function dtor); //done
    static void destroyCache(Cache* c);
    int shrink(); //done
    void* allocObject(); //done
    void freeObject(void* object); //done
    void printCacheInfo() const;
    int printError();
    bool isObjectInThisCache(void* obj);
    Cache* getNext() const { return next;}
    void setNext(Cache* c) { next = c;}

};


#endif //MOJPROJEKAT_CACHE_HPP
