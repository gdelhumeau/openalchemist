/********************************************************************
                          OpenAlchemist
 
  File : OptionsMenuState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
 
 
*********************************************************************/

#include "../memory.h"
#include <ClanLib/core.h>

#include "OptionsMenuState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"
#include "../Preferences.h"

enum{
		OPTIONS_ITEM_RENDER,
		OPTIONS_ITEM_SCREENSIZE,
    //OPTIONS_ITEM_CHANGESKIN,
    OPTIONS_ITEM_FULLSCREEN,
    OPTIONS_ITEM_SOUND,
    OPTIONS_ITEM_MUSIC,
    OPTIONS_ITEM_QUIT
};

enum{
		RENDER_CHOICE_OPENGL = 0,
		RENDER_CHOICE_SDL
};

enum{
		ITEM_NO = 0,
		ITEM_YES
};

OptionsMenuState::OptionsMenuState()
{
	_background = NULL;
}

OptionsMenuState::~OptionsMenuState()
{
    deinit();
}


void OptionsMenuState::init()
{
    _items.clear();
    _items.insert (_items.end (), &_render_item);
		_items.insert (_items.end (), &_screensize_item);
		_items.insert (_items.end (), &_fullscreen_item);
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
	
		unload_gfx();
}

void OptionsMenuState::load_gfx(std::string skin)
{
		unload_gfx();
	
    // Getting skins resources
    CL_Zip_Archive zip(skin);
    CL_ResourceManager gfx("menu_options.xml", &zip, false);

    // First, the sprites
    _background = my_new CL_Sprite("menu_options/dialog_background", &gfx);


    int x = 400 - _background -> get_width () / 2;
    int y = 300 - _background -> get_height () / 2;
		
		_render_item.set_description_sprites(
																				 my_new CL_Sprite("menu_options/render/unselected", &gfx),
																				 my_new CL_Sprite("menu_options/render/selected", &gfx),
																				 NULL
																				 );
		
		_render_item.add_choice(my_new CL_Sprite("menu_options/render-choices/opengl", &gfx));
		_render_item.add_choice(my_new CL_Sprite("menu_options/render-choices/sdl", &gfx));
		
		_screensize_item.set_description_sprites(
																				 my_new CL_Sprite("menu_options/screensize/unselected", &gfx),
																				 my_new CL_Sprite("menu_options/screensize/selected", &gfx),
																				 my_new CL_Sprite("menu_options/screensize/locked", &gfx)
																				 );
		
		_screensize_item.add_choice(my_new CL_Sprite("menu_options/screensize-choices/320x240", &gfx));
		_screensize_item.add_choice(my_new CL_Sprite("menu_options/screensize-choices/640x480", &gfx));
		_screensize_item.add_choice(my_new CL_Sprite("menu_options/screensize-choices/640x480-wide", &gfx));
		_screensize_item.add_choice(my_new CL_Sprite("menu_options/screensize-choices/800x600", &gfx));
		_screensize_item.add_choice(my_new CL_Sprite("menu_options/screensize-choices/800x600-wide", &gfx));
		
		_fullscreen_item.set_description_sprites(
																				 my_new CL_Sprite("menu_options/fullscreen/unselected", &gfx),
																				 my_new CL_Sprite("menu_options/fullscreen/selected", &gfx),
																				 NULL
																				 );
	
		_fullscreen_item.add_choice(my_new CL_Sprite("menu_options/item-no", &gfx));
		_fullscreen_item.add_choice(my_new CL_Sprite("menu_options/item-yes", &gfx));
	
    /*
        _items_p[OPTIONS_ITEM_CHANGESKIN] = my_new CL_Sprite("menu_options/changeskin/unselected", &gfx);
        _items_selected_p[OPTIONS_ITEM_CHANGESKIN] = my_new CL_Sprite("menu_options/changeskin/selected", &gfx);
     
        _items_p[OPTIONS_ITEM_FULLSCREEN] = my_new CL_Sprite("menu_options/fullscreen/unselected", &gfx);
        _items_selected_p[OPTIONS_ITEM_FULLSCREEN] = my_new CL_Sprite("menu_options/fullscreen/selected", &gfx);
     
        _items_p[OPTIONS_ITEM_SOUND] = my_new CL_Sprite("menu_options/sound/unselected", &gfx);
        _items_selected_p[OPTIONS_ITEM_SOUND] = my_new CL_Sprite("menu_options/sound/selected", &gfx);
     
        _items_p[OPTIONS_ITEM_MUSIC] = my_new CL_Sprite("menu_options/music/unselected", &gfx);
        _items_selected_p[OPTIONS_ITEM_MUSIC] = my_new CL_Sprite("menu_options/music/selected", &gfx);
     
        _items_p[OPTIONS_ITEM_QUIT] = my_new CL_Sprite("menu_options/quit/unselected", &gfx);
        _items_selected_p[OPTIONS_ITEM_QUIT] = my_new CL_Sprite("menu_options/quit/selected", &gfx);
        */

    _sound_level_item.set_description_sprites(
																							my_new CL_Sprite("menu_options/sound/unselected", &gfx),
																							my_new CL_Sprite("menu_options/sound/selected", &gfx),
																							NULL
																							);

    _music_level_item.set_description_sprites(
																							my_new CL_Sprite("menu_options/music/unselected", &gfx),
																							my_new CL_Sprite("menu_options/music/selected", &gfx),
																							NULL
																							);

    _quit_item.set_gfx(my_new CL_Sprite("menu_options/quit/unselected", &gfx),
                       my_new CL_Sprite("menu_options/quit/selected", &gfx),
                       NULL);
                       
    _sound_level_item.clear_choices();
		_music_level_item.clear_choices();

    for(int i=0; i<=10; ++i)
    {
        _sound_level_item.add_choice(my_new CL_Sprite("menu_options/sound_level/"+to_string(i), &gfx));
        _music_level_item.add_choice(my_new CL_Sprite("menu_options/sound_level/"+to_string(i), &gfx));
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
		
		_render_item.set_x(x + CL_Integer_to_int("menu_options/render/left", &gfx));
    _render_item.set_y(y + CL_Integer_to_int("menu_options/render/top", &gfx));
		
		_render_item.set_choice_x(x + CL_Integer_to_int("menu_options/render-choices/left", &gfx));
    _render_item.set_choice_y(y + CL_Integer_to_int("menu_options/render/top", &gfx));
		
		_screensize_item.set_x(x + CL_Integer_to_int("menu_options/screensize/left", &gfx));
    _screensize_item.set_y(y + CL_Integer_to_int("menu_options/screensize/top", &gfx));
		
		_screensize_item.set_choice_x(x + CL_Integer_to_int("menu_options/screensize-choices/left", &gfx));
    _screensize_item.set_choice_y(y + CL_Integer_to_int("menu_options/screensize/top", &gfx));
		
		_fullscreen_item.set_x(x + CL_Integer_to_int("menu_options/fullscreen/left", &gfx));
    _fullscreen_item.set_y(y + CL_Integer_to_int("menu_options/fullscreen/top", &gfx));
		
		_fullscreen_item.set_choice_x(x + CL_Integer_to_int("menu_options/fullscreen-choices/left", &gfx));
    _fullscreen_item.set_choice_y(y + CL_Integer_to_int("menu_options/fullscreen/top", &gfx));		
    
    _quit_item.set_x(x + CL_Integer_to_int("menu_options/quit/left", &gfx));
    _quit_item.set_y(y + CL_Integer_to_int("menu_options/quit/top", &gfx));
		
		Preferences *p_pref = pref_get_instance();		
		if(p_pref -> render_opengl)
		{
				_render_item.set_current_choice(RENDER_CHOICE_OPENGL);
		}
		else
		{
				_render_item.set_current_choice(RENDER_CHOICE_SDL);
		}
		_screensize_item.set_current_choice(p_pref -> screen_size);
		if(p_pref -> fullscreen)
		{
				_fullscreen_item.set_current_choice(ITEM_YES);
		}
		else
		{
				_fullscreen_item.set_current_choice(ITEM_NO);
		}

}

void OptionsMenuState::unload_gfx()
{
	if(_background)
	{
		my_delete(_background);
		_background = NULL;
	}
	_render_item.unload_gfx();
	_screensize_item.unload_gfx();
	_fullscreen_item.unload_gfx();
	_sound_level_item.unload_gfx();
	_music_level_item.unload_gfx();	
}

void OptionsMenuState::action_performed(int selection, int action_type)
{
	if(ACTION_TYPE_ENTER == action_type)				
	{
			switch(selection)
			{					
					case OPTIONS_ITEM_QUIT:
					{							
						_p_common_resources -> p_engine -> stop_current_state ();
					}
					break;
			}					
	}
}

void OptionsMenuState::update_child()
{
		_screensize_item.set_locked (_render_item.get_current_choice() != RENDER_CHOICE_OPENGL);
		
		Preferences *p_pref = pref_get_instance();
		switch(_render_item.get_current_choice())
		{
				case RENDER_CHOICE_OPENGL:
						p_pref -> render_opengl = true;
						break;
				case RENDER_CHOICE_SDL:
						p_pref -> render_opengl = false;
						break;											
		}
		
		bool display_changed = false;
		if(p_pref -> screen_size != (int)_screensize_item.get_current_choice())
		{
				p_pref -> screen_size = _screensize_item.get_current_choice();
				display_changed = true;			
		}
		
		bool fullscreen = (int) _fullscreen_item.get_current_choice() == ITEM_YES;
		if(p_pref -> fullscreen != fullscreen)
		{
				p_pref -> fullscreen = fullscreen;
				display_changed = true;
		}
		
		if(display_changed)
		{
				_p_common_resources -> p_engine -> change_screen_size();
//				std::cout << "Call here change screen size function" << std::endl;
		}
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




