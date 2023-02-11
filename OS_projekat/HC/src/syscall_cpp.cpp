//
// Created by os on 8/22/22.
//


#include "../h/syscall_cpp.hpp"


void* operator new (size_t size){
    return mem_alloc(size);
}
void operator delete (void* pt){
    mem_free(pt);
}
Thread::~Thread() {
    mem_free(this->myHandle->stack);
}
Thread::Thread(void (*body)(void *), void *arg) {
    thread_create_CPPAPI(&this->myHandle,body,arg);
}
Thread::Thread() {
    thread_create_CPPAPI(&this->myHandle,&wrapper,(void*)this);
}
int Thread::start() {
    Scheduler::put(this->myHandle);
    return 0;
}

void Thread::wrapper(void *arg) {
    ((Thread*)arg)->run();
}

void Thread::dispatch() {
    thread_dispatch();
}

int Thread::sleep(time_t) {
    return 0;
}

char Console::getc() {
    return ::getc();
}

void Console::putc(char c) {
    ::putc(c);
}

Semaphore::Semaphore(unsigned int init) {
    sem_open(&myHandle,init);
}
Semaphore::~Semaphore() {
    sem_close(myHandle);
}
int Semaphore::wait(){
    sem_wait(myHandle);
    return 0;
}
int Semaphore::signal (){
    sem_signal(myHandle);
    return 0;
}
