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
  panel_x = CL_Integer_to_int("gameover_x", &gfx);
  panel_y = CL_Integer_to_int("gameover_y", &gfx);
  new_score_y = CL_Integer_to_int("menu/new-hightscore/new-score-top", &gfx);
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
  common_resources -> main_font -> draw(385, new_score_y, to_string(common_resources -> player1.get_score()));
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



