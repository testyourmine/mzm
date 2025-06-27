#include "data/sprites/skree.h"
#include "macros.h"

const s16 sSkreeFallingSpeed[8] = {
    PIXEL_SIZE / 2 * 1,
    PIXEL_SIZE / 2 * 2,
    PIXEL_SIZE / 2 * 3,
    PIXEL_SIZE / 2 * 4,
    PIXEL_SIZE / 2 * 6,
    PIXEL_SIZE / 2 * 7,
    PIXEL_SIZE / 2 * 8,
    SHORT_MAX
};

const u32 sSkreeGreenGfx[264] = INCBIN_U32("data/sprites/SkreeGreen.gfx.lz");
const u16 sSkreeGreenPal[16] = INCBIN_U16("data/sprites/SkreeGreen.pal");
const u32 sSkreeBlueGfx[264] = INCBIN_U32("data/sprites/SkreeBlue.gfx.lz");
const u16 sSkreeBluePal[16] = INCBIN_U16("data/sprites/SkreeBlue.pal");

static const u16 sSkreeOam_Idle_Frame0[OAM_DATA_SIZE(4)] = {
    0x4,
    0x0, OBJ_SIZE_16x16 | 0x1f0, OBJ_SPRITE_OAM | 0x200,
    0x10, OBJ_SIZE_16x16 | 0x1f0, OBJ_SPRITE_OAM | 0x202,
    0x0, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x0, OBJ_SPRITE_OAM | 0x200,
    0x10, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x0, OBJ_SPRITE_OAM | 0x202
};

static const u16 sSkreeOam_Idle_Frame1[OAM_DATA_SIZE(2)] = {
    0x2,
    0x0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x20c,
    0x10, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x20e
};

static const u16 sSkreeOam_Idle_Frame2[OAM_DATA_SIZE(4)] = {
    0x4,
    OBJ_SHAPE_VERTICAL | 0x0, 0x1fc, OBJ_SPRITE_OAM | 0x210,
    OBJ_SHAPE_VERTICAL | 0x10, 0x1fc, OBJ_SPRITE_OAM | 0x212,
    0x0, 0x4, OBJ_SPRITE_OAM | 0x211,
    0x0, OBJ_X_FLIP | 0x1f4, OBJ_SPRITE_OAM | 0x211
};

static const u16 sSkreeOam_Idle_Frame3[OAM_DATA_SIZE(2)] = {
    0x2,
    0x0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x213,
    0x10, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x215
};

static const u16 sSkreeOam_Spinning_Frame1[OAM_DATA_SIZE(4)] = {
    0x4,
    0x0, OBJ_SIZE_16x16 | 0x1f0, OBJ_SPRITE_OAM | 0x208,
    OBJ_SHAPE_HORIZONTAL | 0x10, 0x1f0, OBJ_SPRITE_OAM | 0x20a,
    0x0, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x0, OBJ_SPRITE_OAM | 0x208,
    OBJ_SHAPE_HORIZONTAL | 0x10, OBJ_X_FLIP | 0x0, OBJ_SPRITE_OAM | 0x20a
};

static const u16 sSkreeOam_Spinning_Frame2[OAM_DATA_SIZE(4)] = {
    0x4,
    0x0, OBJ_SIZE_16x16 | 0x1f0, OBJ_SPRITE_OAM | 0x204,
    OBJ_SHAPE_HORIZONTAL | 0x10, 0x1f0, OBJ_SPRITE_OAM | 0x206,
    0x0, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x0, OBJ_SPRITE_OAM | 0x204,
    OBJ_SHAPE_HORIZONTAL | 0x10, OBJ_X_FLIP | 0x0, OBJ_SPRITE_OAM | 0x206
};

static const u16 sSkreeOam_CrashingUnused_Frame0[OAM_DATA_SIZE(4)] = {
    0x4,
    0xf0, OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x1f0, OBJ_SPRITE_OAM | 0x200,
    0xe0, OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x1f0, OBJ_SPRITE_OAM | 0x202,
    0xf0, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x0, OBJ_SPRITE_OAM | 0x200,
    0xe0, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x0, OBJ_SPRITE_OAM | 0x202
};

static const u16 sSkreeOam_CrashingUnused_Frame1[OAM_DATA_SIZE(2)] = {
    0x2,
    0xf0, OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x20c,
    0xe0, OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x20e
};

static const u16 sSkreeOam_CrashingUnused_Frame2[OAM_DATA_SIZE(4)] = {
    0x4,
    OBJ_SHAPE_VERTICAL | 0xf0, OBJ_Y_FLIP | 0x1fc, OBJ_SPRITE_OAM | 0x210,
    OBJ_SHAPE_VERTICAL | 0xe0, OBJ_Y_FLIP | 0x1fc, OBJ_SPRITE_OAM | 0x212,
    0xf8, OBJ_Y_FLIP | 0x4, OBJ_SPRITE_OAM | 0x211,
    0xf8, OBJ_X_FLIP | OBJ_Y_FLIP | 0x1f4, OBJ_SPRITE_OAM | 0x211
};

static const u16 sSkreeOam_CrashingUnused_Frame3[OAM_DATA_SIZE(2)] = {
    0x2,
    0xf0, OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x213,
    0xe0, OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x215
};

static const u16 sSkreeOam_CrashingUnused2_Frame1[OAM_DATA_SIZE(4)] = {
    0x4,
    0xf0, OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x1f0, OBJ_SPRITE_OAM | 0x208,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_Y_FLIP | 0x1f0, OBJ_SPRITE_OAM | 0x20a,
    0xf0, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x0, OBJ_SPRITE_OAM | 0x208,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_X_FLIP | OBJ_Y_FLIP | 0x0, OBJ_SPRITE_OAM | 0x20a
};

static const u16 sSkreeOam_CrashingUnused2_Frame2[OAM_DATA_SIZE(4)] = {
    0x4,
    0xf0, OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x1f0, OBJ_SPRITE_OAM | 0x204,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_Y_FLIP | 0x1f0, OBJ_SPRITE_OAM | 0x206,
    0xf0, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x0, OBJ_SPRITE_OAM | 0x204,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_X_FLIP | OBJ_Y_FLIP | 0x0, OBJ_SPRITE_OAM | 0x206
};

static const u16 sSkreeExplosionOAM_GoingUp_Frame0[OAM_DATA_SIZE(3)] = {
    0x3,
    0x6, 0x1fb, OBJ_SPRITE_OAM | 0x238,
    0xf6, 0x1fb, OBJ_SPRITE_OAM | 0x217,
    0xfe, 0x1fb, OBJ_SPRITE_OAM | 0x218
};

static const u16 sSkreeExplosionOAM_GoingUp_Frame1[OAM_DATA_SIZE(3)] = {
    0x3,
    0xf8, 0x1fb, OBJ_SPRITE_OAM | 0x217,
    0xfd, 0x1fb, OBJ_SPRITE_OAM | 0x218,
    0x2, 0x1fb, OBJ_SPRITE_OAM | 0x238
};

static const u16 sSkreeExplosionOAM_GoingUp_Frame2[OAM_DATA_SIZE(2)] = {
    0x2,
    0xff, 0x1f9, OBJ_SPRITE_OAM | 0x238,
    0xf9, OBJ_Y_FLIP | 0x1f9, OBJ_SPRITE_OAM | 0x238
};

static const u16 sSkreeExplosionOAM_GoingDown_Frame0[OAM_DATA_SIZE(3)] = {
    0x3,
    OBJ_SHAPE_VERTICAL | 0xf6, 0x1fa, OBJ_SPRITE_OAM | 0x219,
    0x6, 0x1fa, OBJ_SPRITE_OAM | 0x23a,
    0xfe, 0x1fa, OBJ_SPRITE_OAM | 0x21a
};

static const u16 sSkreeExplosionOAM_GoingDown_Frame1[OAM_DATA_SIZE(2)] = {
    0x2,
    0xfa, 0x1fa, OBJ_SPRITE_OAM | 0x219,
    0xfe, 0x1fa, OBJ_SPRITE_OAM | 0x21a
};

static const u16 sSkreeExplosionOAM_GoingDown_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fa, OBJ_SPRITE_OAM | 0x219
};

const struct FrameData sSkreeOam_Idle[5] = {
    [0] = {
        .pFrame = sSkreeOam_Idle_Frame0,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [1] = {
        .pFrame = sSkreeOam_Idle_Frame1,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [2] = {
        .pFrame = sSkreeOam_Idle_Frame2,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [3] = {
        .pFrame = sSkreeOam_Idle_Frame3,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sSkreeOam_Spinning[6] = {
    [0] = {
        .pFrame = sSkreeOam_Idle_Frame0,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [1] = {
        .pFrame = sSkreeOam_Spinning_Frame1,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [2] = {
        .pFrame = sSkreeOam_Spinning_Frame2,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [3] = {
        .pFrame = sSkreeOam_Spinning_Frame1,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [4] = {
        .pFrame = sSkreeOam_Spinning_Frame2,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [5] = FRAME_DATA_TERMINATOR
};

const struct FrameData sSkreeOam_GoingDown[5] = {
    [0] = {
        .pFrame = sSkreeOam_Idle_Frame0,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [1] = {
        .pFrame = sSkreeOam_Idle_Frame1,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [2] = {
        .pFrame = sSkreeOam_Idle_Frame2,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [3] = {
        .pFrame = sSkreeOam_Idle_Frame3,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sSkreeOam_Crashing[5] = {
    [0] = {
        .pFrame = sSkreeOam_Idle_Frame0,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [1] = {
        .pFrame = sSkreeOam_Idle_Frame1,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [2] = {
        .pFrame = sSkreeOam_Idle_Frame2,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [3] = {
        .pFrame = sSkreeOam_Idle_Frame3,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sSkreeOam_CrashingUnused[5] = {
    [0] = {
        .pFrame = sSkreeOam_CrashingUnused_Frame0,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [1] = {
        .pFrame = sSkreeOam_CrashingUnused_Frame1,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [2] = {
        .pFrame = sSkreeOam_CrashingUnused_Frame2,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [3] = {
        .pFrame = sSkreeOam_CrashingUnused_Frame3,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sSkreeOam_CrashingUnused2[6] = {
    [0] = {
        .pFrame = sSkreeOam_CrashingUnused_Frame0,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [1] = {
        .pFrame = sSkreeOam_CrashingUnused2_Frame1,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [2] = {
        .pFrame = sSkreeOam_CrashingUnused2_Frame2,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [3] = {
        .pFrame = sSkreeOam_CrashingUnused2_Frame1,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [4] = {
        .pFrame = sSkreeOam_CrashingUnused2_Frame2,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [5] = FRAME_DATA_TERMINATOR
};

const struct FrameData sSkreeOam_CrashingUnused3[5] = {
    [0] = {
        .pFrame = sSkreeOam_CrashingUnused_Frame0,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [1] = {
        .pFrame = sSkreeOam_CrashingUnused_Frame1,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [2] = {
        .pFrame = sSkreeOam_CrashingUnused_Frame2,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [3] = {
        .pFrame = sSkreeOam_CrashingUnused_Frame3,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sSkreeOam_CrashingUnused4[5] = {
    [0] = {
        .pFrame = sSkreeOam_CrashingUnused_Frame0,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [1] = {
        .pFrame = sSkreeOam_CrashingUnused_Frame1,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [2] = {
        .pFrame = sSkreeOam_CrashingUnused_Frame2,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [3] = {
        .pFrame = sSkreeOam_CrashingUnused_Frame3,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sSkreeExplosionOAM_GoingDown[4] = {
    [0] = {
        .pFrame = sSkreeExplosionOAM_GoingDown_Frame0,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [1] = {
        .pFrame = sSkreeExplosionOAM_GoingDown_Frame1,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [2] = {
        .pFrame = sSkreeExplosionOAM_GoingDown_Frame2,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sSkreeExplosionOAM_GoingUp[4] = {
    [0] = {
        .pFrame = sSkreeExplosionOAM_GoingUp_Frame0,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [1] = {
        .pFrame = sSkreeExplosionOAM_GoingUp_Frame1,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [2] = {
        .pFrame = sSkreeExplosionOAM_GoingUp_Frame2,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [3] = FRAME_DATA_TERMINATOR
};
