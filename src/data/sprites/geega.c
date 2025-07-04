#include "data/sprites/geega.h"
#include "macros.h"

const u32 sGeegaGfx[153] = INCBIN_U32("data/sprites/Geega.gfx.lz");
const u16 sGeegaPal[16] = INCBIN_U16("data/sprites/Geega.pal");
const u32 sGeegaWhiteGfx[153] = INCBIN_U32("data/sprites/GeegaWhite.gfx.lz");
const u16 sGeegaWhitePal[16] = INCBIN_U16("data/sprites/GeegaWhite.pal");

static const u16 sGeegaOam_Idle_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x200
};

static const u16 sGeegaOam_Idle_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf9, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x202
};

static const u16 sGeegaOam_Idle_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x204
};

static const u16 sGeegaOam_Moving_Frame4[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x206
};

static const u16 sGeegaOam_Moving_Frame5[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf7, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x208
};

static const u16 sGeegaOam_Moving_Frame6[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf7, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x20a
};

const struct FrameData sGeegaOam_Idle[5] = {
    [0] = {
        .pFrame = sGeegaOam_Idle_Frame0,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [1] = {
        .pFrame = sGeegaOam_Idle_Frame1,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [2] = {
        .pFrame = sGeegaOam_Idle_Frame2,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [3] = {
        .pFrame = sGeegaOam_Idle_Frame1,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGeegaOam_Moving[9] = {
    [0] = {
        .pFrame = sGeegaOam_Idle_Frame0,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [1] = {
        .pFrame = sGeegaOam_Idle_Frame1,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [2] = {
        .pFrame = sGeegaOam_Idle_Frame2,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [3] = {
        .pFrame = sGeegaOam_Idle_Frame1,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [4] = {
        .pFrame = sGeegaOam_Moving_Frame4,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [5] = {
        .pFrame = sGeegaOam_Moving_Frame5,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [6] = {
        .pFrame = sGeegaOam_Moving_Frame6,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [7] = {
        .pFrame = sGeegaOam_Moving_Frame5,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [8] = FRAME_DATA_TERMINATOR
};
