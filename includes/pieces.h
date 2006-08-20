/* OpenAlchemist - just a simple game 
 * ----------------------------------
 *
 * Copyright (C) 2005, 2006 Guillaume Delhumeau <guillaume.delhumeau at laposte.net>
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

#ifndef _PIECES_H_
#define _PIECES_H_

#include "misc.h"

class Pieces{

  public:
  CL_Sprite *normal[NUMBER_OF_PIECES];
  CL_Sprite *appearing[NUMBER_OF_PIECES];
  CL_Sprite *disappearing[NUMBER_OF_PIECES];
  CL_Sprite *mini[NUMBER_OF_PIECES];
  CL_Sprite *hidder[NUMBER_OF_PIECES-3];

  int width, height;

  // Mini Sprite coords  
  int progress_x[NUMBER_OF_PIECES];
  int progress_y[NUMBER_OF_PIECES];

  // Methods
  void load_gfx(CL_ResourceManager *gfx_pieces)
    {

      // First we load the sprites
      for(int i=1; i<=NUMBER_OF_PIECES; ++i)
      {
        normal[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/normal", gfx_pieces);
        appearing[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/appear", gfx_pieces);
        disappearing[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/disappear", gfx_pieces);
        mini[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/little", gfx_pieces);

   
        progress_x[i-1] = CL_Integer_to_int("pieces/piece_"+to_string(i)+"/progress-x", gfx_pieces);
        progress_y[i-1] = CL_Integer_to_int("pieces/piece_"+to_string(i)+"/progress-y", gfx_pieces);

        if(i>3)
          hidder[i-4] = new CL_Sprite("pieces/piece_"+to_string(i)+"/hidder", gfx_pieces);    

      }

      // Then, propreties
      width = CL_Integer_to_int("pieces/width", gfx_pieces);
      height = CL_Integer_to_int("pieces/height", gfx_pieces);

    }

  void unload_gfx()
    {
      // Delete the pieces sprites
      for(int i = 0; i<NUMBER_OF_PIECES; ++i)
      {
        delete normal[i];
        delete appearing[i];
        delete disappearing[i];

        if(i < NUMBER_OF_PIECES - 4)
          delete hidder[i];
      }
    }


};

#endif
