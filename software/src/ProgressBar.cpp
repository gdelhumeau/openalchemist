/********************************************************************
                          OpenAlchemist

  File : ProgressBar.cpp
  Description : ProgressBar implementation
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include "ProgressBar.h"
#include "misc.h"

ProgressBar::ProgressBar()
{
  head    = NULL;
  head_ok = NULL;
  foot    = NULL;
  item    = NULL;
  item_ok = NULL;
}

ProgressBar::~ProgressBar()
{
  unload_gfx();
}

void ProgressBar::load_gfx(std::string skin)
{
  // Getting skins resources
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("gfx.xml", &zip, false);


  head     = new CL_Sprite("progress_bar/head/sprite",    &gfx);
  head_ok  = new CL_Sprite("progress_bar/head/sprite_ok", &gfx);
  foot     = new CL_Sprite("progress_bar/foot/sprite",    &gfx);
  item     = new CL_Sprite("progress_bar/item/sprite",    &gfx);
  item_ok  = new CL_Sprite("progress_bar/item/sprite_ok", &gfx);

  left     = CL_Integer_to_int("progress_bar/left",       &gfx);
  head_top = CL_Integer_to_int("progress_bar/head/top",   &gfx);
  foot_top = CL_Integer_to_int("progress_bar/foot/top",   &gfx);

}

void ProgressBar::unload_gfx()
{
  if(head)
  {
    delete head;
    head = NULL;
  }

  if(head_ok)
  {
    delete head_ok;
    head_ok = NULL;
  }

  if(foot)
  {
    delete foot;
    foot = NULL;
  }

  if(item)
  {
    delete item;
    item = NULL;
  }

  if(item_ok)
  {
    delete item_ok;
    item_ok = NULL;
  }
}

void ProgressBar::draw(int percentage)
{
  int head_height = head -> get_height();
  int height = foot_top - (head_top + head_height);

  /*if(hightscores[current_difficulty] > 0)
    v = height * (global_score + global_bonus) / hightscores[current_difficulty];*/
  
  int v = height * percentage / 100;
  if(v > height) v = height;

  for(int i=0; i<=height; ++i)
  {
    if(height - i < v)
      item_ok -> draw(left, head_top+head_height+i-1);
    else
      item -> draw(left, head_top+head_height+i-1);
  }
  item -> update();
  item_ok -> update();

  if(percentage < 100)
  {
    head -> draw(left, head_top);
    head -> update();
  }
  else
  {
    head_ok -> draw(left, head_top);
    head_ok -> update();
  }
  foot -> draw(left, foot_top);
  foot -> update();
}
