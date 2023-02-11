//
// Created by os on 8/22/22.
//

#ifndef PROJECT_BASE_BUFFER_HPP
#define PROJECT_BASE_BUFFER_HPP
#include "../h/syscall_c.h"
#include "printing.hpp"

#include "../lib/console.h"
#include "MemoryAllocator.hpp"

class Buffer {
private:
    int cap;
    int *buffer;
    int head, tail;

    sem_t spaceAvailable;
    sem_t itemAvailable;
    sem_t mutexHead;
    sem_t mutexTail;

public:
    Buffer(int _cap);
    ~Buffer();

    void put(int val);
    int get();

    int getCnt();
    friend class MemoryAllocator;
    int numOfElems=0;

};

#endif //PROJECT_BASE_BUFFER_HPP
