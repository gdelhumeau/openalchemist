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

  panel = NULL;
}

void GameOverState::deinit()
{

}

void GameOverState::load_gfx(std::string skin)
{
  // Getting skins resources
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("gfx.xml", &zip, false);

  panel = new CL_Surface("gameover", &gfx);
  panel_x = CL_Integer_to_int("gameover_x", &gfx);
  panel_y = CL_Integer_to_int("gameover_y", &gfx);
}

void GameOverState::unload_gfx()
{
  if(panel)
  {
    delete panel;
    panel = NULL;
  }
}

void GameOverState::draw()
{
  panel -> draw(panel_x, panel_y);
}

void GameOverState::update()
{
  
}

void GameOverState::events()
{
  if(common_resources -> key.enter -> get() || common_resources -> key.retry -> get())
  {
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
    common_resources -> engine -> set_state_pause_menu();
  }

  if(common_resources->key.skins -> get())
  {
    common_resources -> engine -> set_state_skin_menu();
  }


}

bool GameOverState::front_layer_behind()
{
  return true;
}

GameOverState::GameOverState()
{

}

GameOverState::~GameOverState()
{
  unload_gfx();
}

