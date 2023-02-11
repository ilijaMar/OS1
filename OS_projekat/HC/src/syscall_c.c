//
// Created by os on 8/6/22.
//

#include "../h/syscall_c.h"
#include "../lib/hw.h"






void* mem_alloc (size_t size){

    uint64 brojBlokova=size/MEM_BLOCK_SIZE;
    uint64 ostatak=size%MEM_BLOCK_SIZE;
    uint64 kod=1;
    if(ostatak!=0) brojBlokova+=1;

    __asm__ volatile("mv a0, %0" : : "r" (kod));//u A0 je kod operacije tj da se radi o mem_alloc
    __asm__ volatile("mv a1, %0" : : "r" (brojBlokova));                                                      // da li moze ovako? u a1 je argument size koji predstavlja VELICINU PROSTORA U BLOKOVIMA
    __asm__ volatile("ecall");//izazovi spoljasnji prekid
    void* returnValue;
    __asm__ volatile("mv %0,a0" : "=r" (returnValue));


    return returnValue;


}

int mem_free(void* adresa){
    uint64 kod=2;
    void* ad=adresa;
    __asm__ volatile("mv a1, %0" : : "r" (ad));
    __asm__ volatile("mv a0, %0" : : "r" (kod));

    __asm__("ecall");
    int returnValue;

    asm volatile("sd a0, %0" : "=m" (returnValue));
    return returnValue;
}

int thread_create(
        thread_t* handle,
        void(*start_routine)(void*),
        void* arg


){


    __asm__ volatile("mv a3, a2");//a3-arg
    __asm__ volatile("mv a2, a1");//a2-start routine
    __asm__ volatile("mv a1, a0");//a1-handle
    __asm__ volatile("li a0, 11");





    __asm__("ecall");

    return 0;
}
int thread_create_CPPAPI(
        thread_t* handle,
        void(*start_routine)(void*),
        void* arg


){


    __asm__ volatile("mv a3, a2");//a3-arg
    __asm__ volatile("mv a2, a1");//a2-start routine
    __asm__ volatile("mv a1, a0");//a1-handle
    __asm__ volatile("li a0, 14");





    __asm__("ecall");

    return 0;
}
int thread_exit(){
    uint64 kod=12;
    __asm__ volatile("mv a0, %0" : : "r" (kod));

    __asm__("ecall");


    return 0;
}

void thread_dispatch (){
    uint64 kod=13;
    __asm__ volatile("mv a0, %0" : : "r" (kod));

    __asm__("ecall");

}

int sem_open (
        sem_t* handle,
        unsigned init
){

    __asm__ volatile("mv a2, a1");//a2-init
    __asm__ volatile("mv a1, a0");//a1-handle
    __asm__ volatile("li a0, 21");

    __asm__("ecall");
    return 0;

}

int sem_close (sem_t handle){
    __asm__ volatile("mv a1, a0");//a1-handle
    __asm__ volatile("li a0, 22");

    __asm__("ecall");
    return 0;
}
int sem_wait (sem_t id){
    __asm__ volatile("mv a1, a0");//a1-id
    __asm__ volatile("li a0, 23");

    __asm__("ecall");
    int returnValue;

    asm volatile("sd a0, %0" : "=m" (returnValue));
    return returnValue;


}
int sem_signal (sem_t id){
    __asm__ volatile("mv a1, a0");//a1-id
    __asm__ volatile("li a0, 24");

    __asm__("ecall");
    int returnValue;

    asm volatile("sd a0, %0" : "=m" (returnValue));
    return returnValue;

}

void statusChange(){
    __asm__ volatile("li a0, 25");
    __asm__("ecall");



}

int getThreadId(){
    __asm__ volatile("li a0, 26");
    __asm__("ecall");

    return 0;
}

char getc(){


    return __getc();
    /*
    __asm__ volatile("li a0, 41\n\t"
                     "ecall");

    char i = 0;
    __asm__ volatile("mv %[i], a0 " : [i] "=r" (i));

    //asm volatile("sd a0, %0" : "=m" (returnValue));

    return i;
    */


}
void putc(char c){

    /*
    __asm__ volatile("mv a1, a0");//a1-c
    __asm__ volatile("li a0, 42");
    __asm__("ecall");
    */
    __putc(c);
}

