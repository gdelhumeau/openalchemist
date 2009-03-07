/********************************************************************
                          OpenAlchemist

  File : GameOverState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include "GameOverState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"

void GameOverState::init()
{
  GameState::init();
  _selection = GAMEOVER_SELECTION_YES;
}

void GameOverState::deinit()
{

}

void GameOverState::load_gfx(std::string skin)
{
  // Getting skins resources
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("menu_gameover.xml", &zip, false);

  _p_dialog_gameover = new CL_Sprite("menu_gameover/dialog_gameover", &gfx);
  _p_dialog_highscore = new CL_Sprite("menu_gameover/dialog_highscore", &gfx);
  _dialog_x = CL_Integer_to_int("menu_gameover/dialog_left", &gfx);
  _dialog_y = CL_Integer_to_int("menu_gameover/dialog_top", &gfx);
  _score1_x = CL_Integer_to_int("menu_gameover/score1_left", &gfx);
  _score1_y = CL_Integer_to_int("menu_gameover/score1_top", &gfx);
  _score2_x = CL_Integer_to_int("menu_gameover/score2_left", &gfx);
  _score2_y = CL_Integer_to_int("menu_gameover/score2_top", &gfx);

  _p_yes_selected = new CL_Sprite("menu_gameover/new_game_question/yes/selected", &gfx);
  _p_yes_unselected = new CL_Sprite("menu_gameover/new_game_question/yes/unselected", &gfx);

  _p_no_selected = new CL_Sprite("menu_gameover/new_game_question/no/selected", &gfx);
  _p_no_unselected = new CL_Sprite("menu_gameover/new_game_question/no/unselected", &gfx);

  _yes_x = CL_Integer_to_int("menu_gameover/new_game_question/yes/left", &gfx);
  _yes_y = CL_Integer_to_int("menu_gameover/new_game_question/yes/top", &gfx);

  _no_x = CL_Integer_to_int("menu_gameover/new_game_question/no/left", &gfx);
  _no_y = CL_Integer_to_int("menu_gameover/new_game_question/no/top", &gfx);
}


void GameOverState::unload_gfx()
{

  if(_p_dialog_gameover)
  {
    delete _p_dialog_gameover;
    _p_dialog_gameover = NULL;
  }

  if(_p_dialog_highscore)
  {
    delete _p_dialog_highscore;
    _p_dialog_highscore = NULL;
  }


  if(_p_yes_selected)
  {
    delete _p_yes_selected;
    _p_yes_selected = NULL;
  }

  if(_p_yes_unselected)
  {
    delete _p_yes_unselected;
    _p_yes_unselected = NULL;
  }

  if(_p_no_selected)
  {
    delete _p_no_selected;
    _p_no_selected = NULL;
  }

  if(_p_no_unselected)
  {
    delete _p_no_unselected;
    _p_no_unselected = NULL;
  }

}

void GameOverState::draw()
{
  _p_dialog -> draw(_dialog_x, _dialog_y);


  if(MODE_HIGHSCORE == _mode)
  {
    std::string new_score = format_number(to_string(_p_common_resources -> highscore));
    std::string old_score = format_number(to_string(_p_common_resources -> old_highscore));

    int new_score_real_x = _score1_x -
      _p_common_resources -> p_main_font -> get_width(new_score, CL_Size(0, 0)) / 2;

    int old_score_real_x = _score2_x - 
      _p_common_resources -> p_main_font -> get_width(old_score, CL_Size(0, 0)) / 2;

    _p_common_resources -> p_main_font -> draw(new_score_real_x, _score1_y, new_score);
    _p_common_resources -> p_main_font -> draw(old_score_real_x, _score2_y, old_score);
  }
  else
  {
    std::string current_score = format_number(to_string(_p_common_resources -> player1.get_score()));
    std::string highscore = format_number(to_string(_p_common_resources -> highscore));

    int score1_real_x = _score1_x -
      _p_common_resources -> p_main_font -> get_width(current_score, CL_Size(0, 0)) / 2;

    int score2_real_x = _score2_x - 
      _p_common_resources -> p_main_font -> get_width(highscore, CL_Size(0, 0)) / 2;

    _p_common_resources -> p_main_font -> draw(score1_real_x, _score1_y, current_score);
    _p_common_resources -> p_main_font -> draw(score2_real_x, _score2_y, highscore);
  }

  if(_selection == GAMEOVER_SELECTION_YES)
  {
    _p_yes_selected -> draw(_yes_x, _yes_y);
    _p_no_unselected  -> draw(_no_x, _no_y);
  }
  else
  {
    _p_yes_unselected -> draw(_yes_x, _yes_y);
    _p_no_selected  -> draw(_no_x, _no_y);
  }
}

void GameOverState::update()
{
  
}

void GameOverState::events()
{
  if(_p_common_resources -> key.enter -> get())
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

  if(_p_common_resources -> key.retry -> get())
  {
    _p_common_resources -> p_engine -> stop_current_state();
    _p_common_resources -> p_engine -> set_state_ingame();
    _p_common_resources -> player1.new_game();
  }

  if(_p_common_resources -> key.undo -> get())
  {
    _p_common_resources -> p_engine -> set_state_ingame();
    _p_common_resources -> player1.undo();
  }

  if(_p_common_resources -> key.escape -> get() || _p_common_resources ->key.pause->get())
  {
    _p_common_resources -> p_engine -> stop_current_state();
    _p_common_resources -> p_engine -> set_state_title();
//    common_resources -> engine -> set_state_pause_menu();
  }

  if(_p_common_resources->key.skins -> get())
  {
    _p_common_resources -> p_engine -> set_state_skin_menu();
  }

  if(_p_common_resources -> key.left -> get())
  {
    _selection = GAMEOVER_SELECTION_YES;
  }

  if(_p_common_resources -> key.right -> get())
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
    _p_dialog = _p_dialog_gameover;
  }
  else
  {
    _p_dialog = _p_dialog_highscore;
  }
}

void GameOverState::start()
{
  _selection = GAMEOVER_SELECTION_YES;
}

GameOverState::GameOverState()
{
  _p_dialog_gameover  = NULL;
  _p_dialog_highscore = NULL;

  _p_yes_selected     = NULL;
  _p_yes_unselected   = NULL;
  _p_no_selected      = NULL;
  _p_no_unselected    = NULL;
}

GameOverState::~GameOverState()
{
  unload_gfx();
}

