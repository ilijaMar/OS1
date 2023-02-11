//
// Created by marko on 20.4.22..
//

#include "../h/riscv.hpp"
#include "../lib/console.h"
#include "../h/printing.hpp"
#include "../h/tcb.hpp"
#include "../h/SemaphoreUser.hpp"
#include "../h/MemoryAllocator.hpp"
#include "../h/syscall_c.h"
void Riscv::popSppSpie()
{
    __asm__ volatile ("csrw sepc, ra");
    __asm__ volatile ("sret");
}

void Riscv::handleTrap() {

    uint64 scause=r_scause();

    sem_t* semhandle;
    sem_t semhToClose;
    sem_t semhandleSigWait;
    thread_t* handle;
    void(*start_routine)(void*);
    void* arg;
    size_t argument;
    unsigned init;
    char karakter;



    __asm__ volatile("mv %0,a1" : "=r" (karakter));

    __asm__ volatile("mv %0,a2" : "=r" (init));
    __asm__ volatile("mv %0,a1" : "=r" (semhandle));
    __asm__ volatile("mv %0,a1" : "=r" (semhandleSigWait));
    __asm__ volatile("mv %0,a1" : "=r" (semhToClose));

    __asm__ volatile("mv %0,a1" : "=r" (argument));

    __asm__ volatile("mv %0,a1" : "=r" (handle));
    __asm__ volatile("mv %0,a2" : "=r" (start_routine));
    __asm__ volatile("mv %0,a3" : "=r" (arg));
    if(scause==0x0000000000000009UL || scause==0x0000000000000008UL){//ecall u SMODU!!!!

        uint64 volatile sepc = r_sepc();
        uint64 volatile status=r_sstatus();
        uint64 volatile sepc1 = r_sepc();

        sepc = sepc +4;
        __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));


        uint64 kodFunkcije;
        __asm__ volatile("mv %0,a0" : "=r" (kodFunkcije));



        if(MemoryAllocator::ma== nullptr)
            MemoryAllocator::initHeader();

        if(kodFunkcije==0x000000000000001UL){


            void* returnValue=MemoryAllocator::ma->mem_alloc(argument);
            if(returnValue== nullptr)
                returnValue=(void*)-1;
            __asm__ volatile("mv a0, %0" : : "r" (returnValue));

        }else if(kodFunkcije==0x000000000000002UL){
            void* argument;
            __asm__ volatile("mv %0,a1" : "=r" (argument));

            int returnValue=MemoryAllocator::ma->mem_free(argument);
            __asm__ volatile("mv a0, %0" : : "r" (returnValue));
        }else if(kodFunkcije==0x00000000000000BUL){

            (*handle) = new TCB(start_routine, arg);

        }else if(kodFunkcije==0x00000000000000EUL){

            (*handle) = new TCB(start_routine, arg,1);

        }else if(kodFunkcije==0x00000000000000CUL) {
            TCB::thread_exit();
            w_sstatus(status);
            w_sepc(sepc1);
        }else if(kodFunkcije==0x00000000000000DUL) {

            TCB::dispatch();
            w_sstatus(status);
            w_sepc(sepc1);
        }else if(kodFunkcije==0x000000000000015UL){//sem open
            (*semhandle)=new SemaphoreUser(init);
        }else if(kodFunkcije==0x000000000000016UL){//sem close
            delete semhToClose;
        }else if(kodFunkcije==0x000000000000017UL){//sem wait
            int rez=(semhandleSigWait)->waitUser();

            __asm__ volatile("mv a0, %0" : : "r" (rez));
            w_sstatus(status);
            w_sepc(sepc1);
        }else if(kodFunkcije==0x000000000000018UL){//sem signal
            int rez=(semhandleSigWait)->signalUser();
            __asm__ volatile("mv a0, %0" : : "r" (rez));
        }else if(kodFunkcije==0x000000000000019UL){//statusChange
            //uint64 volatile status=r_sstatus();
            //status&=~0x100;
            //w_sstatus(status);
            Riscv::mc_sstatus(Riscv::SSTATUS_SPP);

            //mc_sstatus(SSTATUS_SPP);
        }else if(kodFunkcije==0x00000000000001AUL){
            TCB::getThreadId();
            w_sstatus(status);
            w_sepc(sepc1);
        }else if(kodFunkcije==0x000000000000029UL) {//getc
            char result=__getc();
            __putc('R');
            //printString("Pokupio sam:");
            //__putc(result);
            //printString("\n");
            __asm__ volatile("mv a0,%[result] " : : [result] "r" (result));

            //__asm__ volatile("mv a0, %0" : : "r" (rez));


        }else if(kodFunkcije==0x00000000000002AUL) {//put
            __putc(karakter);

        }

        //Riscv::w_sstatus(status);

        //Riscv::mc_sip(Riscv::SIP_SSIE);

    }else if(scause==0x8000000000000001UL){//softverski prekid tj prekid od tajmera

        mc_sip(SIP_SSIE);

    }else if(scause==0x8000000000000009UL){//spoljasnji prekid od konzole

        mc_sip(SIP_SSIE);
        console_handler();

    }else{


        //nista od ovoga
        //print scause
        /*
        printString("Scause:");
        printInt(r_scause());
        printString("\n");

        printString("sepc:");
        printInt(r_sepc());
        printString("\n");

       //print sepc
       printString("Sepc:");
       printInteger(r_sepc());
       printString("\n");
       //print stval
       printString("Stval:");
       printInteger(r_stval());
       printString("\n");
        */
    }
}