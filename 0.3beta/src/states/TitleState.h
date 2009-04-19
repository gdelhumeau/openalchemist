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
#define NUMBER_OF_KEYS       7
#define NUMBER_OF_PIC_BLINK  2
#define BLINK_REMANENCE     50

#define LEFT                 0
#define UP                   1
#define RIGHT                2
#define DOWN                 3
#define ESCAPE               4
#define OPTIONS              5
#define ROTATE               6



/**
 * Title State
 */
class TitleState : public GameState{

  private:

  DemoPlayer demo_player;

  SDL_Surface *start_message;
 // int start_message_x, start_message_y;


  /** Picture for keys, contain two clip to blink **/
  //SDL_Surface *keydemo_left;
  //SDL_Surface *keydemo_up;
  //SDL_Surface *keydemo_right;
  //SDL_Surface *keydemo_down;
  //SDL_Surface *keydemo_escape;
  //SDL_Surface *keydemo_options;

  SDL_Surface *keydemo[NUMBER_OF_KEYS];

  /** SDL coords to split picture in clip for blinking **/
  // we assume here that all the pics representing keys are same size
  SDL_Rect keydemo_tab_clips[NUMBER_OF_PIC_BLINK][NUMBER_OF_KEYS];

  int blinking_steps, blink_clip;

  /** Help sentences **/
  SDL_Surface *sentences[NUMBER_OF_SENTENCES];

  /** Help sentences coords **/
  int sentences_x[NUMBER_OF_SENTENCES], sentences_y[NUMBER_OF_SENTENCES];

  /** Help sentences time **/
  int sentences_time[NUMBER_OF_SENTENCES];

  /** Keyboard demo coords **/
  int arrow_key_x, arrow_key_y;
  int round_key_x, round_key_y;

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
