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

#endif /* STRUCT_H */
