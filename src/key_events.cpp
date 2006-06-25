/* OpenAlchemist - just a simple game 
 * ----------------------------------
 *
 * Copyright (C) 2005 Guillaume Delhumeau <guillaume.delhumeau at laposte.net>
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

#define TO_RAD PI/180

/**
 * Key events
 */
void Game::key_events()
{
  // Switch to fullscreen/windowed mode
  if(key_fullscreen->get())
  {
    toggle_screen();
  }
    
  // New game
  if(key_retry->get())
  {
    new_game();
  }
    
  
  // Key entries are for the playing mode only 
  if(GAME_MODE_PLAYING == game_mode)
  {  
    // Change the order of the pieces 
    if(key_change_angle->get() && current_pieces_next_angle<=current_pieces_angle+90)
    {     
      current_pieces_next_angle += 90;
      current_pieces_placed = false;

      if((current_pieces_next_angle%180 == 90))
      {
        position_bis = 0;
      }
      else
      {
        if(position == NUMBER_OF_COLS -1)
          position --;
        
        position_bis = 1;
      }

    }

    // Look the key to know if we have to move the pieces to the left
    if(key_left->get() && position > 0)
    {
      old_position = position;
      old_position_bis = position_bis;
      position--;
      current_pieces_placed = false;
    }

    // Look the key to know if we have to move the pieces to the right
    if(key_right->get() && position < NUMBER_OF_COLS - 1)
    {
      if(!(position == NUMBER_OF_COLS - 2 && position_bis))
      {
        old_position = position;
        old_position_bis = position_bis;
        position++;
        current_pieces_placed = false;
      }
    }

    // Move the pieces if the order has been changed      
    if(current_pieces_angle<current_pieces_next_angle)
    {
      current_pieces_angle += time_interval * 0.35;
      if(current_pieces_angle>=current_pieces_next_angle)
      {
        while(current_pieces_next_angle>=360)
        {
          current_pieces_next_angle-=360;             
        }
        current_pieces_angle = current_pieces_next_angle;
      }
    }
      
    // Move the pieces to the right
    if(!current_pieces_placed)
    {
      if(position * pieces_width + position_bis *pieces_width/2 >= position_x)
      {
        position_x += time_interval * 0.25;
        if(position_x > position * pieces_width + (position_bis )*pieces_width/2)
        {
          position_x = position * pieces_width + (position_bis )*pieces_width/2;
          current_pieces_placed = true;
        }
      }
    }

    if(!current_pieces_placed) 
    {  
      // Move the pieces to the left
      if(position * pieces_width + (position_bis )*pieces_width/2 <= position_x)
      {
        position_x -= time_interval * 0.25;
        if(position_x < position * pieces_width + (position_bis)*pieces_width/2)
        {
          position_x = position * pieces_width + (position_bis)*pieces_width/2;
          current_pieces_placed = true;
        }
      }
    }
          

    

    // It's time for the pieces to fall
    if(key_falling -> get())
    {
      falling_requested = true; 
    } 
      
    if(falling_requested && current_pieces_placed && (current_pieces_angle >= current_pieces_next_angle))
    {
      falling_requested = false;
        

      current_piece1 -> set_position(game_left+position_x+cos(current_pieces_angle*TO_RAD)*current_pieces_r,
                                 zone_top+pieces_height/2+sin((current_pieces_angle)*TO_RAD)*current_pieces_r);

      current_piece2 -> set_position(game_left+position_x+cos((current_pieces_angle+180)*TO_RAD)*current_pieces_r,
                                 zone_top+pieces_height/2+sin((current_pieces_angle+180)*TO_RAD)*current_pieces_r);
      
      Piece *piece_on_top, *piece_on_bottom;
      if(current_piece1 -> get_y() <= current_piece2 -> get_y())
      {
        piece_on_top = current_piece1;
        piece_on_bottom = current_piece2;
      }
      else
      {
        piece_on_top = current_piece2;
        piece_on_bottom = current_piece1;
      }

      int piece_top_x = (int)((int)piece_on_top->get_x()-game_left)/(pieces_width);
      int piece_bottom_x = (int)((int)piece_on_bottom->get_x()-game_left)/(pieces_width);  
        
      int y_bottom = -1;
      while(y_bottom < NUMBER_OF_LINES-1 && !body[piece_bottom_x][y_bottom+1])
      {
        ++y_bottom;
      }    
        
      if(y_bottom == -1 && body[piece_bottom_x][0])
      {
        game_mode = GAME_MODE_GAME_OVER;
      }
      else
      {
        body[piece_bottom_x][y_bottom] = piece_on_bottom;
      }
                
                
      int y_top = -1;
      while(y_top < NUMBER_OF_LINES-1 && !body[piece_top_x][y_top+1])
      {
        ++y_top;
      }      
        
      if(y_top==-1 && body[piece_top_x][0])
      {
        game_mode = GAME_MODE_GAME_OVER;
        body[piece_bottom_x][y_bottom] = NULL;
      }
      else
      {          
        body[piece_top_x][y_top] = piece_on_top;
      } 
      piece_on_bottom -> start_fall(piece_bottom_x*pieces_width+game_left,game_top+(y_bottom-2)*pieces_height);
      piece_on_top -> start_fall(piece_top_x*pieces_width+game_left,game_top+(y_top-2)*pieces_height);
               
        
      if(game_mode == GAME_MODE_PLAYING)
      {
        falling_list.clear();
        falling_list.push_back(piece_on_top);
        falling_list.push_back(piece_on_bottom);
    
        current_piece1 = new Piece(next_piece1->get_score_value());
        current_piece2 = new Piece(next_piece2->get_score_value());
            
      
            
    
        int value = current_piece1 -> get_score_value() - 1;
        current_piece1 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                                      pieces_disappearing[value], pieces_mini[value]);
      
        value = current_piece2 -> get_score_value() - 1;
        current_piece2 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                                      pieces_disappearing[value], pieces_mini[value]);
            
            
        game_mode = GAME_MODE_FALLING_AND_CREATING;      
      }  
 
    }    
      
  }


}
