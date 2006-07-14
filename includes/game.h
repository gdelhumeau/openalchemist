/* OpenAlchemist - just a simple game 
 * ----------------------------------
 *
 * Copyright (C) 2005 Guillaume Delhumeau <guillaume.delhumeau at laposte.net>
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
#include "KeyboardKey.h"
#include "coords.h"

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
#define PAUSE_STEP_DISAPPEARING 3

#define NUMBER_OF_DIFFICULTIES 3

/**
 * This is the main class witch contains all the game
 */
class Game{

  // Context
  CL_DisplayWindow  * window;
  CL_GraphicContext * gc;
  bool opengl;

  // Sprites
  CL_Surface * background, *game_over;
  CL_Font *font_a;

  // Sprites
  CL_Sprite *pieces_normal[NUMBER_OF_PIECES];
  CL_Sprite *pieces_appearing[NUMBER_OF_PIECES];
  CL_Sprite *pieces_disappearing[NUMBER_OF_PIECES];
  CL_Sprite *pieces_mini[NUMBER_OF_PIECES];
  CL_Sprite *pieces_hidder[NUMBER_OF_PIECES-3];

  // Sprites for pause
  CL_Sprite *pause_background;
  CL_Sprite *pause_resume, *pause_resume_selected;
  CL_Sprite *pause_undo, *pause_undo_selected, *pause_undo_unavailable;
  CL_Sprite *pause_retry, *pause_retry_selected;
  CL_Sprite *pause_changeskin, *pause_changeskin_selected;
  CL_Sprite *pause_fullscreen, *pause_fullscreen_selected;
  CL_Sprite *pause_sound, *pause_sound_selected;
  CL_Sprite *pause_music, *pause_music_selected;
  CL_Sprite *pause_backmain, *pause_backmain_selected;
  CL_Sprite *pause_quit, *pause_quit_selected;
  
  CL_Sprite *pause_sound_level[11];

  // Sprites for progress bar
  CL_Sprite *progress_bar[10];
  int progress_bar_left, progress_bar_top;
  
  // Pause
  bool pause;
  bool pause_appearing;

  int pause_step;
  int pause_selection;
  float pause_alpha, pause_max_alpha;

  int pause_resume_left, pause_resume_top;
  int pause_retry_left, pause_retry_top;
  int pause_undo_left, pause_undo_top;
  int pause_changeskin_left, pause_changeskin_top;
  int pause_fullscreen_left, pause_fullscreen_top;
  int pause_sound_left, pause_sound_top;
  int pause_music_left, pause_music_top;
  int pause_backmain_left, pause_backmain_top;
  int pause_quit_left, pause_quit_top;
  int pause_sound_level_left;

  int pieces_progress_x[NUMBER_OF_PIECES];
  int pieces_progress_y[NUMBER_OF_PIECES];

  // Sounds
  int sound_level, music_level;


  // Menus
  CL_Sprite *new_hightscore;
  int new_score_top, old_score_top;
  
  // Available pieces
  int unlocked_pieces;
  int visible_pieces;
  
  std::string skin;
  bool is_gfx_loaded;
  
  bool falling_requested;


  int fps;

  int game_top, game_left, zone_top, next_top, next_left;
  int pieces_width, pieces_height;
  int score_top, score_left;
  int bonus_top, bonus_left;
  int hightscore_top, hightscore_left;
  int combo;

  u_int hightscores[NUMBER_OF_DIFFICULTIES];
  
  // Game mode
  int game_mode;
  short current_difficulty;

  // Score
  u_int global_score;
  u_int global_bonus;
  u_int undo_global_bonus;
  u_int last_hightscore;

  // Game Table
  Piece *body[NUMBER_OF_COLS][NUMBER_OF_LINES];

  // UNDO
  int body_undo[NUMBER_OF_COLS][NUMBER_OF_LINES];
  int undo_position, undo_angle, undo_position_bis;
  int undo_piece1_score, undo_piece2_score;
  int undo_next_next_piece1, undo_next_next_piece2;
  bool undo;
  int undo_unlocked_pieces;
  int undo_visible_pieces;
  
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
 
  // Keys
  KeyboardKey * key_fullscreen;
  KeyboardKey * key_change_angle;
  KeyboardKey * key_left;
  KeyboardKey * key_right;
  KeyboardKey * key_falling;
  KeyboardKey * key_retry;
  KeyboardKey * key_undo;
  KeyboardKey * key_echap;
  KeyboardKey * key_up;
  KeyboardKey * key_down;
  KeyboardKey * key_enter;

  public:

  //Constructor
  Game::Game(CL_DisplayWindow *window, bool opengl);
  //Destructor
  Game::~Game();

  // Some methods
  void Game::choose_skin();
  void Game::load_gfx();
  void Game::unload_gfx();
  void Game::toggle_screen();
  void Game::main_loop();

  // Methods to draw the game
  void Game::draw_game();  
  void Game::draw_playing();
  void Game::draw_falling();
  void Game::draw_destroying();
  void Game::draw_to_playing();
  void Game::draw_game_over();
  void Game::draw_new_hightscore();
  void Game::draw_pause();

  void Game::calc_score();
 
  void Game::load_preferences();
  void Game::save_preferences();
  void Game::read_scores();
  void Game::save_scores();
  void Game::key_events();
  void Game::key_events_playing();
  void Game::key_events_pause();
  void Game::undo_last();
  void Game::new_game(short difficulty);
  void Game::fall();
  void Game::detect_to_destroy();
  void Game::detect_to_fall();

  void Game::stop();

};

#endif
