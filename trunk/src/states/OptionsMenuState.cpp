/********************************************************************
                          OpenAlchemist
 
  File : OptionsMenuState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
 
 
*********************************************************************/

#include <ClanLib/core.h>

#include "OptionsMenuState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"
#include "../Preferences.h"

enum{
    //OPTIONS_ITEM_CHANGESKIN,
    //OPTIONS_ITEM_FULLSCREEN,
    OPTIONS_ITEM_SOUND,
    OPTIONS_ITEM_MUSIC,
    OPTIONS_ITEM_QUIT
};


OptionsMenuState::OptionsMenuState()
{
}

OptionsMenuState::~OptionsMenuState()
{
    deinit();
}


void OptionsMenuState::init()
{
    _items.clear();
    _items.insert (_items.end (), &_sound_level_item);
    _items.insert (_items.end (), &_music_level_item);
    _items.insert (_items.end (), &_quit_item);

    Preferences *p_pref = pref_get_instance();

    _sound_level = p_pref -> sound_level;
    _music_level = p_pref -> music_level;
}

void OptionsMenuState::deinit()
{
    Preferences *p_pref = pref_get_instance();

    p_pref -> sound_level = _sound_level;
    p_pref -> music_level = _music_level;

    p_pref -> write();
}

void OptionsMenuState::load_gfx(std::string skin)
{
    // Getting skins resources
    CL_Zip_Archive zip(skin);
    CL_ResourceManager gfx("menu_options.xml", &zip, false);

    // First, the sprites
    _background = new CL_Sprite("menu_options/dialog_background", &gfx);


    int x = 400 - _background -> get_width () / 2;
    int y = 300 - _background -> get_height () / 2;

    /*
        _items_p[OPTIONS_ITEM_CHANGESKIN] = new CL_Sprite("menu_options/changeskin/unselected", &gfx);
        _items_selected_p[OPTIONS_ITEM_CHANGESKIN] = new CL_Sprite("menu_options/changeskin/selected", &gfx);
     
        _items_p[OPTIONS_ITEM_FULLSCREEN] = new CL_Sprite("menu_options/fullscreen/unselected", &gfx);
        _items_selected_p[OPTIONS_ITEM_FULLSCREEN] = new CL_Sprite("menu_options/fullscreen/selected", &gfx);
     
        _items_p[OPTIONS_ITEM_SOUND] = new CL_Sprite("menu_options/sound/unselected", &gfx);
        _items_selected_p[OPTIONS_ITEM_SOUND] = new CL_Sprite("menu_options/sound/selected", &gfx);
     
        _items_p[OPTIONS_ITEM_MUSIC] = new CL_Sprite("menu_options/music/unselected", &gfx);
        _items_selected_p[OPTIONS_ITEM_MUSIC] = new CL_Sprite("menu_options/music/selected", &gfx);
     
        _items_p[OPTIONS_ITEM_QUIT] = new CL_Sprite("menu_options/quit/unselected", &gfx);
        _items_selected_p[OPTIONS_ITEM_QUIT] = new CL_Sprite("menu_options/quit/selected", &gfx);
        */

    _sound_level_item.set_description_sprites(new CL_Sprite("menu_options/sound/unselected", &gfx),
            new CL_Sprite("menu_options/sound/selected", &gfx));

    _music_level_item.set_description_sprites(new CL_Sprite("menu_options/music/unselected", &gfx),
            new CL_Sprite("menu_options/music/selected", &gfx));

    _quit_item.set_gfx(new CL_Sprite("menu_options/quit/unselected", &gfx),
                       new CL_Sprite("menu_options/quit/selected", &gfx),
                       NULL);
                       
    _sound_level_item.clear_choices();
	_music_level_item.clear_choices();

	std::cout << "gralala\n";
    for(int i=0; i<=10; ++i)
    {
        _sound_level_item.add_choice(new CL_Sprite("menu_options/sound_level/"+to_string(i), &gfx));
        _music_level_item.add_choice(new CL_Sprite("menu_options/sound_level/"+to_string(i), &gfx));
    }


    // Then, propreties

    /*
        _items_left[OPTIONS_ITEM_CHANGESKIN] = CL_Integer_to_int("menu_options/changeskin/left", &gfx);
        _items_top[OPTIONS_ITEM_CHANGESKIN] = CL_Integer_to_int("menu_options/changeskin/top", &gfx);
     
        _items_left[OPTIONS_ITEM_FULLSCREEN] = CL_Integer_to_int("menu_options/fullscreen/left", &gfx);
        _items_top[OPTIONS_ITEM_FULLSCREEN] = CL_Integer_to_int("menu_options/fullscreen/top", &gfx);
     
        _items_left[OPTIONS_ITEM_SOUND] = CL_Integer_to_int("menu_options/sound/left", &gfx);
        _items_top[OPTIONS_ITEM_SOUND] = CL_Integer_to_int("menu_options/sound/top", &gfx);
     
        _items_left[OPTIONS_ITEM_MUSIC] = CL_Integer_to_int("menu_options/music/left", &gfx);
        _items_top[OPTIONS_ITEM_MUSIC] = CL_Integer_to_int("menu_options/music/top", &gfx);
     
        _items_left[OPTIONS_ITEM_QUIT] = CL_Integer_to_int("menu_options/quit/left", &gfx);
        _items_top[OPTIONS_ITEM_QUIT] = CL_Integer_to_int("menu_options/quit/top", &gfx);
     
     
        _sound_level_left = CL_Integer_to_int("menu_options/sound_level/left", &gfx);*/

    _sound_level_item.set_x(x + CL_Integer_to_int("menu_options/sound/left", &gfx));
    _sound_level_item.set_y(y + CL_Integer_to_int("menu_options/sound/top", &gfx));
    
    _sound_level_item.set_choice_x(x + CL_Integer_to_int("menu_options/sound/left", &gfx)+250);
    _sound_level_item.set_choice_y(y + CL_Integer_to_int("menu_options/sound/top", &gfx));

    _music_level_item.set_x(x + CL_Integer_to_int("menu_options/music/left", &gfx));
    _music_level_item.set_y(y + CL_Integer_to_int("menu_options/music/top", &gfx));
    
    _music_level_item.set_choice_x(x + CL_Integer_to_int("menu_options/music/left", &gfx)+250);
    _music_level_item.set_choice_y(y + CL_Integer_to_int("menu_options/music/top", &gfx));
    
    _quit_item.set_x(x + CL_Integer_to_int("menu_options/quit/left", &gfx));
    _quit_item.set_y(y + CL_Integer_to_int("menu_options/quit/top", &gfx));

}

void OptionsMenuState::unload_gfx()
{}

void OptionsMenuState::action_performed(int selection, int action_type)
{
	if(ACTION_TYPE_ENTER == action_type && OPTIONS_ITEM_QUIT == selection)
	{
		_p_common_resources -> p_engine -> stop_current_state ();
	}
}

void OptionsMenuState::update_child()
{
	
}


/*
void OptionsMenuState::draw()
{
	
    int x = 400 - _p_background -> get_width()/2;
    int y = 300 - _p_background -> get_height()/2;
    _p_background -> draw(x,y);
 
    // Drawing
    for(int i=0; i<OPTIONS_NUMBER_OF_ITEMS; ++i)
    {
 
        if(i == _selection)
        {
            _items_selected_p[i] -> draw(x + _items_left[i], y + _items_top[i]);
            _items_selected_p[i] -> update(_p_common_resources -> time_interval);
 
        }
        else
        {
            _items_p[i] -> draw(x + _items_left[i], y + _items_top[i]);
            _items_p[i] -> update(_p_common_resources -> time_interval);
        }
    }
 
    _sound_level_sprites_p[_sound_level] -> draw(x + _sound_level_left, y
            + _items_top[OPTIONS_ITEM_SOUND]);
    _sound_level_sprites_p[_music_level] -> draw(x + _sound_level_left, y
            + _items_top[OPTIONS_ITEM_MUSIC]);
    _sound_level_sprites_p[_sound_level] -> update();
    _sound_level_sprites_p[_music_level] -> update();
 
}*/




