#include "funcs.h"
#include "gba.h"
#include "io.h"
#include "macros.h"
#include "syscalls.h"
#include "types.h"
#include "variables.h"
#include "structs/structs.h"
#include "data/data.h"

void AgbMain(void)
{
    InitializeGame();

    while (TRUE)
    {
        UpdateInput();
        gFrameCounter8Bit++;
        switch (gMainGameMode)
        {
            case 0:
                LinkResetSerial();
                gUnk_290 = 0;
                gUnk_6ac = 0;
                gUnk_6bc = 0;
                gMainGameMode++;
                break;

            case 1:
                gUnk_6ac++;
                LinkHandleConnection();
                if (gUnk_88 & 1)
                {
                    gUnk_290++;
                    if (gUnk_290 > 3)
                    {
                        gUnk_70 = 0;
                        gUnk_7c = 0;
                        gUnk_6c0 = 0;
                        gMainGameMode++;
                    }
                }
                else if (gUnk_6bc != 0)
                {
                    gUnk_70 = 0;
                    gUnk_7c = 0;
                    gUnk_6c0 = 0;
                    gMainGameMode++;
                }
                if (gUnk_6ac > 90)
                {
                    gUnk_88 |= 1;
                    gUnk_6bc = 0x20;
                    gUnk_6ac = 0;
                }
                break;

            case 2:
                LinkDisableSerial();
                if (LoadGraphics() != 0)
                {
                    gUnk_24 |= (*(struct Unk_7e44*)0x02007e44).v4;
                    gMainGameMode++;
                }
                else
                {
                    gMainGameMode += 2;
                }
                break;

            case 3:
                if (gUnk_8c != 0)
                {
                    if (gUnk_8c >= 3)
                        gUnk_8c -= 2;
                    else
                        gUnk_8c = 0;

                    gUnk_78 = 0x10 - gUnk_8c;
                    if (gUnk_8c == 0)
                        gMainGameMode++;
                }
                break;

            case 4:
        }

        VBlankIntrWait();
    }
}

u32 LoadGraphics(void)
{
    u8 loadedGraphics;
    u8 graphicsOffset;

    graphicsOffset = 0x80;
    if ((u8)gUnk_6c <= 7)
    {
        graphicsOffset = (u8)gUnk_6c;
    }
    else if (gUnk_6a8 == 1)
    {
        graphicsOffset = 0;
    }
    else if(gUnk_6a8 == 2 || (graphicsOffset = 0x80, gUnk_6a8 == 3))
    {
        graphicsOffset = 2;
    }
    
    if (graphicsOffset != 0x80)
    {
        if (gUnk_6bc != 0)
        {
            LZ77UncompVRAM(PTR_ARRAY_02007fc8[graphicsOffset], (UNK_7E44.v8 << 14) + VRAM_BASE + 0x5000);
            DMA_SET(3, VRAM_BASE + 0x1000, PALRAM_BASE, C_32_2_16(DMA_ENABLE, 0xF0));
        }
        else
        {
            LZ77UncompVRAM(PTR_ARRAY_02007fac[graphicsOffset], (UNK_7E44.v8 << 14) + VRAM_BASE + 0x5000);
            DMA_SET(3, ARRAY_02001854, PALRAM_BASE, C_32_2_16(DMA_ENABLE, 0x100));
        }
        loadedGraphics = TRUE;
    }
    else
    {
        loadedGraphics = FALSE;
    }
    return loadedGraphics;
}

void InitializeGame(void)
{
    u8 tmp;
    u8 tmp2;
    u8 tmp3;
    u16 tmp4;
    
    dma_fill32(3, 0, IWRAM_BASE, IWRAM_SIZE - 0x15D);
    write16(REG_WAITCNT, WAIT_GAMEPACK_CGB | WAIT_BANK0_SUBSEQUENT_1CYCLE | WAIT_BANK0_3CYCLES);
    DMA_SET(3, InterruptTable, 0x3000030, 0x8400000e);
    DMA_SET(3, 0x2000104, 0x3000090, 0x84000080);
    gIntrCodePointer = (void*)0x3000090;
    dma_fill16(3, 0, VRAM_BASE, VRAM_SIZE);
    DMA_SET(3, ARRAY_02001854, PALRAM_OBJ, 0x80000100);
    ApplyMonochromeToPalette((u16*)ARRAY_02001854, PALRAM_BASE, 0);
    ApplyMonochromeToPalette((u16*)ARRAY_02001854, VRAM_BASE + 0x1000, -8);
    LZ77UncompVRAM(ARRAY_02001a54, ((tmp2 = UNK_7E44.v8) << 14) + VRAM_BASE);
    LZ77UncompVRAM(ARRAY_02005550, ((tmp = UNK_7E44.v9) << 11) + VRAM_BASE);
    LZ77UncompVRAM(ARRAY_02005b10, ((tmp3 = UNK_7E44.v1) << 11) + VRAM_BASE);
    dma_fill32(3, 0xA0, 0x30002a0, 0x400);
    dma_fill32(3, 0xA0, 0x7000000, 0x400);
    ValidateGameVersion();
    write16(REG_BG0CNT, UNK_7E44.v18 | UNK_7E44.v22 | (UNK_7E44.v17 << 8) | (UNK_7E44.v16 << 2));
    write16(REG_BG2CNT, UNK_7E44.v2 | UNK_7E44.v6 | (tmp3 << 8) | (UNK_7E44.v0 << 2));
    write16(REG_BG3CNT, UNK_7E44.v10 | UNK_7E44.v14 | (tmp << 8) | (tmp2 << 2));
    gUnk_6b8 = 0x5500;
    gMainGameMode = 0;
    gUnk_88 = 0;
    gUnk_6c = 0xfe;
    gUnk_70 = 1;
    write16(REG_IE, 0x2001);
    write16(REG_DISPSTAT, 8);
    write16(REG_IF, 0xffff);
    write16(REG_IME, 1);
    gUnk_8c = tmp4 = 0x10;
    gUnk_78 = 0;
    gUnk_80 = 0x10;
    write16(REG_BLDY, tmp4);
    write16(REG_BLDALPHA, tmp4 << 8);
    write16(REG_BLDCNT, 0x2844);
    gUnk_24 = UNK_7E44.v12;
}
