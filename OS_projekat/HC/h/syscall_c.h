//
// Created by os on 8/6/22.
//

#ifndef PROJECT_BASE_SYSCALL_C_H
#define PROJECT_BASE_SYSCALL_C_H
#include "../lib/hw.h"
#include "../lib/console.h"
//#include "../h/tcb.hpp"
//#include "tcb.hpp"


#ifdef __cplusplus
extern "C" {
#endif

void *mem_alloc(size_t size);
int mem_free(void* adresa);


typedef struct TCB *thread_t;
int thread_create(
        thread_t *handle,
        void(*start_routine)(void *),
        void *arg
        );
int thread_create_CPPAPI(
        thread_t *handle,
        void(*start_routine)(void *),
        void *arg
);
int thread_exit();
void thread_dispatch();
int getThreadId();
typedef struct SemaphoreUser *sem_t;
int sem_open (
        sem_t* handle,
        unsigned init
);
int sem_close (sem_t handle);
int sem_wait (sem_t id);
int sem_signal (sem_t id);
void statusChange();
char getc();
void putc(char c);
#ifdef __cplusplus
}
#endif












#endif //PROJECT_BASE_SYSCALL_C_H
