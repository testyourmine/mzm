#ifndef ACID_WORM_DATA_H
#define ACID_WORM_DATA_H

#include "types.h"
#include "oam.h"

extern const s16 sAcidWormSpitCloseYVelocity[16];

extern const s16 sAcidWormSpitFarYVelocity[26];

extern const s16 sAcidWormSpitMiddleYVelocity[20];

extern const s16 sAcidWormSwingingMovement[33];

extern const s16 sAcidWormHeadRandomXVelocity[45];

extern const u32 sAcidWormGfx[1000];
extern const u16 sAcidWormPal[64];

extern const u16 sAcidWormPartOam_Unused2_Frame0[52];

extern const u16 sAcidWormPartOam_Unused2_Frame1[52];

extern const u16 sAcidWormPartOam_Unused2_Frame2[52];

extern const u16 sAcidWormOam_Spitting_Frame4[34];

extern const u16 sAcidWormOam_Spitting_Frame3[34];

extern const u16 sAcidWormOam_Spitting_Frame2[34];

extern const u16 sAcidWormOam_Spitting_Frame0[34];

extern const u16 sAcidWormOam_MouthClosed_Frame2[34];

extern const u16 sAcidWormOam_Idle_Frame0[34];

extern const u16 sAcidWormOam_Idle_Frame1[34];

extern const u16 sAcidWormOam_Idle_Frame2[34];

extern const u16 sAcidWormOam_Moving_Frame0[34];

extern const u16 sAcidWormOam_Moving_Frame1[34];

extern const u16 sAcidWormPartOam_AroundMouth_Frame0[4];

extern const u16 sAcidWormPartOam_WeakPoint_Frame0[4];

extern const u16 sAcidWormPartOam_WeakPoint_Frame1[4];

extern const u16 sAcidWormPartOam_WeakPoint_Frame2[4];

extern const u16 sAcidWormPartOam_BelowWeakPoint_Frame0[4];

extern const u16 sAcidWormPartOam_AboveSegments_Frame0[4];

extern const u16 sAcidWormPartOam_Segment_Frame0[4];

extern const u16 sAcidWormSpitOAM_Moving_Frame0[4];

extern const u16 sAcidWormSpitOAM_Moving_Frame1[4];

extern const u16 sAcidWormSpitOAM_Moving_Frame2[4];

extern const u16 sAcidWormSpitOAM_Exploding_Frame1[13];

extern const u16 sAcidWormSpitOAM_Exploding_Frame2[16];

extern const u16 sAcidWormSpitOAM_Exploding_Frame3[25];

extern const u16 sAcidWormSpitOAM_Exploding_Frame4[19];

extern const struct FrameData sAcidWormOam_Idle[5];

extern const struct FrameData sAcidWormOam_Moving[3];

extern const struct FrameData sAcidWormOam_Spitting[15];

extern const struct FrameData sAcidWormOam_MouthClosed[5];

extern const struct FrameData sAcidWormPartOam_AroundMouth[2];

extern const struct FrameData sAcidWormPartOam_WeakPoint[9];

extern const struct FrameData sAcidWormPartOam_Unused[5];

extern const struct FrameData sAcidWormPartOam_BelowWeakPoint[2];

extern const struct FrameData sAcidWormPartOam_AboveSegments[2];

extern const struct FrameData sAcidWormPartOam_Segment[2];

extern const struct FrameData sAcidWormPartOam_Unused2[5];

extern const struct FrameData sAcidWormSpitOAM_Moving[4];

extern const struct FrameData sAcidWormSpitOAM_Exploding[6];

extern const struct FrameData sAcidWormOam_Warning[14];

extern const struct FrameData sAcidWormOam_SpawnOnTop[24];

#endif