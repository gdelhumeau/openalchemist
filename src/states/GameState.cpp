// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : GameState.cpp
//  Description : Describe the generic GameState
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

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
