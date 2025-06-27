#include "data/sprites/space_pirate_carrying_power_bomb.h"
#include "macros.h"

const u32 sFakePowerBombGfx[115] = INCBIN_U32("data/sprites/FakePowerBomb.gfx.lz");
const u16 sFakePowerBombPal[16] = INCBIN_U16("data/sprites/FakePowerBomb.pal");

static const u16 sFakePowerBombOam_Idle_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x200
};

static const u16 sFakePowerBombOam_Idle_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x202
};

static const u16 sFakePowerBombOam_Idle_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x204
};

static const u16 sFakePowerBombOam_Idle_Frame3[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x206
};

const struct FrameData sFakePowerBombOam_Idle[5] = {
    [0] = {
        .pFrame = sFakePowerBombOam_Idle_Frame0,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [1] = {
        .pFrame = sFakePowerBombOam_Idle_Frame1,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [2] = {
        .pFrame = sFakePowerBombOam_Idle_Frame2,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [3] = {
        .pFrame = sFakePowerBombOam_Idle_Frame3,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [4] = FRAME_DATA_TERMINATOR
};
