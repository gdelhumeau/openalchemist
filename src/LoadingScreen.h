/********************************************************************
                          OpenAlchemist
 
  File : LoadingScreen.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
 
 
*********************************************************************/

#ifndef _LOADING_SCREEN_H_
#define _LOADING_SCREEN_H_

#include <ClanLib/display.h>

class LoadingScreen
{

public:
    LoadingScreen();
    ~LoadingScreen();

		void init(CL_GraphicContext &gc, CL_DisplayWindow & window);
    void set_progression(float progression);

private:

    CL_Image _logo;
    CL_Image _progression;
    CL_Image _progression_cursor;

		CL_GraphicContext * _p_gc;
		CL_DisplayWindow * _p_window;

};


#endif
