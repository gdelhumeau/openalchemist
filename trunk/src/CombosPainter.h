// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : CombosPainter.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _COMBOS_PAINTER_H_
#define _COMBOS_PAINTER_H_

#include <ClanLib/display.h>

/** 
* Draws the current combo score
*/
class CombosPainter{

public:

	/** 
	* Constructor
	*/
	CombosPainter();
 
	/** 
	* Destructor
	*/
	~CombosPainter();

	/** 
	* Load gfx
	*/
	void load_gfx(CL_GraphicContext &gc, std::string skin);
	
	/** 
	* Unload GFX
	*/
	void unload_gfx();

	/** 
	* Set the score to desplay
	*/
	void set_score(int score);

	/** 
	* Draw the combo score
	*/
	void draw(CL_GraphicContext &gc);

	/** 
	* Update
	*/
	void update();

private:

	/**
	* State 
	*/
	enum State{
		STATE_APPEARING,
		STATE_DISPLAY,
		STATE_DISAPPEARING	
	};

	/** 
	* Score to draw
	*/
	int _score;

	/** 
	* Current state
	*/
	State _state;

	/** 
	* Is the combo painter enabled
	*/
	bool _is_enabled;

	/**
	* Single text sprite
	*/
	CL_Sprite _sprite_single;

	/**
	* Plural text sprite
	*/
	CL_Sprite _sprite_plural;

	/**
	* Font
	*/
	CL_Font _font;

	/**
	* Coords
	*/ 
	int _sprite_x, _sprite_y, _score_x, _score_y;

	/**
	* Actual coords
	*/
	float _sprite_current_x, _sprite_current_y, _score_current_x, _score_current_y;

	/** 
	* Next state time
	*/
	unsigned long int _next_time;

	/** 
	* Font height
	*/
	int _font_height;

	/** 
	* Update appearing state
	*/
	void _update_appearing();

	/** 
	* Update display state
	*/
	void _update_display();

	/** 
	* Update disappearing state
	*/
	void _update_disappearing();

};

#endif