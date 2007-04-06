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


void Game::undo_last()
{
  // First verify than the last move is not the first one
  if(undo.possible)
  {
    undo.possible = false;

    // Delete the pieces in the body and replace by new ones
    for(int i=0; i<NUMBER_OF_COLS; ++i)
      for(int j=0; j<NUMBER_OF_LINES; ++j)
      {
        if(body[i][j]) delete body[i][j];
        body[i][j] = NULL;
        if(undo.body[i][j] >= 0)
        {
          body[i][j] = new Piece(undo.body[i][j]);
          body[i][j] -> set_sprites(pieces.normal[undo.body[i][j]], pieces.appearing[undo.body[i][j]],
                                    pieces.disappearing[undo.body[i][j]], pieces.mini[undo.body[i][j]]);
          body[i][j] -> set_position(i*pieces.width+gfx_misc.game_left,gfx_misc.game_top+(j-2)*pieces.height);
        }
      } 

    global_bonus -= undo.global_bonus;

    undo.next_next_piece1 = next_piece1 -> get_piece_number();
    undo.next_next_piece2 = next_piece2 -> get_piece_number();
  
    
    int value = current_piece1 -> get_piece_number();
    next_piece1 -> set_piece_number(value);
    next_piece1 -> set_sprites(pieces.normal[value], pieces.appearing[value],
                               pieces.disappearing[value], pieces.mini[value]);

    value = current_piece2 -> get_piece_number();
    next_piece2 -> set_piece_number(value);
    next_piece2 -> set_sprites(pieces.normal[value], pieces.appearing[value],
                               pieces.disappearing[value], pieces.mini[value]);

    value = undo.piece1_number;
    current_piece1 -> set_piece_number(value);
    current_piece1 -> set_sprites(pieces.normal[value], pieces.appearing[value],
                                  pieces.disappearing[value], pieces.mini[value]);

    value = undo.piece2_number;
    current_piece2 -> set_piece_number(value);
    current_piece2 -> set_sprites(pieces.normal[value], pieces.appearing[value],
                                  pieces.disappearing[value], pieces.mini[value]);

        
    position = undo.position;
    position_bis = undo.position_bis;
    position_x = position * pieces.width + position_bis * pieces.width / 2;

    current_pieces_angle = undo.angle;
    current_pieces_next_angle = undo.angle;

    unlocked_pieces = undo.unlocked_pieces;
    visible_pieces =  undo.visible_pieces;

    calc_score();

    game_mode = GAME_MODE_PLAYING;
        
  }
}
