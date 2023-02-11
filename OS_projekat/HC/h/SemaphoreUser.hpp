//
// Created by os on 8/19/22.
//

#ifndef PROJECT_BASE_SEMAPHORE_HPP
#define PROJECT_BASE_SEMAPHORE_HPP

#endif //PROJECT_BASE_SEMAPHORE_HPP
#include "../h/list.hpp"
#include "../h/tcb.hpp"
#include "printing.hpp"
#include "../lib/hw.h"
class SemaphoreUser{

public:
     ~SemaphoreUser();
     int signalUser();
     int waitUser();
     SemaphoreUser(unsigned in): value(in){

     }
private:

    void* operator new (size_t size);

    void operator delete (void* addr);

    friend class Riscv;


    int value;

    List<TCB> waiting;

};
