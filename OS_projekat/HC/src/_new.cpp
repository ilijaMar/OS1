//
// Created by os on 8/2/22.
//

#include "../h/syscall_c.h"
#include "../lib/mem.h"
#include "../h/printing.hpp"

/*
uint64 i=0;
void *operator new(uint64 n){//broj bajtova koji treba da alocira

    return mem_alloc(n);

    //return __mem_alloc(n);

}


void *operator new[](uint64 n){//broj bajtova koji treba da alocira (niz)
    return mem_alloc(n);
    //printString("Usao u _new[]\n");
    //return __mem_alloc(n);

}

void operator delete(void *p){//brise 1 pointer
    mem_free(p);
    //__mem_free(p);
}

void operator delete[](void *p){
    mem_free(p);
    //__mem_free(p);
}
*/