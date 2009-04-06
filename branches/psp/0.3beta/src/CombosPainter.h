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
//#include <SDL/SDL_TTF.h>

class CombosPainter{

  private:

  int score;

  int mode;

  bool enabled;
  
  /**
   * Combo text sprite
   */
  SDL_Surface * sprite_single;

  /**
   * Combo text sprite
   */
  SDL_Surface * sprite_plural;

  /**
   * Combo font
   */
	// TODO : find a way to make a font
  //TTF_Font * font;

  /**
   * Combo coords
   */ 
  int sprite_x, sprite_y, score_x, score_y;

  /**
   * Actual coords
   */
  double sprite_current_x, sprite_current_y, score_current_x, score_current_y;

  unsigned long int next_time;

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
