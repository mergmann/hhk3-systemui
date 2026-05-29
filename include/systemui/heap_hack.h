#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern volatile uint8_t *heapEndPtr;
extern uint8_t heapMax;

__attribute__((noreturn)) void heapReset();

void uninitFixedRegion(uint32_t size);

/**
 * @brief Initialize a fixed region of memory at the end of the heap
 *
 * @param size
 * @return void*
 */
void *initFixedRegion(uint32_t size);

#ifdef __cplusplus
}
#endif
