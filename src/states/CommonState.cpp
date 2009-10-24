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
	_p_common_resources -> main_font.draw_text(gc, 580.0f,550.0f,
		to_string(_p_common_resources -> p_engine -> get_fps()));

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
#ifdef DEBUG
	CL_InputDevice &keyboard = ic.get_keyboard();
	if(keyboard.get_keycode(CL_KEY_S))
	{
		_p_common_resources -> p_engine -> set_skin("/home/keph/documents/dev/openalchemist/svn/trunk/skins/aqua.zip");
	}
	if(keyboard.get_keycode(CL_KEY_D))
	{
		_p_common_resources -> p_engine -> set_skin("/home/keph/documents/dev/openalchemist/svn/trunk/skins/vectoriel.zip");
	}
#endif

	if(_p_common_resources->key.fullscreen -> get(ic))
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