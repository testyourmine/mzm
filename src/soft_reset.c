#include "soft_reset.h"
#include "gba.h"
#include "callbacks.h"

#include "data/shortcut_pointers.h"

#include "constants/cutscene.h"

#include "structs/display.h"
#include "structs/game_state.h"
#include "structs/cutscene.h"

/**
 * @brief 7ef9c | 54 | Subroutine for a soft reset
 * 
 * @return u32 bool, ended
 */
u32 SoftResetSubroutine(void)
{
    switch (gGameModeSub1)
    {
        case 0:
            SoftResetInit();
            gGameModeSub1++;
            break;

        case 1:
            if (gWrittenToBldy_NonGameplay - 4 < 1)
                gWrittenToBldy_NonGameplay = 0;
            else
                gWrittenToBldy_NonGameplay -= 4;
            
            if (gWrittenToBldy_NonGameplay == 0)
                gGameModeSub1++;
            break;

        case 2:
            return TRUE;
    }

    return FALSE;
}

/**
 * @brief 7eff0 | 110 | Initializes a soft reset
 * 
 */
void SoftResetInit(void)
{
    // The use of non gameplay ram in this function is inconsequential

    CallbackSetVblank(SoftResetVBlank_Empty);

    DMA_FILL_32(3, 0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    WRITE_16(REG_BLDCNT, CUTSCENE_DATA.bldcnt = BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_INCREASE_EFFECT);

    WRITE_16(REG_BLDY, gWrittenToBldy_NonGameplay = BLDY_MAX_VALUE);
    WRITE_16(REG_DISPCNT, CUTSCENE_DATA.dispcnt = 0);

    gNextOamSlot = 0;
    ClearGfxRam();
    ResetFreeOam();

    gOamXOffset_NonGameplay = gOamYOffset_NonGameplay = 0;
    SET_BACKDROP_COLOR(COLOR_BLACK);
    gGameModeSub3 = 0;

    gBg0HOFS_NonGameplay = gBg0VOFS_NonGameplay = 0;
    gBg1HOFS_NonGameplay = gBg1VOFS_NonGameplay = 0;
    gBg2HOFS_NonGameplay = gBg2VOFS_NonGameplay = 0;
    gBg3HOFS_NonGameplay = gBg3VOFS_NonGameplay = 0;

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);
    
    WRITE_16(REG_DISPCNT, CUTSCENE_DATA.dispcnt = 0);

    CallbackSetVblank(SoftResetVBlank);
}

/**
 * @brief 7f100 | 14 | V-blank code for a soft reset
 * 
 */
void SoftResetVBlank(void)
{
    WRITE_16(REG_BLDY, gWrittenToBldy_NonGameplay);
}

/**
 * @brief 7f114 | c | Empty v-blank for a soft reset
 * 
 */
void SoftResetVBlank_Empty(void)
{
    vu8 c = 0;
}
