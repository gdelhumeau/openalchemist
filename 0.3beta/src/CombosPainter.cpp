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

#define COMBOS_SPEED 0.5

#define MODE_APPEARING 1
#define MODE_DISPLAY 2
#define MODE_DISAPPEARING 3

CombosPainter :: CombosPainter()
{
  _sprite_single = NULL;
  _sprite_plural = NULL;
  _font          = NULL;

  _next_time = 0;
  _enabled = false;
  _mode = MODE_APPEARING;
}

CombosPainter :: ~CombosPainter()
{
  unload_gfx();
}

void CombosPainter :: load_gfx(std::string skin)
{

  // Getting resources
  //CommonResources *resources = common_resources_get_instance();
  unload_gfx();
  // Getting skins resources
 // TODO: Resources management stuff for combo painting 
 //       regarding the chosen skin
/*
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx_combos("combos.xml", &zip, false);*/

  _sprite_single = IMG_Load_fromSkin(skin, "misc/combos-text-single.png");
  _sprite_plural = IMG_Load_fromSkin(skin, "misc/combos-text-plural.png");

  _font =  new BitmapFont(skin, COMBO_FONT);
 // printf("New bitmap font created\n");

  _sprite_x =  PSP_SDL_SCREEN_WIDTH/2 ;//CL_Integer_to_int("combos/text/left", &gfx_combos);
  _sprite_y =  PSP_SDL_SCREEN_HEIGHT/4; //CL_Integer_to_int("combos/text/top", &gfx_combos);

  _score_x = PSP_SDL_SCREEN_WIDTH/2 ; //CL_Integer_to_int("combos/score/left", &gfx_combos);
  _score_y = PSP_SDL_SCREEN_HEIGHT/2 - _font -> GetCharHeight(); //CL_Integer_to_int("combos/score/top", &gfx_combos);  
 // printf("other attributes of combo painter OK, end of load_gfx()\n");
}


void CombosPainter :: unload_gfx()
{
  if(_sprite_single)
  {
    SDL_FreeSurface(_sprite_single);
    _sprite_single = NULL;
  }
  if(_sprite_plural)
  {
    SDL_FreeSurface (_sprite_plural);
    _sprite_plural = NULL;
  }
  if(_font)
  {
    _font->unload_gfx();
    delete _font;
    _font = NULL;
  }
}

void CombosPainter :: set_score(int score)
{
  this -> _score = score;

  if(!_enabled)
  {
    _score_current_y  = - _font -> GetCharHeight();
    _sprite_current_x = PSP_SDL_SCREEN_WIDTH;
    _mode = MODE_APPEARING;
  }
  else
  {
    _next_time = SDL_GetTicks() + 1500;
  }

  _enabled = true;
//printf("CombosPainter : End of set_score, score is %d\n", _score);
}

void CombosPainter :: draw()
{
  if(!_enabled)
    return;

  _font -> draw((int)_score_x, (int)_score_current_y, to_string(_score));
  if(_score == 1)
    psp_sdl_blit_on_screen_at_XY(_sprite_single, (int)_sprite_current_x, (int)_sprite_y);
	//sprite_single -> draw(sprite_current_x, sprite_y);
  else
    psp_sdl_blit_on_screen_at_XY(_sprite_plural, (int)_sprite_current_x, (int)_sprite_y);
    
    //sprite_plural -> draw(sprite_current_x, sprite_y);
//printf("CombosPainter:end of draw(), coords : %d, %d\n",(int)_score_x, (int)_score_current_y);
  
}

void CombosPainter :: update()
{
  if(_enabled)
  {
    switch(_mode)
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
//printf("CombosPainter update done, mode is : %d\n",_mode);
}

  
void CombosPainter :: update_appearing()
{
  // Getting resources
  CommonResources *resources = common_resources_get_instance();
//printf("begin  CombosPainter update_appearing\n");
  if(_sprite_current_x > _sprite_x)
  {
    _sprite_current_x -= (int)(COMBOS_SPEED * resources -> time_interval);
    if(_sprite_current_x < _sprite_x)
      _sprite_current_x = _sprite_x;
  }
 
  if(_score_current_y < _score_y)
  {
    _score_current_y += (int)(COMBOS_SPEED * resources -> time_interval);
    if(_score_current_y > _score_y)
      _score_current_y = _score_y;
  }

  if(_score_current_y >= _score_y && _sprite_current_x <= _sprite_x)
  {
    _mode = MODE_DISPLAY;
    _next_time = SDL_GetTicks() + 1500;
  }

//printf("CombosPainter update_appearing done, coords are : %d, %d\n",(int)_sprite_current_x,(int)_score_current_y);
//printf("targets are %d, %d\n",(int)_sprite_x,(int)_score_y);
}


void CombosPainter :: update_display()
{
  if(SDL_GetTicks()  > _next_time)
  {
    _mode = MODE_DISAPPEARING;
  }
//printf("CombosPainter update_display done\n");
}

void CombosPainter :: update_disappearing()
{
  // Getting resources
  CommonResources *resources = common_resources_get_instance();

  if(_sprite_current_x < PSP_SDL_SCREEN_WIDTH)
  {
    _sprite_current_x += (int)(COMBOS_SPEED * resources -> time_interval);
  }
 
  if(_score_current_y > -_font -> GetCharHeight()) 
  {
    _score_current_y -= (int)(COMBOS_SPEED * resources -> time_interval);
  }

  if(_score_current_y < -(_font -> GetCharHeight()) && _sprite_current_x > PSP_SDL_SCREEN_WIDTH)
  {
    _enabled = false;
  }
//printf("CombosPainter update_disappearing done, coords are : %d, %d\n",(int)_sprite_current_x,(int)_score_current_y);
//printf("targets are %d, %d\n",(int)_sprite_x,(int)_score_y);
}
