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
#include "Piece.h"

const int Piece::score[12] = { 1, 3, 9, 30, 90, 300, 900, 3000, 9000, 30000, 90000, 300000 };

CommonResources::CommonResources()
{
  main_font = NULL;
  /*for(int i = 0; i<NUMBER_OF_PIECES; ++i)
    {
    pieces_normal[i] = NULL;
    pieces_appearing[i] = NULL;
    pieces_disappearing[i] = NULL;
    }*/
}

CommonResources::~CommonResources()
{
  unload_gfx();
}

void CommonResources::init(GameEngine *engine)
{
  this -> engine = engine;
  read_scores();
}

void CommonResources::load_gfx(std::string skin)
{
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("gfx.xml",&zip, false);
  CL_ResourceManager gfx_pieces("pieces.xml", &zip, false);

  main_font = new CL_Font("font", &gfx);

  // Then, propreties
  pieces_width = CL_Integer_to_int("pieces/width", &gfx_pieces);
  pieces_height = CL_Integer_to_int("pieces/height", &gfx_pieces);

  player1.load_gfx(skin);

}


void CommonResources::unload_gfx()
{
  if(main_font)
  {
    delete main_font;
    main_font = NULL;
  }

  player1.unload_gfx();

}

void CommonResources::read_scores()
{
  for(u_int i = 0; i < NUMBER_OF_DIFFICULTIES; ++i)
  {
    hightscores[i] = 0;
  }

  std::string path = get_save_path();

  try
  {
#ifdef WIN32
    CL_InputSource_File file(path+"\\hightscores");
#else
    CL_InputSource_File file(path+"/hightscores");
#endif

    file.open();
    for(u_int i = 0; i < NUMBER_OF_DIFFICULTIES; ++i)
    {
      hightscores[i] = file.read_uint32();
    }
    file.close();
  }
  catch(CL_Error e)
  {
    std::cout << "Can't read hightscores file. Probably doesn't exist. \n";
    for(u_int i = 0; i < NUMBER_OF_DIFFICULTIES; ++i)
    {
      hightscores[i] = 0;
    }
    
  }
}


CommonResources* common_resources_get_instance()
{
  static CommonResources instance;
  return &instance;
}
