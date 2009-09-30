/********************************************************************
                          OpenAlchemist

  File : Player.cpp
  Description : Player implementation
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <ClanLib/core.h>
#include "CombosPainter.h"
#include "CommonResources.h"
#include "misc.h"
#include "memory.h"

#define COMBOS_SPEED 1

enum{
	MODE_APPEARING,
	MODE_DISPLAY,
	MODE_DISAPPEARING	
};

CombosPainter :: CombosPainter()
{
  _next_time = 0;
  _is_enabled = false;
  _mode = MODE_APPEARING;
}

CombosPainter :: ~CombosPainter()
{
  unload_gfx();
}

void CombosPainter :: load_gfx(CL_GraphicContext &gc, std::string skin)
{

	unload_gfx();

  // Getting skins resources
  CL_VirtualFileSystem vfs(skin, true);
  CL_VirtualDirectory vd(vfs, "./");
  CL_ResourceManager gfx_combos("combos.xml", vd);

  _sprite_single = CL_Sprite(gc, "combos/text/sprite_single", &gfx_combos);
  _sprite_plural = CL_Sprite(gc, "combos/text/sprite_plural", &gfx_combos);
  _font = CL_Font_Sprite(gc, "combos/font", &gfx_combos);

  _sprite_x =  CL_Integer_to_int("combos/text/left", &gfx_combos);
  _sprite_y =  CL_Integer_to_int("combos/text/top", &gfx_combos);

  _score_x =  CL_Integer_to_int("combos/score/left", &gfx_combos);
  _score_y =  CL_Integer_to_int("combos/score/top", &gfx_combos);  

	_font_height = _font.get_font_metrics(gc).get_height();

}


void CombosPainter :: unload_gfx()
{
 
}

void CombosPainter :: set_score(int score)
{
  this -> _score = score;

  if(!_is_enabled)
  {
    _score_current_y  = - _font_height;
    _sprite_current_x = 800;
    _mode = MODE_APPEARING;
  }
  else
  {
    _next_time = CL_System::get_time() + 1500;
  }

  _is_enabled = true;

}

void CombosPainter :: draw(CL_GraphicContext &gc)
{
  if(!_is_enabled)
    return;

  _font.draw_text(gc, _score_x, _score_current_y, to_string(_score));
  if(_score == 1)
    _sprite_single.draw(gc, _sprite_current_x, _sprite_y);
  else
    _sprite_plural.draw(gc, _sprite_current_x, _sprite_y);

  
}

void CombosPainter :: update()
{
  if(_is_enabled)
  {
    switch(_mode)
    {
    case MODE_APPEARING:
      _update_appearing();
      break;  
    case MODE_DISPLAY:
      _update_display();
      break;
    case MODE_DISAPPEARING:
      _update_disappearing();
      break;
    }
  }
}

  
void CombosPainter :: _update_appearing()
{
  // Getting resources
  CommonResources *resources = common_resources_get_instance();

  if(_sprite_current_x > _sprite_x)
  {
    _sprite_current_x -= COMBOS_SPEED * resources -> time_interval;
    if(_sprite_current_x < _sprite_x)
      _sprite_current_x = _sprite_x;
  }
 
  if(_score_current_y < _score_y)
  {
    _score_current_y += COMBOS_SPEED * resources -> time_interval;
    if(_score_current_y > _score_y)
      _score_current_y = _score_y;
  }

  if(_score_current_y >= _score_y && _sprite_current_x <= _sprite_x)
  {
    _mode = MODE_DISPLAY;
    _next_time = CL_System::get_time() + 1500;
  }
}


void CombosPainter :: _update_display()
{
  if(CL_System::get_time() > _next_time)
  {
    _mode = MODE_DISAPPEARING;
  }
}

void CombosPainter :: _update_disappearing()
{
  // Getting resources
  CommonResources *resources = common_resources_get_instance();

  if(_sprite_current_x < 800)
  {
    _sprite_current_x += COMBOS_SPEED * resources -> time_interval;
  }
 
  if(_score_current_y > -_font_height)
  {
    _score_current_y -= COMBOS_SPEED * resources -> time_interval;
  }

  if(_score_current_y < - _font_height && _sprite_current_x > 800)
  {
    _is_enabled = false;
  }
}
