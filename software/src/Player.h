/********************************************************************
                          OpenAlchemist

  File : Player.h
  Description : Implements Player Class
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <ClanLib/display.h>

#include "Piece.h"
#include "Board.h"
#include "KeyboardKey.h"
#include "ProgressBar.h"

#define GAME_MODE_PLAYING 1
#define GAME_MODE_FALLING_AND_CREATING 2
#define GAME_MODE_DESTROYING 3

/**
 * Implements the player, keys events for going left, right & falling
 * and contains his board.
 */
class Player{

  protected:

  /**
   * X Position
   */
  float x;

  /**
   * Angle
   */
  float angle;  

  /**
   * Angle required (for changing)
   */
  int target_angle;

  /**
   * Current position (in cols)
   */
  int position;

  /**
   * Old position (to undo - in cols)
   */
  int old_position;

  /**
   * 1 if angle = 90 or 180
   */
  int position_bis;

  /**
   * Old position bis to undo
   */
  int old_position_bis;

  /**
   * To know if pieces are moving too the left or to the right or not
   */
  bool placed;

  /**
   * Game Mode
   */
  int game_mode;
  
  /**
   * One of the next piece (displaying in top)
   */
  Piece* next_piece1;

  /**
   * One of the next piece (displaying in top)
   */
  Piece* next_piece2;

  // TODO comment
  int next_next_piece1, next_next_piece2;

  /**
   * X Position for next items
   */
  int next_left;

  /**
   * Y Position for next items
   */
  int next_top;

  /**
   * One of the current pieces
   */
  Piece* current_piece1;

  /**
   * One of the current pieces
   */
  Piece* current_piece2;


  /**
   * Rayon of circle which contains playable pieces
   */
  int current_pieces_r;

  /** 
   * Contains the normal pieces sprites
   */
  CL_Sprite *pieces_normal[NUMBER_OF_PIECES];

  /**
   * Contains the appearing pieces sprites
   */
  CL_Sprite *pieces_appearing[NUMBER_OF_PIECES];

  /**
   * Contains the disappearing pieces sprites
   */
  CL_Sprite *pieces_disappearing[NUMBER_OF_PIECES];

  /**
   * Contains the mini pieces sprites
   */
  CL_Sprite *pieces_mini[NUMBER_OF_PIECES];

  /**
   * Contains the hidden pieces sprites
   */
  CL_Sprite *pieces_hidden[NUMBER_OF_PIECES - 3];

  /**
   * 
   */
  int pieces_progress_x[NUMBER_OF_PIECES];

  /**
   *
   */
  int pieces_progress_y[NUMBER_OF_PIECES];

  /**
   * Board game
   */
  Board board;

  /**
   * Key for playing
   */
  KeyboardKey *key_change_angle;

  /**
   * Key for playing
   */
  KeyboardKey *key_left;

  /**
   * Key for playing
   */
  KeyboardKey *key_right;

  /**
   * Key for playing
   */
  KeyboardKey *key_falling;


  /**
   * True if player press fall button
   */
  bool falling_requested;

  /**
   * Combo counter
   */
  int combo;

  /**
   * Progress Bar
   */
  ProgressBar progress_bar;

  /**
   * Undo elements
   */
  int undo_position;
  int undo_position_bis;
  int undo_piece1_number;
  int undo_piece2_number;
  float undo_angle;
  bool undo_possible;
  
  public:
  /**
   * Constructor
   */
  Player();

  /**
   * Destructor
   */
  ~Player();

  /**
   * Load GFX
   */
  void load_gfx(std::string skin);

  /**
   * Unload GFX
   */
  void unload_gfx();

  /**
   * Checking key events
   */
  void events();

  /**
   * Change angle of playable pieces
   */
  void change_angle();

  /**
   * Move playable pieces to the left
   */
  void move_left();

  /**
   * Move playable pieces to the right
   */
  void move_right();

  /**
   * Make a new party
   */
  void new_game();

  /**
   * Draw player (board and playable pieces)
   */
  void draw();

  /**
   * Update playable pieces and board
   */
  void update();

  /**
   * Update when game_mode = playing
   */
  void update_playing();

  /**
   * Update when game_mode = falling & creating
   */
  void update_falling_and_creating();

  /**
   * Update when game_mode = destroying
   */
  void update_destroying();

  /**
   * Fall playable pieces
   */
  void fall();

  /**
   * Prepare game to play (after a fall)
   */
  void prepare_to_play();

  /**
   * Undoing last action
   */
  void undo();

  /**
   * Returning if undo is available
   */
  bool is_undo_available();

  /**
   *
   */
  int get_visible_pieces();

};

#endif
