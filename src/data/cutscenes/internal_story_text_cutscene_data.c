#include "data/cutscenes/internal_story_text_cutscene_data.h"
#include "data/text_data.h"
#include "cutscenes/story_text_cutscene.h"

#include "constants/game_state.h"

const u16* const * const sStoryTextPointers[7] = {
    [LANGUAGE_JAPANESE] = (const u16* const * const)sJapaneseTextPointers_Story,
    [LANGUAGE_HIRAGANA] = (const u16* const * const)sHiraganaTextPointers_Story,
    [LANGUAGE_ENGLISH] = (const u16* const * const)sEnglishTextPointers_Story,
    #ifdef REGION_US_BETA
    [LANGUAGE_GERMAN] = (const u16* const * const)sGermanTextPointers_Story,
    [LANGUAGE_FRENCH] = (const u16* const * const)sFrenchTextPointers_Story,
    [LANGUAGE_ITALIAN] = (const u16* const * const)sItalianTextPointers_Story,
    [LANGUAGE_SPANISH] = (const u16* const * const)sSpanishTextPointers_Story
    #else // !REGION_US_BETA
    [LANGUAGE_GERMAN] = (const u16* const * const)sEnglishTextPointers_Story,
    [LANGUAGE_FRENCH] = (const u16* const * const)sEnglishTextPointers_Story,
    [LANGUAGE_ITALIAN] = (const u16* const * const)sEnglishTextPointers_Story,
    [LANGUAGE_SPANISH] = (const u16* const * const)sEnglishTextPointers_Story
    #endif // REGION_US_BETA
};

const struct CutsceneSubroutineData sStoryTextCutsceneSubroutineData[7] = {
    [0] = {
        .pFunction = StoryTextCutsceneInit,
        .oamLength = 0
    },
    [1] = {
        .pFunction = StoryTextCutsceneProcessText,
        .oamLength = 0
    },
    [2] = {
        .pFunction = StoryTextCutsceneSetVerticalOffset,
        .oamLength = 0
    },
    [3] = {
        .pFunction = StoryTextCutsceneFadeIn,
        .oamLength = 0
    },
    [4] = {
        .pFunction = StoryTextCutsceneCheckInput,
        .oamLength = 0
    },
    [5] = {
        .pFunction = StoryTextCutsceneFadeOut,
        .oamLength = 0
    },
    [6] = {
        .pFunction = StoryTextCutsceneEnd,
        .oamLength = 0
    },
};
