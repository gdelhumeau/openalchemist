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
  CL_Sprite *_p_normal_sprite;
  CL_Sprite *_p_appearing_sprite;
  CL_Sprite *_p_disappearing_sprite;
  CL_Sprite *_p_current_sprite;
  CL_Sprite *_p_mini_sprite;

  static const int _score[12];

  // For scores:
  int _score_value;

  // For ...
  int _piece_number;

  // Real coords on the screen
  double _x, _y;

  // Goal target coord
  int _target_y;

    
  public:

  // Constructor
  Piece(int piece_number)
  {

    _p_normal_sprite = NULL;
    _p_appearing_sprite = NULL;
    _p_disappearing_sprite = NULL;
    _p_mini_sprite = NULL;
    _p_current_sprite = NULL; 

    this -> _piece_number = piece_number;
    this -> _score_value = _score[piece_number];
    _x = 0.0;
    _y = 0.0;
    _target_y = 0;      
  }
  
  // Method to set the sprites
  void set_sprites(CL_Sprite *normal, CL_Sprite *appearing, CL_Sprite *disappearing, CL_Sprite *mini)
  {
    _p_normal_sprite = normal;
    _p_appearing_sprite = appearing;
    _p_disappearing_sprite = disappearing;
    _p_mini_sprite = mini;
    _p_current_sprite = _p_normal_sprite;
  }
 
  // Methods to display - be carefull, if current_prite is not initialized
  void draw(CL_GraphicContext* context = 0)
    {
      _p_current_sprite -> draw(_x, _y, context);
    }

  void draw_mini(CL_GraphicContext* context = 0)
    {
      _p_mini_sprite -> draw(_x, _y, context); 
    }

  void start_appear()
    {
      _p_appearing_sprite -> set_play_loop(false);
      _p_current_sprite = _p_appearing_sprite;
      _p_current_sprite -> restart();      
    }

  void start_disappear()
    {
      _p_disappearing_sprite -> set_play_loop(false);
      _p_current_sprite = _p_disappearing_sprite;
      _p_current_sprite -> restart();
    }

  void start_fall(int target_x, int target_y)
    {
      this -> _target_y = target_y;
      _x = target_x;
    }

  void set_normal()
    {
      _p_current_sprite = _p_normal_sprite;
    }

 // Return true if the piece is appeared
  bool appear()
    {
      _p_appearing_sprite -> update();
      if(_p_appearing_sprite -> is_finished())
      {
        _p_current_sprite = _p_normal_sprite;
        return true;
      }
   
      return false;
    }

  // Return true if the piece is disappeared
  bool disappear()
    {
      _p_disappearing_sprite -> update();
      if(_p_disappearing_sprite -> is_finished())
      {
        _p_current_sprite = _p_normal_sprite;
        return true;
      }
      return false;


    }


  // Return true if the piece is placed
  bool fall(double time_interval)
    {
      _y += PIECE_SPEED * time_interval;
      if(_y >= _target_y)
      {
        _y = _target_y;
        return true;
      }

      return false;
    }
    
  void set_score_value(int _score_value)
    {
      _score_value = _score_value; 
    }

  int get_score_value()
    {
      return _score_value;
    }

  void set_piece_number(int piece_number)
    {
      _piece_number = piece_number;
      this -> _score_value = _score[_piece_number];
    }

  int get_piece_number()
    {
      return _piece_number;
    }

  // Setters
  void set_x(float x)
    {
      this -> _x = x;
    }

  void set_y(float y)
    {
      this -> _y = y;
    }

  void set_position(float x, float y)
  {
    this -> _x = x;
    this -> _y = y;
  }
  
  //Getters
  float get_x()
  {
    return _x;
  }
  
  float get_y()
  {
    return _y;
  }

  void print()
    {
      std::cout << "-----\nnormal_sprite: " << _p_normal_sprite << "\n"
        << "appearing_sprite: " << _p_appearing_sprite << "\n"
                << "disappearing_spirte: " << _p_disappearing_sprite << "\n"
                << "current_sprite: " << _p_current_sprite << "\n";
      if(_p_current_sprite == _p_appearing_sprite)// && appearing_sprite -> is_finished())
      {
        _p_current_sprite = _p_normal_sprite;
      }
    }



};


#endif
