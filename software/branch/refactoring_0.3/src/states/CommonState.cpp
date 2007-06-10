/********************************************************************
                          OpenAlchemist

  File : CommonState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "CommonState.h"


CommonState::CommonState()
{

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
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("gfx.xml",&zip, false);

  background = new CL_Surface("background", &gfx);
}


void CommonState::unload_gfx()
{

}


void CommonState::draw()
{
  background -> draw(0, 0);
}


void CommonState::update()
{

}


void CommonState::events()
{

}


