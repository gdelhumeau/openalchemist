/********************************************************************
                          OpenAlchemist

  File : CombosPainter.h
  Description : Implements Combos draw functions
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _COMBOS_PAINTER_H_
#define _COMBOS_PAINTER_H_

//#include <ClanLib/display.h>
#include <SDL/SDL.h>
#include <iostream>
#include "BitmapFont.h"
//#include <SDL/SDL_TTF.h>

class CombosPainter{

  private:

  int  _score;

  int  _mode;

  bool _enabled;
  
  /**
   * Combo text sprite
   */
  SDL_Surface * _sprite_single;

  /**
   * Combo text sprite
   */
  SDL_Surface * _sprite_plural;

  /**
   * Combo font
   */
  BitmapFont * _font;

  /**
   * Combo coords
   */ 
  int _sprite_x, _sprite_y, _score_x, _score_y;

  /**
   * Actual coords
   */
  double _sprite_current_x, _sprite_current_y, _score_current_x, _score_current_y;

  unsigned long int _next_time;

  public:

  CombosPainter();
  ~CombosPainter();
  void load_gfx(std::string skin);
  void unload_gfx();
  void set_score(int score);
  void draw();
  void update();

  private:
  void update_appearing();
  void update_display();
  void update_disappearing();

};

#endif
