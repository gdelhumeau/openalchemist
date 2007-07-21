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
  key_echap  = new KeyboardKey(CL_KEY_ESCAPE, false);
  key_pause  = new KeyboardKey(CL_KEY_PAUSE , false);
}

void InGameState::deinit()
{
  delete key_echap;
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

  if(key_echap->get() || key_pause->get())
  {
    common_resources -> engine -> set_state_pause_menu();
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



