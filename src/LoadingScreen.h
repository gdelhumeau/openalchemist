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

    void set_progression(float progression);

private:

    CL_Surface * _p_logo;
    CL_Surface * _p_progression;
    CL_Surface * _p_progression_cursor;

};


#endif
