#include "cheats.h"
#include "hook.h"
#include "manager.h"
#include <string.h>

void    speed_multiplier_x05(void)
{
    WRITEFLOAT(0x0039AF74, 0.5f);
}

void    speed_multiplier_x1(void)
{
    WRITEFLOAT(0x0039AF74, 1.0f);
}

void    speed_multiplier_x1375(void)
{
    WRITEFLOAT(0x0039AF74, 1.375f);
}

void    speed_multiplier_x15(void)
{
    if (any_is_pressed(KEY_CPAD) && is_pressed(KEY_B))
        WRITEFLOAT(0x0039AF74, 1.5f);
    else
        WRITEFLOAT(0x0039AF74, 1.0f);
}

void    speed_multiplier_x2(void)
{
    if (any_is_pressed(KEY_CPAD) && is_pressed(KEY_B))
        WRITEFLOAT(0x0039AF74, 2.0f);
    else
        WRITEFLOAT(0x0039AF74, 1.0f);
}

void    speed_multiplier_x25(void)
{
    if (any_is_pressed(KEY_CPAD) && is_pressed(KEY_B))
        WRITEFLOAT(0x0039AF74, 2.5f);
    else
        WRITEFLOAT(0x0039AF74, 1.0f);
}

/* asm function */
void    hooked_wild_shiny(void);
t_hook  wild_shiny_hook = {0};

void    wild_pokemon_shiny(void)
{
    static int  state = 0;

    if (!state)
    {
        if (!wild_shiny_hook.is_initialized)
            init_hook(&wild_shiny_hook, 0x0031835C, (u32)hooked_wild_shiny);
        enable_hook(&wild_shiny_hook);
        state = 1;
    }
    else
    {
        disable_hook(&wild_shiny_hook);
        state = 0;
    }
    update_status(state, WILD_POKEMON_SHINY);
    disable_entry(WILD_POKEMON_SHINY);
}

/* asm function */
void    hooked_always_catch(void);

void    always_catch(void)
{
    static int      state = 0;
    static t_hook   hook = {0};

    if (!state)
    {
        if (!hook.is_initialized)
            init_hook(&hook, 0x0048F1E0, (u32)hooked_always_catch);
        enable_hook(&hook);
        state = 1;
    }
    else
    {
        disable_hook(&hook);
        state = 0;
    }
    update_status(state, ALWAYS_CATCH);
    disable_entry(ALWAYS_CATCH);
}

/* asm function */
void    hooked_catch_trainers_pokemon(void);
t_hook  catch_trainers_pokemon_hook = {0};

void    catch_trainers_pokemon(void)
{
    if (is_pressed( BUTTON_ST + BUTTON_DU ))
    {
        if (!catch_trainers_pokemon_hook.is_initialized)
            init_hook(&catch_trainers_pokemon_hook, 0x002FE95C, (u32)hooked_catch_trainers_pokemon);
        enable_hook(&catch_trainers_pokemon_hook);
    }
    if (is_pressed( BUTTON_ST + BUTTON_DD ))
    {
        disable_hook(&catch_trainers_pokemon_hook);
    }
}

void    rematch_trainers(void)
{
    static int  state = 0;

    if (is_pressed(BUTTON_L))
    {
        WRITEU32(0x0049D200, 0xE3A00000);
        WRITEU32(0x0049D204, 0xE12FFF1E);
        state = 1;
    }
    else if (state)
    {
        state = 0;
        WRITEU32(0x0049D200, 0xE5911004);
        WRITEU32(0x0049D204, 0xE5900044);
    }
}

/* asm function */
void    hooked_experience_modifier(void);

static int  g_exp_modifier_value = 100;
static int  g_exp_modifier_state = 0;

int     multiply_exp(int exp)
{
    float   result;

    result = (float)exp * ((float)g_exp_modifier_value / 100.0f);
    return ((int)result);
}

void    update_exp_modifier(void)
{
    char    *buffer;
    char    temp[7] = {0};

    xsprintf(temp, " %d%%", g_exp_modifier_value);
    buffer = get_displayed_name(EXP_MODIFIER);
    reset_name(EXP_MODIFIER);
    if (!buffer)
        goto exit;
    strcat(buffer, temp);
    if (g_exp_modifier_state)
        strcat(buffer, " [On]");
    else
        strcat(buffer, " [Off]");
exit:
    return;
}

void    exp_modifier(void)
{
    static t_hook   hook = {0};

    if (!g_exp_modifier_state)
    {
        if (!hook.is_initialized)
            init_hook(&hook, 0x0048F1EC, (u32)hooked_experience_modifier);
        enable_hook(&hook);
        g_exp_modifier_state = 1;        
    }
    else
    {
        disable_hook(&hook);
        g_exp_modifier_state = 0;
    }
    update_exp_modifier();
    disable_entry(EXP_MODIFIER);
}

void    raise_1_percent(void)
{
    int     temp;

    temp = g_exp_modifier_value % 10;
    g_exp_modifier_value -= temp;
    temp++;
    if (temp > 9)
        temp = 0;
    g_exp_modifier_value += temp;
    update_exp_modifier();
    disable_entry(EXP_RAISE_ONE);
}

void    raise_10_percent(void)
{
    int     temp;

    temp = (g_exp_modifier_value / 10) % 10;
    g_exp_modifier_value -= (temp * 10);
    temp++;
    if (temp > 9)
        temp = 0;
    g_exp_modifier_value += (temp * 10);
    update_exp_modifier();
    disable_entry(EXP_RAISE_TEN);
}

void    raise_100_percent(void)
{
    int     temp;

    temp = (g_exp_modifier_value / 100) % 10;
    g_exp_modifier_value -= (temp * 100);
    temp++;
    if (temp > 9)
        temp = 0;
    g_exp_modifier_value += (temp * 100);
    update_exp_modifier();
    disable_entry(EXP_RAISE_HUNDRED);
}

void    raise_1000_percent(void)
{
    int     temp;

    temp = (g_exp_modifier_value / 1000) % 10;
    g_exp_modifier_value -= (temp * 1000);
    temp++;
    if (temp > 9)
        temp = 0;
    g_exp_modifier_value += (temp * 1000);
    update_exp_modifier();
    disable_entry(EXP_RAISE_THOUSAND);
}