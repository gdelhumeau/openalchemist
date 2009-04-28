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
  _p_background = NULL;
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


void CommonState::load_gfx(std::string skin)
{
	unload_gfx();
	
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("general.xml",&zip, false);

  _p_background = my_new CL_Surface("background", &gfx);
}


void CommonState::unload_gfx()
{
  if(_p_background)
  {
    my_delete(_p_background);
    _p_background = NULL;
  }

}


void CommonState::draw()
{
  _p_background -> draw(0, 0);
  _p_common_resources -> p_main_font -> draw(580,550,to_string(_p_common_resources -> p_engine -> get_fps()));

  if(_p_common_resources -> p_current_player)
    _p_common_resources -> p_current_player -> draw();
}


void CommonState::update()
{

}


void CommonState::events()
{
  if(_p_common_resources->key.fullscreen -> get())
  {
    _p_common_resources -> p_engine -> toggle_screen();
  }
}

bool CommonState::front_layer_behind()
{
  return false;
}
