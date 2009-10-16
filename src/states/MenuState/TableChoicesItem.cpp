// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : TableChoicesItem.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include "TableChoicesItem.h"

TableChoicesItem::TableChoicesItem()
{
	_nb_cols = 2;
	_nb_rows = 0;
	_choice_width = 0;
	_choice_height = 0;
	_choice_margin_width = 0;
	_choice_margin_height = 0;
	_cursor_col = 0;
	_cursor_row = 0;
	_begin_x = 0;
	_begin_y = 0;
	_arrow_up_x = 0;
	_arrow_up_y = 0;
	_arrow_down_x = 0;
	_arrow_down_y = 0;
}

void TableChoicesItem::add_choice(CL_Image * p_image)	
{
	_choices.push_back(p_image);
}

void TableChoicesItem::set_cursor(CL_GraphicContext & gc,
				CL_ResourceManager & gfx,
				std::string name)
{
	_cursor = CL_Sprite(gc, name, &gfx);
}

void TableChoicesItem::set_arrow_up(CL_GraphicContext & gc,
									CL_ResourceManager & gfx,
									std::string name)
{
	_arrow_up = CL_Sprite(gc, name, &gfx);
}

void TableChoicesItem::set_arrow_down(CL_GraphicContext & gc,
									  CL_ResourceManager & gfx,
									  std::string name)
{
	_arrow_down = CL_Sprite(gc, name, &gfx);
}

void TableChoicesItem::draw(CL_GraphicContext &gc)
{
	for(unsigned int i=0; i<_choices.size(); ++i)
	{
		int row = i / _nb_cols;
		int col = i % _nb_cols;
		int x = _begin_x + col*(_choice_width+_choice_margin_width);
		int y = _begin_y + row*(_choice_height+_choice_margin_height);

		_choices[i]->set_alpha(_alpha);
		_choices[i]->draw(gc, (float)x, (float)y);
	}

	_arrow_up.set_alpha(_alpha);
	_arrow_down.set_alpha(_alpha);
	_arrow_up.draw(gc, (float)_arrow_up_x, (float)_arrow_up_y);
	_arrow_down.draw(gc, (float)_arrow_down_x, (float)_arrow_down_y);
}

void TableChoicesItem::action_performed(ActionType action_type)
{

}

void TableChoicesItem::mouse_moved(int mouse_x, int mouse_y)
{

}

bool TableChoicesItem::quit_menu_on_action()
{
	return false;
}

bool TableChoicesItem::is_inside(int x, int y)
{
	return true;
}