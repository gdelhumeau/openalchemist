/********************************************************************
                          OpenAlchemist

  File : CommonResources.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <ClanLib/core.h>

#include "CommonResources.h"
#include "Preferences.h"
#include "misc.h"

CommonResources::CommonResources()
{
  main_font = NULL;
  for(int i = 0; i<NUMBER_OF_PIECES; ++i)
  {
    pieces_normal[i] = NULL;
    pieces_appearing[i] = NULL;
    pieces_disappearing[i] = NULL;
  }
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
  CL_ResourceManager gfx_pieces("pieces.xml", &zip, false);

  main_font = new CL_Font("font", &gfx);

  Preferences *pref = pref_get_instance();
  
  // First we load the sprites
  for(int i = 1; i<=NUMBER_OF_PIECES; ++i)
  {
    if(pref -> colorblind)
      pieces_normal[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/normal-color-blind", &gfx_pieces);
    else
      pieces_normal[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/normal", &gfx_pieces);

    pieces_appearing[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/appear", &gfx_pieces);
    pieces_disappearing[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/disappear", &gfx_pieces);
    
    if(pref -> colorblind)
      pieces_mini[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/little-color-blind", &gfx_pieces);
    else
      pieces_mini[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/little", &gfx_pieces);
   
  }

  // Then, propreties
  pieces_width = CL_Integer_to_int("pieces/width", &gfx_pieces);
  pieces_height = CL_Integer_to_int("pieces/height", &gfx_pieces);
}


void CommonResources::unload_gfx()
{
  if(main_font)
  {
    delete main_font;
    main_font = NULL;
  }

  // Delete the pieces sprites
  for(int i = 0; i<NUMBER_OF_PIECES; ++i)
  {
    if(pieces_normal[i])
    {
      delete pieces_normal[i];
      pieces_normal[i] = NULL;
    }
    if(pieces_appearing[i])
    {
      delete pieces_appearing[i];
      pieces_appearing[i] = NULL;
    }
    if(pieces_disappearing[i])
    {
      delete pieces_disappearing[i];
      pieces_disappearing[i] = NULL;
    }

  }
  
}


CommonResources* common_resources_get_instance()
{
  static CommonResources instance;
  return &instance;
}
