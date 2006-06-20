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


class Game{

  // Context
  CL_DisplayWindow  * window;
  CL_GraphicContext * gc;


  // Sprites
  CL_Surface * background, *game_over;
  CL_Font *font_a;

  // Sprites
  CL_Sprite *pieces_normal[NUMBER_OF_PIECES];
  CL_Sprite *pieces_appearing[NUMBER_OF_PIECES];
  CL_Sprite *pieces_disappearing[NUMBER_OF_PIECES];
  CL_Sprite *pieces_mini[NUMBER_OF_PIECES];

  int pieces_progress_x[NUMBER_OF_PIECES-3];
  int pieces_progress_y[NUMBER_OF_PIECES-3];
  
  // TODO bidule
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
  
  // Game mode
  int game_mode;
  int global_score;
  int global_bonus;

  // Game Table
  Piece *body[NUMBER_OF_COLS][NUMBER_OF_LINES];
  
  // 4 pieces
  Piece *current_piece1, *current_piece2;
  Piece *next_piece1, *next_piece2; 
  
  // Current pieces position
  float current_pieces_center_x;
  float current_pieces_center_y;
  float current_pieces_r;
  int current_pieces_center_target;
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

  public:

  //Constructor
  Game::Game(CL_DisplayWindow *window);
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

  void Game::calc_score();
  
  
  void Game::key_events();
  void Game::new_game();
  void Game::fall();
  void Game::detect_to_destroy();
  void Game::detect_to_fall();

  void Game::stop();

};

#endif
