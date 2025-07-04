#include "data/sprites/atomic.h"

#include "macros.h"

const s16 sAtomicIdleYMovement[65] = {
    0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 2,
    2, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, -1, -1, -2,
    -2, -1, -1, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, 0, 0, 0,
    SHORT_MAX
};

const s16 sAtomicIdleXMovement[81] = {
    0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 2, 2,
    2, 2, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, -1, -1, -1, -1, -1, -2, -2,
    -2, -2, -1, -1, -1, -1, -1, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, 0, 0, 0,
    SHORT_MAX
};

const u32 sAtomicGfx[752] = INCBIN_U32("data/sprites/Atomic.gfx.lz");
const u16 sAtomicPal[64] = INCBIN_U16("data/sprites/Atomic.pal");

static const u16 sAtomicOam_Idle_Frame0[OAM_DATA_SIZE(4)] = {
    0x4,
    0xf4, 0x1fc, OBJ_SPRITE_OAM | 0x292,
    0xfc, 0x4, OBJ_SPRITE_OAM | 0x291,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x21a,
    0x1, 0x1f7, OBJ_SPRITE_OAM | 0x293
};

static const u16 sAtomicOam_Idle_Frame1[OAM_DATA_SIZE(3)] = {
    0x3,
    0xf8, 0x1f6, OBJ_SPRITE_OAM | 0x293,
    0x0, 0x1, OBJ_SPRITE_OAM | 0x293,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x21c
};

static const u16 sAtomicOam_Idle_Frame2[OAM_DATA_SIZE(4)] = {
    0x4,
    0xfc, 0x1f4, OBJ_SPRITE_OAM | 0x291,
    0x3, 0x1fe, OBJ_SPRITE_OAM | 0x292,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x21e,
    0xf7, OBJ_X_FLIP | OBJ_Y_FLIP | 0x1, OBJ_SPRITE_OAM | 0x293
};

static const u16 sAtomicOam_Idle_Frame3[OAM_DATA_SIZE(4)] = {
    0x4,
    0xf8, 0x0, OBJ_SPRITE_OAM | 0x293,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x21c,
    0xfb, 0x1f5, OBJ_SPRITE_OAM | 0x291,
    0x3, 0x1fc, OBJ_SPRITE_OAM | 0x292
};

static const u16 sAtomicOam_Idle_Frame4[OAM_DATA_SIZE(4)] = {
    0x4,
    0xfd, 0x1fe, OBJ_SPRITE_OAM | 0x293,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x21a,
    0xf8, 0x1f6, OBJ_SPRITE_OAM | 0x291,
    0x3, 0x1fa, OBJ_SPRITE_OAM | 0x292
};

static const u16 sAtomicOam_Idle_Frame5[OAM_DATA_SIZE(4)] = {
    0x4,
    0x1, OBJ_X_FLIP | 0x1, OBJ_SPRITE_OAM | 0x293,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x218,
    0xf5, OBJ_X_FLIP | 0x1f9, OBJ_SPRITE_OAM | 0x292,
    0xff, OBJ_X_FLIP | 0x1f6, OBJ_SPRITE_OAM | 0x291
};

static const u16 sAtomicOam_Idle_Frame6[OAM_DATA_SIZE(4)] = {
    0x4,
    0xf4, OBJ_X_FLIP | 0x1fc, OBJ_SPRITE_OAM | 0x292,
    0xfc, OBJ_X_FLIP | 0x1f4, OBJ_SPRITE_OAM | 0x291,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x21a,
    0x1, OBJ_X_FLIP | 0x1, OBJ_SPRITE_OAM | 0x293
};

static const u16 sAtomicOam_Idle_Frame7[OAM_DATA_SIZE(3)] = {
    0x3,
    0xf8, OBJ_X_FLIP | 0x2, OBJ_SPRITE_OAM | 0x293,
    0x0, OBJ_X_FLIP | 0x1f7, OBJ_SPRITE_OAM | 0x293,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x21c
};

static const u16 sAtomicOam_Idle_Frame8[OAM_DATA_SIZE(4)] = {
    0x4,
    0xfc, OBJ_X_FLIP | 0x4, OBJ_SPRITE_OAM | 0x291,
    0x3, OBJ_X_FLIP | 0x1fa, OBJ_SPRITE_OAM | 0x292,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x21e,
    0xf7, OBJ_Y_FLIP | 0x1f7, OBJ_SPRITE_OAM | 0x293
};

static const u16 sAtomicOam_Idle_Frame9[OAM_DATA_SIZE(4)] = {
    0x4,
    0xf8, OBJ_X_FLIP | 0x1f8, OBJ_SPRITE_OAM | 0x293,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x21c,
    0xfb, OBJ_X_FLIP | 0x3, OBJ_SPRITE_OAM | 0x291,
    0x3, OBJ_X_FLIP | 0x1fc, OBJ_SPRITE_OAM | 0x292
};

static const u16 sAtomicOam_Idle_Frame10[OAM_DATA_SIZE(4)] = {
    0x4,
    0xfd, OBJ_X_FLIP | 0x1fa, OBJ_SPRITE_OAM | 0x293,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x21a,
    0xf8, OBJ_X_FLIP | 0x2, OBJ_SPRITE_OAM | 0x291,
    0x3, OBJ_X_FLIP | 0x1fe, OBJ_SPRITE_OAM | 0x292
};

static const u16 sAtomicOam_Idle_Frame11[OAM_DATA_SIZE(4)] = {
    0x4,
    0x1, 0x1f7, OBJ_SPRITE_OAM | 0x293,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x218,
    0xf5, 0x1ff, OBJ_SPRITE_OAM | 0x292,
    0xff, 0x2, OBJ_SPRITE_OAM | 0x291
};

static const u16 sAtomicElectricityOam_MovingVertical_Frame0[OAM_DATA_SIZE(2)] = {
    0x2,
    OBJ_SHAPE_VERTICAL | 0x0, OBJ_SIZE_16x32 | 0x1f8, OBJ_SPRITE_OAM | 0x1215,
    OBJ_SHAPE_HORIZONTAL | 0x20, 0x1f8, OBJ_SPRITE_OAM | 0x1295
};

static const u16 sAtomicElectricityOam_MovingVertical_Frame1[OAM_DATA_SIZE(2)] = {
    0x2,
    OBJ_SHAPE_VERTICAL | 0x0, OBJ_SIZE_8x32 | 0x1fc, OBJ_SPRITE_OAM | 0x1217,
    0x20, 0x1fc, OBJ_SPRITE_OAM | 0x1297
};

static const u16 sAtomicElectricityOam_MovingVertical_Frame3[OAM_DATA_SIZE(2)] = {
    0x2,
    OBJ_SHAPE_VERTICAL | 0x8, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_16x32 | 0x1fb, OBJ_SPRITE_OAM | 0x1215,
    OBJ_SHAPE_HORIZONTAL | 0x0, OBJ_X_FLIP | OBJ_Y_FLIP | 0x1fb, OBJ_SPRITE_OAM | 0x1295
};

static const u16 sAtomicElectricityOam_MovingVertical_Frame5[OAM_DATA_SIZE(2)] = {
    0x2,
    OBJ_SHAPE_VERTICAL | 0x8, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_8x32 | 0x1fc, OBJ_SPRITE_OAM | 0x1217,
    0x0, OBJ_X_FLIP | OBJ_Y_FLIP | 0x1fc, OBJ_SPRITE_OAM | 0x1297
};

static const u16 sAtomicElectricityOam_MovingVertical_Frame6[OAM_DATA_SIZE(2)] = {
    0x2,
    OBJ_SHAPE_VERTICAL | 0x0, OBJ_X_FLIP | OBJ_SIZE_16x32 | 0x1f8, OBJ_SPRITE_OAM | 0x1215,
    OBJ_SHAPE_HORIZONTAL | 0x20, OBJ_X_FLIP | 0x1f8, OBJ_SPRITE_OAM | 0x1295
};

static const u16 sAtomicElectricityOam_MovingVertical_Frame7[OAM_DATA_SIZE(2)] = {
    0x2,
    OBJ_SHAPE_VERTICAL | 0x0, OBJ_X_FLIP | OBJ_SIZE_8x32 | 0x1fc, OBJ_SPRITE_OAM | 0x1217,
    0x20, OBJ_X_FLIP | 0x1fc, OBJ_SPRITE_OAM | 0x1297
};

static const u16 sAtomicElectricityOam_MovingVertical_Frame9[OAM_DATA_SIZE(2)] = {
    0x2,
    OBJ_SHAPE_VERTICAL | 0x8, OBJ_Y_FLIP | OBJ_SIZE_16x32 | 0x1f8, OBJ_SPRITE_OAM | 0x1215,
    OBJ_SHAPE_HORIZONTAL | 0x0, OBJ_Y_FLIP | 0x1f8, OBJ_SPRITE_OAM | 0x1295
};

static const u16 sAtomicElectricityOam_MovingVertical_Frame10[OAM_DATA_SIZE(2)] = {
    0x2,
    OBJ_SHAPE_VERTICAL | 0x8, OBJ_Y_FLIP | OBJ_SIZE_8x32 | 0x1fc, OBJ_SPRITE_OAM | 0x1217,
    0x0, OBJ_Y_FLIP | 0x1fc, OBJ_SPRITE_OAM | 0x1297
};

static const u16 sAtomicElectricityOam_MovingVertical_Unused_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    OBJ_SHAPE_VERTICAL | 0x10, OBJ_SIZE_8x32 | 0x1fc, OBJ_SPRITE_OAM | 0x1258
};

static const u16 sAtomicElectricityOam_MovingVertical_Unused_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    OBJ_SHAPE_VERTICAL | 0x8, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_8x32 | 0x1fc, OBJ_SPRITE_OAM | 0x1258
};

static const u16 sAtomicElectricityOam_MovingVertical_Unused_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    OBJ_SHAPE_VERTICAL | 0x10, OBJ_SIZE_8x32 | 0x1fc, OBJ_SPRITE_OAM | 0x1279
};

static const u16 sAtomicElectricityOam_MovingVertical_Unused_Frame3[OAM_DATA_SIZE(1)] = {
    0x1,
    OBJ_SHAPE_VERTICAL | 0x8, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_8x32 | 0x1fc, OBJ_SPRITE_OAM | 0x1279
};

static const u16 sAtomicElectricityOam_MovingDiagonal_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    0x0, OBJ_SIZE_32x32 | 0x1e0, OBJ_SPRITE_OAM | 0x1280
};

static const u16 sAtomicElectricityOam_MovingDiagonal_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    0x0, OBJ_SIZE_32x32 | 0x1e0, OBJ_SPRITE_OAM | 0x1284
};

static const u16 sAtomicElectricityOam_MovingDiagonal_Frame3[OAM_DATA_SIZE(1)] = {
    0x1,
    0x0, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_32x32 | 0x1e0, OBJ_SPRITE_OAM | 0x1280
};

static const u16 sAtomicElectricityOam_MovingDiagonal_Frame5[OAM_DATA_SIZE(1)] = {
    0x1,
    0x0, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_32x32 | 0x1e0, OBJ_SPRITE_OAM | 0x1284
};

static const u16 sAtomicElectricityOam_MovingDiagonal_Frame6[OAM_DATA_SIZE(1)] = {
    0x1,
    0x0, OBJ_SIZE_32x32 | 0x1e0, OBJ_SPRITE_OAM | 0x1288
};

static const u16 sAtomicElectricityOam_MovingDiagonal_Frame7[OAM_DATA_SIZE(1)] = {
    0x1,
    0x0, OBJ_SIZE_32x32 | 0x1e0, OBJ_SPRITE_OAM | 0x128c
};

static const u16 sAtomicElectricityOam_MovingDiagonal_Frame9[OAM_DATA_SIZE(1)] = {
    0x1,
    0x0, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_32x32 | 0x1e0, OBJ_SPRITE_OAM | 0x1288
};

static const u16 sAtomicElectricityOam_MovingDiagonal_Frame10[OAM_DATA_SIZE(1)] = {
    0x1,
    0x0, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_32x32 | 0x1e0, OBJ_SPRITE_OAM | 0x128c
};

static const u16 sAtomicElectricityOam_MovingDiagonal_Unused_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    0x10, OBJ_SIZE_16x16 | 0x1e0, OBJ_SPRITE_OAM | 0x129a
};

static const u16 sAtomicElectricityOam_MovingDiagonal_Unused_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    0x10, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x1e0, OBJ_SPRITE_OAM | 0x129a
};

static const u16 sAtomicElectricityOam_MovingDiagonal_Unused_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0x10, OBJ_SIZE_16x16 | 0x1e0, OBJ_SPRITE_OAM | 0x12da
};

static const u16 sAtomicElectricityOam_MovingDiagonal_Unused_Frame3[OAM_DATA_SIZE(1)] = {
    0x1,
    0x10, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x1e0, OBJ_SPRITE_OAM | 0x12da
};

static const u16 sAtomicElectricityOam_MovingHorizontal_Frame0[OAM_DATA_SIZE(2)] = {
    0x2,
    OBJ_SHAPE_HORIZONTAL | 0xf8, OBJ_SIZE_32x16 | 0x1d8, OBJ_SPRITE_OAM | 0x12b0,
    OBJ_SHAPE_VERTICAL | 0xf8, 0x1f8, OBJ_SPRITE_OAM | 0x12b4
};

static const u16 sAtomicElectricityOam_MovingHorizontal_Frame1[OAM_DATA_SIZE(2)] = {
    0x2,
    OBJ_SHAPE_HORIZONTAL | 0xfc, OBJ_SIZE_32x8 | 0x1d8, OBJ_SPRITE_OAM | 0x12f0,
    0xfc, 0x1f8, OBJ_SPRITE_OAM | 0x12f4
};

static const u16 sAtomicElectricityOam_MovingHorizontal_Frame3[OAM_DATA_SIZE(2)] = {
    0x2,
    OBJ_SHAPE_HORIZONTAL | 0xfb, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_32x16 | 0x1e0, OBJ_SPRITE_OAM | 0x12b0,
    OBJ_SHAPE_VERTICAL | 0xfb, OBJ_X_FLIP | OBJ_Y_FLIP | 0x1d8, OBJ_SPRITE_OAM | 0x12b4
};

static const u16 sAtomicElectricityOam_MovingHorizontal_Frame5[OAM_DATA_SIZE(2)] = {
    0x2,
    OBJ_SHAPE_HORIZONTAL | 0xfc, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_32x8 | 0x1e0, OBJ_SPRITE_OAM | 0x12f0,
    0xfc, OBJ_X_FLIP | OBJ_Y_FLIP | 0x1d8, OBJ_SPRITE_OAM | 0x12f4
};

static const u16 sAtomicElectricityOam_MovingHorizontal_Frame6[OAM_DATA_SIZE(2)] = {
    0x2,
    OBJ_SHAPE_HORIZONTAL | 0xf8, OBJ_Y_FLIP | OBJ_SIZE_32x16 | 0x1d8, OBJ_SPRITE_OAM | 0x12b0,
    OBJ_SHAPE_VERTICAL | 0xf8, OBJ_Y_FLIP | 0x1f8, OBJ_SPRITE_OAM | 0x12b4
};

static const u16 sAtomicElectricityOam_MovingHorizontal_Frame7[OAM_DATA_SIZE(2)] = {
    0x2,
    OBJ_SHAPE_HORIZONTAL | 0xfc, OBJ_Y_FLIP | OBJ_SIZE_32x8 | 0x1d8, OBJ_SPRITE_OAM | 0x12f0,
    0xfc, OBJ_Y_FLIP | 0x1f8, OBJ_SPRITE_OAM | 0x12f4
};

static const u16 sAtomicElectricityOam_MovingHorizontal_Frame9[OAM_DATA_SIZE(2)] = {
    0x2,
    OBJ_SHAPE_HORIZONTAL | 0xf8, OBJ_X_FLIP | OBJ_SIZE_32x16 | 0x1e0, OBJ_SPRITE_OAM | 0x12b0,
    OBJ_SHAPE_VERTICAL | 0xf8, OBJ_X_FLIP | 0x1d8, OBJ_SPRITE_OAM | 0x12b4
};

static const u16 sAtomicElectricityOam_MovingHorizontal_Frame10[OAM_DATA_SIZE(2)] = {
    0x2,
    OBJ_SHAPE_HORIZONTAL | 0xfc, OBJ_X_FLIP | OBJ_SIZE_32x8 | 0x1e0, OBJ_SPRITE_OAM | 0x12f0,
    0xfc, OBJ_X_FLIP | 0x1d8, OBJ_SPRITE_OAM | 0x12f4
};

static const u16 sAtomicElectricityOam_MovingHorizontal_Unused_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    OBJ_SHAPE_HORIZONTAL | 0xfc, OBJ_SIZE_32x8 | 0x1d8, OBJ_SPRITE_OAM | 0x12b5
};

static const u16 sAtomicElectricityOam_MovingHorizontal_Unused_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    OBJ_SHAPE_HORIZONTAL | 0xfc, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_32x8 | 0x1d0, OBJ_SPRITE_OAM | 0x12b5
};

static const u16 sAtomicElectricityOam_MovingHorizontal_Unused_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    OBJ_SHAPE_HORIZONTAL | 0xfc, OBJ_SIZE_32x8 | 0x1d8, OBJ_SPRITE_OAM | 0x12d6
};

static const u16 sAtomicElectricityOam_MovingHorizontal_Unused_Frame3[OAM_DATA_SIZE(1)] = {
    0x1,
    OBJ_SHAPE_HORIZONTAL | 0xfc, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_32x8 | 0x1d0, OBJ_SPRITE_OAM | 0x12d6
};

static const u16 sAtomicElectricityOam_ExplodingNonDiagonal_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, OBJ_SPRITE_OAM | 0x1290
};

static const u16 sAtomicElectricityOam_ExplodingNonDiagonal_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf8, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x12dc
};

static const u16 sAtomicElectricityOam_ExplodingNonDiagonal_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf0, OBJ_SIZE_32x32 | 0x1f0, OBJ_SPRITE_OAM | 0x1210
};

static const u16 sAtomicElectricityOam_ExplodingNonDiagonal_Frame3[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf0, OBJ_SIZE_32x32 | 0x1f0, OBJ_SPRITE_OAM | 0x120c
};

static const u16 sAtomicElectricityOam_ExplodingNonDiagonal_Frame4[OAM_DATA_SIZE(4)] = {
    0x4,
    0xe0, OBJ_SIZE_32x32 | 0x1e0, OBJ_SPRITE_OAM | 0x1208,
    0xe0, OBJ_X_FLIP | OBJ_SIZE_32x32 | 0x0, OBJ_SPRITE_OAM | 0x1208,
    0x0, OBJ_Y_FLIP | OBJ_SIZE_32x32 | 0x1e0, OBJ_SPRITE_OAM | 0x1208,
    0x0, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_32x32 | 0x0, OBJ_SPRITE_OAM | 0x1208
};

static const u16 sAtomicElectricityOam_ExplodingNonDiagonal_Frame5[OAM_DATA_SIZE(8)] = {
    0x8,
    0xdf, OBJ_SIZE_16x16 | 0x11, OBJ_SPRITE_OAM | 0x129a,
    0xdf, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x1df, OBJ_SPRITE_OAM | 0x129a,
    0x11, OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x11, OBJ_SPRITE_OAM | 0x129a,
    0x11, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x1df, OBJ_SPRITE_OAM | 0x129a,
    0xe0, OBJ_SIZE_32x32 | 0x1e0, OBJ_SPRITE_OAM | 0x1204,
    0xe0, OBJ_X_FLIP | OBJ_SIZE_32x32 | 0x0, OBJ_SPRITE_OAM | 0x1204,
    0x0, OBJ_Y_FLIP | OBJ_SIZE_32x32 | 0x1e0, OBJ_SPRITE_OAM | 0x1204,
    0x0, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_32x32 | 0x0, OBJ_SPRITE_OAM | 0x1204
};

static const u16 sAtomicElectricityOam_ExplodingNonDiagonal_Frame6[OAM_DATA_SIZE(8)] = {
    0x8,
    0xdb, OBJ_SIZE_16x16 | 0x15, OBJ_SPRITE_OAM | 0x12da,
    0xdb, OBJ_X_FLIP | OBJ_SIZE_16x16 | 0x1db, OBJ_SPRITE_OAM | 0x12da,
    0x15, OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x15, OBJ_SPRITE_OAM | 0x12da,
    0x15, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x1db, OBJ_SPRITE_OAM | 0x12da,
    0xe0, OBJ_SIZE_32x32 | 0x1e0, OBJ_SPRITE_OAM | 0x1200,
    0xe0, OBJ_X_FLIP | OBJ_SIZE_32x32 | 0x0, OBJ_SPRITE_OAM | 0x1200,
    0x0, OBJ_Y_FLIP | OBJ_SIZE_32x32 | 0x1e0, OBJ_SPRITE_OAM | 0x1200,
    0x0, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_32x32 | 0x0, OBJ_SPRITE_OAM | 0x1200
};

static const u16 sAtomicElectricityOam_ExplodingDiagonal_Frame3[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf0, OBJ_SIZE_32x32 | 0x1f0, OBJ_SPRITE_OAM | 0x120c
};

static const u16 sAtomicElectricityOam_ExplodingDiagonal_Frame4[OAM_DATA_SIZE(4)] = {
    0x4,
    0xe0, OBJ_SIZE_32x32 | 0x1e0, OBJ_SPRITE_OAM | 0x1208,
    0xe0, OBJ_X_FLIP | OBJ_SIZE_32x32 | 0x0, OBJ_SPRITE_OAM | 0x1208,
    0x0, OBJ_Y_FLIP | OBJ_SIZE_32x32 | 0x1e0, OBJ_SPRITE_OAM | 0x1208,
    0x0, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_32x32 | 0x0, OBJ_SPRITE_OAM | 0x1208
};

static const u16 sAtomicElectricityOam_ExplodingDiagonal_Frame5[OAM_DATA_SIZE(12)] = {
    0xc,
    0xe0, OBJ_SIZE_32x32 | 0x1e0, OBJ_SPRITE_OAM | 0x1204,
    0xe0, OBJ_X_FLIP | OBJ_SIZE_32x32 | 0x0, OBJ_SPRITE_OAM | 0x1204,
    0x0, OBJ_Y_FLIP | OBJ_SIZE_32x32 | 0x1e0, OBJ_SPRITE_OAM | 0x1204,
    0x0, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_32x32 | 0x0, OBJ_SPRITE_OAM | 0x1204,
    OBJ_SHAPE_VERTICAL | 0xd8, 0x1fc, OBJ_SPRITE_OAM | 0x1258,
    0xe8, 0x1fc, OBJ_SPRITE_OAM | 0x1298,
    OBJ_SHAPE_HORIZONTAL | 0xfc, 0x1d8, OBJ_SPRITE_OAM | 0x12b5,
    0xfc, 0x1e8, OBJ_SPRITE_OAM | 0x12b7,
    OBJ_SHAPE_VERTICAL | 0x18, OBJ_X_FLIP | OBJ_Y_FLIP | 0x1fc, OBJ_SPRITE_OAM | 0x1258,
    0x10, OBJ_X_FLIP | OBJ_Y_FLIP | 0x1fc, OBJ_SPRITE_OAM | 0x1298,
    OBJ_SHAPE_HORIZONTAL | 0xfc, OBJ_X_FLIP | OBJ_Y_FLIP | 0x18, OBJ_SPRITE_OAM | 0x12b5,
    0xfc, OBJ_X_FLIP | OBJ_Y_FLIP | 0x10, OBJ_SPRITE_OAM | 0x12b7
};

static const u16 sAtomicElectricityOam_ExplodingDiagonal_Frame6[OAM_DATA_SIZE(12)] = {
    0xc,
    0xe0, OBJ_SIZE_32x32 | 0x1e0, OBJ_SPRITE_OAM | 0x1200,
    0xe0, OBJ_X_FLIP | OBJ_SIZE_32x32 | 0x0, OBJ_SPRITE_OAM | 0x1200,
    0x0, OBJ_Y_FLIP | OBJ_SIZE_32x32 | 0x1e0, OBJ_SPRITE_OAM | 0x1200,
    0x0, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_32x32 | 0x0, OBJ_SPRITE_OAM | 0x1200,
    OBJ_SHAPE_VERTICAL | 0xd0, 0x1fc, OBJ_SPRITE_OAM | 0x1279,
    0xe0, 0x1fc, OBJ_SPRITE_OAM | 0x12b9,
    OBJ_SHAPE_HORIZONTAL | 0xfc, 0x1d0, OBJ_SPRITE_OAM | 0x12d6,
    0xfc, 0x1e0, OBJ_SPRITE_OAM | 0x12d8,
    OBJ_SHAPE_VERTICAL | 0x20, OBJ_X_FLIP | OBJ_Y_FLIP | 0x1fc, OBJ_SPRITE_OAM | 0x1279,
    0x18, OBJ_X_FLIP | OBJ_Y_FLIP | 0x1fc, OBJ_SPRITE_OAM | 0x12b9,
    OBJ_SHAPE_HORIZONTAL | 0xfc, OBJ_X_FLIP | OBJ_Y_FLIP | 0x20, OBJ_SPRITE_OAM | 0x12d6,
    0xfc, OBJ_X_FLIP | OBJ_Y_FLIP | 0x18, OBJ_SPRITE_OAM | 0x12d8
};

static const u16 sAtomicElectricityOam_MovingVertical_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfc, 0x1fc, OBJ_SPRITE_OAM | 0x1204
};

static const u16 sAtomicElectricityOam_Charging_Frame0[OAM_DATA_SIZE(1)] = {
    0x1,
    OBJ_SHAPE_VERTICAL | 0xf0, OBJ_SIZE_8x32 | 0x1f8, OBJ_SPRITE_OAM | 0x125f
};

static const u16 sAtomicElectricityOam_Charging_Frame1[OAM_DATA_SIZE(1)] = {
    0x1,
    0xfb, OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x12de
};

static const u16 sAtomicElectricityOam_Charging_Frame2[OAM_DATA_SIZE(1)] = {
    0x1,
    OBJ_SHAPE_HORIZONTAL | 0x1, OBJ_SIZE_32x8 | 0x1f0, OBJ_SPRITE_OAM | 0x125b
};

static const u16 sAtomicElectricityOam_Charging_Frame4[OAM_DATA_SIZE(1)] = {
    0x1,
    OBJ_SHAPE_VERTICAL | 0xf0, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_8x32 | 0x0, OBJ_SPRITE_OAM | 0x125f
};

static const u16 sAtomicElectricityOam_Charging_Frame5[OAM_DATA_SIZE(1)] = {
    0x1,
    0xf5, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_16x16 | 0x1f8, OBJ_SPRITE_OAM | 0x12de
};

static const u16 sAtomicElectricityOam_Charging_Frame7[OAM_DATA_SIZE(1)] = {
    0x1,
    OBJ_SHAPE_HORIZONTAL | 0xf7, OBJ_X_FLIP | OBJ_Y_FLIP | OBJ_SIZE_32x8 | 0x1f0, OBJ_SPRITE_OAM | 0x125b
};

const struct FrameData sAtomicOam_Idle[13] = {
    [0] = {
        .pFrame = sAtomicOam_Idle_Frame0,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [1] = {
        .pFrame = sAtomicOam_Idle_Frame1,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [2] = {
        .pFrame = sAtomicOam_Idle_Frame2,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [3] = {
        .pFrame = sAtomicOam_Idle_Frame3,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [4] = {
        .pFrame = sAtomicOam_Idle_Frame4,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [5] = {
        .pFrame = sAtomicOam_Idle_Frame5,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [6] = {
        .pFrame = sAtomicOam_Idle_Frame6,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [7] = {
        .pFrame = sAtomicOam_Idle_Frame7,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [8] = {
        .pFrame = sAtomicOam_Idle_Frame8,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [9] = {
        .pFrame = sAtomicOam_Idle_Frame9,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [10] = {
        .pFrame = sAtomicOam_Idle_Frame10,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [11] = {
        .pFrame = sAtomicOam_Idle_Frame11,
        .timer = CONVERT_SECONDS(2.f / 15)
    },
    [12] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtomicElectricityOam_MovingVertical[13] = {
    [0] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame0,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [1] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame1,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [2] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame2,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [3] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame3,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [4] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame2,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [5] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame5,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [6] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame6,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [7] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame7,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [8] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame2,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [9] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame9,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [10] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame10,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [11] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame2,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [12] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtomicElectricityOam_MovingVertical_Unused[5] = {
    [0] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Unused_Frame0,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [1] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Unused_Frame1,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [2] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Unused_Frame2,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [3] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Unused_Frame3,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtomicElectricityOam_MovingDiagonal[13] = {
    [0] = {
        .pFrame = sAtomicElectricityOam_MovingDiagonal_Frame0,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [1] = {
        .pFrame = sAtomicElectricityOam_MovingDiagonal_Frame1,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [2] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame2,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [3] = {
        .pFrame = sAtomicElectricityOam_MovingDiagonal_Frame3,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [4] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame2,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [5] = {
        .pFrame = sAtomicElectricityOam_MovingDiagonal_Frame5,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [6] = {
        .pFrame = sAtomicElectricityOam_MovingDiagonal_Frame6,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [7] = {
        .pFrame = sAtomicElectricityOam_MovingDiagonal_Frame7,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [8] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame2,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [9] = {
        .pFrame = sAtomicElectricityOam_MovingDiagonal_Frame9,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [10] = {
        .pFrame = sAtomicElectricityOam_MovingDiagonal_Frame10,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [11] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame2,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [12] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtomicElectricityOam_MovingDiagonal_Unused[5] = {
    [0] = {
        .pFrame = sAtomicElectricityOam_MovingDiagonal_Unused_Frame0,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [1] = {
        .pFrame = sAtomicElectricityOam_MovingDiagonal_Unused_Frame1,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [2] = {
        .pFrame = sAtomicElectricityOam_MovingDiagonal_Unused_Frame2,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [3] = {
        .pFrame = sAtomicElectricityOam_MovingDiagonal_Unused_Frame3,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtomicElectricityOam_MovingHorizontal[13] = {
    [0] = {
        .pFrame = sAtomicElectricityOam_MovingHorizontal_Frame0,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [1] = {
        .pFrame = sAtomicElectricityOam_MovingHorizontal_Frame1,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [2] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame2,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [3] = {
        .pFrame = sAtomicElectricityOam_MovingHorizontal_Frame3,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [4] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame2,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [5] = {
        .pFrame = sAtomicElectricityOam_MovingHorizontal_Frame5,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [6] = {
        .pFrame = sAtomicElectricityOam_MovingHorizontal_Frame6,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [7] = {
        .pFrame = sAtomicElectricityOam_MovingHorizontal_Frame7,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [8] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame2,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [9] = {
        .pFrame = sAtomicElectricityOam_MovingHorizontal_Frame9,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [10] = {
        .pFrame = sAtomicElectricityOam_MovingHorizontal_Frame10,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [11] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame2,
        .timer = CONVERT_SECONDS(1.f / 60)
    },
    [12] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtomicElectricityOam_MovingHorizontal_Unused[5] = {
    [0] = {
        .pFrame = sAtomicElectricityOam_MovingHorizontal_Unused_Frame0,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [1] = {
        .pFrame = sAtomicElectricityOam_MovingHorizontal_Unused_Frame1,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [2] = {
        .pFrame = sAtomicElectricityOam_MovingHorizontal_Unused_Frame2,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [3] = {
        .pFrame = sAtomicElectricityOam_MovingHorizontal_Unused_Frame3,
        .timer = CONVERT_SECONDS(1.f / 30)
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtomicElectricityOam_ExplodingNonDiagonal[8] = {
    [0] = {
        .pFrame = sAtomicElectricityOam_ExplodingNonDiagonal_Frame0,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [1] = {
        .pFrame = sAtomicElectricityOam_ExplodingNonDiagonal_Frame1,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [2] = {
        .pFrame = sAtomicElectricityOam_ExplodingNonDiagonal_Frame2,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [3] = {
        .pFrame = sAtomicElectricityOam_ExplodingNonDiagonal_Frame3,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [4] = {
        .pFrame = sAtomicElectricityOam_ExplodingNonDiagonal_Frame4,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [5] = {
        .pFrame = sAtomicElectricityOam_ExplodingNonDiagonal_Frame5,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [6] = {
        .pFrame = sAtomicElectricityOam_ExplodingNonDiagonal_Frame6,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [7] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtomicElectricityOam_ExplodingDiagonal[8] = {
    [0] = {
        .pFrame = sAtomicElectricityOam_ExplodingNonDiagonal_Frame0,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [1] = {
        .pFrame = sAtomicElectricityOam_ExplodingNonDiagonal_Frame1,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [2] = {
        .pFrame = sAtomicElectricityOam_ExplodingNonDiagonal_Frame2,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [3] = {
        .pFrame = sAtomicElectricityOam_ExplodingDiagonal_Frame3,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [4] = {
        .pFrame = sAtomicElectricityOam_ExplodingDiagonal_Frame4,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [5] = {
        .pFrame = sAtomicElectricityOam_ExplodingDiagonal_Frame5,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [6] = {
        .pFrame = sAtomicElectricityOam_ExplodingDiagonal_Frame6,
        .timer = CONVERT_SECONDS(1.f / 15)
    },
    [7] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtomicElectricityOam_Charging[12] = {
    [0] = {
        .pFrame = sAtomicElectricityOam_Charging_Frame0,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [1] = {
        .pFrame = sAtomicElectricityOam_Charging_Frame1,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [2] = {
        .pFrame = sAtomicElectricityOam_Charging_Frame2,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [3] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame2,
        .timer = CONVERT_SECONDS(0.5f)
    },
    [4] = {
        .pFrame = sAtomicElectricityOam_Charging_Frame4,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [5] = {
        .pFrame = sAtomicElectricityOam_Charging_Frame5,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [6] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame2,
        .timer = CONVERT_SECONDS(0.5f)
    },
    [7] = {
        .pFrame = sAtomicElectricityOam_Charging_Frame7,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [8] = {
        .pFrame = sAtomicElectricityOam_MovingVertical_Frame2,
        .timer = CONVERT_SECONDS(0.5f)
    },
    [9] = {
        .pFrame = sAtomicElectricityOam_Charging_Frame0,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [10] = {
        .pFrame = sAtomicElectricityOam_Charging_Frame4,
        .timer = CONVERT_SECONDS(0.05f)
    },
    [11] = FRAME_DATA_TERMINATOR
};
