/********************************************************************
                          OpenAlchemist

  File : InGameState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include "InGameState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"

void InGameState::init()
{
  GameState::init();
}

void InGameState::deinit()
{
  GameState::deinit();
}

void InGameState::load_gfx(std::string skin)
{

}

void InGameState::unload_gfx()
{

}

void InGameState::draw()
{
  
}

void InGameState::update()
{
  common_resources -> player1.update();
}

void InGameState::events()
{
  common_resources -> player1.events();

  if(common_resources -> key.escape -> get() || common_resources ->key.pause->get())
  {
    common_resources -> engine -> set_state_pause_menu();
  }

  if(common_resources->key.skins -> get())
  {
    common_resources -> engine -> set_state_skin_menu();
  }

  if(common_resources->key.options -> get() )
  {
    common_resources -> engine -> set_state_options_menu();
  }

}

bool InGameState::front_layer_behind()
{
  return false;
}

InGameState::InGameState()
{

}

InGameState::~InGameState()
{

}



