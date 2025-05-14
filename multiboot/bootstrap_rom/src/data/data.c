#include "funcs.h"
#include "gba.h"
#include "io.h"
#include "macros.h"
#include "syscalls.h"
#include "types.h"
#include "variables.h"
#include "structs/structs.h"

#include "data/data.h"

const u16 sPalette[1 * 16] = INCBIN_U16("data/Palette.pal");
const u8 sLinkErrorJapaneseGfx[1144] = INCBIN_U8("data/LinkErrorJapanese.gfx.lz");
const u8 sLinkErrorEnglishGfx[936] = INCBIN_U8("data/LinkErrorEnglish.gfx.lz");
const u8 sLinkTextTileTable[500] = INCBIN_U8("data/LinkText.tt");

const u8 sScreenBreatheEffectValues[12] = {
    16, 15, 14, 13, 12, 11, 10, 11, 12, 13, 14, 15
};

const Func_T sIntrTable[13] = {
    TransferExchangeData,
    Callback_Empty,
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

const char sWaitText[]          = "     WAIT...     ";
const char sSuccessText[]       = "    SUCCESS    ";
const char sFailureText[]       = "   FAILURE   ";
const char sErrorText[]         = "    ERROR    ";
const char sCanceledText[]      = "   CANCELED   ";
const char sNoLinkText[]        = "    NO LINK    ";
const char sIrregularLinkText[] = "IRREGULAR LINK";
