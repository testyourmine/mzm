#ifndef HOLTZ_DATA_H
#define HOLTZ_DATA_H

#include "types.h"
#include "macros.h"
#include "oam.h"

extern const s16 sHoltzIdleYVelocity[65];

extern const u32 sHoltzGfx[200];
extern const u16 sHoltzPal[16];

extern const u16 sHoltzOam_Idle_Frame0[13];

extern const u16 sHoltzOam_Idle_Frame1[13];

extern const u16 sHoltzOam_Idle_Frame2[13];

extern const u16 sHoltzOam_Idle_Frame3[16];

extern const u16 sHoltzOam_Warning_Frame1[16];

extern const u16 sHoltzOam_Warning_Frame2[16];

extern const u16 sHoltzOam_Warning_Frame3[16];

extern const u16 sHoltzOam_Warning_Frame4[13];

extern const u16 sHoltzOam_Warning_Frame5[13];

extern const u16 sHoltzOam_Warning_Frame6[13];

extern const u16 sHoltzOam_Warning_Frame7[13];

extern const u16 sHoltzOam_Warning_Frame8[16];

extern const u16 sHoltzOam_GoingDown_Frame0[13];

extern const u16 sHoltzOam_GoingDown_Frame1[13];

extern const u16 sHoltzOam_IdleAware_Frame2[16];

extern const u16 sHoltzOam_GoingUp_Frame2[16];

extern const u16 sHoltzOam_GoingUp_Frame1[19];

extern const u16 sHoltzOam_GoingUp_Frame0[19];

extern const struct FrameData sHoltzOam_Idle[5];

extern const struct FrameData sHoltzOam_Warning[10];

extern const struct FrameData sHoltzOam_GoingDown[3];

extern const struct FrameData sHoltzOam_IdleAware[4];

extern const struct FrameData sHoltzOam_GoingUp[8];

extern const struct FrameData sHoltzOam_BonkingOnCeiling[10];

#endif
