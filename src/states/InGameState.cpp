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
  _p_common_resources -> player1.update();
}

void InGameState::events()
{
  _p_common_resources -> player1.events();

  if(_p_common_resources -> key.escape -> get() || _p_common_resources ->key.pause->get())
  {
    _p_common_resources -> p_engine -> set_state_pause_menu();
  }

  if(_p_common_resources->key.skins -> get())
  {
    _p_common_resources -> p_engine -> set_state_skin_menu();
  }

  if(_p_common_resources->key.options -> get() )
  {
    _p_common_resources -> p_engine -> set_state_options_menu();
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



