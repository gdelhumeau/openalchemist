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
  current_player = NULL;
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
  this -> skin = skin;

  unload_gfx();

  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("general.xml",&zip, false);
  CL_ResourceManager gfx_pieces("pieces.xml", &zip, false);

  main_font = new CL_Font("font", &gfx);

  // Then, propreties
  pieces_width = CL_Integer_to_int("pieces/width", &gfx_pieces);
  pieces_height = CL_Integer_to_int("pieces/height", &gfx_pieces);

  player1.load_gfx(skin);
  front_layer.load_gfx(skin);

}


void CommonResources::unload_gfx()
{
  if(main_font)
  {
    delete main_font;
    main_font = NULL;
  }

  player1.unload_gfx();
  front_layer.unload_gfx();

}

void CommonResources::read_scores()
{
  highscore = 0;
    
  std::string path = get_save_path();

  try
  {
    CL_InputSource_File file(path+get_path_separator()+"hightscores-"+get_version());

    file.open();
    highscore = file.read_uint32();
        
  }
  catch(CL_Error e)
  {
    std::cout << "Can't read hightscores file. Probably doesn't exist. \n";
    highscore = 0;
  }
}

void CommonResources::save_scores()
{
  std::string path = get_save_path();

  try
  {
#ifdef WIN32
    CL_OutputSource_File file(path+"\\hightscores-"+get_version());
#else
    CL_OutputSource_File file(path+"/hightscores-"+get_version());
#endif
    
    file.open();
    file.write_uint32(highscore);
    file.close();
  }
  catch(CL_Error e)
  {
    std::cout << "Can't write hightscores file. \n";
  }
}


CommonResources* common_resources_get_instance()
{
  static CommonResources instance;
  return &instance;
}
