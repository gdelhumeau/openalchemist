/********************************************************************
                          OpenAlchemist

  File : CommonState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "CommonState.h"
#include "../GameEngine.h"
#include "../CommonResources.h"
#include "../KeyboardKey.h"
#include "../misc.h"

CommonState::CommonState()
{
  background = NULL;
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
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("general.xml",&zip, false);

  background = new CL_Surface("background", &gfx);
}


void CommonState::unload_gfx()
{
  if(background)
  {
    delete background;
    background = NULL;
  }

}


void CommonState::draw()
{
  background -> draw(0, 0);
  common_resources -> main_font -> draw(580,550,to_string(common_resources -> engine -> get_fps()));

  if(common_resources -> current_player)
    common_resources -> current_player -> draw();
}


void CommonState::update()
{

}


void CommonState::events()
{
  if(common_resources->key.fullscreen -> get())
  {
    common_resources -> engine -> toggle_screen();
  }
}

bool CommonState::front_layer_behind()
{
  return false;
}
