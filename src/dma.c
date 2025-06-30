#include "dma.h"
#include "gba.h"

struct DMA {
    const void* pSrc;
    void* pDst;
    u32 control;
};

/**
 * @brief 31e4 | d0 | Peform DMA transfer
 * 
 * @param channel The DMA channel to perform the transfer on
 * @param src The pointer to the source
 * @param dst The pointer to the destination
 * @param len The number of bytes to transfer
 * @param bitSize The number of bits per transfer, either 16 or 32
 */
void DmaTransfer(u8 channel, const void *src, void *dst, u32 len, u8 bitSize)
{
    volatile struct DMA *regDMA;
    volatile struct DMA *pDma;
    volatile struct DMA *_pDma;
    vu32 sizeControl;
    s32 chunkSize;
    u32 nbrHalfWords;
    u32 lengthControl;
    u32 tmp;
    u32 tmp2;
    u32 dmaEnable0;
    u32 dmaEnable1;
    u32 dmaEnable2;

    pDma = (regDMA = REG_DMA0) + channel;

    if (bitSize == 32)
    {
        // Code written like this to match
        tmp = DMA_32BIT;
        tmp <<= 16;
        sizeControl = tmp;
    }
    else
    {
        sizeControl = 0;
    }

    tmp2 = channel << 1;
    chunkSize = 0x800;
    nbrHalfWords = bitSize / 16;
    lengthControl = chunkSize >> nbrHalfWords;
    dmaEnable0 = DMA_ENABLE << 16;
    lengthControl |= dmaEnable0;
    tmp2 += channel;
    tmp = tmp2 << 2;

    transferNextChunk:
    while (len > chunkSize)
    {
        pDma->pSrc = src;
        pDma->pDst = dst;

        pDma->control = sizeControl | lengthControl;
        pDma->control;

        _pDma = (volatile struct DMA*)((u8*)regDMA + tmp);
        if (_pDma->control & dmaEnable0)
        {
            dmaEnable1 = DMA_ENABLE << 16;
            waitForDmaEnable1:
            if (_pDma->control & dmaEnable1) goto waitForDmaEnable1;
        }

        len -= 0x800;
        src += chunkSize;
        dst += chunkSize;
        goto transferNextChunk;
    }

    pDma->pSrc = src;
    pDma->pDst = dst;

    len = len >> nbrHalfWords;
    dmaEnable1 = dmaEnable0;
    len = len | dmaEnable1;
    pDma->control = sizeControl | len;
    pDma->control;

    _pDma = (volatile struct DMA*)((u8*)regDMA + tmp);
    if (_pDma->control & dmaEnable1)
    {
        dmaEnable2 = DMA_ENABLE << 16;
        waitForDmaEnable2:
        if (_pDma->control & dmaEnable2) goto waitForDmaEnable2;
    }
}
