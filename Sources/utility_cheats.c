#include "cheats.h"
#include "hook.h"

void    remove_qr_wait_time(void)
{
    static int state = 0;

    if (!state)
    {
        WRITEU32(0x0043DAA8, 0xE3A00000);
        state = 1;
    }
    else
    {
        WRITEU32(0x0043DAA8, 0xEBFEDB00);
        state = 0;
    }
    update_status(state, REMOVE_QR_WAIT_TIME);
    disable_entry(REMOVE_QR_WAIT_TIME);
}

void    remove_qr_ban_list(void)
{
    static int  state = 0;
    u32         offset = 0x005A3FF0;
    int         i;
    int         j;

    if (!state)
    {
        for (i = 0; i < 9; i++)
        {
            WRITEU32(offset, 0);
            offset += 4;
        }
        state = 1;
    }
    else
    {
        j = 0x311;
        for (i = 0; i < 18; i++)
        {
            WRITEU16(offset, j++);
            offset += 2;
        }
    }
    update_status(state, REMOVE_QR_BAN_LIST);
    disable_entry(REMOVE_QR_BAN_LIST);
}

void    qr_scan_point_100(void)
{
    u32 offset;

    if (READU32(0x0067206C) != 0)
    {
        offset = READU32(0x0067206C + offset);
        offset = READU32(0x00000024 + offset);
        offset = READU32(0x00000004 + offset);
        WRITEU8(0x0006960B + offset, 0x64);
    }
}

void    no_outlines(void)
{
    static int  state = 0;

    if (!state)
    {
        WRITEU32(0x0041B748, 0xE320F000);
        state = 1;
    }
    else
    {
        WRITEU32(0x0041B748, 0xE5802004);
        state = 0;
    }
    update_status(state, NO_OUTLINES);
    disable_entry(NO_OUTLINES);
}

void    instant_messages(void)
{
    static int  state = 0;

    if (!state)
    {
        WRITEU32(0x003BF26C, 0xE3A05003);
        WRITEU32(0x003BE9C8, 0xE3A04003);
        state = 1;
    }
    else
    {
        WRITEU32(0x003BF26C, 0xE5D05000);
        WRITEU32(0x003BE9C8, 0xE1A04001);
        state = 0;
    }
    update_status(state, INSTANT_MESSAGES);
    disable_entry(INSTANT_MESSAGES);
}

void    walk_through_walls(void)
{
    static int state = 0;

    if (is_pressed(KEY_R))
    {
        if (!state)
        {
            state = 1;
            WRITEU32(0x0039D140, 0xE1A00000);
            WRITEU32(0x0039D274, 0xE1A00000);
        }
    }
    else if (state)
    {
        state = 0;        
        WRITEU32(0x0039D140, 0xEB01E7E7);
        WRITEU32(0x0039D274, 0xEB01E79A);
    }
    //update_status(state, WALK_THROUGH_WALLS);
    //disable_entry(WALK_THROUGH_WALLS);
}

void    rename_any_pokemon(void)
{
    static int  state = 0;

    if (!state)
    {
        WRITEU32(0x004A84F8, 0xE3A00001);
        state = 1;
    }
    else
    {
        WRITEU32(0x004A84F8, 0xE1A00005);
        state = 0;
    }
    update_status(state, RENAME_ANY_POKEMON);
    disable_entry(RENAME_ANY_POKEMON);    
}

void    learn_any_tm_hm(void)
{
    static int state = 0;

    if (!state)
    {
        WRITEU32(0x0048F0AC, 0xE3A00001);
        state = 1;
    }
    else
    {
        WRITEU32(0x0048F0AC, 0x13100001);
        state = 0;
    }
    update_status(state, LEARN_ANY_TM_HM);
    disable_entry(LEARN_ANY_TM_HM);    
}

void    save_slot_teleporter(void)
{
    static  u32     slot[4] = {0};

    u32     offset;
    int     i;

    // Selecting the slot
    if (is_pressed(BUTTON_L))
        i = 0;
    else if (is_pressed(BUTTON_R))
        i = 2;
    else
        goto exit;
    offset = READU32(0x34197890);
    if (!offset)
        goto exit;
    // Saving
    if (is_pressed(BUTTON_DU))
    {
        slot[i++] = READU32(0xE68 + offset);
        slot[i] = READU32(0xE70 + offset);
        goto exit;
    }
    // Restoring
    if (is_pressed(BUTTON_DD))
    {
        if (slot[i] == 0 && slot[i + 1] == 0)
            goto exit;
        WRITEU32(0xE68 + offset, slot[i++]);
        WRITEU32(0xE70 + offset, slot[i]);
        goto exit;
    }
exit:
    return;
}

/* asm function */
void    hooked_pc_option1(void);
void    hooked_pc_option2(void);

t_hook  g_pc_option_hook1 = {0};
t_hook  g_pc_option_hook2 = {0};

void    pc_from_option(void)
{
    static int state = 0;

    if (!state)
    {
        if (!g_pc_option_hook1.is_initialized)
        {
            init_hook(&g_pc_option_hook1, 0x37D560, (u32)hooked_pc_option1);
            init_hook(&g_pc_option_hook2, 0x373C48, (u32)hooked_pc_option2);
        }
        enable_hook(&g_pc_option_hook1);
        enable_hook(&g_pc_option_hook2);
        state = 1;
    }
    else
    {
        disable_hook(&g_pc_option_hook1);
        disable_hook(&g_pc_option_hook2);
        state = 0;
    }
    update_status(state, PC_FROM_OPTION);
    disable_entry(PC_FROM_OPTION);
}

static const char * socks_colors[] = 
{
    "No Socks",
    "White Knee Socks",
    "Black Knee Socks",
    "Red Knee Socks",
    "Yellow Knee Socks",
    "Green Knee Socks",
    "Blue Knee Socks",
    "Orange Knee Socks",
    "Darker Blue Knee Socks",
    "Purple Knee Socks",
    "Pink Knee Socks",
    "Grey Knee Socks",
    "Beije Knee Socks",
    "Light Pink Knee Socks",
    "Dark Red Knee Socks"
};

static const char * hat_colors[] = 
{
    "Red Tipped Black Baseball Cap",
    "Blue Tipped Black Baseball Cap",
    "Rainbow Tipped Black Baseball Cap",
    "Fully Blue Basbell Cap",
    "Fully White Baseball Cap",
    "Brown Sun Hat",
    "Blue Rimmed Brown Sun Hat",
    "Pink Rimmed Brown Sun Hat",
    "Red Rimmed Brown Sun Hat",
    "Yellow Rimmed Brown Sun Hat",
    "Light Blue Rimmed Brown Sun Hat",
    "Orange Rimmed Brown Sun Hat",
    "Black Rimmed Brown Sun Hat",
    "Pink Rimmed Brown Sun Hat",
    "White Sun Hat With Flower"
};

static const char * shirt_colors[] =
{
    "Yellow Sunflower Shirt",
    "Blue Sunflower Shirt",
    "Tan Sunflower Shirt",
    "Yellow Tight Shirt",
    "Blue Tight Shirt",
    "Tan Tight Shirt",
    "Beije Tight Shirt",
    "Green Tight Shirt",
    "Dark Blue Tight Shirt",
    "Grey Tight Shirt",
    "Purple Tight Shirt",
    "Maroon Tight Shirt",
    "Yellow and Green Striped Tight Shirt",
    "Yellow and Purple Striped Tight Shirt",
    "Yellow and Pink Striped Tight Shirt",
};

static const char * shoe_colors[] =
{
    "Red and Black",
    "Orange and Yellow",
    "Orange and Black",
    "White and Black",
    "Grey and Black",
    "Black and Red",
    "Black and Yellow",
    "Black and Light Blue",
    "Black and Dark Blue",
    "Black and Orange",
    "Black and Blue",
    "Black and Purple",
    "Black and Pink",
    "Black and White",
    "Black and Beije"
};

static const char * pants_colors[] = 
{
    "White Pants",
    "Black Pants",
    "Red Pants",
    "Yellow Pants",
    "Green Pants",
    "Blue Pants",
    "Orange Pants",
    "Darker Blue Pants",
    "Purple Pants",
    "Pink Pants"
};


