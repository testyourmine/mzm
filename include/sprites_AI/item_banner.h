#ifndef ITEM_BANNER_AI_H
#define ITEM_BANNER_AI_H

#include "types.h"

// Item banner

#define ITEM_BANNER_POSE_GFX_INIT 0x8
#define ITEM_BANNER_POSE_POP_UP 0x9
#define ITEM_BANNER_POSE_STATIC 0x23
#define ITEM_BANNER_POSE_REMOVAL_INIT 0x24
#define ITEM_BANNER_POSE_REMOVAL_ANIMATION 0x25

void ItemBanner(void);
void SaveYesNoCursor(void);

#endif /* ITEM_BANNER_AI_H* */