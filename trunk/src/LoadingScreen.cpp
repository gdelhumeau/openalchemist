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

LoadingScreen::LoadingScreen()
{
    std::string file_path = get_data_path();
    _p_logo = new CL_Surface(file_path + get_path_separator() +
                             "loading.png");
                             
    _p_progression = new CL_Surface(file_path + get_path_separator() +
                             	    "progression.png");
    _p_progression_cursor = new CL_Surface(file_path + get_path_separator() +
                                           "progression-cursor.png");
}

LoadingScreen::~LoadingScreen()
{
    delete _p_logo;
    delete _p_progression;
    delete _p_progression_cursor;
}

void LoadingScreen::set_progression(float progression)
{
    CL_Display::clear(CL_Color(0, 0, 0));
    _p_logo -> draw(400 - _p_logo->get_width() / 2, 300 - _p_logo->get_height() / 2);
    
    int base_x = 400 - _p_progression -> get_width() / 2;
    int base_y = 550;
    _p_progression -> draw(base_x, base_y);
    
    int width = progression * _p_progression -> get_width();
    for(int i=0; i<width; ++i)
    {
    	_p_progression_cursor -> draw(base_x + i, base_y);
    }

    CL_Display::flip();
    CL_System::keep_alive();
}

