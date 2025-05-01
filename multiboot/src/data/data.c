#include "funcs.h"
#include "gba.h"
#include "io.h"
#include "macros.h"
#include "syscalls.h"
#include "types.h"
#include "variables.h"
#include "structs/structs.h"

#include "data/data.h"

const u16 sPalette[16 * 16] = INCBIN_U16("data/Palette.pal");
const u8 sBackgroundImageGfx[15100] = INCBIN_U8("data/BackgroundImage.gfx.lz");
const u8 sBackgroundImageTileTable[1472] = INCBIN_U8("data/BackgroundImage.tt");
const u8 sLinkTextTileTable[504] = INCBIN_U8("data/LinkText.tt");
const u8 sLinkCompleteJapaneseGfx[876] = INCBIN_U8("data/LinkCompleteJapanese.gfx.lz");
const u8 sLinkCompleteEnglishGfx[4268] = INCBIN_U8("data/LinkCompleteEnglish.gfx.lz");
const u8 sLinkErrorJapaneseGfx[584] = INCBIN_U8("data/LinkErrorJapanese.gfx.lz");
const u8 sLinkErrorEnglishGfx[2780] = INCBIN_U8("data/LinkErrorEnglish.gfx.lz");

const struct DispRegsSettings sDispRegsSettings = {
    .bg2CntCharBase = 2,
    .bg2CntScreenBase = 14,
    .bg2CntPriority = BGCNT_LOW_MID_PRIORITY,
    .v3 = 0,
    .dispCntBg2 = DCNT_BG2,
    .v6 = 0,

    .bg3CntCharBase = 2,
    .bg3CntScreenBase = 15,
    .bg3CntPriority = BGCNT_LOW_PRIORITY,
    .v11 = 0,
    .dispCntBg3 = DCNT_BG3,
    .v14 = 0,

    .bg0CntCharBase = 0,
    .bg0CntScreenBase = 13,
    .bg0CntPriority = BGCNT_HIGH_PRIORITY,
    .v19 = 0,
    .dispCntBg0 = DCNT_BG0,
    .v22 = 0,
};

const Func_T sIntrTable[13] = {
    LinkCommunicate,
    LinkReloadTransfer,
    UpdateDisplay,
    Callback_Empty,
    Callback_Empty,
    Callback_Empty,
    Callback_Empty,
    Callback_Empty,
    Callback_Empty,
    Callback_Empty,
    Callback_Empty,
    Callback_Empty,
    Callback_Empty
};

const char sMakerCodeMagicNumber[4] = { '0', '1', 0x96, 0x0 };

const char sMetroidFusionJapaneseGameCode[4] = { 'A', 'M', 'T', 'J' };
const char sMetroidFusionEnglishGameCode[4] = { 'A', 'M', 'T', 'E' };
const char sMetroidFusionPalGameCode[4] = { 'A', 'M', 'T', 'P' };

const char sMetroidZeroMissionJapaneseGameCode[4] = { 'B', 'M', 'X', 'J' };
const char sMetroidZeroMissionEnglishGameCode[4] = { 'B', 'M', 'X', 'E' };
const char sMetroidZeroMissionPalGameCode[4] = { 'B', 'M', 'X', 'P' };

const u8 sEmpty_02007eac[256] = { 0 };

const u8 * const sLinkCompleteGraphicsEntries[LANGUAGE_END] = {
    [LANGUAGE_JAPANESE] = sLinkCompleteJapaneseGfx,
    [LANGUAGE_HIRAGANA] = sLinkCompleteJapaneseGfx,
    [LANGUAGE_ENGLISH] = sLinkCompleteEnglishGfx,
    [LANGUAGE_GERMAN] = sLinkCompleteEnglishGfx,
    [LANGUAGE_FRENCH] = sLinkCompleteEnglishGfx,
    [LANGUAGE_ITALIAN] = sLinkCompleteEnglishGfx,
    [LANGUAGE_SPANISH] = sLinkCompleteEnglishGfx
};

const u8 * const sLinkErrorGraphicsEntries[LANGUAGE_END] = {
    [LANGUAGE_JAPANESE] = sLinkErrorJapaneseGfx,
    [LANGUAGE_HIRAGANA] = sLinkErrorJapaneseGfx,
    [LANGUAGE_ENGLISH] = sLinkErrorEnglishGfx,
    [LANGUAGE_GERMAN] = sLinkErrorEnglishGfx,
    [LANGUAGE_FRENCH] = sLinkErrorEnglishGfx,
    [LANGUAGE_ITALIAN] = sLinkErrorEnglishGfx,
    [LANGUAGE_SPANISH] = sLinkErrorEnglishGfx
};
