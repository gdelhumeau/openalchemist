/* OpenAlchemist - just a simple game 
 * ----------------------------------
 *
 * Copyright (C) 2005, 2006 Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef _GAME_H_
#define _GAME_H_

#define NUMBER_OF_PIECES 12
#define NUMBER_OF_COLS 6
#define NUMBER_OF_LINES 9

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <vector>
#include <list>
#include "piece.h"
#include "gfx_misc.h"
#include "KeyboardKey.h"
#include "key.h"
#include "coords.h"
#include "pieces.h"
#include "skins_selector.h"
#include "pause.h"
#include "undo.h"
#include "progress_bar.h"
#include "frontlayer.h"


#define GAME_MODE_TO_PLAYING 0
#define GAME_MODE_PLAYING 1
#define GAME_MODE_FALLING_AND_CREATING 2
#define GAME_MODE_DETECTING_WHAT_DESTROY 3
#define GAME_MODE_DESTROYING 4
#define GAME_MODE_DETECTING_WHAT_FALL 5
#define GAME_MODE_GAME_OVER 6
#define GAME_MODE_NEW_HIGHTSCORE 7

#define PAUSE_STEP_APPEARING 1
#define PAUSE_STEP_MENU 2
#define PAUSE_STEP_SKINS 3
#define PAUSE_STEP_DISAPPEARING 4

#define NUMBER_OF_DIFFICULTIES 3

/**
 * This is the main class witch contains all the game
 */
class Game{

  // Context
  
  /** Window of the game */
  CL_DisplayWindow  * window;
  
  /** True if OpenGL is used, false is it's SDL */
  bool opengl;

  // Skin
  std::string skin;

  // Gfx Misc
  GfxMisc gfx_misc;

  // Pieces Sprites
  Pieces pieces;

  // Progress Bar
  ProgressBar progress_bar;
  
  // Skins selector
  SkinsSelector skins_selector;
  
  // Pause
  Pause pause;

  // Keys
  Key key;

  // UNDO
  Undo undo;

  // FrontLayer
  FrontLayer front_layer;

  // Sounds
  int sound_level, music_level;

    
  // Available pieces
  int unlocked_pieces;
  int visible_pieces;
  
  bool is_gfx_loaded;
  bool falling_requested;


  int fps;
  int combo;

  u_int hightscores[NUMBER_OF_DIFFICULTIES];
  
  // Game mode
  int game_mode;
  short current_difficulty;

  // Score
  u_int global_score;
  u_int global_bonus;
  u_int last_hightscore;
  // The same in string format
  std::string str_score;
  std::string str_bonus;
  std::string str_hightscore;
  // Displaying...
  int score_left;
  int bonus_left;
  int hightscore_left;


  // Game Table
  Piece *body[NUMBER_OF_COLS][NUMBER_OF_LINES];

  
  // 4 pieces
  Piece *current_piece1, *current_piece2;
  Piece *next_piece1, *next_piece2; 
  
  // Current pieces position
  int position;
  int old_position;
  short position_bis;
  short old_position_bis;

  float position_x;

  float current_pieces_r;
  float current_pieces_angle;
  int current_pieces_next_angle;
  bool current_pieces_placed;
  bool end;

  // List of the falling pieces
  std::vector<Piece*> falling_list;
  std::vector<Coords*> list_to_destroy;
  std::list<Piece*> appearing_list;
  std::list<Coords*> list_to_create;
  
  float time_interval;
 
  public:

  //Constructor
  Game(CL_DisplayWindow *window, bool opengl);
  //Destructor
  ~Game();

  // Some methods
  void choose_skin();
  void load_gfx();
  void unload_gfx();
  void toggle_screen();
  void main_loop();
  void calc_score();
  void apply_skin();

  // Methods to draw the game
  void draw_game();  
  void draw_playing();
  void draw_falling();
  void draw_destroying();
  void draw_to_playing();
  void draw_game_over();
  void draw_new_hightscore();
  void draw_pause();  
  void draw_progress_bar();
  void draw_skins_selector();

  // Methods...
  void load_preferences();
  void save_preferences();
  void read_scores();
  void save_scores();
  void key_events();
  void key_events_playing();
  void key_events_pause();
  void key_events_skins_selector();
  void undo_last();
  void new_game(short difficulty);
  void fall();
  void detect_to_destroy();
  void detect_to_fall();

  void stop();

};

#endif
