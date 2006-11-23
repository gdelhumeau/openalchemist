/* OpenAlchemist - just a simple game 
 * ----------------------------------
 *
 * Copyright (C) 2006 Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "headers.h"

#define PAUSE_ITEM_RESUME 0
#define PAUSE_ITEM_UNDO 1
#define PAUSE_ITEM_RETRY 2
#define PAUSE_ITEM_CHANGESKIN 3
#define PAUSE_ITEM_FULLSCREEN 4
#define PAUSE_ITEM_SOUND 5
#define PAUSE_ITEM_MUSIC 6
#define PAUSE_ITEM_BACKMAIN 7
#define PAUSE_ITEM_QUIT 8


void Pause::load_gfx(CL_ResourceManager *gfx_pause)
{
  // First, the sprites
  background = new CL_Sprite("menu/pause/background", gfx_pause); 

  items[PAUSE_ITEM_RESUME] = new CL_Sprite("menu/pause/resume/unselected", gfx_pause);
  items_selected[PAUSE_ITEM_RESUME] = new CL_Sprite("menu/pause/resume/selected", gfx_pause);

  items[PAUSE_ITEM_UNDO] = new CL_Sprite("menu/pause/undo/unselected", gfx_pause);
  items_selected[PAUSE_ITEM_UNDO] = new CL_Sprite("menu/pause/undo/selected", gfx_pause);
  undo_unavailable = new CL_Sprite("menu/pause/undo/unavailable", gfx_pause);

  items[PAUSE_ITEM_RETRY] = new CL_Sprite("menu/pause/retry/unselected", gfx_pause);
  items_selected[PAUSE_ITEM_RETRY] = new CL_Sprite("menu/pause/retry/selected", gfx_pause);

  items[PAUSE_ITEM_CHANGESKIN] = new CL_Sprite("menu/pause/changeskin/unselected", gfx_pause);
  items_selected[PAUSE_ITEM_CHANGESKIN] = new CL_Sprite("menu/pause/changeskin/selected", gfx_pause);

  items[PAUSE_ITEM_FULLSCREEN] = new CL_Sprite("menu/pause/fullscreen/unselected", gfx_pause);
  items_selected[PAUSE_ITEM_FULLSCREEN] = new CL_Sprite("menu/pause/fullscreen/selected", gfx_pause);

  items[PAUSE_ITEM_SOUND] = new CL_Sprite("menu/pause/sound/unselected", gfx_pause);
  items_selected[PAUSE_ITEM_SOUND] = new CL_Sprite("menu/pause/sound/selected", gfx_pause);

  items[PAUSE_ITEM_MUSIC] = new CL_Sprite("menu/pause/music/unselected", gfx_pause);
  items_selected[PAUSE_ITEM_MUSIC] = new CL_Sprite("menu/pause/music/selected", gfx_pause);

  items[PAUSE_ITEM_BACKMAIN] = new CL_Sprite("menu/pause/backmain/unselected", gfx_pause);
  items_selected[PAUSE_ITEM_BACKMAIN] = new CL_Sprite("menu/pause/backmain/selected", gfx_pause);

  items[PAUSE_ITEM_QUIT] = new CL_Sprite("menu/pause/quit/unselected", gfx_pause);
  items_selected[PAUSE_ITEM_QUIT] = new CL_Sprite("menu/pause/quit/selected", gfx_pause);

  for(int i=0; i<=10; ++i)
  {
    sound_level[i] = new CL_Sprite("menu/pause/sound-level/"+to_string(i), gfx_pause);
  }


  // Then, propreties
  items_left[PAUSE_ITEM_RESUME] = CL_Integer_to_int("menu/pause/resume/left", gfx_pause);
  items_top[PAUSE_ITEM_RESUME] = CL_Integer_to_int("menu/pause/resume/top", gfx_pause);

  items_left[PAUSE_ITEM_UNDO] = CL_Integer_to_int("menu/pause/undo/left", gfx_pause);
  items_top[PAUSE_ITEM_UNDO] = CL_Integer_to_int("menu/pause/undo/top", gfx_pause);

  items_left[PAUSE_ITEM_RETRY] = CL_Integer_to_int("menu/pause/retry/left", gfx_pause);
  items_top[PAUSE_ITEM_RETRY] = CL_Integer_to_int("menu/pause/retry/top", gfx_pause);

  items_left[PAUSE_ITEM_CHANGESKIN] = CL_Integer_to_int("menu/pause/changeskin/left", gfx_pause);
  items_top[PAUSE_ITEM_CHANGESKIN] = CL_Integer_to_int("menu/pause/changeskin/top", gfx_pause);

  items_left[PAUSE_ITEM_FULLSCREEN] = CL_Integer_to_int("menu/pause/fullscreen/left", gfx_pause);
  items_top[PAUSE_ITEM_FULLSCREEN] = CL_Integer_to_int("menu/pause/fullscreen/top", gfx_pause);

  items_left[PAUSE_ITEM_SOUND] = CL_Integer_to_int("menu/pause/sound/left", gfx_pause);
  items_top[PAUSE_ITEM_SOUND] = CL_Integer_to_int("menu/pause/sound/top", gfx_pause);

  items_left[PAUSE_ITEM_MUSIC] = CL_Integer_to_int("menu/pause/music/left", gfx_pause);
  items_top[PAUSE_ITEM_MUSIC] = CL_Integer_to_int("menu/pause/music/top", gfx_pause);
  
  items_left[PAUSE_ITEM_BACKMAIN] = CL_Integer_to_int("menu/pause/backmain/left", gfx_pause);
  items_top[PAUSE_ITEM_BACKMAIN] = CL_Integer_to_int("menu/pause/backmain/top", gfx_pause);

  items_left[PAUSE_ITEM_QUIT] = CL_Integer_to_int("menu/pause/quit/left", gfx_pause);
  items_top[PAUSE_ITEM_QUIT] = CL_Integer_to_int("menu/pause/quit/top", gfx_pause);

  sound_level_left = CL_Integer_to_int("menu/pause/sound-level/left", gfx_pause);

  if(CL_Boolean_to_bool("menu/pause/alpha_appearing", gfx_pause))
  {
    appearing = true;
    max_alpha =(float)CL_Integer_to_int("menu/pause/alpha_max", gfx_pause) / 100.0;
  }
  else
    appearing = false;

}


void Pause::unload_gfx()
{
  delete background;

  delete undo_unavailable;
  for(int i=0; i<PAUSE_NUMBER_OF_ITEMS; ++i)
  {
    delete items[i];
    delete items_selected[i];
  }

  for(int i=0; i<=10; i++)
  {
    delete sound_level[i];
  }

}


void Game::draw_pause()
{
  if(PAUSE_STEP_APPEARING == pause.step)
  {
    if(pause.alpha+0.003*time_interval >= pause.max_alpha)
    {
      pause.step = PAUSE_STEP_MENU;
      pause.alpha = 1.0;
    }
    pause.alpha += 0.003*time_interval;

    int x = 400 - pause.background -> get_width()/2;
    int y = 300 - pause.background -> get_height()/2;
    pause.background -> set_alpha(pause.alpha);
    pause.background -> draw(x,y);

    for(int i=0; i<PAUSE_NUMBER_OF_ITEMS; ++i)
    {
      pause.items[i] -> set_alpha(pause.alpha);
      pause.items_selected[i] -> set_alpha(pause.alpha);
    }

    pause.undo_unavailable -> set_alpha(pause.alpha);
  
    pause.sound_level[sound_level] -> set_alpha(pause.alpha);
    pause.sound_level[music_level] -> set_alpha(pause.alpha);


  }
  else if(PAUSE_STEP_DISAPPEARING == pause.step)
  {
    pause.alpha -= 0.007*time_interval;
    if(pause.alpha <= 0.0)
      pause.is_paused = false;

    int x = 400 - pause.background -> get_width()/2;
    int y = 300 - pause.background -> get_height()/2;
    pause.background -> set_alpha(pause.alpha);
    pause.background -> draw(x,y);    

    for(int i=0; i<PAUSE_NUMBER_OF_ITEMS; ++i)
    {
      pause.items[i] -> set_alpha(pause.alpha);
      pause.items_selected[i] -> set_alpha(pause.alpha);
    }
   
    pause.undo_unavailable -> set_alpha(pause.alpha);
   
    pause.sound_level[sound_level] -> set_alpha(pause.alpha);
    pause.sound_level[music_level] -> set_alpha(pause.alpha);
    
    
  }

  if(PAUSE_STEP_SKINS == pause.step)
  {
    int x = 400 - pause.background -> get_width()/2;
    int y = 300 - pause.background -> get_height()/2;
    pause.background -> draw(x,y);
    pause.background -> update();
    draw_skins_selector();
  }
  else
  {
    int x = 400 - pause.background -> get_width()/2;
    int y = 300 - pause.background -> get_height()/2;
    pause.background -> draw(x,y);
    pause.background -> update();


    // Drawing 
    for(int i=0; i<PAUSE_NUMBER_OF_ITEMS; ++i)
    {

      if(i == pause.selection)
      {
        pause.items_selected[i] -> draw(x + pause.items_left[i], y + pause.items_top[i]);
        pause.items_selected[i] -> update();
     
      }
      else
      {
        if(i != PAUSE_ITEM_UNDO || undo.possible)
        {
          pause.items[i] -> draw(x + pause.items_left[i], y + pause.items_top[i]);
          pause.items[i] -> update();
        }
        else
        {
          pause.undo_unavailable -> draw(x + pause.items_left[i], y + pause.items_top[i]);
          pause.undo_unavailable -> update();
        }
      }
    }
    


    pause.sound_level[sound_level] -> draw(x + pause.sound_level_left, y 
                                           + pause.items_top[PAUSE_ITEM_SOUND]);
    pause.sound_level[music_level] -> draw(x + pause.sound_level_left, y 
                                           + pause.items_top[PAUSE_ITEM_MUSIC]);
    pause.sound_level[sound_level] -> update();
    pause.sound_level[music_level] -> update();

  }
}

void Game::key_events_pause()
{
  if(pause.step == PAUSE_STEP_APPEARING)
    return;

  if(pause.step == PAUSE_STEP_SKINS)
  {
    key_events_skins_selector();
    return;
  }

   
  if(key.echap->get())
  {   
    if(pause.appearing && opengl)
      pause.step = PAUSE_STEP_DISAPPEARING;
    else
      pause.is_paused = false;
    
  }

  if(key.up -> get())
  {
    if(pause.selection == 0)
      pause.selection = PAUSE_ITEM_QUIT;
    else
    {
      pause.selection --;
      if(pause.selection == PAUSE_ITEM_UNDO && !undo.possible)
      {
        pause.selection --;
      }
    }
  }

  if(pause.selection == PAUSE_ITEM_SOUND && key.left -> get())
  {
    if(sound_level > 0)
      sound_level--;
  }

  if(pause.selection == PAUSE_ITEM_SOUND && key.right -> get())
  {
    if(sound_level < 10)
      sound_level++;
  }

  if(pause.selection == PAUSE_ITEM_MUSIC && key.left -> get())
  {
    if(music_level > 0)
      music_level--;
  }

  if(pause.selection == PAUSE_ITEM_MUSIC && key.right -> get())
  {
    if(music_level < 10)
      music_level++;
  }

  if(key.down -> get())
  {
    if(pause.selection == PAUSE_ITEM_QUIT)
      pause.selection = 0;
    else
    {
      pause.selection ++;
      if(pause.selection == PAUSE_ITEM_UNDO && !undo.possible)
      {
        pause.selection ++;
      }
    }
  }

  if(key.enter -> get())
  {
    switch(pause.selection)
    {
    case PAUSE_ITEM_RESUME:
      if(pause.appearing && opengl)
        pause.step = PAUSE_STEP_DISAPPEARING;
      else
        pause.is_paused = false;
      break;
    case PAUSE_ITEM_UNDO:
      undo_last();
      if(pause.appearing && opengl)
        pause.step = PAUSE_STEP_DISAPPEARING;
      else
        pause.is_paused = false;
      pause.is_paused = false;
      break;
    case PAUSE_ITEM_RETRY:
      new_game(0);
      break;
    case PAUSE_ITEM_CHANGESKIN:
      choose_skin();
      break;
    case PAUSE_ITEM_FULLSCREEN:
      toggle_screen();
      break;
    case PAUSE_ITEM_BACKMAIN:
      break;
    case PAUSE_ITEM_QUIT:
      end = true;
      pause.is_paused = false;
    }
  }



}
