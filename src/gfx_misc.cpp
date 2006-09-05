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

#include "headers.h"

void GfxMisc::load_gfx(CL_ResourceManager *gfx)
    {
      background = new CL_Surface("background", gfx);
      game_over = new CL_Surface("gameover", gfx);  
      
      // Load the font, to display score and framerate
      font_a = new CL_Font("font", gfx);  

      // Load some var
  game_top = CL_Integer_to_int("game/top", gfx);
  game_left = CL_Integer_to_int("game/left", gfx); 

  zone_top = CL_Integer_to_int("zone_top", gfx);    
  next_left = CL_Integer_to_int("game/next_left", gfx);
  next_top = CL_Integer_to_int("game/next_top", gfx);
  score_top = CL_Integer_to_int("score_top", gfx);
  score_right = CL_Integer_to_int("score_right", gfx);
  bonus_right = CL_Integer_to_int("bonus_score_right", gfx);
  bonus_top = CL_Integer_to_int("bonus_score_top", gfx);
  hightscore_right = CL_Integer_to_int("hight_score_right", gfx);
  hightscore_top = CL_Integer_to_int("hight_score_top", gfx);
  new_score_top = CL_Integer_to_int("menu/new-hightscore/new-score-top", gfx);
  old_score_top = CL_Integer_to_int("menu/new-hightscore/old-score-top", gfx);

  new_hightscore = new CL_Sprite("menu/new-hightscore/dialog", gfx);
  
  

    }

  void GfxMisc::unload_gfx()
    {
      delete background;
      delete game_over;
      delete font_a;
      delete new_hightscore;
    }
