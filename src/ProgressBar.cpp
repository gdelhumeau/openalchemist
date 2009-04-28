/********************************************************************
                          OpenAlchemist

  File : ProgressBar.cpp
  Description : ProgressBar implementation
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include "ProgressBar.h"
#include "misc.h"
#include "memory.h"

ProgressBar::ProgressBar()
{
  _p_head    = NULL;
  _p_head_ok = NULL;
  _p_foot    = NULL;
  _p_item    = NULL;
  _p_item_ok = NULL;
}

ProgressBar::~ProgressBar()
{
  unload_gfx();
}

void ProgressBar::load_gfx(std::string skin)
{
	unload_gfx();
	
  // Getting skins resources
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("progress_bar.xml", &zip, false);


  _p_head     = my_new CL_Sprite("progress_bar/head/sprite",    &gfx);
  _p_head_ok  = my_new CL_Sprite("progress_bar/head/sprite_ok", &gfx);
  _p_foot     = my_new CL_Sprite("progress_bar/foot/sprite",    &gfx);
  _p_item     = my_new CL_Sprite("progress_bar/item/sprite",    &gfx);
  _p_item_ok  = my_new CL_Sprite("progress_bar/item/sprite_ok", &gfx);

  _left     = CL_Integer_to_int("progress_bar/left",       &gfx);
  _head_top = CL_Integer_to_int("progress_bar/head/top",   &gfx);
  _foot_top = CL_Integer_to_int("progress_bar/foot/top",   &gfx);

}

void ProgressBar::unload_gfx()
{
  if(_p_head)
  {
    my_delete(_p_head);
    _p_head = NULL;
  }

  if(_p_head_ok)
  {
    my_delete(_p_head_ok);
    _p_head_ok = NULL;
  }

  if(_p_foot)
  {
    my_delete(_p_foot);
    _p_foot = NULL;
  }

  if(_p_item)
  {
    my_delete(_p_item);
    _p_item = NULL;
  }

  if(_p_item_ok)
  {
    my_delete(_p_item_ok);
    _p_item_ok = NULL;
  }
}

void ProgressBar::draw(int percentage)
{
  int head_height = _p_head -> get_height();
  int height = _foot_top - (_head_top + head_height);

  /*if(hightscores[current_difficulty] > 0)
    v = height * (global_score + global_bonus) / hightscores[current_difficulty];*/
  
  int v = height * percentage / 100;
  if(v > height) v = height;

  for(int i=0; i<=height; ++i)
  {
    if(height - i < v)
      _p_item_ok -> draw(_left, _head_top+head_height+i-1);
    else
      _p_item -> draw(_left, _head_top+head_height+i-1);
  }
  _p_item -> update();
  _p_item_ok -> update();

  if(percentage < 100)
  {
    _p_head -> draw(_left, _head_top);
    _p_head -> update();
  }
  else
  {
    _p_head_ok -> draw(_left, _head_top);
    _p_head_ok -> update();
  }
  _p_foot -> draw(_left, _foot_top);
  _p_foot -> update();
}
