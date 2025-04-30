#ifndef STRUCT_H
#define STRUCT_H

#include "types.h"

struct Unk_7e44
{
    u8 v0;
    u8 v1;
    u8 v2;
    u8 v3;
    u16 v4;
    //u8 v5;
    u16 v6;
    //u8 v7;
    u8 v8;
    u8 v9;
    u8 v10;
    u8 v11;
    u16 v12;
    //u8 v13;
    u16 v14;
    //u8 v15;
    u8 v16;
    u8 v17;
    u8 v18;
    u8 v19;
    u8 v20;
    u8 v21;
    u16 v22;
    //u8 v23;
};

struct Unk_2a0
{
    u8 field0;       // offset 0
    u8 _pad1;        // offset 1, padding
    u32 field1_0:9;
    u16 field1_9:7;      // offset 2
    u8 _pad2[4];     // offset 4–7, padding or unused
};

struct LinkSession {
    u8 isParent;
    u8 state;
    u8 localId;
    u8 playerCount;
    u16 handshakeBuffer[4];
    u8 receivedNothing;
    u8 serialIntrCounter;
};

struct LinkConnection {
    u8 handshakeAsParent;
    u8 unk_11;
    u8 hardwareErrorFlag;
    u8 checksumErrorFlag;
    u8 overflowErrorFlags;
    u8 sioErrorFlags;
    u16 checksum;
    u8 sendCmdIndex;
    u8 recvCmdIndex;
};

struct SendQueue {
    u16 data[2][32];
    u8 pos;
    u8 count;
};

struct RecvQueue {
    u16 data[2][2][32];
    u8 pos;
    u8 count;
};

struct LinkInfo {
    struct LinkSession session;
    struct LinkConnection connection;
    struct SendQueue sendQueue;
    struct RecvQueue recvQueue;
};

#endif /* STRUCT_H */
