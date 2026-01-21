#include "part2.h"
#include "types.h"
#include "gba.h"
#include "macros.h"

#include "structs/part2.h"

extern u8 sUnk_030023DC[];

void sub_03000778(void)
{
    gUnk_03005A90 = 0;
}

void sub_03000784(u32 arg0)
{
    gUnk_03005AA8 = arg0;
}

void sub_03000790(void)
{
    if (gUnk_03005AA4 != 0)
    {
        gUnk_03005AA6 = 1;
        return;
    }
    gUnk_03005AA6 = 0;

    if (gEmuAudio_Pulse1_Vol & 0x10)
    {
        gUnk_03005A94 = gEmuAudio_Pulse1_Vol & 0xF;
    }
    else
    {
        gUnk_03005A94 = 0xF;
    }

    gUnk_03005AA2 = 0xF;
    sub_03000784(sUnk_030023DC[gEmuAudio_Pulse1_Hi >> 3] * 4);
    if (gEmuAudio_SndChn & 1)
    {
        gUnk_03005FCC = 1;
        gUnk_03005AA4 = 0;
    }
}

void sub_03000824(void)
{
    if ((gUnk_03005FCC != 0) && (gUnk_03005AA4 == 0))
    {
        gUnk_03005AA4 = 2;
    }
}

void sub_03000848(u16 arg0)
{
    u32 tmp;

    tmp = 1;
    gUnk_03005AAC = 0;
    gUnk_03005AA0 = arg0;
    if (arg0 == 0)
    {
        gUnk_03005A94 = 0;
        return;
    }

    gUnk_03005FD0 = NES_CLOCK_SPEED / (arg0 + 1);
    tmp = gUnk_03005FC4; // fake
    if (gUnk_03005FD0 == gUnk_03005FC4)
    {
        gUnk_03005FC4 -= 1;
    }
}

void sub_0300089C(u8 arg0)
{
    gUnk_03005A94 = arg0;
    gUnk_03005AA2 = 1;
}

// SQ1_VOL
void sub_030008B4(u8 arg0)
{
    u8 var_0;
    u8 var_1;

    var_0 = gEmuAudio_Pulse1_Vol & 0x10;
    var_1 = arg0 & 0x10;

    gEmuAudio_Pulse1_Vol = arg0;
    gUnk_03005AAD = 0;

    if ((arg0 & 0xC0) == 0xC0)
    {
        gEmuAudio_Pulse1_Vol = arg0 & 0x7F;
    }

    if ((var_0 != 0) && (var_1 == 0) && (gUnk_03005FCC != 0))
    {
        gUnk_03005AAD = 4;
        gUnk_03005AA2 = 1;
    }
}

// SQ1_SWEEP
void sub_03000918(u8 arg0)
{
    gEmuAudio_Pulse1_Sweep = arg0;
    gUnk_03005AAA = 1;
}

// SQ1_LO
void sub_03000930(u8 arg0)
{
    gEmuAudio_Pulse1_Lo = arg0;
    gUnk_03005AAC = 1;
}

void sub_03000948(void)
{
    if (gUnk_03005AAC != 0)
    {
        sub_03000848((gUnk_03005AA0 & 0xF00) | gEmuAudio_Pulse1_Lo);
    }
}
