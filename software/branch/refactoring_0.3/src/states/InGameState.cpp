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
  common_resources -> main_font -> draw(10,10,"42");
}

void InGameState::update()
{

}

void InGameState::events()
{

}

InGameState::InGameState()
{

}

InGameState::~InGameState()
{

}



