// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : Piece.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _PIECE_H_
#define _PIECE_H_

#include <iostream>
#include <ClanLib/display.h>

#define PIECE_SPEED 0.7f

/** 
* Piece class
*/
class Piece
{

public:

	/** Constructor */
	Piece(int piece_number)
	{

		_p_normal_sprite = NULL;
		_p_appearing_sprite = NULL;
		_p_disappearing_sprite = NULL;
		_p_mini_sprite = NULL;
		_p_current_sprite = NULL; 

		this -> _piece_number = piece_number;
		this -> _score_value = _score[piece_number];
		_x = 0.0;
		_y = 0.0;
		_target_y = 0;      
	}

	/** Method to set the sprites */
	void set_sprites(CL_Sprite *normal, CL_Sprite *appearing, CL_Sprite *disappearing, CL_Sprite *mini)
	{
		_p_normal_sprite = normal;
		_p_appearing_sprite = appearing;
		_p_disappearing_sprite = disappearing;
		_p_mini_sprite = mini;
		_p_current_sprite = _p_normal_sprite;
	}

	/** Methods to display - be carefull, if current_prite is not initialized */
	void draw(CL_GraphicContext &gc)
	{
		_p_current_sprite -> draw(gc, _x, _y);
	}

	/** Draw mini version of the piece */
	void draw_mini(CL_GraphicContext &gc)
	{
		_p_mini_sprite -> draw(gc, _x, _y); 
	}

	/** Start appear */
	void start_appear()
	{
		_p_appearing_sprite -> set_play_loop(false);
		_p_current_sprite = _p_appearing_sprite;
		_p_current_sprite -> restart();      
	}
	
	/** Start disappear */
	void start_disappear()
	{
		_p_disappearing_sprite -> set_play_loop(false);
		_p_current_sprite = _p_disappearing_sprite;
		_p_current_sprite -> restart();
	}

	/** Start fall */
	void start_fall(int target_x, int target_y)
	{
		this -> _target_y = target_y;
		_x = (float) target_x;
	}

	/** Set normal state */
	void set_normal()
	{
		_p_current_sprite = _p_normal_sprite;
	}

	/** Makes piece appears - return true if the piece is appeared */
	bool appear()
	{
		_p_appearing_sprite -> update();
		if(_p_appearing_sprite -> is_finished())
		{
			_p_current_sprite = _p_normal_sprite;
			return true;
		}

		return false;
	}

	/** Make piece disappear - return true if the piece is disappeared */
	bool disappear()
	{
		_p_disappearing_sprite -> update();
		if(_p_disappearing_sprite -> is_finished())
		{
			_p_current_sprite = _p_normal_sprite;
			return true;
		}
		return false;


	}

	/** Make piece fall -  return true if the piece is placed */
	bool fall(float time_interval)
	{
		_y += PIECE_SPEED * time_interval;
		if(_y >= _target_y)
		{
			_y = (float)_target_y;
			return true;
		}

		return false;
	}

	/** Set value of the piece */
	void set_score_value(int _score_value)
	{
		_score_value = _score_value; 
	}

	/** Get piece value */
	int get_score_value()
	{
		return _score_value;
	}

	/** Set piece ID */
	void set_piece_number(int piece_number)
	{
		_piece_number = piece_number;
		this -> _score_value = _score[_piece_number];
	}

	/** Get piece ID */
	int get_piece_number()
	{
		return _piece_number;
	}

	/** Set piece x */
	void set_x(float x)
	{
		this -> _x = x;
	}

	/** Set piece y */
	void set_y(float y)
	{
		this -> _y = y;
	}

	/** Set piece x */
	void set_x(int x)
	{
		this -> _x = (float)x;
	}

	/** Set piece y */
	void set_y(int y)
	{
		this -> _y = (float)y;
	}

	/** Set position */
	void set_position(float x, float y)
	{
		this -> _x = x;
		this -> _y = y;
	}

	/** Set position */
	void set_position(int x, int y)
	{
		this -> _x = (float)x;
		this -> _y = (float)y;
	}

	/** Get X coord */
	float get_x()
	{
		return _x;
	}

	/** Get y coord */
	float get_y()
	{
		return _y;
	}

	/** Print piece value to the text output */
	void print()
	{
		std::cout << "-----\nnormal_sprite: " << _p_normal_sprite << "\n"
			<< "appearing_sprite: " << _p_appearing_sprite << "\n"
			<< "disappearing_spirte: " << _p_disappearing_sprite << "\n"
			<< "current_sprite: " << _p_current_sprite << "\n";
		if(_p_current_sprite == _p_appearing_sprite)// && appearing_sprite -> is_finished())
		{
			_p_current_sprite = _p_normal_sprite;
		}
	}

private:

	/** Normal sprite */
	CL_Sprite *_p_normal_sprite;

	/** Appearing sprite */
	CL_Sprite *_p_appearing_sprite;

	/** Disappearing sprite */
	CL_Sprite *_p_disappearing_sprite;

	/** Current sprite */
	CL_Sprite *_p_current_sprite;

	/** Mini sprite */
	CL_Sprite *_p_mini_sprite;

	/** Pieces values */
	static const int _score[12];

	/** Piece value */
	int _score_value;

	/** Piece number */
	int _piece_number;

	/** Current coords on the screen */
	float _x, _y;

	/** Target coords */
	int _target_y;


};


#endif
