/********************************************************************
                          OpenAlchemist

  File : GameState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <iostream>
#include "GameState.h"
#include "../CommonResources.h"
#include "../memory.h"

GameState::GameState()
{
	  _p_common_resources = common_resources_get_instance();
  return;
}


GameState::~GameState()
{
  return;
}

void GameState::init()
{

}


void GameState::deinit()
{
 
}
