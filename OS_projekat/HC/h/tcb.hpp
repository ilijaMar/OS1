// Created by os on 8/1/22.
//

#ifndef PROJECT_BASE_TCB_HPP
#define PROJECT_BASE_TCB_HPP
#include "scheduler.hpp"
#include "../lib/hw.h"
#include "../h/syscall_c.h"
#include "../h/printing.hpp"
#include "../h/MemoryAllocator.hpp"
class TCB{
public:
    uint64 *stack;//pokazivac na niz lokaciju u memoriji koji predstavlja stek
    ~TCB(){delete[] stack;}
    //using Body = void(*)();
    using BodyArg=void(*)(void*);//pokazivac na funckiju koja nema argumente i nema povratnu vrednost i predstavlja telo korutine

    //static TCB *thread_create(BodyArg body,void* arg);//moramo da znamo koje telo izvrsava, i njen stek
    static void thread_exit();

    static int ID;
    int id=ID++;
    bool isFinished() const;
    void setFinished(bool finished); //geteri i seteri za finished

    uint64 getTimeSlice() const { //geteri i seteri za timeSlice
        return timeSlice;
    }

    void setTimeSlice(uint64 timeSlice) {
        TCB::timeSlice = timeSlice;
    }

    static void yield();//predavanje procesora od strane korutine

    static TCB *running;
    static int getThreadId();
    static int ubi(int id);
    enum Status{
        SEM_DEAD,READY,RUNNING,BLOCKED
    };

    Status status=READY;

private: //pocetni kontekst je metoda korutine body a stek je prazan sp pokazuje na najvecu mem lokaciju jer raste ka nizim adresama

    TCB(BodyArg b,void* arg):
    bodyArg(b),
    argument(arg),
    finished(false)
    {

        uint64 brojBlokova=DEFAULT_STACK_SIZE/MEM_BLOCK_SIZE;

        stack = (bodyArg== nullptr) ? nullptr : (uint64*)MemoryAllocator::ma->mem_alloc(brojBlokova);

        context={ bodyArg== nullptr? 0 : (uint64) &(threadWrapper), stack==nullptr ? 0 : (uint64) &stack[DEFAULT_STACK_SIZE]};

        //kada kreiramo korutinu ubacimo je u skedzule
        if(bodyArg!=nullptr){Scheduler::put(this);} //ako je main ne stavljamo je u sceduler

    }
    TCB(BodyArg b,void* arg,uint64 a):
            bodyArg(b),
            argument(arg),
            finished(false)
    {

        uint64 brojBlokova=DEFAULT_STACK_SIZE/MEM_BLOCK_SIZE;

        stack = (bodyArg== nullptr) ? nullptr : (uint64*)MemoryAllocator::ma->mem_alloc(brojBlokova);

        context={ bodyArg== nullptr? 0 : (uint64) &(threadWrapper), stack==nullptr ? 0 : (uint64) &stack[DEFAULT_STACK_SIZE]};

        //kada kreiramo korutinu ubacimo je u skedzule


    }
    struct Context{
        //svi registri koje koristi korutina
        uint64 ra;//stack pointer
        uint64 sp;//dokle je korutina stigla tj mesto na koje korutina treba da se vrati(ono sto upisujem u pc)
        // ostale registe R0-R31 cuvacemo na samom steku


    };



    BodyArg bodyArg;
    void* argument;

    Context context;
    bool finished;//naznaka da li je korutina gotova

    uint64 timeSlice=DEFAULT_TIME_SLICE;//koliko ce se dugo izvrsavati korutina kada joj se dodeli procesor
    static uint64 timeSliceProgress;//dokle je stigla korutina

    friend class Riscv;
    friend class MemoryAllocator;

    void* operator new (size_t size);
    void *operator new[](size_t size);
    void operator delete (void* addr);
    void operator delete[](void *addr);


    //metoda koja se prva izvrsava za svaku novokreiranu nit ona ce da poziva Body
    static void threadWrapper();

    //metoda koja cuva sp ra strukture Context tekuceg procesa i podmece isto to novoizabranog procesa
    static void contextSwitch(Context *old,Context *newChosen);

    //vrsi promenu kontektsa pomocu yield
public: static void dispatch();

};


#endif //PROJECT_BASE_TCB_HPP
