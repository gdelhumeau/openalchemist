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




void Game::draw_pause()
{
  if(PAUSE_STEP_APPEARING == pause_step)
  {
    pause_alpha += 0.007*time_interval;
    if(pause_alpha >= pause_max_alpha)
    {
      pause_step = PAUSE_STEP_MENU;
      pause_alpha = 1.0;
    }

    int x = 400 - pause_background -> get_width()/2;
    int y = 300 - pause_background -> get_height()/2;
    pause_background -> set_alpha(pause_alpha);
    pause_background -> draw(x,y);

    pause_resume -> set_alpha(pause_alpha);
    pause_resume_selected -> set_alpha(pause_alpha);
    pause_undo -> set_alpha(pause_alpha);
    pause_undo_selected -> set_alpha(pause_alpha);
    pause_undo_unavailable -> set_alpha(pause_alpha);
    pause_retry -> set_alpha(pause_alpha);
    pause_retry_selected -> set_alpha(pause_alpha);
    pause_changeskin -> set_alpha(pause_alpha);
    pause_changeskin_selected -> set_alpha(pause_alpha);
    pause_fullscreen -> set_alpha(pause_alpha);
    pause_fullscreen_selected -> set_alpha(pause_alpha);
    pause_backmain -> set_alpha(pause_alpha);
    pause_backmain_selected -> set_alpha(pause_alpha);
    pause_quit -> set_alpha(pause_alpha);
    pause_quit_selected -> set_alpha(pause_alpha);


  }
  else if(PAUSE_STEP_DISAPPEARING == pause_step)
  {
    pause_alpha -= 0.007*time_interval;
    if(pause_alpha <= 0.0)
      pause = false;

    int x = 400 - pause_background -> get_width()/2;
    int y = 300 - pause_background -> get_height()/2;
    pause_background -> set_alpha(pause_alpha);
    pause_background -> draw(x,y);    

    pause_resume -> set_alpha(pause_alpha);
    pause_resume_selected -> set_alpha(pause_alpha);
    pause_undo -> set_alpha(pause_alpha);
    pause_undo_selected -> set_alpha(pause_alpha);
    pause_undo_unavailable -> set_alpha(pause_alpha);
    pause_retry -> set_alpha(pause_alpha);
    pause_retry_selected -> set_alpha(pause_alpha);
    pause_changeskin -> set_alpha(pause_alpha);
    pause_changeskin_selected -> set_alpha(pause_alpha);
    pause_fullscreen -> set_alpha(pause_alpha);
    pause_fullscreen_selected -> set_alpha(pause_alpha);
    pause_sound -> set_alpha(pause_alpha);
    pause_sound_selected -> set_alpha(pause_alpha);
    pause_music -> set_alpha(pause_alpha);
    pause_music_selected -> set_alpha(pause_alpha);
    pause_backmain -> set_alpha(pause_alpha);
    pause_backmain_selected -> set_alpha(pause_alpha);
    pause_quit -> set_alpha(pause_alpha);
    pause_quit_selected -> set_alpha(pause_alpha);
    
  }

  //else if(PAUSE_STEP_MENU == pause_step)
  {
    int x = 400 - pause_background -> get_width()/2;
    int y = 300 - pause_background -> get_height()/2;
    pause_background -> draw(x,y);
    pause_background -> update();


    // Drawing 
    if(PAUSE_ITEM_RESUME == pause_selection)
    {
      pause_resume_selected -> draw(x + pause_resume_left, y + pause_resume_top);
      pause_resume_selected -> update();
    }
    else
    {
      pause_resume -> draw(x + pause_resume_left, y + pause_resume_top);
      pause_resume -> update();
    }

    if(PAUSE_ITEM_UNDO == pause_selection)
    {
      pause_undo_selected -> draw(x + pause_undo_left, y + pause_undo_top);
      pause_undo_selected -> update();
    }
    else if(undo)
    {
      pause_undo -> draw(x + pause_undo_left, y + pause_undo_top);
      pause_undo -> update();
    }
    else
    {
      pause_undo_unavailable -> draw(x + pause_undo_left, y + pause_undo_top);
      pause_undo_unavailable -> update();
    }

    if(PAUSE_ITEM_RETRY == pause_selection)
    {
      pause_retry_selected -> draw(x + pause_retry_left, y + pause_retry_top);
      pause_retry_selected -> update();
    }
    else
    {
      pause_retry -> draw(x + pause_retry_left, y + pause_retry_top);
      pause_retry -> update();
    }

    if(PAUSE_ITEM_CHANGESKIN == pause_selection)
    {
      pause_changeskin_selected -> draw(x + pause_changeskin_left, y + pause_changeskin_top);
      pause_changeskin_selected -> update();
    }
    else
    {
      pause_changeskin -> draw(x + pause_changeskin_left, y + pause_changeskin_top);
      pause_changeskin -> update();
    }

    if(PAUSE_ITEM_FULLSCREEN == pause_selection)
    {
      pause_fullscreen_selected -> draw(x + pause_fullscreen_left, y + pause_fullscreen_top);
      pause_fullscreen_selected -> update();
    }
    else
    {
      pause_fullscreen -> draw(x + pause_fullscreen_left, y + pause_fullscreen_top);
      pause_fullscreen -> update();
    }

    if(PAUSE_ITEM_SOUND == pause_selection)
    {
      pause_sound_selected -> draw(x + pause_sound_left, y + pause_sound_top);
      pause_sound_selected -> update();
    }
    else
    {
      pause_sound -> draw(x + pause_sound_left, y + pause_sound_top);
      pause_sound -> update();
    }

    if(PAUSE_ITEM_MUSIC == pause_selection)
    {
      pause_music_selected -> draw(x + pause_music_left, y + pause_music_top);
      pause_music_selected -> update();
    }
    else
    {
      pause_music -> draw(x + pause_music_left, y + pause_music_top);
      pause_music -> update();
    }

    if(PAUSE_ITEM_BACKMAIN == pause_selection)
    {
      pause_backmain_selected -> draw(x + pause_backmain_left, y + pause_backmain_top);
      pause_backmain_selected -> update();
    }
    else
    {
      pause_backmain -> draw(x + pause_backmain_left, y + pause_backmain_top);
      pause_backmain_selected -> update();
    }

    if(PAUSE_ITEM_QUIT == pause_selection)
    {
      pause_quit_selected -> draw(x + pause_quit_left, y + pause_quit_top);
      pause_quit_selected -> update();
    }
    else
    {       
      pause_quit -> draw(x + pause_quit_left, y + pause_quit_top);
      pause_quit -> update();
    }    

    pause_sound_level[sound_level] -> draw(x + pause_sound_level_left, y + pause_sound_top);
    pause_sound_level[music_level] -> draw(x + pause_sound_level_left, y + pause_music_top);
    pause_sound_level[sound_level] -> update();
    pause_sound_level[music_level] -> update();

  }
}

void Game::key_events_pause()
{
  if(pause_step == PAUSE_STEP_APPEARING)
    return;

   
  if(key_echap->get())
  {
    if(pause_appearing && opengl)
      pause_step = PAUSE_STEP_DISAPPEARING;
    else
      pause = false;
  }

  if(key_up -> get())
  {
    if(pause_selection == 0)
      pause_selection = PAUSE_ITEM_QUIT;
    else
    {
      pause_selection --;
      if(pause_selection == PAUSE_ITEM_UNDO && !undo)
      {
        pause_selection --;
      }
    }
  }

  if(pause_selection == PAUSE_ITEM_SOUND && key_left -> get())
  {
    if(sound_level > 0)
      sound_level--;
  }

  if(pause_selection == PAUSE_ITEM_SOUND && key_right -> get())
  {
    if(sound_level < 10)
      sound_level++;
  }

  if(pause_selection == PAUSE_ITEM_MUSIC && key_left -> get())
  {
    if(music_level > 0)
      music_level--;
  }

  if(pause_selection == PAUSE_ITEM_MUSIC && key_right -> get())
  {
    if(music_level < 10)
      music_level++;
  }

  if(key_down -> get())
  {
    if(pause_selection == PAUSE_ITEM_QUIT)
       pause_selection = 0;
    else
    {
      pause_selection ++;
      if(pause_selection == PAUSE_ITEM_UNDO && !undo)
      {
        pause_selection ++;
      }
    }
  }

  if(key_enter -> get())
  {
    switch(pause_selection)
    {
    case PAUSE_ITEM_RESUME:
      if(pause_appearing && opengl)
        pause_step = PAUSE_STEP_DISAPPEARING;
      else
        pause = false;
      break;
    case PAUSE_ITEM_UNDO:
      undo_last();
      if(pause_appearing && opengl)
        pause_step = PAUSE_STEP_DISAPPEARING;
      else
        pause = false;
      pause = false;
      break;
    case PAUSE_ITEM_RETRY:
      if(pause_appearing && opengl)
        pause_step = PAUSE_STEP_DISAPPEARING;
      else
        pause = false;
      pause = false;
      new_game(0);
      break;
    case PAUSE_ITEM_CHANGESKIN:
      break;
    case PAUSE_ITEM_FULLSCREEN:
      toggle_screen();
      break;
    case PAUSE_ITEM_BACKMAIN:
      break;
    case PAUSE_ITEM_QUIT:
      end = true;
      pause = false;
    }
  }



}
