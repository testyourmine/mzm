#include "part2.h"
#include "types.h"
#include "gba.h"
#include "macros.h"

#include "structs/part2.h"

extern u8 sUnk_030023DC[];

// SQ1_HI
void sub_030009A0(u8 arg0)
{
    gEmuAudio_Pulse1_Hi = arg0;
    sub_03000848(((arg0 & 7) << 8) | gEmuAudio_Pulse1_Lo);
    if (gUnk_03005FCC == 0)
    {
        sub_03000778();
    }
    sub_03000790();
}

void sub_030009DC(void)
{
    gUnk_03005A90 = 0;
    gUnk_03005FD0 = 0;
    gUnk_03005A94 = 0;
    gUnk_03005A96 = 0;
    gEmuAudio_Pulse1_Vol = 0;
    gEmuAudio_Pulse1_Sweep = 0;
    gEmuAudio_Pulse1_Lo = 0;
    gEmuAudio_Pulse1_Hi = 0;
    gUnk_03005AA0 = 0;
    gUnk_03005AA2 = 0;
    gUnk_03005FCC = 0;
    gUnk_03005AA4 = 0;
    gUnk_03005AA6 = 0;
    gUnk_03005AA8 = 0;
    gUnk_03005AAA = 0;
    gUnk_03005AAC = 0;
    gUnk_03005AAD = 0;
}

// Real file split between part2_2 and part2_3

void sub_03000D20(void)
{
    gUnk_03005AB0 = 0;
}

void sub_03000D2C(u32 arg0)
{
    gUnk_03005AC8 = arg0;
}

void sub_03000D38(void)
{
    if (gUnk_03005AC4 != 0)
    {
        gUnk_03005AC6 = 1;
        return;
    }

    gUnk_03005AC6 = 0;
    if (gEmuAudio_Pulse2_Vol & 0x10)
    {
        gUnk_03005AB4 = gEmuAudio_Pulse2_Vol & 0xF;
    }
    else
    {
        gUnk_03005AB4 = 0xF;
    }

    gUnk_03005AC2 = 0xF;
    if (gUnk_03005FD8 != 0)
    {
        gUnk_03005ACA = 1;
    }
    else
    {
        gUnk_03005ACA = 4;
    }

    sub_03000D2C(sUnk_030023DC[gEmuAudio_Pulse2_Hi >> 3] * 4);
    if (gEmuAudio_SndChn & 2)
    {
        gUnk_03005FD8 = 1;
        gUnk_03005AC4 = 0;
    }
}

void sub_03000DEC(void)
{
    if ((gUnk_03005FD8 != 0) && (gUnk_03005AC4 == 0))
    {
        gUnk_03005AC4 = 2;
    }
}

void sub_03000E10(void)
{
    if (gUnk_03005ACC != 0)
    {
        sub_03000E40((gUnk_03005AC0 & 0xF00) | gEmuAudio_Pulse2_Lo);
    }
}

void sub_03000E40(u16 arg0)
{
    u32 tmp;

    gUnk_03005ACC = 0;
    gUnk_03005AC0 = arg0;
    if (arg0 == 0)
    {
        gUnk_03005AB4 = 0;
        return;
    }

    gUnk_03005FC4 = NES_CLOCK_SPEED / (arg0 + 1);
    tmp = gUnk_03005FD0; // fake
    if (tmp == gUnk_03005FC4)
    {
        tmp = 1;
        gUnk_03005FC4 -= 1;
    }
}

void sub_03000E94(u8 arg0)
{
    gUnk_03005AB4 = arg0;
    gUnk_03005AC2 = 1;
}

// SQ2_VOL
void sub_03000EAC(u8 arg0)
{
    u8 var_0;
    u8 var_1;

    var_0 = gEmuAudio_Pulse2_Vol & 0x10;
    var_1 = arg0 & 0x10;

    gEmuAudio_Pulse2_Vol = arg0;
    gUnk_03005ACD = 0;

    if ((arg0 & 0xC0) == 0xC0)
    {
        gEmuAudio_Pulse2_Vol = arg0 & 0x7F;
    }

    if ((var_0 != 0) && (var_1 == 0) && (gUnk_03005FD8 != 0))
    {
        gUnk_03005ACD = 4;
        gUnk_03005AC2 = 1;
    }
}

// SQ2_SWEEP
void sub_03000F10(u8 arg0)
{
    gEmuAudio_Pulse2_Sweep = arg0;
    gUnk_03005ACA = 1;
}

// SQ2_LO
void sub_03000F28(u8 arg0)
{
    gEmuAudio_Pulse2_Lo = arg0;
    gUnk_03005ACC = 1;
}

// SQ2_HI
void sub_03000F40(u8 arg0)
{
    gEmuAudio_Pulse2_Hi = arg0;
    sub_03000E40(((arg0 & 7) << 8) | gEmuAudio_Pulse2_Lo);
    if (gUnk_03005FD8 == 0)
    {
        sub_03000D20();
    }
    sub_03000D38();
}

void sub_03000F7C(void)
{
    gUnk_03005AB0 = 0;
    gUnk_03005FC4 = 0;
    gUnk_03005AB4 = 0;
    gUnk_03005AB6 = 0;
    gEmuAudio_Pulse2_Vol = 0;
    gEmuAudio_Pulse2_Sweep = 0;
    gEmuAudio_Pulse2_Lo = 0;
    gEmuAudio_Pulse2_Hi = 0;
    gUnk_03005AC0 = 0;
    gUnk_03005AC2 = 0;
    gUnk_03005FD8 = 0;
    gUnk_03005AC4 = 0;
    gUnk_03005AC6 = 0;
    gUnk_03005AC8 = 0;
    gUnk_03005ACA = 0;
    gUnk_03005ACC = 0;
    gUnk_03005ACD = 0;
}
