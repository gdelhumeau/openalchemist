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
};

/**
 * SkinsMenu State
 */
class SkinsMenuState : public GameState{

  private:
  int step;

  float alpha;

  CL_Sprite *background;  

  int selection;

  /** Skins filename list */
  std::vector<std::string> list;
  /** Logos of the skin list */
  std::vector<CL_Surface*> logo_list;
  /** Number of skins scanning in the /skins folder */
  int number;
  /** Current skin index */
  int current_selection;

  /** Skins propreties list (read in the .openalchemist/skins file) */
  std::vector<SkinsPropreties*> propreties_list;

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
