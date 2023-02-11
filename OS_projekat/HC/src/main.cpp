//
// Created by os on 8/2/22.
//
#include "../h/tcb.hpp"


#include "../h/riscv.hpp"








void userMain(void*);
void mallocFree(){
    printString("mallocFree\n");
    constexpr int num = 100;
    void* addrs[num];
    for(int i = 0; i<num;i++){
        addrs[i] = mem_alloc(100);
        if(addrs[i] == 0){
            printString("not ok\n");
            return;
        }
    }

    for(int i = 0 ; i<num;i+=2){
        int retval = mem_free(addrs[i]);
        if(retval != 0){
            printString("not ok\n");
            return;
        }
    }

    for(int i = 0 ; i<num;i+=2){
        addrs[i] = mem_alloc(20);
        if(addrs[i] == 0){
            printString("not ok\n");;
            return;
        }
    }

    for(int i = 0; i<num;i++){
        int retval = mem_free(addrs[i]);
        if(retval != 0){
            printString("not ok\n");;
            return;
        }
    }

    printString("ok\n");;
}
void bigMalloc(){
    printString("big Malloc\n");;
    uint64 x = (uint64)HEAP_END_ADDR - (uint64)HEAP_START_ADDR + 100UL;
    void* p = mem_alloc(x);
    if(p == 0) printString("ok\n");
    else printString("not ok\n");
}
class Test{
public:
    int a;
};

void lotOfSmallMallocs(){
    printString("lotOfSmallMallocs\n");;
    uint64 cnt = 0;
    uint64 sum = 0;
    uint64 N = 10000UL;
    uint64 X = 10UL;
    for(uint64 i = 0; i<N;i++){
        Test* t = (Test*)mem_alloc(sizeof(Test));
        if(t == 0)break;
        t->a = X;
        sum+=t->a;
        cnt++;
    }
    printInt(cnt);
    printString("\n");
    if(sum == X*cnt) printString("ok\n");
    else printString("not ok\n");
}
void stressTesting(){
    printString("stressTesting\n");
    constexpr int num = 100;
    void* addrs[num];
    for(int i = 0; i<num;i++){
        addrs[i] = mem_alloc(1);
        if(addrs[i] == 0){
            printString("not ok\n");
            return;
        }
    }
    int sz = 100;
    while(sz > 0){
        printString("sz:");
        printInt(sz);
        for(int i = 0 ; i<num;i+=2){
            printString("i:");
            printInt(i);
            printString("free\n");
            int retval = mem_free(addrs[i]);
            if(retval != 0){
                printString("not ok\n");
                return;
            }
            printString("alloc\n");
            addrs[i] = mem_alloc(sz*2);
            if(addrs[i] == 0){
                printString("not ok\n");;
                return;
            }
        }
        for(int i = 1 ; i<num;i+=2){
            printString("i:");
            printInt(i);
            printString("free\n");
            int retval = mem_free(addrs[i]);
            if(retval != 0){
                printString("not ok\n");
                return;
            }
            printString("alloc\n");
            addrs[i] = mem_alloc(sz);
            if(addrs[i] == 0){
                printString("not ok\n");;
                return;
            }
        }
        sz-=10;
    }
    printString("ok\n");;
}
int main() {
    Riscv::mc_sstatus(Riscv::SSTATUS_SIE);
    Riscv::w_stvec((uint64) &Riscv::supervisorTrap);
    //mallocFree();
    //bigMalloc();
    //lotOfSmallMallocs();

    //stressTesting();
    //omogucavanje da se prekidi prihvataju u celom sistemu

    //Riscv::ms_sstatus(Riscv::SSTATUS_SIE);
    /*
    void* a= mem_alloc(sizeof(uint64));
    printString("test1:\n");
    printInteger((uint64)a);
    printString("\n");


    void* b= mem_alloc(sizeof(uint64));
    printString("test2:\n");
    printInteger((uint64)b);
    printString("\n");

    void* c= mem_alloc(sizeof(uint64));
    printString("test3:\n");
    printInteger((uint64)c);
    printString("\n");


    mem_free(a);
    mem_free(c);
    mem_free(b);



    */

    thread_t handle0 = nullptr;
    //thread_t handle1= nullptr;


    thread_create(&handle0, nullptr, nullptr);
    TCB::running = (TCB*)(handle0);

    //statusChange();
    //Riscv::w_sstatus(1);
    userMain(nullptr);

    /*
    thread_create(&handle1, userMain, nullptr);
    //TCB::running = (TCB*)(handle1);

    while(!(handle1->isFinished())){
        thread_dispatch();
    }
    */
    printString("\n");
    printString("Finished\n");

    //Riscv::mc_sstatus(Riscv::SSTATUS_SIE);
    //printString("test");
    return 0;
    //Threads_C_API_test();


    //producerConsumer_C_API();










    /*
    thread_t handle0 = nullptr;
    thread_t handle1 = nullptr;


    thread_create(&handle0, nullptr, nullptr);
    TCB::running = (TCB*)(handle0);

    thread_create(&handle1, workerBodyA, nullptr);
    printString("CoroutineA created\n");



    while (!((TCB*)(handle1)->isFinished())){
        thread_dispatch();
    }
    thread_t handle0 = nullptr;
    thread_t handle1 = nullptr;

    thread_create(&handle1, workerBodyA, nullptr);
    printString("CoroutineA created\n");

    thread_create(&handle0, nullptr, nullptr);
    TCB::running = (TCB*)(handle0);


    while (!((TCB*)(handle1)->isFinished())){
        thread_dispatch();
    }
    thread_t* handle2 = new thread_t;
    thread_t* handle3 = new thread_t;
    thread_t* handle4 = new thread_t;



    thread_create(handle1, workerBodyA, nullptr);
    printString("CoroutineA created\n");

    thread_create(handle0, nullptr, nullptr);
    TCB::running = (TCB*)(*handle0);



    thread_create(handle2, workerBodyB, nullptr);
    printString("CoroutineB created\n");

    thread_create(handle3, workerBodyC, nullptr);
    printString("CoroutineC created\n");

    thread_create(handle4, workerBodyD, nullptr);
    printString("CoroutineD created\n");


    while (!((TCB*)(*handle1)->isFinished() &&
            (TCB*)(*handle2)->isFinished() &&
            (TCB*)(*handle3)->isFinished()  &&
            (TCB*)(*handle4)->isFinished())){
        thread_dispatch();
    }
    */



}