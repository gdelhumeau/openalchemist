/********************************************************************
                          OpenAlchemist

  File : Piece.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _PIECE_H_
#define _PIECE_H_

#include <iostream>

#include <ClanLib/display.h>

#define PIECE_SPEED 0.7

class Piece
{
  private:

  // For display:
  CL_Sprite *normal_sprite;
  CL_Sprite *appearing_sprite;
  CL_Sprite *disappearing_sprite;
  CL_Sprite *current_sprite;
  CL_Sprite *mini_sprite;

  static const int score[12];

  // For scores:
  int score_value;

  // For ...
  int piece_number;

  // Real coords on the screen
  double x, y;

  // Goal target coord
  int target_y;

    
  public:

  // Constructor
  Piece(int piece_number)
  {

    normal_sprite = NULL;
    appearing_sprite = NULL;
    disappearing_sprite = NULL;
    mini_sprite = NULL;
    current_sprite = NULL; 

    this -> piece_number = piece_number;
    this -> score_value = score[piece_number];
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
  void draw(CL_GraphicContext* context = 0)
    {
      current_sprite -> draw(x, y, context);
    }

  void draw_mini(CL_GraphicContext* context = 0)
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
  bool fall(double time_interval)
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

  void set_piece_number(int _piece_number)
    {
      piece_number = _piece_number;
      this -> score_value = score[piece_number];
    }

  int get_piece_number()
    {
      return piece_number;
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
