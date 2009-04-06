/********************************************************************
                          OpenAlchemist

  File : TitleState.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _TITLE_STATE_H_
#define _TITLE_STATE_H_

//#include <ClanLib/display.h>
#include <SDL/SDL.h>

#include "GameState.h"
#include "../KeyboardKey.h"
#include "../DemoPlayer.h"

class GameEngine;

#define NUMBER_OF_SENTENCES 16

/**
 * Title State
 */
class TitleState : public GameState{

  private:

  DemoPlayer demo_player;

  SDL_Surface *start_message;
  int start_message_x, start_message_y;

  SDL_Surface *keydemo_left, *keydemo_up, *keydemo_right, *keydemo_down;
  SDL_Surface *keydemo_escape, *keydemo_options;

  /** Help sentences **/
  SDL_Surface *sentences[NUMBER_OF_SENTENCES];

  /** Help sentences coords **/
  int sentences_x[NUMBER_OF_SENTENCES], sentences_y[NUMBER_OF_SENTENCES];

  /** Help sentences time **/
  int sentences_time[NUMBER_OF_SENTENCES];

  /** Keyboard demo coords **/
  int keyleft_x, keyleft_y, keyup_x, keyup_y, keyright_x, keyright_y, keydown_x, keydown_y;

  /** Time when will come the next step **/
  u_int next_time;

  /** Current Step **/
  short int step;

  bool new_game, fall, change_angle, select_the_position;

  public:
  void init();
  void deinit();
  void load_gfx(std::string skin);
  void unload_gfx();
  void draw();
  void update();
  void events();

  bool front_layer_behind();

  void print();

  TitleState();
  ~TitleState();

  void start();


};

#endif
