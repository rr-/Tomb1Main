#include "3dsystem/3d_gen.h"
#include "3dsystem/phd_math.h"
#include "game/cinema.h"
#include "game/control.h"
#include "game/vars.h"
#include "util.h"

void CalculateCinematicCamera()
{
    PHD_VECTOR campos;
    PHD_VECTOR camtar;

    int16_t* ptr = &Cine[8 * CineFrame];
    int32_t tx = ptr[0];
    int32_t ty = ptr[1];
    int32_t tz = ptr[2];
    int32_t cx = ptr[3];
    int32_t cy = ptr[4];
    int32_t cz = ptr[5];
    int16_t fov = ptr[6];
    int16_t roll = ptr[7];

    int32_t c = phd_cos(Camera.target_angle);
    int32_t s = phd_sin(Camera.target_angle);

    camtar.x = Camera.pos.x + ((tx * c + tz * s) >> W2V_SHIFT);
    camtar.y = Camera.pos.y + ty;
    camtar.z = Camera.pos.z + ((tz * c - tx * s) >> W2V_SHIFT);
    campos.x = Camera.pos.x + ((cz * s + cx * c) >> W2V_SHIFT);
    campos.y = Camera.pos.y + cy;
    campos.z = Camera.pos.z + ((cz * c - cx * s) >> W2V_SHIFT);

    AlterFOV(fov);
    phd_LookAt(
        campos.x, campos.y, campos.z, camtar.x, camtar.y, camtar.z, roll);
}

void InGameCinematicCamera()
{
    CineFrame++;
    if (CineFrame >= NumCineFrames) {
        CineFrame = NumCineFrames - 1;
    }

    int16_t* ptr = &Cine[8 * CineFrame];
    int32_t tx = ptr[0];
    int32_t ty = ptr[1];
    int32_t tz = ptr[2];
    int32_t cx = ptr[3];
    int32_t cy = ptr[4];
    int32_t cz = ptr[5];
    int16_t fov = ptr[6];
    int16_t roll = ptr[7];

    int32_t c = phd_cos(CinematicPosition.y_rot);
    int32_t s = phd_sin(CinematicPosition.y_rot);

    Camera.target.x = CinematicPosition.x + ((c * tx + s * tz) >> 14);
    Camera.target.y = CinematicPosition.y + ty;
    Camera.target.z = CinematicPosition.z + ((c * tz - s * tx) >> 14);
    Camera.pos.x = CinematicPosition.x + ((s * cz + c * cx) >> 14);
    Camera.pos.y = CinematicPosition.y + cy;
    Camera.pos.z = CinematicPosition.z + ((c * cz - s * cx) >> 14);

    AlterFOV(fov);

    phd_LookAt(
        Camera.pos.x, Camera.pos.y, Camera.pos.z, Camera.target.x,
        Camera.target.y, Camera.target.z, roll);
    GetFloor(Camera.pos.x, Camera.pos.y, Camera.pos.z, &Camera.pos.room_number);
}

void T1MInjectGameCinema()
{
    INJECT(0x00411370, CalculateCinematicCamera);
    INJECT(0x004115F0, InGameCinematicCamera);
}