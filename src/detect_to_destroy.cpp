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
#include <stack>
#include <vector>
 
/**
 * Detect the pieces to destroy
 */ 
void Game::detect_to_destroy()
{
    
  game_mode = GAME_MODE_DETECTING_WHAT_DESTROY;    
  
  // This table is used to know if a piece have been explorated 
  bool body_mark[NUMBER_OF_COLS][NUMBER_OF_LINES];
  for(int k=0; k<NUMBER_OF_COLS; ++k)
    for(int l=0; l<NUMBER_OF_LINES; ++l)
      body_mark[k][l] = false;
      
  // Stack to explore the body
  std::stack<Coords*> stack;
  
  // We clear the list witch will contains the pieces to make disappear
  list_to_destroy.clear();
      
    
  // We will look for all pieces in the table
  for(int i=0; i<NUMBER_OF_COLS; ++i)
    for(int j=0; j<NUMBER_OF_LINES; ++j)
    {
      if(body[i][j] != NULL && !body_mark[i][j])
      {
        int counter = 0;            
        int score_of_root = body[i][j] -> get_score_value();
        
        std::vector<Coords*> list;
           
        stack.push(new Coords(i,j));
        while(!stack.empty())
        {
          Coords *c = stack.top(); 
          int x = c->x;
          int y = c->y;
          stack.pop(); 
          delete c;
                       
          if(x >= 0 && x < NUMBER_OF_COLS && y >= 0 && y < NUMBER_OF_LINES 
             && body[x][y]!=NULL)
          {
            if(!body_mark[x][y] && body[x][y]->get_score_value() == score_of_root)
            {
              list.insert(list.end(),new Coords(x,y));
              body_mark[x][y] = true;
              counter ++;
              stack.push(new Coords(x - 1, y));
              stack.push(new Coords(x + 1, y));
              stack.push(new Coords(x, y - 1));
              stack.push(new Coords(x, y + 1));                                                                  
            }
          }              
                             
        }
        if(counter >= 3)
        {
          if(body[i][j]->get_score_value() > 1)
          {
            global_bonus += (counter - 3)*(body[i][j]->get_score_value()-1)*3;
          }
          else
          {
            global_bonus += (counter - 3);
          }

          
          Coords new_piece(NUMBER_OF_COLS+1,-1);
          
          std::vector<Coords*>::iterator it = list.begin();
          while(it != list.end())
          {
            Coords *c = (Coords*) *it;                 
            body[c->x][c->y]->start_disappear();                    
            list_to_destroy.insert(list_to_destroy.end(),c);
                    
            // Select the lefter and bottomer Coords for create new piece
            if(c->y > new_piece.y)
            {
              new_piece.x = c->x;
              new_piece.y = c->y;
            }
            else if(c->y == new_piece.y)
            {
              if(c->x < new_piece.x)
              {
                new_piece.x = c->x;
                new_piece.y = c->y;
              }
            }
            new_piece.score = body[c->x][c->y]->get_score_value()+1;                          
            if(new_piece.score > NUMBER_OF_PIECES)
            {
              new_piece.score = NUMBER_OF_PIECES;
            }
            if(new_piece.score > visible_pieces)
            {
              ++visible_pieces;
            }
            if(new_piece.score > unlocked_pieces + 1)
            {
              unlocked_pieces ++;
            }

            ++it;
          }
                
          list_to_create.insert(list_to_create.end(), new Coords(&new_piece));
                
        }
      }
    }
    
  if(list_to_destroy.empty())
  {
    game_mode = GAME_MODE_TO_PLAYING;
  }
  else
  {
    game_mode = GAME_MODE_DESTROYING;
  }
    
            
}
 

