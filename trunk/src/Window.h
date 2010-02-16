// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : Window.h
//  Description : Window used to display game
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or +
//
// **********************************************************************

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <ClanLib/display.h>

class GameEngine;

/** 
* Manage the game window and the render target
*/
class Window{

public:

	/** 
	* Constructor
	*/
	Window(int game_width, int game_height);

	/** 
	* Destructor
	*/
	~Window();

	/** 
	* Manage window
	*/
	void manage(GameEngine & game_engine);

	/** 
	* Clear and prepare window for a new frame
	*/
	void prepare();

	/** 
	* Display the frame when it's done
	*/
	void display();

	/** 
	* Get the game surface width
	*/
	inline int get_game_width() const { return _game_width; }

	/** 
	* Get the game surface height
	*/
	inline int get_game_height() const { return _game_height; }

	/** 
	* Get the Graphic Context
	*/
	inline CL_GraphicContext & get_gc() { return _clanlib_window.get_gc(); }

	/** 
	* Get the Input Context
	*/
	inline CL_InputContext & get_ic() { return _clanlib_window.get_ic(); }

	/** 
	* Get current scale
	*/
	inline float get_scale() const { return _scale; }

	/** 
	* Get the display translation (x)
	*/
	inline int get_dx() const { return _dx; }

	/** 
	* Get the display translation (y)
	*/
	inline int get_dy() const { return _dy; }

private:

	/**
	* ClanLib window
	*/
	CL_DisplayWindow _clanlib_window;

	/** 
	* Slot for quit event
	*/
	CL_Slot _quit_event;

	/** 
	* Game Width
	*/
	int _game_width;

	/** 
	* Game Height
	*/
	int _game_height;

	/** 
	* Display scale
	*/
	float _scale;

	/** 
	* Display translation (x)
	*/
	int _dx;

	/** 
	* Display translation (dy)
	*/
	int _dy;

};

#endif