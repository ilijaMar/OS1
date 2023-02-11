//
// Created by os on 8/8/22.
//

#ifndef PROJECT_BASE_MEMORYALLOCATOR_HPP
#define PROJECT_BASE_MEMORYALLOCATOR_HPP
#include "../lib/hw.h"
#include "../h/printing.hpp"


class MemoryAllocator{

public:

    MemoryAllocator(){
        //this->freeMemHead={nullptr , nullptr,(&HEAP_END_ADDR-&HEAP_START_ADDR)/MEM_BLOCK_SIZE};

    }

    void* mem_alloc (size_t size);
    int mem_free (void*);
    static MemoryAllocator* ma;
    struct BlockHeader {
        BlockHeader* next;
        BlockHeader* prev;
        size_t size;//u blokovima

    };

    BlockHeader* freeMemHead;

    int tryToJoin (BlockHeader* cur);
    static void initHeader();
};








#endif //PROJECT_BASE_MEMORYALLOCATOR_HPP
