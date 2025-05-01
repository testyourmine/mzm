#ifndef VARIABLES_H
#define VARIABLES_H

#include "types.h"
#include "structs/structs.h"

extern u16 gLinkSavedIme;
extern u8 gNumVBlanksWithoutSerialIntr;
extern u8 gSendBufferEmpty;
extern u8 gHandshakePlayerCount;
extern u8 gChecksumAvailable;
extern u16 gSendNonzeroCheck;
extern u16 gRecvNonzeroCheck;
extern u8 gMainGameMode;
extern u16 gRecvCmds[MAX_LINK_PLAYERS][CMD_LENGTH];
extern u8 gFusionGameCode;
extern u16 gDispCnt;
extern const Func_T gIntrTable[13];
extern u8 gLinkLocalId;
extern s8 gLanguage;
extern u8 gUnk_70; // set but never read
extern u16 gChangedInput;
extern u16 gBldAlpha_L;
extern u8 gUnk_7c; // set but never read
extern u16 gBldY;
extern u32 gLinkStatus;
extern u8 gLinkFinished;
extern u16 gBldAlpha_H;
extern u16 gInterruptCode[0x100];
extern u8 gLinkFinishedDelayTimer;
extern u8 gShouldAdvanceLinkState;
extern u8 gLinkUnkFlag9;
extern struct Unk_2a0 gUnk_2a0[0x400];
extern u8 gFrameCounter8Bit;
extern u16 gPreviousButtonInput;
extern u8 gZeroMissionGameCode;
extern u16 gLinkTimer;
extern u8 gLinkPlayerCount;
extern u16 gSendCmd[CMD_LENGTH];
extern u16 gSendCmd0;
extern u16 gSendCmd1;
extern u16 gCommand;
extern u8 gLinkErrorFlag;
extern u16 gUnk_6c0; // set but never read
extern u8 gLastSendQueueCount;
extern u8 gLastRecvQueueCount;
extern struct LinkInfo gLink;

extern u16 gInterruptCheckFlag;
extern u16 (*gIntrCodePointer)[0x100];

#endif /* VARIABLES_H */
