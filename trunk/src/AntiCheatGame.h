// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : AntiCheatGame.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _ANTI_CHEAT_GAME_H_
#define _ANTI_CHEAT_GAME_H_

#include <vector>
#include "Board.h"

/** AntiCheatGame - check if recorded game is valid */
class AntiCheatGame{

public:
	void new_game();

	/** Place elements and record it. Returns false if the event is illegal. */
	bool place_elements(int piece_1, int piece_1_x, int piece_1_y,
						int piece_2, int piece_2_x, int piece_2_y);

	inline int get_piece_1() const { return _piece_1; }

	inline int get_piece_2() const { return _piece_2; }

	inline int get_next_piece_1() const { return _next_piece_1; }

	inline int get_next_piece_2() const { return _next_piece_2; }

private:

	/** Initial random seed (anti-cheat checker) */
	unsigned __int32 _initial_random_seed;

	/** Actual random seed (changes during game) */
	unsigned __int32 _random_seed;

	/** Progression - number of unlocked pieces and visible pieces */
	int _unlocked_pieces, _visible_pieces;

	/** Progression, but for undoing */
	int _undo_unlocked_pieces, _undo_visible_pieces;

	/** Score */
	unsigned int _body_score;

	/** Bonus score	*/
	unsigned int _bonus_score;

	/** Old score */
	unsigned int _undo_body_score;

	/** Old Bonus score */
	unsigned int _undo_bonus_score;

	/** Current pieces */
	int _piece_1, _piece_2;
	
	/** Next pieces */
	int _next_piece_1, _next_piece_2;

	/** Current board */
	int _board[NUMBER_OF_COLS][NUMBER_OF_LINES];

	/** Old Board game (for undoing) */
	int _undo_board[NUMBER_OF_COLS][NUMBER_OF_LINES];

	/** List of explorated pieces during "pieces to destroy" exploration */
	bool _board_mark[NUMBER_OF_COLS][NUMBER_OF_LINES];

	/** Game over state*/
	bool _game_over;

	/** Custom random number generator (be sure it's the same on all platforms) */
	int _get_next_random_int(int min, int max);

	/** Compute next random pieces */
	int _get_next_piece(){ return _get_next_random_int(0, _unlocked_pieces); }

	/** Snap the game to be able to undo */
	void _snap();

	void _place_elements(	int piece_1, int piece_1_x, int piece_1_y,
							int piece_2, int piece_2_x, int piece_2_y);

	bool _detect_pieces_to_destroy();

	void _detect_pieces_to_destroy_from(int i, int j);

	void _destroy_pieces(std::vector<Coords>& detected_pieces);

	void _create_won_piece(std::vector<Coords>& detected_pieces);

	void _choose_new_piece_coords(Coords& new_piece, std::vector<Coords>& detected_pieces);

	void _unlock_piece(Coords& new_piece);

	void _create_new_pieces();

	void _detect_pieces_to_fall();
};

#endif