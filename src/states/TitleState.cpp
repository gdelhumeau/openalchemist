/********************************************************************
                          OpenAlchemist

  File : TitleState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <ClanLib/core.h>

#include "TitleState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"



void TitleState::init()
{
	GameState::init();
}

void TitleState::deinit()
{
}

void TitleState::load_gfx(std::string skin)
{
	// Getting skins resources
	CL_Zip_Archive zip(skin);
	CL_ResourceManager gfx("title.xml", &zip, false);
	
	_p_start_message = new CL_Sprite("title/start_message/sprite", &gfx);
	_start_message_x = CL_Integer_to_int("title/start_message/left", &gfx);
	_start_message_y = CL_Integer_to_int("title/start_message/top", &gfx);
	
	for(int i=0; i<NUMBER_OF_SENTENCES; ++i)
	{
		_sentences_p[i] = new CL_Sprite("title/help/"+to_string(i+1)+"/sentence", &gfx);
		_sentences_x[i] = CL_Integer_to_int("title/help/"+to_string(i+1)+"/left", &gfx);
		_sentences_y[i] = CL_Integer_to_int("title/help/"+to_string(i+1)+"/top", &gfx);
		_sentences_time[i] = CL_Integer_to_int("title/help/"+to_string(i+1)+"/time", &gfx);
	}
	
	_p_keydemo_left    = new CL_Sprite("title/keydemo/left", &gfx);
	_p_keydemo_up      = new CL_Sprite("title/keydemo/up", &gfx);
	_p_keydemo_right   = new CL_Sprite("title/keydemo/right", &gfx);
	_p_keydemo_down    = new CL_Sprite("title/keydemo/down", &gfx);
	_p_keydemo_escape  = new CL_Sprite("title/keydemo/escape", &gfx);
	_p_keydemo_options = new CL_Sprite("title/keydemo/options", &gfx);
	
	_keyleft_x = 50;
	_keyleft_y = _keyright_y = _keydown_y = 100;
	_keyup_x = _keydown_x = 100;
	_keyup_y = 50;
	_keyright_x = 150;
	
	_demo_player.load_gfx(skin);
	
}

void TitleState::unload_gfx()
{
	for(int i=0; i<NUMBER_OF_SENTENCES; ++i)
	{
		if(_sentences_p[i])
		{
			delete _sentences_p[i];
			_sentences_p[i] = NULL;
		}
	}
	
	if(_p_start_message)
	{
		delete _p_start_message;
		_p_start_message = NULL;
	}
	
	if(_p_keydemo_left)
	{
		delete _p_keydemo_left;
		_p_keydemo_left = NULL;
	}
	
	if(_p_keydemo_up)
	{
		delete _p_keydemo_up;
		_p_keydemo_up = NULL;
	}
	
	if(_p_keydemo_right)
	{
		delete _p_keydemo_right;
		_p_keydemo_right = NULL;
	}
	
	if(_p_keydemo_down)
	{
		delete _p_keydemo_down;
		_p_keydemo_down = NULL;
	}
	
	if(_p_keydemo_escape)
	{
		delete _p_keydemo_escape;
		_p_keydemo_escape = NULL;
	}
	
	if(_p_keydemo_options)
	{
		delete _p_keydemo_options;
		_p_keydemo_options = NULL;
	}
	
}

void TitleState::draw()
{
	
	_sentences_p[_step] -> draw (_sentences_x[_step], _sentences_y[_step]);
	
	_p_start_message -> draw(_start_message_x,_start_message_y);
	
	switch(_step)
	{
		case 2:
			_p_keydemo_left -> draw(_sentences_x[_step] + _sentences_p[_step] -> get_width()/2 - _p_keydemo_left -> get_width()/2,
													 _sentences_y[_step] + _sentences_p[_step] -> get_height());
			_p_keydemo_left -> update();
			break;
		case 3:
			_p_keydemo_right -> draw(_sentences_x[_step] + _sentences_p[_step] -> get_width()/2 - _p_keydemo_left -> get_width()/2,
														_sentences_y[_step] + _sentences_p[_step] -> get_height());
			_p_keydemo_right -> update();
			break;
		case 4:
			_p_keydemo_up -> draw(_sentences_x[_step] + _sentences_p[_step] -> get_width()/2 - _p_keydemo_left -> get_width()/2,
												 _sentences_y[_step] + _sentences_p[_step] -> get_height());
			_p_keydemo_up -> update();
			break;
		case 5:
		case 7:
			_p_keydemo_down -> draw(_sentences_x[_step] + _sentences_p[_step] -> get_width()/2 - _p_keydemo_left -> get_width()/2,
													 _sentences_y[_step] + _sentences_p[_step] -> get_height());
			_p_keydemo_down -> update();
			break;
		case 6:
			_p_keydemo_left -> draw(_sentences_x[_step] + _sentences_p[_step] -> get_width()/2 - _p_keydemo_left -> get_width(),
													 _sentences_y[_step] + _sentences_p[_step] -> get_height());
			_p_keydemo_left -> update();
			
			_p_keydemo_right -> draw(_sentences_x[_step] + _sentences_p[_step] -> get_width()/2 + _p_keydemo_left -> get_width(),
														_sentences_y[_step] + _sentences_p[_step] -> get_height());
			_p_keydemo_right -> update();
			break;
		case 12:
			_p_keydemo_escape -> draw(_sentences_x[_step] + _sentences_p[_step] -> get_width()/2 - _p_keydemo_left -> get_width()/2,
														 _sentences_y[_step] + _sentences_p[_step] -> get_height());
			_p_keydemo_escape -> update();
			break;
		case 13:
			_p_keydemo_options -> draw(_sentences_x[_step] + _sentences_p[_step] -> get_width()/2 - _p_keydemo_left -> get_width()/2,
															_sentences_y[_step] + _sentences_p[_step] -> get_height());
			_p_keydemo_options -> update();
			break;
			break;
			
	}
}

void TitleState::update()
{
	_p_start_message -> update();
	
	if(_next_time < CL_System::get_time())
	{
		_step = (_step + 1) % NUMBER_OF_SENTENCES;
		_next_time = CL_System::get_time() + _sentences_time[_step];
		_sentences_p[_step] -> update();
	}
	
	switch(_step)
	{
		// Welcome to OpenAlchemist !
		case 0:
			_new_game = false;
			break;
			
			// This is your pieces
		case 1:
			if(!_new_game)
		{
			_new_game = true;
			_demo_player.new_game();
		}
			break;
			
			// You can move them to the left...
		case 2:
			_demo_player.move_left();
			break;
			
			// ...or to the right !
		case 3:
			_demo_player.move_right();
			_change_angle = false;
			break;
			
			// You can also rotate pieces...
		case 4:
			if(!_change_angle)
		{
			_demo_player.change_angle();
			_change_angle = true;
		}
			_fall = false;
			break;
			
			// ...and make them fall !
		case 5:
			if(!_fall)
		{
			_demo_player.fall();
			_fall = true;
			_select_the_position = false;
		}
			break;
			
			// Select the position...
		case 6:
			if(!_select_the_position)
		{
			_select_the_position = true;
			_demo_player.move_left();
			_fall = false;
		}
			break;
			
			// ...and fall !
		case 7:
			if(!_fall)
		{
			_demo_player.fall();
			_fall = true;
		}
			break;
			
			// When you have more than 3 same items...
		case 8:
			break;
			
			// ...they're destroyed...
		case 9:
			break;
			
			// ...and a new one is created !
		case 10:
			break;
			
			// Align more than 3 items and you get bonus !
		case 11:
			break;
			
			// You can also open the game menu...
		case 12:
			break;
			
			// ...or the options menu !
		case 13:
			break;
			
			// Now you know everything...
		case 14:
			break;
			
			// ...so start a new game and have fun !
		case 15:
			break;
	}
	
	_demo_player.update();
}

void TitleState::events()
{
	if(_p_common_resources -> key.enter -> get() || CL_Keyboard::get_keycode(CL_KEY_SPACE))
	{
		_p_common_resources -> p_engine -> set_state_ingame();
		_p_common_resources -> player1.new_game();
	}
	
	if(_p_common_resources-> key.escape -> get() || _p_common_resources -> key.pause -> get())
	{
		_p_common_resources -> p_engine -> set_state_pause_menu();
	}
	
	if(_p_common_resources -> key.skins -> get())
	{
		_p_common_resources -> p_engine -> set_state_skin_menu();
	}
	
	if(_p_common_resources->key.options -> get() )
	{
		_p_common_resources -> p_engine -> set_state_options_menu();
	}
	
}

bool TitleState::front_layer_behind()
{
	return true;
}

TitleState::TitleState()
{
	_p_start_message   = NULL;
	_p_keydemo_left    = NULL;
	_p_keydemo_up      = NULL;
	_p_keydemo_right   = NULL;
	_p_keydemo_down    = NULL;
	_p_keydemo_escape  = NULL;
	_p_keydemo_options = NULL;
	
	for(int i=0; i<NUMBER_OF_SENTENCES; ++i)
	{
		_sentences_p[i] = NULL;
	}
}

TitleState::~TitleState()
{
	unload_gfx();
}

void TitleState::start()
{
	_step = 0;
	_next_time = CL_System::get_time() + 5000;
	_p_common_resources -> p_current_player = &_demo_player;
	_demo_player.new_game();
}
