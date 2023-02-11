//
// Created by os on 8/7/22.
//

#include "../h/MemoryAllocator.hpp"


MemoryAllocator* MemoryAllocator:: ma =nullptr;
void *MemoryAllocator::mem_alloc(size_t size) {

    BlockHeader *blk = freeMemHead, *prev = nullptr;
    for (; blk!=nullptr; prev=blk, blk=blk->next)
        if (blk->size>=size) break;
    if(blk== nullptr)
        return nullptr;

    size_t remainingSize = blk->size-size;
    if (remainingSize*MEM_BLOCK_SIZE >= sizeof(BlockHeader) + MEM_BLOCK_SIZE) {
        blk->size = size;

        size_t offset = sizeof(BlockHeader) + size*MEM_BLOCK_SIZE;
        BlockHeader* newBlk = (BlockHeader*)((char*)blk + offset);
        if(newBlk>HEAP_END_ADDR)
            return nullptr;
        if (prev) {
            prev->next = newBlk;

        }else freeMemHead = newBlk;
        newBlk->prev=prev;
        newBlk->next = blk->next;
        if(blk->next)
            blk->next->prev=newBlk;

        newBlk->size = remainingSize - sizeof(BlockHeader);

    }else{
        if (prev) {
            prev->next = blk->next;
            blk->next->prev=prev;
        }
        else {
            freeMemHead = blk->next;
            blk->next->prev=freeMemHead;
        }

    }
    blk->next = nullptr;
    blk->prev = nullptr;
    return (char*)blk + sizeof(BlockHeader);
}



int MemoryAllocator::mem_free(void* adresa) {

    BlockHeader* blk=(BlockHeader*)((char*)adresa-sizeof(BlockHeader));
    BlockHeader* cur=0;
    if (!freeMemHead || (char*)blk<(char*)freeMemHead)
        cur = 0;
    else
        for (cur=freeMemHead; cur->next!=0 && (char*)blk>(char*)(cur->next); cur=cur->next);




    blk->prev=cur;
    if (cur) blk->next = cur->next;
    else blk->next = freeMemHead;
    if (blk->next) blk->next->prev = blk;
    if (cur) cur->next = blk;
    else freeMemHead = blk;

    tryToJoin(cur);
    tryToJoin(blk);
    return 0;


}

int MemoryAllocator::tryToJoin(MemoryAllocator::BlockHeader *cur) {
    if (!cur) return 0;
    if (cur->next && (char*)cur + sizeof(BlockHeader) + cur->size*MEM_BLOCK_SIZE == (char*)(cur->next)) {

        cur->size =cur->size*MEM_BLOCK_SIZE+cur->next->size*MEM_BLOCK_SIZE+sizeof(BlockHeader);//pretvori u bajtove pa u blokove
        cur->size=cur->size/MEM_BLOCK_SIZE;
        cur->next = cur->next->next;
        if (cur->next) cur->next->prev = cur;
        return 1;
    } else
        return 0;

}

void MemoryAllocator::initHeader(){

    MemoryAllocator::ma = (MemoryAllocator*)HEAP_START_ADDR;
    HEAP_START_ADDR=(char*)HEAP_START_ADDR+sizeof(MemoryAllocator);

    ma->freeMemHead=(BlockHeader*)HEAP_START_ADDR;
    ma->freeMemHead->prev=ma->freeMemHead->next= nullptr;
    ma->freeMemHead->size=((char*)HEAP_END_ADDR-(char*)&HEAP_START_ADDR)/MEM_BLOCK_SIZE;
    HEAP_START_ADDR=(char*)HEAP_START_ADDR+sizeof(BlockHeader);


}




