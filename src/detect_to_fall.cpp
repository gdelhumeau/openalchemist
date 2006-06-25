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
#include <vector> 

/**
 * Detect the pieces to fall
 */ 
void Game::detect_to_fall()
{
  falling_list.clear();
  for(int i=0; i<NUMBER_OF_COLS; ++i)
    for(int j=NUMBER_OF_LINES-2; j>=0; --j)
    {
      if(body[i][j] != NULL)
      {
        int k = 1;
        while(j+k < NUMBER_OF_LINES && body[i][j+k] == NULL)
        {
          body[i][j+k] = body[i][j+k-1];
          body[i][j+k-1] = NULL;
          body[i][j+k] -> start_fall((int)(body[i][j+k]->get_x()),
                                     (int)(game_top+(j+k-2)*pieces_height));
          k++;
        }
        if(k>1)
        {
          falling_list.insert(falling_list.end(), body[i][j+k-1]);
        }
      }
    }
    
  game_mode = GAME_MODE_FALLING_AND_CREATING;
    
}
