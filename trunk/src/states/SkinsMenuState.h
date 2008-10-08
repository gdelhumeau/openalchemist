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
        delete logo;
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
  int step;

  /**
   * Alpha blending
   */
  float alpha;

  /**
   * Menu background
   */
  CL_Sprite *background;  

  /**
   * Unavaible skin logo
   */
  CL_Surface *logo_unavailable;

  /**
   * Cursor
   */
  CL_Sprite *cursor;

  /**
   * Arrow Up (displayed when skin list is more long than a screen)
   */
  CL_Sprite *arrow_down;

  /**
   * Arrow down
   */
  CL_Sprite *arrow_up;

  /**
   * Arrows coords
   */
  int arrow_down_left, arrow_down_top;
  int arrow_up_left, arrow_up_top;

  /**
   * Selection coords
   */
  int selection_x, selection_y;

  /**
   * Number of lines in the skins board 
   */
  int number_y;

  /**
   * Start for drawing in the sin board (scroll)
   */
  int y_start;

  /**
   * Skins preview coords
   */
  int skins_preview_x;
  int skins_preview_y;
  int skins_preview_width;
  int skins_preview_height;

  /**
   * Skins preview cursor coords
   */
  int cursor_x;
  int cursor_y;
  int cursor_width;
  int cursor_height;

  /**
   * Skins skins list (read in the .openalchemist/skins file) 
   */
  std::vector<Skin*> skins_list;

  /**
   * Skins board. Board which contains skins to draw in the menu
   */
  Skin **skins_board[2];

  /**
   * Makes menu appear
   */
  void appear();

  /**
   * Makes menu disappear
   */
  void disappear();

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
