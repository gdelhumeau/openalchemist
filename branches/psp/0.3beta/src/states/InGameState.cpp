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
#include <SDL/SDL.h>

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
  switch(common_resources->CurrentKeyPressed)
  {
	  case KEY_ESCAPE:
	  case KEY_PAUSE:
	  {
	    common_resources -> engine -> set_state_pause_menu();
	    common_resources->CurrentKeyPressed = 0;
	    break;
	  }
	
	  case KEY_SKINS:
	  {
	    common_resources -> engine -> set_state_skin_menu();
	    common_resources->CurrentKeyPressed = 0;
	    break;
	  }
	
	  case KEY_OPTIONS:
	  {
	    common_resources -> engine -> set_state_options_menu();
	    common_resources->CurrentKeyPressed = 0;
	    break;
	  }
	
   }
}

bool InGameState::front_layer_behind()
{
  return false;
}

void InGameState::print()
{
  printf("InGameState\n");
}

InGameState::InGameState()
{

}

InGameState::~InGameState()
{

}



