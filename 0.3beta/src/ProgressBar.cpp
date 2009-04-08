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
  /*CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("progress_bar.xml", &zip, false);*/


  head     = IMG_Load_fromSkin(skin, "misc/bar-head.png"    );
  head_ok  = IMG_Load_fromSkin(skin, "misc/bar-head-ok.png" );
  foot     = IMG_Load_fromSkin(skin, "misc/bar-foot.png"    );
  item     = IMG_Load_fromSkin(skin, "misc/bar-item.png"    );
  item_ok  = IMG_Load_fromSkin(skin, "misc/bar-item-ok.png" );

  left     = 395; //CL_Integer_to_int("progress_bar/left",       &gfx);
  head_top = 135; //CL_Integer_to_int("progress_bar/head/top",   &gfx);
  foot_top = 245; //CL_Integer_to_int("progress_bar/foot/top",   &gfx);

}

void ProgressBar::unload_gfx()
{
  if(head)
  {
    SDL_FreeSurface(head);
    head = NULL;
  }

  if(head_ok)
  {
    SDL_FreeSurface (head_ok);
    head_ok = NULL;
  }

  if(foot)
  {
    SDL_FreeSurface (foot);
    foot = NULL;
  }

  if(item)
  {
    SDL_FreeSurface (item);
    item = NULL;
  }

  if(item_ok)
  {
    SDL_FreeSurface (item_ok);
    item_ok = NULL;
  }
}

void ProgressBar::draw(int percentage)
{
  int head_height = head->h;// -> get_height();
  int height = foot_top - (head_top + head_height);

  /*if(hightscores[current_difficulty] > 0)
    v = height * (global_score + global_bonus) / hightscores[current_difficulty];*/
  
  int v = height * percentage / 100;
  if(v > height) v = height;

  for(int i=0; i<=height; ++i)
  {
    if(height - i < v)
      //item_ok -> draw(left, head_top+head_height+i-1);
      psp_sdl_blit_on_screen_at_XY(item_ok, left, head_top+head_height+i-1);
    else
      //item -> draw(left, head_top+head_height+i-1);
      psp_sdl_blit_on_screen_at_XY(item, left, head_top+head_height+i-1);
  }

  if(percentage < 100)
  {
    //head -> draw(left, head_top);
    psp_sdl_blit_on_screen_at_XY(head, left, head_top);
    //head -> update();
//    psp_sdl_flip();
  }
  else
  {
    //head_ok -> draw(left, head_top);
    psp_sdl_blit_on_screen_at_XY(head_ok, left, head_top);
    //head_ok -> update();
//    psp_sdl_flip();
  }
  //foot -> draw(left, foot_top);
  psp_sdl_blit_on_screen_at_XY(foot, left, foot_top);
  //foot -> update();
//  psp_sdl_flip();
}
