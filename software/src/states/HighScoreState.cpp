/********************************************************************
                          OpenAlchemist

  File : HighScoreState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include "HighScoreState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"

void HighScoreState::init()
{
  GameState::init();

  panel = NULL;
}

void HighScoreState::deinit()
{

}

void HighScoreState::load_gfx(std::string skin)
{
  // Getting skins resources
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("menu_highscores.xml", &zip, false);

  panel = new CL_Sprite("menu-new-highscore/dialog", &gfx);
  panel_x = CL_Integer_to_int("menu-new-highscore/panel_x", &gfx);
  panel_y = CL_Integer_to_int("menu-new-highscore/panel_y", &gfx);
  new_score_x = CL_Integer_to_int("menu-nehighscore/new-score-left", &gfx);
  new_score_y = CL_Integer_to_int("menu-new-highscore/new-score-top", &gfx);
  old_score_x = CL_Integer_to_int("menu-new-highscore/old-score-left", &gfx);
  old_score_y = CL_Integer_to_int("menu-new-highscore/old-score-top", &gfx);
}

void HighScoreState::unload_gfx()
{
  if(panel)
  {
    delete panel;
    panel = NULL;
  }
}

void HighScoreState::draw()
{
  panel -> draw(panel_x, panel_y);

  std::string new_score = format_number(to_string(common_resources -> highscore));
  std::string old_score = format_number(to_string(common_resources -> old_highscore));

  int new_score_real_x = new_score_x -
    common_resources -> main_font -> get_width(new_score, CL_Size(0, 0)) / 2;

  int old_score_real_x = old_score_x - 
    common_resources -> main_font -> get_width(old_score, CL_Size(0, 0)) / 2;

  common_resources -> main_font -> draw(new_score_real_x, new_score_y, new_score);
  common_resources -> main_font -> draw(old_score_real_x, old_score_y, old_score);
}

void HighScoreState::update()
{

}

void HighScoreState::events()
{
   if(CL_Keyboard::get_keycode(CL_KEY_ENTER))
  {
    common_resources -> engine -> set_state_ingame();
    common_resources -> player1.new_game();
  }

  if(common_resources -> key.undo -> get())
  {
    common_resources -> player1.undo();
    common_resources -> engine -> stop_current_state();
  }

  if(common_resources -> key.escape -> get() || common_resources ->key.pause->get())
  {
    common_resources -> engine -> set_state_pause_menu();
  }

  if(common_resources->key.skins -> get())
  {
    common_resources -> engine -> set_state_skin_menu();
  }
  
}

bool HighScoreState::front_layer_behind()
{
  return true;
}

HighScoreState::HighScoreState()
{

}

HighScoreState::~HighScoreState()
{
  unload_gfx();
}



