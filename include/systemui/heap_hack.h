#pragma once

#include <stddef.h>
#include <stdint.h>

extern uint32_t *heapEndPtr;
extern uint32_t heapMax;

extern __attribute__((noreturn)) void heapReset();

/**
 * @brief Initialize a fixed region of memory at the end of the heap
 *
 * @param size
 * @return void*
 */
void *initFixedRegion(uint32_t size);
