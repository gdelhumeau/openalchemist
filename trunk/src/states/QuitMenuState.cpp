/********************************************************************
                          OpenAlchemist
 
  File : QuitMenuState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
 
 
*********************************************************************/

#include <iostream>
#include "QuitMenuState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"

void QuitMenuState::init()
{
    _items.clear();
    _items.insert (_items.end (), &_choice_item);

    panel_exit     = NULL;
    panel_give_up  = NULL;
    panel_retry    = NULL;
}

void QuitMenuState::deinit()
{}

void QuitMenuState::load_gfx(std::string skin)
{
    // Getting skins resources
    CL_Zip_Archive zip(skin);
    CL_ResourceManager gfx("menu_quit.xml", &zip, false);

    panel_exit    = new CL_Sprite("menu_quit/dialog_panel/sprite_exit", &gfx);
    panel_give_up = new CL_Sprite("menu_quit/dialog_panel/sprite_giveup", &gfx);
    panel_retry   = new CL_Sprite("menu_quit/dialog_panel/sprite_retry", &gfx);

    panel_x = CL_Integer_to_int("menu_quit/dialog_panel/left", &gfx);
    panel_y = CL_Integer_to_int("menu_quit/dialog_panel/top", &gfx);

    CL_Sprite * yes_selected   = new CL_Sprite("menu_quit/dialog_yes/selected", &gfx);
    CL_Sprite * yes_unselected = new CL_Sprite("menu_quit/dialog_yes/unselected", &gfx);
    int yes_x = CL_Integer_to_int("menu_quit/dialog_yes/left", &gfx);
    int yes_y = CL_Integer_to_int("menu_quit/dialog_yes/top", &gfx);

    CL_Sprite * no_selected   = new CL_Sprite("menu_quit/dialog_no/selected", &gfx);
    CL_Sprite * no_unselected = new CL_Sprite("menu_quit/dialog_no/unselected", &gfx);
    int no_x = CL_Integer_to_int("menu_quit/dialog_no/left", &gfx);
    int no_y = CL_Integer_to_int("menu_quit/dialog_no/top", &gfx);

    _choice_item.set_gfx(yes_unselected, yes_selected, no_unselected, no_selected);
    _choice_item.set_x(yes_x);
    _choice_item.set_x2(no_x);
    _choice_item.set_y(yes_y);
    _choice_item.set_y2(no_y);

}

void QuitMenuState::unload_gfx()
{
    if(panel_exit)
    {
        delete panel_exit;
        panel_exit = NULL;
    }
    if(panel_give_up)
    {
        delete panel_give_up;
        panel_give_up = NULL;
    }
    if(panel_retry)
    {
        delete panel_retry;
        panel_retry = NULL;
    }

    _choice_item.unload_gfx();

}



void QuitMenuState::action_performed(int selection)
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


void QuitMenuState::update_child()
{
}

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
