#pragma once

#include <cstddef>
#include <cstdint>

extern "C" std::byte *heapEndPtr;
extern "C" std::byte heapMax;

extern "C" [[noreturn]] void heapReset();

/**
 * @brief Initialize a fixed region of memory at the end of the heap
 *
 * @param size
 * @return void*
 */
void *initFixedRegion(uint32_t size);
