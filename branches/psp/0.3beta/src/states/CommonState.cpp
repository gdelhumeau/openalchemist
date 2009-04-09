/********************************************************************
                          OpenAlchemist

  File : CommonState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

//#include <ClanLib/core.h>
//#include <ClanLib/display.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "CommonState.h"
#include "../GameEngine.h"
#include "../CommonResources.h"
#include "../KeyboardKey.h"
#include "../misc.h"
#include "../psp_sdl.h"

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
  background = NULL;
}


void CommonState::deinit()
{
}


void CommonState::load_gfx(std::string skin)
{
//TODO : zlib usage + resources management
  //CL_Zip_Archive zip(skin);
  //CL_ResourceManager gfx("general.xml",&zip, false);
  //new CL_Surface("background", &gfx);
  unload_gfx();
  background = IMG_Load_fromSkin(skin, "misc/landscape.png");
}


void CommonState::unload_gfx()
{
  if(background)
  {
    //delete background;
    SDL_FreeSurface(background);
    background = NULL;
  }

}


void CommonState::draw()
{
  //background -> draw(0, 0);
  psp_sdl_blit_on_screen(background);
  //TODO: font stuffs
  //common_resources -> main_font -> draw(580,550,to_string(common_resources -> engine -> get_fps()));

  if(common_resources -> current_player)
    common_resources -> current_player -> draw();
}


void CommonState::update()
{

}


void CommonState::events()
{
  switch(common_resources->CurrentKeyPressed)
{
case (KEY_FULLSCREEN):
  {
    common_resources -> engine -> toggle_screen();
    common_resources->CurrentKeyPressed = 0;
    break;
  }
}
}

bool CommonState::front_layer_behind()
{
  return false;
}


void CommonState::print()
{
  printf("CommonState\n");
}