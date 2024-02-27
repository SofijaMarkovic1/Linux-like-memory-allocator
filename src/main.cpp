//
// Created by os on 7/9/22.
//
#include "../h/syscall_cpp.hpp"
#include "../test/printing.hpp"
#include "../h/riscv.hpp"
#include "../h/console.hpp"
#include "../javni_test/drugi/userMain.hpp"


extern "C" void supervisorTrap();
int main(){
    SlabAllocator::initSlabAllocator(sizeof(TCB), sizeof(TCB::sleepNode), sizeof(Sem), sizeof(Sem::node), sizeof(myBuffer), sizeof(Scheduler::node));
    thread_t main;
    Riscv::w_stvec((uint64) &supervisorTrap);
    thread_create(&main, nullptr, nullptr);
    TCB::running = main;
    console::init();
    Riscv::ms_sstatus(Riscv::SSTATUS_SIE);
    //userMode();
    userMain();
    //privilagedMode();
    //BuddyAllocator::getInstance()->NOfBlocks();
    console::waitTillTheEnd();
    //SlabAllocator::deleteSlabAllocator();
    return 0;
}
