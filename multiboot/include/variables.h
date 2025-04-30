#ifndef VARIABLES_H
#define VARIABLES_H

#include "types.h"
#include "structs/structs.h"

extern u8 gMainGameMode; // 0x03000010
extern u16 gRecvCmds[2][2]; // 0x03000018
extern u16 gUnk_24; // 0x03000024
extern u8 gLinkLocalId; // 0x03000068
extern s8 gUnk_6c; // 0x0300006c
extern u8 gUnk_70; // 0x03000070
extern u16 gChangedInput; // 0x03000074
extern u16 gUnk_78; // 0x03000078
extern u8 gUnk_7c; // 0x0300007c
extern u16 gUnk_80; // 0x03000080
extern u32 gErrorFlag; // 0x03000084
extern u8 gUnk_88; // 0x03000088
extern u16 gUnk_8c; // 0x0300008c
extern u8 gUnk_290; // 0x03000290
extern u8 gShouldAdvanceLinkState; // 0x03000298
extern u8 gLinkUnkFlag9; // 0x0300029c
extern struct Unk_2a0 gUnk_2a0[4];
extern u8 gFrameCounter8Bit; // 0x030006a0
extern u16 gPreviousButtonInput; // 0x030006a4
extern u8 gUnk_6a8; // 0x030006a8
extern u16 gUnk_6ac; // 0x030006ac
extern u8 gLinkPlayerCount; // 0x030006b0
// extern u16 gSendCmd[2]; // 0x030006b4
extern u16 gSendCmd0; // 0x030006b4
extern u16 gSendCmd1; // 0x030006b6
extern u16 gSendCmd2; // 0x030006b8
extern u8 gUnk_6bc; // 0x030006bc
extern u16 gUnk_6c0; // 0x030006c0

extern u16 gInterruptCheckFlag; // 0x03007ff8
extern u16 (*gIntrCodePointer)[0x100]; // 0x0x03007ffc

#endif /* VAIRABLES_H */
