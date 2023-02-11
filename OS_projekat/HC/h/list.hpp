//
// Created by marko on 20.4.22..
//

#ifndef OS1_VEZBE07_RISCV_CONTEXT_SWITCH_1_SYNCHRONOUS_LIST_HPP
#define OS1_VEZBE07_RISCV_CONTEXT_SWITCH_1_SYNCHRONOUS_LIST_HPP
#include "printing.hpp"
#include "../h/MemoryAllocator.hpp"
template<typename T>
class List
{
private:
    struct Elem
    {
        T *data;
        Elem *next;

        Elem(T *data, Elem *next) : data(data), next(next) {}

        void* operator new (size_t size){
            uint64 brojBlokova=size/MEM_BLOCK_SIZE;
            uint64 ostatak=size%MEM_BLOCK_SIZE;

            if(ostatak!=0) brojBlokova+=1;
            return MemoryAllocator::ma->mem_alloc(brojBlokova);
        }
        void *operator new[](size_t size){
            uint64 brojBlokova=size/MEM_BLOCK_SIZE;
            uint64 ostatak=size%MEM_BLOCK_SIZE;

            if(ostatak!=0) brojBlokova+=1;
            return MemoryAllocator::ma->mem_alloc(brojBlokova);
        }
        void operator delete (void* addr){
            MemoryAllocator::ma->mem_free(addr);
        }
        void operator delete[](void *addr){
            MemoryAllocator::ma->mem_free(addr);
        }
    };

    Elem *head, *tail;

public:
    List() : head(0), tail(0) {}

    List(const List<T> &) = delete;

    List<T> &operator=(const List<T> &) = delete;

    int numElem=0;
    friend class MemoryAllocator;
    void addFirst(T *data)
    {

        Elem *elem = new Elem(data, head);
        head = elem;
        if (!tail) { tail = head; }
        numElem++;
    }

    void addLast(T *data)
    {

        Elem *elem = new Elem(data, 0);
        if (tail)
        {
            tail->next = elem;
            tail = elem;
        } else
        {
            head = tail = elem;
        }
        numElem++;
    }

    T *removeFirst()
    {
        if (head==0 || tail==0) { return 0; }

        Elem *elem = head;
        head = head->next;
        if (!head) { tail = 0; head=0; }

        T *ret = elem->data;
        numElem--;
        delete elem;
        return ret;
    }

    T *peekFirst()
    {
        if (!head) { return 0; }
        return head->data;
    }

    T *removeLast()
    {
        if (!head) { return 0; }

        Elem *prev = 0;
        for (Elem *curr = head; curr && curr != tail; curr = curr->next)
        {
            prev = curr;
        }

        Elem *elem = tail;
        if (prev) { prev->next = 0; }
        else { head = 0; }
        tail = prev;

        T *ret = elem->data;
        numElem--;
        delete elem;
        return ret;
    }

    T *peekLast()
    {
        if (!tail) { return 0; }
        return tail->data;
    }
    int isEmpty(){
        if(head== nullptr&& tail== nullptr) return 1;
        else return 0;
    }
};



#endif //OS1_VEZBE07_RISCV_CONTEXT_SWITCH_1_SYNCHRONOUS_LIST_HPP
