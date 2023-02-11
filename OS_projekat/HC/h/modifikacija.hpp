//
// Created by os on 8/31/22.
//

#ifndef PROJECT_BASE_MODIFIKACIJA_HPP
#define PROJECT_BASE_MODIFIKACIJA_HPP
#include "syscall_c.h"
#include "printing.hpp"
bool finA= false;
bool finB= false;
bool finC= false;

void nitA(void* arg){
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10000; ++j) {
            for (int k = 0; k < 30000; ++k) {

            }
        }
        printString("A:");
        getThreadId();
    }
    finA= true;
    thread_dispatch();
}
void nitB(void* arg){
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10000; ++j) {
            for (int k = 0; k < 30000; ++k) {

            }
        }
        printString("B:");
        getThreadId();
    }
    finB= true;
    thread_dispatch();
}
void nitC(void* arg){
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10000; ++j) {
            for (int k = 0; k < 30000; ++k) {

            }
        }
        printString("C:");
        getThreadId();
    }
    finC= true;
    thread_dispatch();
}
void pokreni_mod_test(){
    thread_t threads[3];
    thread_create(&threads[0], nitA, nullptr);
    printString("Thread A created");

    thread_create(&threads[1], nitB, nullptr);
    printString("Thread B created");

    thread_create(&threads[2], nitC, nullptr);
    printString("Thread C created");

    while (!(finA && finB && finC)) {
        thread_dispatch();
    }
}
#endif //PROJECT_BASE_MODIFIKACIJA_HPP
