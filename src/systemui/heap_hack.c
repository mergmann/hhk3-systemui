#include "systemui/heap_hack.h"

extern void heapFree(void *ptr);

void *initFixedRegion(uint32_t size) {
  uint8_t *ptr = &heapMax - size;

  // Check if we have enough space at the end of the heap to allocate our region
  if (heapEndPtr > ptr)
    return nullptr;

  volatile uint8_t *endPtr = heapEndPtr;

  // Consume the full heap space, preven sbrk from growing
  heapEndPtr = &heapMax;

  // Size of the free block between the current heap end and our fixed region
  uint32_t freeSize = ptr - endPtr;

  // Only donate if there is enough space to donate
  if (freeSize >= 8) {
    *(uint32_t *)endPtr = freeSize - 4;
    heapFree((void *)(endPtr + 4));
  }

  return ptr;
}

void uninitFixedRegion(uint32_t size) {
  // Move the heap end pointer back to its original position, effectively
  // "freeing" the fixed region. This allows the heap to grow again if needed.
  heapEndPtr = &heapMax - size;
}
