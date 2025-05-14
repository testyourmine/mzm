#ifndef DATA_H
#define DATA_H

#include "types.h"
#include "constants/constants.h"

extern const u16 sPalette[16 * 16];
extern const u8 sBackgroundImageGfx[15100];
extern const u8 sBackgroundImageTileTable[1472];
extern const u8 sLinkTextTileTable[504];
extern const u8 sLinkCompleteJapaneseGfx[876];
extern const u8 sLinkCompleteEnglishGfx[4268];
extern const u8 sLinkErrorJapaneseGfx[584];
extern const u8 sLinkErrorEnglishGfx[2780];

extern const struct DispRegsSettings sDispRegsSettings;

extern const Func_T sIntrTable[13];

extern const char sMakerCodeMagicNumber[4];

extern const char sMetroidFusionJapaneseGameCode[4];
extern const char sMetroidFusionEnglishGameCode[4];
extern const char sMetroidFusionPalGameCode[4];

extern const char sMetroidZeroMissionJapaneseGameCode[4];
extern const char sMetroidZeroMissionEnglishGameCode[4];
extern const char sMetroidZeroMissionPalGameCode[4];

extern const u8 sEmpty_02007eac[256];

extern const u8 * const sLinkCompleteGraphicsEntries[LANGUAGE_END];
extern const u8 * const sLinkErrorGraphicsEntries[LANGUAGE_END];

#endif /* DATA_H */
