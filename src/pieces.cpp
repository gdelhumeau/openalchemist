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

#include "headers.h"

void Pieces::load_gfx(CL_ResourceManager *gfx_pieces)
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

void Pieces::unload_gfx()
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

void Game::apply_skin()
{

  // We have to change the sprite references in the Pieces...
  for(int i=0; i<NUMBER_OF_COLS; ++i)
    for(int j=0; j<NUMBER_OF_LINES; ++j)
    {
      if(body[i][j])
      {
        int value = body[i][j] -> get_piece_number();
        body[i][j] -> set_sprites(pieces.normal[value], pieces.appearing[value],
                                  pieces.disappearing[value], pieces.mini[value]);
      }
    }

  int value;
  value = next_piece1 -> get_piece_number();
  next_piece1 -> set_sprites(pieces.normal[value], pieces.appearing[value],
                             pieces.disappearing[value], pieces.mini[value]);
  
  value = next_piece2 -> get_piece_number();
  next_piece2 -> set_sprites(pieces.normal[value], pieces.appearing[value],
                             pieces.disappearing[value], pieces.mini[value]);
  
  value = current_piece1 ->  get_piece_number();
  current_piece1 -> set_sprites(pieces.normal[value], pieces.appearing[value],
                                pieces.disappearing[value], pieces.mini[value]);
  
  value = current_piece2 ->  get_piece_number();
  current_piece2 -> set_sprites(pieces.normal[value], pieces.appearing[value],
                                pieces.disappearing[value], pieces.mini[value]);

  // The next_pieces depends on the skin, so:
  next_piece1 -> set_position(next_left, next_top);
  next_piece2 -> set_position(next_left+(pieces.width)/2,next_top);
  

}
