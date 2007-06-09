/********************************************************************
                          OpenAlchemist

  File : CommonState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include "CommonState.h"


CommonState::CommonState(CL_DisplayWindow *window, bool opengl)
{
  this -> window = window;
  this -> opengl = opengl;
}


CommonState::~CommonState()
{
  
}

void CommonState::init()
{

}


void CommonState::deinit()
{

}


void CommonState::load_gfx(std::string skin)
{

}


void CommonState::unload_gfx()
{

}


void CommonState::draw()
{

}


void CommonState::update()
{

}


void CommonState::events()
{

}


