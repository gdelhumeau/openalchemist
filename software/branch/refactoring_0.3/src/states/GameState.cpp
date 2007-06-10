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
  return;
}


GameState::~GameState()
{
  return;
}

void GameState::init()
{
  std::cout << "GameState class may not be used cause it is an abstract class" << std::endl;
}


void GameState::deinit()
{
  std::cout << "GameState class may not be used cause it is an abstract class" << std::endl;
}


void GameState::load_gfx(std::string skin)
{
  std::cout << "GameState class may not be used cause it is an abstract class" << std::endl;
}


void GameState::unload_gfx()
{
  std::cout << "GameState class may not be used cause it is an abstract class" << std::endl;
}


void GameState::draw()
{
  std::cout << "GameState class may not be used cause it is an abstract class" << std::endl;
}


void GameState::update()
{
  std::cout << "GameState class may not be used cause it is an abstract class" << std::endl;
}


void GameState::events()
{
  std::cout << "GameState class may not be used cause it is an abstract class" << std::endl;
}

