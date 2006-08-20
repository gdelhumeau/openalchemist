/* OpenAlchemist - just a simple game 
 * ----------------------------------
 *
 * Copyright (C) 2006 Guillaume Delhumeau <guillaume.delhumeau at laposte.net>
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

  resume = new CL_Sprite("menu/pause/resume/unselected", gfx_pause);
  resume_selected = new CL_Sprite("menu/pause/resume/selected", gfx_pause);

  undo = new CL_Sprite("menu/pause/undo/unselected", gfx_pause);
  undo_selected = new CL_Sprite("menu/pause/undo/selected", gfx_pause);
  undo_unavailable = new CL_Sprite("menu/pause/undo/unavailable", gfx_pause);

  retry = new CL_Sprite("menu/pause/retry/unselected", gfx_pause);
  retry_selected = new CL_Sprite("menu/pause/retry/selected", gfx_pause);

  changeskin = new CL_Sprite("menu/pause/changeskin/unselected", gfx_pause);
  changeskin_selected = new CL_Sprite("menu/pause/changeskin/selected", gfx_pause);

  fullscreen = new CL_Sprite("menu/pause/fullscreen/unselected", gfx_pause);
  fullscreen_selected = new CL_Sprite("menu/pause/fullscreen/selected", gfx_pause);

  sound = new CL_Sprite("menu/pause/sound/unselected", gfx_pause);
  sound_selected = new CL_Sprite("menu/pause/sound/selected", gfx_pause);

  music = new CL_Sprite("menu/pause/music/unselected", gfx_pause);
  music_selected = new CL_Sprite("menu/pause/music/selected", gfx_pause);

  backmain = new CL_Sprite("menu/pause/backmain/unselected", gfx_pause);
  backmain_selected = new CL_Sprite("menu/pause/backmain/selected", gfx_pause);

  quit = new CL_Sprite("menu/pause/quit/unselected", gfx_pause);
  quit_selected = new CL_Sprite("menu/pause/quit/selected", gfx_pause);

  for(int i=0; i<=10; i++)
  {
    sound_level[i] = new CL_Sprite("menu/pause/sound-level/"+to_string(i), gfx_pause);
  }


  // Then, propreties
  resume_left = CL_Integer_to_int("menu/pause/resume/left", gfx_pause);
  resume_top = CL_Integer_to_int("menu/pause/resume/top", gfx_pause);

  undo_left = CL_Integer_to_int("menu/pause/undo/left", gfx_pause);
  undo_top = CL_Integer_to_int("menu/pause/undo/top", gfx_pause);

  retry_left = CL_Integer_to_int("menu/pause/retry/left", gfx_pause);
  retry_top = CL_Integer_to_int("menu/pause/retry/top", gfx_pause);

  changeskin_left = CL_Integer_to_int("menu/pause/changeskin/left", gfx_pause);
  changeskin_top = CL_Integer_to_int("menu/pause/changeskin/top", gfx_pause);

  fullscreen_left = CL_Integer_to_int("menu/pause/fullscreen/left", gfx_pause);
  fullscreen_top = CL_Integer_to_int("menu/pause/fullscreen/top", gfx_pause);

  sound_left = CL_Integer_to_int("menu/pause/sound/left", gfx_pause);
  sound_top = CL_Integer_to_int("menu/pause/sound/top", gfx_pause);

  music_left = CL_Integer_to_int("menu/pause/music/left", gfx_pause);
  music_top = CL_Integer_to_int("menu/pause/music/top", gfx_pause);
  
  backmain_left = CL_Integer_to_int("menu/pause/backmain/left", gfx_pause);
  backmain_top = CL_Integer_to_int("menu/pause/backmain/top", gfx_pause);

  quit_left = CL_Integer_to_int("menu/pause/quit/left", gfx_pause);
  quit_top = CL_Integer_to_int("menu/pause/quit/top", gfx_pause);

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

  delete resume;
  delete resume_selected;

  delete undo;
  delete undo_selected;
  delete undo_unavailable;

  delete retry;
  delete retry_selected;

  delete changeskin;
  delete changeskin_selected;

  delete fullscreen;
  delete fullscreen_selected;

  delete sound;
  delete sound_selected;

  delete music;
  delete music_selected;

  delete backmain;
  delete backmain_selected;

  delete quit;
  delete quit_selected;

  for(int i=0; i<=10; i++)
  {
    delete sound_level[i];
  }

}


void Game::draw_pause()
{
  if(PAUSE_STEP_APPEARING == pause.step)
  {
    if(pause.alpha+0.007*time_interval >= pause.max_alpha)
    {
      pause.step = PAUSE_STEP_MENU;
      pause.alpha = 1.0;
    }
    pause.alpha += 0.007*time_interval;

    int x = 400 - pause.background -> get_width()/2;
    int y = 300 - pause.background -> get_height()/2;
    pause.background -> set_alpha(pause.alpha);
    pause.background -> draw(x,y);

    pause.resume -> set_alpha(pause.alpha);
    pause.resume_selected -> set_alpha(pause.alpha);
    pause.undo -> set_alpha(pause.alpha);
    pause.undo_selected -> set_alpha(pause.alpha);
    pause.undo_unavailable -> set_alpha(pause.alpha);
    pause.retry -> set_alpha(pause.alpha);
    pause.retry_selected -> set_alpha(pause.alpha);
    pause.changeskin -> set_alpha(pause.alpha);
    pause.changeskin_selected -> set_alpha(pause.alpha);
    pause.fullscreen -> set_alpha(pause.alpha);
    pause.fullscreen_selected -> set_alpha(pause.alpha);
    pause.sound -> set_alpha(pause.alpha);
    pause.sound_selected -> set_alpha(pause.alpha);
    pause.music -> set_alpha(pause.alpha);
    pause.music_selected -> set_alpha(pause.alpha);
    pause.backmain -> set_alpha(pause.alpha);
    pause.backmain_selected -> set_alpha(pause.alpha);
    pause.quit -> set_alpha(pause.alpha);
    pause.quit_selected -> set_alpha(pause.alpha);
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

    pause.resume -> set_alpha(pause.alpha);
    pause.resume_selected -> set_alpha(pause.alpha);
    pause.undo -> set_alpha(pause.alpha);
    pause.undo_selected -> set_alpha(pause.alpha);
    pause.undo_unavailable -> set_alpha(pause.alpha);
    pause.retry -> set_alpha(pause.alpha);
    pause.retry_selected -> set_alpha(pause.alpha);
    pause.changeskin -> set_alpha(pause.alpha);
    pause.changeskin_selected -> set_alpha(pause.alpha);
    pause.fullscreen -> set_alpha(pause.alpha);
    pause.fullscreen_selected -> set_alpha(pause.alpha);
    pause.sound -> set_alpha(pause.alpha);
    pause.sound_selected -> set_alpha(pause.alpha);
    pause.music -> set_alpha(pause.alpha);
    pause.music_selected -> set_alpha(pause.alpha);
    pause.backmain -> set_alpha(pause.alpha);
    pause.backmain_selected -> set_alpha(pause.alpha);
    pause.quit -> set_alpha(pause.alpha);
    pause.quit_selected -> set_alpha(pause.alpha);
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
    if(PAUSE_ITEM_RESUME == pause.selection)
    {
      pause.resume_selected -> draw(x + pause.resume_left, y + pause.resume_top);
      pause.resume_selected -> update();
    }
    else
    {
      pause.resume -> draw(x + pause.resume_left, y + pause.resume_top);
      pause.resume -> update();
    }

    if(PAUSE_ITEM_UNDO == pause.selection)
    {
      pause.undo_selected -> draw(x + pause.undo_left, y + pause.undo_top);
      pause.undo_selected -> update();
    }
    else if(undo.possible)
    {
      pause.undo -> draw(x + pause.undo_left, y + pause.undo_top);
      pause.undo -> update();
    }
    else
    {
      pause.undo_unavailable -> draw(x + pause.undo_left, y + pause.undo_top);
      pause.undo_unavailable -> update();
    }

    if(PAUSE_ITEM_RETRY == pause.selection)
    {
      pause.retry_selected -> draw(x + pause.retry_left, y + pause.retry_top);
      pause.retry_selected -> update();
    }
    else
    {
      pause.retry -> draw(x + pause.retry_left, y + pause.retry_top);
      pause.retry -> update();
    }

    if(PAUSE_ITEM_CHANGESKIN == pause.selection)
    {
      pause.changeskin_selected -> draw(x + pause.changeskin_left, y + pause.changeskin_top);
      pause.changeskin_selected -> update();
    }
    else
    {
      pause.changeskin -> draw(x + pause.changeskin_left, y + pause.changeskin_top);
      pause.changeskin -> update();
    }

    if(PAUSE_ITEM_FULLSCREEN == pause.selection)
    {
      pause.fullscreen_selected -> draw(x + pause.fullscreen_left, y + pause.fullscreen_top);
      pause.fullscreen_selected -> update();
    }
    else
    {
      pause.fullscreen -> draw(x + pause.fullscreen_left, y + pause.fullscreen_top);
      pause.fullscreen -> update();
    }

    if(PAUSE_ITEM_SOUND == pause.selection)
    {
      pause.sound_selected -> draw(x + pause.sound_left, y + pause.sound_top);
      pause.sound_selected -> update();
    }
    else
    {
      pause.sound -> draw(x + pause.sound_left, y + pause.sound_top);
      pause.sound -> update();
    }

    if(PAUSE_ITEM_MUSIC == pause.selection)
    {
      pause.music_selected -> draw(x + pause.music_left, y + pause.music_top);
      pause.music_selected -> update();
    }
    else
    {
      pause.music -> draw(x + pause.music_left, y + pause.music_top);
      pause.music -> update();
    }

    if(PAUSE_ITEM_BACKMAIN == pause.selection)
    {
      pause.backmain_selected -> draw(x + pause.backmain_left, y + pause.backmain_top);
      pause.backmain_selected -> update();
    }
    else
    {
      pause.backmain -> draw(x + pause.backmain_left, y + pause.backmain_top);
      pause.backmain_selected -> update();
    }

    if(PAUSE_ITEM_QUIT == pause.selection)
    {
      pause.quit_selected -> draw(x + pause.quit_left, y + pause.quit_top);
      pause.quit_selected -> update();
    }
    else
    {       
      pause.quit -> draw(x + pause.quit_left, y + pause.quit_top);
      pause.quit -> update();
    }    

    pause.sound_level[sound_level] -> draw(x + pause.sound_level_left, y + pause.sound_top);
    pause.sound_level[music_level] -> draw(x + pause.sound_level_left, y + pause.music_top);
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

   
  if(key_echap->get())
  {   
    if(pause.appearing && opengl)
      pause.step = PAUSE_STEP_DISAPPEARING;
    else
      pause.is_paused = false;
    
  }

  if(key_up -> get())
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

  if(pause.selection == PAUSE_ITEM_SOUND && key_left -> get())
  {
    if(sound_level > 0)
      sound_level--;
  }

  if(pause.selection == PAUSE_ITEM_SOUND && key_right -> get())
  {
    if(sound_level < 10)
      sound_level++;
  }

  if(pause.selection == PAUSE_ITEM_MUSIC && key_left -> get())
  {
    if(music_level > 0)
      music_level--;
  }

  if(pause.selection == PAUSE_ITEM_MUSIC && key_right -> get())
  {
    if(music_level < 10)
      music_level++;
  }

  if(key_down -> get())
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

  if(key_enter -> get())
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
