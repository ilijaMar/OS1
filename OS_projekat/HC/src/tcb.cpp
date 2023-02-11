//
// Created by os on 8/1/22.
//

#include "../h/tcb.hpp"
#include "../h/riscv.hpp"
#include "../h/scheduler.hpp"
#include "../lib/hw.h"
#include "../lib/mem.h"

TCB *TCB::running= nullptr;
int TCB::ID=0;
uint64 TCB::timeSliceProgress=DEFAULT_TIME_SLICE;

bool TCB::isFinished() const {
    return finished;
}

void TCB::setFinished(bool finished) {
    TCB::finished = finished;
}


void TCB::yield() {
    //cuvanje procesoriskih registara obavljamo u supervisorTrap koja predstavlja kod Trap prekidne rutine koja se stalo izvrsava tako da ne mora ovde
    //tako da sad pri sinhronoj promeni konteksta samo hocemo da udjemo u kod te prekidne rutine Trapa tj !da izazovemo prekid

    //__asm__ volatile("ecall");
    //sada u onom delu gde se obradjuje tip prekida moramo da proverimo da li se radi o ecall prekidu



    Riscv::pushRegisters(); //cuvanje konteksta

    TCB::dispatch();

    Riscv::popRegisters(); //restauracija konteksta

}

void TCB::dispatch() {

    //printString("DISPATCH\n");
    //Riscv::pushRegisters();

    TCB *old=running;

    //printString("Tekuca nit je:");
    //printString((char*)old->argument);
    //printString("\n");
    //ako korutina nije zavrsila vracamo je u skedzuler
    if(!old->isFinished() && old->status==READY) {Scheduler::put(old);}

    //iz skedzulera uzimamo sledecu korutinu i proglasavamo je za running
    running=Scheduler::get();


    //treba da sacuvamo ra sp tekuceg procesa i da umetnemo ra sp novog
    TCB::contextSwitch(&old->context,&running->context);

    //Riscv::popRegisters();


}



void TCB::threadWrapper() {
    // ! posto smo do ove tacke dosli iz prekidne rutine tj zbog prekidne rutine(prekidna rutina je zatrazila promenu konteksta) to znaci da smo i dalje u privilegovanom rezimu rada i moramo da se vratimo
    //! tj moramo da uradimo sve da bismo presli u stanje pre prekidne rutine
    //! //(ponovo omogucimo prekide i vratimo se u neprivilegovan rezim)
    Riscv::popSppSpie();//u sustini vraca iz prekidne rutine
    //kada istekne timeSlice poziva se dispath koji menja kontekst i skedzuler bira neku nit koja do sad nije pocela
    //adresa contexta nove niti ce biti u A1 i on ce se postaviti u PC registar a taj context je inicijalizovan u konstruktoru da bude ova metoda

    running->bodyArg(running->argument);//telo se izvrsi...

    if(running->bodyArg!= nullptr)
        running->setFinished(true);//proglasimo ekxplicitno da je nit gotovaTCB::yield();
    //TCB::dispatch();//posto smo zavrsili predamo procesor drugoj niti
    thread_dispatch();

}

void TCB::thread_exit() {

    TCB* old=running;
    running->setFinished(true);
    running=Scheduler::get();

    TCB::contextSwitch(&old->context,&running->context);


}
int TCB::getThreadId(){
    printString("ID running:");
    printInt(running->id);
    printString("\n");
    TCB::dispatch();
    return 0;
}

int TCB::ubi(int id) {
    while(TCB* izvadjena=Scheduler::get()){
        if(izvadjena->id==id)
            break;
        else{
            Scheduler::put(izvadjena);
        }
    }
    return 0;
}
void* TCB::operator new (size_t size){
    uint64 brojBlokova=size/MEM_BLOCK_SIZE;
    uint64 ostatak=size%MEM_BLOCK_SIZE;

    if(ostatak!=0) brojBlokova+=1;
    return MemoryAllocator::ma->mem_alloc(brojBlokova);

}

void *TCB::operator new[](size_t size) {
    uint64 brojBlokova=size/MEM_BLOCK_SIZE;
    uint64 ostatak=size%MEM_BLOCK_SIZE;

    if(ostatak!=0) brojBlokova+=1;
    return MemoryAllocator::ma->mem_alloc(brojBlokova);
}

void TCB::operator delete (void* addr){
     MemoryAllocator::ma->mem_free(addr);
}

void TCB::operator delete[](void *addr){
    MemoryAllocator::ma->mem_free(addr);
}
