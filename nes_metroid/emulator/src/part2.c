#include "types.h"
#include "gba.h"
#include "macros.h"

extern const u32 sUnk_03002370;
extern u32 gUnk_03005A50;
extern u32 gUnk_03005A54;
extern u32 gUnk_03005A58;
extern u8 gUnk_03005A5C;
extern u8 gUnk_03005A5D;
extern u8 gUnk_03005A5E;
extern u16 gUnk_03005A60;
extern void (*gUnk_03005A64)(s32, s32);
extern u32 gUnk_03005FBC;

extern u32 _03002330[];
extern u32 _03002370;

void sub_03000000(u16 arg0);
u16 sub_03000024(u8 arg0);
u16 sub_03000050(u16 arg0);
void sub_03000080(void);
void sub_03000188(u16 arg0);
void sub_030001B4(void);
void sub_030001C4(u32 arg0);
void sub_030001F0(u32 arg0, u16 arg1, u32 arg2, u8 arg3);
void sub_0300023C(s32 arg0, s32 arg1, u16 arg2, s32 arg3, void* arg4);
void sub_030002A4(s32 arg0, s32 arg1, s32 arg2, u16 arg3, s32 arg4, void* arg5);

void sub_03000000(u16 arg0)
{
    if (gUnk_03005FBC != arg0)
    {
        gUnk_03005FBC = arg0;
        WRITE_16(REG_TM1CNT_L, -arg0);
    }
}

u16 sub_03000024(u8 arg0)
{
    u32 ret;

    ret = 0x10000 - (0x01000AE0 / _03002330[arg0]);
    return ret;
}

u16 sub_03000050(u16 arg0)
{
    u32 var_r1;

    var_r1 = 0x01000AE0 / arg0;
    if (var_r1 > 0xFFFF)
    {
        var_r1 = 0xFFFF;
    }
    var_r1 = 0x10000 - var_r1;
    return var_r1;
}

void sub_03000080(void)
{
    WRITE_32(REG_DMA1_CNT, 0x84400004);
    WRITE_16(REG_DMA1_CNT_H, _03002370);

    if (gUnk_03005A5C != 0)
    {
        if (gUnk_03005A5D != 0)
        {
            switch (gUnk_03005A5D)
            {
                case 1:
                    if (gUnk_03005A5E == 0)
                    {
                        gUnk_03005A5E = 1;
                        sub_030001C4(gUnk_03005A54);
                        gUnk_03005A64(gUnk_03005A50, gUnk_03005FBC);
                    }
                    else
                    {
                        gUnk_03005A5E = 0;
                        sub_030001C4(gUnk_03005A50);
                        gUnk_03005A64(gUnk_03005A54, gUnk_03005FBC);
                    }
                    break;
    
                case 2:
                    switch (gUnk_03005A5E)
                    {
                        case 0:
                            gUnk_03005A5E = 1;
                            sub_030001C4(gUnk_03005A54);
                            gUnk_03005A64(gUnk_03005A58, gUnk_03005FBC);
                            break;
        
                        case 1:
                            gUnk_03005A5E = 2;
                            sub_030001C4(gUnk_03005A58);
                            gUnk_03005A64(gUnk_03005A50, gUnk_03005FBC);
                            break;
        
                        case 2:
                            gUnk_03005A5E = 0;
                            sub_030001C4(gUnk_03005A50);
                            gUnk_03005A64(gUnk_03005A54, gUnk_03005FBC);
                            break;
                    }
                    break;
            }
        }
        else
        {
            sub_030001C4(gUnk_03005A50);
        }
    }
    else
    {
        sub_030001B4();
    }
}

void sub_03000188(u16 arg0)
{
    WRITE_16(REG_TM1CNT_L, -gUnk_03005FBC);
    WRITE_16(REG_TM1CNT_H, 0xC4);

    WRITE_16(REG_TM0CNT_L, arg0);
    WRITE_16(REG_TM0CNT_H, 0x80);
}

void sub_030001B4(void)
{
    WRITE_32(REG_TM0CNT_H, 0);
    WRITE_32(REG_TM1CNT_H, 0);
}

void sub_030001C4(u32 arg0)
{
    WRITE_16(REG_DMA1_SRC, arg0);
    WRITE_16(REG_DMA1_SRC + 2, arg0 >> 0x10);

    WRITE_16(REG_DMA1_DST, 0xA0);
    WRITE_16(REG_DMA1_DST + 2, 0x400);

    WRITE_16(REG_DMA1_CNT_H, 0xB200);
}

void sub_030001F0(u32 arg0, u16 arg1, u32 arg2, u8 arg3)
{
    WRITE_16(REG_SOUNDCNT_H, 0xB06);

    gUnk_03005FBC = arg2;
    gUnk_03005A5C = arg3;
    gUnk_03005A50 = arg0;
    gUnk_03005A5D = 0;

    sub_030001C4(arg0);
    sub_03000188(arg1);
}

void sub_0300023C(s32 arg0, s32 arg1, u16 arg2, s32 arg3, void* arg4)
{
    WRITE_16(REG_SOUNDCNT_H, 0xB06);

    gUnk_03005FBC = arg3;
    gUnk_03005A5C = 1;
    gUnk_03005A50 = arg0;
    gUnk_03005A54 = arg1;
    gUnk_03005A5D = 1;
    gUnk_03005A5E = 0;
    gUnk_03005A64 = arg4;

    sub_030001C4(arg0);
    sub_03000188(arg2);
}

void sub_030002A4(s32 arg0, s32 arg1, s32 arg2, u16 arg3, s32 arg4, void* arg5)
{
    WRITE_16(REG_SOUNDCNT_X, 0x80);
    WRITE_16(REG_SOUNDCNT_L, 0);
    WRITE_16(REG_SOUNDCNT_H, 0xB00);
    WRITE_16(REG_SOUNDCNT_H, 0xB04);

    gUnk_03005FBC = arg4;
    gUnk_03005A5C = 1;
    gUnk_03005A50 = arg0;
    gUnk_03005A54 = arg1;
    gUnk_03005A58 = arg2;
    gUnk_03005A5D = 2;
    gUnk_03005A5E = 0;
    gUnk_03005A60 = arg3;
    gUnk_03005A64 = arg5;

    sub_030001C4(arg0);
    sub_03000188(arg3);
}
