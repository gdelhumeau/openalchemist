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
#include "../misc.h"
#include "../Window.h"

#pragma warning(disable:4244)

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
SkinsMenuState::SkinsMenuState()
{

}

/************************************************************************/
/* Destructor                                                           */
/************************************************************************/
SkinsMenuState::~SkinsMenuState()
{
}

/************************************************************************/
/* Init                                                                 */
/************************************************************************/
void SkinsMenuState::init()
{
	_items.push_back(&_skin_chooser);

	_load_registred_skins();
	_scan_skins_path(get_skins_path());
	_scan_skins_path(get_user_skins_path());
	_sort_skins();

	for(unsigned int i=0; i<_skins_list.size(); ++i)
	{
		_skin_chooser.add_choice(&_skins_list[i]->logo);
	}
}

/************************************************************************/
/* Term                                                                 */
/************************************************************************/
void SkinsMenuState::deinit()
{
	_save_registred_skins();

	// Deleting skins;
	for(unsigned int i = 0; i < _skins_list.size(); ++i)
	{
		my_delete(_skins_list[i]);
	}

	_skins_list.clear();
}

static const int LOGO_WIDTH = 200;
static const int LOGO_HEIGHT = 150;
static const int NB_COLS = 2;

/************************************************************************/
/* Load GFX                                                             */
/************************************************************************/
void SkinsMenuState::load_gfx(CL_GraphicContext &gc, std::string skin)
{
	// Getting skins resources
	CL_VirtualFileSystem vfs(skin, true);
	CL_VirtualDirectory vd(vfs, "./");
	CL_ResourceManager gfx("menu_skins.xml", vd);

	// First, the sprites
	_background = CL_Sprite(gc, "menu_skins/background", &gfx); 
	logo_unavailable = CL_Image(gc, "menu_skins/logo_unavailable", &gfx); 

	_skin_chooser.set_cursor(gc, gfx, "menu_skins/cursor");
	_skin_chooser.set_arrow_up(gc, gfx, "menu_skins/arrow_up/sprite");
	_skin_chooser.set_arrow_down(gc, gfx, "menu_skins/arrow_down/sprite");

	_skin_chooser.set_begin_x(CL_Integer_to_int("menu_skins/skins-preview-coords/left", &gfx));
	_skin_chooser.set_begin_y(CL_Integer_to_int("menu_skins/skins-preview-coords/top", &gfx));

	_skin_chooser.set_margin_width(CL_Integer_to_int(
		"menu_skins/skins-preview-coords/margin-horizontal", &gfx));
	_skin_chooser.set_margin_height(CL_Integer_to_int(
		"menu_skins/skins-preview-coords/margin-vertical", &gfx));

	_skin_chooser.set_arrow_up_x(CL_Integer_to_int("menu_skins/arrow_up/left", &gfx));
	_skin_chooser.set_arrow_up_y(CL_Integer_to_int("menu_skins/arrow_up/top", &gfx));
	_skin_chooser.set_arrow_down_x(CL_Integer_to_int("menu_skins/arrow_down/left", &gfx));
	_skin_chooser.set_arrow_down_y(CL_Integer_to_int("menu_skins/arrow_down/top", &gfx));

	_skin_chooser.set_choice_width(LOGO_WIDTH);
	_skin_chooser.set_choice_height(LOGO_HEIGHT);
	_skin_chooser.set_nb_cols(NB_COLS);
	



// 	arrow_down = CL_Sprite(gc, "menu_skins/arrow_down/sprite", &gfx);
// 	arrow_down_left = CL_Integer_to_int("menu_skins/arrow_down/left", &gfx);
// 	arrow_down_top = CL_Integer_to_int("menu_skins/arrow_down/top", &gfx);
// 
// 	arrow_up = CL_Sprite(gc, "menu_skins/arrow_up/sprite", &gfx);
// 	arrow_up_left = CL_Integer_to_int("menu_skins/arrow_up/left", &gfx);
// 	arrow_up_top = CL_Integer_to_int("menu_skins/arrow_up/top", &gfx);
// 
// 	skins_preview_x = CL_Integer_to_int("menu_skins/skins-preview-coords/left", &gfx);
// 	skins_preview_y = CL_Integer_to_int("menu_skins/skins-preview-coords/top", &gfx);
// 	skins_preview_width = CL_Integer_to_int("menu_skins/skins-preview-coords/width", &gfx);
// 	skins_preview_height = CL_Integer_to_int("menu_skins/skins-preview-coords/height", &gfx);
// 
// 	cursor_x      = CL_Integer_to_int("menu_skins/cursor-coords/left", &gfx);
// 	cursor_y      = CL_Integer_to_int("menu_skins/cursor-coords/top", &gfx);
// 	cursor_width  = CL_Integer_to_int("menu_skins/cursor-coords/width", &gfx);
// 	cursor_height = CL_Integer_to_int("menu_skins/cursor-coords/height", &gfx);
// 	
	//_basic_item.set_gfx()

}

/************************************************************************/
/* Unload GFX                                                           */
/************************************************************************/
void SkinsMenuState::unload_gfx()
{

}

// 
// void SkinsMenuState::events(Window & window)
// {
// 	if(step != STATE_ACTIVE)
// 		return;
// 
// 	CL_InputContext & ic = window.get_ic();
// 
// 	if(_p_common_resources->key.escape->get(ic) || _p_common_resources->key.skins->get(ic))
// 	{   
// 		step = STATE_DISAPPEARING;
// 	}
// 
// 	// KEY DOWN
// 	if(_p_common_resources -> key.down -> get(ic))
// 	{
// 		// If we don't go outline
// 		if(selection_y + 1 < number_y)
// 		{
// 			// If there is a skin in this place
// 			if(skins_board[selection_x][selection_y + 1])
// 			{
// 				selection_y++;
// 
// 				if(selection_y > y_start + 1)
// 					y_start ++;
// 			}
// 			// Else, we just increment y_start
// 			else if(selection_y > y_start && selection_x == 1 &&
// 				!skins_board[1][selection_y+1] && 
// 				skins_board[0][selection_y+1])
// 			{
// 				y_start ++;
// 			}
// 		}
// 	}
// 
// 	// KEY UP
// 	if(_p_common_resources -> key.up -> get(ic))
// 	{
// 		if(selection_y > 0 && skins_board[selection_x][selection_y-1])
// 		{
// 			selection_y--;
// 
// 			if(selection_y < y_start)
// 				y_start --;
// 		}
// 	}
// 
// 	// KEY RIGHT
// 	if(_p_common_resources -> key.right -> get(ic))
// 	{
// 		if(selection_x == 0 && skins_board[1][selection_y])
// 		{
// 			selection_x = 1;
// 		}
// 	}
// 
// 	// KEY LEFT
// 	if(_p_common_resources -> key.left -> get(ic))
// 	{
// 		if(selection_x == 1 && skins_board[0][selection_y])
// 		{
// 			selection_x = 0;
// 		}
// 	}
// 
// 	// KEY ENTER
// 	if(_p_common_resources -> key.enter -> get(ic))
// 	{
// 		// Can we see all pieces ?
// 		if(skins_board[selection_x][selection_y] -> element >= (unsigned int) _p_common_resources->player1.get_visible_pieces()
// 			// Is this the current skin ?
// 			&& _p_common_resources -> skin != skins_board[selection_x][selection_y] -> filename)
// 		{
// 			_p_common_resources -> p_engine -> set_skin(skins_board[selection_x][selection_y] -> filename);
// 		}
// 	}
// 
// }

/************************************************************************/
/* Set skin element                                                     */
/************************************************************************/
void SkinsMenuState::set_skin_elements(unsigned int element)
{
	for(unsigned int i = 0; i < _skins_list.size(); ++i)
	{
		if(_skins_list[i] -> filename == _p_common_resources -> skin)
		{
			if(_skins_list[i] -> element < element)
				_skins_list[i] -> element = element;
		}
	}
}

/************************************************************************/
/* Action performed                                                     */
/************************************************************************/
void SkinsMenuState::action_performed(int selection, int action_type)
{

}

/************************************************************************/
/* Update child                                                         */
/************************************************************************/
void SkinsMenuState::update_child()
{

}

/************************************************************************/
/* Load registred skins                                                 */
/************************************************************************/
void SkinsMenuState::_load_registred_skins()
{
	// Fist we load Skin propreties saved in the conf file
	std::string path = get_save_path();
	std::string file_path = path + get_path_separator() + "skins-" + get_version();

	_skins_list.clear();
	try
	{
		CL_File file(file_path);
		int file_size = file.get_size();
		while(file.get_position() != file_size)
		{     
			Skin *p_skin = my_new Skin();
			p_skin -> filename = file.read_string_a();
			p_skin -> element = file.read_uint8();
			try
			{
				// We load the logo sprite in the gfx ressources file
				CL_VirtualFileSystem vfs(p_skin -> filename, true);
				CL_VirtualDirectory vd(vfs, "./");
				CL_ResourceManager gfx("general.xml", vd);
				p_skin -> logo = CL_Image(*_p_common_resources->p_gc, "logo", &gfx);
				_skins_list.push_back(p_skin);
			}
			catch(CL_Exception&)
			{
				// We forget this skin
				std::cout << "We don't use " << p_skin -> filename << 
					" because it doesn't exist." << std::endl;
				delete p_skin;
			}
		}
		file.close();
	}
	catch(CL_Exception&)
	{
		std::cout << "Error while reading " << file_path <<
			" file, probably doesn't exist yet." << std::endl;
	}
}

/************************************************************************/
/* Scan skins path                                                      */
/************************************************************************/
void SkinsMenuState::_scan_skins_path(std::string path)
{
	CL_DirectoryScanner scanner;
	if (scanner.scan(path, "*.zip"))
	{
		while(scanner.next())
		{
			if(scanner.is_readable())
			{
				try
				{
					std::string filename = path+get_path_separator()
						+scanner.get_name().c_str();
					// We load the logo sprite in the gfx ressources file

					CL_VirtualFileSystem vfs(filename, true);
					CL_VirtualDirectory vd(vfs, "./");
					CL_ResourceManager gfx("general.xml", vd);					
					
					// Check if this skin is not aleady loaded
					bool found = false;
					for(unsigned int i = 0; i < _skins_list.size(); ++i)
					{
						if(_skins_list[i] -> filename == filename)
						{
							found = true;
							break;
						}
					}
					if(!found)
					{
						CL_Image logo = CL_Image(*_p_common_resources->p_gc, "logo", &gfx);
						Skin * p_skin = my_new Skin();
						p_skin -> filename = filename;
						p_skin -> element = 3;
						p_skin -> logo = logo;
						_skins_list.push_back(p_skin);
					}

				}
				catch(CL_Exception&)
				{
					std::cout << "Skin " << path << scanner.get_name().c_str() << 
						" is not valid." << std::endl;
				}
			}        

		}
	}
}

/************************************************************************/
/* Sort skins                                                           */
/************************************************************************/
void SkinsMenuState::_sort_skins()
{
	// Sorting skin list by alphabetical order (bubble sort)
	for(unsigned int i=0; i<_skins_list.size(); ++i)
	{
		for(unsigned int j=i+1; j<_skins_list.size(); ++j)
		{
			if(_skins_list[i]->filename.compare(_skins_list[j]->filename)>0)
			{
				Skin * p_sk = _skins_list[i];
				_skins_list[i] = _skins_list[j];
				_skins_list[j] = p_sk;
			}
		}
	}
}

/************************************************************************/
/* Save registred skins                                                 */
/************************************************************************/
void SkinsMenuState::_save_registred_skins()
{
	// Saving progression skin file
	std::string file_path = get_save_path() + get_path_separator() +
		"skins-" + get_version();
	try
	{
		CL_File file(file_path, CL_File::create_always, CL_File::access_write);
		for(unsigned int i = 0; i < _skins_list.size(); ++i)
		{
			file.write_string_a(_skins_list[i]->filename);
			file.write_uint8 (_skins_list[i]->element);  
		}
		file.close();

	}
	catch(CL_Exception&)
	{
		std::cout << "Error while reading " << file_path <<
			"file, probably doesn't exist yet." << std::endl;
	}
}