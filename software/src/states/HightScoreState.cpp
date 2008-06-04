/********************************************************************
                          OpenAlchemist

  File : HightScoreState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include "HightScoreState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"

void HightScoreState::init()
{
  GameState::init();

  panel = NULL;
}

void HightScoreState::deinit()
{

}

void HightScoreState::load_gfx(std::string skin)
{
  // Getting skins resources
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("gfx.xml", &zip, false);

  panel = new CL_Sprite("menu/new-hightscore/dialog", &gfx);
  panel_x = CL_Integer_to_int("menu/new-hightscore/panel_x", &gfx);
  panel_y = CL_Integer_to_int("menu/new-hightscore/panel_y", &gfx);
  new_score_x = CL_Integer_to_int("menu/new-hightscore/new-score-left", &gfx);
  new_score_y = CL_Integer_to_int("menu/new-hightscore/new-score-top", &gfx);
  old_score_x = CL_Integer_to_int("menu/new-hightscore/old-score-left", &gfx);
  old_score_y = CL_Integer_to_int("menu/new-hightscore/old-score-top", &gfx);
}

void HightScoreState::unload_gfx()
{
  if(panel)
  {
    delete panel;
    panel = NULL;
  }
}

void HightScoreState::draw()
{
  panel -> draw(panel_x, panel_y);

  std::string new_score = format_number(to_string(common_resources -> hightscores[0]));
  std::string old_score = format_number(to_string(common_resources -> old_hightscore));

  int new_score_real_x = new_score_x -
    common_resources -> main_font -> get_width(new_score, CL_Size(0, 0)) / 2;

  int old_score_real_x = old_score_x - 
    common_resources -> main_font -> get_width(old_score, CL_Size(0, 0)) / 2;

  common_resources -> main_font -> draw(new_score_real_x, new_score_y, new_score);
  common_resources -> main_font -> draw(old_score_real_x, old_score_y, old_score);
}

void HightScoreState::update()
{

}

void HightScoreState::events()
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();  

  if(CL_Keyboard::get_keycode(CL_KEY_ENTER))
  {
    resources -> engine -> set_state_ingame();
    resources -> player1.new_game();
  }

  if(resources -> key.undo -> get())
  {
    resources -> player1.undo();
    resources -> engine -> stop_current_state();
  }
}

bool HightScoreState::front_layer_behind()
{
  return true;
}

HightScoreState::HightScoreState()
{

}

HightScoreState::~HightScoreState()
{
  unload_gfx();
}



