#include <iostream>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "MyMemory.hpp"

pthread_mutex_t mem_mutex = PTHREAD_MUTEX_INITIALIZER;

using namespace ex4;

static free_block free_block_list_head = {0, 0};
static const size_t overhead = sizeof(size_t);
static const size_t align_to = 16;

void *MyMemory::my_malloc(size_t size)
{
    pthread_mutex_lock(&mem_mutex);
    void *to_return = my_malloc_helper(size);
    pthread_mutex_unlock(&mem_mutex);
    return to_return;
}

void *MyMemory::my_malloc_helper(size_t size)
{
    size = (size + sizeof(size_t) + (align_to - 1)) & ~(align_to - 1);
    free_block *block = free_block_list_head.next;
    free_block **head = &(free_block_list_head.next);
    while (block != 0)
    {
        if (block->size >= size)
        {
            *head = block->next;
            return ((char *)block) + sizeof(size_t);
        }
        head = &(block->next);
        block = block->next;
    }

    block = (free_block *)sbrk(size);
    block->size = size;

    return ((char *)block) + sizeof(size_t);
}

void MyMemory::my_free(void *ptr)
{
    pthread_mutex_lock(&mem_mutex);
    my_free_helper(ptr);
    pthread_mutex_unlock(&mem_mutex);
}

void MyMemory::my_free_helper(void *ptr)
{
    free_block *block = (free_block *)(((char *)ptr) - sizeof(size_t));
    block->next = free_block_list_head.next;
    free_block_list_head.next = block;
}



void *MyMemory::my_calloc(size_t n, size_t size)
{
    size_t total = n * size;
    void *p = MyMemory::my_malloc(total);

    if (!p)
        return NULL;

    return memset(p, 0, total);
}
