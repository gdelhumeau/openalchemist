// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : QuitMenuState.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include "../memory.h"
#include <iostream>
#include "QuitMenuState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"

void QuitMenuState::init()
{
	_items.clear();
	_items.insert (_items.end (), &_choice_item);
}

void QuitMenuState::deinit()
{}

void QuitMenuState::load_gfx(CL_GraphicContext &gc, std::string skin)
{
	unload_gfx();

	// Getting skins resources
	CL_VirtualFileSystem vfs(skin, true);
	CL_VirtualDirectory vd(vfs, "./");	
	CL_ResourceManager gfx("menu_quit.xml",vd);

	panel_exit    = CL_Sprite(gc, "menu_quit/dialog_panel/sprite_exit", &gfx);
	panel_give_up = CL_Sprite(gc, "menu_quit/dialog_panel/sprite_giveup", &gfx);
	panel_retry   = CL_Sprite(gc, "menu_quit/dialog_panel/sprite_retry", &gfx);

	panel_x = CL_Integer_to_int("menu_quit/dialog_panel/left", &gfx);
	panel_y = CL_Integer_to_int("menu_quit/dialog_panel/top", &gfx);

	int yes_x = CL_Integer_to_int("menu_quit/dialog_yes/left", &gfx);
	int yes_y = CL_Integer_to_int("menu_quit/dialog_yes/top", &gfx);

	int no_x = CL_Integer_to_int("menu_quit/dialog_no/left", &gfx);
	int no_y = CL_Integer_to_int("menu_quit/dialog_no/top", &gfx);

	_choice_item.set_gfx(gc, gfx, "menu_quit/dialog_yes/unselected", "menu_quit/dialog_yes/selected",
		"menu_quit/dialog_no/unselected", "menu_quit/dialog_no/selected");
	_choice_item.set_x(yes_x);
	_choice_item.set_x2(no_x);
	_choice_item.set_y(yes_y);
	_choice_item.set_y2(no_y);

}

void QuitMenuState::unload_gfx()
{    
	_choice_item.unload_gfx();

}



void QuitMenuState::action_performed(int selection, int action_type)
{
	if(ACTION_TYPE_ENTER == action_type)
	{
		int s = _choice_item.get_selection();
		if(CHOICE_LEFT == s)
		{
			switch(action)
			{
			case QUITMENU_EXIT:
				_p_common_resources -> p_engine -> stop();
				break;
			case QUITMENU_GIVE_UP:
				_p_common_resources -> p_engine -> stop_current_state();
				_p_common_resources -> p_engine -> set_state_title();
				break;
			case QUITMENU_RETRY:
				_p_common_resources -> player1.new_game();
				_p_common_resources -> p_engine -> stop_current_state();
				break;
			}
		}
		else
		{
			_p_common_resources -> p_engine -> stop_current_state();
		}
	}

}


void QuitMenuState::update_child()
{}

QuitMenuState::QuitMenuState()
{}

QuitMenuState::~QuitMenuState()
{
	unload_gfx();
}



void QuitMenuState::set_action(int a)
{
	action = a;
	switch(action)
	{
	case QUITMENU_EXIT:
		_background = panel_exit;
		break;
	case QUITMENU_GIVE_UP:
		_background = panel_give_up;
		break;
	case QUITMENU_RETRY:
		_background = panel_retry;
		break;
	}
}
