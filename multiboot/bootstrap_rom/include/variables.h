#ifndef VARIABLES_H
#define VARIABLES_H

#include "types.h"
#include "structs/structs.h"

extern u16 gTransferUpdateResult_Unused; // used in unused function
extern u8 gUnk_5002; // set to zero and never read
extern u16 gTransferDataTimer;
extern u8 gTransferStartupTimer;
extern u8 gTransferTimeoutTimer;
extern u8 gTransferGbaDetectedCount;
extern u8 gTransferGbaId;
extern u16 gRegIme_Backup;
extern u16 gRegIe_Backup;
extern u16 gRegTm3Cnt_H_Backup;
extern u16 gRegSiocnt_Backup;
extern u16 gRegRcnt_Backup;
extern u8 gUnk_5020; // set but never read
extern u8 gScreenMode;
extern const Func_T gIntrTable[13];
extern u8 gScreenBreatheEffectOffset;
extern u32 gTransferUpdateResult;
extern u16 gPreviousButtonInput;
extern u16 gUnk_5078; // set but never read
extern u16 gUnk_507c; // set but never read
extern u16 gChangedInput;
extern u16 gBldY;
extern u8 gMainGameMode;
extern u16 gUnk_508c; // set to zero and never read
extern u16 gInterruptCode[0x100];
extern u8 gUnk_5290; // set to zero and never read
extern u16 gDispCnt;
extern u8 gScreenBreatheEffectTimer;
extern struct TransferManager gTransferManager;

extern u16 gInterruptCheckFlag;
extern u16 (*gIntrCodePointer)[0x100];

#endif /* VARIABLES_H */
