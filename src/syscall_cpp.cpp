//
// Created by os on 7/24/22.
//

#include "../h/syscall_cpp.hpp"

void *operator new(size_t n)
{
    return mem_alloc(n);
}

void *operator new[](size_t n)
{
    return mem_alloc(n);
}

void operator delete(void *p) noexcept
{
    mem_free(p);
}

void operator delete[](void *p) noexcept
{
    mem_free(p);
}

char Console::getc() {
    return ::getc();
}

void Console::putc(char c) {
    ::putc(c);
}

Semaphore::Semaphore(unsigned int init) {
    sem_open(&myHandle, init);
}

Semaphore::~Semaphore() {
    sem_close(myHandle);
}

int Semaphore::wait() {
    if(myHandle == nullptr) return -1;
    return sem_wait(myHandle);
}

int Semaphore::signal() {
    if(myHandle== nullptr) return -1;
    return sem_signal(myHandle);
}
/*
void *Semaphore::operator new(size_t n) {
    return SlabAllocator::allocSemaphore();
}

void *Semaphore::operator new[](size_t n) {
    return SlabAllocator::allocSemaphore();
}

void Semaphore::operator delete(void *p) noexcept {
    SlabAllocator::freeSemaphore(p);
}

void Semaphore::operator delete[](void *p) noexcept {
    SlabAllocator::freeSemaphore(p);
}
*/
void Thread::dispatch() {
    thread_dispatch();
}

int Thread::sleep(time_t t) {
    return time_sleep(t);
}

Thread::Thread() : Thread(&thread_wrapper, (void*) this){}

int Thread::start() {
    if(myHandle == nullptr) return -1;
    return startCPPthread(myHandle);
}

Thread::~Thread() {
    if(myHandle!= nullptr){
        myHandle->setFinished(true);
        thread_dispatch();
    }
}

Thread::Thread(void (*body)(void *), void *arg) {
    createCPPthread(&myHandle, body, arg);
}

void Thread::thread_wrapper(void *arg){
    Thread* t=(Thread*)arg;
    if(t == nullptr) return;
    t->run();
}
PeriodicThread::PeriodicThread(time_t period): Thread(thread_wrapperP, (void*)new Args(this, period)) {}

void PeriodicThread::thread_wrapperP(void *args) {
    Args* a = (Args*) args;
    if(a->thread == nullptr) return;
    time_t t = a->period;
    while(true){
        a->thread->periodicActivation();
        time_sleep(t);
    }
}