//
// Created by marko on 20.4.22..
//

#include "../lib/hw.h"
#include "../h/tcb.hpp"
#include "../h/printing.hpp"
#include "../h/syscall_c.h"

/*
bool finishedA = false;
bool finishedB = false;
bool finishedC = false;
bool finishedD = false;

uint64 fibonacci(uint64 n) {
    if (n == 0 || n == 1) { return n; }
    if (n % 10 == 0) {thread_dispatch(); }
    return fibonacci(n - 1) + fibonacci(n - 2);
}


void workerBodyA(void* arg) {

    //printString("USAO U A\n");
    for (uint64 i = 0; i < 10; i++) {
        printString("A: i="); printInt(i); printString("\n");
        for (uint64 j = 0; j < 10000; j++) {
            for (uint64 k = 0; k < 30000; k++) {  }

           thread_dispatch();
        }
    }
    printString("A finished!\n");
    //TCB::running->setFinished(true);
    finishedA = true;
    thread_dispatch();

}

void workerBodyB(void* arg) {
    for (uint64 i = 0; i < 16; i++) {
        printString("B: i="); printInt(i); printString("\n");
        for (uint64 j = 0; j < 10000; j++) {
            for (uint64 k = 0; k < 30000; k++) { }
            thread_dispatch();
        }
    }
    printString("B finished!\n");
    //TCB::running->setFinished(true);
    finishedB = true;


    thread_dispatch();
}

void workerBodyC(void* arg) {
    uint8 i = 0;
    for (; i < 3; i++) {
        printString("C: i="); printInt(i); printString("\n");
    }

    printString("C: dispatch\n");
    __asm__ ("li t1, 7");
    thread_dispatch();

    uint64 t1 = 0;
    __asm__ ("mv %[t1], t1" : [t1] "=r"(t1));

    printString("C: t1="); printInt(t1); printString("\n");

    uint64 result = fibonacci(12);
    printString("C: fibonaci="); printInt(result); printString("\n");

    for (; i < 6; i++) {
        printString("C: i="); printInt(i); printString("\n");
    }

    printString("C finished!\n");
    //TCB::running->setFinished(true);
    finishedC = true;
    thread_dispatch();

}

void workerBodyD(void* arg) {
    uint8 i = 10;
    for (; i < 13; i++) {
        printString("D: i="); printInt(i); printString("\n");
    }

    printString("D: dispatch\n");
    __asm__ ("li t1, 5");
    thread_dispatch();

    uint64 result = fibonacci(16);
    printString("D: fibonaci="); printInt(result); printString("\n");

    for (; i < 16; i++) {
        printString("D: i="); printInt(i); printString("\n");
    }

    printString("D finished!\n");
    //TCB::running->setFinished(true);
    finishedD = true;
    thread_dispatch();

}

void Threads_C_API_test() {
    thread_t threads[4];
    thread_create(&threads[0], workerBodyA, nullptr);
    printString("ThreadA created\n");

    printString("ID A niti:");
    printInt(threads[0]->id);
    printString("\n");

    thread_create(&threads[1], workerBodyB, nullptr);
    printString("ThreadB created\n");

    printString("ID B niti:");
    printInt(threads[1]->id);
    printString("\n");

    thread_create(&threads[2], workerBodyC, nullptr);
    printString("ThreadC created\n");

    printString("ID C niti:");
    printInt(threads[2]->id);
    printString("\n");

    thread_create(&threads[3], workerBodyD, nullptr);
    printString("ThreadD created\n");

    printString("ID D niti:");
    printInt(threads[3]->id);
    printString("\n");

    while (!(finishedA && finishedB && finishedC && finishedD)) {
       thread_dispatch();
    }



}
*/