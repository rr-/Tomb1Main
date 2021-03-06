#include "game/traps/teeth_trap.h"

#include "game/collide.h"
#include "game/control.h"
#include "game/sphere.h"
#include "global/vars.h"

BITE_INFO Teeth1A = { -23, 0, -1718, 0 };
BITE_INFO Teeth1B = { 71, 0, -1718, 1 };
BITE_INFO Teeth2A = { -23, 10, -1718, 0 };
BITE_INFO Teeth2B = { 71, 10, -1718, 1 };
BITE_INFO Teeth3A = { -23, -10, -1718, 0 };
BITE_INFO Teeth3B = { 71, -10, -1718, 1 };

void SetupTeethTrap(OBJECT_INFO *obj)
{
    obj->control = TeethTrapControl;
    obj->collision = TrapCollision;
    obj->save_flags = 1;
    obj->save_anim = 1;
}

// original name: TeethTrap
void TeethTrapControl(int16_t item_num)
{
    ITEM_INFO *item = &Items[item_num];
    if (TriggerActive(item)) {
        item->goal_anim_state = TT_NASTY;
        if (item->touch_bits && item->current_anim_state == TT_NASTY) {
            LaraItem->hit_points -= TEETH_TRAP_DAMAGE;
            LaraItem->hit_status = 1;
            BaddieBiteEffect(item, &Teeth1A);
            BaddieBiteEffect(item, &Teeth1B);
            BaddieBiteEffect(item, &Teeth2A);
            BaddieBiteEffect(item, &Teeth2B);
            BaddieBiteEffect(item, &Teeth3A);
            BaddieBiteEffect(item, &Teeth3B);
        }
    } else {
        item->goal_anim_state = TT_NICE;
    }
    AnimateItem(item);
}
