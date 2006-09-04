/* OpenAlchemist - just a simple game 
 * ----------------------------------
 *
 * Copyright (C) 2005, 2006 Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
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

#ifndef _GFX_MISC_H_
#define _GFX_MISC_H_

#include "headers.h"

class GfxMisc{

  public:
  
  // Sprites
  CL_Surface * background, *game_over;
  CL_Sprite *new_hightscore;
  CL_Font *font_a;

  int game_top, game_left, zone_top, next_top, next_left;
  
  int score_top, score_right;
  int bonus_top, bonus_right;
  int hightscore_top, hightscore_right;
  int new_score_top, old_score_top;

  void load_gfx(CL_ResourceManager *gfx);
  void unload_gfx();
   
};

#endif
