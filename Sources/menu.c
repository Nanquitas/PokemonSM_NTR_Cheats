#include "cheats.h"
#include "notes.h"

#define 	MOON_TID	0x00175E00
#define 	SUN_TID 	0x00164800

char	*builder_name = "Nanquitas";

void	my_menus(void)
{	
	u32 	tid;

	tid = get_tid_low();

	if (tid == MOON_TID)
		new_unselectable_entry("Pokemon Moon Plugin V1 Beta3");
	else if (tid == SUN_TID)
		new_unselectable_entry("Pokemon Sun Plugin V1 Beta3");
	else
	{
		new_unselectable_entry("!!! Unrecognized Title ID !!!");
		new_unselectable_entry("!!!  Contact the authors  !!!");
		return;
	}
	// Unlock stick and touch screen capabilities
	set_hid_address(0x10002000);
	
	new_spoiler("!!!   FAQ   !!!");
		new_separator();
		new_unselectable_entry("Press Y when the cursor is");
		new_unselectable_entry("yellow to find how to use");
		new_unselectable_entry("the selected cheat.");
		new_separator();
	exit_spoiler();
	// Menu declaration in pokemon_spawner.c
	pokemon_spawner_menu();
	new_spoiler("Battle cheats");
		new_spoiler("Speed Multiplier");
			new_radio_entry("Walk/Run Speed x0.5", speed_multiplier_x05);
			new_radio_entry("Walk/Run Speed x1.0", speed_multiplier_x1);
			new_radio_entry("Walk/Run Speed x1.375", speed_multiplier_x1375);
			new_radio_entry("Walk/Run Speed x1.5", speed_multiplier_x15);
			new_radio_entry("Walk/Run Speed x2.0", speed_multiplier_x2);
			new_radio_entry("Walk/Run Speed x2.5", speed_multiplier_x25);
		exit_spoiler();
		new_spoiler("Experience Modifier");
			new_toggle_entry("Exp Modifier:", exp_modifier, EXP_MODIFIER);
			new_separator();
			new_entry_index("Raise 1%", raise_1_percent, EXP_RAISE_ONE);
			new_entry_index("Raise 10%", raise_10_percent, EXP_RAISE_TEN);
			new_entry_index("Raise 100%", raise_100_percent, EXP_RAISE_HUNDRED);
			new_entry_index("Raise 1000%", raise_1000_percent, EXP_RAISE_THOUSAND);
			new_separator();
			update_exp_modifier();
		exit_spoiler();
		new_toggle_entry("Wild pokemons are shiny", wild_pokemon_shiny, WILD_POKEMON_SHINY);
		new_toggle_entry("100% Catch rate", always_catch, ALWAYS_CATCH);
		new_entry_note("Catch Trainer's Pokemon", catch_trainers_pokemon_note, catch_trainers_pokemon);
		new_entry_note("Rematch Trainers", rematch_trainers_note, rematch_trainers);
	exit_spoiler();
	new_spoiler("Items cheats");
		new_entry("Max Money", max_money);
		new_entry_note("All Z Crystals", z_crystals_note, all_z_crystals);
		new_entry_note("All TM / HM", all_tm_hm_note, get_all_tm_hm);
		new_entry_note("All items x950", all_items_note, all_items_x950);
		new_entry_note("All medicines", all_medicines_note, all_medicine);
		new_entry_note("All berries", all_berries_note, all_berries);
		new_entry_note("All male's clothes", all_clothes_note, all_clothes_male);
		new_entry_note("All female's clothes", all_clothes_note, all_clothes_female);
	exit_spoiler();
	new_spoiler("Egg cheats");
		new_toggle_entry("Receive egg from daycare", receive_egg_from_daycare, RECEIVE_EGG_FROM_DAYCARE);
		new_toggle_entry("Egg instant hatch", egg_instant_hatch, EGG_INSTANT_HATCH);
	exit_spoiler();
	new_spoiler("Utility");
		new_spoiler("QR Codes");
			new_toggle_entry("Remove wait time", remove_qr_wait_time, REMOVE_QR_WAIT_TIME);
			new_toggle_entry("Remove QR ban list", remove_qr_ban_list, REMOVE_QR_BAN_LIST);
			new_entry("QR Scan points x100", qr_scan_point_100);
		exit_spoiler();
		new_toggle_entry("No outlines", no_outlines, NO_OUTLINES);
		new_toggle_entry("Instant message", instant_messages, INSTANT_MESSAGES);
		new_entry_note("Walk through walls", walk_through_walls_note, walk_through_walls);
		new_toggle_entry("Rename any pokemon", rename_any_pokemon, RENAME_ANY_POKEMON);
		new_toggle_entry("Learn any TM / HM", learn_any_tm_hm, LEARN_ANY_TM_HM);
		new_entry_note("Teleporter", teleporter_note, save_slot_teleporter);
		new_entry_index_note("Access PC from Options", access_pc_note, pc_from_option, PC_FROM_OPTION);
	exit_spoiler();
	new_spoiler("Stats cheats");
		new_entry("Festival coins x9999999", festival_coin_9999999);
		new_entry("Poke Festival coins x9999999", poke_festival_coin_9999999);
		new_entry("Thumbs Ups x1500000", thumbsups_1500000);
		new_entry("Max Battle Points", max_battle_points);
	exit_spoiler();
	new_unselectable_entry("Special thanks to ymyn and");
	new_unselectable_entry("DarkFlare for the cheats !!!");
}



