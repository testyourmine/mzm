#ifndef FUNCS_H
#define FUNCS_H

#include "types.h"
#include "structs/structs.h"

void AgbMain(void); // 0200023c
u32 LoadGraphics(void); // 020003c8
void InitializeGame(void); // 02000490
void LinkHandleConnection(void); // 020006bc
void UpdateDisplay(void); // 020007b8
void unk_020007fc(void);
void UpdateInput(void); // 02000848
void FillPalette(const u8 *src, u16 *dst, u8 palette); // 02000878
void empty_89c(void); // 0200089c

void LinkBuildSendCmd(u16 command); // 020008a0
void LinkProcessRecvCmds(void); // 02000940
void ApplyMonochromeToPalette(const u16* src, u16* dst, s8 additionalValue); // 020009d0
void LinkDisableSerial(void); // 02000a38
void LinkEnableSerial(void); // 02000aa0
void LinkResetSerial(void); // 02000b74
u32 LinkMain(u8* shouldAdvanceLinkState, u16 sendCmd[2], u16 recvCmds[2][2]); // 02000b84
void LinkCheckParentOrChild(void); // 02000ca4
void LinkInitTimer(void); // 02000cd0
void LinkEnqueueSendCmd(u16 sendCmd[2]); // 02000d20
void LinkDequeueRecvCmds(u16 recvCmds[2][2]); // 02000e00
void LinkVSync(void); // 02000f08
void LinkReloadTransfer(void); // 02000f78
void LinkCommunicate(void); // 02000f88
void LinkStartTransfer(void); // 02001018
u8 LinkDoHandshake(void); // 02001028
void LinkDoRecv(void); // 02001124
void LinkDoSend(void); // 0200122c
void LinkStopTimer(void); // 020012c8
void LinkSendRecvDone(void); // 020012fc
void LinkResetSendBuffer(void); // 0200132c
void LinkResetRecvBuffer(void); // 02001374

void FormatNumber(u8 xPosition, u8 yPosition, u8 *format, u32 value, u8 length, u16* output); // 020013d0
u32 CheckSameString(const char * a, const char * b, u8 size); // 0200161c
void ValidateGameVersion(void); // 0200164c

#endif /* FUNCS_H */
