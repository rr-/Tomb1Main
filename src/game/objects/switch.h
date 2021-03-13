#ifndef T1M_GAME_OBJECTS_SWITCH_H
#define T1M_GAME_OBJECTS_SWITCH_H

#include "game/types.h"

typedef enum {
    SWITCH_STATE_OFF = 0,
    SWITCH_STATE_ON = 1,
    SWITCH_STATE_LINK = 2,
} SWITCH_STATE;

extern PHD_VECTOR Switch2Position;
extern int16_t Switch1Bounds[12];
extern int16_t Switch2Bounds[12];

void SetupSwitch1(OBJECT_INFO *obj);
void SetupSwitch2(OBJECT_INFO *obj);
void SwitchCollision(int16_t item_num, ITEM_INFO *lara_item, COLL_INFO *coll);
void SwitchCollision2(int16_t item_num, ITEM_INFO *lara_item, COLL_INFO *coll);
void SwitchControl(int16_t item_num);
int32_t SwitchTrigger(int16_t item_num, int16_t timer);

#endif
