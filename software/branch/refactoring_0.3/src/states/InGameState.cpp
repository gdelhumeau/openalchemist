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
}

InGameState::InGameState()
{

}

InGameState::~InGameState()
{

}



