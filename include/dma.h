#ifndef DMA_H
#define DMA_H

#include "types.h"

void DmaTransfer(u8 channel, const void *src, void *dst, u32 len, u8 bitSize);

#endif /* DMA_H */
