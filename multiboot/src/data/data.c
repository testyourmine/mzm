#include "funcs.h"
#include "gba.h"
#include "io.h"
#include "macros.h"
#include "syscalls.h"
#include "types.h"
#include "variables.h"
#include "structs/structs.h"

#include "data/data.h"

const u8 ARRAY_02001854[512] = INCBIN_U8("data/ARRAY_02001854");
const u8 ARRAY_02001a54[15100] = INCBIN_U8("data/ARRAY_02001a54");
const u8 ARRAY_02005550[1472] = INCBIN_U8("data/ARRAY_02005550");
const u8 ARRAY_02005b10[504] = INCBIN_U8("data/ARRAY_02005b10");
const u8 ARRAY_02005d08[876] = INCBIN_U8("data/ARRAY_02005d08");
const u8 ARRAY_02006074[4268] = INCBIN_U8("data/ARRAY_02006074");
const u8 ARRAY_02007120[584] = INCBIN_U8("data/ARRAY_02007120");
const u8 ARRAY_02007368[2780] = INCBIN_U8("data/ARRAY_02007368");

const struct Unk_7e44 UNK_7E44 = {
    .v0 = 0x2,
    .v1 = 0xe,
    .v2 = 0x2,
    .v3 = 0x0,
    .v4 = 0x400,
    .v6 = 0x0,
    .v8 = 0x2,
    .v9 = 0xf,
    .v10 = 0x3,
    .v11 = 0x0,
    .v12 = 0x800,
    .v14 = 0x0,
    .v16 = 0x0,
    .v17 = 0xd,
    .v18 = 0x0,
    .v19 = 0x0,
    .v20 = 0x0,
    .v21 = 0x1,
    .v22 = 0x0,
};

const Func_T InterruptTable[13] = {
    LinkCommunicate,
    LinkReloadTransfer,
    UpdateDisplay,
    empty_89c,
    empty_89c,
    empty_89c,
    empty_89c,
    empty_89c,
    empty_89c,
    empty_89c,
    empty_89c,
    empty_89c,
    empty_89c
};

const char DAT_02007e90[4] = { 0x30, 0x31, 0x96, 0x0 };

const char DAT_02007e94[4] = { 'A', 'M', 'T', 'J' };
const char DAT_02007e98[4] = { 'A', 'M', 'T', 'E' };
const char DAT_02007e9c[4] = { 'A', 'M', 'T', 'P' };

const char DAT_02007ea0[4] = { 'B', 'M', 'X', 'J' };
const char DAT_02007ea4[4] = { 'B', 'M', 'X', 'E' };
const char DAT_02007ea8[4] = { 'B', 'M', 'X', 'P' };

const u8 EMPTY_02007eac[256] = { 0 };

const u8 * const PTR_ARRAY_02007fac[7] = {
    ARRAY_02005d08,
    ARRAY_02005d08,
    ARRAY_02006074,
    ARRAY_02006074,
    ARRAY_02006074,
    ARRAY_02006074,
    ARRAY_02006074
};

const u8 * const PTR_ARRAY_02007fc8[7] = {
    ARRAY_02007120,
    ARRAY_02007120,
    ARRAY_02007368,
    ARRAY_02007368,
    ARRAY_02007368,
    ARRAY_02007368,
    ARRAY_02007368
};
