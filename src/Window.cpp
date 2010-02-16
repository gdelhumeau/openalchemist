// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : Window.cpp
//  Description : Window used to display game
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or +
//
// **********************************************************************

#include "Window.h"
#include "CommonResources.h"
#include "Preferences.h"
#include "GameEngine.h"
#include "misc.h"

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
Window::Window(int game_width, int game_height)
{
	_game_width = game_width;
	_game_height = game_height;
	_scale = 1;
}

/************************************************************************/
/* Destructor                                                           */
/************************************************************************/
Window::~Window()
{
}

/************************************************************************/
/* Min                                                                  */
/************************************************************************/
#ifndef WIN32
inline float min(float a, float b){ return a < b ? a : b; }
#endif

/************************************************************************/
/* Manager                                                              */
/************************************************************************/
void Window::manage(GameEngine & game_engine)
{
	// Save the old main_window (if valid), so graphics are not lost 
	// when screen mode is changed.
	// It is destroyed as "previous_window" does out of scope
	CL_DisplayWindow previous_window = _clanlib_window;	

	// Window description
	CL_DisplayWindowDescription desc;
	desc.set_title("OpenAlchemist");
	desc.set_size(CL_Size(_game_width, _game_height), true);
	Preferences *p_pref = pref_get_instance();
	if(p_pref -> fullscreen)
	{
		desc.set_fullscreen(true);
		desc.set_decorations(false);
	}
	else
	{
		desc.set_allow_resize(true);
	}

	// Open the window
	_clanlib_window = CL_DisplayWindow(desc);

	// Add an icon
	CL_PixelBuffer icon = CL_PixelBuffer(get_data_path()+"logo.png");
	_clanlib_window.set_large_icon(icon);

	// Drawing black window
	prepare();
	display();

	// Set some variables
	CommonResources * p_common_resources = common_resources_get_instance();
	p_common_resources -> p_window = &_clanlib_window;
	p_common_resources -> p_gc = &_clanlib_window.get_gc();

	// Add a callback when user close the window
	_quit_event = _clanlib_window.sig_window_close().connect(
		&game_engine, &GameEngine::stop);
	
}

/************************************************************************/
/* Clear                                                                */
/************************************************************************/
void Window::prepare()
{
	CL_GraphicContext gc = _clanlib_window.get_gc();

	// Clear screen
	gc.clear();

	// Stretch the game to the window
	_scale = min((float) gc.get_width() / _game_width, 
		(float) gc.get_height() / _game_height);
	CL_Mat4f matrix_scale = CL_Mat4f::scale(_scale, _scale, 1.0f);
	
	// Center the game
	_dx = (int)(gc.get_width()-_game_width*_scale)/2;
	_dy = (int)(gc.get_height()-_game_height*_scale)/2;
	CL_Mat4f matrix_translate = CL_Mat4f::translate((float)_dx, (float)_dy, 0);

	// Apply transformations
	CL_Mat4f matrix_transform = matrix_scale * matrix_translate;
	gc.set_modelview(matrix_transform);
}

/************************************************************************/
/* Display                                                              */
/************************************************************************/
void Window::display()
{
	_clanlib_window.flip(0);

	// This call updates input and performs other "housekeeping"
	// Call this each frame
	CL_KeepAlive::process();
}