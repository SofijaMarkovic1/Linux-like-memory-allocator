//
// Created by os on 2/4/23.
//

#include "../h/Cache.hpp"
#include "../test/printing.hpp"
unsigned Cache::calculateBestNumOfEntries(size_t szOfObject) {
    if(szOfObject < (1<<12)) return (1<<12) / szOfObject;
    else return 1;
}

Cache *Cache::createCache(char *name, size_t size, Cache::Function ctor, Cache::Function dtor) {
    Cache* c = (Cache*)BuddyAllocator::getInstance()->alloc(BuddyAllocator::fromSizeToExpOf2(sizeof(Cache)));
    if(c == nullptr) return nullptr; //TODO greska nema memorije za pravljenje kesa sa imenom name
    c->name = name;
    c->sizeOfObject = size;
    c->constructor = ctor;
    c->destructor = dtor;
    c->numOfSlabs = 0;
    c->numOfObjects = 0;
    c->e = NO_ERROR;
    c->numOfEntriesInSlabs = calculateBestNumOfEntries(c->sizeOfObject);
    c->sizeOfOneSlab = c->sizeOfObject<(1<<12) ? 1<<12 : BuddyAllocator::fromSizeToExpOf2(c->sizeOfObject);
    c->emptyHead = c->emptyTail = c->fullHead = c->fullTail = c->halfFullHead = c->halfFullTail = nullptr;
    c->next = nullptr;
    if(c->addSlab() < 0){ //TODO greska nema memorije za pravljenje kesa sa imenom name
        BuddyAllocator::getInstance()->free(c, sizeof(Cache));
        return nullptr;
    }
    return c;
}

int Cache::addSlab() {
    Slab* s = Slab::createSlab(numOfEntriesInSlabs, sizeOfObject, constructor, destructor);
    if(s == nullptr) {
        e = CANT_ALLOCATE_NEW_SLAB;
        return -1; //TODO greska nema memorije za dodavanje novog slab-a u kes sa imenom name
    }
    s->setNext(nullptr);
    if(emptyHead == nullptr){
        emptyHead = emptyTail = s;
    }
    else{
        emptyTail->setNext(s);
        emptyTail = emptyTail->getNext();
    }
    numOfSlabs++;
    return 0;
}

int Cache::shrink() {
    if(emptyHead == nullptr) return 0; //no empty slabs
    if(emptyHead->getNext() == nullptr && halfFullHead == nullptr) return 0; //no other place to put data
    int count = 0;
    while(emptyHead){
        Slab* temp = emptyHead;
        emptyHead = emptyHead->getNext();
        if(emptyHead == nullptr) emptyTail = nullptr;
        temp->setNext(nullptr);
        Slab::destroySlab(temp);
        count++;
        numOfSlabs--;
    }
    return count;
}

void *Cache::allocObject() {
    void* object = nullptr;
    if(halfFullHead){ //there are half full slabs
        object = halfFullHead->getPlaceForObject();
        if(object == nullptr) {
            e = CANT_ALLOCATE_OBJECT;
            return nullptr;
        }
        if(halfFullHead->isFull()){ //if it's full move it to Full list
            Slab* temp = halfFullHead;
            halfFullHead = halfFullHead->getNext();
            if(halfFullHead == nullptr) halfFullTail = nullptr;
            temp->setNext(nullptr);
            if(fullHead){
                fullTail->setNext(temp);
                fullTail = fullTail->getNext();
            }
            else{
                fullTail = fullHead = temp;
            }
        }
        numOfObjects++;
        return object;
    } else if(emptyHead){
        object = emptyHead->getPlaceForObject();
        if(object == nullptr) {
            e = CANT_ALLOCATE_OBJECT;
            return nullptr;
        }
        if(emptyHead->isFull()){ //if it's full move it to Full list
            Slab* temp = emptyHead;
            emptyHead = emptyHead->getNext();
            if(emptyHead == nullptr) emptyTail = nullptr;
            temp->setNext(nullptr);
            if(fullHead){
                fullTail->setNext(temp);
                fullTail = fullTail->getNext();
            }
            else{
                fullTail = fullHead = temp;
            }
            numOfObjects++;
            return object;
        } else{ //if it's not full move it to HalfFull list
            Slab* temp = emptyHead;
            emptyHead = emptyHead->getNext();
            if(emptyHead == nullptr) emptyTail = nullptr;
            temp->setNext(nullptr);
            if(halfFullHead){
                halfFullTail->setNext(temp);
                halfFullTail = halfFullTail->getNext();
            }
            else{
                halfFullHead = halfFullTail = temp;
            }
            numOfObjects++;
            return object;
        }
    } else{ //add new empty slab
        if(addSlab() < 0) {
            e = CANT_ALLOCATE_OBJECT;
            return nullptr; //TODO greska nema memorije za vise objekata u kesu name
        }
        object = emptyHead->getPlaceForObject();
        if(object == nullptr) return nullptr;
        if(emptyHead->isFull()){ //if it's full move it to Full list
            Slab* temp = emptyHead;
            emptyHead = emptyHead->getNext();
            if(emptyHead == nullptr) emptyTail = nullptr;
            temp->setNext(nullptr);
            if(fullHead){
                fullTail->setNext(temp);
                fullTail = fullTail->getNext();
            }
            else{
                fullTail = fullHead = temp;
            }
            numOfObjects++;
            return object;
        } else{ //if it's not full move it to HalfFull list
            Slab* temp = emptyHead;
            emptyHead = emptyHead->getNext();
            if(emptyHead == nullptr) emptyTail = nullptr;
            temp->setNext(nullptr);
            if(halfFullHead){
                halfFullTail->setNext(temp);
                halfFullTail = halfFullTail->getNext();
            }
            else{
                halfFullHead = halfFullTail = temp;
            }
            numOfObjects++;
            return object;
        }
    }
    e = CANT_ALLOCATE_OBJECT;
    return nullptr;
}

void Cache::freeObject(void *object) {
    //if(numOfObjects==0 || object == nullptr || !isObjectInThisCache(object)) {
        //TODO greska objekat za dealokaciju na adresi object nije alociran u kesu name
        //return;
    //}
    if(numOfObjects == 0){
        e = DEALLOCATION_FROM_EMPTY_CACHE;
        return;
    }
    if(object == nullptr){
        e = NULLPTR_OBJECT;
        return;
    }
    if(!isObjectInThisCache(object)){
        e = OBJECT_NOT_IN_CACHE;
        return;
    }
    Slab* cur, *prev;
    cur = halfFullHead;
    prev = nullptr;
    while (cur){
        if(cur->isObjectInThisSlub((char*)object)) break;
        prev = cur;
        cur = cur->getNext();
    }
    if(cur){ //cur - half full
        if(cur->freeObject((char*)object) < 0)return;
        numOfObjects--;
        if(cur->isEmpty()){ // if it became empty
            if(prev){
                prev->setNext(cur->getNext());
            } else{
                halfFullHead = halfFullHead->getNext();
                if(halfFullHead == nullptr) halfFullTail = nullptr;
            }
            if(emptyHead){
                emptyTail->setNext(cur);
                emptyTail = emptyTail->getNext();
                cur->setNext(nullptr);
            }
            else{
                emptyHead = emptyTail = cur;
                cur->setNext(nullptr);
            }
        }
        return;
    }
    cur = fullHead;
    prev = nullptr;
    while (cur){
        if(cur->isObjectInThisSlub((char*)object)) break;
        prev = cur;
        cur = cur->getNext();
    }
    if(cur){ //cur - full
        if(cur->freeObject((char*)object)<0) return;
        numOfObjects--;
        if(cur->isEmpty()){ // if it became empty
            if(prev){
                prev->setNext(cur->getNext());
            } else{
                fullHead = fullHead->getNext();
                if(fullHead == nullptr) fullTail = nullptr;
            }
            if(emptyHead){
                emptyTail->setNext(cur);
                emptyTail = emptyTail->getNext();
                cur->setNext(nullptr);
            }
            else{
                emptyHead = emptyTail = cur;
                cur->setNext(nullptr);
            }
        } else{ //it became half full
            if(prev){
                prev->setNext(cur->getNext());
            } else{
                fullHead = fullHead->getNext();
                if(fullHead == nullptr) fullTail = nullptr;
            }
            if(halfFullHead){
                halfFullTail->setNext(cur);
                halfFullTail = halfFullTail->getNext();
                cur->setNext(nullptr);
            }
            else{
                halfFullHead = halfFullTail = cur;
                cur->setNext(nullptr);
            }

        }
        return;
    }
    e = OBJECT_NOT_IN_CACHE;
    //TODO greska objekat za dealokaciju na adresi object nije alociran u kesu name
}

void Cache::destroyCache(Cache *c) {
    //free Empty slabs
    if(c == nullptr) return;
    Slab* cur = c->emptyHead;
    while(cur){
        Slab* temp = cur;
        cur = cur->getNext();
        Slab::destroySlab(temp);
    }
    c->emptyHead = c->emptyTail = nullptr;

    //free Half Full slabs
    cur = c->halfFullHead;
    while(cur){
        Slab* temp = cur;
        cur = cur->getNext();
        Slab::destroySlab(temp);
    }
    c->halfFullHead = c->halfFullTail = nullptr;

    //free Full slabs
    cur = c->fullHead;
    while(cur){
        Slab* temp = cur;
        cur = cur->getNext();
        Slab::destroySlab(temp);
    }
    c->fullTail = c->fullHead = nullptr;

    //free the cache
    c->next = nullptr;
    BuddyAllocator::getInstance()->free(c, sizeof(Cache));
}

void Cache::printCacheInfo() const {
    printString("-> CACHE-INFO:\n1) Cache name: ");
    printString(name);
    printString("\n2) Slot size: ");
    printInt(sizeOfObject);
    printString("\n3) Total number of blocks: ");
    printInt(sizeOfOneSlab*numOfSlabs/4096);
    printString("\n4) Number of slabs: ");
    printInt(numOfSlabs);
    printString("\n5) Number of objects in one slab: ");
    printInt(numOfEntriesInSlabs);
    printString("\n6) Occupancy percentage of cache: ");

    unsigned percent1 = numOfObjects*100/(numOfSlabs*numOfEntriesInSlabs);
    printInt(percent1);

    printString("%\n");
}

bool Cache::isObjectInThisCache(void *obj) {
    Slab* cur = halfFullHead;
    while (cur){
        if(cur->isObjectInThisSlub((char*)obj)) return true;
        cur = cur->getNext();
    }
    cur = fullHead;
    while (cur){
        if(cur->isObjectInThisSlub((char*)obj)) return true;
        cur = cur->getNext();
    }
    return false;
}

int Cache::printError() {
    int ret = 0;
    switch (e) {
        case NO_ERROR:{
            break;
        }
        case CANT_ALLOCATE_NEW_SLAB:{
            ret = -1;
            printString("Can't allocate new slab\n");
            break;
        }
        case CANT_ALLOCATE_OBJECT:{
            ret = -2;
            printString("Can't allocate new object\n");
            break;
        }
        case DEALLOCATION_FROM_EMPTY_CACHE:{
            ret = -3;
            printString("Trying deallocation from an empty cache\n");
            break;
        }
        case NULLPTR_OBJECT:{
            ret = -4;
            printString("Passed pointer is nullptr\n");
            break;
        }
        case OBJECT_NOT_IN_CACHE:{
            ret = -5;
            printString("Passed object is not in this cache\n");
            break;
        }
    }
    e = NO_ERROR;
    return ret;
}
