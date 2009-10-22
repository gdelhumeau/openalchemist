// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : TitleState.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include "../memory.h"
#include <ClanLib/core.h>

#include "TitleState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"

#pragma warning(disable:4244)

void TitleState::init()
{
}

void TitleState::term()
{
}

void TitleState::load_gfx(CL_GraphicContext & gc, std::string skin)
{
	unload_gfx();

	// Getting skins resources
	CL_VirtualFileSystem vfs(skin, true);
	CL_VirtualDirectory vd(vfs, "./");	
	CL_ResourceManager gfx("title.xml",vd);

	_start_message = CL_Sprite(gc, "title/start_message/sprite", &gfx);
	_start_message_x = CL_Integer_to_int("title/start_message/left", &gfx);
	_start_message_y = CL_Integer_to_int("title/start_message/top", &gfx);

	for(int i=0; i<NUMBER_OF_SENTENCES; ++i)
	{
		_sentences[i] = CL_Sprite(gc, "title/help/"+to_string(i+1)+"/sentence", &gfx);
		_sentences_x[i] = CL_Integer_to_int("title/help/"+to_string(i+1)+"/left", &gfx);
		_sentences_y[i] = CL_Integer_to_int("title/help/"+to_string(i+1)+"/top", &gfx);
		_sentences_time[i] = CL_Integer_to_int("title/help/"+to_string(i+1)+"/time", &gfx);
	}

	_keydemo_left    = CL_Sprite(gc, "title/keydemo/left", &gfx);
	_keydemo_up      = CL_Sprite(gc, "title/keydemo/up", &gfx);
	_keydemo_right   = CL_Sprite(gc, "title/keydemo/right", &gfx);
	_keydemo_down    = CL_Sprite(gc, "title/keydemo/down", &gfx);
	_keydemo_escape  = CL_Sprite(gc, "title/keydemo/escape", &gfx);
	_keydemo_options = CL_Sprite(gc, "title/keydemo/options", &gfx);

	_keyleft_x = 50;
	_keyleft_y = _keyright_y = _keydown_y = 100;
	_keyup_x = _keydown_x = 100;
	_keyup_y = 50;
	_keyright_x = 150;

	_demo_player.load_gfx(gc, skin);

}

void TitleState::unload_gfx()
{

}

void TitleState::draw(CL_GraphicContext & gc)
{

	_sentences[_step].draw (gc, _sentences_x[_step], _sentences_y[_step]);

	_start_message.draw(gc, _start_message_x,_start_message_y);

	switch(_step)
	{
	case 2:
		_keydemo_left.draw(gc, _sentences_x[_step] + _sentences[_step].get_width()/2 - _keydemo_left.get_width()/2,
			_sentences_y[_step] + _sentences[_step].get_height());
		_keydemo_left.update();
		break;
	case 3:
		_keydemo_right.draw(gc, _sentences_x[_step] + _sentences[_step].get_width()/2 - _keydemo_left.get_width()/2,
			_sentences_y[_step] + _sentences[_step].get_height());
		_keydemo_right.update();
		break;
	case 4:
		_keydemo_up.draw(gc, _sentences_x[_step] + _sentences[_step].get_width()/2 - _keydemo_left.get_width()/2,
			_sentences_y[_step] + _sentences[_step].get_height());
		_keydemo_up.update();
		break;
	case 5:
	case 7:
		_keydemo_down.draw(gc, _sentences_x[_step] + _sentences[_step].get_width()/2 - _keydemo_left.get_width()/2,
			_sentences_y[_step] + _sentences[_step].get_height());
		_keydemo_down.update();
		break;
	case 6:
		_keydemo_left.draw(gc, _sentences_x[_step] + _sentences[_step].get_width()/2 - _keydemo_left.get_width(),
			_sentences_y[_step] + _sentences[_step].get_height());
		_keydemo_left.update();

		_keydemo_right.draw(gc, _sentences_x[_step] + _sentences[_step].get_width()/2 + _keydemo_left.get_width(),
			_sentences_y[_step] + _sentences[_step].get_height());
		_keydemo_right.update();
		break;
	case 12:
		_keydemo_escape.draw(gc, _sentences_x[_step] + _sentences[_step].get_width()/2 - _keydemo_left.get_width()/2,
			_sentences_y[_step] + _sentences[_step].get_height());
		_keydemo_escape.update();
		break;
	case 13:
		_keydemo_options.draw(gc, _sentences_x[_step] + _sentences[_step].get_width()/2 - _keydemo_left.get_width()/2,
			_sentences_y[_step] + _sentences[_step].get_height());
		_keydemo_options.update();
		break;
		break;

	}
}

void TitleState::update(CL_GraphicContext & gc)
{
	_start_message.update();

	if(_next_time < CL_System::get_time())
	{
		_step = (_step + 1) % NUMBER_OF_SENTENCES;
		_next_time = CL_System::get_time() + _sentences_time[_step];
		_sentences[_step].update();
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

		// ...and a my_new one is created !
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

		// ...so start a my_new game and have fun !
	case 15:
		break;
	}

	_demo_player.update();
}

void TitleState::events(Window & window)
{
	CL_InputContext & ic = window.get_ic();
	CL_InputDevice &keyboard = ic.get_keyboard();
	if(_p_common_resources -> key.enter -> get(ic) || keyboard.get_keycode(CL_KEY_SPACE))
	{
		_p_common_resources -> p_engine -> set_state_ingame();
		_p_common_resources -> player1.new_game();
	}

	if(_p_common_resources-> key.escape -> get(ic) || _p_common_resources -> key.pause -> get(ic))
	{
		_p_common_resources -> p_engine -> set_state_pause_menu();
	}

	if(_p_common_resources -> key.skins -> get(ic))
	{
		_p_common_resources -> p_engine -> set_state_skin_menu();
	}

	if(_p_common_resources->key.options -> get(ic) )
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
