// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : CommonState.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "../memory.h"
#include "CommonState.h"
#include "../GameEngine.h"
#include "../CommonResources.h"
#include "../KeyboardKey.h"
#include "../misc.h"
#include "../Preferences.h"

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
CommonState::CommonState()
{
	_enable_framerate_drawing = false;
}

/************************************************************************/
/* Destructor                                                           */
/************************************************************************/
CommonState::~CommonState()
{
	unload_gfx();
	term();
}

/************************************************************************/
/* Init                                                                 */
/************************************************************************/
void CommonState::init()
{
}

/************************************************************************/
/* Terminate                                                            */
/************************************************************************/
void CommonState::term()
{
}

/************************************************************************/
/* Load GFX                                                             */
/************************************************************************/
void CommonState::load_gfx(CL_GraphicContext & gc, std::string skin)
{
	unload_gfx();

	CL_VirtualFileSystem vfs(skin, true);
	CL_VirtualDirectory vd(vfs, "./");	
	CL_ResourceManager gfx("general.xml",vd);

	_background = CL_Image(gc, "background", &gfx);
}

/************************************************************************/
/* Unload GFX                                                           */
/************************************************************************/
void CommonState::unload_gfx()
{

}

/************************************************************************/
/* Draw                                                                 */
/************************************************************************/
void CommonState::draw(CL_GraphicContext & gc)
{
	_background.draw(gc, 0, 0);
	if(_enable_framerate_drawing)
	{
		_p_common_resources -> main_font.draw_text(gc, 580.0f,580.0f,
			to_string(_p_common_resources -> p_engine -> get_fps()));
	}

	if(_p_common_resources -> p_current_player)
		_p_common_resources -> p_current_player -> draw(gc);
}

/************************************************************************/
/* Update                                                               */
/************************************************************************/
void CommonState::update(CL_GraphicContext & gc)
{

}

/************************************************************************/
/* Events                                                               */
/************************************************************************/
void CommonState::events(Window & window)
{
	CL_InputContext & ic = window.get_ic();
	if(_p_common_resources->key.framerate.get(ic))
	{
		_enable_framerate_drawing = !_enable_framerate_drawing;
	}
	if(_p_common_resources->key.fullscreen.get(ic))
	{
		_p_common_resources -> p_engine -> toggle_screen();
	}
}

/************************************************************************/
/* Front layer behind                                                   */
/************************************************************************/
bool CommonState::front_layer_behind()
{
	return false;
}