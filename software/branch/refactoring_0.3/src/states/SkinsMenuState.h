/********************************************************************
                          OpenAlchemist

  File : SkinsMenuState.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _SKINSMENU_STATE_H_
#define _SKINSMENU_STATE_H_

#include <ClanLib/display.h>

#include "GameState.h"
#include "../KeyboardKey.h"

class GameEngine;

class SkinsPropreties{
  public:
  std::string filename;
  u_int element; 
  CL_Surface *logo;

  SkinsPropreties()
    {
      filename = "";
      element  = 3;
      logo = NULL;
    }

  ~SkinsPropreties()
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
  int step;

  float alpha;

  CL_Sprite *background;  
  CL_Sprite *cursor;
  CL_Sprite *arrow_down;
  CL_Sprite *arrow_up;

  int arrow_down_left, arrow_down_top;
  int arrow_up_left, arrow_up_top;

  int selection_x, selection_y;

  /** Number of skins scanning in the /skins folder */
  int number_y;
  /** Current skin index */
  int current_selection;

  int y_start;

  /** Skins propreties list (read in the .openalchemist/skins file) */
  std::vector<SkinsPropreties*> propreties_list;
  SkinsPropreties **skins_board[2];

  void appear();
  void disappear();

  public:
  void init();
  void deinit();
  void load_gfx(std::string skin);
  void unload_gfx();
  void draw();
  void update();
  void events();

  void start();

  bool front_layer_behind();

  SkinsMenuState();
  ~SkinsMenuState();


};

#endif
