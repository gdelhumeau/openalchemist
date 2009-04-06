/********************************************************************
                          OpenAlchemist

  File : Player.cpp
  Description : Player implementation
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include "CombosPainter.h"
#include "CommonResources.h"
#include "misc.h"
#include "psp_sdl.h"

//#include <ClanLib/core.h>

#define COMBOS_SPEED 1

#define MODE_APPEARING 1
#define MODE_DISPLAY 2
#define MODE_DISAPPEARING 3

CombosPainter :: CombosPainter()
{
  sprite_single = NULL;
  sprite_plural = NULL;
//  font          = NULL;

  next_time = 0;
  enabled = false;
  mode = MODE_APPEARING;
}

CombosPainter :: ~CombosPainter()
{
  unload_gfx();
}

void CombosPainter :: load_gfx(std::string skin)
{

  // Getting resources
  //CommonResources *resources = common_resources_get_instance();

  // Getting skins resources
 // TODO: Resources management stuff for combo painting 
 //       regarding the chosen skin
/*
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx_combos("combos.xml", &zip, false);

  sprite_single = new CL_Sprite("combos/text/sprite_single", &gfx_combos);
  sprite_plural = new CL_Sprite("combos/text/sprite_plural", &gfx_combos);
  font = new CL_Font("combos/font", &gfx_combos);

  sprite_x =  CL_Integer_to_int("combos/text/left", &gfx_combos);
  sprite_y =  CL_Integer_to_int("combos/text/top", &gfx_combos);

  score_x =  CL_Integer_to_int("combos/score/left", &gfx_combos);
  score_y =  CL_Integer_to_int("combos/score/top", &gfx_combos);  
*/
}


void CombosPainter :: unload_gfx()
{
  /*if(sprite_single)
  {
    delete sprite_single;
    sprite_single = NULL;
  }
  if(sprite_plural)
  {
    delete sprite_plural;
    sprite_plural = NULL;
  }
  if(font)
  {
    delete font;
    font = NULL;
  }*/
}

void CombosPainter :: set_score(int score)
{
  this -> score = score;

  if(!enabled)
  {
	//TODO : font stuffs
    //score_current_y  = - font -> get_height();
    sprite_current_x = 800;
    mode = MODE_APPEARING;
  }
  else
  {
// TODO : Use SDL time
//    next_time = CL_System::get_time() + 1500;
  }

  enabled = true;

}

void CombosPainter :: draw()
{
  if(!enabled)
    return;

//  font -> draw(score_x, score_current_y, to_string(score));
  if(score == 1)
    //TODO: SDL Blit thing
    psp_sdl_blit_on_screen(sprite_single);
	//sprite_single -> draw(sprite_current_x, sprite_y);
  else
    //TODO: SDL Blit thing
    psp_sdl_blit_on_screen(sprite_plural);
    
    //sprite_plural -> draw(sprite_current_x, sprite_y);

  
}

void CombosPainter :: update()
{
  if(enabled)
  {
    switch(mode)
    {
    case MODE_APPEARING:
      update_appearing();
      break;  
    case MODE_DISPLAY:
      update_display();
      break;
    case MODE_DISAPPEARING:
      update_disappearing();
      break;
    }
  }
}

  
void CombosPainter :: update_appearing()
{
  // Getting resources
  CommonResources *resources = common_resources_get_instance();

  if(sprite_current_x > sprite_x)
  {
    sprite_current_x -= COMBOS_SPEED * resources -> time_interval;
    if(sprite_current_x < sprite_x)
      sprite_current_x = sprite_x;
  }
 
  if(score_current_y < score_y)
  {
    score_current_y += COMBOS_SPEED * resources -> time_interval;
    if(score_current_y > score_y)
      score_current_y = score_y;
  }

  if(score_current_y >= score_y && sprite_current_x <= sprite_x)
  {
    mode = MODE_DISPLAY;
    //TODO:SDL time stuffs
	//next_time = CL_System::get_time() + 1500;
  }
}


void CombosPainter :: update_display()
{
//TODO: SDL time stuffs
/*  if(CL_System::get_time() > next_time)
  {
    mode = MODE_DISAPPEARING;
  }
*/
}

void CombosPainter :: update_disappearing()
{
  // Getting resources
  CommonResources *resources = common_resources_get_instance();

  if(sprite_current_x < 800)
  {
    sprite_current_x += COMBOS_SPEED * resources -> time_interval;
  }
 
 /* if(score_current_y > -font -> get_height())
  {
    score_current_y -= COMBOS_SPEED * resources -> time_interval;
  }

  if(score_current_y < - font -> get_height() && sprite_current_x > 800)
  {
    enabled = false;
  }*/
}
