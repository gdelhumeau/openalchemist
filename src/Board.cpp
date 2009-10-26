// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : Board.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include "memory.h"
#include "Board.h"
#include "CommonResources.h"
#include "GameEngine.h"
#include "misc.h"

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
Board::Board()
{
	/* Initializing all to NULL */
	for (int i = 0; i < NUMBER_OF_COLS; ++i)
		for (int j = 0; j < NUMBER_OF_LINES; ++j)
			_p_board[i][j] = NULL;
}

/************************************************************************/
/* Destructor                                                           */
/************************************************************************/
Board::~Board()
{
	clear();
}

/************************************************************************/
/* Clear                                                                */
/************************************************************************/
void Board::clear()
{
	/* Initializing all to NULL */
	for (int i = 0; i < NUMBER_OF_COLS; ++i)
		for (int j = 0; j < NUMBER_OF_LINES; ++j)
			if (_p_board[i][j])
			{
				my_delete(_p_board[i][j]);
				_p_board[i][j] = NULL;
			}

}

/************************************************************************/
/* Apply skin                                                           */
/************************************************************************/
void Board::apply_skin(CL_Sprite* pieces_normal,
					   CL_Sprite* pieces_appearing,
					   CL_Sprite* pieces_disappearing,
					   CL_Sprite* pieces_mini)
{
	for (int i = 0; i < NUMBER_OF_COLS; ++i)
		for (int j = 0; j < NUMBER_OF_LINES; ++j)
		{
			if (_p_board[i][j])
			{
				int value = _p_board[i][j] -> get_piece_number();
				_p_board[i][j] -> set_sprites(&pieces_normal[value], &pieces_appearing[value],
					&pieces_disappearing[value], &pieces_mini[value]);
			}
		}
}

/************************************************************************/
/* Draw                                                                 */
/************************************************************************/
void Board::draw(CL_GraphicContext & gc)
{
	// Getting resources
	static CommonResources *p_resources = common_resources_get_instance();

	for (int i = 0; i < NUMBER_OF_COLS; ++i)
	{
		for (int j = 0; j < NUMBER_OF_LINES; ++j)
		{
			if (_p_board[i][j])
			{
				_p_board[i][j] -> draw(gc);
			}
		}
	}

	// Displaying scores
	p_resources -> main_font.draw_text(gc, score_left, score_top, str_score);
	p_resources -> main_font.draw_text(gc, bonus_left, bonus_top, str_bonus);
	p_resources -> main_font.draw_text(gc, hightscore_left, hightscore_top, str_hightscore);
}

/************************************************************************/
/* Add pieces                                                           */
/************************************************************************/
void Board::add_pieces(Piece* piece1, Piece* piece2)
{
	// Getting resources
	static CommonResources *p_resources = common_resources_get_instance();

	// Saving old score
	undo_body_score = body_score;
	undo_bonus_score = bonus_score;	

	// Saving board state for undoing
	for (int i = 0; i < NUMBER_OF_COLS; ++i)
		for (int j = 0; j < NUMBER_OF_LINES; ++j)
		{
			if (_p_board[i][j])
			{
				_undo_board[i][j] = _p_board[i][j] -> get_piece_number();
			}
			else
			{
				_undo_board[i][j] = -1;
			}
		}

		undo_unlocked_pieces = unlocked_pieces;
		undo_visible_pieces = visible_pieces;

		Piece *piece_on_top, *piece_on_bottom;
		if (piece1 -> get_y() <= piece2 -> get_y())
		{
			piece_on_top = piece1;
			piece_on_bottom = piece2;
		}
		else
		{
			piece_on_top = piece2;
			piece_on_bottom = piece1;
		}


		int piece_top_x = (int) ((int) piece_on_top->get_x() - game_left) / (p_resources->pieces_width);
		int piece_bottom_x = (int) ((int) piece_on_bottom->get_x() - game_left) / (p_resources->pieces_width);

		int y_bottom = -1;
		while (y_bottom < NUMBER_OF_LINES - 1 && !_p_board[piece_bottom_x][y_bottom + 1])
		{
			++y_bottom;
		}

		if (y_bottom == -1 && _p_board[piece_bottom_x][0])
		{
			calc_score();
			p_resources -> p_engine -> set_state_gameover(false);
		}
		else
		{
			_p_board[piece_bottom_x][y_bottom] = piece_on_bottom;
		}


		int y_top = -1;
		while (y_top < NUMBER_OF_LINES - 1 && !_p_board[piece_top_x][y_top + 1])
		{
			++y_top;
		}

		if (y_top == -1 && _p_board[piece_top_x][0])
		{
			calc_score();
			p_resources -> p_engine -> set_state_gameover(false);
			_p_board[piece_bottom_x][y_bottom] = NULL;
		}
		else
		{
			_p_board[piece_top_x][y_top] = piece_on_top;
		}

		piece_on_bottom -> start_fall(piece_bottom_x * p_resources->pieces_width + game_left,
			game_top + (y_bottom - 2) * p_resources->pieces_height);
		piece_on_top -> start_fall(piece_top_x * p_resources->pieces_width + game_left,
			game_top + (y_top - 2) * p_resources->pieces_height);

		_falling_list.clear();
		_falling_list.push_back(piece_on_top);
		_falling_list.push_back(piece_on_bottom);

}

/************************************************************************/
/* Fall and create                                                      */
/************************************************************************/
bool Board::fall_and_create()
{
	// Getting resources
	static CommonResources *resources = common_resources_get_instance();

	bool all_pieces_are_placed = true;
	for (unsigned int i = 0; i < _falling_list.size(); ++i)
	{
		if (_falling_list[i])
		{
			if (!_falling_list[i] -> fall(resources -> delta_time))
			{
				all_pieces_are_placed = false;
			}
		}
	}

	// This part makes pieces appear
	std::list<Piece*>::iterator it = _appearing_list.begin();
	while (it != _appearing_list.end())
	{
		Piece *p = (Piece*) * it;
		if (p -> appear())
		{
			it = _appearing_list.erase(it);
		}
		else
		{
			all_pieces_are_placed = false;
			++it;
		}
	}

	return all_pieces_are_placed;

}

/************************************************************************/
/* Detect pieces to destroy                                             */
/************************************************************************/
bool Board::detect_pieces_to_destroy()
{

	// This table is used to know if a piece have been explorated 
	for (int k = 0; k < NUMBER_OF_COLS; ++k)
		for (int l = 0; l < NUMBER_OF_LINES; ++l)
			_board_mark[k][l] = false;

	// We clear the list witch will contains the pieces to make disappear
	_list_to_destroy.clear();

	// We will look from all pieces in the table
	for (int x = 0; x < NUMBER_OF_COLS; ++x)
		for (int y = 0; y < NUMBER_OF_LINES; ++y)
		{
			_detect_pieces_to_destroy_from(x, y);
		}

		// if the list_to_destroy is not empty, then we have detected some pieces
		return !_list_to_destroy.empty();

}

/************************************************************************/
/* Destect pieces to destroy from coords                                */
/************************************************************************/
void Board::_detect_pieces_to_destroy_from(int i,
										   int j)
{
	if (_p_board[i][j] != NULL && !_board_mark[i][j])
	{
		int counter = 0;
		int root_number = _p_board[i][j] -> get_piece_number();

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
				&& _p_board[x][y] != NULL)
			{
				// We look if this piece is the same as the reference
				if (!_board_mark[x][y] && _p_board[x][y]->get_piece_number() == root_number)
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
		{
			_pieces_to_destroy_detected(detected_pieces);
		}
		else
		{			
			detected_pieces.clear();					
		}

	}
}

/************************************************************************/
/* Pieces to destroys are detected                                      */
/************************************************************************/
void Board::_pieces_to_destroy_detected(std::vector<Coords> &detected_pieces)
{

	Coords c = detected_pieces[0];
	unsigned int piece_number = _p_board[c.x][c.y]->get_piece_number();

	int counter = (int) detected_pieces.size();

	// if we aligned the last element
	if (piece_number == NUMBER_OF_PIECES - 1)
	{
		std::cout << "You align " << counter << " ultimate elements ! Cheater :p" << std::endl;
		bonus_score += counter * _p_board[c.x][c.y]->get_score_value();
	}
	// If it was not last element
	else
	{
		bonus_score += (counter - 3) * _p_board[c.x][c.y]->get_score_value();
	}
	

	_create_new_piece(detected_pieces);

}

/************************************************************************/
/* Create new piece                                                     */
/************************************************************************/
void Board::_create_new_piece(std::vector<Coords> &detected_pieces)
{
	// Determining the new piece coords
	Coords new_piece(NUMBER_OF_COLS + 1, -1);
	_choose_new_piece_coords(new_piece, detected_pieces);

	// Determining the new piece number
	new_piece.piece_number =
		_p_board[detected_pieces[0].x][detected_pieces[0].y]->get_piece_number() + 1;
	if (new_piece.piece_number >= NUMBER_OF_PIECES)
	{
		new_piece.piece_number = NUMBER_OF_PIECES - 1;
	}

	// Maybe we have unlocked new element ?
	_unlock_piece(new_piece);

	// We add the my_new piece except if we have aligned 3 last elements
	if (new_piece.piece_number != NUMBER_OF_PIECES - 1)
		_list_to_create.insert(_list_to_create.end(), Coords(&new_piece));

}

/************************************************************************/
/* Choose new piece coord                                               */
/************************************************************************/
void Board::_choose_new_piece_coords(Coords &new_piece, std::vector<Coords> &detected_pieces)
{
	std::vector<Coords>::iterator it = detected_pieces.begin();
	while (it != detected_pieces.end())
	{
		Coords c = (Coords) * it;
		_p_board[c.x][c.y]->start_disappear();
		_list_to_destroy.insert(_list_to_destroy.end(), c);

		// Select the lefter and bottomer Coords for create my_new piece
		if (c.y > new_piece.y)
		{
			new_piece.x = c.x;
			new_piece.y = c.y;
		}
		else if (c.y == new_piece.y)
		{
			if (c.x < new_piece.x)
			{
				new_piece.x = c.x;
				new_piece.y = c.y;
			}
		}

		++it;
	}
}

/************************************************************************/
/* Unlock piece                                                         */
/************************************************************************/
void Board::_unlock_piece(Coords &new_piece)
{
	static CommonResources *resources = common_resources_get_instance();

	if (new_piece.piece_number > visible_pieces - 1)
	{
		++visible_pieces;

		// now we have unlocked this element with this skin		
		resources -> p_engine -> set_skin_element(visible_pieces);
	}
	if (new_piece.piece_number > unlocked_pieces)
	{
		unlocked_pieces++;
	}
}

/************************************************************************/
/* Destroy                                                              */
/************************************************************************/
bool Board::destroy()
{
	bool end = true;
	std::vector<Coords>::iterator it = _list_to_destroy.begin();
	while(it != _list_to_destroy.end())
	{
		Coords c = *it;

		if (_p_board[c.x][c.y] != NULL && !_p_board[c.x][c.y]->disappear())
		{
			end = false;
			it++;
		}
		else
		{
			my_delete(_p_board[c.x][c.y]);
			_p_board[c.x][c.y] = NULL;
			it = _list_to_destroy.erase(it);
		}

	}

	return end;
}

/************************************************************************/
/* Create new pieces                                                    */
/************************************************************************/
void Board::create_new_pieces(CL_Sprite *pieces_normal,
							  CL_Sprite *pieces_appearing,
							  CL_Sprite *pieces_disappearing,
							  CL_Sprite *pieces_mini)
{
	// Getting resources
	static CommonResources *resources = common_resources_get_instance();

	_list_to_destroy.clear();
	_appearing_list.clear();

	std::list<Coords>::iterator it = _list_to_create.begin();
	while (it != _list_to_create.end())
	{
		Coords c = (Coords) * it;
		if (	c.x >= 0 && c.x < NUMBER_OF_COLS
			&& c.y >= 0 && c.y < NUMBER_OF_LINES
			&& !_p_board[c.x][c.y])
		{

			int score = c.piece_number;
			Piece *p = my_new Piece(score);
			p -> set_position(c.x * resources->pieces_width + game_left,
				game_top + (c.y - 2) * resources->pieces_height);

			p -> set_sprites(&pieces_normal[score], &pieces_appearing[score],
				&pieces_disappearing[score], &pieces_mini[score]);


			p -> start_appear();

			_p_board[c.x][c.y] = p;
			_appearing_list.insert(_appearing_list.begin(), p);

			it = _list_to_create.erase(it);
		}
	}
}

/************************************************************************/
/* Detect pirces to fall                                                */
/************************************************************************/
void Board::detect_pieces_to_fall()
{
	// Getting resources
	static CommonResources *resources = common_resources_get_instance();

	_falling_list.clear();
	for (int i = 0; i < NUMBER_OF_COLS; ++i)
		for (int j = NUMBER_OF_LINES - 2; j >= 0; --j)
		{
			if (_p_board[i][j] != NULL)
			{
				int k = 1;
				while (j + k < NUMBER_OF_LINES && _p_board[i][j + k] == NULL)
				{
					_p_board[i][j + k] = _p_board[i][j + k - 1];
					_p_board[i][j + k - 1] = NULL;
					_p_board[i][j + k] -> start_fall((int) (_p_board[i][j + k]->get_x()),
						(int) (game_top + (j + k - 2) * resources->pieces_height));
					k++;
				}
				if (k > 1)
				{
					_falling_list.insert(_falling_list.end(), _p_board[i][j + k - 1]);
				}
			}
		}
}

/************************************************************************/
/* Is game over                                                         */
/************************************************************************/
bool Board::is_game_over()
{
	for (int i = 0; i < NUMBER_OF_COLS; ++i)
		for (int j = 0; j < 2; ++j)
		{

			if (_p_board[i][j] != NULL)
			{
				calc_score();
				return true;
			}
		}

		return false;

}

/************************************************************************/
/* Compute score                                                        */
/************************************************************************/
void Board::calc_score()
{
	// Getting resources
	static CommonResources *p_resources = common_resources_get_instance();

	body_score = 0;
	for (int i = 0; i < NUMBER_OF_COLS; ++i)
	{
		for (int j = 2; j < NUMBER_OF_LINES; ++j)
		{
			if (_p_board[i][j])
			{
				body_score += _p_board[i][j]->get_score_value();
			}
		}
	}

	str_score = format_number(to_string(body_score));
	str_bonus = format_number(to_string(bonus_score));
	str_hightscore = format_number(to_string(p_resources->highscore));

	int score_width = p_resources->main_font.get_text_size(
		*p_resources->p_gc, str_score).width;
	int bonus_width = p_resources->main_font.get_text_size(
		*p_resources->p_gc, str_bonus).width;
	int hightscore_width = p_resources->main_font.get_text_size(
		*p_resources->p_gc, str_hightscore).width;

	score_left = score_right - score_width;
	bonus_left = bonus_right - bonus_width;
	hightscore_left = hightscore_right - hightscore_width;
}

/************************************************************************/
/* Undo                                                                 */
/************************************************************************/
void Board::undo(
				 CL_Sprite *pieces_normal,
				 CL_Sprite* pieces_appearing,
				 CL_Sprite* pieces_disappearing,
				 CL_Sprite* pieces_mini)
{
	// Getting resources
	static CommonResources *resources = common_resources_get_instance();

	if (body_score + bonus_score == resources -> highscore)
	{
		resources -> highscore = resources -> old_highscore;
		resources -> save_scores();
	}

	// Delete the pieces in the board and replace by my_new ones
	for (int i = 0; i < NUMBER_OF_COLS; ++i)
	{
		for (int j = 0; j < NUMBER_OF_LINES; ++j)
		{
			if (_p_board[i][j]) my_delete(_p_board[i][j]);
			_p_board[i][j] = NULL;

			if (_undo_board[i][j] >= 0)
			{
				_p_board[i][j] = my_new Piece(_undo_board[i][j]);
				_p_board[i][j] -> set_sprites(&pieces_normal[_undo_board[i][j]],
					&pieces_appearing[_undo_board[i][j]],
					&pieces_disappearing[_undo_board[i][j]],
					&pieces_mini[_undo_board[i][j]]);
				_p_board[i][j] -> set_position(i * resources->pieces_width + game_left, game_top + (j - 2) * resources->pieces_height);
			}
		}
	}

	bonus_score = undo_bonus_score;
	// Penality !
	bonus_score *= 0.9;

	unlocked_pieces = undo_unlocked_pieces;
	visible_pieces = undo_visible_pieces;

	calc_score();
}