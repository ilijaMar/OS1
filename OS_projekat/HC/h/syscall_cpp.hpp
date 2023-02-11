//
// Created by os on 8/20/22.
//

#ifndef PROJECT_BASE_SYSCALL_CPP_HPP
#define PROJECT_BASE_SYSCALL_CPP_HPP
#include "syscall_c.h"
#include "scheduler.hpp"
#include "tcb.hpp"
void* operator new (size_t size);
void operator delete (void* pt);
class Thread {
public:
    Thread (void (*body)(void*), void* arg);
    virtual ~Thread ();
    int start ();
    static void dispatch ();
    static int sleep (time_t);
    static void wrapper(void* arg);

protected:
    Thread ();
    virtual void run () {}
private:
    thread_t myHandle;
};

class Semaphore {
public:
    Semaphore (unsigned init = 1);
    virtual ~Semaphore ();
    int wait ();
    int signal ();
private:
    sem_t myHandle;
};


class Console {
public:
    static char getc ();
    static void putc (char c);
};

#endif //PROJECT_BASE_SYSCALL_CPP_HPP
