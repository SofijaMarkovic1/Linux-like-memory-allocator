//
// Created by os on 2/6/23.
//
#include "../h/slab.h"

void kmem_init(void *space, int block_num){
    SlabAllocator::initSlabAllocator(sizeof(TCB), sizeof(TCB::sleepNode), sizeof(Sem), sizeof(Sem::node), sizeof(myBuffer), sizeof(Scheduler::node));
}
kmem_cache_t *kmem_cache_create(const char *name, size_t size, void (*ctor)(void *), void (*dtor)(void *)){
    return Cache::createCache((char*)name, size, ctor, dtor);
}
int kmem_cache_shrink(kmem_cache_t *cachep){
    if(cachep == nullptr) return -1;
    return cachep->shrink();
}

void *kmem_cache_alloc(kmem_cache_t *cachep){
    return cachep->allocObject();
}

void kmem_cache_free(kmem_cache_t *cachep, void *objp){
    if(objp == nullptr) return;
    cachep->freeObject(objp);
}

void *kmalloc(size_t size){
    return SlabAllocator::allocBuff(size);
}

void kfree(const void *objp){
    SlabAllocator::freeBuff((void*)objp);
}

void kmem_cache_destroy(kmem_cache_t *cachep){
    Cache::destroyCache(cachep);
}

void kmem_cache_info(kmem_cache_t *cachep){
    cachep->printCacheInfo();
}
int kmem_cache_error(kmem_cache_t *cachep){
    return cachep->printError();
}