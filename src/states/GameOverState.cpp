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

#include "GameOverState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"
#include "../Window.h"

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
GameOverState::GameOverState()
{
	_is_highscore = false;
	_quit_enabled = false;
}

/************************************************************************/
/* Destructor                                                           */
/************************************************************************/
GameOverState::~GameOverState()
{
	unload_gfx();
}

/************************************************************************/
/* Init                                                                 */
/************************************************************************/
void GameOverState::init()
{
	_items.clear();
	_items.push_back(&_quit_choice_item);
}

/************************************************************************/
/* Term                                                                 */
/************************************************************************/
void GameOverState::term()
{

}

/************************************************************************/
/* Load GFX                                                             */
/************************************************************************/
void GameOverState::load_gfx(CL_GraphicContext & gc, std::string skin)
{
	unload_gfx();

	// Getting skins resources
	CL_VirtualFileSystem vfs(skin, true);
	CL_VirtualDirectory vd(vfs, "./");	
	CL_ResourceManager gfx("menu_gameover.xml",vd);

	_dialog_gameover = CL_Sprite(gc, "menu_gameover/dialog_gameover", &gfx);
	_dialog_highscore = CL_Sprite(gc, "menu_gameover/dialog_highscore", &gfx);
	_score1_x = CL_Integer_to_int("menu_gameover/score1_left", &gfx);
	_score1_y = CL_Integer_to_int("menu_gameover/score1_top", &gfx);
	_score2_x = CL_Integer_to_int("menu_gameover/score2_left", &gfx);
	_score2_y = CL_Integer_to_int("menu_gameover/score2_top", &gfx);

	_quit_choice_item.set_gfx(gc, gfx, 
		"menu_gameover/new_game_question/yes/unselected",
		"menu_gameover/new_game_question/yes/selected",
		"menu_gameover/new_game_question/no/unselected",
		"menu_gameover/new_game_question/no/selected");

	_quit_choice_item.set_x(
		CL_Integer_to_int("menu_gameover/new_game_question/yes/left", &gfx));
	_quit_choice_item.set_x2(
		CL_Integer_to_int("menu_gameover/new_game_question/no/left", &gfx));
	_quit_choice_item.set_y(
		CL_Integer_to_int("menu_gameover/new_game_question/yes/top", &gfx));
	_quit_choice_item.set_y2(
		CL_Integer_to_int("menu_gameover/new_game_question/no/top", &gfx));
}

/************************************************************************/
/* Unload GFX                                                           */
/************************************************************************/
void GameOverState::unload_gfx()
{

}

/************************************************************************/
/* Draw                                                                 */
/************************************************************************/
void GameOverState::draw(CL_GraphicContext & gc)
{
	MenuState::draw(gc);

	if(_is_highscore)
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
}

/************************************************************************/
/* Events                                                               */
/************************************************************************/
void GameOverState::events(Window & window)
{
	MenuState::events(window);
		
	CL_InputContext & ic = window.get_ic();

	if(_p_common_resources -> key.retry.get(ic))
	{
		_p_common_resources -> p_engine -> stop_current_state();
		_p_common_resources -> p_engine -> set_state_ingame();
		_p_common_resources -> player1.new_game();
	}

	if(_p_common_resources -> key.undo.get(ic))
	{
		_p_common_resources -> p_engine -> set_state_ingame();
		_p_common_resources -> player1.undo();
	}

	if(_p_common_resources->key.skins.get(ic))
	{
		_p_common_resources -> p_engine -> set_state_skin_menu();
	}
}

/************************************************************************/
/* Set mode                                                             */
/************************************************************************/
void GameOverState::set_highscore(bool highscore)
{
	_is_highscore = highscore;
	if(_is_highscore)
	{
		_background = _dialog_highscore;
	}
	else
	{
		_background = _dialog_gameover;
	}
}

/************************************************************************/
/* Action performed                                                     */
/************************************************************************/
void GameOverState::action_performed(int selection, ActionType action_type)
{
	switch(action_type)
	{
	case ACTION_TYPE_ENTER:
	case ACTION_TYPE_MOUSE:
		if(_quit_choice_item.get_selection() == CHOICE_LEFT)
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
		break;
	default:
		break;
	}
}

/************************************************************************/
/* Update child                                                         */
/************************************************************************/
void GameOverState::update_child()
{
	
}
