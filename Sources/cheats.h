#ifndef CHEATS_H
#define CHEATS_H

#include "plugin.h"

enum
{
    POKESPAWNER,
    POKEINIT,
    RAISE_SPAWN_ID_ONE,
    RAISE_SPAWN_ID_TEN,
    RAISE_SPAWN_ID_HUNDRED,
    RAISE_SPAWN_LEVEL_ONE,
    RAISE_SPAWN_LEVEL_TEN,
    RESET_SPAWN_LEVEL,

    WALK_THROUGH_WALLS,
    ALWAYS_CATCH,
    RENAME_ANY_POKEMON,
    INSTANT_MESSAGES,
    NO_OUTLINES,
    WILD_POKEMON_SHINY,
    RECEIVE_EGG_FROM_DAYCARE,
    EGG_INSTANT_HATCH,
    REMOVE_QR_WAIT_TIME,
    REMOVE_QR_BAN_LIST,
    LEARN_ANY_TM_HM,
    EXP_MODIFIER,
    EXP_RAISE_ONE,
    EXP_RAISE_TEN,
    EXP_RAISE_HUNDRED,
    EXP_RAISE_THOUSAND,
    PC_FROM_OPTION

} e_identifiers;

/*
** helpers.c
*/

void    disable_entry(int identifier);
void    update_status(int state, int identifier);
void    new_entry_note(char *str, const char * const note, void (*function)(void));
void    new_entry_index(char *str, void (*function)(void), int identifier);
void    new_entry_index_note(char *str, const char * const note, void (*function)(void), int identifier);
void    new_toggle_entry(char *str, void (*function)(void), int identifier);
void    new_toggle_entry_note(char *str, char *note, void (*function)(void), int identifier);

/*
** battle_cheats.c
*/
void    update_exp_modifier(void);
void    exp_modifier(void);
void    raise_1_percent(void);
void    raise_10_percent(void);
void    raise_100_percent(void);
void    raise_1000_percent(void);

/*
** utility_cheats.c
*/

void    pc_from_option(void);


/*
** cheats.c
*/

void    max_money(void);
void    walk_through_walls(void);
void    all_z_crystals(void);
void    always_catch(void);
void    catch_trainers_pokemon(void);
void    rename_any_pokemon(void);
void    instant_messages(void);
void    no_outlines(void);
void    rematch_trainers(void);
void    wild_pokemon_shiny(void);
void    receive_egg_from_daycare(void);
void    egg_instant_hatch(void);
void    remove_qr_wait_time(void);
void    remove_qr_ban_list(void);
void    qr_scan_point_100(void);
void    festival_coin_9999999(void);
void    poke_festival_coin_9999999(void);
void    thumbsups_1500000(void);
void    max_battle_points(void);
void    learn_any_tm_hm(void);
void    get_all_tm_hm(void);
void    all_items_x950(void);
void    all_medicine(void);
void    all_berries(void);
void    all_clothes_male(void);
void    all_clothes_female(void);
void    speed_multiplier_x05(void);
void    speed_multiplier_x1(void);
void    speed_multiplier_x1375(void);
void    speed_multiplier_x15(void);
void    speed_multiplier_x2(void);
void    speed_multiplier_x25(void);
void    save_slot_teleporter(void);



/*
** pokemon_spawner.c
*/
void    raise_id_one(void);
void    raise_id_ten(void);
void    raise_id_hundred(void);
void    raise_level_one(void);
void    raise_level_ten(void);
void    reset_spawnlevel(void);
void    pokemon_spawner_menu(void);

#endif
