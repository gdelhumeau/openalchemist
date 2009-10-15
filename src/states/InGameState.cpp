// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : InGameState.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include "../memory.h"
#include "InGameState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"
#include "../Window.h"

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
InGameState::InGameState()
{

}

/************************************************************************/
/* Destructor                                                           */
/************************************************************************/
InGameState::~InGameState()
{

}

/************************************************************************/
/* Init                                                                 */
/************************************************************************/
void InGameState::init()
{
}

/************************************************************************/
/* Term                                                                 */
/************************************************************************/
void InGameState::deinit()
{
}

/************************************************************************/
/* Load GFX                                                             */
/************************************************************************/
void InGameState::load_gfx(CL_GraphicContext & gc, std::string skin)
{

}

/************************************************************************/
/* Unload GFX                                                           */
/************************************************************************/
void InGameState::unload_gfx()
{

}

/************************************************************************/
/* Draw                                                                 */
/************************************************************************/
void InGameState::draw(CL_GraphicContext & gc)
{

}

/************************************************************************/
/* Update                                                               */
/************************************************************************/
void InGameState::update(CL_GraphicContext & gc)
{
	_p_common_resources -> player1.update();
}

/************************************************************************/
/* Events                                                               */
/************************************************************************/
void InGameState::events(Window & window)
{
	CL_InputContext & ic = window.get_ic();
	_p_common_resources -> player1.events(ic);

	if(_p_common_resources -> key.escape -> get(ic) || _p_common_resources ->key.pause->get(ic))
	{
		_p_common_resources -> p_engine -> set_state_pause_menu();
	}

	if(_p_common_resources->key.skins -> get(ic))
	{
		_p_common_resources -> p_engine -> set_state_skin_menu();
	}

	if(_p_common_resources->key.options -> get(ic) )
	{
		_p_common_resources -> p_engine -> set_state_options_menu();
	}

}

/************************************************************************/
/* Front layer behind                                                   */
/************************************************************************/
bool InGameState::front_layer_behind()
{
	return false;
}