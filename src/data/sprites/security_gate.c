#include "data/sprites/security_gate.h"
#include "macros.h"

const u32 sSecurityGateGfx[122] = INCBIN_U32("data/sprites/SecurityGate.gfx.lz");
const u16 sSecurityGatePal[16] = INCBIN_U16("data/sprites/SecurityGate.pal");

static const u16 sSecurityGateOam_Opened_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    0xc0, 0x1f8, OBJ_SPRITE_OAM | 0x22c
};

static const u16 sSecurityGateOam_Closing_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    OBJ_SHAPE_HORIZONTAL | 0xc0, 0x1f8, OBJ_SPRITE_OAM | 0x222
};

static const u16 sSecurityGateOam_Closing_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    OBJ_SHAPE_HORIZONTAL | 0xc0, 0x1f8, OBJ_SPRITE_OAM | 0x226
};

static const u16 sSecurityGateOam_Closing_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0xc0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x202
};

static const u16 sSecurityGateOam_Closing_Frame3[OAM_DATA_SIZE(1)] = {
    0x1,
    0xc0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x206
};

static const u16 sSecurityGateOam_Closing_Frame4[OAM_DATA_SIZE(2)] = {
    0x2,
    0xc8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x202,
    OBJ_SHAPE_HORIZONTAL | 0xc0, 0x1f8, OBJ_SPRITE_OAM | 0x220
};

static const u16 sSecurityGateOam_Closing_Frame5[OAM_DATA_SIZE(2)] = {
    0x2,
    0xc8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x206,
    OBJ_SHAPE_HORIZONTAL | 0xc0, 0x1f8, OBJ_SPRITE_OAM | 0x228
};

static const u16 sSecurityGateOam_Closing_Frame6[OAM_DATA_SIZE(2)] = {
    0x2,
    0xd0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x202,
    0xc0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x200
};

static const u16 sSecurityGateOam_Closing_Frame7[OAM_DATA_SIZE(2)] = {
    0x2,
    0xd0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x206,
    0xc0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x208
};

static const u16 sSecurityGateOam_Closing_Frame8[OAM_DATA_SIZE(3)] = {
    0x3,
    0xd8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x202,
    0xc8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x200,
    OBJ_SHAPE_HORIZONTAL | 0xc0, 0x1f8, OBJ_SPRITE_OAM | 0x228
};

static const u16 sSecurityGateOam_Closing_Frame9[OAM_DATA_SIZE(3)] = {
    0x3,
    0xd8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x206,
    0xc8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x208,
    OBJ_SHAPE_HORIZONTAL | 0xc0, 0x1f8, OBJ_SPRITE_OAM | 0x200
};

static const u16 sSecurityGateOam_Closing_Frame10[OAM_DATA_SIZE(3)] = {
    0x3,
    0xe0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x202,
    0xd0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x200,
    0xc0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x208
};

static const u16 sSecurityGateOam_Closing_Frame11[OAM_DATA_SIZE(3)] = {
    0x3,
    0xe0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x206,
    0xd0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x208,
    0xc0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x204
};

static const u16 sSecurityGateOam_Closing_Frame12[OAM_DATA_SIZE(4)] = {
    0x4,
    0xe8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x202,
    0xd8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x200,
    0xc8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x208,
    OBJ_SHAPE_HORIZONTAL | 0xc0, 0x1f8, OBJ_SPRITE_OAM | 0x200
};

static const u16 sSecurityGateOam_Closing_Frame13[OAM_DATA_SIZE(4)] = {
    0x4,
    0xe8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x206,
    0xd8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x208,
    0xc8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x204,
    OBJ_SHAPE_HORIZONTAL | 0xc0, 0x1f8, OBJ_SPRITE_OAM | 0x220
};

static const u16 sSecurityGateOam_Closing_Frame14[OAM_DATA_SIZE(4)] = {
    0x4,
    0xf0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x202,
    0xe0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x200,
    0xd0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x208,
    0xc0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x204
};

static const u16 sSecurityGateOam_Closing_Frame15[OAM_DATA_SIZE(5)] = {
    0x5,
    0xf0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x206,
    0xe0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x208,
    0xd0, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x204,
    OBJ_SHAPE_HORIZONTAL | 0xc0, 0x1f8, OBJ_SPRITE_OAM | 0x20c,
    OBJ_SHAPE_HORIZONTAL | 0xc8, 0x1f8, OBJ_SPRITE_OAM | 0x220
};

static const u16 sSecurityGateOam_Closing_Frame16[OAM_DATA_SIZE(5)] = {
    0x5,
    0xfb, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x202,
    0xeb, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x200,
    0xdb, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x208,
    0xcb, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x204,
    0xbb, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x20a
};

static const u16 sSecurityGateOam_Closed_Frame0[OAM_DATA_SIZE(5)] = {
    0x5,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x202,
    0xe8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x200,
    0xd8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x208,
    0xc8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x204,
    OBJ_SHAPE_HORIZONTAL | 0xc0, 0x1f8, OBJ_SPRITE_OAM | 0x22a
};

static const u16 sSecurityGateOam_Closed_Frame1[OAM_DATA_SIZE(5)] = {
    0x5,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x202,
    0xe8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x20e,
    0xd8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x210,
    0xc8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x212,
    OBJ_SHAPE_HORIZONTAL | 0xc0, 0x1f8, OBJ_SPRITE_OAM | 0x22a
};

static const u16 sSecurityGateOam_Closed_Frame2[OAM_DATA_SIZE(5)] = {
    0x5,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x202,
    0xe8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x214,
    0xd8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x216,
    0xc8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x218,
    OBJ_SHAPE_HORIZONTAL | 0xc0, 0x1f8, OBJ_SPRITE_OAM | 0x22a
};

const struct FrameData sSecurityGateOam_Opened[2] = {
    [0] = {
        .pFrame = sSecurityGateOam_Opened_Frame0,
        .timer = UCHAR_MAX
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sSecurityGateOam_Closing[18] = {
    [0] = {
        .pFrame = sSecurityGateOam_Closing_Frame0,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [1] = {
        .pFrame = sSecurityGateOam_Closing_Frame1,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [2] = {
        .pFrame = sSecurityGateOam_Closing_Frame2,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [3] = {
        .pFrame = sSecurityGateOam_Closing_Frame3,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [4] = {
        .pFrame = sSecurityGateOam_Closing_Frame4,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [5] = {
        .pFrame = sSecurityGateOam_Closing_Frame5,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [6] = {
        .pFrame = sSecurityGateOam_Closing_Frame6,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [7] = {
        .pFrame = sSecurityGateOam_Closing_Frame7,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [8] = {
        .pFrame = sSecurityGateOam_Closing_Frame8,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [9] = {
        .pFrame = sSecurityGateOam_Closing_Frame9,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [10] = {
        .pFrame = sSecurityGateOam_Closing_Frame10,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [11] = {
        .pFrame = sSecurityGateOam_Closing_Frame11,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [12] = {
        .pFrame = sSecurityGateOam_Closing_Frame12,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [13] = {
        .pFrame = sSecurityGateOam_Closing_Frame13,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [14] = {
        .pFrame = sSecurityGateOam_Closing_Frame14,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [15] = {
        .pFrame = sSecurityGateOam_Closing_Frame15,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [16] = {
        .pFrame = sSecurityGateOam_Closing_Frame16,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [17] = FRAME_DATA_TERMINATOR
};

const struct FrameData sSecurityGateOam_Closed[4] = {
    [0] = {
        .pFrame = sSecurityGateOam_Closed_Frame0,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [1] = {
        .pFrame = sSecurityGateOam_Closed_Frame1,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [2] = {
        .pFrame = sSecurityGateOam_Closed_Frame2,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sSecurityGateOam_Opening[18] = {
    [0] = {
        .pFrame = sSecurityGateOam_Closing_Frame16,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [1] = {
        .pFrame = sSecurityGateOam_Closing_Frame15,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [2] = {
        .pFrame = sSecurityGateOam_Closing_Frame14,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [3] = {
        .pFrame = sSecurityGateOam_Closing_Frame13,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [4] = {
        .pFrame = sSecurityGateOam_Closing_Frame12,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [5] = {
        .pFrame = sSecurityGateOam_Closing_Frame11,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [6] = {
        .pFrame = sSecurityGateOam_Closing_Frame10,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [7] = {
        .pFrame = sSecurityGateOam_Closing_Frame9,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [8] = {
        .pFrame = sSecurityGateOam_Closing_Frame8,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [9] = {
        .pFrame = sSecurityGateOam_Closing_Frame7,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [10] = {
        .pFrame = sSecurityGateOam_Closing_Frame6,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [11] = {
        .pFrame = sSecurityGateOam_Closing_Frame5,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [12] = {
        .pFrame = sSecurityGateOam_Closing_Frame4,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [13] = {
        .pFrame = sSecurityGateOam_Closing_Frame3,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [14] = {
        .pFrame = sSecurityGateOam_Closing_Frame2,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [15] = {
        .pFrame = sSecurityGateOam_Closing_Frame1,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [16] = {
        .pFrame = sSecurityGateOam_Closing_Frame0,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [17] = FRAME_DATA_TERMINATOR
};
