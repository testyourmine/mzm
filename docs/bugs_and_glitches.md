# Bugs and Glitches
These are known bugs and glitches in the game: code that clearly does not work as intended or was designed poorly. Some of them cause visible gameplay issues, while others are harmless. The bugs listed here can be fixed by compiling with the `BUGFIX` flag (bugs in the TODO section don't have a fix implemented yet). 


## Contents

- [Bugs](#bugs)
  - ["Ground" Dessgeegas always set the "Dessgeega long beam killed" event and unlock doors](#ground-dessgeegas-always-set-the-dessgeega-long-beam-killed-event-and-unlock-doors)
  - [Mother Brain block does not spawn when there are too many sprites](#mother-brain-block-does-not-spawn-when-there-are-too-many-sprites)
- [Oversights and Design Flaws](#oversights-and-design-flaws)
  - [Floating point math is used when fixed point could have been used](#floating-point-math-is-used-when-fixed-point-could-have-been-used)
- [Uninitialized Variables](#uninitialized-variables)
- [TODO](#todo)
  - [Bugs](#bugs-1)
  - [Oversights and Design Flaws](#oversights-and-design-flaws-1)


## Bugs

### "Ground" Dessgeegas always set the "Dessgeega long beam killed" event and unlock doors

Fix : Edit `DessgeegaDeath` in [dessgeega.c](https://github.com/metroidret/mzm/blob/master/src/sprites_AI/dessgeega.c) to check for the sprite id to run the event and door logic.

```c
#ifdef BUGFIX
if (gCurrentSprite.spriteId == PSPRITE_DESSGEEGA_AFTER_LONG_BEAM)
#endif
{
    // Set event every time a ground dessgeega is killed instead of checking for the sprite ID ?
    EventFunction(EVENT_ACTION_SETTING, EVENT_LONG_BEAM_DESSGEEGA_KILLED);
    // Unlock doors
    gDoorUnlockTimer = -ONE_THIRD_SECOND;
}
```

### Mother Brain block does not spawn when there are too many sprites

Whenever there are too many (24) active sprites in the Mother Brain room, the block that is meant to prevent Samus from leaving the Mother Brain fight fails to spawn. This happens because the block is its own independent sprite, and needs an additional free sprite slot to spawn. The code tries to spawn the block only once, and does not check if it was successfully spawned. The fight continues regardless, and the next Mother Brain pose is set.

**Fix:** Edit `MotherBrainSpawnBlock` in [mother_brain.c](../src/sprites_AI/mother_brain.c) to check if the block sprite was spawned successfully before changing to the next Mother Brain sprite pose. The `SpriteSpawnSecondary()` function returns `0xFF` if it failed to spawn the sprite. By not changing the pose, the game will keep trying to spawn the block until it succeeds. This usually happens just a few frames before the first attempt, so no side effects are noticeable in the Mother Brain fight.

```c
#ifdef BUGFIX
u8 blockSlot = SpriteSpawnSecondary(SSPRITE_MOTHER_BRAIN_BLOCK, 0, SPRITE_GFX_SLOT_SPECIAL,
    gCurrentSprite.primarySpriteRamSlot, yPosition, xPosition, 0);
if (blockSlot != UCHAR_MAX)
{
    gCurrentSprite.pose = MOTHER_BRAIN_PART_POSE_GLASS_STAGE_1;
    gCurrentSprite.status &= ~SPRITE_STATUS_IGNORE_PROJECTILES;
}
#else // !BUGFIX
SpriteSpawnSecondary(SSPRITE_MOTHER_BRAIN_BLOCK, 0, SPRITE_GFX_SLOT_SPECIAL,
    gCurrentSprite.primarySpriteRamSlot, yPosition, xPosition, 0);
gCurrentSprite.pose = MOTHER_BRAIN_PART_POSE_GLASS_STAGE_1;
gCurrentSprite.status &= ~SPRITE_STATUS_IGNORE_PROJECTILES;
#endif // BUGFIX
```

## Oversights and Design Flaws

#### Floating point math is used when fixed point could have been used

`PowerBombExplosion`:
```c
verticalAxis = gCurrentPowerBomb.semiMinorAxis * 4;
horizontalAxis = gCurrentPowerBomb.semiMinorAxis * 8;
#ifdef BUGFIX
verticalAxis = FixedMultiplication(verticalAxis, Q_8_8(0.95));
horizontalAxis = FixedMultiplication(horizontalAxis, Q_8_8(0.95));
#else // !BUGFIX
verticalAxis *= 0.95;
horizontalAxis *= 0.95;
#endif // BUGFIX
```
Could also do `verticalAxis * 19 / 20`

`ImagoCocoonSporeMove`:
```c
case IMAGO_COCOON_SPORE_PART_DIAG_RIGHT_UP:
    #ifdef BUGFIX
    movement = FixedMultiplication(movement, Q_8_8(0.8));
    #else // !BUGFIX
    movement *= 0.8; // 4 * 0.8 = 3.2
    #endif // BUGFIX
    gCurrentSprite.yPosition -= movement;
    gCurrentSprite.xPosition += movement;
    break;
```
Could also do `movement * 4 / 5`

`RidleyLandingShipLanding`:
```c
#ifdef BUGFIX
if (movement >= 2848 - FixedMultiplication(sRidleyLandingScrollingInfo[1].length, Q_8_8(2.f / 3)))
#else // !BUGFIX
if (movement >= 2848 - sRidleyLandingScrollingInfo[1].length / 1.5)
#endif // BUGFIX
{
    CUTSCENE_DATA.dispcnt |= sRidleyLandingPageData[2].bg;
    CutsceneStartBackgroundScrolling(sRidleyLandingScrollingInfo[1], sRidleyLandingPageData[2].bg);
}
```
Could also do `sRidleyLandingScrollingInfo[1].length * 2 / 3`

## Uninitialized Variables

| Variable | Function | File |
|----------|----------|------|
| `effect` | `SamusCheckSetEnvironmentalEffect` | [samus.c](../src/samus.c) |
| `stop` | `SamusShinesparking` | [samus.c](../src/samus.c) |
| `pEffectAnim` | `SamusUpdateGraphicsOam` | [samus.c](../src/samus.c) |
| `result` | `BlockSamusApplyScrewSpeedboosterDamageToEnvironment` | [block.c](../src/block.c) |
| `action` | `BgClipCheckOpeningHatch` | [bg_clip.c](../src/bg_clip.c) |
| `pDoor` | `ConnectionCheckAreaConnection` | [connection.c](../src/connection.c) |
| `dst` | `TextProcessStory` | [text.c](../src/text.c) |
| `tmp1`, `tmp2` | `MinimapDraw` | [minimap.c](../src/minimap.c) |
| `pActivation`, `pStatusActivation` | `StatusScreenGetSlotForNewItem` | [status_screen.c](../src/menus/status_screen.c) |
| `ptr` | `StatusScreenSetBeamsVisibility` | [status_screen.c](../src/menus/status_screen.c) |
| `ptr` | `StatusScreenSetSuitsVisibility` | [status_screen.c](../src/menus/status_screen.c) |
| `pActivation` | `StatusScreenToggleItem` | [status_screen.c](../src/menus/status_screen.c) |
| `src` | `TitleScreenTransferGroundGraphics` | [title_screen.c](../src/menus/title_screen.c) |
| `currSlot` | `unk_818cc` | [tourian_escape.c](../src/tourian_escape.c) |
| `diff` | `SramWriteChecked` | [sram.c](../src/sram/sram.c) |
| `updateTextAndEvents` | `BootDebugModeSubroutine` | [boot_debug.c](../src/menus/boot_debug.c) |
| `updateText` | `BootDebugSoundSubroutine` | [boot_debug.c](../src/menus/boot_debug.c) |


## TODO

### Bugs

- PowerBombExplosion doesn't check if out of bounds, which can lead to memory corruption
  - Fix: don't check collision with any blocks outside of the room
- Dying during a door transition (from lava) puts Samus in the no-clip state
  - Potential fixes: don't check lava damage during a door transition, or check the sub game mode value before incrementing it
- Sidehoppers and dessgeegas don't initialize the delay (stored in work1) for their first jump
  - Potential fixes: initialize work1 in SidehopperInit, or call SidehopperIdleInit
- Turning when the game tries to lock you in place for the fully powered suit cutscene allows you to control Samus
  - Potential fix: check lastWallTouchedMidAir first ([code](https://github.com/metroidret/mzm/blob/4d9b219990ad5cce9c35f495195fe6019fecbac1/src/samus.c#L6551-L6555))
- Bomb hover on frozen enemies ([video](https://youtu.be/UIK8YnT1sG4))
- Door clipping using frozen enemies ([video](https://www.youtube.com/watch?v=iMObZ5EbooE))
- Warping when Samus stands on multiple respawning enemies and kills one ([video](https://youtu.be/WfxkYSPTjWw))
- Killing Imago with pseudo screw softlocks the game
  - Fix: add a case in the AI for pseudo screw
- Frame perfect pause buffering on ziplines ignores collision
- Clipping into slopes ([video](https://www.youtube.com/watch?v=XiZRJesXHWw))
- Chozo statue refill glitch
- Collecting an item during a power bomb explosion allows Samus to move early
- "Stop enemy" clipdata prevents bomb jumping

### Oversights and Design Flaws

- Mecha Ridley's missiles can be kept alive after it dies, which get corrupted graphics from the message box
  - Potential fix: kill any missiles after mecha dies
- ClipdataConvertToCollision is copied to RAM, but the code immediately jumps to the code in ROM
  - The function has a switch statement which compiles as a jump table using the original ROM addresses
  - Potential fix: call ClipdataConvertToCollision directly instead of copying it to RAM
