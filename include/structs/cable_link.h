#ifndef CABLE_LINK_STRUCTS_H
#define CABLE_LINK_STRUCTS_H

#include "types.h"

typedef u16 (CableLinkBuffer1_T)[2][2];

struct MultiBootData {
    u32 systemWork_1[5];
    u8 handshakeData;
    u16 handshakeTimeout;
    u8 probeCount;
    u8 clientData[3];
    u8 paletteData;
    u8 responseBit;
    u8 clientBit;
    u8 reserved_1;
    const u8* bootSourcePointer;
    const u8* bootEndPointer;
    const u8* dataSentPointer;
    u8* reserved_2[3];
    u32 systemWork_2[4];
    u8 sendFlag;
    u8 probeTargetBit;
    u8 checkWait;
    u8 serverType;
};

struct IoTransferInfo {
    Func_T pFunction;
    u8 unk_4; // copy of error flag after timeout
    u16 timer;
    u8 active;
    u8 stage;
    u8 unk_A; // stage
    u8 result;
    u8 errorFlag;
    // contains information about type of data, used to determine what to put into gUnk_30058c0
    // if gUnk_30058c4 is 0x5500 and language is same then 0x4400
    // if gUnk_30058c4 is 0x6600, if one fusion ending then 0x2200, if multiple then 0
    // if gUnk_30058c4 is 0x3300 then 0x3300
    u16 unk_E;
    s8 fusionGalleryImages;
    s8 language;
    u16 musicTrack;
    u16 musicPriority;
};

struct CableLinkInfo {
    u8 unk_0; // is parent and is ready?
    u8 unk_1; // stage
    u8 unk_2; // multiplayer id?
    u8 unk_3; // number of times data sent is properly received?
    u16 sioIncomingData[4];
    u8 unk_C; // true if unk_1A1 is 0, false otherwise, used for error flag
    u8 unk_D; // threshold?
    u8 unk_E; // unused
    u8 unk_F; // unused
    u8 unk_10; // if 1 then write 0x8FFF to link, else write 0x7C40, set to 1 when GBA parent ready, set to 0 after link write
    u8 unk_11; // contains data from link
    u8 hardwareErrorFlag;
    u8 checksumErrorFlag;
    u8 overflowErrorFlags;
    u8 sioErrorFlags;
    u16 unk_16; // reads from SIOMULTI and sends data over link, checksum?
    u8 unk_18; // index into first dimension of unk_1C
    u8 unk_19; // index into second dimension of unk_A0
    u8 unk_1A; // unused
    u8 unk_1B; // unused
    u16 unk_1C[2][32]; // contains data from gUnk_30058c0, transferred over link
    u8 unk_9C; // index into second dimension of unk_1C
    u8 unk_9D; // offset to index into second dimension of unk_1C?
    u8 unk_9E; // unused
    u8 unk_9F; // unused
    u16 unk_A0[2][2][32]; // contains data from SIOMULTI 0-3
    u8 unk_1A0; // index into third dimension of gCableLinkInfo.unk_A0
    u8 unk_1A1; // offset to index into third dimension of gCableLinkInfo.unk_A0
    u8 unk_1A2; // unused
};

struct CableLinkSerialTransferInfo {
    u8 isParent;
    u8 stage;
    u8 unk_2; // set but never read?
    u8 dataTransferStage;
    u8 verifyTransferResult; // 0 if transfer not verified yet, 1 if correct number of GBA's, 2 if more than 2 GBA's detected
    u8 errorDuringTransfer;
    u8 unk_6; // unused
    u8 unk_7; // unused
    const u32* pData; // pointer to data to transfer
    s32 dataCursor; // index into data to transfer
    s32 dataSizeInt;
    u32 dataChecksum;
};

extern struct IoTransferInfo gIoTransferInfo;

extern struct MultiBootData gMultiBootParamData;
extern const u8* gDataSentPointer;
extern u32 gDataSentSize;

extern u16 gRegIme_Backup;
extern u16 gRegIe_Backup;
extern u16 gRegTm3Cnt_H_Backup;
extern u16 gRegSiocnt_Backup;
extern u16 gRegRcnt_Backup;

extern u32 gUnk_3005874; // set to result of unk_891a0 but never used
extern u8 gUnk_3005884; // set to 0 but never used
extern u32 gUnk_3005880; // never set but read for switch case, always 0?
extern u16 gUnk_3005888[4]; // contains value ready from cable link

extern u8 gUnk_30058aa; // unused
extern u16 gSerialTransferDataTimer;
extern u8 gSerialTransferStartupTimer;
extern u8 gUnk_30058af; // unused
extern u8 gSerialTransferGbaDetectedCount;
extern u8 gSerialTransferGbaId; // unused, 0 = parent, 1-3 = child 1-3 GBA
extern u16 gSerialTransferUpdateResult;
extern struct CableLinkSerialTransferInfo gCableLinkSerialTransferInfo;

extern u32 gErrorFlag;
// Pairs of value, 0x2200 = (gIoTransferInfo.unk_E, 1), 0x4400 = (gIoTransferInfo.unk_E, 2), 0x5500 = (gIoTransferInfo.unk_E, gLanguage), 0x8800 =  (gIoTransferInfo.unk_E, gButtonInput)
extern u16 gUnk_30058c0[2];
// 2x2, contains data from gCableLinkInfo.unk_A0, which contains data from SIOMULTI 0-3
// Used to restore gIoTransferInfo language, fusionGalleryImages, 
extern CableLinkBuffer1_T gUnk_30058c4;

extern struct CableLinkInfo gCableLinkInfo;
extern u16 gUnk_30058d0; // REG_IME temp store
extern u8 gUnk_30058d2; // Connection timeout timer?
extern u8 gUnk_30058d3; // bool, true when unk_18 and unk_9D is 0, false when unk_18 is at the end of unk_1C
extern u8 gUnk_3005b54; // contains gCableLinkInfo.unk_1A1, but unused?
extern u8 gUnk_30058d5; // backup/previous gCableLinkInfo.unk_3
extern u8 gUnk_30058d6; // bool, true when unk_18 is 0, false when initialized
extern u16 gUnk_30058d8; // contains data from gUnk_30058c0
extern u16 gUnk_30058da; // contains data from SIOMULTI
extern u8 gUnk_3005b50; // contains gCableLinkInfo.unk_9D, but unused?

extern u8 gUnk_30058cc; // random value, 0 or 1
extern u8 gUnk_30058cd; // contains bits 2-4 of CableLinkDetectError return value (gCableLinkInfo.unk_3?), never read
extern u8 gUnk_30058ce; // contains bits 0-1 of CableLinkDetectError return value (gCableLinkInfo.unk_2?), never read
extern u8 gUnk_30058cf; // contains bits 9-11 of CableLinkDetectError return value (gCableLinkInfo.unk_11?), never read

#endif /* CABLE_LINK_STRUCTS_H */