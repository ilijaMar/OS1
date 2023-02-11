//
// Created by os on 8/19/22.
//
#include "../h/SemaphoreUser.hpp"


int SemaphoreUser::signalUser(){

    if(waiting.isEmpty()){
        value++;
    }
    else{

        TCB* freed=waiting.removeFirst();
        if(freed!= nullptr) {
            (freed)->status = TCB::READY;

            Scheduler::put(freed);

        }
    }
    return 0;

}
int SemaphoreUser::waitUser() {

    if(value==0){

        TCB::running->status = TCB::BLOCKED;
        waiting.addLast(TCB::running);
        TCB::dispatch();
    }
    else{

        value--;
    }

    if (TCB::running->status == TCB::SEM_DEAD){
        TCB::running->status=TCB::READY;
        return -1;
    }

    return 0;
    /*
    if(value==0){
        TCB::running->status = TCB::BLOCKED;
        waiting.addLast(TCB::running);
        TCB::dispatch();
    }else{
        value=value-1;
    }
    if (TCB::running->status == TCB::SEM_DEAD) {
        TCB::running->status = TCB::READY;
        return -1;
    }
    return 0;

    if (value < 0) {
        TCB::running->status = TCB::BLOCKED;
        waiting.addLast(TCB::running);
        TCB::dispatch();
    }
    if (TCB::running->status == TCB::SEM_DEAD){
        TCB::running->status=TCB::READY;
        return -1;
    }
    return 0;
     */
}


SemaphoreUser::~SemaphoreUser() {
    while (TCB* freed=waiting.removeFirst()){
        (freed)->status=TCB::SEM_DEAD;
        Scheduler::put(freed);
    }
}


void* SemaphoreUser::operator new (size_t size){
    uint64 brojBlokova=size/MEM_BLOCK_SIZE;
    uint64 ostatak=size%MEM_BLOCK_SIZE;

    if(ostatak!=0) brojBlokova+=1;
    return MemoryAllocator::ma->mem_alloc(brojBlokova);
}

void SemaphoreUser::operator delete (void* addr){

    MemoryAllocator::ma->mem_free(addr);

}
