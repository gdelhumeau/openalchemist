/********************************************************************
                          OpenAlchemist
 
  File : PauseMenuState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
 
 
 *********************************************************************/

#include "../memory.h"
#include <ClanLib/core.h>

#include "PauseMenuState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"

enum
{
    PAUSE_ITEM_RESUME,
    PAUSE_ITEM_UNDO,
    PAUSE_ITEM_RETRY,
    PAUSE_ITEM_OPTIONS,
    PAUSE_ITEM_GIVEUP,
    PAUSE_ITEM_QUIT
};

void PauseMenuState::init ()
{
    _items.clear();
    _items.insert (_items.end (), &_resume_item);
    _items.insert (_items.end (), &_undo_item);
    _items.insert (_items.end (), &_retry_item);
    _items.insert (_items.end (), &_options_item);
    _items.insert (_items.end (), &_giveup_item);
    _items.insert (_items.end (), &_quit_item);
}

void PauseMenuState::deinit ()
{ 
	unload_gfx();
}

void PauseMenuState::load_gfx (CL_GraphicContext &gc, std::string skin)
{
	unload_gfx();
	
    // Getting skins resources
    CL_VirtualFileSystem vfs(skin, true);
  	CL_VirtualDirectory vd(vfs, "./");	
  	CL_ResourceManager gfx("menu_pause.xml",vd);


    // First, the sprites
    _background = CL_Sprite (gc, "menu_pause/background", &gfx);

    int x = 400 - _background.get_width () / 2;
    int y = 300 - _background.get_height () / 2;


    // resume
    _resume_item.set_gfx (gc, gfx, 
                          "menu_pause/resume/unselected", 
                          "menu_pause/resume/selected");
    _resume_item.set_x (x + CL_Integer_to_int ("menu_pause/resume/left", &gfx));
    _resume_item.set_y (y + CL_Integer_to_int ("menu_pause/resume/top", &gfx));

    // undo
    _undo_item.set_gfx (gc, gfx, 
                        "menu_pause/undo/unselected",
                        "menu_pause/undo/selected",
                        "menu_pause/undo/unavailable");
    _undo_item.set_x (x + CL_Integer_to_int ("menu_pause/undo/left", &gfx));
    _undo_item.set_y (y + CL_Integer_to_int ("menu_pause/undo/top", &gfx));
    _undo_item.set_locked (true);

    // retry
    _retry_item.set_gfx (gc, gfx,
                         "menu_pause/retry/unselected",
                         "menu_pause/retry/selected");
    _retry_item.set_x (x + CL_Integer_to_int ("menu_pause/retry/left", &gfx));
    _retry_item.set_y (y + CL_Integer_to_int ("menu_pause/retry/top", &gfx));

    // options
    _options_item.set_gfx (gc, gfx,
                           "menu_pause/options/unselected",
                           "menu_pause/options/selected");
    _options_item.set_x (x + CL_Integer_to_int ("menu_pause/options/left", &gfx));
    _options_item.set_y (y + CL_Integer_to_int ("menu_pause/options/top", &gfx));

    // give up
    _giveup_item.set_gfx (gc, gfx,
                          "menu_pause/giveup/unselected",
													"menu_pause/giveup/selected",
                          "menu_pause/giveup/unavailable");
    _giveup_item.set_x (x + CL_Integer_to_int ("menu_pause/giveup/left", &gfx));
    _giveup_item.set_y (y + CL_Integer_to_int ("menu_pause/giveup/top", &gfx));

    // quit
    _quit_item.set_gfx (gc, gfx,
                        "menu_pause/quit/unselected",
                        "menu_pause/quit/selected");
    _quit_item.set_x (x + CL_Integer_to_int ("menu_pause/quit/left", &gfx));
    _quit_item.set_y (y + CL_Integer_to_int ("menu_pause/quit/top", &gfx));


}

void PauseMenuState::unload_gfx ()
{
    _resume_item.unload_gfx ();
    _undo_item.unload_gfx ();
    _retry_item.unload_gfx ();	
}

void PauseMenuState::action_performed (int selection, int action_type)
{
    if(ACTION_TYPE_ENTER == action_type)
    {
        switch (selection)
        {
        case PAUSE_ITEM_RESUME:
            _p_common_resources -> p_engine -> stop_current_state ();
            break;
        case PAUSE_ITEM_UNDO:
            _p_common_resources -> player1.undo ();
            _p_common_resources -> p_engine -> stop_current_state ();
            _p_common_resources -> p_engine -> set_state_ingame ();
            break;
        case PAUSE_ITEM_RETRY:
            {
                if (_p_common_resources -> player1.is_game_over ())
                {
                    _p_common_resources -> player1.new_game ();
                    _p_common_resources -> p_engine -> stop_current_state ();
                    _p_common_resources -> p_engine -> set_state_ingame ();
                }
                else
                {
                    _p_common_resources -> p_engine -> stop_current_state ();
                    _p_common_resources -> p_engine -> set_state_quit_menu (QUITMENU_RETRY);
                }
                break;
            }
        case PAUSE_ITEM_GIVEUP:
            {
                if (_p_common_resources -> player1.is_game_over ())
                {
                    _p_common_resources -> p_engine -> stop_current_state ();
                    _p_common_resources -> p_engine -> set_state_title ();
                }
                else
                {
                    _p_common_resources -> player1.give_up ();
                    _p_common_resources -> p_engine -> stop_current_state ();
                    _p_common_resources -> p_engine -> set_state_quit_menu (QUITMENU_GIVE_UP);
                }
                break;
            }
        case PAUSE_ITEM_OPTIONS:
            {
                start ();
                _p_common_resources -> p_engine -> set_state_options_menu ();
                break;
            }
        case PAUSE_ITEM_QUIT:
            {
                _p_common_resources -> p_engine -> set_state_quit_menu (QUITMENU_EXIT);
                break;
            }
        }
    }

}

void PauseMenuState::update_child ()
{
    _undo_item.set_locked (!_p_common_resources -> player1.is_undo_available ());
    _giveup_item.set_locked(!_p_common_resources -> p_current_player -> is_human());
}

PauseMenuState::PauseMenuState ()
{
}

PauseMenuState::~PauseMenuState ()
{
    deinit ();
}



