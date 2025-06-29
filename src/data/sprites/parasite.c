#include "data/sprites/parasite.h"
#include "macros.h"

const u32 sParasiteGfx[309] = INCBIN_U32("data/sprites/Parasite.gfx.lz");
const u16 sParasitePal[16] = INCBIN_U16("data/sprites/Parasite.pal");

static const u16 sParasiteOam_Idle_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf8, 0x1fc, OBJ_SPRITE_OAM | 0x200
};

static const u16 sParasiteOam_Idle_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf8, 0x1fc, OBJ_SPRITE_OAM | 0x201
};

static const u16 sParasiteOam_Idle_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf8, 0x1fc, OBJ_SPRITE_OAM | 0x202
};

static const u16 sParasiteOam_Idle_Frame5[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf8, 0x1fc, OBJ_SPRITE_OAM | 0x203
};

static const u16 sParasiteOam_LandingAfterFalling_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf8, 0x1fc, OBJ_SPRITE_OAM | 0x220
};

static const u16 sParasiteOam_LandingAfterFalling_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf8, 0x1fc, OBJ_SPRITE_OAM | 0x221
};

static const u16 sParasiteOam_Landing_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf8, 0x1fc, OBJ_SPRITE_OAM | 0x222
};

static const u16 sParasiteOam_Landing_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf8, 0x1fc, OBJ_SPRITE_OAM | 0x223
};

static const u16 sParasiteOam_Tumbling_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf8, 0x1fb, OBJ_SPRITE_OAM | 0x204
};

static const u16 sParasiteOam_Tumbling_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, OBJ_Y_FLIP | 0x1fc, OBJ_SPRITE_OAM | 0x200
};

static const u16 sParasiteOam_Tumbling_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf8, 0x1fc, OBJ_SPRITE_OAM | 0x205
};

static const u16 sParasiteOam_TurningBackOnFeet_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf9, 0x1fc, OBJ_SPRITE_OAM | 0x224
};

static const u16 sParasiteOam_TurningBackOnFeet_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf9, 0x1fc, OBJ_SPRITE_OAM | 0x225
};

static const u16 sParasiteOam_TurningBackOnFeet_Frame3[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfa, OBJ_Y_FLIP | 0x1fc, OBJ_SPRITE_OAM | 0x224,
};

static const u16 sParasiteOam_TurningAround_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf8, 0x1fc, OBJ_SPRITE_OAM | 0x206
};

static const u16 sParasiteOam_JumpingUp_Unused_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf9, 0x1fd, OBJ_SPRITE_OAM | 0x207
};

static const u16 sParasiteOam_JumpingUp_Unused_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf9, 0x1fd, OBJ_SPRITE_OAM | 0x208
};

static const u16 sParasiteOam_JumpingUp_Unused_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf9, 0x1fd, OBJ_SPRITE_OAM | 0x209
};

static const u16 sParasiteOam_JumpingUp_Unused_Frame5[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf9, 0x1fe, OBJ_SPRITE_OAM | 0x20a
};

static const u16 sParasiteOam_JumpingUp_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf9, 0x1fc, OBJ_SPRITE_OAM | 0x207
};

static const u16 sParasiteOam_JumpingDown_Unused_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf9, 0x1fb, OBJ_SPRITE_OAM | 0x227
};

static const u16 sParasiteOam_JumpingDown_Unused_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf9, 0x1fb, OBJ_SPRITE_OAM | 0x228
};

static const u16 sParasiteOam_JumpingDown_Unused_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf9, 0x1fb, OBJ_SPRITE_OAM | 0x229
};

static const u16 sParasiteOam_JumpingDown_Unused_Frame5[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf9, 0x1fb, OBJ_SPRITE_OAM | 0x22a
};

static const u16 sParasiteOam_Attached_Unused_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfa, 0x1fc, OBJ_SPRITE_OAM | 0x20b
};

static const u16 sParasiteOam_Attached_Unused_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfa, 0x1fc, OBJ_SPRITE_OAM | 0x20c
};

static const u16 sParasiteOam_Attached_Unused_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfa, 0x1fc, OBJ_SPRITE_OAM | 0x20d
};

static const u16 sParasiteOam_Attached_Unused_Frame5[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfa, 0x1fc, OBJ_SPRITE_OAM | 0x20e
};

static const u16 sParasiteOam_Attached_Unused_Frame6[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfa, 0x1fc, OBJ_SPRITE_OAM | 0x20f
};

static const u16 sParasiteOam_Attached_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, OBJ_SPRITE_OAM | 0x22b
};

static const u16 sParasiteOam_Attached_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, OBJ_SPRITE_OAM | 0x22c
};

static const u16 sParasiteOam_Attached_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, OBJ_SPRITE_OAM | 0x22d
};

static const u16 sParasiteOam_Attached_Frame5[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, OBJ_SPRITE_OAM | 0x22e
};

static const u16 sParasiteOam_Attached_Frame6[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, OBJ_SPRITE_OAM | 0x22f
};

static const u16 sParasiteOam_Expelled_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, OBJ_SPRITE_OAM | 0x210
};

static const u16 sParasiteOam_Expelled_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, OBJ_SPRITE_OAM | 0x211
};

static const u16 sParasiteOam_Expelled_Frame3[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, OBJ_SPRITE_OAM | 0x212
};

static const u16 sParasiteOam_Expelled_Frame4[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, OBJ_SPRITE_OAM | 0x213
};

static const u16 sParasiteOam_Expelled_Frame5[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, OBJ_SPRITE_OAM | 0x214
};

static const u16 sParasiteOam_Expelled_Frame6[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, OBJ_SPRITE_OAM | 0x215
};

static const u16 sParasiteOam_Expelled_Frame7[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, OBJ_SPRITE_OAM | 0x216
};

static const u16 sParasiteOam_Dying_Unused_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfa, 0x1fc, OBJ_SPRITE_OAM | 0x230
};

static const u16 sParasiteOam_Dying_Unused_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfa, 0x1fc, OBJ_SPRITE_OAM | 0x231
};

static const u16 sParasiteOam_Dying_Unused_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfa, 0x1fc, OBJ_SPRITE_OAM | 0x232
};

static const u16 sParasiteOam_Dying_Unused_Frame3[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfa, 0x1fc, OBJ_SPRITE_OAM | 0x233
};

static const u16 sParasiteOam_Dying_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, OBJ_SPRITE_OAM | 0x217
};

static const u16 sParasiteOam_Dying_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, OBJ_X_FLIP | OBJ_Y_FLIP | 0x1fc, OBJ_SPRITE_OAM | 0x217
};

static const u16 sParasiteOam_Dying_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfb, 0x1fc, OBJ_SPRITE_OAM | 0x218
};

static const u16 sParasiteOam_Dying_Frame3[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfa, OBJ_X_FLIP | OBJ_Y_FLIP | 0x1fc, OBJ_SPRITE_OAM | 0x218
};

static const u16 sParasiteOam_Dying_Frame4[OAM_DATA_SIZE(2)] = {
    0x2,
    0xf9, 0x1fc, OBJ_SPRITE_OAM | 0x219,
    0xf4, 0x1fc, OBJ_SPRITE_OAM | 0x237
};

static const u16 sParasiteOam_Dying_Frame5[OAM_DATA_SIZE(2)] = {
    0x2,
    0xf8, 0x1fc, OBJ_SPRITE_OAM | 0x21a,
    0xf4, 0x1fc, OBJ_SPRITE_OAM | 0x238
};

static const u16 sParasiteOam_Dying_Frame6[OAM_DATA_SIZE(2)] = {
    0x2,
    0xf7, 0x1fc, OBJ_SPRITE_OAM | 0x21b,
    0xf3, 0x1fc, OBJ_SPRITE_OAM | 0x239
};

static const u16 sParasiteOam_Dying_Frame7[OAM_DATA_SIZE(2)] = {
    0x2,
    0xf6, OBJ_X_FLIP | 0x1fc, OBJ_SPRITE_OAM | 0x21b,
    0xf2, 0x1fc, OBJ_SPRITE_OAM | 0x23a
};

static const u16 sParasiteOam_Dying_Frame8[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf1, 0x1fc, OBJ_SPRITE_OAM | 0x23b
};

static const u16 sParasiteOam_Dying_Frame9[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf1, OBJ_X_FLIP | 0x1fc, OBJ_SPRITE_OAM | 0x23b
};

const struct FrameData sParasiteOam_Idle[7] = {
    [0] = {
        .pFrame = sParasiteOam_Idle_Frame0,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [1] = {
        .pFrame = sParasiteOam_Idle_Frame1,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [2] = {
        .pFrame = sParasiteOam_Idle_Frame2,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [3] = {
        .pFrame = sParasiteOam_Idle_Frame1,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [4] = {
        .pFrame = sParasiteOam_Idle_Frame0,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [5] = {
        .pFrame = sParasiteOam_Idle_Frame5,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sParasiteOam_LandingAfterFalling[5] = {
    [0] = {
        .pFrame = sParasiteOam_Idle_Frame0,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [1] = {
        .pFrame = sParasiteOam_LandingAfterFalling_Frame1,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [2] = {
        .pFrame = sParasiteOam_LandingAfterFalling_Frame2,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [3] = {
        .pFrame = sParasiteOam_LandingAfterFalling_Frame1,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sParasiteOam_Landing[4] = {
    [0] = {
        .pFrame = sParasiteOam_Landing_Frame0,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [1] = {
        .pFrame = sParasiteOam_Idle_Frame0,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [2] = {
        .pFrame = sParasiteOam_Landing_Frame2,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sParasiteOam_Tumbling[5] = {
    [0] = {
        .pFrame = sParasiteOam_Tumbling_Frame0,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [1] = {
        .pFrame = sParasiteOam_Tumbling_Frame1,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [2] = {
        .pFrame = sParasiteOam_Tumbling_Frame2,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [3] = {
        .pFrame = sParasiteOam_Tumbling_Frame1,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sParasiteOam_TurningBackOnFeet[8] = {
    [0] = {
        .pFrame = sParasiteOam_Tumbling_Frame1,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [1] = {
        .pFrame = sParasiteOam_TurningBackOnFeet_Frame1,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [2] = {
        .pFrame = sParasiteOam_TurningBackOnFeet_Frame2,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [3] = {
        .pFrame = sParasiteOam_TurningBackOnFeet_Frame3,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [4] = {
        .pFrame = sParasiteOam_Landing_Frame0,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [5] = {
        .pFrame = sParasiteOam_Idle_Frame0,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [6] = {
        .pFrame = sParasiteOam_Landing_Frame2,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [7] = FRAME_DATA_TERMINATOR
};

const struct FrameData sParasiteOam_TurningAround[2] = {
    [0] = {
        .pFrame = sParasiteOam_TurningAround_Frame0,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sParasiteOam_JumpingUp_Unused[7] = {
    [0] = {
        .pFrame = sParasiteOam_JumpingUp_Unused_Frame0,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [1] = {
        .pFrame = sParasiteOam_JumpingUp_Unused_Frame1,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [2] = {
        .pFrame = sParasiteOam_JumpingUp_Unused_Frame2,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [3] = {
        .pFrame = sParasiteOam_JumpingUp_Unused_Frame1,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [4] = {
        .pFrame = sParasiteOam_JumpingUp_Unused_Frame0,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [5] = {
        .pFrame = sParasiteOam_JumpingUp_Unused_Frame5,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sParasiteOam_JumpingDown_Unused[7] = {
    [0] = {
        .pFrame = sParasiteOam_JumpingDown_Unused_Frame0,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [1] = {
        .pFrame = sParasiteOam_JumpingDown_Unused_Frame1,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [2] = {
        .pFrame = sParasiteOam_JumpingDown_Unused_Frame2,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [3] = {
        .pFrame = sParasiteOam_JumpingDown_Unused_Frame1,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [4] = {
        .pFrame = sParasiteOam_JumpingDown_Unused_Frame0,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [5] = {
        .pFrame = sParasiteOam_JumpingDown_Unused_Frame5,
        .timer = CONVERT_SECONDS(0.1f)
    },
    [6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sParasiteOam_JumpingUp[3] = {
    [0] = {
        .pFrame = sParasiteOam_JumpingUp_Unused_Frame0,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [1] = {
        .pFrame = sParasiteOam_JumpingUp_Frame1,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sParasiteOam_Attached_Unused[9] = {
    [0] = {
        .pFrame = sParasiteOam_Attached_Unused_Frame0,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [1] = {
        .pFrame = sParasiteOam_Attached_Unused_Frame1,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [2] = {
        .pFrame = sParasiteOam_Attached_Unused_Frame2,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [3] = {
        .pFrame = sParasiteOam_Attached_Unused_Frame1,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [4] = {
        .pFrame = sParasiteOam_Attached_Unused_Frame0,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [5] = {
        .pFrame = sParasiteOam_Attached_Unused_Frame5,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [6] = {
        .pFrame = sParasiteOam_Attached_Unused_Frame6,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [7] = {
        .pFrame = sParasiteOam_Attached_Unused_Frame5,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [8] = FRAME_DATA_TERMINATOR
};

const struct FrameData sParasiteOam_Attached[9] = {
    [0] = {
        .pFrame = sParasiteOam_Attached_Frame0,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [1] = {
        .pFrame = sParasiteOam_Attached_Frame1,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [2] = {
        .pFrame = sParasiteOam_Attached_Frame2,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [3] = {
        .pFrame = sParasiteOam_Attached_Frame1,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [4] = {
        .pFrame = sParasiteOam_Attached_Frame0,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [5] = {
        .pFrame = sParasiteOam_Attached_Frame5,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [6] = {
        .pFrame = sParasiteOam_Attached_Frame6,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [7] = {
        .pFrame = sParasiteOam_Attached_Frame5,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [8] = FRAME_DATA_TERMINATOR
};

const struct FrameData sParasiteOam_Expelled[9] = {
    [0] = {
        .pFrame = sParasiteOam_Attached_Frame0,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [1] = {
        .pFrame = sParasiteOam_Expelled_Frame1,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [2] = {
        .pFrame = sParasiteOam_Expelled_Frame2,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [3] = {
        .pFrame = sParasiteOam_Expelled_Frame3,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [4] = {
        .pFrame = sParasiteOam_Expelled_Frame4,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [5] = {
        .pFrame = sParasiteOam_Expelled_Frame5,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [6] = {
        .pFrame = sParasiteOam_Expelled_Frame6,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [7] = {
        .pFrame = sParasiteOam_Expelled_Frame7,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [8] = FRAME_DATA_TERMINATOR
};

const struct FrameData sParasiteOam_Dying_Unused[5] = {
    [0] = {
        .pFrame = sParasiteOam_Dying_Unused_Frame0,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [1] = {
        .pFrame = sParasiteOam_Dying_Unused_Frame1,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [2] = {
        .pFrame = sParasiteOam_Dying_Unused_Frame2,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [3] = {
        .pFrame = sParasiteOam_Dying_Unused_Frame3,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sParasiteOam_Dying[11] = {
    [0] = {
        .pFrame = sParasiteOam_Dying_Frame0,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [1] = {
        .pFrame = sParasiteOam_Dying_Frame1,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [2] = {
        .pFrame = sParasiteOam_Dying_Frame2,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [3] = {
        .pFrame = sParasiteOam_Dying_Frame3,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [4] = {
        .pFrame = sParasiteOam_Dying_Frame4,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [5] = {
        .pFrame = sParasiteOam_Dying_Frame5,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [6] = {
        .pFrame = sParasiteOam_Dying_Frame6,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [7] = {
        .pFrame = sParasiteOam_Dying_Frame7,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [8] = {
        .pFrame = sParasiteOam_Dying_Frame8,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [9] = {
        .pFrame = sParasiteOam_Dying_Frame9,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [10] = FRAME_DATA_TERMINATOR
};
