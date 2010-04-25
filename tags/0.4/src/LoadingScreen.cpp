// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : LoadingScreen.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include <ClanLib/core.h>
#include "LoadingScreen.h"
#include "misc.h"
#include "memory.h"
#include "Window.h"

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
LoadingScreen::LoadingScreen(Window& window):
_window(window)
{

}

/************************************************************************/
/* Destructor                                                           */
/************************************************************************/
LoadingScreen::~LoadingScreen()
{
}

/************************************************************************/
/* Init                                                                 */
/************************************************************************/
void LoadingScreen::init()
{
	CL_GraphicContext& gc = _window.get_gc();
	std::string file_path = get_data_path();
	_logo = CL_Image(gc, file_path + "loading.png");

	_progression = CL_Image(gc, file_path +	"progression.png");
	_progression_cursor = CL_Image(gc, file_path + "progression-cursor.png");
}

/************************************************************************/
/* Set progression                                                      */
/************************************************************************/
void LoadingScreen::set_progression(float progression)
{    
	_window.prepare();
	
	CL_GraphicContext& gc = _window.get_gc();
	_logo.draw(gc, 400 - _logo.get_width() / 2, 280 - _logo.get_height() / 2);

	int base_x = 400 - _progression.get_width() / 2;
	int base_y = 550;
	_progression.draw(gc, base_x, base_y);

	int width = (int) (progression * _progression.get_width());
	for(int i=0; i<width; ++i)
	{
		_progression_cursor.draw(gc, base_x + i, base_y);
	}

	_window.display();
}