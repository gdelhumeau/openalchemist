/********************************************************************
                          OpenAlchemist

  File : SkinsMenuState.h
  Description : Skins Menu Implementation
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _SKINSMENU_STATE_H_
#define _SKINSMENU_STATE_H_

#include <ClanLib/display.h>

#include "GameState.h"

class GameEngine;

/**
 * Skin class
 */
class Skin{
  public:

  /**
   * Skin filename
   */
  std::string filename;

  /**
   * Unlocked elements
   */
  u_int element; 

  /**
   * Skin logo presentation
   */
  CL_Surface *logo;

  /**
   * Constructor
   */
  Skin()
    {
      filename = "";
      element  = 3;
      logo = NULL;
    }

  /**
   * Destructor
   */
  ~Skin()
    {
      if(logo)
        my_delete(logo);
    }
};

/**
 * SkinsMenu State
 */
class SkinsMenuState : public GameState{

  private:

  /**
   * Step (Normal, Appearing, Disappearing)
   */
  int _step;

  /**
   * Alpha blending
   */
  float _alpha;

  /**
   * Menu background
   */
  CL_Sprite *_p_background;  

  /**
   * Unavaible skin logo
   */
  CL_Surface *_p_logo_unavailable;

  /**
   * Cursor
   */
  CL_Sprite *_p_cursor;

  /**
   * Arrow Up (displayed when skin list is more long than a screen)
   */
  CL_Sprite *_p_arrow_down;

  /**
   * Arrow down
   */
  CL_Sprite *_p_arrow_up;

  /**
   * Arrows coords
   */
  int _arrow_down_left, _arrow_down_top;
  int _arrow_up_left, _arrow_up_top;

  /**
   * Selection coords
   */
  int _selection_x, _selection_y;

  /**
   * Number of lines in the skins board 
   */
  int _number_y;

  /**
   * Start for drawing in the sin board (scroll)
   */
  int _y_start;

  /**
   * Skins preview coords
   */
  int _skins_preview_x;
  int _skins_preview_y;
  int _skins_preview_width;
  int _skins_preview_height;

  /**
   * Skins preview cursor coords
   */
  int _cursor_x;
  int _cursor_y;
  int _cursor_width;
  int _cursor_height;

  /**
   * Skins skins list (read in the .openalchemist/skins file) 
   */
  std::vector<Skin*> _skins_list;

  /**
   * Skins board. Board which contains skins to draw in the menu
   */
  Skin **skins_board[2];

  /**
   * Makes menu appear
   */
  void _appear();

  /**
   * Makes menu disappear
   */
  void _disappear();

  public:
  void init();
  void deinit();
  void load_gfx(std::string skin);
  void unload_gfx();
  void draw();
  void update();
  void events();

  /**
   * Starts appear
   */
  void start();

  bool front_layer_behind();

  void set_skin_elements(u_int element);

  SkinsMenuState();
  ~SkinsMenuState();


};

#endif
