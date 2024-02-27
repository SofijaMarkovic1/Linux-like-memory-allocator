//
// Created by os on 2/5/23.
//

#ifndef MOJPROJEKAT_SLABALLOCATOR_HPP
#define MOJPROJEKAT_SLABALLOCATOR_HPP

#include "../h/Cache.hpp"
//#include "../h/syscall_c.hpp"
class SlabAllocator {
private:
    static Cache* cacheTCB;
    static Cache* cacheSEM;
    static Cache* cacheMYBUFFER;
    static Cache* cacheSCHEDULERNODE;
    static Cache* cacheSEMNODE;
    static Cache* cacheSLEEPNODE;
    static Cache* cache5;
    static Cache* cache6;
    static Cache* cache7;
    static Cache* cache8;
    static Cache* cache9;
    static Cache* cache10;
    static Cache* cache11;
    static Cache* cache12;
    static Cache* cache13;
    static Cache* cache14;
    static Cache* cache15;
    static Cache* cache16;
    static Cache* cache17;

    static Cache* head, *tail;


    static size_t TCB_SIZE;
    static size_t SEM_SIZE;
    static size_t SEM_NODE_SIZE;
    static size_t SLEEP_NODE_SIZE;
    static size_t MY_BUFFER_SIZE;
    static size_t SCHEDULER_NODE_SIZE;


    static void shrinkAllExcept(Cache* c);

public:
    static void initSlabAllocator(size_t tcb, size_t sleepNode, size_t sem, size_t semNode, size_t myBuffer, size_t schedulerNode){
        TCB_SIZE = tcb;
        SLEEP_NODE_SIZE = sleepNode;
        SEM_SIZE = sem;
        SEM_NODE_SIZE = semNode;
        MY_BUFFER_SIZE = myBuffer;
        SCHEDULER_NODE_SIZE = schedulerNode;
    }
    static void deleteSlabAllocator(){
        Cache* cur = head;
        while(cur){
            Cache* temp = cur;
            cur = cur->getNext();
            Cache::destroyCache(temp);
        }
    }

    static void* allocTCB();
    static void freeTCB(void* t);



    static void* allocSem();
    static void freeSem(void* s);

    static void* allocMyBuffer();
    static void freeMyBuffer(void* b);

    static void* allocSchedulerNode();
    static void freeSchedulerNode(void* n);

    static void * allocSemNode();
    static void freeSemNode(void* n);

    static void* allocSleepNode();
    static void freeSleepNode(void* n);

    static void* allocBuff(size_t size);
    static void freeBuff(void* obj);


};


#endif //MOJPROJEKAT_SLABALLOCATOR_HPP
