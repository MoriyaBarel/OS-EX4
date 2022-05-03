#include <iostream>

namespace ex4
{
    typedef struct free_block
    {
        size_t size;
        struct free_block *next;
    } free_block;

    class MyMemory
    {
    public:
        void *my_malloc(size_t size);
        void *my_calloc(size_t n, size_t size);
        void my_free(void *ptr);

        void *my_calloc_helper(size_t n, size_t size);
        void *my_malloc_helper(size_t size);
        void my_free_helper(void *ptr);
    };
}