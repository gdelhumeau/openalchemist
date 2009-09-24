/********************************************************************
                          OpenAlchemist

  File : CombosPainter.h
  Description : Implements Combos draw functions
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _COMBOS_PAINTER_H_
#define _COMBOS_PAINTER_H_

#include <ClanLib/display.h>

class CombosPainter{

  private:

  int _score;

  int _mode;

  bool _is_enabled;
  
  /**
   * Combo text sprite
   */
  CL_Sprite _p_sprite_single;

  /**
   * Combo text sprite
   */
  CL_Sprite _p_sprite_plural;

  /**
   * Combo font
   */
  CL_Font _p_font;

  /**
   * Combo coords
   */ 
  int _sprite_x, _sprite_y, _score_x, _score_y;

  /**
   * Actual coords
   */
  double _sprite_current_x, _sprite_current_y, _score_current_x, _score_current_y;

  unsigned long int _next_time;

	float _font_height;

  public:

  CombosPainter();
  ~CombosPainter();
  void load_gfx(CL_GraphicContext &gc, std::string skin);
  void unload_gfx();
  void set_score(int score);
  void draw(CL_GraphicContext &gc);
  void update();

  private:
  void _update_appearing();
  void _update_display();
  void _update_disappearing();

};

#endif
