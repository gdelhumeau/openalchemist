/********************************************************************
                          OpenAlchemist

  File : CommonResources.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _COMMON_RESOURCES_H_
#define _COMMON_RESOURCES_H_

//#include <ClanLib/display.h>

#include <pspctrl.h>
//#include <psptypes.h>
//#include <pspkernel.h>
//#include <png.h>

#include "Board.h"
#include "HumanPlayer.h"
#include "DemoPlayer.h"
#include "FrontLayer.h"
#include "Keys.h"
#include "BitmapFont.h"

#define NUMBER_OF_DIFFICULTIES 3

class GameEngine;

class CommonResources{

  public:
  GameEngine *engine;

  BitmapFont *main_font;

  int score;

  HumanPlayer player1;
  Player *current_player;

  FrontLayer front_layer;

  Keys key;

  int CurrentKeyPressed;

  std::string skin;

  /** Sprites */
  int pieces_width, pieces_height;

  double time_interval;
  int fps;

  u_int highscore;
  u_int old_highscore;


  void init(GameEngine *engine);
  void load_gfx(std::string skin);
  void unload_gfx();

  void read_scores();
  void save_scores();

  CommonResources();
  ~CommonResources();

};

CommonResources* common_resources_get_instance();

#endif
