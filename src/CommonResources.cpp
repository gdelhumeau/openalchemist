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
#include "memory.h"

const int Piece::_score[12] = { 1, 3, 9, 30, 90, 300, 900, 3000, 9000, 30000, 90000, 300000 };

static CommonResources* p_instance = NULL;

CommonResources::CommonResources()
{
	p_current_player = NULL;
}

CommonResources::~CommonResources()
{
	unload_gfx();
}

void CommonResources::init(GameEngine *engine)
{
	this -> p_engine = engine;
	read_scores();

}

void CommonResources::load_gfx(CL_GraphicContext &gc, std::string skin)
{
	this -> skin = skin;

	unload_gfx();

	CL_VirtualFileSystem vfs(skin, true);
	CL_VirtualDirectory vd(vfs, "./");	
	CL_ResourceManager gfx("general.xml", vd);
	CL_ResourceManager gfx_pieces("pieces.xml", vd);

	main_font = CL_Font_Sprite(gc, "font", &gfx);

	// Then, propreties
	pieces_width = CL_Integer_to_int("pieces/width", &gfx_pieces);
	pieces_height = CL_Integer_to_int("pieces/height", &gfx_pieces);

	player1.load_gfx(gc, skin);
	front_layer.load_gfx(gc, skin);

}


void CommonResources::unload_gfx()
{
	player1.unload_gfx();
	front_layer.unload_gfx();
}

void CommonResources::read_scores()
{
	highscore = 0;

	std::string path = get_save_path();

	try
	{
		CL_File file(path+get_path_separator()+"hightscores-"+get_version());

		highscore = file.read_uint32();

	}
	catch(CL_Exception & e)
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
		CL_File file(path+"\\hightscores-"+get_version());
#else
		CL_File file(path+"/hightscores-"+get_version());
#endif

		file.write_uint32(highscore);
		file.close();
	}
	catch(CL_Exception & e)
	{
		std::cout << "Can't write hightscores file. \n";
	}
}


CommonResources* common_resources_get_instance()
{ 
	if(!p_instance)
	{
		std::cout << "Common Resources Init must be called" << std::endl;
	}
	return p_instance;
}

void common_resources_init()
{
	if(!p_instance)
		p_instance = my_new CommonResources();
}

void common_resources_term()
{
	if(p_instance)
	{
		my_delete(p_instance);
		p_instance = NULL;
	}
}
