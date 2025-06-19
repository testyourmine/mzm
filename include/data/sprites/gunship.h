#ifndef GUNSHIP_DATA_DATA_H
#define GUNSHIP_DATA_DATA_H

#include "types.h"
#include "oam.h"

extern const s16 sGunshipTakingOffYVelocity[153];

extern const s16 sGunshipFlyingYVelocity[22];

extern const u32 sGunshipGfx[1027];
extern const u16 sGunshipPal[48];
extern const u16 sGunshipFlashingPal[8 * 16];

extern const u16 sGunshipOam_Idle_Frame0[52];

extern const u16 sGunshipOam_Idle_Frame1[52];

extern const u16 sGunshipOam_Idle_Frame2[52];

extern const u16 sGunshipOam_Idle_Frame3[52];

extern const u16 sGunshipPartOam_EntranceFrontClosed_Frame0[13];

extern const u16 sGunshipPartOam_EntranceFrontOpening_Frame0[13];

extern const u16 sGunshipPartOam_EntranceFrontOpening_Frame1[13];

extern const u16 sGunshipPartOam_EntranceFrontOpening_Frame2[13];

extern const u16 sGunshipPartOam_EntranceFrontOpening_Frame3[13];

extern const u16 sGunshipPartOam_EntranceFrontOpened_Frame0[19];

extern const u16 sGunshipPartOam_EntranceFrontOpened_Frame1[19];

extern const u16 sGunshipPartOam_EntranceFrontOpened_Frame2[19];

extern const u16 sGunshipPartOam_EntranceFrontOpened_Frame3[19];

extern const u16 sGunshipPartOam_EntranceBackCLosed_Frame0[16];

extern const u16 sGunshipPartOam_EntranceBackOpening_Frame0[16];

extern const u16 sGunshipPartOam_EntranceBackOpening_Frame1[16];

extern const u16 sGunshipPartOam_EntranceBackOpening_Frame2[16];

extern const u16 sGunshipPartOam_EntranceBackOpening_Frame3[16];

extern const u16 sGunshipPartOam_EntranceBackOpening_Frame4[16];

extern const u16 sGunshipPartOam_EntranceBackOpening_Frame5[16];

extern const u16 sGunshipPartOam_EntranceBackOpening_Frame6[16];

extern const u16 sGunshipPartOam_EntranceBackOpening_Frame7[16];

extern const u16 sGunshipPartOam_EntranceBackOpened_Frame0[25];

extern const u16 sGunshipPartOam_EntranceBackOpened_Frame1[25];

extern const u16 sGunshipPartOam_EntranceBackOpened_Frame2[25];

extern const u16 sGunshipPartOam_EntranceBackOpened_Frame3[25];

extern const u16 sGunshipPartOam_Platform_Frame0[7];

extern const u16 sGunshipPartOam_Platform_Frame1[7];

extern const u16 sGunshipPartOam_Platform_Frame2[7];

extern const u16 sGunshipPartOam_Platform_Frame3[7];

extern const u16 sGunshipOam_Flying_Frame0[82];

extern const u16 sGunshipOam_Flying_Frame1[82];

extern const u16 sGunshipOam_Flying_Frame2[82];

extern const u16 sGunshipOam_Flying_Frame3[82];

extern const u16 sGunshipPartOam_FlamesHorizontal_Frame0[25];

extern const u16 sGunshipPartOam_FlamesHorizontal_Frame1[25];

extern const u16 sGunshipPartOam_FlamesHorizontal_Frame2[4];

extern const u16 sGunshipPartOam_FlamesVertical_Frame0[13];

extern const u16 sGunshipPartOam_FlamesVertical_Frame1[25];

extern const u16 sGunshipPartOam_FlamesVertical_Frame2[25];

extern const struct FrameData sGunshipOam_Idle[7];

extern const struct FrameData sGunshipOam_Refilling[7];

extern const struct FrameData sGunshipPartOam_EntranceFrontClosed[2];

extern const struct FrameData sGunshipPartOam_EntranceFrontOpening[5];

extern const struct FrameData sGunshipPartOam_EntranceFrontOpened[7];

extern const struct FrameData sGunshipPartOam_EntranceFrontClosing[6];

extern const struct FrameData sGunshipPartOam_EntranceBackClosed[2];

extern const struct FrameData sGunshipPartOam_EntranceBackOpening[9];

extern const struct FrameData sGunshipPartOam_EntranceBackOpened[7];

extern const struct FrameData sGunshipPartOam_EntranceBackClosing[9];

extern const struct FrameData sGunshipPartOam_Platform[5];

extern const struct FrameData sGunshipOam_Flying[7];

extern const struct FrameData sGunshipPartOam_FlamesHorizontal[4];

extern const struct FrameData sGunshipPartOam_FlamesVertical[4];

#endif
