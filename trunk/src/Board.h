/********************************************************************
                          OpenAlchemist

  File : Board.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <list>

#include "Piece.h"
#include "Coords.h"

#define NUMBER_OF_PIECES 12
#define NUMBER_OF_COLS 6
#define NUMBER_OF_LINES 9

/**
 * This class contains board game
 */
class Board{

  /**
   * Board game
   */
  Piece *_p_board[NUMBER_OF_COLS][NUMBER_OF_LINES];

  /**
   * Old Board game (for undoing)
   */
  int _undo_board[NUMBER_OF_COLS][NUMBER_OF_LINES];

  /**
   * List of pieces which are falling
   */
  std::vector<Piece*> _falling_list;

  /**
   * List of pieces we have to destroy (only coords)
   */
  std::vector<Coords*> _list_to_destroy;

  /**
   * List of pieces which are appearing
   */
  std::list<Piece*> _appearing_list;

  /**
   * List of pieces we have to create (only coords)
   */
  std::list<Coords*> _list_to_create;

	/**
	 * List of explorated pieces during "pieces to destroy" exploration
	 */
	bool _board_mark[NUMBER_OF_COLS][NUMBER_OF_LINES];

  public:

  /**
   * Game Position
   */
  int game_top, game_left, zone_top;

  /**
   * Progression - number of unlocked pieces and visible pieces
   */
  int unlocked_pieces, visible_pieces;
  
  /**
   * Progression, but for undoing
   */
  int undo_unlocked_pieces, undo_visible_pieces;

  /**
   * Score
   */
  u_int score;

  /**
   * Bonus score
   */
  u_int bonus_score;

  /**
   * Old score
   */
  u_int undo_score;

  /**
   * Old Bonus score
   */
  u_int undo_bonus_score;

  /**
   * Score in string format
   */
  std::string str_score;

  /**
   * Bonus score in string format
   */
  std::string str_bonus;

  /**
   * Hight score in string format
   */
  std::string str_hightscore;

  /**
   * Score coords
   */
  int score_left, score_right, score_top, bonus_left, bonus_right, bonus_top,
    hightscore_left, hightscore_right, hightscore_top;


  /** 
   * Constructor
   */
  Board();

  /**
   * Destructor
   */
  ~Board();

  /**
   * Clearing the board (my_delete all elements)
   */
  void clear();

  /**
   * Applying current to the board by giving sprites references
   */
  void apply_skin(CL_Sprite **pieces_normal, CL_Sprite** pieces_appearing, CL_Sprite** pieces_disappearing, CL_Sprite** pieces_mini);

  /**
   * Drawing the board
   */
  void draw();

  /**
   * Adding pieces to the game board - making them fall
   */
  void add_pieces(Piece* piece1, Piece* piece2);


  /**
   * Making pieces fall and create my_new ones
   * @return true if every pieces are corectly placed
   */
  bool fall_and_create();

  /**
   * Look if there is pieces to destroy
   * @return true if there is pieces to destroy
   */
  bool detect_pieces_to_destroy();

	private:

	/**
	 * Detect pieces to destroy from (x,y) coords
	 */
	void _detect_pieces_to_destroy_from(int x, int y);
	
	/**
	 * Function called when pieces to destoyes are detected
	 */
	void _pieces_to_destroy_detected(std::vector<Coords*> &detected_pieces);

	/**
	 * Funcion called when we want to create a my_new piece from thoses
	 * we have destroyed
	 */
	void _create_new_piece(std::vector<Coords*> &detected_pieces);	

	/**
	 * Choose the my_new piece coords
	 */
	void _choose_new_piece_coords(Coords &new_piece, std::vector<Coords*> &detected_pieces);	

	/**
	 * Check if we have unlocked a piece with the my_new one
	 */
	void _unlock_piece(Coords &new_piece);

	public:

  /**
   * Destroying pieces
   * @return true if pieces are deleted
   */
  bool destroy();

  /**
   * Creating my_new pieces - sprites are needed for this operation
   */
  void create_new_pieces(CL_Sprite **pieces_normal, CL_Sprite **pieces_appearing, CL_Sprite **pieces_disappearing,
                         CL_Sprite **pieces_mini);

  /**
   * Detecting pieces which have to fall
   */
  void detect_pieces_to_fall();


  /**
   * Detecting if pieces are upside the limit, so if game is over
   */
  bool is_game_over();

  /**
   * Calculating score
   */
  void calc_score();

  /**
   * Undoing last action
   */
  void undo(CL_Sprite **pieces_normal, CL_Sprite** pieces_appearing, CL_Sprite** pieces_disappearing, CL_Sprite** pieces_mini);

};

#endif
