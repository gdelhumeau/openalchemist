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

#include <math.h>
#include <stdlib.h>
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "piece.h"
#include "game.h"
#include "misc.h"

#define TO_RAD PI/180

void Game::draw_game()
{
       
  background->draw(0,0);    
  font_a->draw(580,550,to_string(fps));  
  font_a->draw(score_left, score_top, to_string(global_score));
  font_a->draw(bonus_left, bonus_top, to_string(global_bonus));

  /* We draw unlocked pieces */
  for(int i=NUMBER_OF_PIECES-1; i>=visible_pieces; --i)
  {
    pieces_hidder[i-3] -> draw(pieces_progress_x[i-3], pieces_progress_y[i-3], 0);
  }

  for(int i=0; i<NUMBER_OF_COLS; ++i)
    for(int j=0; j<NUMBER_OF_LINES; ++j)
    {
      if(body[i][j])
      {
        body[i][j] -> draw(); 
      }
    }

  

  next_piece1 -> draw_mini();
  next_piece2 -> draw_mini();

  if(GAME_MODE_PLAYING == game_mode)
  {
    draw_playing();
  }
  else if(GAME_MODE_FALLING_AND_CREATING == game_mode)
  {
    draw_falling();    
  }
  else if(GAME_MODE_DESTROYING == game_mode)
  {
    draw_destroying();     
  }  
  else if(GAME_MODE_DETECTING_WHAT_FALL == game_mode)
  {
    detect_to_fall();
  }  
  else if(GAME_MODE_TO_PLAYING == game_mode)
  {          
    draw_to_playing();
  }
  else if(GAME_MODE_GAME_OVER == game_mode)
  {
    draw_game_over();
  }

  
}

void Game::draw_playing()
{
  

  current_piece1 -> set_position(game_left+position_x+cos(current_pieces_angle*TO_RAD)*current_pieces_r,
                                 zone_top+pieces_height/2+sin((current_pieces_angle)*TO_RAD)*current_pieces_r);

  current_piece2 -> set_position(game_left+position_x+cos((current_pieces_angle+180)*TO_RAD)*current_pieces_r,
                                 zone_top+pieces_height/2+sin((current_pieces_angle+180)*TO_RAD)*current_pieces_r);
     
  current_piece1 -> draw();
  current_piece2 -> draw();
}

void Game::draw_falling()
{
  bool all_pieces_are_placed = true;
  for(u_int i=0; i<falling_list.size(); ++i)
  {
    if(falling_list[i])
    {
      if(!falling_list[i] -> fall(time_interval))
        all_pieces_are_placed = false;
    }
  }

  /* This part makes pieces appear */
  std::list<Piece*>::iterator it = appearing_list.begin();
  while(it != appearing_list.end())
  {
    Piece *p = (Piece*)*it;
    if(p -> appear())
    {
      it = appearing_list.erase(it);
    }
    else
    {
      all_pieces_are_placed = false;
      ++it;
    }
  }
  
  
  if(all_pieces_are_placed)
  {
    
    combo ++;
    
    /* Only the second time */
    if(combo == 2)
    {
      for(int i=0; i<NUMBER_OF_COLS; ++i)
        for(int j=0; j<2; ++j)
        {
          if(body[i][j] != NULL)
          {
            game_mode = GAME_MODE_GAME_OVER;
            return;
          }
        }
    }
    detect_to_destroy();     
  
  }
}

void Game::draw_destroying()
{
  bool end = true;
  for(u_int i=0; i<list_to_destroy.size(); i++)
  {    
    if(list_to_destroy[i])
    {
      Coords *c = list_to_destroy[i];
            
      if(body[c->x][c->y] != NULL && !body[c->x][c->y]->disappear())
      {
        end = false;
      }
      else
      {
        delete body[c->x][c->y];
        body[c->x][c->y] = NULL;
        delete c;
        list_to_destroy[i] = NULL;
      }
    }
  }


  if(end)
  {
    list_to_destroy.clear(); 
    appearing_list.clear();
    
    std::list<Coords*>::iterator it = list_to_create.begin();
    while(it != list_to_create.end())
    {
      Coords *c = (Coords*) *it;
      if(c && c->x >= 0 && c->x < NUMBER_OF_COLS
         && c->y >=0 && c->y < NUMBER_OF_LINES
         && !body[c->x][c->y])
      {
      

        int score = c->score;
        Piece *p = new Piece(score);  
        p -> set_position(c->x*pieces_width+game_left,
                          game_top+(c->y-2)*pieces_height);
               
        p -> set_sprites(pieces_normal[score-1], pieces_appearing[score-1],
                         pieces_disappearing[score-1], pieces_mini[score-1]);

                        
        p -> start_appear();
                
        body[c->x][c->y] = p; 
        appearing_list.insert(appearing_list.begin(), p);

        delete c;
        it = list_to_create.erase(it);
      }
    }   

      
        
    game_mode = GAME_MODE_DETECTING_WHAT_FALL;   
  }    
}

void Game::draw_to_playing()
{
  for(int i=0; i<NUMBER_OF_COLS; ++i)
    for(int j=0; j<2; ++j)
    {
      if(body[i][j] != NULL)
      {
        game_mode = GAME_MODE_GAME_OVER;
        return;
      }
    }

  next_piece1 -> set_score_value(1+rand()%(unlocked_pieces));
  next_piece2 -> set_score_value(1+rand()%(unlocked_pieces));
          
  int value;
  value = next_piece1 -> get_score_value() - 1;
  next_piece1 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                             pieces_disappearing[value], pieces_mini[value]);
      
  value = next_piece2 -> get_score_value() - 1;
  next_piece2 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                             pieces_disappearing[value], pieces_mini[value]);
          
  game_mode = GAME_MODE_PLAYING;
  calc_score();

  combo = 0;

}

void Game::draw_game_over()
{
  current_piece1 -> draw();
  current_piece2 -> draw();
    
  if(current_piece1 -> fall(time_interval) & current_piece2 -> fall(time_interval))
    game_over -> draw(400-game_over->get_width()/2, 300-game_over->get_height()/2);
}
