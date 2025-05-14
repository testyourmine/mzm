#ifndef FUNCS_H
#define FUNCS_H

#include "types.h"
#include "structs/structs.h"
#include "constants/constants.h"

extern void IntrMain(void);

void AgbMain(void);
void UpdateDisplay(void);
void UpdateInput(void);
void empty_5c8(void);
void Callback_Empty(void);

u32 TransferProcessRecv(u32 *recvBuffer);
void TransferInit(void);
void TransferCloseSerial(void);
void TransferOpenSerialMulti(void);
void TransferOpenSerial32(void);
u16 TransferHandleTransfer(u32 transferMode, u32 size, const u32* pData, u32* recvBuffer);
void TransferDetermineSendRecvState(void);
void TransferSetUpTransferManager(u32 size, const u32 *pData, u32 *recvBuffer);
void TransferExchangeData(void);
void TransferStartTransfer(void);
void TransferBackupIoRegs(void);
void TransferRetrieveIoRegs(void);

void FormatNumber(u8 xPosition, u8 yPosition, u8 *format, u32 value, u8 length, u16* output, u8 palette);
void unk_da4(u8 typeSize, u32 param_2, u16 param_3, u16 *output);
void DrawTime(u8 digit, u8 xPosition, u8 yPosition, u32 time, u16* src, u8 palette);

#endif /* FUNCS_H */
