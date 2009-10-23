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

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
TableChoicesItem::TableChoicesItem()
{
	_nb_cols = 2;
	_nb_displayed_rows = 2;
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
	_scrolling_row = 0;
	_mouse_x = 0;
	_mouse_y = 0;
	_p_parent = NULL;
}

/************************************************************************/
/* Add choice                                                           */
/************************************************************************/
void TableChoicesItem::add_choice(CL_Image * p_image)	
{
	_choices.push_back(p_image);
	_choices_enabled.push_back(true);
}

/************************************************************************/
/* Set cursor                                                           */
/************************************************************************/
void TableChoicesItem::set_cursor(CL_GraphicContext & gc,
				CL_ResourceManager & gfx,
				std::string name)
{
	_cursor = CL_Sprite(gc, name, &gfx);
}

/************************************************************************/
/* Set arrow up                                                         */
/************************************************************************/
void TableChoicesItem::set_arrow_up(CL_GraphicContext & gc,
									CL_ResourceManager & gfx,
									std::string name)
{
	_arrow_up = CL_Sprite(gc, name, &gfx);
}

/************************************************************************/
/* Set arrow down                                                       */
/************************************************************************/
void TableChoicesItem::set_arrow_down(CL_GraphicContext & gc,
									  CL_ResourceManager & gfx,
									  std::string name)
{
	_arrow_down = CL_Sprite(gc, name, &gfx);
}

/************************************************************************/
/* Set disabled choice                                                  */
/************************************************************************/
void TableChoicesItem::set_disabled_choice(CL_GraphicContext & gc, 
										   CL_ResourceManager & gfx,
										   std::string name)
{
	_disabled_choice = CL_Image(gc, name, &gfx);
}

/************************************************************************/
/* Set choice enabled                                                   */
/************************************************************************/
void TableChoicesItem::set_choice_enabled(unsigned int choice_index, bool enable)
{
	if(choice_index < _choices_enabled.size())
	{
		_choices_enabled[choice_index] = enable;
	}
}

/************************************************************************/
/* Draw                                                                 */
/************************************************************************/
void TableChoicesItem::draw(CL_GraphicContext &gc)
{
	_disabled_choice.set_alpha(_alpha);
	for(unsigned int i=0; i<_choices.size(); ++i)
	{
		int row = i / _nb_cols;
		int col = i % _nb_cols;

		if(row >= _scrolling_row && row < _scrolling_row + _nb_displayed_rows)
		{
			int x = _begin_x + col*(_choice_width+_choice_margin_width);
			int y = _begin_y + (row-_scrolling_row)*(_choice_height+_choice_margin_height);

			_choices[i]->set_alpha(_alpha);
			_choices[i]->draw(gc, x, y);
			if(!_choices_enabled[i])
			{
				_disabled_choice.draw(gc, x, y);
			}
		}
	}

	_arrow_up.set_alpha(_alpha);
	_arrow_down.set_alpha(_alpha);
	_arrow_up.draw(gc, _arrow_up_x, _arrow_up_y);
	_arrow_down.draw(gc, _arrow_down_x, _arrow_down_y);

	// Cursor
	int x = _begin_x + _cursor_col * (_choice_width+_choice_margin_width)
		+ _choice_width/2 - _cursor.get_width()/2;
	int y = _begin_y + (_cursor_row-_scrolling_row) * (_choice_height+_choice_margin_height)
		+_choice_height/2 - _cursor.get_height()/2;
	_cursor.set_alpha(_alpha);
	_cursor.draw(gc, x, y);
}

/************************************************************************/
/* Action performed                                                     */
/************************************************************************/
void TableChoicesItem::action_performed(ActionType action_type)
{
	// Compute number of rows
	_nb_rows = (int) ceil((float)_choices.size() / (float)_nb_cols);

	// Manage action
	switch(action_type)
	{
	case ACTION_TYPE_LEFT:
		if(_cursor_col > 0)
			_cursor_col--;
		break;
	case ACTION_TYPE_RIGHT:
		if(_cursor_col < _nb_cols - 1)
			_cursor_col++;
		break;
	case ACTION_TYPE_UP:
		if(_cursor_row > 0)
			_cursor_row--;
		if(_cursor_row < _scrolling_row)
			_scrolling_row--;
		break;
	case ACTION_TYPE_DOWN:
		if(_cursor_row < _nb_rows - 1)
			_cursor_row++;
		if(_cursor_row >= _scrolling_row + _nb_displayed_rows)
			_scrolling_row++;
		break;
	case ACTION_TYPE_MOUSE:
		_mouse_clicked();
		break;
	case ACTION_TYPE_ENTER:
		if(_p_parent)
		{
			int choice = _cursor_row * _nb_cols + _cursor_col;
			if(_choices_enabled[choice])
			{			
				_p_parent -> choice_selected(choice);
			}
		}
		break;
	}

	// If the cursor position changed and is on the last row
	if(_cursor_row == _nb_rows - 1)
	{
		// Maybe the row is not full
		int nb_elems = _choices.size() % _nb_cols;
		if(nb_elems>0 && _cursor_col >= nb_elems)
		{
			_cursor_col = nb_elems - 1;
		}
	}
}

/************************************************************************/
/* Mouse clicked                                                        */
/************************************************************************/
void TableChoicesItem::_mouse_clicked()
{
	// Arrow UP
	if(_mouse_x >= _arrow_up_x && _mouse_x <= _arrow_up_x + _arrow_up.get_width()
		&& _mouse_y >= _arrow_up_y && _mouse_y <= _arrow_up_y + _arrow_up.get_height())
	{
		if(_scrolling_row > 0)
			_scrolling_row --;

		if(_cursor_row >= _scrolling_row + _nb_displayed_rows)
			_cursor_row--;

		return;
	}

	// Arrow Down
	if(_mouse_x >= _arrow_down_x && _mouse_x <= _arrow_down_x + _arrow_down.get_width()
		&& _mouse_y >= _arrow_down_y && _mouse_y <= _arrow_down_y + _arrow_down.get_height())
	{
		if(_scrolling_row + _nb_displayed_rows < _nb_rows)
		{
			_scrolling_row++;
			if(_cursor_row < _scrolling_row)
			{
				_cursor_row++;
			}
		}

		return;
	}

	// Else ;)
	for(unsigned int i=0; i<_choices.size(); ++i)
	{
		int row = i / _nb_cols;
		int col = i % _nb_cols;

		if(row >= _scrolling_row && row < _scrolling_row + _nb_displayed_rows)
		{
			int x = _begin_x + col*(_choice_width+_choice_margin_width);
			int y = _begin_y + (row-_scrolling_row)*(_choice_height+_choice_margin_height);

			if(_mouse_x >= x && _mouse_x <= x + _choice_width 
				&& _mouse_y >= y && _mouse_y <= y + _choice_height)
			{
				_cursor_col = col;
				_cursor_row = row;
				action_performed(ACTION_TYPE_ENTER);
				return;
			}
		}
	}
}

/************************************************************************/
/* Mouse moved                                                          */
/************************************************************************/
void TableChoicesItem::mouse_moved(int mouse_x, int mouse_y)
{
	_mouse_x = mouse_x;
	_mouse_y = mouse_y;

	for(unsigned int i=0; i<_choices.size(); ++i)
	{
		int row = i / _nb_cols;
		int col = i % _nb_cols;

		if(row >= _scrolling_row && row < _scrolling_row + _nb_displayed_rows)
		{
			int x = _begin_x + col*(_choice_width+_choice_margin_width);
			int y = _begin_y + (row-_scrolling_row)*(_choice_height+_choice_margin_height);

			if(_mouse_x >= x && _mouse_x <= x + _choice_width 
				&& _mouse_y >= y && _mouse_y <= y + _choice_height)
			{
				_cursor_col = col;
				_cursor_row = row;
			}
		}
	}
}

/************************************************************************/
/* Quit menu on action                                                  */
/************************************************************************/
bool TableChoicesItem::quit_menu_on_action()
{
	return false;
}

/************************************************************************/
/* Is inside                                                            */
/************************************************************************/
bool TableChoicesItem::is_inside(int x, int y)
{
	return true;
}
