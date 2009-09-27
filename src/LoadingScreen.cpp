/********************************************************************
                            OpenAlchemist
 
  File : LoadingScreen.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
 
 
 *********************************************************************/

#include <ClanLib/core.h>
#include "LoadingScreen.h"
#include "misc.h"
#include "memory.h"

LoadingScreen::LoadingScreen()
{
    
}

LoadingScreen::~LoadingScreen()
{
}

void LoadingScreen::init(CL_GraphicContext &gc, CL_DisplayWindow & window)
{
		_p_gc = &gc;
		_p_window = &window;
		std::string file_path = get_data_path();
    _logo = CL_Image(gc, file_path + get_path_separator() +
                             "loading.png");
                             
    _progression = CL_Image(gc, file_path + get_path_separator() +
                             	    "progression.png");
    _progression_cursor = CL_Image(gc, file_path + get_path_separator() +
                                           "progression-cursor.png");
}

void LoadingScreen::set_progression(float progression)
{    
    _logo.draw(*_p_gc, 400 - _logo.get_width() / 2, 280 - _logo.get_height() / 2);
    
    int base_x = 400 - _progression.get_width() / 2;
    int base_y = 550;
    _progression.draw(*_p_gc, base_x, base_y);
    
    int width = progression * _progression.get_width();
    for(int i=0; i<width; ++i)
    {
    	_progression_cursor.draw(*_p_gc, base_x + i, base_y);
    }

   	_p_window -> flip(0);
    CL_KeepAlive::process();
}

