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
  key_fullscreen = NULL;
}


CommonState::~CommonState()
{
  unload_gfx();
  deinit();
}

void CommonState::init()
{
  GameState::init();
  key_fullscreen  = new KeyboardKey(CL_KEY_F11, false);
}


void CommonState::deinit()
{
  if(key_fullscreen)
  {
    delete key_fullscreen;
    key_fullscreen = NULL;
  }
}


void CommonState::load_gfx(std::string skin)
{
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("gfx.xml",&zip, false);

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

  common_resources -> player1.draw();
}


void CommonState::update()
{

}


void CommonState::events()
{
  if(key_fullscreen -> get())
  {
    common_resources -> engine -> toggle_screen();
  }
}


