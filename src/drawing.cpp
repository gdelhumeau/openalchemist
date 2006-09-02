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

/**
 * Draw the game
 */
void Game::draw_game()
{
       
  background->draw(0,0);    
  font_a->draw(580,550,to_string(fps)); 

  /* Displaying scores */
  std::string score = format_number(to_string(global_score));
  std::string bonus = format_number(to_string(global_bonus));
  std::string hightscore = format_number(to_string(hightscores[current_difficulty])); 

  int score_width = font_a->get_width(score, CL_Size(0, 0));
  int bonus_width = font_a->get_width(bonus, CL_Size(0, 0));
  int hightscore_width = font_a->get_width(hightscore, CL_Size(0, 0));

  font_a->draw(score_right - score_width, score_top, score);
  font_a->draw(bonus_right - bonus_width, bonus_top, bonus);
  font_a->draw(hightscore_right - hightscore_width, hightscore_top, hightscore);

  /* We draw unlocked pieces */
  for(int i=0; i<NUMBER_OF_PIECES; ++i)
  {
    if(i >= visible_pieces)
      pieces.hidder[i-3] -> draw(pieces.progress_x[i], pieces.progress_y[i], 0);
    else
      pieces.mini[i] -> draw(pieces.progress_x[i], pieces.progress_y[i], 0);
  }

  
  /* Drawing the body */
  for(int i=0; i<NUMBER_OF_COLS; ++i)
    for(int j=0; j<NUMBER_OF_LINES; ++j)
    {
      if(body[i][j])
      {
        body[i][j] -> draw(); 
      }
    }

  /* Draw the front layer */
  if(front_layer.enabled)
    front_layer.draw();

  /* Drawing the progress bar */
  draw_progress_bar();  


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
  else if(GAME_MODE_NEW_HIGHTSCORE == game_mode)
  {
    draw_new_hightscore();
  }

  if(pause.is_paused)
  {
    draw_pause();
  }

  
}

/**
 * Draw the game when player can play
 */
void Game::draw_playing()
{
  

  current_piece1 -> set_position(game_left+position_x+cos(current_pieces_angle*TO_RAD)*current_pieces_r,
                                 zone_top+pieces.height/2+sin((current_pieces_angle)*TO_RAD)*current_pieces_r);

  current_piece2 -> set_position(game_left+position_x+cos((current_pieces_angle+180)*TO_RAD)*current_pieces_r,
                                 zone_top+pieces.height/2+sin((current_pieces_angle+180)*TO_RAD)*current_pieces_r);
     
  current_piece1 -> draw();
  current_piece2 -> draw();
}

/**
 * Draw the game when pieces are falling
 */
void Game::draw_falling()
{

  if(pause.is_paused)
    return;

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
      if(game_mode != GAME_MODE_GAME_OVER && game_mode != GAME_MODE_NEW_HIGHTSCORE)
      {
      for(int i=0; i<NUMBER_OF_COLS; ++i)
        for(int j=0; j<2; ++j)
        {
    
          if(body[i][j] != NULL)
          {
            game_mode = GAME_MODE_GAME_OVER;
            if(global_score + global_bonus > hightscores[current_difficulty])
            {
              game_mode = GAME_MODE_NEW_HIGHTSCORE;
              save_scores();
            }
            return;
          }
        }
      }
    }
    detect_to_destroy();     
  
  }
}

/**
 * Draw the game when pieces are disappearing
 */
void Game::draw_destroying()
{

  if(pause.is_paused)return;

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
      

        int score = c->piece_number;
        Piece *p = new Piece(score);  
        p -> set_position(c->x*pieces.width+game_left,
                          game_top+(c->y-2)*pieces.height);
               
        p -> set_sprites(pieces.normal[score], pieces.appearing[score],
                         pieces.disappearing[score], pieces.mini[score]);

                        
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

/**
 * Draw the game when the player is going to play
 */
void Game::draw_to_playing()
{
  calc_score();
  if(game_mode != GAME_MODE_GAME_OVER && game_mode != GAME_MODE_NEW_HIGHTSCORE)
  {
    for(int i=0; i<NUMBER_OF_COLS; ++i)
      for(int j=0; j<2; ++j)
      {
      
        if(body[i][j] != NULL)
        {
          game_mode = GAME_MODE_GAME_OVER;
          if(global_score + global_bonus > hightscores[current_difficulty])
          {
            game_mode = GAME_MODE_NEW_HIGHTSCORE;
            save_scores();
          }
        
          return;
        }
      
      
      }
  }

  if(undo.next_next_piece1 >= 0)
  {
    next_piece1 -> set_piece_number(undo.next_next_piece1);
    next_piece2 -> set_piece_number(undo.next_next_piece2);
    undo.next_next_piece1 = -1;
  }
  else
  {
    next_piece1 -> set_piece_number(rand()%(unlocked_pieces));
    next_piece2 -> set_piece_number(rand()%(unlocked_pieces));
  }
          
  int value;
  value = next_piece1 -> get_piece_number();
  next_piece1 -> set_sprites(pieces.normal[value], pieces.appearing[value],
                             pieces.disappearing[value], pieces.mini[value]);
      
  value = next_piece2 -> get_piece_number();
  next_piece2 -> set_sprites(pieces.normal[value], pieces.appearing[value],
                             pieces.disappearing[value], pieces.mini[value]);
          
  game_mode = GAME_MODE_PLAYING;
  
  combo = 0;

}

/**
 * Draw the game when the game is over
 */
void Game::draw_game_over()
{
  if(current_piece1 -> fall(time_interval) & current_piece2 -> fall(time_interval))
    game_over -> draw(400-game_over->get_width()/2, 300-game_over->get_height()/2);
}

/**
 * Draw the game when the game is over
 */
void Game::draw_new_hightscore()
{
  if(current_piece1 -> fall(time_interval) & current_piece2 -> fall(time_interval))
  {
    new_hightscore -> draw(400-new_hightscore -> get_width()/2, 300-new_hightscore -> get_height()/2);
    new_hightscore -> update();
    font_a->draw(400-font_a->get_width(format_number(to_string(global_score+global_bonus)))/2, 
                 new_score_top, format_number(to_string(global_score+global_bonus)));
    font_a->draw(400-font_a->get_width(format_number(to_string(last_hightscore)))/2,
                 old_score_top, format_number(to_string(last_hightscore)));
  }

}

void Game::draw_progress_bar()
{
  int head_height = progress_bar.head -> get_height();
  int height = progress_bar.foot_top - (progress_bar.head_top + head_height);

  int v = height;
  if(hightscores[current_difficulty] > 0)
    v = height * (global_score + global_bonus) / hightscores[current_difficulty];
  if(v > height) v = height;

  for(int i=0; i<=height; ++i)
  {
    if(height - i < v)
      progress_bar.item_ok -> draw(progress_bar.left, progress_bar.head_top+head_height+i-1);
    else
      progress_bar.item -> draw(progress_bar.left, progress_bar.head_top+head_height+i-1);
  }
  progress_bar.item -> update();
  progress_bar.item_ok -> update();

  if(hightscores[current_difficulty] > global_score + global_bonus)
  {
    progress_bar.head -> draw(progress_bar.left, progress_bar.head_top);
    progress_bar.head -> update();
  }
  else
  {
    progress_bar.head_ok -> draw(progress_bar.left, progress_bar.head_top);
    progress_bar.head_ok -> update();
  }
  progress_bar.foot -> draw(progress_bar.left, progress_bar.foot_top);
  progress_bar.foot -> update();
}
