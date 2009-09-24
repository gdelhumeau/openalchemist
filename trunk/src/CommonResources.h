/********************************************************************
                          OpenAlchemist

  File : CommonResources.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _COMMON_RESOURCES_H_
#define _COMMON_RESOURCES_H_

#include <ClanLib/display.h>

#include "Board.h"
#include "HumanPlayer.h"
#include "DemoPlayer.h"
#include "FrontLayer.h"
#include "Keys.h"

#define NUMBER_OF_DIFFICULTIES 3

class GameEngine;

class CommonResources{

  public:
  GameEngine *p_engine;
  CL_Font main_font;
	CL_GraphicContext * p_gc;
	CL_DisplayWindow * p_window;

  int score;

  HumanPlayer player1;
  Player *p_current_player;

  FrontLayer front_layer;

  Keys key;

  std::string skin;

  /** Sprites */
  int pieces_width, pieces_height;

  double time_interval;
  int fps;

  unsigned int highscore;
  unsigned int old_highscore;


  void init(GameEngine *p_engine);
  void load_gfx(CL_GraphicContext &gc, std::string skin);
  void unload_gfx();

  void read_scores();
  void save_scores();

  CommonResources();
  ~CommonResources();

};

void common_resources_init();
void common_resources_term();
CommonResources* common_resources_get_instance();

#endif
