/********************************************************************
                          OpenAlchemist

  File : CommonResources.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <ClanLib/core.h>

#include "CommonResources.h"

CommonResources::CommonResources()
{
  main_font = NULL;
}

CommonResources::~CommonResources()
{
  unload_gfx();
}

void CommonResources::init(GameEngine *engine)
{
  this -> engine = engine;
}

void CommonResources::load_gfx(std::string skin)
{
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("gfx.xml",&zip, false);

  main_font = new CL_Font("font", &gfx);
}


void CommonResources::unload_gfx()
{
  if(main_font)
  {
    delete main_font;
    main_font = NULL;
  }
  
}


CommonResources* common_resources_get_instance()
{
  static CommonResources instance;
  return &instance;
}
