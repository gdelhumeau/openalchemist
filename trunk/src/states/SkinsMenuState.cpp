// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : SkinMenuState.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include <ClanLib/core.h>

#include "SkinsMenuState.h"
#include "../memory.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"
#include "../Window.h"

#define STATE_APPEARING 0
#define STATE_ACTIVE 1
#define STATE_DISAPPEARING 2

#define APPEARING_SPEED 0.003

#pragma warning(disable:4244)

void SkinsMenuState::init(CL_GraphicContext &gc)
{

	// Fist we load Skin propreties saved in the conf file

	std::string path = get_save_path();
	std::string file_path = path + get_path_separator() + "skins-" + get_version();

	skins_list.clear();
	try
	{
		CL_File file(file_path);
		int file_size = file.get_size();
		while(file.get_position() != file_size)
		{     
			Skin *sp = new Skin();
			sp -> filename = file.read_string_a();
			sp -> element = file.read_uint8();

			try
			{
				// We load the logo sprite in the gfx ressources file
				CL_VirtualFileSystem vfs(sp -> filename, true);
				CL_VirtualDirectory vd(vfs, "./");
				CL_ResourceManager gfx("general.xml", vd);
				sp -> logo = CL_Image(gc, "logo", &gfx);
				skins_list.insert(skins_list.end(), sp);
			}
			catch(CL_Exception&)
			{
				// We forget this skin
				std::cout << "We don't use " << sp -> filename << " because it doesn't exist." << std::endl;
				delete sp;
			}

		}
		file.close();

	}
	catch(CL_Exception&)
	{
		std::cout << "Error while reading " << file_path << " file, probably doesn't exist yet." << std::endl;
	}

	// Then, we scan the current ./skins folder
	std::string dir = get_skins_path() + get_path_separator();

	CL_DirectoryScanner scanner;
	if (scanner.scan(dir, "*.zip"))
	{
		while(scanner.next())
		{
			if(scanner.is_readable())
			{
				try
				{
					std::string filename = dir+scanner.get_name().c_str();
					// We load the logo sprite in the gfx ressources file

					CL_VirtualFileSystem vfs(filename, true);

					CL_VirtualDirectory vd(vfs, "./");

					CL_ResourceManager gfx("general.xml", vd);
					CL_Image logo = CL_Image(gc, "logo", &gfx);
					bool found = false;
					for(unsigned int i = 0; i < skins_list.size(); ++i)
					{
						if(skins_list[i] -> filename == filename)
						{
							found = true;
							break;
						}
					}
					if(!found)
					{
						Skin *sp = new Skin();
						sp -> filename = filename;
						sp -> element = 3;
						sp -> logo = logo;
						skins_list.insert(skins_list.end(), sp);
					}

				}
				catch(CL_Exception&)
				{
					std::cout << "Skin " << dir << scanner.get_name().c_str() << " is not valid." << std::endl;
				}
			}        

		}
	}

	// Sorting skin list by alphabetical order (bubble sort)
	for(unsigned int i=0; i<skins_list.size(); ++i)
		for(unsigned int j=i+1; j<skins_list.size(); ++j)
		{
			if(skins_list[i]->filename.compare(skins_list[j]->filename)>0)
			{
				Skin * sk = skins_list[i];
				skins_list[i] = skins_list[j];
				skins_list[j] = sk;
			}
		}

		// Calculating the lines number needed for the board
		number_y = skins_list.size() / 2;
		if(skins_list.size() % 2 > 0)
			number_y += 1;

		// Making the board
		skins_board[0] = my_new Skin* [number_y];
		skins_board[1] = my_new Skin* [number_y];

		// Initializing the board
		for(int x=0; x<2; ++x)
			for(int y=0; y<number_y; ++y)
			{
				skins_board[x][y] = NULL;
			}

			// Setting skins to the board
			int x= 0, y = 0;
			for(unsigned int i = 0; i < skins_list.size(); ++i)
			{
				skins_board[x][y] = skins_list[i];
				x++;
				if(x > 1)
				{
					y++;
					x = 0;
				}
			}

			// Initalizing variables
			selection_x = selection_y = 0;
			y_start = 0;
}

void SkinsMenuState::deinit()
{
	// Saving progression skin file
	std::string file_path = get_save_path() + get_path_separator() + "skins-" + get_version();

	try
	{
		CL_File file(file_path, CL_File::create_always, CL_File::access_write);
		for(unsigned int i = 0; i < skins_list.size(); ++i)
		{
			file.write_string_a(skins_list[i]->filename);
			file.write_uint8 (skins_list[i]->element);  
		}
		file.close();

	}
	catch(CL_Exception&)
	{
		std::cout << "Error while reading " << file_path << "file, probably doesn't exist yet." << std::endl;
	}

	for(unsigned int i = 0; i < skins_list.size(); ++i)
	{
		delete skins_list[i];
	}

	skins_list.clear();

	// Temp hack
	//my_delete(skins_board[0]);
	//my_delete(skins_board[1]);
}

void SkinsMenuState::load_gfx(CL_GraphicContext &gc, std::string skin)
{
	// Getting skins resources
	CL_VirtualFileSystem vfs(skin, true);
	CL_VirtualDirectory vd(vfs, "./");
	CL_ResourceManager gfx("menu_skins.xml", vd);

	// First, the sprites
	background = CL_Sprite(gc, "menu_skins/background", &gfx); 
	logo_unavailable = CL_Image(gc, "menu_skins/logo_unavailable", &gfx); 

	cursor = CL_Sprite(gc, "menu_skins/cursor", &gfx);
	arrow_down = CL_Sprite(gc, "menu_skins/arrow_down/sprite", &gfx);
	arrow_down_left = CL_Integer_to_int("menu_skins/arrow_down/left", &gfx);
	arrow_down_top = CL_Integer_to_int("menu_skins/arrow_down/top", &gfx);

	arrow_up = CL_Sprite(gc, "menu_skins/arrow_up/sprite", &gfx);
	arrow_up_left = CL_Integer_to_int("menu_skins/arrow_up/left", &gfx);
	arrow_up_top = CL_Integer_to_int("menu_skins/arrow_up/top", &gfx);

	skins_preview_x = CL_Integer_to_int("menu_skins/skins-preview-coords/left", &gfx);
	skins_preview_y = CL_Integer_to_int("menu_skins/skins-preview-coords/top", &gfx);
	skins_preview_width = CL_Integer_to_int("menu_skins/skins-preview-coords/width", &gfx);
	skins_preview_height = CL_Integer_to_int("menu_skins/skins-preview-coords/height", &gfx);

	cursor_x      = CL_Integer_to_int("menu_skins/cursor-coords/left", &gfx);
	cursor_y      = CL_Integer_to_int("menu_skins/cursor-coords/top", &gfx);
	cursor_width  = CL_Integer_to_int("menu_skins/cursor-coords/width", &gfx);
	cursor_height = CL_Integer_to_int("menu_skins/cursor-coords/height", &gfx);


}

void SkinsMenuState::unload_gfx()
{

}

void SkinsMenuState::draw(CL_GraphicContext &gc)
{
	int x = 400 - background.get_width()/2;
	int y = 300 - background.get_height()/2;
	background.draw(gc, x,y);

	// Drawing logo skins
	for(int i=0; i<2; ++i)
		for(int j=0; j<2 && j+y_start<number_y; ++j)
		{
			if(skins_board[i][j+y_start])
			{ 
				if(!(skins_board[i][j+y_start]->logo.is_null()))
					skins_board[i][j+y_start] -> logo.draw(gc, skins_preview_x+i*skins_preview_width,
					skins_preview_y+j*skins_preview_height);

				// If the skin is not available, we draw logo_unavailable
				if(_p_common_resources -> skin != skins_board[i][j+y_start] -> filename
					&& skins_board[i][j+y_start] -> element < (unsigned int) _p_common_resources->player1.get_visible_pieces())
					logo_unavailable.draw(gc, skins_preview_x+i*skins_preview_width,
					skins_preview_y+j*skins_preview_height);
			}
		}

		// Drawing the cursor
		cursor.draw(gc, cursor_x+selection_x*cursor_width, 
			cursor_y+(selection_y-y_start)*cursor_height);

		// Drawig arrows, if needed
		if(y_start + 2 < number_y)
		{
			arrow_down.draw(gc, arrow_down_left, arrow_down_top);
		}

		if(y_start > 0)
		{
			arrow_up.draw(gc, arrow_up_left, arrow_up_top);
		}

}

void SkinsMenuState::update(CL_GraphicContext &gc)
{
	switch(step)
	{
	case STATE_APPEARING:
		appear();
		break;
	case STATE_DISAPPEARING:
		disappear();
		break;
	}
}

void SkinsMenuState::events(Window & window)
{
	if(step != STATE_ACTIVE)
		return;

	CL_InputContext & ic = window.get_ic();

	if(_p_common_resources->key.escape->get(ic) || _p_common_resources->key.skins->get(ic))
	{   
		step = STATE_DISAPPEARING;
	}

	// KEY DOWN
	if(_p_common_resources -> key.down -> get(ic))
	{
		// If we don't go outline
		if(selection_y + 1 < number_y)
		{
			// If there is a skin in this place
			if(skins_board[selection_x][selection_y + 1])
			{
				selection_y++;

				if(selection_y > y_start + 1)
					y_start ++;
			}
			// Else, we just increment y_start
			else if(selection_y > y_start && selection_x == 1 &&
				!skins_board[1][selection_y+1] && 
				skins_board[0][selection_y+1])
			{
				y_start ++;
			}
		}
	}

	// KEY UP
	if(_p_common_resources -> key.up -> get(ic))
	{
		if(selection_y > 0 && skins_board[selection_x][selection_y-1])
		{
			selection_y--;

			if(selection_y < y_start)
				y_start --;
		}
	}

	// KEY RIGHT
	if(_p_common_resources -> key.right -> get(ic))
	{
		if(selection_x == 0 && skins_board[1][selection_y])
		{
			selection_x = 1;
		}
	}

	// KEY LEFT
	if(_p_common_resources -> key.left -> get(ic))
	{
		if(selection_x == 1 && skins_board[0][selection_y])
		{
			selection_x = 0;
		}
	}

	// KEY ENTER
	if(_p_common_resources -> key.enter -> get(ic))
	{
		// Can we see all pieces ?
		if(skins_board[selection_x][selection_y] -> element >= (unsigned int) _p_common_resources->player1.get_visible_pieces()
			// Is this the current skin ?
			&& _p_common_resources -> skin != skins_board[selection_x][selection_y] -> filename)
		{
			_p_common_resources -> p_engine -> set_skin(skins_board[selection_x][selection_y] -> filename);
		}
	}

}

void SkinsMenuState::appear()
{ 
	if(alpha + APPEARING_SPEED*_p_common_resources -> delta_time >= 1.0)
	{
		step = STATE_ACTIVE;
		alpha = 1.0;
	}
	else
		alpha += APPEARING_SPEED * _p_common_resources -> delta_time;

	background .set_alpha(alpha);
	arrow_up   .set_alpha(alpha);
	arrow_down .set_alpha(alpha);
	cursor     .set_alpha(alpha);
	logo_unavailable .set_alpha(alpha);

	for(unsigned int i = 0; i < skins_list.size(); ++i)
	{
		skins_list[i] -> logo .set_alpha(alpha);
	}


}

void SkinsMenuState::disappear()
{  
	alpha -= APPEARING_SPEED * _p_common_resources -> delta_time;

	background .set_alpha(alpha);
	arrow_up   .set_alpha(alpha);
	arrow_down .set_alpha(alpha);
	cursor     .set_alpha(alpha);
	logo_unavailable .set_alpha(alpha);

	for(unsigned int i = 0; i < skins_list.size(); ++i)
	{
		skins_list[i] -> logo .set_alpha(alpha);
	}

	if(alpha <= 0.0)
	{
		_p_common_resources -> p_engine -> stop_current_state();
		start();
	}

}

void SkinsMenuState::start()
{
	step = STATE_APPEARING;
	alpha = 0.0;
}

bool SkinsMenuState::front_layer_behind()
{
	return true;
}

void SkinsMenuState::set_skin_elements(unsigned int element)
{
	for(unsigned int i = 0; i < skins_list.size(); ++i)
	{
		if(skins_list[i] -> filename == _p_common_resources -> skin)
		{
			if(skins_list[i] -> element < element)
				skins_list[i] -> element = element;
		}
	}
}

SkinsMenuState::SkinsMenuState()
{
	
}

SkinsMenuState::~SkinsMenuState()
{
	deinit();
}



