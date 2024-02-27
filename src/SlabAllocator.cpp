//
// Created by os on 2/5/23.
//

#include "../h/SlabAllocator.hpp"

Cache* SlabAllocator::cacheTCB = nullptr;
Cache* SlabAllocator::cacheSEM = nullptr;
Cache* SlabAllocator::cacheMYBUFFER = nullptr;
Cache* SlabAllocator::cacheSCHEDULERNODE = nullptr;
Cache* SlabAllocator::cacheSEMNODE= nullptr;
Cache* SlabAllocator::cacheSLEEPNODE= nullptr;
Cache* SlabAllocator::cache5 = nullptr;
Cache* SlabAllocator::cache6 = nullptr;
Cache* SlabAllocator::cache7 = nullptr;
Cache* SlabAllocator::cache8 = nullptr;
Cache* SlabAllocator::cache9 = nullptr;
Cache* SlabAllocator::cache10 = nullptr;
Cache* SlabAllocator::cache11 = nullptr;
Cache* SlabAllocator::cache12 = nullptr;
Cache* SlabAllocator::cache13 = nullptr;
Cache* SlabAllocator::cache14 = nullptr;
Cache* SlabAllocator::cache15 = nullptr;
Cache* SlabAllocator::cache16 = nullptr;
Cache* SlabAllocator::cache17 = nullptr;

Cache* SlabAllocator::head = nullptr;
Cache* SlabAllocator::tail = nullptr;


size_t SlabAllocator::TCB_SIZE = 0;
size_t SlabAllocator::SEM_SIZE= 0;
size_t SlabAllocator::MY_BUFFER_SIZE = 0;
size_t SlabAllocator::SCHEDULER_NODE_SIZE = 0;
size_t SlabAllocator::SEM_NODE_SIZE = 0;
size_t SlabAllocator::SLEEP_NODE_SIZE = 0;


void *SlabAllocator::allocTCB() {
    if(cacheTCB == nullptr){
        cacheTCB = Cache::createCache((char*)"TCB", TCB_SIZE, nullptr, nullptr);
        if(cacheTCB == nullptr) return nullptr;
        cacheTCB->setNext(nullptr);
        if(head == nullptr){
            head = tail = cacheTCB;
        } else{
            tail->setNext(cacheTCB);
            tail = tail->getNext();
        }
    }
    void * object = cacheTCB->allocObject();
    if(object == nullptr){
        shrinkAllExcept(cacheTCB);
        object = cacheTCB->allocObject();
    }
    return object;
}

void SlabAllocator::freeTCB(void* t) {
    if(cacheTCB == nullptr) return;
    cacheTCB->freeObject(t);
}

void *SlabAllocator::allocSem() {
    if(cacheSEM == nullptr){
        cacheSEM = Cache::createCache((char*)"SEM", SEM_SIZE, nullptr, nullptr);
        if(cacheSEM == nullptr) return nullptr;
        cacheSEM->setNext(nullptr);
        if(head == nullptr){
            head = tail = cacheSEM;
        } else{
            tail->setNext(cacheSEM);
            tail = tail->getNext();
        }
    }
    void * object = cacheSEM->allocObject();
    if(object == nullptr){
        shrinkAllExcept(cacheSEM);
        object = cacheSEM->allocObject();
    }
    return object;
}

void SlabAllocator::freeSem(void *s) {
    if(cacheSEM == nullptr) return;
    cacheSEM->freeObject(s);
}

void* SlabAllocator::allocMyBuffer() {
    if(cacheMYBUFFER == nullptr){
        cacheMYBUFFER = Cache::createCache((char*)"MY_BUFFER", MY_BUFFER_SIZE, nullptr, nullptr);
        if(cacheMYBUFFER == nullptr) return nullptr;
        cacheMYBUFFER->setNext(nullptr);
        if(head == nullptr){
            head = tail = cacheMYBUFFER;
        } else{
            tail->setNext(cacheMYBUFFER);
            tail = tail->getNext();
        }
    }
    void * object = cacheMYBUFFER->allocObject();
    if(object == nullptr){
        shrinkAllExcept(cacheMYBUFFER);
        object = cacheMYBUFFER->allocObject();
    }
    return object;
}

void SlabAllocator::freeMyBuffer(void *b) {
    if(cacheMYBUFFER == nullptr) return;
    cacheMYBUFFER->freeObject(b);
}


void *SlabAllocator::allocBuff(size_t size) {
    int x = BuddyAllocator::fromSizeToExpOf2(size);
    size = (1<<x);
    switch (size) {
        case (1<<5):{
            if(cache5 == nullptr){
                cache5 = Cache::createCache((char*)"size-5", 1<<5, nullptr, nullptr);
                if(cache5 == nullptr) return nullptr;
                cache5->setNext(nullptr);
                if(head == nullptr){
                    head = tail = cache5;
                } else{
                    tail->setNext(cache5);
                    tail = tail->getNext();
                }
            }
            void * object = cache5->allocObject();
            if(object == nullptr){
                shrinkAllExcept(cache5);
                object = cache5->allocObject();
            }
            return object;
        }
        case (1<<6):{
            if(cache6 == nullptr){
                cache6 = Cache::createCache((char*)"size-6", 1<<6, nullptr, nullptr);
                if(cache6 == nullptr) return nullptr;
                cache6->setNext(nullptr);
                if(head == nullptr){
                    head = tail = cache6;
                } else{
                    tail->setNext(cache6);
                    tail = tail->getNext();
                }
            }
            void * object = cache6->allocObject();
            if(object == nullptr){
                shrinkAllExcept(cache6);
                object = cache6->allocObject();
            }
            return object;
        }
        case (1<<7):{
            if(cache7 == nullptr){
                cache7 = Cache::createCache((char*)"size-7", 1<<7, nullptr, nullptr);
                if(cache7 == nullptr) return nullptr;
                cache7->setNext(nullptr);
                if(head == nullptr){
                    head = tail = cache7;
                } else{
                    tail->setNext(cache7);
                    tail = tail->getNext();
                }
            }
            void * object = cache7->allocObject();
            if(object == nullptr){
                shrinkAllExcept(cache7);
                object = cache7->allocObject();
            }
            return object;
        }
        case (1<<8):{
            if(cache8 == nullptr){
                cache8 = Cache::createCache((char*)"size-8", 1<<8, nullptr, nullptr);
                if(cache8 == nullptr) return nullptr;
                cache8->setNext(nullptr);
                if(head == nullptr){
                    head = tail = cache8;
                } else{
                    tail->setNext(cache8);
                    tail = tail->getNext();
                }
            }
            void * object = cache8->allocObject();
            if(object == nullptr){
                shrinkAllExcept(cache8);
                object = cache8->allocObject();
            }
            return object;
        }
        case (1<<9):{
            if(cache9 == nullptr){
                cache9 = Cache::createCache((char*)"size-9", 1<<9, nullptr, nullptr);
                if(cache9 == nullptr) return nullptr;
                cache9->setNext(nullptr);
                if(head == nullptr){
                    head = tail = cache9;
                } else{
                    tail->setNext(cache9);
                    tail = tail->getNext();
                }
            }
            void * object = cache9->allocObject();
            if(object == nullptr){
                shrinkAllExcept(cache9);
                object = cache9->allocObject();
            }
            return object;
        }
        case (1<<10):{
            if(cache10 == nullptr){
                cache10 = Cache::createCache((char*)"size-10", 1<<10, nullptr, nullptr);
                if(cache10 == nullptr) return nullptr;
                cache10->setNext(nullptr);
                if(head == nullptr){
                    head = tail = cache10;
                } else{
                    tail->setNext(cache10);
                    tail = tail->getNext();
                }
            }
            void * object = cache10->allocObject();
            if(object == nullptr){
                shrinkAllExcept(cache10);
                object = cache10->allocObject();
            }
            return object;
        }
        case (1<<11):{
            if(cache11 == nullptr){
                cache11 = Cache::createCache((char*)"size-11", 1<<11, nullptr, nullptr);
                if(cache11 == nullptr) return nullptr;
                cache11->setNext(nullptr);
                if(head == nullptr){
                    head = tail = cache11;
                } else{
                    tail->setNext(cache11);
                    tail = tail->getNext();
                }
            }
            void * object = cache11->allocObject();
            if(object == nullptr){
                shrinkAllExcept(cache11);
                object = cache11->allocObject();
            }
            return object;
        }
        case (1<<12):{
            if(cache12 == nullptr){
                cache12 = Cache::createCache((char*)"size-12", 1<<12, nullptr, nullptr);
                if(cache12 == nullptr) return nullptr;
                cache12->setNext(nullptr);
                if(head == nullptr){
                    head = tail = cache12;
                } else{
                    tail->setNext(cache12);
                    tail = tail->getNext();
                }
            }
            void * object = cache12->allocObject();
            if(object == nullptr){
                shrinkAllExcept(cache12);
                object = cache12->allocObject();
            }
            return object;
        }
        case (1<<13):{
            if(cache13 == nullptr){
                cache13 = Cache::createCache((char*)"size-13", 1<<13, nullptr, nullptr);
                if(cache13 == nullptr) return nullptr;
                cache13->setNext(nullptr);
                if(head == nullptr){
                    head = tail = cache13;
                } else{
                    tail->setNext(cache13);
                    tail = tail->getNext();
                }
            }
            void * object = cache13->allocObject();
            if(object == nullptr){
                shrinkAllExcept(cache13);
                object = cache13->allocObject();
            }
            return object;
        }
        case (1<<14):{
            if(cache14 == nullptr){
                cache14 = Cache::createCache((char*)"size-14", 1<<14, nullptr, nullptr);
                if(cache14 == nullptr) return nullptr;
                cache14->setNext(nullptr);
                if(head == nullptr){
                    head = tail = cache14;
                } else{
                    tail->setNext(cache14);
                    tail = tail->getNext();
                }
            }
            void * object = cache14->allocObject();
            if(object == nullptr){
                shrinkAllExcept(cache14);
                object = cache14->allocObject();
            }
            return object;
        }
        case (1<<15):{
            if(cache15 == nullptr){
                cache15 = Cache::createCache((char*)"size-15", 1<<15, nullptr, nullptr);
                if(cache15 == nullptr) return nullptr;
                cache15->setNext(nullptr);
                if(head == nullptr){
                    head = tail = cache15;
                } else{
                    tail->setNext(cache15);
                    tail = tail->getNext();
                }
            }
            void * object = cache15->allocObject();
            if(object == nullptr){
                shrinkAllExcept(cache15);
                object = cache15->allocObject();
            }
            return object;
        }
        case (1<<16):{
            if(cache16 == nullptr){
                cache16 = Cache::createCache((char*)"size-16", 1<<16, nullptr, nullptr);
                if(cache16 == nullptr) return nullptr;
                cache16->setNext(nullptr);
                if(head == nullptr){
                    head = tail = cache16;
                } else{
                    tail->setNext(cache16);
                    tail = tail->getNext();
                }
            }
            void * object = cache16->allocObject();
            if(object == nullptr){
                shrinkAllExcept(cache16);
                object = cache16->allocObject();
            }
            return object;
        }
        case (1<<17):{
            if(cache17 == nullptr){
                cache17 = Cache::createCache((char*)"size-17", 1<<17, nullptr, nullptr);
                if(cache17 == nullptr) return nullptr;
                cache17->setNext(nullptr);
                if(head == nullptr){
                    head = tail = cache17;
                } else{
                    tail->setNext(cache17);
                    tail = tail->getNext();
                }
            }
            void * object = cache17->allocObject();
            if(object == nullptr){
                shrinkAllExcept(cache17);
                object = cache17->allocObject();
            }
            return object;
        }
        default:{
            return nullptr;
        }
    }
    return nullptr;
}

void SlabAllocator::freeBuff(void* obj) {
    if(obj == nullptr) return;
    if(cache5 && cache5->isObjectInThisCache(obj)) {
        cache5->freeObject(obj);
        return;
    }
    if(cache6 && cache6->isObjectInThisCache(obj)) {
        cache6->freeObject(obj);
        return;
    }
    if(cache7 && cache7->isObjectInThisCache(obj)) {
        cache7->freeObject(obj);
        return;
    }
    if(cache8 && cache8->isObjectInThisCache(obj)) {
        cache8->freeObject(obj);
        return;
    }
    if(cache9 && cache9->isObjectInThisCache(obj)) {
        cache9->freeObject(obj);
        return;
    }
    if(cache10 && cache10->isObjectInThisCache(obj)) {
        cache10->freeObject(obj);
        return;
    }
    if(cache11 && cache11->isObjectInThisCache(obj)) {
        cache11->freeObject(obj);
        return;
    }
    if(cache12 && cache12->isObjectInThisCache(obj)) {
        cache12->freeObject(obj);
        return;
    }
    if(cache13 && cache13->isObjectInThisCache(obj)) {
        cache13->freeObject(obj);
        return;
    }
    if(cache14 && cache14->isObjectInThisCache(obj)) {
        cache14->freeObject(obj);
        return;
    }
    if(cache15 && cache15->isObjectInThisCache(obj)) {
        cache15->freeObject(obj);
        return;
    }
    if(cache16 && cache16->isObjectInThisCache(obj)) {
        cache16->freeObject(obj);
        return;
    }
    if(cache17 && cache17->isObjectInThisCache(obj)) {
        cache17->freeObject(obj);
        return;
    }
}

void *SlabAllocator::allocSchedulerNode() {
    if(cacheSCHEDULERNODE == nullptr){
        cacheSCHEDULERNODE = Cache::createCache((char*)"SCHEDULER-NODE", SCHEDULER_NODE_SIZE, nullptr, nullptr);
        if(cacheSCHEDULERNODE == nullptr) return nullptr;
        cacheSCHEDULERNODE->setNext(nullptr);
        if(head == nullptr){
            head = tail = cacheSCHEDULERNODE;
        } else{
            tail->setNext(cacheSCHEDULERNODE);
            tail = tail->getNext();
        }
    }
    void * object = cacheSCHEDULERNODE->allocObject();
    if(object == nullptr){
        shrinkAllExcept(cacheSCHEDULERNODE);
        object = cacheSCHEDULERNODE->allocObject();
    }
    return object;
}

void SlabAllocator::freeSchedulerNode(void *n) {
    if(cacheSCHEDULERNODE == nullptr) return;
    cacheSCHEDULERNODE->freeObject(n);
}

void *SlabAllocator::allocSemNode() {
    if(cacheSEMNODE == nullptr){
        cacheSEMNODE = Cache::createCache((char*)"SEM-NODE", SEM_NODE_SIZE, nullptr, nullptr);
        if(cacheSEMNODE == nullptr) return nullptr;
        cacheSEMNODE->setNext(nullptr);
        if(head == nullptr){
            head = tail = cacheSEMNODE;
        } else{
            tail->setNext(cacheSEMNODE);
            tail = tail->getNext();
        }
    }
    void * object = cacheSEMNODE->allocObject();
    if(object == nullptr){
        shrinkAllExcept(cacheSEMNODE);
        object = cacheSEMNODE->allocObject();
    }
    return object;
}

void SlabAllocator::freeSemNode(void * n) {
    if(cacheSEMNODE == nullptr) return;
    cacheSEMNODE->freeObject(n);
}


void * SlabAllocator::allocSleepNode() {
    if(cacheSLEEPNODE == nullptr){
        cacheSLEEPNODE = Cache::createCache((char*)"SLEEP-NODE", SLEEP_NODE_SIZE, nullptr, nullptr);
        if(cacheSLEEPNODE == nullptr) return nullptr;
        cacheSLEEPNODE->setNext(nullptr);
        if(head == nullptr){
            head = tail = cacheSLEEPNODE;
        } else{
            tail->setNext(cacheSLEEPNODE);
            tail = tail->getNext();
        }
    }
    void * object = cacheSLEEPNODE->allocObject();
    if(object == nullptr){
        shrinkAllExcept(cacheSLEEPNODE);
        object = cacheSLEEPNODE->allocObject();
    }
    return object;
}

void SlabAllocator::freeSleepNode(void *n) {
    if(cacheSLEEPNODE == nullptr) return;
    cacheSLEEPNODE->freeObject(n);
}

void SlabAllocator::shrinkAllExcept(Cache *c) {
    Cache* cur = head;
    while(cur){
        if(cur!=c) cur->shrink();
        cur = cur->getNext();
    }
}


