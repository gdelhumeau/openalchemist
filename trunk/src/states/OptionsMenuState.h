/********************************************************************
                          OpenAlchemist
 
  File : OptionsMenuState.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
 
 
*********************************************************************/

#ifndef _OPTIONSMENU_STATE_H_
#define _OPTIONSMENU_STATE_H_

#include <ClanLib/display.h>

#include "MenuState.h"
#include "MenuState/BasicItem.h"
#include "MenuState/MultipleChoicesItem.h"

#define OPTIONS_NUMBER_OF_ITEMS 5

class GameEngine;

/**
 * OptionsMenu State
 */
class OptionsMenuState : public MenuState
{

private:
    MultipleChoicesItem _render_item;
    MultipleChoicesItem _screensize_item;
    MultipleChoicesItem _fullscreen_item;
    MultipleChoicesItem _framerate_item;
    MultipleChoicesItem _sound_level_item;
    MultipleChoicesItem _music_level_item;

    BasicItem _quit_item;


    int _sound_level;
    int _music_level;


public:
    void init();
    void deinit();
    void load_gfx(std::string skin);
    void unload_gfx();
    void action_performed(int selection, int action_type);
    void update_child();
		void toggle_screen();

    OptionsMenuState();
    ~OptionsMenuState();


};

#endif
