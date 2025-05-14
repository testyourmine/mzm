#ifndef STRUCT_H
#define STRUCT_H

#include "types.h"

struct TransferStatus {
    u8 isParent;
    u8 stage;
    u8 unk_2; // set but never read, cursor * 100 / sizeInt
    u8 dataTransferStage;
    u8 verifyTransferResult; // 0 if transfer not verified yet, 1 if correct number of GBA's, 2 if more than 2 GBA's detected
    u8 errorDuringTransfer;
};

struct TransferData {
    u32* pData; // pointer to data to transfer
    s32 cursor; // index into data to transfer
    s32 sizeInt;
    u32 checksum;
};

struct TransferManager {
    struct TransferStatus status;
    struct TransferData data;
};

#endif /* STRUCT_H */
