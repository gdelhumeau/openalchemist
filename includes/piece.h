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

#ifndef _PIECE_H_
#define _PIECE_H_

#include <ClanLib/display.h>

#define PIECE_SPEED 0.4

class Piece
{
  private:

  // For display:
  CL_Sprite *normal_sprite;
  CL_Sprite *appearing_sprite;
  CL_Sprite *disappearing_sprite;
  CL_Sprite *current_sprite;
  CL_Sprite *mini_sprite;

  // For scores:
  int score_value;

  // Real coords on the screen
  float x, y;

  // Goal target coord
  int target_y;

    
  public:

  // Constructor
  Piece(int score_value)
  {

    normal_sprite = NULL;
    appearing_sprite = NULL;
    disappearing_sprite = NULL;
    mini_sprite = NULL;
    current_sprite = NULL;    

    this -> score_value = score_value;
    x = 0.0;
    y = 0.0;
    target_y = 0;      
  }
  
  // Method to set the sprites
  void set_sprites(CL_Sprite *normal, CL_Sprite *appearing, CL_Sprite *disappearing, CL_Sprite *mini)
  {
    normal_sprite = normal;
    appearing_sprite = appearing;
    disappearing_sprite = disappearing;
    mini_sprite = mini;
    current_sprite = normal_sprite;
  }
 
  // Methods to display - be carefull, if current_prite is not initialized
  void Piece::draw(CL_GraphicContext* context = 0)
    {
      current_sprite -> draw(x, y, context);
    }

  void Piece::draw_mini(CL_GraphicContext* context = 0)
    {
      mini_sprite -> draw(x, y, context); 
    }

  void start_appear()
    {
      appearing_sprite -> set_play_loop(false);
      current_sprite = appearing_sprite;
      current_sprite -> restart();      
    }

  void start_disappear()
    {
      disappearing_sprite -> set_play_loop(false);
      current_sprite = disappearing_sprite;
      current_sprite -> restart();
    }

  void start_fall(int target_x, int target_y)
    {
      this -> target_y = target_y;
      x = target_x;
    }

  void set_normal()
    {
      current_sprite = normal_sprite;
    }

 // Return true if the piece is appeared
  bool appear()
    {
      if(current_sprite != appearing_sprite)
        return true;

      appearing_sprite -> update();
      if(appearing_sprite -> is_finished())
      {
        current_sprite = normal_sprite;
        return true;
      }
   
      return false;
    }

  // Return true if the piece is disappeared
  bool disappear()
    {
      disappearing_sprite -> update();
      if(disappearing_sprite -> is_finished())
      {
        current_sprite = normal_sprite;
        return true;
      }
      return false;


    }


  // Return true if the piece is placed
  bool fall(float time_interval)
    {
      y += PIECE_SPEED * time_interval;
      if(y >= target_y)
      {
        y = target_y;
        return true;
      }

      return false;
    }
    
  void set_score_value(int _score_value)
    {
      score_value = _score_value; 
    }

  int get_score_value()
    {
      return score_value;
    }

  // Setters
  void set_x(float x)
    {
      this -> x = x;
    }

  void set_y(float y)
    {
      this -> y = y;
    }

  void set_position(float x, float y)
  {
    this -> x = x;
    this -> y = y;
  }
  
  //Getters
  float get_x()
  {
    return x;
  }
  
  float get_y()
  {
    return y;
  }

  void print()
    {
      std::cout << "-----\nnormal_sprite: " << normal_sprite << "\n"
        << "appearing_sprite: " << appearing_sprite << "\n"
                << "disappearing_spirte: " << disappearing_sprite << "\n"
                << "current_sprite: " << current_sprite << "\n";
      if(current_sprite == appearing_sprite)// && appearing_sprite -> is_finished())
      {
        current_sprite = normal_sprite;
      }
    }



};

#endif
