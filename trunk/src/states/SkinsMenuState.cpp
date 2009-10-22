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
#include "../GameEngine.h"

/************************************************************************/
/* Constants                                                            */
/************************************************************************/
static const int LOGO_WIDTH = 200;
static const int LOGO_HEIGHT = 150;
static const int NB_COLS = 2;
static const int NB_ROWS = 2;

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
SkinsMenuState::SkinsMenuState()
{
	_skin_chooser.set_parent(this);
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

	SkinsManager & skins_manager = _p_common_resources->p_engine->get_skins_manager();
	for(unsigned int i=0; i<skins_manager.get_nb_skins(); ++i)
	{
		_skin_chooser.add_choice(&skins_manager.get_skin(i)->get_logo());
	}
}

/************************************************************************/
/* Term                                                                 */
/************************************************************************/
void SkinsMenuState::term()
{
	
}

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
	
	_skin_chooser.set_disabled_choice(gc, gfx, "menu_skins/logo_unavailable");
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
	_skin_chooser.set_nb_cols(NB_ROWS);	


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
	SkinsManager & skins_manager = _p_common_resources->p_engine->get_skins_manager();
	for(unsigned int i=0; i<skins_manager.get_nb_skins(); ++i)
	{
		bool skin_enabled = skins_manager.get_skin(i)->get_unlocked_elements() >= 
			(unsigned int) _p_common_resources->player1.get_visible_pieces();

		_skin_chooser.set_choice_enabled(i, skin_enabled);
	}
}

/************************************************************************/
/* Choice selected                                                      */
/************************************************************************/
void SkinsMenuState::choice_selected(int choice)
{
	SkinsManager & skins_manager = _p_common_resources->p_engine->get_skins_manager();
	Skin * p_skin = skins_manager.get_skin(choice);
	if(_p_common_resources->skin != p_skin->get_filename())
	{
		_p_common_resources->p_engine->set_skin(p_skin->get_filename());
	}
}