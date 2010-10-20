// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : AntiCheatGame.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include <ClanLib/core.h>
#include <iostream>
#include <stack>
#include "AntiCheatGame.h"
#include "CommonResources.h"
//#include "GameEngine.h"

/************************************************************************/
/* Constants                                                            */
/************************************************************************/
static const int NO_PIECE = -1;

/************************************************************************/
/* New Game                                                             */
/************************************************************************/
void AntiCheatGame::new_game()
{
	_initial_random_seed = CL_System::get_time();
	_random_seed = _initial_random_seed;
	_unlocked_pieces = 3;
	_game_over = false;
	// Init the board
	for(int i_col=0; i_col<NUMBER_OF_COLS; ++i_col)	
		for(int i_line=0; i_line<NUMBER_OF_LINES; ++i_line)
			_board[i_col][i_line]=NO_PIECE;	
	// Init next pieces
	_piece_1 = _get_next_piece();
	_piece_2 = _get_next_piece();
	_next_piece_1 = _get_next_piece();
	_next_piece_2 = _get_next_piece();
}

/************************************************************************/
/* Next integer                                                         */
/************************************************************************/
int AntiCheatGame::_get_next_random_int(int min, int max)
{
	// Change random seed
	_random_seed = _random_seed * 214013L + 2531011L;
	// Compute random number
	int rand = (_random_seed >> 16) & 0x7fff;
	// Apply range
	return min + rand % (max - min);
}

/************************************************************************/
/* Place elements                                                       */
/************************************************************************/
bool AntiCheatGame::place_elements(	int piece_1, int piece_1_x, int piece_1_y,
							int piece_2, int piece_2_x, int piece_2_y)
{
	// Anti cheat verification (are pieces correct ?)
	if(!((piece_1 == _piece_1 && piece_2 == _piece_2) || (piece_2 == _piece_1 && piece_1 == _piece_2)))
		return false;

	// Second anti cheat verification (are pieces well placed in x ?)
	if(!(abs(piece_1_x - piece_2_x) <= 1))
		return false;

	// Snap current state for undo
	_snap();

	// Place elements
	_place_elements(piece_1, piece_1_x, piece_1_y, piece_2, piece_2_x, piece_2_y);

	// Compute next pieces
	_piece_1 = _next_piece_1;
	_piece_2 = _next_piece_2;
	_next_piece_1 = _get_next_piece();
	_next_piece_2 = _get_next_piece();

	return true;
}

/************************************************************************/
/* Snap                                                                 */
/************************************************************************/
void AntiCheatGame::_snap()
{
	// Saving old score
	_undo_body_score = _body_score;
	_undo_bonus_score = _bonus_score;	

	// Saving old progression
	_undo_unlocked_pieces = _unlocked_pieces;
	_undo_visible_pieces = _visible_pieces;

	// Saving board state
	for (int x = 0; x < NUMBER_OF_COLS; ++x)
		for (int y = 0; y < NUMBER_OF_LINES; ++y)		
			_undo_board[x][y] = _board[x][y];	
}

/************************************************************************/
/* Place elements                                                       */
/************************************************************************/
void AntiCheatGame::_place_elements(	int piece_1, int piece_1_x, int piece_1_y,
							int piece_2, int piece_2_x, int piece_2_y)
{
	// Compute which piece is top and which is bottom
	int piece_on_top;
	int piece_on_bottom;
	int piece_top_x;
	int piece_bottom_x;
	if (piece_1_y <= piece_2_y)
	{
		piece_on_top = piece_1;
		piece_on_bottom = piece_2;
		piece_top_x = piece_1_x;
		piece_bottom_x = piece_2_x;
	}
	else
	{
		piece_on_top = piece_2;
		piece_on_bottom = piece_1;
		piece_top_x = piece_2_x;
		piece_bottom_x = piece_1_x;
	}

	// Compute y position for piece on bottom
	int y_bottom = -1;
	while (y_bottom < NUMBER_OF_LINES - 1 && _board[piece_bottom_x][y_bottom + 1]<0)
		++y_bottom;	

	if (y_bottom == -1 && _board[piece_bottom_x][0]>=0)
		_game_over = true;
	else
		_board[piece_bottom_x][y_bottom] = piece_on_bottom;

	// Compute y position for piece on top
	int y_top = -1;
	while (y_top < NUMBER_OF_LINES - 1 && _board[piece_top_x][y_top + 1]<0)
		++y_top;

	if (y_top == -1 && _board[piece_top_x][0]>=0)
	{
		_game_over = true;
		_board[piece_bottom_x][y_bottom] = NO_PIECE;
	}
	else
	{
		_board[piece_top_x][y_top] = piece_on_top;
	}

	_detect_pieces_to_destroy();
}

/************************************************************************/
/* Detect pieces to destroy                                             */
/************************************************************************/
bool AntiCheatGame::_detect_pieces_to_destroy()
{
	// This table is used to know if a piece have been explorated 
	for (int k = 0; k < NUMBER_OF_COLS; ++k)
		for (int l = 0; l < NUMBER_OF_LINES; ++l)
			_board_mark[k][l] = false;

	// We will look from all pieces in the table
	for (int x = 0; x < NUMBER_OF_COLS; ++x)
		for (int y = 0; y < NUMBER_OF_LINES; ++y)
		{
			_detect_pieces_to_destroy_from(x, y);
		}

	// if the list_to_destroy is not empty, then we have detected some pieces
	return true/*!_list_to_destroy.empty()*/;
}

/************************************************************************/
/* Detect pieces to destroy from coords                                 */
/************************************************************************/
void AntiCheatGame::_detect_pieces_to_destroy_from(int i, int j)
{
	if (_board[i][j]>=0 && !_board_mark[i][j])
	{
		int counter = 0;
		int root_number = _board[i][j];

		// Detected pieces to be destroyed
		std::vector<Coords> detected_pieces;

		// Stack to explore the board
		std::stack<Coords> stack;
		stack.push(Coords(i, j));

		// while we have coordinates to explore
		while (!stack.empty())
		{
			// Getting top coords
			Coords c = stack.top();
			int x = c.x;
			int y = c.y;
			stack.pop();

			if (x >= 0 && x < NUMBER_OF_COLS && y >= 0 && y < NUMBER_OF_LINES
				&& _board[x][y] >= 0)
			{
				// We look if this piece is the same as the reference
				if (!_board_mark[x][y] && _board[x][y] == root_number)
				{
					// We add this pieces to the detected_pieces list
					detected_pieces.insert(detected_pieces.end(), Coords(x, y));
					_board_mark[x][y] = true;
					counter++;

					// We will explore neighboors
					stack.push(Coords(x - 1, y));
					stack.push(Coords(x + 1, y));
					stack.push(Coords(x, y - 1));
					stack.push(Coords(x, y + 1));
				}
			}
		}

		if (counter >= 3)
			_destroy_pieces(detected_pieces);
		else
			detected_pieces.clear();					
	}
}

/************************************************************************/
/* Pieces to destroys are detected                                      */
/************************************************************************/
void AntiCheatGame::_destroy_pieces(std::vector<Coords>& detected_pieces)
{
	Coords c = detected_pieces[0];
	unsigned int piece_number = _board[c.x][c.y];

	int counter = (int) detected_pieces.size();

	// if we aligned the last element
	if (piece_number == NUMBER_OF_PIECES - 1)
	{
		std::cout << "You align " << counter << " ultimate elements ! Cheater :p" << std::endl;
		_bonus_score += counter * _board[c.x][c.y]/*->get_score_value()*/;
	}
	// If it was not last element
	else
	{
		_bonus_score += (counter - 3) * _board[c.x][c.y]/*->get_score_value()*/;
	}
	
	_create_won_piece(detected_pieces);
}

/************************************************************************/
/* Create new piece (after a destruction                                */
/************************************************************************/
void AntiCheatGame::_create_won_piece(std::vector<Coords>& detected_pieces)
{
	// Determining the new piece coords
	Coords new_piece(NUMBER_OF_COLS + 1, -1);
	_choose_new_piece_coords(new_piece, detected_pieces);

	// Determining the new piece number
	new_piece.piece_number =
		_board[detected_pieces[0].x][detected_pieces[0].y] + 1;
	if (new_piece.piece_number >= NUMBER_OF_PIECES)
	{
		new_piece.piece_number = NUMBER_OF_PIECES - 1;
	}

	// Maybe we have unlocked new element ?
	_unlock_piece(new_piece);

	// We add the new piece except if we have aligned 3 last elements
	if (new_piece.piece_number != NUMBER_OF_PIECES - 1){
		_board[new_piece.x][new_piece.y]=new_piece.piece_number;
		_detect_pieces_to_destroy_from(new_piece.x, new_piece.y);
	}
}

/************************************************************************/
/* Choose new piece coord                                               */
/************************************************************************/
void AntiCheatGame::_choose_new_piece_coords(Coords& new_piece, std::vector<Coords>& detected_pieces)
{
	for (std::vector<Coords>::iterator it = detected_pieces.begin(); it != detected_pieces.end(); ++it)
	{
		Coords c = (Coords) *it;
		_board[c.x][c.y] = NO_PIECE; // delete old piece
		
		// Select the lefter and bottomer Coords for create my_new piece
		if (c.y > new_piece.y)
		{
			new_piece.x = c.x;
			new_piece.y = c.y;
		}
		else if (c.y == new_piece.y && c.x < new_piece.x)
		{
			new_piece.x = c.x;
			new_piece.y = c.y;	
		}
	}
}

/************************************************************************/
/* Unlock piece                                                         */
/************************************************************************/
void AntiCheatGame::_unlock_piece(Coords& new_piece)
{
	static CommonResources* p_resources = common_resources_get_instance();

	if (new_piece.piece_number > _visible_pieces - 1)
	{
		++_visible_pieces;

		// now we have unlocked this element with this skin		
/*		p_resources -> p_engine -> set_skin_element(_visible_pieces);*/
	}
	if (new_piece.piece_number > _unlocked_pieces)
	{
		++_unlocked_pieces;
	}
}

/************************************************************************/
/* Detect pieces to fall                                                */
/************************************************************************/
void AntiCheatGame::_detect_pieces_to_fall()
{
	for (int i = 0; i < NUMBER_OF_COLS; ++i)
		for (int j = NUMBER_OF_LINES - 2; j >= 0; --j)
		{
			if (_board[i][j] >= 0)
			{
				int k = 1;
				while (j + k < NUMBER_OF_LINES && _board[i][j + k] < 0)
				{
					_board[i][j + k] = _board[i][j + k - 1];
					_board[i][j + k - 1] = NO_PIECE;					
					k++;
				}
			}
		}
}