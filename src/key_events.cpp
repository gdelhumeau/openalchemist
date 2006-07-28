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
#define PIECE_MOVING_SPEED 0.25


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
    new_game(0);
  }

  if(CL_Keyboard::get_keycode(CL_KEY_F9))
  {
    pause = true;
    pause_step = PAUSE_STEP_SKINS;
    choose_skin();
    pause_background -> set_alpha(1.0);
    pause_requested = false;
  }
    
  if(pause)
    key_events_pause();
  else
    key_events_playing();
  
}

void Game::key_events_playing()
{

  if(key_echap->get())
  {
    pause = true;
    pause_selection = 0;
    pause_alpha = 0.0;
    pause_requested = true;

    if(pause_appearing)
      pause_step = PAUSE_STEP_APPEARING;
    else
      pause_step = PAUSE_STEP_MENU;
  }
  
  if(GAME_MODE_PLAYING == game_mode || GAME_MODE_GAME_OVER == game_mode)
  {
   // Undo the last move
    if(key_undo -> get())
    {
      undo_last();
    }
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
        position_x += time_interval * PIECE_MOVING_SPEED;
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
        position_x -= time_interval * PIECE_MOVING_SPEED;
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
      undo_global_bonus = 0;

      undo = true;
      
      // Copy to the undo body
      for(int i=0; i<NUMBER_OF_COLS; ++i)
        for(int j=0; j<NUMBER_OF_LINES; ++j)
        {
          if(body[i][j])
          {
            body_undo[i][j] = body[i][j] -> get_score_value();
          }
          else
          {
            body_undo[i][j] = 0;
          }
        } 

      undo_global_bonus = 0;
      undo_position = position;
      undo_position_bis = position_bis;
      undo_piece1_score = current_piece1 -> get_score_value();
      undo_piece2_score = current_piece2 -> get_score_value();
      undo_angle = current_pieces_next_angle;
      undo_unlocked_pieces = unlocked_pieces;
      undo_visible_pieces = visible_pieces;
        

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


void Game::undo_last()
{
  // First verify than the last move is not the first one
  if(undo)
  {
    undo = false;

    // Delete the pieces in the body and replace by new ones
    for(int i=0; i<NUMBER_OF_COLS; ++i)
      for(int j=0; j<NUMBER_OF_LINES; ++j)
      {
        if(body[i][j]) delete body[i][j];
        body[i][j] = NULL;
        if(body_undo[i][j] > 0)
        {
          body[i][j] = new Piece(body_undo[i][j]);
          body[i][j] -> set_sprites(pieces_normal[body_undo[i][j]-1], pieces_appearing[body_undo[i][j]-1],
                                    pieces_disappearing[body_undo[i][j]-1], pieces_mini[body_undo[i][j]-1]);
          body[i][j] -> set_position(i*pieces_width+game_left,game_top+(j-2)*pieces_height);
        }
      } 

    global_bonus -= undo_global_bonus;

    undo_next_next_piece1 = next_piece1 -> get_score_value();
    undo_next_next_piece2 = next_piece2 -> get_score_value();
        
    int value = current_piece1 -> get_score_value() - 1;
    next_piece1 -> set_score_value(value+1);
    next_piece1 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                               pieces_disappearing[value], pieces_mini[value]);

    value = current_piece2 -> get_score_value() - 1;
    next_piece2 -> set_score_value(value+1);
    next_piece2 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                               pieces_disappearing[value], pieces_mini[value]);

    value = undo_piece1_score - 1;
    current_piece1 -> set_score_value(value+1);
    current_piece1 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                                  pieces_disappearing[value], pieces_mini[value]);

    value = undo_piece2_score - 1;
    current_piece2 -> set_score_value(value+1);
    current_piece2 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                                  pieces_disappearing[value], pieces_mini[value]);

        
    position = undo_position;
    position_bis = undo_position_bis;
    position_x = position * pieces_width + position_bis * pieces_width / 2;

    current_pieces_angle = undo_angle;
    current_pieces_next_angle = undo_angle;

    unlocked_pieces = undo_unlocked_pieces;
    visible_pieces =  undo_visible_pieces;

    calc_score();

    game_mode = GAME_MODE_TO_PLAYING;
        
  }
}
