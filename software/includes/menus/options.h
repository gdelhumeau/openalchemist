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

#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#define OPTIONS_NUMBER_OF_ITEMS 5

class OptionsMenu{

  public:
  bool is_optionsd;
  bool appearing;
  bool requested;

  int step;
  int selection;
  float alpha, max_alpha;

  int resume_left, resume_top;
  int changeskin_left, changeskin_top;
  int fullscreen_left, fullscreen_top;
  int sound_left, sound_top;
  int music_left, music_top;
  int sound_level_left;

  /* Sprites */
  CL_Sprite *items[OPTIONS_NUMBER_OF_ITEMS];
  CL_Sprite *items_selected[OPTIONS_NUMBER_OF_ITEMS];
  int items_left[OPTIONS_NUMBER_OF_ITEMS];
  int items_top[OPTIONS_NUMBER_OF_ITEMS];

  CL_Sprite *background;  
  CL_Sprite *sound_level[11];

  /* Methods */

  void load_gfx(CL_ResourceManager *gfx_pause);
  void unload_gfx();
   

};



#endif /*_OPTIONS_H_*/
