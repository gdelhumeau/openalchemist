// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : GameOverState.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include "../memory.h"
#include "GameOverState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"
#include "../Window.h"

#pragma warning(disable:4244)

void GameOverState::init()
{
	GameState::init();
	_selection = GAMEOVER_SELECTION_YES;
}

void GameOverState::deinit()
{

}

void GameOverState::load_gfx(CL_GraphicContext & gc, std::string skin)
{
	unload_gfx();

	// Getting skins resources
	CL_VirtualFileSystem vfs(skin, true);
	CL_VirtualDirectory vd(vfs, "./");	
	CL_ResourceManager gfx("menu_gameover.xml",vd);

	_dialog_gameover = CL_Sprite(gc, "menu_gameover/dialog_gameover", &gfx);
	_dialog_highscore = CL_Sprite(gc, "menu_gameover/dialog_highscore", &gfx);
	_dialog_x = CL_Integer_to_int("menu_gameover/dialog_left", &gfx);
	_dialog_y = CL_Integer_to_int("menu_gameover/dialog_top", &gfx);
	_score1_x = CL_Integer_to_int("menu_gameover/score1_left", &gfx);
	_score1_y = CL_Integer_to_int("menu_gameover/score1_top", &gfx);
	_score2_x = CL_Integer_to_int("menu_gameover/score2_left", &gfx);
	_score2_y = CL_Integer_to_int("menu_gameover/score2_top", &gfx);

	_yes_selected = CL_Sprite(gc, "menu_gameover/new_game_question/yes/selected", &gfx);
	_yes_unselected = CL_Sprite(gc, "menu_gameover/new_game_question/yes/unselected", &gfx);

	_no_selected = CL_Sprite(gc, "menu_gameover/new_game_question/no/selected", &gfx);
	_no_unselected = CL_Sprite(gc, "menu_gameover/new_game_question/no/unselected", &gfx);

	_yes_x = CL_Integer_to_int("menu_gameover/new_game_question/yes/left", &gfx);
	_yes_y = CL_Integer_to_int("menu_gameover/new_game_question/yes/top", &gfx);

	_no_x = CL_Integer_to_int("menu_gameover/new_game_question/no/left", &gfx);
	_no_y = CL_Integer_to_int("menu_gameover/new_game_question/no/top", &gfx);
}


void GameOverState::unload_gfx()
{



}

void GameOverState::draw(CL_GraphicContext & gc)
{
	_dialog.draw(gc, _dialog_x, _dialog_y);


	if(MODE_HIGHSCORE == _mode)
	{
		std::string new_score = format_number(to_string(_p_common_resources -> highscore));
		std::string old_score = format_number(to_string(_p_common_resources -> old_highscore));

		int new_score_real_x = _score1_x -
			_p_common_resources -> main_font.get_text_size(gc, new_score).width / 2;

		int old_score_real_x = _score2_x - 
			_p_common_resources -> main_font.get_text_size(gc, old_score).width / 2;

		_p_common_resources -> main_font.draw_text(gc, new_score_real_x, _score1_y, new_score);
		_p_common_resources -> main_font.draw_text(gc, old_score_real_x, _score2_y, old_score);
	}
	else
	{
		std::string current_score = format_number(to_string(_p_common_resources -> player1.get_score()));
		std::string highscore = format_number(to_string(_p_common_resources -> highscore));

		int score1_real_x = _score1_x -
			_p_common_resources -> main_font.get_text_size(gc, current_score).width / 2;

		int score2_real_x = _score2_x - 
			_p_common_resources -> main_font.get_text_size(gc, highscore).width / 2;

		_p_common_resources -> main_font.draw_text(gc, score1_real_x, _score1_y, current_score);
		_p_common_resources -> main_font.draw_text(gc, score2_real_x, _score2_y, highscore);
	}

	if(_selection == GAMEOVER_SELECTION_YES)
	{
		_yes_selected.draw(gc, _yes_x, _yes_y);
		_no_unselected.draw(gc, _no_x, _no_y);
	}
	else
	{
		_yes_unselected.draw(gc, _yes_x, _yes_y);
		_no_selected.draw(gc, _no_x, _no_y);
	}
}

void GameOverState::update(CL_GraphicContext & gc)
{

}

void GameOverState::events(Window & window)
{
	CL_InputContext & ic = window.get_ic();
	if(_p_common_resources -> key.enter -> get(ic))
	{

		if(_selection == GAMEOVER_SELECTION_YES)
		{
			_p_common_resources -> p_engine -> stop_current_state();
			_p_common_resources -> p_engine -> set_state_ingame();
			_p_common_resources -> player1.new_game();
		}
		else
		{
			_p_common_resources -> p_engine -> stop_current_state();
			_p_common_resources -> p_engine -> set_state_title();
		}
	}

	if(_p_common_resources -> key.retry -> get(ic))
	{
		_p_common_resources -> p_engine -> stop_current_state();
		_p_common_resources -> p_engine -> set_state_ingame();
		_p_common_resources -> player1.new_game();
	}

	if(_p_common_resources -> key.undo -> get(ic))
	{
		_p_common_resources -> p_engine -> set_state_ingame();
		_p_common_resources -> player1.undo();
	}

	if(_p_common_resources -> key.escape -> get(ic) ||
		_p_common_resources ->key.pause->get(ic))
	{
		_p_common_resources -> p_engine -> stop_current_state();
		_p_common_resources -> p_engine -> set_state_title();
		//    common_resources -> engine -> set_state_pause_menu();
	}

	if(_p_common_resources->key.skins -> get(ic))
	{
		_p_common_resources -> p_engine -> set_state_skin_menu();
	}

	if(_p_common_resources -> key.left -> get(ic))
	{
		_selection = GAMEOVER_SELECTION_YES;
	}

	if(_p_common_resources -> key.right -> get(ic))
	{
		_selection = GAMEOVER_SELECTION_NO;
	}

}

bool GameOverState::front_layer_behind()
{
	return true;
}

void GameOverState::set_mode(int mode)
{
	this -> _mode = mode;
	if(mode == MODE_GAMEOVER)
	{
		_dialog = _dialog_gameover;
	}
	else
	{
		_dialog = _dialog_highscore;
	}
}

void GameOverState::start()
{
	_selection = GAMEOVER_SELECTION_YES;
}

GameOverState::GameOverState()
{

}

GameOverState::~GameOverState()
{
	unload_gfx();
}

