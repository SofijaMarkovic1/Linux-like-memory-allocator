//
// Created by os on 7/24/22.
//

#ifndef PROJECT_BASE_CONSOLE_HPP
#define PROJECT_BASE_CONSOLE_HPP
#include "../h/myBuffer.hpp"
#include "../lib/hw.h"
#include "../h/TCB.hpp"
//#include "../h/MemoryAllocator.hpp"
#include "../h/syscall_c.hpp"
class console {
public:
    static myBuffer* inputBuffer;
    static myBuffer* outputBuffer;
    static void consoleHandlerInput(void*);
    static void consoleHandlerOutput(void*);
    static TCB* consoleThreadInput;
    static TCB* consoleThreadOutput;
    static void init();
    static void waitTillTheEnd();
};


#endif //PROJECT_BASE_CONSOLE_HPP
