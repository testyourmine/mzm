#include "dma.h"
#include "gba.h"

struct DMA {
    const void* pSrc;
    void* pDst;
    u32 control;
};

void DmaTransfer(u8 channel, const void *src, void *dst, u32 len, u8 bitSize)
{
    volatile struct DMA* pDma;
    vu32 sizeControl;
    u32 lengthControl;
    u32 chunkSize;
    vu32* _pDma;
    u32 tmp;
    u32 tmp2;
    u32 tmp3;
    u32 tmp4;
    u32 tmp5;
    u32 tmp6;
    u32 dma;
    volatile struct DMA *regDMA;

    pDma = (regDMA = REG_DMA0) + channel;

    if (bitSize == 32)
    {
        tmp = DMA_32BIT;
        tmp <<= 16;
        sizeControl = tmp;
    }
    else
    {
        sizeControl = 0;
    }

    tmp2 = channel << 1;
    lengthControl = 0x800;
    chunkSize = 0x800;
    tmp6 = bitSize / 16;
    lengthControl = (0x800 >> (bitSize / 16));
    tmp3 = DMA_ENABLE << 16;
    lengthControl |= tmp3;
    tmp2 += channel;
    tmp = tmp2 << 2;

    loop1:
    while (len > chunkSize)
    {
        pDma->pSrc = src;
        pDma->pDst = dst;

        pDma->control = sizeControl | lengthControl;
        pDma->control;

        _pDma = (vu32*)((u8*)regDMA + tmp);
        if (_pDma[2] & (tmp3))
        {
            tmp4 = DMA_ENABLE << 16;
            loop2:
            dma = _pDma[2];
            if ((dma & tmp4) != 0) goto loop2;
        }

        len -= 0x800;
        src += chunkSize;
        dst += chunkSize;
        goto loop1;
    }

    pDma->pSrc = src;
    pDma->pDst = dst;

    len = len >> tmp6;
    tmp4 = tmp3;
    len = len | tmp4;
    pDma->control = sizeControl | len;
    pDma->control;

    _pDma = (vu32*)((u8*)regDMA + tmp);
    if (_pDma[2] & (tmp4))
    {
        tmp5 = (DMA_ENABLE << 16);
        loop3:
        dma = _pDma[2];
        if ((dma & tmp5) != 0) goto loop3;
    }
}
