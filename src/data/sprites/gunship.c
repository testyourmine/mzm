#include "data/sprites/gunship.h"
#include "macros.h"

const s16 sGunshipTakingOffYVelocity[153] = {
0, 0, -1, 0, 0, -1, 0, 0, 0, -1, 0, -1, 0, -1, 0,
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -1,
-2, -1, -2, -1, -2, -2, -2, -2, -2, -2, -2, -2,
-2, -3, -3, -3, -3, -4, -4, -4, -4, -2, -2, -2,
-2, -2, -2, -2, -2, -1, -2, -1, -2, -1, -2, -1,
-2, 0, -1, 0, -1, 0, -1, 0, -1, 0, 0, -1, 0, 0,
-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0,
1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0,
1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1,
0, -1, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0,
-1, 0, -1, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, SHORT_MAX
};

const s16 sGunshipFlyingYVelocity[22] = {
    -3, -3, -3, -3, -4, -4, -4, -4, -5, -5, -6, -6,
    -7, -7, -8, -12, -16, -20, -24, -28, -32, SHORT_MAX
};

const u32 sGunshipGfx[1027] = INCBIN_U32("data/sprites/Gunship.gfx.lz");
const u16 sGunshipPal[48] = INCBIN_U16("data/sprites/Gunship.pal");
const u16 sGunshipFlashingPal[8 * 16] = INCBIN_U16("data/sprites/GunshipFlashingPal.pal");

static const u16 sGunshipOam_Idle_Frame0[OAM_DATA_SIZE(17)] = {
    0x11,
    OBJ_SHAPE_VERTICAL | 0xf8, 0x18d, OBJ_SPRITE_OAM | 0x1300,
    0xf4, 0x195, OBJ_SPRITE_OAM | 0x1301,
    OBJ_SHAPE_HORIZONTAL | 0xef, OBJ_SIZE_32x8 | 0x19d, OBJ_SPRITE_OAM | 0x1302,
    0xef, 0x1bd, OBJ_SPRITE_OAM | 0x1306,
    OBJ_SHAPE_VERTICAL | 0xf8, OBJ_X_FLIP | 0x6b, OBJ_SPRITE_OAM | 0x1300,
    0xf4, OBJ_X_FLIP | 0x63, OBJ_SPRITE_OAM | 0x1301,
    OBJ_SHAPE_HORIZONTAL | 0xef, OBJ_X_FLIP | OBJ_SIZE_32x8 | 0x43, OBJ_SPRITE_OAM | 0x1302,
    0xef, OBJ_X_FLIP | 0x3b, OBJ_SPRITE_OAM | 0x1306,
    0xeb, OBJ_SIZE_16x16 | 0x1ca, OBJ_SPRITE_OAM | 0x1240,
    0xeb, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x26, OBJ_SPRITE_OAM | 0x1240,
    OBJ_SHAPE_HORIZONTAL | 0xdb, OBJ_SIZE_32x16 | 0x1d8, OBJ_SPRITE_OAM | 0x1200,
    0xdb, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x1204,
    OBJ_SHAPE_HORIZONTAL | 0xdb, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x8, OBJ_SPRITE_OAM | 0x1200,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_SIZE_64x32 | 0x180, OBJ_SPRITE_OAM | 0x280,
    0xcb, OBJ_SIZE_64x64 | 0x1c0, OBJ_SPRITE_OAM | 0x208,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_X_FLIP | OBJ_SIZE_64x32 | 0x40, OBJ_SPRITE_OAM | 0x280,
    0xcb, OBJ_X_FLIP | OBJ_SIZE_64x64 | 0x0, OBJ_SPRITE_OAM | 0x208
};

static const u16 sGunshipOam_Idle_Frame1[OAM_DATA_SIZE(17)] = {
    0x11,
    OBJ_SHAPE_VERTICAL | 0xf8, 0x18d, OBJ_SPRITE_OAM | 0x1340,
    0xf4, 0x195, OBJ_SPRITE_OAM | 0x1341,
    OBJ_SHAPE_HORIZONTAL | 0xef, OBJ_SIZE_32x8 | 0x19d, OBJ_SPRITE_OAM | 0x1342,
    0xef, 0x1bd, OBJ_SPRITE_OAM | 0x1346,
    OBJ_SHAPE_VERTICAL | 0xf8, OBJ_X_FLIP | 0x6b, OBJ_SPRITE_OAM | 0x1340,
    0xf4, OBJ_X_FLIP | 0x63, OBJ_SPRITE_OAM | 0x1341,
    OBJ_SHAPE_HORIZONTAL | 0xef, OBJ_X_FLIP | OBJ_SIZE_32x8 | 0x43, OBJ_SPRITE_OAM | 0x1342,
    0xef, OBJ_X_FLIP | 0x3b, OBJ_SPRITE_OAM | 0x1346,
    0xeb, OBJ_SIZE_16x16 | 0x1ca, OBJ_SPRITE_OAM | 0x1242,
    0xeb, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x26, OBJ_SPRITE_OAM | 0x1242,
    OBJ_SHAPE_HORIZONTAL | 0xdb, OBJ_SIZE_32x16 | 0x1d8, OBJ_SPRITE_OAM | 0x1200,
    0xdb, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x1204,
    OBJ_SHAPE_HORIZONTAL | 0xdb, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x8, OBJ_SPRITE_OAM | 0x1200,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_SIZE_64x32 | 0x180, OBJ_SPRITE_OAM | 0x280,
    0xcb, OBJ_SIZE_64x64 | 0x1c0, OBJ_SPRITE_OAM | 0x208,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_X_FLIP | OBJ_SIZE_64x32 | 0x40, OBJ_SPRITE_OAM | 0x280,
    0xcb, OBJ_X_FLIP | OBJ_SIZE_64x64 | 0x0, OBJ_SPRITE_OAM | 0x208
};

static const u16 sGunshipOam_Idle_Frame2[OAM_DATA_SIZE(17)] = {
    0x11,
    OBJ_SHAPE_VERTICAL | 0xf8, 0x18d, OBJ_SPRITE_OAM | 0x1307,
    0xf4, 0x195, OBJ_SPRITE_OAM | 0x1308,
    OBJ_SHAPE_HORIZONTAL | 0xef, OBJ_SIZE_32x8 | 0x19d, OBJ_SPRITE_OAM | 0x1309,
    0xef, 0x1bd, OBJ_SPRITE_OAM | 0x130d,
    OBJ_SHAPE_VERTICAL | 0xf8, OBJ_X_FLIP | 0x6b, OBJ_SPRITE_OAM | 0x1307,
    0xf4, OBJ_X_FLIP | 0x63, OBJ_SPRITE_OAM | 0x1308,
    OBJ_SHAPE_HORIZONTAL | 0xef, OBJ_X_FLIP | OBJ_SIZE_32x8 | 0x43, OBJ_SPRITE_OAM | 0x1309,
    0xef, OBJ_X_FLIP | 0x3b, OBJ_SPRITE_OAM | 0x130d,
    0xeb, OBJ_SIZE_16x16 | 0x1ca, OBJ_SPRITE_OAM | 0x1244,
    0xeb, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x26, OBJ_SPRITE_OAM | 0x1244,
    OBJ_SHAPE_HORIZONTAL | 0xdb, OBJ_SIZE_32x16 | 0x1d8, OBJ_SPRITE_OAM | 0x1200,
    0xdb, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x1204,
    OBJ_SHAPE_HORIZONTAL | 0xdb, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x8, OBJ_SPRITE_OAM | 0x1200,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_SIZE_64x32 | 0x180, OBJ_SPRITE_OAM | 0x280,
    0xcb, OBJ_SIZE_64x64 | 0x1c0, OBJ_SPRITE_OAM | 0x208,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_X_FLIP | OBJ_SIZE_64x32 | 0x40, OBJ_SPRITE_OAM | 0x280,
    0xcb, OBJ_X_FLIP | OBJ_SIZE_64x64 | 0x0, OBJ_SPRITE_OAM | 0x208
};

static const u16 sGunshipOam_Idle_Frame3[OAM_DATA_SIZE(17)] = {
    0x11,
    OBJ_SHAPE_VERTICAL | 0xf8, 0x18d, OBJ_SPRITE_OAM | 0x1347,
    0xf4, 0x195, OBJ_SPRITE_OAM | 0x1348,
    OBJ_SHAPE_HORIZONTAL | 0xef, OBJ_SIZE_32x8 | 0x19d, OBJ_SPRITE_OAM | 0x1349,
    0xef, 0x1bd, OBJ_SPRITE_OAM | 0x134d,
    OBJ_SHAPE_VERTICAL | 0xf8, OBJ_X_FLIP | 0x6b, OBJ_SPRITE_OAM | 0x1347,
    0xf4, OBJ_X_FLIP | 0x63, OBJ_SPRITE_OAM | 0x1348,
    OBJ_SHAPE_HORIZONTAL | 0xef, OBJ_X_FLIP | OBJ_SIZE_32x8 | 0x43, OBJ_SPRITE_OAM | 0x1349,
    0xef, OBJ_X_FLIP | 0x3b, OBJ_SPRITE_OAM | 0x134d,
    0xeb, OBJ_SIZE_16x16 | 0x1ca, OBJ_SPRITE_OAM | 0x1246,
    0xeb, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x26, OBJ_SPRITE_OAM | 0x1246,
    OBJ_SHAPE_HORIZONTAL | 0xdb, OBJ_SIZE_32x16 | 0x1d8, OBJ_SPRITE_OAM | 0x1200,
    0xdb, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x1204,
    OBJ_SHAPE_HORIZONTAL | 0xdb, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x8, OBJ_SPRITE_OAM | 0x1200,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_SIZE_64x32 | 0x180, OBJ_SPRITE_OAM | 0x280,
    0xcb, OBJ_SIZE_64x64 | 0x1c0, OBJ_SPRITE_OAM | 0x208,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_X_FLIP | OBJ_SIZE_64x32 | 0x40, OBJ_SPRITE_OAM | 0x280,
    0xcb, OBJ_X_FLIP | OBJ_SIZE_64x64 | 0x0, OBJ_SPRITE_OAM | 0x208
};

static const u16 sGunshipPartOam_EntranceFrontClosed_Frame0[OAM_DATA_SIZE(4)] = {
    0x4,
    OBJ_SHAPE_HORIZONTAL | 0xd0, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x210,
    0xd0, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x210,
    0xcf, OBJ_SIZE_16x16 | 0x1e2, OBJ_SPRITE_OAM | 0x206,
    0xcf, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0xe, OBJ_SPRITE_OAM | 0x206
};

static const u16 sGunshipPartOam_EntranceFrontOpening_Frame0[OAM_DATA_SIZE(4)] = {
    0x4,
    OBJ_SHAPE_HORIZONTAL | 0xd0, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x210,
    0xd0, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x210,
    0xce, OBJ_SIZE_16x16 | 0x1e1, OBJ_SPRITE_OAM | 0x206,
    0xce, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0xf, OBJ_SPRITE_OAM | 0x206
};

static const u16 sGunshipPartOam_EntranceFrontOpening_Frame1[OAM_DATA_SIZE(4)] = {
    0x4,
    OBJ_SHAPE_HORIZONTAL | 0xd0, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x210,
    0xd0, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x210,
    0xcd, OBJ_SIZE_16x16 | 0x1e0, OBJ_SPRITE_OAM | 0x206,
    0xcd, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x10, OBJ_SPRITE_OAM | 0x206
};

static const u16 sGunshipPartOam_EntranceFrontOpening_Frame2[OAM_DATA_SIZE(4)] = {
    0x4,
    OBJ_SHAPE_HORIZONTAL | 0xd0, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x210,
    0xd0, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x210,
    0xcd, OBJ_SIZE_16x16 | 0x1df, OBJ_SPRITE_OAM | 0x206,
    0xcd, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x11, OBJ_SPRITE_OAM | 0x206
};

static const u16 sGunshipPartOam_EntranceFrontOpening_Frame3[OAM_DATA_SIZE(4)] = {
    0x4,
    OBJ_SHAPE_HORIZONTAL | 0xd0, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x210,
    0xd0, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x210,
    0xcd, OBJ_SIZE_16x16 | 0x1dd, OBJ_SPRITE_OAM | 0x206,
    0xcd, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x13, OBJ_SPRITE_OAM | 0x206
};

static const u16 sGunshipPartOam_EntranceFrontOpened_Frame0[OAM_DATA_SIZE(6)] = {
    0x6,
    0xd2, 0x1e6, OBJ_SPRITE_OAM | 0x121a,
    0xd2, OBJ_X_FLIP | 0x12, OBJ_SPRITE_OAM | 0x121a,
    OBJ_SHAPE_HORIZONTAL | 0xd0, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x210,
    0xd0, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x210,
    0xcd, OBJ_SIZE_16x16 | 0x1de, OBJ_SPRITE_OAM | 0x206,
    0xcd, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x12, OBJ_SPRITE_OAM | 0x206
};

static const u16 sGunshipPartOam_EntranceFrontOpened_Frame1[OAM_DATA_SIZE(6)] = {
    0x6,
    0xd2, 0x1e6, OBJ_SPRITE_OAM | 0x123a,
    0xd2, OBJ_X_FLIP | 0x12, OBJ_SPRITE_OAM | 0x123a,
    OBJ_SHAPE_HORIZONTAL | 0xd0, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x210,
    0xd0, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x210,
    0xcd, OBJ_SIZE_16x16 | 0x1de, OBJ_SPRITE_OAM | 0x206,
    0xcd, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x12, OBJ_SPRITE_OAM | 0x206
};

static const u16 sGunshipPartOam_EntranceFrontOpened_Frame2[OAM_DATA_SIZE(6)] = {
    0x6,
    0xd2, 0x1e6, OBJ_SPRITE_OAM | 0x125a,
    0xd2, OBJ_X_FLIP | 0x12, OBJ_SPRITE_OAM | 0x125a,
    OBJ_SHAPE_HORIZONTAL | 0xd0, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x210,
    0xd0, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x210,
    0xcd, OBJ_SIZE_16x16 | 0x1de, OBJ_SPRITE_OAM | 0x206,
    0xcd, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x12, OBJ_SPRITE_OAM | 0x206
};

static const u16 sGunshipPartOam_EntranceFrontOpened_Frame3[OAM_DATA_SIZE(6)] = {
    0x6,
    0xd2, 0x1e6, OBJ_SPRITE_OAM | 0x127a,
    0xd2, OBJ_X_FLIP | 0x12, OBJ_SPRITE_OAM | 0x127a,
    OBJ_SHAPE_HORIZONTAL | 0xd0, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x210,
    0xd0, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x210,
    0xcd, OBJ_SIZE_16x16 | 0x1de, OBJ_SPRITE_OAM | 0x206,
    0xcd, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x12, OBJ_SPRITE_OAM | 0x206
};

static const u16 sGunshipPartOam_EntranceBackCLosed_Frame0[OAM_DATA_SIZE(5)] = {
    0x5,
    OBJ_SHAPE_HORIZONTAL | 0xcb, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x290,
    0xcb, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x290,
    OBJ_SHAPE_HORIZONTAL | 0xcb, OBJ_SIZE_32x16 | 0x1f0, OBJ_SPRITE_OAM | 0x250,
    0xcd, OBJ_SIZE_16x16 | 0x1e0, OBJ_SPRITE_OAM | 0x2d8,
    0xcd, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x10, OBJ_SPRITE_OAM | 0x2d8
};

static const u16 sGunshipPartOam_EntranceBackOpening_Frame0[OAM_DATA_SIZE(5)] = {
    0x5,
    OBJ_SHAPE_HORIZONTAL | 0xca, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x290,
    0xca, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x290,
    OBJ_SHAPE_HORIZONTAL | 0xcb, OBJ_SIZE_32x16 | 0x1f0, OBJ_SPRITE_OAM | 0x250,
    0xcd, OBJ_SIZE_16x16 | 0x1e0, OBJ_SPRITE_OAM | 0x2d8,
    0xcd, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x10, OBJ_SPRITE_OAM | 0x2d8
};

static const u16 sGunshipPartOam_EntranceBackOpening_Frame1[OAM_DATA_SIZE(5)] = {
    0x5,
    OBJ_SHAPE_HORIZONTAL | 0xc8, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x290,
    0xc8, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x290,
    OBJ_SHAPE_HORIZONTAL | 0xcb, OBJ_SIZE_32x16 | 0x1f0, OBJ_SPRITE_OAM | 0x250,
    0xcd, OBJ_SIZE_16x16 | 0x1e0, OBJ_SPRITE_OAM | 0x2d8,
    0xcd, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x10, OBJ_SPRITE_OAM | 0x2d8
};

static const u16 sGunshipPartOam_EntranceBackOpening_Frame2[OAM_DATA_SIZE(5)] = {
    0x5,
    OBJ_SHAPE_HORIZONTAL | 0xc6, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x290,
    0xc6, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x290,
    OBJ_SHAPE_HORIZONTAL | 0xcb, OBJ_SIZE_32x16 | 0x1f0, OBJ_SPRITE_OAM | 0x250,
    0xcd, OBJ_SIZE_16x16 | 0x1e0, OBJ_SPRITE_OAM | 0x2d8,
    0xcd, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x10, OBJ_SPRITE_OAM | 0x2d8
};

static const u16 sGunshipPartOam_EntranceBackOpening_Frame3[OAM_DATA_SIZE(5)] = {
    0x5,
    OBJ_SHAPE_HORIZONTAL | 0xc4, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x290,
    0xc4, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x290,
    OBJ_SHAPE_HORIZONTAL | 0xcb, OBJ_SIZE_32x16 | 0x1f0, OBJ_SPRITE_OAM | 0x250,
    0xcd, OBJ_SIZE_16x16 | 0x1e0, OBJ_SPRITE_OAM | 0x2d8,
    0xcd, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x10, OBJ_SPRITE_OAM | 0x2d8
};

static const u16 sGunshipPartOam_EntranceBackOpening_Frame4[OAM_DATA_SIZE(5)] = {
    0x5,
    OBJ_SHAPE_HORIZONTAL | 0xc5, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x290,
    0xc5, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x290,
    OBJ_SHAPE_HORIZONTAL | 0xcb, OBJ_SIZE_32x16 | 0x1f0, OBJ_SPRITE_OAM | 0x250,
    0xcd, OBJ_SIZE_16x16 | 0x1e0, OBJ_SPRITE_OAM | 0x2d8,
    0xcd, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x10, OBJ_SPRITE_OAM | 0x2d8
};

static const u16 sGunshipPartOam_EntranceBackOpening_Frame5[OAM_DATA_SIZE(5)] = {
    0x5,
    OBJ_SHAPE_HORIZONTAL | 0xc3, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x2d0,
    0xc3, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x2d0,
    OBJ_SHAPE_HORIZONTAL | 0xcb, OBJ_SIZE_32x16 | 0x1f0, OBJ_SPRITE_OAM | 0x250,
    0xcd, OBJ_SIZE_16x16 | 0x1e0, OBJ_SPRITE_OAM | 0x2d8,
    0xcd, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x10, OBJ_SPRITE_OAM | 0x2d8
};

static const u16 sGunshipPartOam_EntranceBackOpening_Frame6[OAM_DATA_SIZE(5)] = {
    0x5,
    OBJ_SHAPE_HORIZONTAL | 0xc3, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x214,
    0xc3, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x214,
    OBJ_SHAPE_HORIZONTAL | 0xcb, OBJ_SIZE_32x16 | 0x1f0, OBJ_SPRITE_OAM | 0x250,
    0xcd, OBJ_SIZE_16x16 | 0x1e0, OBJ_SPRITE_OAM | 0x2d8,
    0xcd, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x10, OBJ_SPRITE_OAM | 0x2d8
};

static const u16 sGunshipPartOam_EntranceBackOpening_Frame7[OAM_DATA_SIZE(5)] = {
    0x5,
    OBJ_SHAPE_HORIZONTAL | 0xc4, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x254,
    0xc4, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x254,
    OBJ_SHAPE_HORIZONTAL | 0xcb, OBJ_SIZE_32x16 | 0x1f0, OBJ_SPRITE_OAM | 0x250,
    0xcd, OBJ_SIZE_16x16 | 0x1e0, OBJ_SPRITE_OAM | 0x2d8,
    0xcd, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x10, OBJ_SPRITE_OAM | 0x2d8
};

static const u16 sGunshipPartOam_EntranceBackOpened_Frame0[OAM_DATA_SIZE(8)] = {
    0x8,
    OBJ_SHAPE_HORIZONTAL | 0xc7, 0x1ef, OBJ_SPRITE_OAM | 0x1218,
    0xc7, 0x1fc, OBJ_SPRITE_OAM | 0x1219,
    OBJ_SHAPE_HORIZONTAL | 0xc7, OBJ_X_FLIP | 0x1, OBJ_SPRITE_OAM | 0x1218,
    OBJ_SHAPE_HORIZONTAL | 0xc4, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x294,
    0xc4, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x294,
    OBJ_SHAPE_HORIZONTAL | 0xcb, OBJ_SIZE_32x16 | 0x1f0, OBJ_SPRITE_OAM | 0x250,
    0xcd, OBJ_SIZE_16x16 | 0x1e0, OBJ_SPRITE_OAM | 0x2d8,
    0xcd, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x10, OBJ_SPRITE_OAM | 0x2d8
};

static const u16 sGunshipPartOam_EntranceBackOpened_Frame1[OAM_DATA_SIZE(8)] = {
    0x8,
    OBJ_SHAPE_HORIZONTAL | 0xc7, 0x1ef, OBJ_SPRITE_OAM | 0x1238,
    0xc7, 0x1fc, OBJ_SPRITE_OAM | 0x1239,
    OBJ_SHAPE_HORIZONTAL | 0xc7, OBJ_X_FLIP | 0x1, OBJ_SPRITE_OAM | 0x1238,
    OBJ_SHAPE_HORIZONTAL | 0xc4, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x294,
    0xc4, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x294,
    OBJ_SHAPE_HORIZONTAL | 0xcb, OBJ_SIZE_32x16 | 0x1f0, OBJ_SPRITE_OAM | 0x250,
    0xcd, OBJ_SIZE_16x16 | 0x1e0, OBJ_SPRITE_OAM | 0x2d8,
    0xcd, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x10, OBJ_SPRITE_OAM | 0x2d8
};

static const u16 sGunshipPartOam_EntranceBackOpened_Frame2[OAM_DATA_SIZE(8)] = {
    0x8,
    OBJ_SHAPE_HORIZONTAL | 0xc7, 0x1ef, OBJ_SPRITE_OAM | 0x1258,
    0xc7, 0x1fc, OBJ_SPRITE_OAM | 0x1259,
    OBJ_SHAPE_HORIZONTAL | 0xc7, OBJ_X_FLIP | 0x1, OBJ_SPRITE_OAM | 0x1258,
    OBJ_SHAPE_HORIZONTAL | 0xc4, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x294,
    0xc4, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x294,
    OBJ_SHAPE_HORIZONTAL | 0xcb, OBJ_SIZE_32x16 | 0x1f0, OBJ_SPRITE_OAM | 0x250,
    0xcd, OBJ_SIZE_16x16 | 0x1e0, OBJ_SPRITE_OAM | 0x2d8,
    0xcd, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x10, OBJ_SPRITE_OAM | 0x2d8
};

static const u16 sGunshipPartOam_EntranceBackOpened_Frame3[OAM_DATA_SIZE(8)] = {
    0x8,
    OBJ_SHAPE_HORIZONTAL | 0xc7, 0x1ef, OBJ_SPRITE_OAM | 0x1278,
    0xc7, 0x1fc, OBJ_SPRITE_OAM | 0x1279,
    OBJ_SHAPE_HORIZONTAL | 0xc7, OBJ_X_FLIP | 0x1, OBJ_SPRITE_OAM | 0x1278,
    OBJ_SHAPE_HORIZONTAL | 0xc4, OBJ_SIZE_32x16 | 0x1e8, OBJ_SPRITE_OAM | 0x294,
    0xc4, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x8, OBJ_SPRITE_OAM | 0x294,
    OBJ_SHAPE_HORIZONTAL | 0xcb, OBJ_SIZE_32x16 | 0x1f0, OBJ_SPRITE_OAM | 0x250,
    0xcd, OBJ_SIZE_16x16 | 0x1e0, OBJ_SPRITE_OAM | 0x2d8,
    0xcd, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x10, OBJ_SPRITE_OAM | 0x2d8
};

static const u16 sGunshipPartOam_Platform_Frame0[OAM_DATA_SIZE(2)] = {
    0x2,
    OBJ_SHAPE_HORIZONTAL | 0xfe, 0x1f0, OBJ_SPRITE_OAM | 0x12d4,
    OBJ_SHAPE_HORIZONTAL | 0xfe, OBJ_X_FLIP | 0x0, OBJ_SPRITE_OAM | 0x12d4
};

static const u16 sGunshipPartOam_Platform_Frame1[OAM_DATA_SIZE(2)] = {
    0x2,
    OBJ_SHAPE_HORIZONTAL | 0xfe, 0x1f0, OBJ_SPRITE_OAM | 0x12f4,
    OBJ_SHAPE_HORIZONTAL | 0xfe, OBJ_X_FLIP | 0x0, OBJ_SPRITE_OAM | 0x12f4
};

static const u16 sGunshipPartOam_Platform_Frame2[OAM_DATA_SIZE(2)] = {
    0x2,
    OBJ_SHAPE_HORIZONTAL | 0xfe, 0x1f0, OBJ_SPRITE_OAM | 0x12d6,
    OBJ_SHAPE_HORIZONTAL | 0xfe, OBJ_X_FLIP | 0x0, OBJ_SPRITE_OAM | 0x12d6
};

static const u16 sGunshipPartOam_Platform_Frame3[OAM_DATA_SIZE(2)] = {
    0x2,
    OBJ_SHAPE_HORIZONTAL | 0xfe, 0x1f0, OBJ_SPRITE_OAM | 0x12f6,
    OBJ_SHAPE_HORIZONTAL | 0xfe, OBJ_X_FLIP | 0x0, OBJ_SPRITE_OAM | 0x12f6
};

static const u16 sGunshipOam_Flying_Frame0[OAM_DATA_SIZE(27)] = {
    0x1b,
    OBJ_SHAPE_VERTICAL | 0xf8, 0x18d, OBJ_SPRITE_OAM | 0x1300,
    0xf4, 0x195, OBJ_SPRITE_OAM | 0x1301,
    OBJ_SHAPE_HORIZONTAL | 0xef, OBJ_SIZE_32x8 | 0x19d, OBJ_SPRITE_OAM | 0x1302,
    0xef, 0x1bd, OBJ_SPRITE_OAM | 0x1306,
    OBJ_SHAPE_VERTICAL | 0xf8, OBJ_X_FLIP | 0x6b, OBJ_SPRITE_OAM | 0x1300,
    0xf4, OBJ_X_FLIP | 0x63, OBJ_SPRITE_OAM | 0x1301,
    OBJ_SHAPE_HORIZONTAL | 0xef, OBJ_X_FLIP | OBJ_SIZE_32x8 | 0x43, OBJ_SPRITE_OAM | 0x1302,
    0xef, OBJ_X_FLIP | 0x3b, OBJ_SPRITE_OAM | 0x1306,
    0xeb, OBJ_SIZE_16x16 | 0x1ca, OBJ_SPRITE_OAM | 0x1240,
    0xeb, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x26, OBJ_SPRITE_OAM | 0x1240,
    OBJ_SHAPE_HORIZONTAL | 0xdb, OBJ_SIZE_32x16 | 0x1d8, OBJ_SPRITE_OAM | 0x1200,
    0xdb, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x1204,
    OBJ_SHAPE_HORIZONTAL | 0xdb, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x8, OBJ_SPRITE_OAM | 0x1200,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_SIZE_32x16 | 0x180, OBJ_SPRITE_OAM | 0x280,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_SIZE_32x16 | 0x1a0, OBJ_SPRITE_OAM | 0x284,
    OBJ_SHAPE_HORIZONTAL | 0xd3, OBJ_SIZE_64x32 | 0x1c0, OBJ_SPRITE_OAM | 0x228,
    OBJ_SHAPE_HORIZONTAL | 0xf8, OBJ_SIZE_32x16 | 0x180, OBJ_SPRITE_OAM | 0x230e,
    OBJ_SHAPE_HORIZONTAL | 0xf8, OBJ_SIZE_32x16 | 0x1a0, OBJ_SPRITE_OAM | 0x2312,
    OBJ_SHAPE_HORIZONTAL | 0xf3, OBJ_SIZE_32x16 | 0x1c0, OBJ_SPRITE_OAM | 0x234e,
    OBJ_SHAPE_HORIZONTAL | 0xf3, OBJ_SIZE_32x16 | 0x1e0, OBJ_SPRITE_OAM | 0x2352,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x60, OBJ_SPRITE_OAM | 0x280,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x40, OBJ_SPRITE_OAM | 0x284,
    OBJ_SHAPE_HORIZONTAL | 0xd3, OBJ_X_FLIP | OBJ_SIZE_64x32 | 0x0, OBJ_SPRITE_OAM | 0x228,
    OBJ_SHAPE_HORIZONTAL | 0xf8, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x60, OBJ_SPRITE_OAM | 0x230e,
    OBJ_SHAPE_HORIZONTAL | 0xf8, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x40, OBJ_SPRITE_OAM | 0x2312,
    OBJ_SHAPE_HORIZONTAL | 0xf3, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x20, OBJ_SPRITE_OAM | 0x234e,
    OBJ_SHAPE_HORIZONTAL | 0xf3, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x0, OBJ_SPRITE_OAM | 0x2352
};

static const u16 sGunshipOam_Flying_Frame1[OAM_DATA_SIZE(27)] = {
    0x1b,
    OBJ_SHAPE_VERTICAL | 0xf8, 0x18d, OBJ_SPRITE_OAM | 0x1340,
    0xf4, 0x195, OBJ_SPRITE_OAM | 0x1341,
    OBJ_SHAPE_HORIZONTAL | 0xef, OBJ_SIZE_32x8 | 0x19d, OBJ_SPRITE_OAM | 0x1342,
    0xef, 0x1bd, OBJ_SPRITE_OAM | 0x1346,
    OBJ_SHAPE_VERTICAL | 0xf8, OBJ_X_FLIP | 0x6b, OBJ_SPRITE_OAM | 0x1340,
    0xf4, OBJ_X_FLIP | 0x63, OBJ_SPRITE_OAM | 0x1341,
    OBJ_SHAPE_HORIZONTAL | 0xef, OBJ_X_FLIP | OBJ_SIZE_32x8 | 0x43, OBJ_SPRITE_OAM | 0x1342,
    0xef, OBJ_X_FLIP | 0x3b, OBJ_SPRITE_OAM | 0x1346,
    0xeb, OBJ_SIZE_16x16 | 0x1ca, OBJ_SPRITE_OAM | 0x1242,
    0xeb, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x26, OBJ_SPRITE_OAM | 0x1242,
    OBJ_SHAPE_HORIZONTAL | 0xdb, OBJ_SIZE_32x16 | 0x1d8, OBJ_SPRITE_OAM | 0x1200,
    0xdb, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x1204,
    OBJ_SHAPE_HORIZONTAL | 0xdb, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x8, OBJ_SPRITE_OAM | 0x1200,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_SIZE_32x16 | 0x180, OBJ_SPRITE_OAM | 0x280,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_SIZE_32x16 | 0x1a0, OBJ_SPRITE_OAM | 0x284,
    OBJ_SHAPE_HORIZONTAL | 0xd3, OBJ_SIZE_64x32 | 0x1c0, OBJ_SPRITE_OAM | 0x228,
    OBJ_SHAPE_HORIZONTAL | 0xf8, OBJ_SIZE_32x16 | 0x180, OBJ_SPRITE_OAM | 0x230e,
    OBJ_SHAPE_HORIZONTAL | 0xf8, OBJ_SIZE_32x16 | 0x1a0, OBJ_SPRITE_OAM | 0x2312,
    OBJ_SHAPE_HORIZONTAL | 0xf3, OBJ_SIZE_32x16 | 0x1c0, OBJ_SPRITE_OAM | 0x234e,
    OBJ_SHAPE_HORIZONTAL | 0xf3, OBJ_SIZE_32x16 | 0x1e0, OBJ_SPRITE_OAM | 0x2352,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x60, OBJ_SPRITE_OAM | 0x280,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x40, OBJ_SPRITE_OAM | 0x284,
    OBJ_SHAPE_HORIZONTAL | 0xd3, OBJ_X_FLIP | OBJ_SIZE_64x32 | 0x0, OBJ_SPRITE_OAM | 0x228,
    OBJ_SHAPE_HORIZONTAL | 0xf8, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x60, OBJ_SPRITE_OAM | 0x230e,
    OBJ_SHAPE_HORIZONTAL | 0xf8, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x40, OBJ_SPRITE_OAM | 0x2312,
    OBJ_SHAPE_HORIZONTAL | 0xf3, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x20, OBJ_SPRITE_OAM | 0x234e,
    OBJ_SHAPE_HORIZONTAL | 0xf3, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x0, OBJ_SPRITE_OAM | 0x2352
};

static const u16 sGunshipOam_Flying_Frame2[OAM_DATA_SIZE(27)] = {
    0x1b,
    OBJ_SHAPE_VERTICAL | 0xf8, 0x18d, OBJ_SPRITE_OAM | 0x1307,
    0xf4, 0x195, OBJ_SPRITE_OAM | 0x1308,
    OBJ_SHAPE_HORIZONTAL | 0xef, OBJ_SIZE_32x8 | 0x19d, OBJ_SPRITE_OAM | 0x1309,
    0xef, 0x1bd, OBJ_SPRITE_OAM | 0x130d,
    OBJ_SHAPE_VERTICAL | 0xf8, OBJ_X_FLIP | 0x6b, OBJ_SPRITE_OAM | 0x1307,
    0xf4, OBJ_X_FLIP | 0x63, OBJ_SPRITE_OAM | 0x1308,
    OBJ_SHAPE_HORIZONTAL | 0xef, OBJ_X_FLIP | OBJ_SIZE_32x8 | 0x43, OBJ_SPRITE_OAM | 0x1309,
    0xef, OBJ_X_FLIP | 0x3b, OBJ_SPRITE_OAM | 0x130d,
    0xeb, OBJ_SIZE_16x16 | 0x1ca, OBJ_SPRITE_OAM | 0x1244,
    0xeb, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x26, OBJ_SPRITE_OAM | 0x1244,
    OBJ_SHAPE_HORIZONTAL | 0xdb, OBJ_SIZE_32x16 | 0x1d8, OBJ_SPRITE_OAM | 0x1200,
    0xdb, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x1204,
    OBJ_SHAPE_HORIZONTAL | 0xdb, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x8, OBJ_SPRITE_OAM | 0x1200,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_SIZE_32x16 | 0x180, OBJ_SPRITE_OAM | 0x280,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_SIZE_32x16 | 0x1a0, OBJ_SPRITE_OAM | 0x284,
    OBJ_SHAPE_HORIZONTAL | 0xd3, OBJ_SIZE_64x32 | 0x1c0, OBJ_SPRITE_OAM | 0x228,
    OBJ_SHAPE_HORIZONTAL | 0xf8, OBJ_SIZE_32x16 | 0x180, OBJ_SPRITE_OAM | 0x230e,
    OBJ_SHAPE_HORIZONTAL | 0xf8, OBJ_SIZE_32x16 | 0x1a0, OBJ_SPRITE_OAM | 0x2312,
    OBJ_SHAPE_HORIZONTAL | 0xf3, OBJ_SIZE_32x16 | 0x1c0, OBJ_SPRITE_OAM | 0x234e,
    OBJ_SHAPE_HORIZONTAL | 0xf3, OBJ_SIZE_32x16 | 0x1e0, OBJ_SPRITE_OAM | 0x2352,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x60, OBJ_SPRITE_OAM | 0x280,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x40, OBJ_SPRITE_OAM | 0x284,
    OBJ_SHAPE_HORIZONTAL | 0xd3, OBJ_X_FLIP | OBJ_SIZE_64x32 | 0x0, OBJ_SPRITE_OAM | 0x228,
    OBJ_SHAPE_HORIZONTAL | 0xf8, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x60, OBJ_SPRITE_OAM | 0x230e,
    OBJ_SHAPE_HORIZONTAL | 0xf8, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x40, OBJ_SPRITE_OAM | 0x2312,
    OBJ_SHAPE_HORIZONTAL | 0xf3, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x20, OBJ_SPRITE_OAM | 0x234e,
    OBJ_SHAPE_HORIZONTAL | 0xf3, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x0, OBJ_SPRITE_OAM | 0x2352
};

static const u16 sGunshipOam_Flying_Frame3[OAM_DATA_SIZE(27)] = {
    0x1b,
    OBJ_SHAPE_VERTICAL | 0xf8, 0x18d, OBJ_SPRITE_OAM | 0x1347,
    0xf4, 0x195, OBJ_SPRITE_OAM | 0x1348,
    OBJ_SHAPE_HORIZONTAL | 0xef, OBJ_SIZE_32x8 | 0x19d, OBJ_SPRITE_OAM | 0x1349,
    0xef, 0x1bd, OBJ_SPRITE_OAM | 0x134d,
    OBJ_SHAPE_VERTICAL | 0xf8, OBJ_X_FLIP | 0x6b, OBJ_SPRITE_OAM | 0x1347,
    0xf4, OBJ_X_FLIP | 0x63, OBJ_SPRITE_OAM | 0x1348,
    OBJ_SHAPE_HORIZONTAL | 0xef, OBJ_X_FLIP | OBJ_SIZE_32x8 | 0x43, OBJ_SPRITE_OAM | 0x1349,
    0xef, OBJ_X_FLIP | 0x3b, OBJ_SPRITE_OAM | 0x134d,
    0xeb, OBJ_SIZE_16x16 | 0x1ca, OBJ_SPRITE_OAM | 0x1246,
    0xeb, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x26, OBJ_SPRITE_OAM | 0x1246,
    OBJ_SHAPE_HORIZONTAL | 0xdb, OBJ_SIZE_32x16 | 0x1d8, OBJ_SPRITE_OAM | 0x1200,
    0xdb, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x1204,
    OBJ_SHAPE_HORIZONTAL | 0xdb, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x8, OBJ_SPRITE_OAM | 0x1200,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_SIZE_32x16 | 0x180, OBJ_SPRITE_OAM | 0x280,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_SIZE_32x16 | 0x1a0, OBJ_SPRITE_OAM | 0x284,
    OBJ_SHAPE_HORIZONTAL | 0xd3, OBJ_SIZE_64x32 | 0x1c0, OBJ_SPRITE_OAM | 0x228,
    OBJ_SHAPE_HORIZONTAL | 0xf8, OBJ_SIZE_32x16 | 0x180, OBJ_SPRITE_OAM | 0x230e,
    OBJ_SHAPE_HORIZONTAL | 0xf8, OBJ_SIZE_32x16 | 0x1a0, OBJ_SPRITE_OAM | 0x2312,
    OBJ_SHAPE_HORIZONTAL | 0xf3, OBJ_SIZE_32x16 | 0x1c0, OBJ_SPRITE_OAM | 0x234e,
    OBJ_SHAPE_HORIZONTAL | 0xf3, OBJ_SIZE_32x16 | 0x1e0, OBJ_SPRITE_OAM | 0x2352,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x60, OBJ_SPRITE_OAM | 0x280,
    OBJ_SHAPE_HORIZONTAL | 0xe8, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x40, OBJ_SPRITE_OAM | 0x284,
    OBJ_SHAPE_HORIZONTAL | 0xd3, OBJ_X_FLIP | OBJ_SIZE_64x32 | 0x0, OBJ_SPRITE_OAM | 0x228,
    OBJ_SHAPE_HORIZONTAL | 0xf8, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x60, OBJ_SPRITE_OAM | 0x230e,
    OBJ_SHAPE_HORIZONTAL | 0xf8, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x40, OBJ_SPRITE_OAM | 0x2312,
    OBJ_SHAPE_HORIZONTAL | 0xf3, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x20, OBJ_SPRITE_OAM | 0x234e,
    OBJ_SHAPE_HORIZONTAL | 0xf3, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x0, OBJ_SPRITE_OAM | 0x2352
};

static const u16 sGunshipPartOam_FlamesHorizontal_Frame0[OAM_DATA_SIZE(8)] = {
    0x8,
    OBJ_SHAPE_HORIZONTAL | 0xf4, OBJ_SIZE_32x16 | 0x1a8, OBJ_SPRITE_OAM | 0x1356,
    0xf4, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x1c8, OBJ_SPRITE_OAM | 0x1356,
    OBJ_SHAPE_HORIZONTAL | 0x4, OBJ_Y_FLIP | OBJ_SIZE_32x8 | 0x1a8, OBJ_SPRITE_OAM | 0x1356,
    OBJ_SHAPE_HORIZONTAL | 0x4, OBJ_X_FLIP | OBJ_Y_FLIP | 0x1c8, OBJ_SPRITE_OAM | 0x1356,
    OBJ_SHAPE_HORIZONTAL | 0xf4, OBJ_SIZE_32x16 | 0x28, OBJ_SPRITE_OAM | 0x1356,
    0xf4, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x48, OBJ_SPRITE_OAM | 0x1356,
    OBJ_SHAPE_HORIZONTAL | 0x4, OBJ_Y_FLIP | OBJ_SIZE_32x8 | 0x28, OBJ_SPRITE_OAM | 0x1356,
    OBJ_SHAPE_HORIZONTAL | 0x4, OBJ_X_FLIP | OBJ_Y_FLIP | 0x48, OBJ_SPRITE_OAM | 0x1356
};

static const u16 sGunshipPartOam_FlamesHorizontal_Frame1[OAM_DATA_SIZE(8)] = {
    0x8,
    OBJ_SHAPE_HORIZONTAL | 0xf4, OBJ_SIZE_32x16 | 0x1a0, OBJ_SPRITE_OAM | 0x1316,
    OBJ_SHAPE_HORIZONTAL | 0x4, OBJ_Y_FLIP | OBJ_SIZE_32x8 | 0x1a0, OBJ_SPRITE_OAM | 0x1316,
    OBJ_SHAPE_HORIZONTAL | 0xf4, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x1c0, OBJ_SPRITE_OAM | 0x1316,
    OBJ_SHAPE_HORIZONTAL | 0x4, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_32x8 | 0x1c0, OBJ_SPRITE_OAM | 0x1316,
    OBJ_SHAPE_HORIZONTAL | 0xf4, OBJ_SIZE_32x16 | 0x20, OBJ_SPRITE_OAM | 0x1316,
    OBJ_SHAPE_HORIZONTAL | 0x4, OBJ_Y_FLIP | OBJ_SIZE_32x8 | 0x20, OBJ_SPRITE_OAM | 0x1316,
    OBJ_SHAPE_HORIZONTAL | 0xf4, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x40, OBJ_SPRITE_OAM | 0x1316,
    OBJ_SHAPE_HORIZONTAL | 0x4, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_32x8 | 0x40, OBJ_SPRITE_OAM | 0x1316
};

static const u16 sGunshipPartOam_FlamesHorizontal_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, OBJ_SPRITE_OAM | 0x280
};

static const u16 sGunshipPartOam_FlamesVertical_Frame0[OAM_DATA_SIZE(4)] = {
    0x4,
    OBJ_SHAPE_HORIZONTAL | 0xf8, OBJ_SIZE_32x16 | 0x1a2, OBJ_SPRITE_OAM | 0x12da,
    OBJ_SHAPE_HORIZONTAL | 0xf4, OBJ_SIZE_32x16 | 0x1be, OBJ_SPRITE_OAM | 0x12da,
    OBJ_SHAPE_HORIZONTAL | 0xf8, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x3e, OBJ_SPRITE_OAM | 0x12da,
    OBJ_SHAPE_HORIZONTAL | 0xf4, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x22, OBJ_SPRITE_OAM | 0x12da
};

static const u16 sGunshipPartOam_FlamesVertical_Frame1[OAM_DATA_SIZE(8)] = {
    0x8,
    OBJ_SHAPE_VERTICAL | 0xfc, OBJ_SIZE_16x32 | 0x1a6, OBJ_SPRITE_OAM | 0x131a,
    OBJ_SHAPE_VERTICAL | 0xfc, OBJ_X_FLIP | OBJ_SIZE_8x32 | 0x1b6, OBJ_SPRITE_OAM | 0x131a,
    OBJ_SHAPE_VERTICAL | 0xf8, OBJ_SIZE_16x32 | 0x1c2, OBJ_SPRITE_OAM | 0x131a,
    OBJ_SHAPE_VERTICAL | 0xf8, OBJ_X_FLIP | OBJ_SIZE_8x32 | 0x1d2, OBJ_SPRITE_OAM | 0x131a,
    OBJ_SHAPE_VERTICAL | 0xfc, OBJ_X_FLIP | OBJ_SIZE_16x32 | 0x4a, OBJ_SPRITE_OAM | 0x131a,
    OBJ_SHAPE_VERTICAL | 0xfc, OBJ_SIZE_8x32 | 0x42, OBJ_SPRITE_OAM | 0x131a,
    OBJ_SHAPE_VERTICAL | 0xf8, OBJ_X_FLIP | OBJ_SIZE_16x32 | 0x2e, OBJ_SPRITE_OAM | 0x131a,
    OBJ_SHAPE_VERTICAL | 0xf8, OBJ_SIZE_8x32 | 0x26, OBJ_SPRITE_OAM | 0x131a
};

static const u16 sGunshipPartOam_FlamesVertical_Frame2[OAM_DATA_SIZE(8)] = {
    0x8,
    OBJ_SHAPE_VERTICAL | 0xf0, OBJ_SIZE_16x32 | 0x1aa, OBJ_SPRITE_OAM | 0x129e,
    OBJ_SHAPE_VERTICAL | 0x10, OBJ_SIZE_16x32 | 0x1aa, OBJ_SPRITE_OAM | 0x131e,
    OBJ_SHAPE_VERTICAL | 0xec, OBJ_SIZE_16x32 | 0x1c6, OBJ_SPRITE_OAM | 0x129e,
    OBJ_SHAPE_VERTICAL | 0xc, OBJ_SIZE_16x32 | 0x1c6, OBJ_SPRITE_OAM | 0x131e,
    OBJ_SHAPE_VERTICAL | 0xf0, OBJ_X_FLIP | OBJ_SIZE_16x32 | 0x46, OBJ_SPRITE_OAM | 0x129e,
    OBJ_SHAPE_VERTICAL | 0x10, OBJ_X_FLIP | OBJ_SIZE_16x32 | 0x46, OBJ_SPRITE_OAM | 0x131e,
    OBJ_SHAPE_VERTICAL | 0xec, OBJ_X_FLIP | OBJ_SIZE_16x32 | 0x2a, OBJ_SPRITE_OAM | 0x129e,
    OBJ_SHAPE_VERTICAL | 0xc, OBJ_X_FLIP | OBJ_SIZE_16x32 | 0x2a, OBJ_SPRITE_OAM | 0x131e
};

const struct FrameData sGunshipOam_Idle[7] = {
    [0] = {
        .pFrame = sGunshipOam_Idle_Frame0,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [1] = {
        .pFrame = sGunshipOam_Idle_Frame1,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [2] = {
        .pFrame = sGunshipOam_Idle_Frame2,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [3] = {
        .pFrame = sGunshipOam_Idle_Frame3,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [4] = {
        .pFrame = sGunshipOam_Idle_Frame2,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [5] = {
        .pFrame = sGunshipOam_Idle_Frame1,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGunshipOam_Refilling[7] = {
    [0] = {
        .pFrame = sGunshipOam_Idle_Frame0,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [1] = {
        .pFrame = sGunshipOam_Idle_Frame1,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [2] = {
        .pFrame = sGunshipOam_Idle_Frame2,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [3] = {
        .pFrame = sGunshipOam_Idle_Frame3,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [4] = {
        .pFrame = sGunshipOam_Idle_Frame2,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [5] = {
        .pFrame = sGunshipOam_Idle_Frame1,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGunshipPartOam_EntranceFrontClosed[2] = {
    [0] = {
        .pFrame = sGunshipPartOam_EntranceFrontClosed_Frame0,
        .timer = UCHAR_MAX
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGunshipPartOam_EntranceFrontOpening[5] = {
    [0] = {
        .pFrame = sGunshipPartOam_EntranceFrontOpening_Frame0,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [1] = {
        .pFrame = sGunshipPartOam_EntranceFrontOpening_Frame1,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [2] = {
        .pFrame = sGunshipPartOam_EntranceFrontOpening_Frame2,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [3] = {
        .pFrame = sGunshipPartOam_EntranceFrontOpening_Frame3,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGunshipPartOam_EntranceFrontOpened[7] = {
    [0] = {
        .pFrame = sGunshipPartOam_EntranceFrontOpened_Frame0,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [1] = {
        .pFrame = sGunshipPartOam_EntranceFrontOpened_Frame1,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [2] = {
        .pFrame = sGunshipPartOam_EntranceFrontOpened_Frame2,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [3] = {
        .pFrame = sGunshipPartOam_EntranceFrontOpened_Frame3,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [4] = {
        .pFrame = sGunshipPartOam_EntranceFrontOpened_Frame2,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [5] = {
        .pFrame = sGunshipPartOam_EntranceFrontOpened_Frame1,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGunshipPartOam_EntranceFrontClosing[6] = {
    [0] = {
        .pFrame = sGunshipPartOam_EntranceFrontOpened_Frame0,
        .timer = CONVERT_SECONDS(7.f / 15)
    },
    [1] = {
        .pFrame = sGunshipPartOam_EntranceFrontOpening_Frame3,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [2] = {
        .pFrame = sGunshipPartOam_EntranceFrontOpening_Frame2,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [3] = {
        .pFrame = sGunshipPartOam_EntranceFrontOpening_Frame1,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [4] = {
        .pFrame = sGunshipPartOam_EntranceFrontOpening_Frame0,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [5] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGunshipPartOam_EntranceBackClosed[2] = {
    [0] = {
        .pFrame = sGunshipPartOam_EntranceBackCLosed_Frame0,
        .timer = UCHAR_MAX
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGunshipPartOam_EntranceBackOpening[9] = {
    [0] = {
        .pFrame = sGunshipPartOam_EntranceBackOpening_Frame0,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [1] = {
        .pFrame = sGunshipPartOam_EntranceBackOpening_Frame1,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [2] = {
        .pFrame = sGunshipPartOam_EntranceBackOpening_Frame2,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [3] = {
        .pFrame = sGunshipPartOam_EntranceBackOpening_Frame3,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [4] = {
        .pFrame = sGunshipPartOam_EntranceBackOpening_Frame4,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [5] = {
        .pFrame = sGunshipPartOam_EntranceBackOpening_Frame5,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [6] = {
        .pFrame = sGunshipPartOam_EntranceBackOpening_Frame6,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [7] = {
        .pFrame = sGunshipPartOam_EntranceBackOpening_Frame7,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [8] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGunshipPartOam_EntranceBackOpened[7] = {
    [0] = {
        .pFrame = sGunshipPartOam_EntranceBackOpened_Frame0,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [1] = {
        .pFrame = sGunshipPartOam_EntranceBackOpened_Frame1,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [2] = {
        .pFrame = sGunshipPartOam_EntranceBackOpened_Frame2,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [3] = {
        .pFrame = sGunshipPartOam_EntranceBackOpened_Frame3,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [4] = {
        .pFrame = sGunshipPartOam_EntranceBackOpened_Frame2,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [5] = {
        .pFrame = sGunshipPartOam_EntranceBackOpened_Frame1,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGunshipPartOam_EntranceBackClosing[9] = {
    [0] = {
        .pFrame = sGunshipPartOam_EntranceBackOpening_Frame7,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [1] = {
        .pFrame = sGunshipPartOam_EntranceBackOpening_Frame6,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [2] = {
        .pFrame = sGunshipPartOam_EntranceBackOpening_Frame5,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [3] = {
        .pFrame = sGunshipPartOam_EntranceBackOpening_Frame4,
        .timer = CONVERT_SECONDS(4.f / 15)
    },
    [4] = {
        .pFrame = sGunshipPartOam_EntranceBackOpening_Frame3,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [5] = {
        .pFrame = sGunshipPartOam_EntranceBackOpening_Frame2,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [6] = {
        .pFrame = sGunshipPartOam_EntranceBackOpening_Frame1,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [7] = {
        .pFrame = sGunshipPartOam_EntranceBackOpening_Frame0,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [8] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGunshipPartOam_Platform[5] = {
    [0] = {
        .pFrame = sGunshipPartOam_Platform_Frame0,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [1] = {
        .pFrame = sGunshipPartOam_Platform_Frame1,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [2] = {
        .pFrame = sGunshipPartOam_Platform_Frame2,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [3] = {
        .pFrame = sGunshipPartOam_Platform_Frame3,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGunshipOam_Flying[7] = {
    [0] = {
        .pFrame = sGunshipOam_Flying_Frame0,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [1] = {
        .pFrame = sGunshipOam_Flying_Frame1,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [2] = {
        .pFrame = sGunshipOam_Flying_Frame2,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [3] = {
        .pFrame = sGunshipOam_Flying_Frame3,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [4] = {
        .pFrame = sGunshipOam_Flying_Frame2,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [5] = {
        .pFrame = sGunshipOam_Flying_Frame1,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGunshipPartOam_FlamesHorizontal[4] = {
    [0] = {
        .pFrame = sGunshipPartOam_FlamesHorizontal_Frame0,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [1] = {
        .pFrame = sGunshipPartOam_FlamesHorizontal_Frame1,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [2] = {
        .pFrame = sGunshipPartOam_FlamesHorizontal_Frame2,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGunshipPartOam_FlamesVertical[4] = {
    [0] = {
        .pFrame = sGunshipPartOam_FlamesVertical_Frame0,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [1] = {
        .pFrame = sGunshipPartOam_FlamesVertical_Frame1,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [2] = {
        .pFrame = sGunshipPartOam_FlamesVertical_Frame2,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [3] = FRAME_DATA_TERMINATOR
};
