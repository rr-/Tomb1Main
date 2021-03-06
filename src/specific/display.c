#include "specific/display.h"

#include "3dsystem/3d_gen.h"
#include "global/const.h"
#include "global/types.h"
#include "global/vars.h"
#include "specific/hwr.h"
#include "specific/init.h"
#include "util.h"

#include <stdlib.h>

void SetupScreenSize()
{
    int32_t width = ((double)GameVidWidth * ScreenSizer);
    int32_t height = ((double)GameVidHeight * ScreenSizer);
    int32_t x = (GameVidWidth - width) / 2;
    int32_t y = (GameVidHeight - height) / 2;
    phd_InitWindow(
        x, y, width, height, VIEW_NEAR, VIEW_FAR, GAME_FOV, GameVidWidth,
        GameVidHeight, ScrPtr);
    DumpX = x;
    DumpY = y;
    DumpWidth = width;
    DumpHeight = height;
    if (!BackScreenSize) {
        BackScreenSize = 640 * 480;
        BackScreen = malloc(BackScreenSize);
        if (!BackScreen) {
            S_ExitSystem("ERROR: Could not allocate enough memory to run (0)");
        }
    }
}

void TempVideoAdjust(int32_t hi_res, double sizer)
{
    ModeLock = 1;
    if (hi_res == HiRes && sizer == ScreenSizer) {
        return;
    }

    if (IsHardwareRenderer) {
        HiRes = hi_res;
        HWR_SwitchResolution();
    } else {
        ScreenSizer = sizer;

        if (hi_res != HiRes) {
            if (HiRes == 2) {
                HiRes = 0;
                GameVidWidth = 320;
                GameVidHeight = 200;
            } else {
                HiRes = 2;
                GameVidWidth = 640;
                GameVidHeight = 480;
            }
        }

        SetupScreenSize();
    }
}

void TempVideoRemove()
{
    ModeLock = 0;
    if (GameHiRes == HiRes && GameSizer == ScreenSizer) {
        return;
    }

    if (IsHardwareRenderer) {
        HiRes = GameHiRes;
        HWR_SwitchResolution();
    } else {
        ScreenSizer = GameSizer;

        if (HiRes != GameHiRes) {
            if (HiRes == 2) {
                HiRes = 0;
                GameVidWidth = 320;
                GameVidHeight = 200;
            } else {
                HiRes = 2;
                GameVidWidth = 640;
                GameVidHeight = 480;
            }
        }

        SetupScreenSize();
    }
}

void S_NoFade()
{
    FadeValue = 0x100000;
    FadeLimit = 0x100000;
}

void S_FadeInInventory(int32_t fade)
{
    if (IsHardwareRenderer) {
        if (CurrentLevel == GF.title_level_num) {
            HWR_DownloadPicture();
        } else {
            HWR_CopyPicture();
        }
    } else if (BackScreen && BackScreenSize) {
        uint8_t *scrptr = ScrPtr;
        uint8_t *bkscrptr = BackScreen;
        for (int i = 0; i < GameVidWidth * GameVidHeight; i++) {
            *bkscrptr++ = *scrptr++;
        }
    }

    if (fade) {
        FadeValue = 0x100000;
        FadeLimit = 0x180000;
        FadeAdder = 0x8000;
    }
}

void S_FadeOutInventory(int32_t fade)
{
    if (fade) {
        FadeValue = 0x180000;
        FadeLimit = 0x100000;
        FadeAdder = -32768;
    }
}

void T1MInjectSpecificDisplay()
{
    INJECT(0x00416470, SetupScreenSize);
    INJECT(0x00416550, TempVideoAdjust);
    INJECT(0x00416B20, S_FadeInInventory);
    INJECT(0x00416BB0, S_FadeOutInventory);
}
