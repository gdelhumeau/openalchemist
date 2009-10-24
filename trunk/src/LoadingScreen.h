// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : LoadingScreen.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _LOADING_SCREEN_H_
#define _LOADING_SCREEN_H_

#include <ClanLib/display.h>

class Window;

class LoadingScreen
{

public:
	LoadingScreen(Window & window);
	~LoadingScreen();

	void init();
	void set_progression(float progression);

private:

	CL_Image _logo;
	CL_Image _progression;
	CL_Image _progression_cursor;

	Window & _window;

};

#endif