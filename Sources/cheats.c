#include "cheats.h"
#include "hook.h"
#include <string.h>

void    receive_egg_from_daycare(void)
{
    static int  state = 0;

    if (!state)
    {
        WRITEU32(0x00444A6C, 0xE3A01001);
        WRITEU32(0x00444A70, 0xE5C011E0);
        WRITEU32(0x00444A74, 0xEA00684B);
        state = 1;
    }
    else
    {
        WRITEU32(0x00444A6C, 0xE2800E1E);
        WRITEU32(0x00444A70, 0xE1D000D0);
        WRITEU32(0x00444A74, 0xE12FFF1E);
        state = 0;
    }
    update_status(state, RECEIVE_EGG_FROM_DAYCARE);
    disable_entry(RECEIVE_EGG_FROM_DAYCARE);
}

/* asm function */
void    hooked_egg_instant_hatch(void);

void    egg_instant_hatch(void)
{
    static int      state = 0;
    static t_hook   hook = {0};

    if (!state)
    {
        if (!hook.is_initialized)
            init_hook(&hook, 0x004919E0, (u32)hooked_egg_instant_hatch);
        enable_hook(&hook);
        state = 1;
    }
    else
    {
        disable_hook(&hook);
        state = 0;
    }
    update_status(state, EGG_INSTANT_HATCH);
    disable_entry(EGG_INSTANT_HATCH);
}


void    festival_coin_9999999(void)
{
    WRITEU32(0x33124D58, 0x0098967F);
}

void    poke_festival_coin_9999999(void)
{

    WRITEU32(0x33124D5C, 0x0098967F);
}

void    thumbsups_1500000(void)
{
    WRITEU32(0x33138B8C, 0x0016E360);
}

void    max_battle_points(void)
{
    u32 offset;

    offset = 0;
    if ( 0x00000000 != READU32(0x0067206C))
    {
        offset = READU32(0x0067206C + offset);
        offset = READU32(0x00000024 + offset);
        offset = READU32(0x00000004 + offset);
        WRITEU16(0x000037B0 + offset, 0x0000270F);
    }
}

