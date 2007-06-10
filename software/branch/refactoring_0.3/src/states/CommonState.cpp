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
#include "../KeyboardKey.h"
#include "../misc.h"

CommonState::CommonState(GameEngine* engine)
{
  this -> engine = engine;
  background = NULL;
  main_font = NULL;
  key_fullscreen = NULL;
}


CommonState::~CommonState()
{
  unload_gfx();
  deinit();
}

void CommonState::init()
{
  key_fullscreen  = new KeyboardKey(CL_KEY_F11, false);
}


void CommonState::deinit()
{
  if(key_fullscreen)
    delete key_fullscreen;
}


void CommonState::load_gfx(std::string skin)
{
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("gfx.xml",&zip, false);

  background = new CL_Surface("background", &gfx);
  main_font = new CL_Font("font", &gfx);
}


void CommonState::unload_gfx()
{
  if(background)
    delete background;
  if(main_font)
    delete main_font;
}


void CommonState::draw()
{
  background -> draw(0, 0);
  main_font -> draw(580,550,to_string(engine -> get_fps()));
}


void CommonState::update()
{

}


void CommonState::events()
{
  if(key_fullscreen -> get())
  {
    engine -> toggle_screen();
  }
}


