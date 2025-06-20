#include "sprites_AI/hive.h"
#include "macros.h"
#include "gba/display.h"

#include "data/sprites/hive.h"
#include "data/sprite_data.h"

#include "constants/audio.h"
#include "constants/event.h"
#include "constants/particle.h"
#include "constants/sprite.h"
#include "constants/sprite_util.h"

#include "structs/bg_clip.h"
#include "structs/display.h"
#include "structs/sprite.h"
#include "structs/samus.h"

#define HIVE_POSE_PHASE_1 0x9
#define HIVE_POSE_PHASE_2 0x23
#define HIVE_POSE_PHASE_3 0x25
#define HIVE_POSE_DEAD 0x67

#define HIVE_ROOTS_POSE_IDLE 0x9

#define MELLOW_POSE_IDLE 0x9
#define MELLOW_POSE_MOVE_INIT 0x22
#define MELLOW_POSE_MOVE 0x23
#define MELLOW_POSE_FLEEING 0x25

#define MELLOW_SWARM_POSE_IDLE 0x9

/**
 * @brief 24a10 | 2c | Spawns 2 particle effects
 * 
 */
static void HiveSpawnParticle(void)
{
    u16 xPosition;
    u16 yPosition;

    yPosition = gCurrentSprite.yPosition;
    xPosition = gCurrentSprite.xPosition;

    ParticleSet(yPosition - HALF_BLOCK_SIZE, xPosition, PE_MEDIUM_DUST);
    ParticleSet(yPosition + BLOCK_SIZE + HALF_BLOCK_SIZE, xPosition, PE_TWO_MEDIUM_DUST);
}

/**
 * @brief 24a3c | 124 | Initializes a hive sprite
 * 
 */
static void HiveInit(void)
{
    u8 roomSlot;
    u8 gfxSlot;
    u16 yPosition;
    u16 xPosition;

    if (EventFunction(EVENT_ACTION_CHECKING, EVENT_THREE_HIVES_DESTROYED))
    {
        // Kill if the 3 hives were destroyed
        gCurrentSprite.status = 0;
        return;
    }

    gCurrentSprite.drawDistanceTop = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE * 2 + HALF_BLOCK_SIZE);
    gCurrentSprite.drawDistanceBottom = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE * 2 + HALF_BLOCK_SIZE);
    gCurrentSprite.drawDistanceHorizontal = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE + QUARTER_BLOCK_SIZE);

    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2);
    gCurrentSprite.hitboxBottom = BLOCK_SIZE * 2;
    gCurrentSprite.hitboxLeft = -THREE_QUARTER_BLOCK_SIZE;
    gCurrentSprite.hitboxRight = THREE_QUARTER_BLOCK_SIZE;

    gCurrentSprite.samusCollision = SSC_HURTS_SAMUS_SOLID;
    gCurrentSprite.frozenPaletteRowOffset = 1;

    gCurrentSprite.pOam = sHiveOam_Idle;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;

    gCurrentSprite.drawOrder = 5;
    gCurrentSprite.health = GET_PSPRITE_HEALTH(gCurrentSprite.spriteId);
    gCurrentSprite.pose = 9;
    gCurrentSprite.work0 = 0;
    
    yPosition = gCurrentSprite.yPosition;
    xPosition = gCurrentSprite.xPosition;
    gfxSlot = gCurrentSprite.spritesetGfxSlot;
    roomSlot = gCurrentSprite.roomSlot;
    
    // Spawn rooms
    SpriteSpawnSecondary(SSPRITE_HIVE_ROOTS, roomSlot, gfxSlot, gCurrentSprite.primarySpriteRamSlot, yPosition, xPosition, 0);

    // Spawn mellows
    SpriteSpawnPrimary(PSPRITE_MELLOW, roomSlot, gfxSlot,
        yPosition + BLOCK_SIZE, xPosition - (HALF_BLOCK_SIZE - ONE_SUB_PIXEL), 0);
    SpriteSpawnPrimary(PSPRITE_MELLOW, roomSlot, gfxSlot,
        yPosition + HALF_BLOCK_SIZE, xPosition + QUARTER_BLOCK_SIZE, 0);
    SpriteSpawnPrimary(PSPRITE_MELLOW, roomSlot, gfxSlot,
        yPosition - (BLOCK_SIZE + EIGHTH_BLOCK_SIZE), xPosition - QUARTER_BLOCK_SIZE, 0);
    SpriteSpawnPrimary(PSPRITE_MELLOW, roomSlot, gfxSlot,
        yPosition - (BLOCK_SIZE + HALF_BLOCK_SIZE), xPosition + (HALF_BLOCK_SIZE - ONE_SUB_PIXEL), 0);
}

/**
 * @brief 24b60 | 54 | Counts the mellow linked to the current hive
 * 
 * @return u8 Number of mellows
 */
static u8 HiveCountMellows(void)
{
    u8 count;
    u8 roomSlot;
    u8 collision;
    struct SpriteData* pSprite;

    count = 0;
    collision = SSC_MELLOW;
    // For current hive only
    roomSlot = gCurrentSprite.roomSlot;

    for (pSprite = gSpriteData; pSprite < gSpriteData + MAX_AMOUNT_OF_SPRITES; pSprite++)
    {
        if (!(pSprite->status & SPRITE_STATUS_EXISTS))
            continue;

        if (pSprite->samusCollision == collision && pSprite->roomSlot == roomSlot)
            count++;
    }

    return count;
}

/**
 * @brief 24bb4 | 78 | Handles the phase 1 of the hive
 * 
 */
static void HivePhase1(void)
{
    if (HiveCountMellows() < 4)
    {
        SpriteSpawnPrimary(PSPRITE_MELLOW, gCurrentSprite.roomSlot, gCurrentSprite.spritesetGfxSlot,
            gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
    }
    
    if (gCurrentSprite.health < GET_PSPRITE_HEALTH(gCurrentSprite.spriteId) / 2)
    {
        gCurrentSprite.frozenPaletteRowOffset = 2;

        gCurrentSprite.pOam = sHiveOam_Phase2;
        gCurrentSprite.animationDurationCounter = 0;
        gCurrentSprite.currentAnimationFrame = 0;

        gCurrentSprite.pose = HIVE_POSE_PHASE_2;
        SoundPlayNotAlreadyPlaying(SOUND_HIVE_SHRINKING);
        HiveSpawnParticle();
    }
}

/**
 * @brief 24c2c | 78 | Handles the phase 2 of the hive
 * 
 */
static void HivePhase2(void)
{
    if (HiveCountMellows() < 4)
    {
        SpriteSpawnPrimary(PSPRITE_MELLOW, gCurrentSprite.roomSlot, gCurrentSprite.spritesetGfxSlot,
            gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
    }
    
    if (gCurrentSprite.health < GET_PSPRITE_HEALTH(gCurrentSprite.spriteId) / 4)
    {
        gCurrentSprite.frozenPaletteRowOffset = 3;

        gCurrentSprite.pOam = sHiveOam_Phase3;
        gCurrentSprite.animationDurationCounter = 0;
        gCurrentSprite.currentAnimationFrame = 0;

        gCurrentSprite.pose = HIVE_POSE_PHASE_3;
        SoundPlayNotAlreadyPlaying(SOUND_HIVE_SHRINKING);
        HiveSpawnParticle();
    }
}

/**
 * @brief 24ca4 | 30 | Handles the phase 3 of the hive
 * 
 */
static void HivePhase3(void)
{
    if (HiveCountMellows() < 4)
    {
        SpriteSpawnPrimary(PSPRITE_MELLOW, gCurrentSprite.roomSlot, gCurrentSprite.spritesetGfxSlot,
            gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
    }
}

/**
 * @brief 24cd4 | 10c | Handles the hive dying
 * 
 */
static void HiveDying(void)
{
    u8 count;
    u8 collision;
    struct SpriteData* pSprite;
    u8 param;
    u8 pose;

    count = 0;
    param = PSPRITE_HIVE;

    // Count hives
    for (pSprite = gSpriteData; pSprite < gSpriteData + MAX_AMOUNT_OF_SPRITES; pSprite++)
    {
        if (!(pSprite->status & SPRITE_STATUS_EXISTS))
            continue;

        if (pSprite->properties & SP_SECONDARY_SPRITE)
            continue;

        if (pSprite->spriteId == param && pSprite->health != 0)
            count++;
    }

    if (count == 0) // Set event if all hives are dead
        EventFunction(EVENT_ACTION_SETTING, EVENT_THREE_HIVES_DESTROYED);

    pose = MELLOW_POSE_IDLE;
    param = gCurrentSprite.roomSlot;
    collision = SSC_MELLOW;

    // Set mellows of current hive to fleeing behavior
    for (pSprite = gSpriteData; pSprite < gSpriteData + MAX_AMOUNT_OF_SPRITES; pSprite++)
    {
        if (!(pSprite->status & SPRITE_STATUS_EXISTS))
            continue;

        if (pSprite->samusCollision == collision && pSprite->roomSlot == param && pSprite->pose == pose)
        {
            pSprite->pose = MELLOW_POSE_FLEEING;
            pSprite->properties |= SP_KILL_OFF_SCREEN;
        }
    }

    if (gCurrentSprite.pose > SPRITE_POSE_DESTROYED || gCurrentSprite.work0 != 0)
    {
        SpriteUtilSpriteDeath(DEATH_NORMAL, gCurrentSprite.yPosition + BLOCK_SIZE + EIGHTH_BLOCK_SIZE,
            gCurrentSprite.xPosition, TRUE, PE_SPRITE_EXPLOSION_SINGLE_THEN_BIG);
    }
    else
    {
        // Set killed behavior
        gCurrentSprite.pose = HIVE_POSE_DEAD;
        gCurrentSprite.pOam = sHiveOam_Dying;
        gCurrentSprite.animationDurationCounter = 0;
        gCurrentSprite.currentAnimationFrame = 0;
        gCurrentSprite.samusCollision = SSC_NONE;
        SoundPlayNotAlreadyPlaying(SOUND_HIVE_DEAD);
        HiveSpawnParticle();
    }
}

/**
 * @brief 24de0 | 10 | Sets the ignore samus collision timer to 1
 * 
 */
static void HiveDead(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = DELTA_TIME;
}

/**
 * @brief 24df0 | 64 | Initializes a hive roots sprite
 * 
 */
static void HiveRootsInit(void)
{
    gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
    gCurrentSprite.samusCollision = SSC_NONE;

    gCurrentSprite.drawDistanceTop = SUB_PIXEL_TO_PIXEL(0);
    gCurrentSprite.drawDistanceBottom = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE * 2);
    gCurrentSprite.drawDistanceHorizontal = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE + QUARTER_BLOCK_SIZE);

    gCurrentSprite.hitboxTop = -PIXEL_SIZE;
    gCurrentSprite.hitboxBottom = PIXEL_SIZE;
    gCurrentSprite.hitboxLeft = -PIXEL_SIZE;
    gCurrentSprite.hitboxRight = PIXEL_SIZE;

    gCurrentSprite.pose = HIVE_ROOTS_POSE_IDLE;

    gCurrentSprite.pOam = sHiveRootsOAM_Idle;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;

    gCurrentSprite.frozenPaletteRowOffset = 1;
}

/**
 * @brief 24e54 | 24 | Syncronises the position of the roots with the hive
 * 
 */
static void HiveRootsIdle(void)
{
    u8 ramSlot;

    ramSlot = gCurrentSprite.primarySpriteRamSlot;

    gCurrentSprite.yPosition = gSpriteData[ramSlot].yPosition;
    gCurrentSprite.xPosition = gSpriteData[ramSlot].xPosition;
}

/**
 * @brief 24e78 | 150 | Initializes a mellow sprite
 * 
 * @param pSprite Sprite data pointer
 */
static void MellowInit(struct SpriteData* pSprite)
{
    if (EventFunction(EVENT_ACTION_CHECKING, EVENT_THREE_HIVES_DESTROYED))
    {
        pSprite->status = 0;
        return;
    }

    pSprite->status &= ~SPRITE_STATUS_NOT_DRAWN;

    pSprite->drawDistanceTop = SUB_PIXEL_TO_PIXEL(HALF_BLOCK_SIZE);
    pSprite->drawDistanceBottom = SUB_PIXEL_TO_PIXEL(HALF_BLOCK_SIZE);
    pSprite->drawDistanceHorizontal = SUB_PIXEL_TO_PIXEL(THREE_QUARTER_BLOCK_SIZE);

    pSprite->hitboxTop = -(QUARTER_BLOCK_SIZE - PIXEL_SIZE);
    pSprite->hitboxBottom = (QUARTER_BLOCK_SIZE - PIXEL_SIZE);
    pSprite->hitboxLeft = -HALF_BLOCK_SIZE;
    pSprite->hitboxRight = HALF_BLOCK_SIZE;

    pSprite->animationDurationCounter = 0;
    pSprite->currentAnimationFrame = 0;
    pSprite->samusCollision = SSC_MELLOW;
    
    pSprite->health = GET_PSPRITE_HEALTH(pSprite->spriteId);
    if (pSprite->roomSlot != 0x88)
    {
        pSprite->pOam = sMellowOam_Idle;
        pSprite->pose = MELLOW_POSE_IDLE;
        pSprite->work3 = MUL_SHIFT(gSpriteRng, 4);
        if (gSpriteRng & 0x1)
            pSprite->work2 = 0x14;
        else
            pSprite->work2 = 0x3C;
        
        if (pSprite->xPosition & 0x1)
            pSprite->drawOrder = 3;
        else
            pSprite->drawOrder = 6;
    }
    else
    {
        pSprite->pOam = sMellowOam_SamusDetected;
        pSprite->bgPriority = BGCNT_GET_PRIORITY(gIoRegistersBackup.BG1CNT);
        pSprite->drawOrder = 3;
        pSprite->work1 = 0;
        pSprite->work2 = 1;
        pSprite->work0 = 0;
        pSprite->work3 = 1;
        pSprite->xPositionSpawn = gSpriteRng & 0x3;
        pSprite->pose = MELLOW_POSE_MOVE;
        pSprite->scaling = 0x20;
        SpriteUtilMakeSpriteFaceSamusDirection();
        if (pSprite->yPosition > gSamusData.yPosition + gSamusPhysics.drawDistanceTop)
            pSprite->status &= ~SPRITE_STATUS_FACING_DOWN;
        else
            pSprite->status |= SPRITE_STATUS_FACING_DOWN;
    }
}

/**
 * @brief 24fc8 | c0 | Handles a mellow being idle
 * 
 * @param pSprite Sprite data pointer
 */
static void MellowIdle(struct SpriteData* pSprite)
{
    s32 movement;
    u8 offset;

    // Idle Y
    offset = pSprite->work3;
    movement = sMellowIdleYVelocity[offset];

    if (movement == SHORT_MAX)
    {
        movement = sMellowIdleYVelocity[0];
        offset = 0;
    }

    // Idle X
    pSprite->work3 = offset + 1;
    pSprite->yPosition += movement;

    offset = pSprite->work2;
    movement = sMellowIdleXVelocity[offset];

    if (movement == SHORT_MAX)
    {
        movement = sMellowIdleXVelocity[0];
        offset = 0;
    }

    pSprite->work2 = offset + 1;
    pSprite->xPosition += movement;

    if (pSprite->work2 == 1 || pSprite->work2 == ARRAY_SIZE(sMellowIdleXVelocity) / 2 + 1)
    {
        if (pSprite->drawOrder == 3)
            pSprite->drawOrder = 6;
        else
            pSprite->drawOrder = 3;
    }

    // Detect samus
    if (SpriteUtilCheckSamusNearSpriteLeftRight(BLOCK_SIZE * 5, BLOCK_SIZE * 4 + QUARTER_BLOCK_SIZE) != NSLR_OUT_OF_RANGE)
    {
        pSprite->pose = MELLOW_POSE_MOVE_INIT;
        pSprite->pOam = sMellowOam_SamusDetected;
        pSprite->animationDurationCounter = 0;
        pSprite->currentAnimationFrame = 0;

        pSprite->bgPriority = BGCNT_GET_PRIORITY(gIoRegistersBackup.BG1CNT);
        pSprite->drawOrder = 3;
    }
}

/**
 * @brief 25088 | 48 | Handles the mellow fleeing
 * 
 * @param pSprite Sprite data pointer
 */
static void MellowFleeing(struct SpriteData* pSprite)
{
    u8 rng;
    s16 movement;

    rng = gSpriteRng / 4;
    movement = rng + EIGHTH_BLOCK_SIZE;
    if (pSprite->work2 < ARRAY_SIZE(sMellowIdleXVelocity) / 2)
        pSprite->xPosition += movement;
    else
        pSprite->xPosition -= movement;

    movement = rng + PIXEL_SIZE;
    if (pSprite->work3 < ARRAY_SIZE(sMellowIdleYVelocity) / 2)
        pSprite->yPosition += movement;
    else
        pSprite->yPosition -= movement;
}

/**
 * @brief 250d0 | 68 | Initializes a mellow sprite to be in samus detected behavior
 * 
 * @param pSprite Sprite data pointer
 */
static void MellowMoveInit(struct SpriteData* pSprite)
{
    pSprite->work1 = 0;
    pSprite->work2 = 1;
    pSprite->work0 = 0;
    pSprite->work3 = 1;

    pSprite->xPositionSpawn = 0;
    pSprite->pose = MELLOW_POSE_MOVE;
    pSprite->scaling = CONVERT_SECONDS(.5f + 1.f / 30);

    SpriteUtilMakeSpriteFaceSamusDirection();
    if (pSprite->yPosition > gSamusData.yPosition + gSamusPhysics.drawDistanceTop)
        pSprite->status &= ~SPRITE_STATUS_FACING_DOWN;
    else
        pSprite->status |= SPRITE_STATUS_FACING_DOWN;
}

#ifdef NON_MATCHING
static void MellowMove(struct SpriteData* pSprite)
{
    // https://decomp.me/scratch/o7G5U
    
    struct SpriteData* pMellow;
    u8 offset;

    u8 limit;
    u8 flip;
    
    u16 spriteY;
    u16 spriteX;
    u16 spriteTop;
    u16 spriteBottom;
    u16 spriteLeft;
    u16 spriteRight;
    u32 newPos;
    u8 ramSlot;

    flip = FALSE;
    offset = QUARTER_BLOCK_SIZE + EIGHTH_BLOCK_SIZE;

    spriteTop = pSprite->yPosition - offset;
    spriteBottom = pSprite->yPosition + offset;
    spriteLeft = pSprite->xPosition - offset;
    spriteRight = pSprite->xPosition + offset;

    ramSlot = pSprite->primarySpriteRamSlot + 1;
    
    for (pMellow = gSpriteData + ramSlot; pMellow < gSpriteData + MAX_AMOUNT_OF_SPRITES; pMellow++)
    {
        if (!(pMellow->status & SPRITE_STATUS_EXISTS))
            continue;

        if (pMellow->samusCollision != SSC_MELLOW)
            continue;

        spriteY = pMellow->yPosition;
        spriteX = pMellow->xPosition;
        if (spriteBottom > spriteY - offset && spriteTop < spriteY + offset &&
            spriteRight > spriteX - offset && spriteLeft < spriteX + offset)
        {
            if (pMellow->freezeTimer == 0)
            {
                if (pSprite->yPosition > spriteY)
                    pMellow->yPosition -= PIXEL_SIZE;
                else
                    pMellow->yPosition += PIXEL_SIZE;

                if (pSprite->xPosition > spriteX)
                    pMellow->xPosition -= PIXEL_SIZE;
                else
                    pMellow->xPosition += PIXEL_SIZE;
            }
            break;
        }
    }

    if (pSprite->roomSlot == 0x88)
    {
        limit = 0x14;
        offset = gSpriteRng + 0x1E;
        spriteY = gSamusData.yPosition - (gSpriteRng * 4 + 0xDC);
        spriteX = gSamusData.xPosition;

        switch (pSprite->xPositionSpawn)
        {
            case 1:
                spriteY -= BLOCK_SIZE * 2;
                if (pSprite->status & SPRITE_STATUS_FACING_RIGHT)
                    spriteX += BLOCK_SIZE * 4;
                else
                    spriteX -= BLOCK_SIZE * 4;
                break;

            case 3:
                spriteY += BLOCK_SIZE / 2;
                if (pSprite->status & SPRITE_STATUS_FACING_RIGHT)
                    spriteX -= BLOCK_SIZE * 4;
                else
                    spriteX += BLOCK_SIZE * 4;
                break;
        }
    }
    else
    {
        spriteY = gSamusData.yPosition + gSamusPhysics.drawDistanceTop;
        spriteX = gSamusData.xPosition;
        limit = 0x1E;
        offset = 0x28;

        switch (pSprite->xPositionSpawn)
        {
            case 1:
                spriteY -= BLOCK_SIZE / 2;
                if (pSprite->status & SPRITE_STATUS_FACING_RIGHT)
                    spriteX += BLOCK_SIZE - BLOCK_SIZE / 4;
                else
                    spriteX -= BLOCK_SIZE - BLOCK_SIZE / 4;
                break;

            case 3:
                spriteY += BLOCK_SIZE / 2;
                if (pSprite->status & SPRITE_STATUS_FACING_RIGHT)
                    spriteX -= BLOCK_SIZE - BLOCK_SIZE / 4;
                else
                    spriteX += BLOCK_SIZE - BLOCK_SIZE / 4;
                break;
        }
    }

    if (pSprite->status & SPRITE_STATUS_FACING_RIGHT)
    {
        if (pSprite->work1 == 0)
        {
            if (pSprite->xPosition <= spriteX - 4)
            {
                if (pSprite->work2 < offset)
                    pSprite->work2++;

                pSprite->xPosition += (pSprite->work2 >> 2);
            }
            else
                pSprite->work1 = pSprite->work2;
        }
        else
        {
            if (--pSprite->work1 != 0)
                pSprite->xPosition += (pSprite->work1 >> 2);
            else
                flip++;
        }
    }
    else
    {
        if (pSprite->work1 == 0)
        {
            if (pSprite->xPosition < spriteX + 4)
                pSprite->work1 = pSprite->work2;
            else
            {
                if (pSprite->work2 < offset)
                    pSprite->work2++;

                offset = (pSprite->work2 >> 2);
                newPos = pSprite->xPosition - offset;
                if (newPos & 0x8000)
                {
                    flip++;
                    pSprite->work1 = 0;
                    pSprite->xPosition = 0;
                }
                else
                    pSprite->xPosition = newPos;
            }
        }
        else
        {
            if (--pSprite->work1 != 0)
            {
                offset = (pSprite->work1 >> 2);
                newPos = pSprite->xPosition - offset;
                if (newPos & 0x8000)
                {
                    flip++;
                    pSprite->work1 = 0x0;
                    pSprite->xPosition = 0x0;
                }
                else
                    pSprite->xPosition = newPos;
            }
            else
                flip++;
        }
    }

    if (flip)
    {
        pSprite->status ^= SPRITE_STATUS_FACING_RIGHT;
        pSprite->work2 = 1;
        pSprite->xPositionSpawn++;
        if (pSprite->xPositionSpawn > 3)
            pSprite->xPositionSpawn = 0;
    }

    flip = FALSE;
    
    if (pSprite->status & SPRITE_STATUS_FACING_DOWN)
    {
        if (pSprite->work0 == 0)
        {
            if (pSprite->yPosition > spriteY - 4)
                pSprite->work0 = pSprite->work3;
            else
            {
                if (pSprite->work3 < limit)
                    pSprite->work3++;

                pSprite->yPosition += (pSprite->work3 >> 2);
            }
        }
        else
        {
            if (--pSprite->work0 != 0)
                pSprite->yPosition += (pSprite->work0 >> 2);
            else
                flip++;
        }
    }
    else
    {
        if (pSprite->work0 == 0)
        {
            if (pSprite->yPosition < spriteY + 4)
                pSprite->work0 = pSprite->work3;
            else
            {
                if (pSprite->work3 < limit)
                    pSprite->work3++;

                offset = (pSprite->work3 >> 2);
                newPos = pSprite->yPosition - offset;
                if (newPos & 0x8000)
                {
                    flip++;
                    pSprite->work0 = 0;
                    pSprite->yPosition = 0;
                }
                else
                    pSprite->yPosition = newPos;
            }
        }
        else
        {
            if (--pSprite->work0 != 0)
            {
                offset = (pSprite->work0 >> 2);
                newPos = pSprite->yPosition - offset;
                if (newPos & 0x8000)
                {
                    flip++;
                    pSprite->work0 = 0;
                    pSprite->yPosition = 0;
                }
                else
                    pSprite->yPosition = newPos;
            }
            else
                flip++;
        }
    }

    if (flip)
    {
        pSprite->status ^= SPRITE_STATUS_FACING_DOWN;
        ///pSprite->work3 = 1;
        gCurrentSprite.work3 = 1;
    }

    pSprite->scaling--;
    if (pSprite->scaling == 0)
    {
        pSprite->scaling = 32;
        if (pSprite->status & SPRITE_STATUS_ONSCREEN)
            SoundPlayNotAlreadyPlaying(SOUND_MELLOW_MOVING);
    }
}
#else
NAKED_FUNCTION
static void MellowMove(struct SpriteData* pSprite)
{
    asm(" \n\
    push {r4, r5, r6, r7, lr} \n\
    mov r7, sl \n\
    mov r6, sb \n\
    mov r5, r8 \n\
    push {r5, r6, r7} \n\
    sub sp, #8 \n\
    mov ip, r0 \n\
    movs r0, #0 \n\
    str r0, [sp] \n\
    movs r5, #0x18 \n\
    mov r2, ip \n\
    ldrh r1, [r2, #2] \n\
    add r0, r1, #0 \n\
    sub r0, #0x18 \n\
    lsl r0, r0, #0x10 \n\
    lsr r0, r0, #0x10 \n\
    str r0, [sp, #4] \n\
    add r1, #0x18 \n\
    lsl r1, r1, #0x10 \n\
    lsr r1, r1, #0x10 \n\
    mov sl, r1 \n\
    ldrh r1, [r2, #4] \n\
    add r0, r1, #0 \n\
    sub r0, #0x18 \n\
    lsl r0, r0, #0x10 \n\
    lsr r0, r0, #0x10 \n\
    mov r8, r0 \n\
    add r1, #0x18 \n\
    lsl r1, r1, #0x10 \n\
    lsr r7, r1, #0x10 \n\
    mov r0, ip \n\
    add r0, #0x23 \n\
    ldrb r0, [r0] \n\
    add r0, #1 \n\
    lsl r0, r0, #0x18 \n\
    lsr r0, r0, #0x18 \n\
    lsl r1, r0, #3 \n\
    sub r1, r1, r0 \n\
    lsl r1, r1, #3 \n\
    ldr r0, lbl_080251dc @ =gSpriteData \n\
    add r2, r1, r0 \n\
    movs r1, #0xa8 \n\
    lsl r1, r1, #3 \n\
    add r0, r0, r1 \n\
    ldr r1, lbl_080251e0 @ =gSamusData \n\
    mov sb, r1 \n\
    cmp r2, r0 \n\
    bhs lbl_08025202 \n\
    add r3, r2, #0 \n\
    add r3, #0x25 \n\
lbl_0802519c: \n\
    ldrh r1, [r2] \n\
    movs r0, #1 \n\
    and r0, r1 \n\
    cmp r0, #0 \n\
    beq lbl_080251f8 \n\
    ldrb r0, [r3] \n\
    cmp r0, #0x12 \n\
    bne lbl_080251f8 \n\
    ldrh r6, [r2, #2] \n\
    ldrh r4, [r2, #4] \n\
    sub r0, r6, r5 \n\
    cmp sl, r0 \n\
    ble lbl_080251f8 \n\
    add r0, r6, r5 \n\
    ldr r1, [sp, #4] \n\
    cmp r1, r0 \n\
    bge lbl_080251f8 \n\
    sub r0, r4, r5 \n\
    cmp r7, r0 \n\
    ble lbl_080251f8 \n\
    add r0, r4, r5 \n\
    cmp r8, r0 \n\
    bge lbl_080251f8 \n\
    ldrb r0, [r3, #0xb] \n\
    cmp r0, #0 \n\
    bne lbl_08025202 \n\
    mov r1, ip \n\
    ldrh r0, [r1, #2] \n\
    cmp r0, r6 \n\
    bls lbl_080251e4 \n\
    sub r0, r6, #4 \n\
    b lbl_080251e6 \n\
    .align 2, 0 \n\
lbl_080251dc: .4byte gSpriteData \n\
lbl_080251e0: .4byte gSamusData \n\
lbl_080251e4: \n\
    add r0, r6, #4 \n\
lbl_080251e6: \n\
    strh r0, [r2, #2] \n\
    mov r1, ip \n\
    ldrh r0, [r1, #4] \n\
    cmp r0, r4 \n\
    bhi lbl_08025240 \n\
    ldrh r0, [r2, #4] \n\
    add r0, #4 \n\
    strh r0, [r2, #4] \n\
    b lbl_08025202 \n\
lbl_080251f8: \n\
    add r3, #0x38 \n\
    add r2, #0x38 \n\
    ldr r0, lbl_08025238 @ =gSpritesetSpritesID \n\
    cmp r2, r0 \n\
    blo lbl_0802519c \n\
lbl_08025202: \n\
    mov r2, ip \n\
    ldrb r0, [r2, #0x1e] \n\
    cmp r0, #0x88 \n\
    bne lbl_08025298 \n\
    movs r7, #0x14 \n\
    ldr r1, lbl_0802523c @ =gSpriteRng \n\
    ldrb r0, [r1] \n\
    add r0, #0x1e \n\
    lsl r0, r0, #0x18 \n\
    lsr r5, r0, #0x18 \n\
    ldrb r1, [r1] \n\
    lsl r1, r1, #2 \n\
    add r1, #0xdc \n\
    mov r2, sb \n\
    ldrh r0, [r2, #0x14] \n\
    sub r0, r0, r1 \n\
    lsl r0, r0, #0x10 \n\
    lsr r6, r0, #0x10 \n\
    ldrh r4, [r2, #0x12] \n\
    mov r1, ip \n\
    ldrh r0, [r1, #8] \n\
    cmp r0, #1 \n\
    beq lbl_08025248 \n\
    cmp r0, #3 \n\
    beq lbl_08025270 \n\
    b lbl_08025304 \n\
    .align 2, 0 \n\
lbl_08025238: .4byte gSpritesetSpritesID \n\
lbl_0802523c: .4byte gSpriteRng \n\
lbl_08025240: \n\
    ldrh r0, [r2, #4] \n\
    sub r0, #4 \n\
    strh r0, [r2, #4] \n\
    b lbl_08025202 \n\
lbl_08025248: \n\
    add r0, r6, #0 \n\
    sub r0, #0x80 \n\
    lsl r0, r0, #0x10 \n\
    lsr r6, r0, #0x10 \n\
    mov r2, ip \n\
    ldrh r1, [r2] \n\
    movs r0, #0x80 \n\
    lsl r0, r0, #2 \n\
    and r0, r1 \n\
    cmp r0, #0 \n\
    beq lbl_08025266 \n\
    movs r1, #0x80 \n\
    lsl r1, r1, #1 \n\
    add r0, r4, r1 \n\
    b lbl_08025300 \n\
lbl_08025266: \n\
    ldr r2, lbl_0802526c @ =0xffffff00 \n\
    add r0, r4, r2 \n\
    b lbl_08025300 \n\
    .align 2, 0 \n\
lbl_0802526c: .4byte 0xffffff00 \n\
lbl_08025270: \n\
    add r0, r6, #0 \n\
    add r0, #0x20 \n\
    lsl r0, r0, #0x10 \n\
    lsr r6, r0, #0x10 \n\
    mov r0, ip \n\
    ldrh r1, [r0] \n\
    movs r0, #0x80 \n\
    lsl r0, r0, #2 \n\
    and r0, r1 \n\
    cmp r0, #0 \n\
    beq lbl_08025290 \n\
    ldr r1, lbl_0802528c @ =0xffffff00 \n\
    add r0, r4, r1 \n\
    b lbl_08025300 \n\
    .align 2, 0 \n\
lbl_0802528c: .4byte 0xffffff00 \n\
lbl_08025290: \n\
    movs r2, #0x80 \n\
    lsl r2, r2, #1 \n\
    add r0, r4, r2 \n\
    b lbl_08025300 \n\
lbl_08025298: \n\
    ldr r0, lbl_080252c0 @ =gSamusPhysics \n\
    add r0, #0x70 \n\
    ldrh r0, [r0] \n\
    mov r1, sb \n\
    ldrh r1, [r1, #0x14] \n\
    add r0, r0, r1 \n\
    lsl r0, r0, #0x10 \n\
    lsr r6, r0, #0x10 \n\
    mov r2, sb \n\
    ldrh r4, [r2, #0x12] \n\
    movs r7, #0x1e \n\
    movs r5, #0x28 \n\
    mov r1, ip \n\
    ldrh r0, [r1, #8] \n\
    cmp r0, #1 \n\
    beq lbl_080252c4 \n\
    cmp r0, #3 \n\
    beq lbl_080252e0 \n\
    b lbl_08025304 \n\
    .align 2, 0 \n\
lbl_080252c0: .4byte gSamusPhysics \n\
lbl_080252c4: \n\
    add r0, r6, #0 \n\
    sub r0, #0x20 \n\
    lsl r0, r0, #0x10 \n\
    lsr r6, r0, #0x10 \n\
    mov r2, ip \n\
    ldrh r1, [r2] \n\
    movs r0, #0x80 \n\
    lsl r0, r0, #2 \n\
    and r0, r1 \n\
    cmp r0, #0 \n\
    bne lbl_080252fc \n\
    add r0, r4, #0 \n\
    sub r0, #0x30 \n\
    b lbl_08025300 \n\
lbl_080252e0: \n\
    add r0, r6, #0 \n\
    add r0, #0x20 \n\
    lsl r0, r0, #0x10 \n\
    lsr r6, r0, #0x10 \n\
    mov r0, ip \n\
    ldrh r1, [r0] \n\
    movs r0, #0x80 \n\
    lsl r0, r0, #2 \n\
    and r0, r1 \n\
    cmp r0, #0 \n\
    beq lbl_080252fc \n\
    add r0, r4, #0 \n\
    sub r0, #0x30 \n\
    b lbl_08025300 \n\
lbl_080252fc: \n\
    add r0, r4, #0 \n\
    add r0, #0x30 \n\
lbl_08025300: \n\
    lsl r0, r0, #0x10 \n\
    lsr r4, r0, #0x10 \n\
lbl_08025304: \n\
    mov r2, ip \n\
    ldrh r1, [r2] \n\
    movs r0, #0x80 \n\
    lsl r0, r0, #2 \n\
    and r0, r1 \n\
    lsl r0, r0, #0x10 \n\
    lsr r3, r0, #0x10 \n\
    cmp r3, #0 \n\
    beq lbl_08025354 \n\
    add r2, #0x2d \n\
    ldrb r0, [r2] \n\
    cmp r0, #0 \n\
    bne lbl_0802533c \n\
    mov r0, ip \n\
    ldrh r1, [r0, #4] \n\
    sub r0, r4, #4 \n\
    cmp r1, r0 \n\
    bgt lbl_08025368 \n\
    mov r1, ip \n\
    add r1, #0x2e \n\
    ldrb r0, [r1] \n\
    cmp r0, r5 \n\
    bhs lbl_08025336 \n\
    add r0, #1 \n\
    strb r0, [r1] \n\
lbl_08025336: \n\
    ldrb r0, [r1] \n\
    lsr r0, r0, #2 \n\
    b lbl_08025348 \n\
lbl_0802533c: \n\
    sub r1, r0, #1 \n\
    strb r1, [r2] \n\
    lsl r0, r1, #0x18 \n\
    cmp r0, #0 \n\
    beq lbl_080253ca \n\
    lsr r0, r0, #0x1a \n\
lbl_08025348: \n\
    mov r1, ip \n\
    ldrh r1, [r1, #4] \n\
    add r0, r0, r1 \n\
    mov r2, ip \n\
    strh r0, [r2, #4] \n\
    b lbl_080253d4 \n\
lbl_08025354: \n\
    mov r2, ip \n\
    add r2, #0x2d \n\
    ldrb r0, [r2] \n\
    cmp r0, #0 \n\
    bne lbl_08025396 \n\
    mov r0, ip \n\
    ldrh r1, [r0, #4] \n\
    add r0, r4, #4 \n\
    cmp r1, r0 \n\
    bge lbl_08025372 \n\
lbl_08025368: \n\
    mov r0, ip \n\
    add r0, #0x2e \n\
    ldrb r0, [r0] \n\
    strb r0, [r2] \n\
    b lbl_080253d4 \n\
lbl_08025372: \n\
    mov r1, ip \n\
    add r1, #0x2e \n\
    ldrb r0, [r1] \n\
    cmp r0, r5 \n\
    bhs lbl_08025380 \n\
    add r0, #1 \n\
    strb r0, [r1] \n\
lbl_08025380: \n\
    ldrb r0, [r1] \n\
    lsr r5, r0, #2 \n\
    mov r1, ip \n\
    ldrh r0, [r1, #4] \n\
    sub r1, r0, r5 \n\
    movs r0, #0x80 \n\
    lsl r0, r0, #8 \n\
    and r0, r1 \n\
    cmp r0, #0 \n\
    bne lbl_080253b2 \n\
    b lbl_080253c4 \n\
lbl_08025396: \n\
    sub r1, r0, #1 \n\
    strb r1, [r2] \n\
    lsl r0, r1, #0x18 \n\
    cmp r0, #0 \n\
    beq lbl_080253ca \n\
    lsr r5, r0, #0x1a \n\
    mov r1, ip \n\
    ldrh r0, [r1, #4] \n\
    sub r1, r0, r5 \n\
    movs r0, #0x80 \n\
    lsl r0, r0, #8 \n\
    and r0, r1 \n\
    cmp r0, #0 \n\
    beq lbl_080253c4 \n\
lbl_080253b2: \n\
    ldr r0, [sp] \n\
    add r0, #1 \n\
    lsl r0, r0, #0x18 \n\
    lsr r0, r0, #0x18 \n\
    str r0, [sp] \n\
    strb r3, [r2] \n\
    mov r2, ip \n\
    strh r3, [r2, #4] \n\
    b lbl_080253d4 \n\
lbl_080253c4: \n\
    mov r0, ip \n\
    strh r1, [r0, #4] \n\
    b lbl_080253d4 \n\
lbl_080253ca: \n\
    ldr r0, [sp] \n\
    add r0, #1 \n\
    lsl r0, r0, #0x18 \n\
    lsr r0, r0, #0x18 \n\
    str r0, [sp] \n\
lbl_080253d4: \n\
    ldr r1, [sp] \n\
    cmp r1, #0 \n\
    beq lbl_08025404 \n\
    mov r2, ip \n\
    ldrh r0, [r2] \n\
    movs r2, #0x80 \n\
    lsl r2, r2, #2 \n\
    add r1, r2, #0 \n\
    eor r0, r1 \n\
    mov r1, ip \n\
    strh r0, [r1] \n\
    add r1, #0x2e \n\
    movs r0, #1 \n\
    strb r0, [r1] \n\
    mov r2, ip \n\
    ldrh r0, [r2, #8] \n\
    add r0, #1 \n\
    strh r0, [r2, #8] \n\
    lsl r0, r0, #0x10 \n\
    lsr r0, r0, #0x10 \n\
    cmp r0, #3 \n\
    bls lbl_08025404 \n\
    movs r0, #0 \n\
    strh r0, [r2, #8] \n\
lbl_08025404: \n\
    movs r0, #0 \n\
    str r0, [sp] \n\
    mov r2, ip \n\
    ldrh r1, [r2] \n\
    movs r0, #0x80 \n\
    lsl r0, r0, #3 \n\
    and r0, r1 \n\
    lsl r0, r0, #0x10 \n\
    lsr r3, r0, #0x10 \n\
    cmp r3, #0 \n\
    beq lbl_08025462 \n\
    add r2, #0x2c \n\
    ldrb r0, [r2] \n\
    cmp r0, #0 \n\
    bne lbl_0802544a \n\
    mov r0, ip \n\
    ldrh r1, [r0, #2] \n\
    sub r0, r6, #4 \n\
    cmp r1, r0 \n\
    ble lbl_08025436 \n\
    mov r0, ip \n\
    add r0, #0x2f \n\
    ldrb r0, [r0] \n\
    strb r0, [r2] \n\
    b lbl_080254e2 \n\
lbl_08025436: \n\
    mov r1, ip \n\
    add r1, #0x2f \n\
    ldrb r0, [r1] \n\
    cmp r0, r7 \n\
    bhs lbl_08025444 \n\
    add r0, #1 \n\
    strb r0, [r1] \n\
lbl_08025444: \n\
    ldrb r0, [r1] \n\
    lsr r0, r0, #2 \n\
    b lbl_08025456 \n\
lbl_0802544a: \n\
    sub r1, r0, #1 \n\
    strb r1, [r2] \n\
    lsl r0, r1, #0x18 \n\
    cmp r0, #0 \n\
    beq lbl_080254e8 \n\
    lsr r0, r0, #0x1a \n\
lbl_08025456: \n\
    mov r1, ip \n\
    ldrh r1, [r1, #2] \n\
    add r0, r0, r1 \n\
    mov r2, ip \n\
    strh r0, [r2, #2] \n\
    b lbl_080254e2 \n\
lbl_08025462: \n\
    mov r4, ip \n\
    add r4, #0x2c \n\
    ldrb r0, [r4] \n\
    add r2, r0, #0 \n\
    cmp r2, #0 \n\
    bne lbl_080254b0 \n\
    mov r0, ip \n\
    ldrh r1, [r0, #2] \n\
    add r0, r6, #4 \n\
    cmp r1, r0 \n\
    bge lbl_08025482 \n\
    mov r0, ip \n\
    add r0, #0x2f \n\
    ldrb r0, [r0] \n\
    strb r0, [r4] \n\
    b lbl_080254e2 \n\
lbl_08025482: \n\
    mov r1, ip \n\
    add r1, #0x2f \n\
    ldrb r0, [r1] \n\
    cmp r0, r7 \n\
    bhs lbl_08025490 \n\
    add r0, #1 \n\
    strb r0, [r1] \n\
lbl_08025490: \n\
    ldrb r0, [r1] \n\
    lsr r5, r0, #2 \n\
    mov r1, ip \n\
    ldrh r0, [r1, #2] \n\
    sub r1, r0, r5 \n\
    movs r0, #0x80 \n\
    lsl r0, r0, #8 \n\
    and r0, r1 \n\
    cmp r0, #0 \n\
    beq lbl_080254d8 \n\
    movs r0, #1 \n\
    str r0, [sp] \n\
    strb r2, [r4] \n\
    mov r1, ip \n\
    strh r2, [r1, #2] \n\
    b lbl_080254e2 \n\
lbl_080254b0: \n\
    sub r1, r0, #1 \n\
    strb r1, [r4] \n\
    lsl r0, r1, #0x18 \n\
    cmp r0, #0 \n\
    beq lbl_080254de \n\
    lsr r5, r0, #0x1a \n\
    mov r1, ip \n\
    ldrh r0, [r1, #2] \n\
    sub r1, r0, r5 \n\
    movs r0, #0x80 \n\
    lsl r0, r0, #8 \n\
    and r0, r1 \n\
    cmp r0, #0 \n\
    beq lbl_080254d8 \n\
    movs r2, #1 \n\
    str r2, [sp] \n\
    strb r3, [r4] \n\
    mov r0, ip \n\
    strh r3, [r0, #2] \n\
    b lbl_080254e2 \n\
lbl_080254d8: \n\
    mov r2, ip \n\
    strh r1, [r2, #2] \n\
    b lbl_080254e2 \n\
lbl_080254de: \n\
    movs r0, #1 \n\
    str r0, [sp] \n\
lbl_080254e2: \n\
    ldr r1, [sp] \n\
    cmp r1, #0 \n\
    beq lbl_080254fe \n\
lbl_080254e8: \n\
    mov r2, ip \n\
    ldrh r0, [r2] \n\
    movs r2, #0x80 \n\
    lsl r2, r2, #3 \n\
    add r1, r2, #0 \n\
    eor r0, r1 \n\
    mov r1, ip \n\
    strh r0, [r1] \n\
    add r1, #0x2f \n\
    movs r0, #1 \n\
    strb r0, [r1] \n\
lbl_080254fe: \n\
    mov r2, ip \n\
    ldrh r0, [r2, #0x12] \n\
    sub r0, #1 \n\
    strh r0, [r2, #0x12] \n\
    lsl r0, r0, #0x10 \n\
    cmp r0, #0 \n\
    bne lbl_08025522 \n\
    movs r0, #0x20 \n\
    strh r0, [r2, #0x12] \n\
    ldrh r1, [r2] \n\
    movs r0, #2 \n\
    and r0, r1 \n\
    cmp r0, #0 \n\
    beq lbl_08025522 \n\
    movs r0, #0xaf \n\
    lsl r0, r0, #1 \n\
    bl SoundPlayNotAlreadyPlaying \n\
lbl_08025522: \n\
    add sp, #8 \n\
    pop {r3, r4, r5} \n\
    mov r8, r3 \n\
    mov sb, r4 \n\
    mov sl, r5 \n\
    pop {r4, r5, r6, r7} \n\
    pop {r0} \n\
    bx r0 \n\
    ");
}
#endif

void Hive(void)
{
    if (gCurrentSprite.freezeTimer != 0)
    {
        SpriteUtilUpdateFreezeTimer();
        SpriteUtilUpdateSecondarySpriteFreezeTimerOfCurrent(SSPRITE_HIVE_ROOTS, gCurrentSprite.primarySpriteRamSlot);
        gCurrentSprite.work0 = gCurrentSprite.freezeTimer;
        return;
    }

    if (SpriteUtilIsSpriteStunned())
        return;

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            HiveInit();
            break;

        case HIVE_POSE_PHASE_1:
            HivePhase1();
            break;

        case HIVE_POSE_PHASE_2:
            HivePhase2();
            break;

        case HIVE_POSE_PHASE_3:
            HivePhase3();
            break;

        case HIVE_POSE_DEAD:
            HiveDead();
            break;

        default:
            HiveDying();
    }
}

/**
 * @brief 255b8 | ac | Hive roots AI
 * 
 */
void HiveRoots(void)
{
    u8 hiveSlot;

    hiveSlot = gCurrentSprite.primarySpriteRamSlot;
    gCurrentSprite.ignoreSamusCollisionTimer = DELTA_TIME;
    if (gSpriteData[hiveSlot].spriteId == PSPRITE_HIVE)
    {
        gCurrentSprite.paletteRow = gSpriteData[hiveSlot].paletteRow;
        if (gSpriteData[hiveSlot].health < GET_PSPRITE_HEALTH(gSpriteData[hiveSlot].spriteId) / 2 && gSpriteData[hiveSlot].freezeTimer == 0)
        {
            gCurrentSprite.status = 0;
            return;
        }
    }
    else
    {
        gCurrentSprite.status = 0;
        return;
    }

    if (gSpriteData[hiveSlot].status == 0)
    {
        gCurrentSprite.status = 0;
        return;
    }

    if (gCurrentSprite.freezeTimer != 0)
    {
        SpriteUtilUpdateFreezeTimer();
        return;
    }

    if (gCurrentSprite.pose == SPRITE_POSE_UNINITIALIZED)
        HiveRootsInit();

    HiveRootsIdle();
}

void Mellow(void)
{
    struct SpriteData* pSprite;

    pSprite = &gCurrentSprite;

    if (pSprite->properties & SP_DAMAGED)
    {
        pSprite->properties &= ~SP_DAMAGED;
        if (pSprite->status & SPRITE_STATUS_ONSCREEN)
            SoundPlayNotAlreadyPlaying(SOUND_MELLOW_DAMAGED);
    }
    
    if (pSprite->freezeTimer != 0)
    {
        SpriteUtilUpdateFreezeTimer();
        return;
    }

    if (SPRITE_GET_ISFT(*pSprite) > CONVERT_SECONDS(.15f) && pSprite->pose < SPRITE_POSE_DESTROYED)
    {
        if (pSprite->animationDurationCounter != 0)
            APPLY_DELTA_TIME_DEC(pSprite->animationDurationCounter);

        return;
    }

    switch (pSprite->pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            MellowInit(pSprite);
            break;

        case MELLOW_POSE_IDLE:
            MellowIdle(pSprite);
            break;

        case MELLOW_POSE_MOVE_INIT:
            MellowMoveInit(pSprite);

        case MELLOW_POSE_MOVE:
            MellowMove(pSprite);
            break;

        case MELLOW_POSE_FLEEING:
            MellowFleeing(pSprite);
            break;

        default:
            SpriteUtilSpriteDeath(DEATH_NORMAL, pSprite->yPosition, pSprite->xPosition, TRUE, PE_SPRITE_EXPLOSION_SMALL);
    }
}

void MellowSwarm(void)
{
    u8 count;
    struct SpriteData* pSprite;
    u8 collision;
    u16 x_pos;
    u16 y_pos;

    count = 0;
    gCurrentSprite.ignoreSamusCollisionTimer = DELTA_TIME;
    if (gCurrentSprite.pose == SPRITE_POSE_UNINITIALIZED)
    {
        if (EventFunction(EVENT_ACTION_CHECKING, EVENT_THREE_HIVES_DESTROYED))
        {
            gCurrentSprite.status = 0;
            return;
        }

        gCurrentSprite.status |= (SPRITE_STATUS_NOT_DRAWN | SPRITE_STATUS_IGNORE_PROJECTILES);
    
        gCurrentSprite.hitboxTop = -PIXEL_SIZE;
        gCurrentSprite.hitboxBottom = PIXEL_SIZE;
        gCurrentSprite.hitboxLeft = -PIXEL_SIZE;
        gCurrentSprite.hitboxRight = PIXEL_SIZE;

        gCurrentSprite.drawDistanceTop = SUB_PIXEL_TO_PIXEL(PIXEL_SIZE);
        gCurrentSprite.drawDistanceBottom = SUB_PIXEL_TO_PIXEL(PIXEL_SIZE);
        gCurrentSprite.drawDistanceHorizontal = SUB_PIXEL_TO_PIXEL(PIXEL_SIZE);

        gCurrentSprite.samusCollision = SSC_NONE;

        gCurrentSprite.pOam = sMellowOam_Idle;
        gCurrentSprite.currentAnimationFrame = 0;
        gCurrentSprite.animationDurationCounter = 0;

        gCurrentSprite.pose = MELLOW_SWARM_POSE_IDLE;

        if (SUB_PIXEL_TO_PIXEL(gSamusData.xPosition) - SUB_PIXEL_TO_PIXEL(gBg1XPosition) > SUB_PIXEL_TO_PIXEL(SCREEN_SIZE_X_SUB_PIXEL) / 2)
            gCurrentSprite.status |= SPRITE_STATUS_X_FLIP;

        gCurrentSprite.yPositionSpawn = 0xF0;

        if (gCurrentSprite.spriteId == PSPRITE_MELLOW_SWARM_HEALTH_BASED)
        {
            if (gEquipment.currentEnergy >= 400)
                gCurrentSprite.work2 = 15;
            else if (gEquipment.currentEnergy >= 300)
                gCurrentSprite.work2 = 12;
            else if (gEquipment.currentEnergy >= 200)
                gCurrentSprite.work2 = 9;
            else if (gEquipment.currentEnergy >= 100)
                gCurrentSprite.work2 = 6;
            else
                gCurrentSprite.work2 = 3;
        }
        else
        {
            gCurrentSprite.work2 = 5;
        }

        return;
    }

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_DOWN && gCurrentSprite.yPositionSpawn != 0x0)
    {
        gCurrentSprite.yPositionSpawn--;
    }
    else
    {
        collision = SSC_MELLOW;
        pSprite = gSpriteData;
        while (pSprite < gSpriteData + MAX_AMOUNT_OF_SPRITES)
        {
            if (pSprite->status & SPRITE_STATUS_EXISTS && pSprite->samusCollision == collision)
            {
                count++;
            }
            pSprite++;
        }

        if (!(gCurrentSprite.status & SPRITE_STATUS_FACING_DOWN))
        {
            if (count >= gCurrentSprite.work2)
            {
                gCurrentSprite.status |= SPRITE_STATUS_FACING_DOWN;
                return;
            }
        }
        else
        {
            if (count <= 0x13)
                gCurrentSprite.yPositionSpawn = 0xF0;
            else
                return;
        }

        if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
            x_pos = gSamusData.xPosition + (gSpriteRng * 0x20);
        else
            x_pos = gSamusData.xPosition + (gSpriteRng * -0x20);
        if (x_pos & 0x8000)
            x_pos = 0x0;
        y_pos = (u16)(gBg1YPosition - ((gSpriteRng * 0x2) + 0x10));
        SpriteSpawnPrimary(PSPRITE_MELLOW, 0x88, gCurrentSprite.spritesetGfxSlot, y_pos, x_pos, 0x0);
    }
}
