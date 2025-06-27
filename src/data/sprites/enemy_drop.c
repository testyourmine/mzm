#include "data/sprites/enemy_drop.h"
#include "macros.h"

static const u16 sEnemyDropOam_SmallEnergy_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, 0x4183
};

static const u16 sEnemyDropOam_SmallEnergy_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, 0x41a3
};

static const u16 sEnemyDropOam_SmallEnergy_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, 0x4184
};

static const u16 sEnemyDropOam_SmallEnergy_Frame3[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, 0x41a4
};

static const u16 sEnemyDropOam_LargeEnergy_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, 0x41c0
};

static const u16 sEnemyDropOam_LargeEnergy_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, 0x41c2,
};

static const u16 sEnemyDropOam_LargeEnergy_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, 0x41c4
};

static const u16 sEnemyDropOam_LargeEnergy_Frame3[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, 0x41c6
};

static const u16 sEnemyDropOam_Missile_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    OBJ_SHAPE_VERTICAL | 0xf8, 0x1fc, 0x4185
};

static const u16 sEnemyDropOam_Missile_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    OBJ_SHAPE_VERTICAL | 0xf8, 0x1fc, 0x4190
};

static const u16 sEnemyDropOam_SuperMissile_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    OBJ_SHAPE_VERTICAL | 0xf8, 0x1fc, 0x4186
};

static const u16 sEnemyDropOam_SuperMissile_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    OBJ_SHAPE_VERTICAL | 0xf8, 0x1fc, 0x4191
};

static const u16 sEnemyDropOam_PowerBomb_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, 0x414b
};

static const u16 sEnemyDropOam_PowerBomb_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, 0x416c
};

static const u16 sEnemyDropOam_MultipleLargeEnergySlot1_Frame0[OAM_DATA_SIZE(3)] = {
    0x3,
    0xf3, OBJ_SIZE_16x16 | 0x1f1, 0x41c0,
    0xf8, OBJ_SIZE_16x16 | 0x0, 0x41c0,
    0x0, OBJ_SIZE_16x16 | 0x1f8, 0x41c0
};

static const u16 sEnemyDropOam_MultipleLargeEnergySlot1_Frame1[OAM_DATA_SIZE(3)] = {
    0x3,
    0xf3, OBJ_SIZE_16x16 | 0x1f1, 0x41c2,
    0xf8, OBJ_SIZE_16x16 | 0x0, 0x41c2,
    0x0, OBJ_SIZE_16x16 | 0x1f8, 0x41c2
};

static const u16 sEnemyDropOam_MultipleLargeEnergySlot1_Frame2[OAM_DATA_SIZE(3)] = {
    0x3,
    0xf3, OBJ_SIZE_16x16 | 0x1f1, 0x41c4,
    0xf8, OBJ_SIZE_16x16 | 0x0, 0x41c4,
    0x0, OBJ_SIZE_16x16 | 0x1f8, 0x41c4
};

static const u16 sEnemyDropOam_MultipleLargeEnergySlot1_Frame3[OAM_DATA_SIZE(3)] = {
    0x3,
    0xf3, OBJ_SIZE_16x16 | 0x1f1, 0x41c6,
    0xf8, OBJ_SIZE_16x16 | 0x0, 0x41c6,
    0x0, OBJ_SIZE_16x16 | 0x1f8, 0x41c6
};

static const u16 sEnemyDropOam_MultipleLargeEnergySlot3_Frame0[OAM_DATA_SIZE(3)] = {
    0x3,
    0xf2, OBJ_SIZE_16x16 | 0x1f7, 0x41c0,
    0xff, OBJ_SIZE_16x16 | 0x1f1, 0x41c0,
    0xfc, OBJ_SIZE_16x16 | 0x1fc, 0x41c0
};

static const u16 sEnemyDropOam_MultipleLargeEnergySlot3_Frame1[OAM_DATA_SIZE(3)] = {
    0x3,
    0xf2, OBJ_SIZE_16x16 | 0x1f7, 0x41c2,
    0xff, OBJ_SIZE_16x16 | 0x1f1, 0x41c2,
    0xfc, OBJ_SIZE_16x16 | 0x1fc, 0x41c2
};

static const u16 sEnemyDropOam_MultipleLargeEnergySlot3_Frame2[OAM_DATA_SIZE(3)] = {
    0x3,
    0xf2, OBJ_SIZE_16x16 | 0x1f7, 0x41c4,
    0xff, OBJ_SIZE_16x16 | 0x1f1, 0x41c4,
    0xfc, OBJ_SIZE_16x16 | 0x1fc, 0x41c4,
};

static const u16 sEnemyDropOam_MultipleLargeEnergySlot3_Frame3[OAM_DATA_SIZE(3)] = {
    0x3,
    0xf2, OBJ_SIZE_16x16 | 0x1f7, 0x41c6,
    0xff, OBJ_SIZE_16x16 | 0x1f1, 0x41c6,
    0xfc, OBJ_SIZE_16x16 | 0x1fc, 0x41c6
};

static const u16 sEnemyDropOam_MultipleLargeEnergySlot2_Frame0[OAM_DATA_SIZE(3)] = {
    0x3,
    0xf4, OBJ_SIZE_16x16 | 0x1fb, 0x41c0,
    0xff, OBJ_SIZE_16x16 | 0x1f3, 0x41c0,
    0xf0, OBJ_SIZE_16x16 | 0x1f4, 0x41c0
};

static const u16 sEnemyDropOam_MultipleLargeEnergySlot2_Frame1[OAM_DATA_SIZE(3)] = {
    0x3,
    0xf4, OBJ_SIZE_16x16 | 0x1fb, 0x41c2,
    0xff, OBJ_SIZE_16x16 | 0x1f3, 0x41c2,
    0xf0, OBJ_SIZE_16x16 | 0x1f4, 0x41c2
};

static const u16 sEnemyDropOam_MultipleLargeEnergySlot2_Frame2[OAM_DATA_SIZE(3)] = {
    0x3,
    0xf4, OBJ_SIZE_16x16 | 0x1fb, 0x41c4,
    0xff, OBJ_SIZE_16x16 | 0x1f3, 0x41c4,
    0xf0, OBJ_SIZE_16x16 | 0x1f4, 0x41c4
};

static const u16 sEnemyDropOam_MultipleLargeEnergySlot2_Frame3[OAM_DATA_SIZE(3)] = {
    0x3,
    0xf4, OBJ_SIZE_16x16 | 0x1fb, 0x41c6,
    0xff, OBJ_SIZE_16x16 | 0x1f3, 0x41c6,
    0xf0, OBJ_SIZE_16x16 | 0x1f4, 0x41c6
};

const struct FrameData sEnemyDropOam_SmallEnergy[5] = {
    [0] = {
        .pFrame = sEnemyDropOam_SmallEnergy_Frame0,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [1] = {
        .pFrame = sEnemyDropOam_SmallEnergy_Frame1,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [2] = {
        .pFrame = sEnemyDropOam_SmallEnergy_Frame2,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [3] = {
        .pFrame = sEnemyDropOam_SmallEnergy_Frame3,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sEnemyDropOam_LargeEnergy[5] = {
    [0] = {
        .pFrame = sEnemyDropOam_LargeEnergy_Frame0,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [1] = {
        .pFrame = sEnemyDropOam_LargeEnergy_Frame1,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [2] = {
        .pFrame = sEnemyDropOam_LargeEnergy_Frame2,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [3] = {
        .pFrame = sEnemyDropOam_LargeEnergy_Frame3,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sEnemyDropOam_Missile[3] = {
    [0] = {
        .pFrame = sEnemyDropOam_Missile_Frame0,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [1] = {
        .pFrame = sEnemyDropOam_Missile_Frame1,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sEnemyDropOam_SuperMissile[3] = {
    [0] = {
        .pFrame = sEnemyDropOam_SuperMissile_Frame0,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [1] = {
        .pFrame = sEnemyDropOam_SuperMissile_Frame1,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sEnemyDropOam_PowerBomb[3] = {
    [0] = {
        .pFrame = sEnemyDropOam_PowerBomb_Frame0,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [1] = {
        .pFrame = sEnemyDropOam_PowerBomb_Frame1,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sEnemyDropOam_MultipleLargeEnergySlot1[5] = {
    [0] = {
        .pFrame = sEnemyDropOam_MultipleLargeEnergySlot1_Frame0,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [1] = {
        .pFrame = sEnemyDropOam_MultipleLargeEnergySlot1_Frame1,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [2] = {
        .pFrame = sEnemyDropOam_MultipleLargeEnergySlot1_Frame2,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [3] = {
        .pFrame = sEnemyDropOam_MultipleLargeEnergySlot1_Frame3,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sEnemyDropOam_MultipleLargeEnergySlot3[5] = {
    [0] = {
        .pFrame = sEnemyDropOam_MultipleLargeEnergySlot3_Frame0,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [1] = {
        .pFrame = sEnemyDropOam_MultipleLargeEnergySlot3_Frame1,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [2] = {
        .pFrame = sEnemyDropOam_MultipleLargeEnergySlot3_Frame2,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [3] = {
        .pFrame = sEnemyDropOam_MultipleLargeEnergySlot3_Frame3,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sEnemyDropOam_MultipleLargeEnergySlot2[5] = {
    [0] = {
        .pFrame = sEnemyDropOam_MultipleLargeEnergySlot2_Frame0,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [1] = {
        .pFrame = sEnemyDropOam_MultipleLargeEnergySlot2_Frame1,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [2] = {
        .pFrame = sEnemyDropOam_MultipleLargeEnergySlot2_Frame2,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [3] = {
        .pFrame = sEnemyDropOam_MultipleLargeEnergySlot2_Frame3,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [4] = FRAME_DATA_TERMINATOR
};
