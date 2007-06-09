/********************************************************************
                          OpenAlchemist

  File : GameState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/


#include "GameState.h"
#include <iostream>


GameState::GameState()
{
  std::cout << "GameState class may not be instanced cause it is an abstract class" << std::endl;
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


void GameState::load_gfx(std::string skin)
{

}


void GameState::unload_gfx()
{

}


void GameState::draw()
{

}


void GameState::update()
{

}


void GameState::events()
{

}

