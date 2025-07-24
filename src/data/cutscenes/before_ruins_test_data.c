#include "data/cutscenes/before_ruins_test_data.h"
#include "gba.h"
#include "macros.h"

const struct CutscenePageData sBeforeRuinsTestPageData[9] = {
    [0] = {
        .graphicsPage = 0,
        .tiletablePage = 0x1E,
        .priority = 3,
        .bg = DCNT_BG3,
        .screenSize = 0x4000
    },
    [1] = {
        .graphicsPage = 2,
        .tiletablePage = 0x1C,
        .priority = 2,
        .bg = DCNT_BG2,
        .screenSize = 0x4000
    },
    [2] = {
        .graphicsPage = 0,
        .tiletablePage = 0x1F,
        .priority = 3,
        .bg = DCNT_BG3,
        .screenSize = 0
    },
    [3] = {
        .graphicsPage = 0,
        .tiletablePage = 0x1E,
        .priority = 2,
        .bg = DCNT_BG2,
        .screenSize = 0
    },
    [4] = {
        .graphicsPage = 2,
        .tiletablePage = 0x1C,
        .priority = 1,
        .bg = DCNT_BG1,
        .screenSize = 0x4000
    },
    [5] = {
        .graphicsPage = 2,
        .tiletablePage = 0x1F,
        .priority = 0,
        .bg = DCNT_BG0,
        .screenSize = 0
    },
    [6] = {
        .graphicsPage = 0,
        .tiletablePage = 0x1E,
        .priority = 3,
        .bg = DCNT_BG3,
        .screenSize = 0
    },
    [7] = {
        .graphicsPage = 0,
        .tiletablePage = 0x1C,
        .priority = 1,
        .bg = DCNT_BG1,
        .screenSize = 0
    },
    [8] = {
        .graphicsPage = 0,
        .tiletablePage = 0x1D,
        .priority = 2,
        .bg = DCNT_BG2,
        .screenSize = 0
    },
};

const u16 sBeforeRuinsTestChozoWallSidesPal[10 * 16] = INCBIN_U16("data/cutscenes/BeforeRuinsTest/ChozoWallSides.pal");
const u16 sBeforeRuinsTestChozoWallPal[8 * 16] = INCBIN_U16("data/cutscenes/BeforeRuinsTest/ChozoWall.pal");
const u16 sBeforeRuinsTestSamusCloseUpPal[16 * 16] = INCBIN_U16("data/cutscenes/BeforeRuinsTest/SamusCloseUp.pal");

const u32 sBeforeRuinsTestLeftSideOfChozoWallGfx[4049] = INCBIN_U32("data/cutscenes/BeforeRuinsTest/LeftSideChozoWall.gfx.lz");
const u32 sBeforeRuinsTestRightSideOfChozoWallGfx[3987] = INCBIN_U32("data/cutscenes/BeforeRuinsTest/RightSideChozoWall.gfx.lz");
const u32 sBeforeRuinsTestChozoWallBackgroundGfx[6446] = INCBIN_U32("data/cutscenes/BeforeRuinsTest/ChozoWallBackground.gfx.lz");
const u32 sBeforeRuinsTestYoungSamusAndGreyVoiceGfx[1792] = INCBIN_U32("data/cutscenes/BeforeRuinsTest/YoungSamusAndGreyVoice.gfx.lz");
const u32 sBeforeRuinsTestYoungSamusAndGreyVoiceCloseUpGfx[3818] = INCBIN_U32("data/cutscenes/BeforeRuinsTest/YoungSamusAndGreyVoiceCloseUp.gfx.lz");
const u32 sBeforeRuinsTestYoungSamusCloseUpGfx[2979] = INCBIN_U32("data/cutscenes/BeforeRuinsTest/YoungSamusCloseUp.gfx.lz");
const u32 sBeforeRuinsTestSamusCloseUpGfx[5285] = INCBIN_U32("data/cutscenes/BeforeRuinsTest/SamusCloseUp.gfx.lz");

const u32 sBeforeRuinsTestLeftSideOfChozoWallTileTable[368] = INCBIN_U32("data/cutscenes/BeforeRuinsTest/LeftSideChozoWall.tt");
const u32 sBeforeRuinsTestRightSideOfChozoWallTileTable[369] = INCBIN_U32("data/cutscenes/BeforeRuinsTest/RightSideChozoWall.tt");
const u32 sBeforeRuinsTestChozoWallBackgroundTileTable[551] = INCBIN_U32("data/cutscenes/BeforeRuinsTest/ChozoWallBackground.tt");
const u32 sBeforeRuinsTestYoungSamusAndGreyVoiceTileTable[185] = INCBIN_U32("data/cutscenes/BeforeRuinsTest/YoungSamusAndGreyVoice.tt");
const u32 sBeforeRuinsTestYoungSamusAndGreyVoiceCloseUpTileTable[452] = INCBIN_U32("data/cutscenes/BeforeRuinsTest/YoungSamusAndGreyVoiceCloseUp.tt");
const u32 sBeforeRuinsTestYoungSamusCloseUpTileTable[368] = INCBIN_U32("data/cutscenes/BeforeRuinsTest/YoungSamusCloseUp.tt");
const u32 sBeforeRuinsTestSamusCloseUpEyesClosedTileTable[251] = INCBIN_U32("data/cutscenes/BeforeRuinsTest/SamusCloseUpEyesClosed.tt");
const u32 sBeforeRuinsTestSamusCloseUpEyesOpenedTileTable[232] = INCBIN_U32("data/cutscenes/BeforeRuinsTest/SamusCloseUpEyesOpened.tt");
const u32 sBeforeRuinsTestSamusCloseUpOutlineTileTable[333] = INCBIN_U32("data/cutscenes/BeforeRuinsTest/SamusCloseUpOutline.tt");
