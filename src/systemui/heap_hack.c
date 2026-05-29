#include "systemui/heap_hack.h"

extern void heapFree(void *ptr);

void *initFixedRegion(uint32_t size) {
  auto ptr = &heapMax - size;

  // Check if we have enough space at the end of the heap to allocate our region
  if (heapEndPtr > ptr)
    return NULL;

  auto endPtr = heapEndPtr;

  // Consume the full heap space, preven sbrk from growing
  heapEndPtr = &heapMax;

  // Size of the free block between our fixed region and the current heap end
  uint32_t blockSize = ptr - endPtr;

  // malloc keeps the end ptr aligned
  auto sizePtr = (uint32_t *)endPtr;

  // Set metadata for the allocator
  *sizePtr = blockSize - 4;

  // Donate the free block to the allocator
  heapFree(endPtr + 4);

  return ptr;
}
