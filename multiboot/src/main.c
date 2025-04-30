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
