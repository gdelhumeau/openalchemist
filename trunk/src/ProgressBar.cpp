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
}

ProgressBar::~ProgressBar()
{
  unload_gfx();
}

void ProgressBar::load_gfx(CL_GraphicContext & gc, std::string skin)
{
	unload_gfx();
	
  // Getting skins resources
  CL_VirtualFileSystem vfs(skin, true);
  CL_VirtualDirectory vd(vfs, "./");
  CL_ResourceManager gfx("progress_bar.xml", vd);


  _p_head     = CL_Sprite(gc, "progress_bar/head/sprite",    &gfx);
  _p_head_ok  = CL_Sprite(gc, "progress_bar/head/sprite_ok", &gfx);
  _p_foot     = CL_Sprite(gc, "progress_bar/foot/sprite",    &gfx);
  _p_item     = CL_Sprite(gc, "progress_bar/item/sprite",    &gfx);
  _p_item_ok  = CL_Sprite(gc, "progress_bar/item/sprite_ok", &gfx);

  _left     = CL_Integer_to_int("progress_bar/left",       &gfx);
  _head_top = CL_Integer_to_int("progress_bar/head/top",   &gfx);
  _foot_top = CL_Integer_to_int("progress_bar/foot/top",   &gfx);

}

void ProgressBar::unload_gfx()
{
 
}

void ProgressBar::draw(CL_GraphicContext & gc, int percentage)
{
  int head_height = _p_head.get_height();
  int height = _foot_top - (_head_top + head_height);

  /*if(hightscores[current_difficulty] > 0)
    v = height * (global_score + global_bonus) / hightscores[current_difficulty];*/
  
  int v = height * percentage / 100;
  if(v > height) v = height;

  for(int i=0; i<=height; ++i)
  {
    if(height - i < v)
      _p_item_ok.draw(gc, _left, _head_top+head_height+i-1);
    else
      _p_item.draw(gc, _left, _head_top+head_height+i-1);
  }
  _p_item.update();
  _p_item_ok.update();

  if(percentage < 100)
  {
    _p_head.draw(gc, _left, _head_top);
    _p_head.update();
  }
  else
  {
    _p_head_ok.draw(gc, _left, _head_top);
    _p_head_ok.update();
  }
  _p_foot.draw(gc, _left, _foot_top);
  _p_foot.update();
}
