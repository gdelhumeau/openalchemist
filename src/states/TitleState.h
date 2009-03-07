/********************************************************************
                          OpenAlchemist

  File : TitleState.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _TITLE_STATE_H_
#define _TITLE_STATE_H_

#include <ClanLib/display.h>

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

  DemoPlayer _demo_player;

  CL_Sprite *_p_start_message;
  int _start_message_x, _start_message_y;

  CL_Sprite *_p_keydemo_left, *_p_keydemo_up, *_p_keydemo_right, *_p_keydemo_down;
  CL_Sprite *_p_keydemo_escape, *_p_keydemo_options;

  /** Help sentences **/
  CL_Sprite *_sentences_p[NUMBER_OF_SENTENCES];

  /** Help sentences coords **/
  int _sentences_x[NUMBER_OF_SENTENCES], _sentences_y[NUMBER_OF_SENTENCES];

  /** Help sentences time **/
  int _sentences_time[NUMBER_OF_SENTENCES];

  /** Keyboard demo coords **/
  int _keyleft_x, _keyleft_y, _keyup_x, _keyup_y, _keyright_x, _keyright_y,
          _keydown_x, _keydown_y;

  /** Time when will come the next step **/
  u_int _next_time;

  /** Current Step **/
  short int _step;

  bool _new_game, _fall, _change_angle, _select_the_position;

	CL_Font * _p_font;

  public:
  void init();
  void deinit();
  void load_gfx(std::string skin);
  void unload_gfx();
  void draw();
  void update();
  void events();

  bool front_layer_behind();

  TitleState();
  ~TitleState();

  void start();


};

#endif
