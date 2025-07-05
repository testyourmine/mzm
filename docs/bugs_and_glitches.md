# Bugs and Glitches
These are known bugs and glitches in the game: code that clearly does not work as intended or was designed poorly. Some of them cause visible gameplay issues, while others are harmless. The bugs listed here can be fixed by compiling with the `BUGFIX` flag (bugs in the TODO section don't have a fix implemented yet). 


## Contents

- [Bugs](#bugs)
  - ["Ground" Dessgeegas always set the "Dessgeega long beam killed" event and unlock doors](#ground-dessgeegas-always-set-the-dessgeega-long-beam-killed-event-and-unlock-doors)
- [Uninitialized Variables](#uninitialized-variables)
- [Oversights and Design Flaws](#oversights-and-design-flaws)
  - [Floating point math is when fixed point could have been used](#floating-point-math-is-used-when-fixed-point-could-have-been-used)
- [TODO](#todo)
  - [Bugs](#bugs-1)
  - [Uninitialized Variables](#uninitialized-variables-1)
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


## Uninitialized Variables


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
- Mother Brain block not spawning when there are too many sprites ([code](https://github.com/metroidret/mzm/blob/4d9b219990ad5cce9c35f495195fe6019fecbac1/src/sprites_AI/mother_brain.c#L625-L626))
  - Potential fix: remove a cannon sprite from the right side of the room
- Killing Imago with pseudo screw softlocks the game
  - Fix: add a case in the AI for pseudo screw
- Frame perfect pause buffering on ziplines ignores collision
- Clipping into slopes ([video](https://www.youtube.com/watch?v=XiZRJesXHWw))
- Chozo statue refill glitch

### Uninitialized Variables
- [MinimapDraw](https://github.com/metroidret/mzm/blob/22dceb902f66667378076e5022e12ef89c5ccf3f/src/minimap.c#L680)
- [BlockSamusApplyScrewSpeedboosterDamageToEnvironment](https://github.com/metroidret/mzm/blob/22dceb902f66667378076e5022e12ef89c5ccf3f/src/block.c#L1053)
- [BootDebugModeSubroutine](https://github.com/metroidret/mzm/blob/22dceb902f66667378076e5022e12ef89c5ccf3f/src/menus/boot_debug.c#L1513)
- [BootDebugSoundSubroutine](https://github.com/metroidret/mzm/blob/22dceb902f66667378076e5022e12ef89c5ccf3f/src/menus/boot_debug.c#L1961)

### Oversights and Design Flaws

- Mecha Ridley's missiles can be kept alive after it dies, which get corrupted graphics from the message box
  - Potential fix: kill any missiles after mecha dies
