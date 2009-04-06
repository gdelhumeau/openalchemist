/********************************************************************
                          OpenAlchemist

  File : GameOverState.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _GAMEOVER_STATE_H_
#define _GAMEOVER_STATE_H_

//#include <ClanLib/display.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "GameState.h"
#include "../KeyboardKey.h"

#define MODE_GAMEOVER 1
#define MODE_HIGHSCORE 2

#define GAMEOVER_SELECTION_YES 1
#define GAMEOVER_SELECTION_NO 2

class GameEngine;


/**
 * InGame State
 */
class GameOverState : public GameState{

  private:

  SDL_Surface * dialog, * dialog_gameover, * dialog_highscore;
  int dialog_x, dialog_y;
  int score1_x;
  int score1_y;
  int score2_x;
  int score2_y;

  SDL_Surface * yes_selected, *yes_unselected;
  SDL_Surface * no_selected, *no_unselected;
  int yes_x, yes_y;
  int no_x, no_y;

  int mode;
  int selection;

  public:
  void init();
  void deinit();
  void load_gfx(std::string skin);
  void unload_gfx();
  void draw();
  void update();
  void events();

  bool front_layer_behind();

  void set_mode(int mode);
  void start();

  void print();

  GameOverState();
  ~GameOverState();


};

#endif
