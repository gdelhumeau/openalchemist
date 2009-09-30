/********************************************************************
                          OpenAlchemist

  File : CommonState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include "../memory.h"
#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "CommonState.h"
#include "../GameEngine.h"
#include "../CommonResources.h"
#include "../KeyboardKey.h"
#include "../misc.h"
#include "../Preferences.h"

CommonState::CommonState()
{
}


CommonState::~CommonState()
{
	unload_gfx();
	deinit();
}

void CommonState::init()
{
	GameState::init();
}


void CommonState::deinit()
{
}


void CommonState::load_gfx(CL_GraphicContext & gc, std::string skin)
{
	unload_gfx();

	CL_VirtualFileSystem vfs(skin, true);
	CL_VirtualDirectory vd(vfs, "./");	
	CL_ResourceManager gfx("general.xml",vd);

	_background = CL_Image(gc, "background", &gfx);
}


void CommonState::unload_gfx()
{

}


void CommonState::draw(CL_GraphicContext & gc)
{
	_background.draw(gc, 0, 0);
	_p_common_resources -> main_font.draw_text(gc, 580.0f,550.0f,
		to_string(_p_common_resources -> p_engine -> get_fps()));

	if(_p_common_resources -> p_current_player)
		_p_common_resources -> p_current_player -> draw(gc);
}


void CommonState::update(CL_GraphicContext & gc)
{

}


void CommonState::events(CL_DisplayWindow & window)
{
	if(_p_common_resources->key.fullscreen -> get(window))
	{
		_p_common_resources -> p_engine -> toggle_screen();
	}
	CL_InputDevice &keyboard = window.get_ic().get_keyboard();
	if(keyboard.get_keycode(CL_KEY_S))
	{
		_p_common_resources -> p_engine -> set_skin("/home/keph/documents/dev/openalchemist/svn/trunk/skins/aqua.zip");
	}
	if(keyboard.get_keycode(CL_KEY_D))
	{
		_p_common_resources -> p_engine -> set_skin("/home/keph/documents/dev/openalchemist/svn/trunk/skins/vectoriel.zip");
	}
}

bool CommonState::front_layer_behind()
{
	return false;
}
