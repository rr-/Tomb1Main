#ifndef T1M_CONFIG_H
#define T1M_CONFIG_H

#include <stdint.h>

typedef enum {
    T1M_BL_TOP_LEFT = 0,
    T1M_BL_TOP_CENTER = 1,
    T1M_BL_TOP_RIGHT = 2,
    T1M_BL_BOTTOM_LEFT = 3,
    T1M_BL_BOTTOM_CENTER = 4,
    T1M_BL_BOTTOM_RIGHT = 5,
} T1M_BAR_LOCATION;

typedef enum {
    T1M_BC_GOLD = 0,
    T1M_BC_BLUE = 1,
    T1M_BC_GREY = 2,
    T1M_BC_RED = 3,
    T1M_BC_SILVER = 4,
    T1M_BC_GREEN = 5,
    T1M_BC_GOLD2 = 6,
    T1M_BC_BLUE2 = 7,
    T1M_BC_PINK = 8,
} T1M_BAR_COLOR;

typedef enum {
    T1M_BSM_DEFAULT = 0,
    T1M_BSM_FLASHING = 1,
    T1M_BSM_ALWAYS = 2,
} T1M_BAR_SHOW_MODE;

struct {
    int8_t disable_healing_between_levels;
    int8_t disable_medpacks;
    int8_t disable_magnums;
    int8_t disable_uzis;
    int8_t disable_shotgun;
    int8_t enable_enemy_healthbar;
    int8_t enable_enhanced_look;
    int8_t enable_enhanced_ui;
    int8_t enable_numeric_keys;
    int8_t enable_shotgun_flash;
    int8_t enable_cheats;
    int8_t healthbar_showing_mode;
    int8_t healthbar_location;
    int8_t healthbar_color;
    int8_t airbar_location;
    int8_t airbar_color;
    int8_t enemy_healthbar_location;
    int8_t enemy_healthbar_color;
    int8_t fix_end_of_level_freeze;
    int8_t fix_tihocan_secret_sound;
    int8_t fix_pyramid_secret_trigger;
    int8_t fix_hardcoded_secret_counts;
} T1MConfig;

int T1MReadConfig();

#endif