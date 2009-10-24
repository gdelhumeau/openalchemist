// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : Player.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <ClanLib/display.h>

#include "Piece.h"
#include "Board.h"
#include "KeyboardKey.h"
#include "ProgressBar.h"
#include "CombosPainter.h"

enum GameMode{
	GAME_MODE_PLAYING,
	GAME_MODE_FALLING_AND_CREATING,
	GAME_MODE_DESTROYING
};

/**
* Implements the player, keys events for going left, right & falling
* and contains his board.
*/
class Player{

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
	void load_gfx(CL_GraphicContext & gc, std::string skin);

	/**
	* Unload GFX
	*/
	void unload_gfx();

	/**
	* Checking key events
	*/
	void events(CL_InputContext & ic);    

	/**
	* Draw player (board and playable pieces)
	*/
	void draw(CL_GraphicContext & gc);

	/**
	* Make a new party
	*/
	void new_game();

	/**
	* Terminate the party
	*/
	void term_game();

	/**
	* Update playable pieces and board
	*/
	void update();  

	/**
	* Get score
	*/
	unsigned int get_score();  

	/**
	* Returning if undo is available
	*/
	bool is_undo_available();

	/**
	* Undoing last action
	*/
	void undo();  

	/**
	* Returns if the game is over
	*/
	bool is_game_over();

	/** 
	* Give up
	*/
	void give_up();  

	/**
	* Get number of visible pieces
	*/
	int get_visible_pieces();

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
	* Fall playable pieces
	*/
	void fall();

	/** 
	* Returns if the player is human
	*/
	virtual bool is_human() = 0;

protected:

	/**
	* X Position
	*/
	float _x;

	/**
	* Angle
	*/
	float _angle;  

	/**
	* Angle required (for changing)
	*/
	int _aimed_angle;

	/**
	* Current position (in cols)
	*/
	int _position;

	/**
	* Old position (to undo - in cols)
	*/
	int _old_position;

	/**
	* 1 if angle = 90 or 180
	*/
	int _position_bis;

	/**
	* Old position bis to undo
	*/
	int _old_position_bis;

	/**
	* To know if the position bis is due to right position
	*/
	bool _is_forced_bis;

	/**
	* To know if pieces are moving too the left or to the right or not
	*/
	bool _is_placed;

	/**
	* Game Mode
	*/
	GameMode _game_mode;

	/** 
	* Save if the game mode has changed
	*/
	bool _game_mode_changed;

	/** 
	* Sound played
	*/
	bool _play_destroying_sound;

	/** 
	* Manual mode (to stop game mode succession - for DemoPlayer)
	*/
	bool _manual_mode;

	/**
	* One of the next piece (displaying in top)
	*/
	Piece* _p_next_piece1;

	/**
	* One of the next piece (displaying in top)
	*/
	Piece* _p_next_piece2;

	/** 
	* Next pieces ID
	*/
	int _next_next_piece1, _next_next_piece2;

	/**
	* X Position for next items
	*/
	int _next_left;

	/**
	* Y Position for next items
	*/
	int _next_top;

	/**
	* One of the current pieces
	*/
	Piece* _p_current_piece1;

	/**
	* One of the current pieces
	*/
	Piece* _p_current_piece2;

	/**
	* Rayon of circle which contains playable pieces
	*/
	int _current_pieces_r;

	/** 
	* Contains the normal pieces sprites
	*/
	CL_Sprite _pieces_normal[NUMBER_OF_PIECES];

	/**
	* Contains the appearing pieces sprites
	*/
	CL_Sprite _pieces_appearing[NUMBER_OF_PIECES];

	/**
	* Contains the disappearing pieces sprites
	*/
	CL_Sprite _pieces_disappearing[NUMBER_OF_PIECES];

	/**
	* Contains the mini pieces sprites
	*/
	CL_Sprite _pieces_mini[NUMBER_OF_PIECES];

	/**
	* Contains the hidden pieces sprites
	*/
	CL_Sprite _pieces_hidden[NUMBER_OF_PIECES - 3];

	/**
	* X Coord of pieces preview
	*/
	int _pieces_preview_x[NUMBER_OF_PIECES];

	/**
	* Y Coord if pieces preview
	*/
	int _pieces_preview_y[NUMBER_OF_PIECES];

	/**
	* Board game
	*/
	Board _board;

	/**
	* Key for playing
	*/
	KeyboardKey *_p_key_change_angle;

	/**
	* Key for playing
	*/
	KeyboardKey *_p_key_left;

	/**
	* Key for playing
	*/
	KeyboardKey *_p_key_right;

	/**
	* Key for playing
	*/
	KeyboardKey *_p_key_falling;

	/**
	* True if player press fall button
	*/
	bool _is_falling_requested;

	/**
	* Combo counter
	*/
	int _combo;

	/**
	* Combos Painter
	*/
	CombosPainter _combos_painter;

	/**
	* Progress Bar
	*/
	ProgressBar _progress_bar;

	/**
	* Undo elements
	*/
	int _undo_position;
	int _undo_position_bis;
	int _undo_piece1_number;
	int _undo_piece2_number;
	int _undo_angle;
	bool _undo_possible;

	/**
	* Update when game_mode = playing
	*/
	void _update_playing();

	/**
	* Update when game_mode = falling & creating
	*/
	void _update_falling_and_creating();

	/**
	* Update when game_mode = destroying
	*/
	void _update_destroying();

	/**
	* Prepare game to play (after a fall)
	*/
	void _prepare_to_play();


};

#endif