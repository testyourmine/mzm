#ifndef FUNCS_H
#define FUNCS_H

#include "types.h"
#include "structs/structs.h"
#include "constants/constants.h"

extern void IntrMain(void);

void AgbMain(void);
u32 LoadGraphics(void);
void InitializeGame(void);
void LinkHandleConnection(void);
void UpdateDisplay(void);
void unk_020007fc(void);
void UpdateInput(void);
void FillPalette(const u8 *src, u16 *dst, u8 palette);
void Callback_Empty(void);

void LinkBuildSendCmd(u16 command);
void LinkProcessRecvCmds(void);
void ApplyMonochromeToPalette(const u16* src, u16* dst, s8 additionalValue);
void LinkDisableSerial(void);
void LinkEnableSerial(void);
void LinkResetSerial(void);
u32 LinkMain(u8* shouldAdvanceLinkState, u16 sendCmd[CMD_LENGTH], u16 recvCmds[MAX_LINK_PLAYERS][CMD_LENGTH]);
void LinkCheckParentOrChild(void);
void LinkInitTimer(void);
void LinkEnqueueSendCmd(u16 sendCmd[CMD_LENGTH]);
void LinkDequeueRecvCmds(u16 recvCmds[MAX_LINK_PLAYERS][CMD_LENGTH]);
void LinkVSync(void);
void LinkReloadTransfer(void);
void LinkCommunicate(void);
void LinkStartTransfer(void);
u8 LinkDoHandshake(void);
void LinkDoRecv(void);
void LinkDoSend(void);
void LinkStopTimer(void);
void LinkSendRecvDone(void);
void LinkResetSendBuffer(void);
void LinkResetRecvBuffer(void);

void FormatNumber(u8 xPosition, u8 yPosition, u8 *format, u32 value, u8 length, u16* output);
u32 CheckSameString(const char *a, const char *b, u8 size);
void ValidateGameVersion(void);

#endif /* FUNCS_H */
