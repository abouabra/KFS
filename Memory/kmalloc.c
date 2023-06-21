// end is defined in the linker script.

#include "kmalloc.h"

void *free_mem_addr = (void *)0x10000;
/* Implementation is just a pointer to some free memory which
 * keeps growing */
void *kmalloc(size_t size)
{
    void * ret = free_mem_addr;
    free_mem_addr += size; /* Remember to increment the pointer */
    return ret;
}