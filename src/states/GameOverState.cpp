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
  selection = GAMEOVER_SELECTION_YES;
}

void GameOverState::deinit()
{

}

void GameOverState::load_gfx(std::string skin)
{
  // Getting skins resources
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("menu_gameover.xml", &zip, false);

  dialog_gameover = new CL_Sprite("menu_gameover/dialog_gameover", &gfx);
  dialog_highscore = new CL_Sprite("menu_gameover/dialog_highscore", &gfx);
  dialog_x = CL_Integer_to_int("menu_gameover/dialog_left", &gfx);
  dialog_y = CL_Integer_to_int("menu_gameover/dialog_top", &gfx);
  score1_x = CL_Integer_to_int("menu_gameover/score1_left", &gfx);
  score1_y = CL_Integer_to_int("menu_gameover/score1_top", &gfx);
  score2_x = CL_Integer_to_int("menu_gameover/score2_left", &gfx);
  score2_y = CL_Integer_to_int("menu_gameover/score2_top", &gfx);

  yes_selected = new CL_Sprite("menu_gameover/new_game_question/yes/selected", &gfx);
  yes_unselected = new CL_Sprite("menu_gameover/new_game_question/yes/unselected", &gfx);

  no_selected = new CL_Sprite("menu_gameover/new_game_question/no/selected", &gfx);
  no_unselected = new CL_Sprite("menu_gameover/new_game_question/no/unselected", &gfx);

  yes_x = CL_Integer_to_int("menu_gameover/new_game_question/yes/left", &gfx);
  yes_y = CL_Integer_to_int("menu_gameover/new_game_question/yes/top", &gfx);

  no_x = CL_Integer_to_int("menu_gameover/new_game_question/no/left", &gfx);
  no_y = CL_Integer_to_int("menu_gameover/new_game_question/no/top", &gfx);
}


void GameOverState::unload_gfx()
{

  if(dialog_gameover)
  {
    delete dialog_gameover;
    dialog_gameover = NULL;
  }

  if(dialog_highscore)
  {
    delete dialog_highscore;
    dialog_highscore = NULL;
  }


  if(yes_selected)
  {
    delete yes_selected;
    yes_selected = NULL;
  }

  if(yes_unselected)
  {
    delete yes_unselected;
    yes_unselected = NULL;
  }

  if(no_selected)
  {
    delete no_selected;
    no_selected = NULL;
  }

  if(no_unselected)
  {
    delete no_unselected;
    no_unselected = NULL;
  }

}

void GameOverState::draw()
{
  dialog -> draw(dialog_x, dialog_y);


  if(MODE_HIGHSCORE == mode)
  {
    std::string new_score = format_number(to_string(common_resources -> highscore));
    std::string old_score = format_number(to_string(common_resources -> old_highscore));

    int new_score_real_x = score1_x -
      common_resources -> main_font -> get_width(new_score, CL_Size(0, 0)) / 2;

    int old_score_real_x = score2_x - 
      common_resources -> main_font -> get_width(old_score, CL_Size(0, 0)) / 2;

    common_resources -> main_font -> draw(new_score_real_x, score1_y, new_score);
    common_resources -> main_font -> draw(old_score_real_x, score2_y, old_score);
  }
  else
  {
    std::string current_score = format_number(to_string(common_resources -> player1.get_score()));
    std::string highscore = format_number(to_string(common_resources -> highscore));

    int score1_real_x = score1_x -
      common_resources -> main_font -> get_width(current_score, CL_Size(0, 0)) / 2;

    int score2_real_x = score2_x - 
      common_resources -> main_font -> get_width(highscore, CL_Size(0, 0)) / 2;

    common_resources -> main_font -> draw(score1_real_x, score1_y, current_score);
    common_resources -> main_font -> draw(score2_real_x, score2_y, highscore);
  }

  if(selection == GAMEOVER_SELECTION_YES)
  {
    yes_selected -> draw(yes_x, yes_y);
    no_unselected  -> draw(no_x, no_y);
  }
  else
  {
    yes_unselected -> draw(yes_x, yes_y);
    no_selected  -> draw(no_x, no_y);
  }
}

void GameOverState::update()
{
  
}

void GameOverState::events()
{
  if(common_resources -> key.enter -> get())
  {

    if(selection == GAMEOVER_SELECTION_YES)
    {
      common_resources -> engine -> stop_current_state();
      common_resources -> engine -> set_state_ingame();
      common_resources -> player1.new_game();
    }
    else
    {
      common_resources -> engine -> stop_current_state();
      common_resources -> engine -> set_state_title();
    }
  }

  if(common_resources -> key.retry -> get())
  {
    common_resources -> engine -> stop_current_state();
    common_resources -> engine -> set_state_ingame();
    common_resources -> player1.new_game();
  }

  if(common_resources -> key.undo -> get())
  {
    common_resources -> engine -> set_state_ingame();
    common_resources -> player1.undo();
  }

  if(common_resources -> key.escape -> get() || common_resources ->key.pause->get())
  {
    common_resources -> engine -> stop_current_state();
    common_resources -> engine -> set_state_title();
//    common_resources -> engine -> set_state_pause_menu();
  }

  if(common_resources->key.skins -> get())
  {
    common_resources -> engine -> set_state_skin_menu();
  }

  if(common_resources -> key.left -> get())
  {
    selection = GAMEOVER_SELECTION_YES;
  }

  if(common_resources -> key.right -> get())
  {
    selection = GAMEOVER_SELECTION_NO;
  }



}

bool GameOverState::front_layer_behind()
{
  return true;
}

void GameOverState::set_mode(int mode)
{
  this -> mode = mode;
  if(mode == MODE_GAMEOVER)
  {
    dialog = dialog_gameover;
  }
  else
  {
    dialog = dialog_highscore;
  }
}

void GameOverState::start()
{
  selection = GAMEOVER_SELECTION_YES;
}

GameOverState::GameOverState()
{
  dialog_gameover  = NULL;
  dialog_highscore = NULL;

  yes_selected     = NULL;
  yes_unselected   = NULL;
  no_selected      = NULL;
  no_unselected    = NULL;
}

GameOverState::~GameOverState()
{
  unload_gfx();
}

