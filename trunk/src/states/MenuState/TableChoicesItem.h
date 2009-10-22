// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : TableChoicesItem.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _TABLE_CHOICES_ITEM_H_
#define _TABLE_CHOICES_ITEM_H_

#include "MenuItem.h"

class TableChoicesItem : public MenuItem{

public:

	TableChoicesItem();

	virtual void draw(CL_GraphicContext &gc);

	virtual void action_performed(ActionType action_type);

	virtual void mouse_moved(int mouse_x, int mouse_y);

	virtual bool quit_menu_on_action();

	virtual bool is_inside(int x, int y);

	/** Add a choice */
	void add_choice(CL_Image * p_image);

	/** Set choice enabled */
	void set_choice_enabled(unsigned int choice_index, bool enable);

	/** Set disabled choice */
	void set_disabled_choice(CL_GraphicContext & gc, CL_ResourceManager & gfx,
		std::string name);

	/** Set cursor */
	void set_cursor(CL_GraphicContext & gc,	CL_ResourceManager & gfx,
		std::string name);

	/** Set up arrow */
	void set_arrow_up(CL_GraphicContext & gc, CL_ResourceManager & gfx,
		std::string name);

	/** Set down arrow */
	void set_arrow_down(CL_GraphicContext & gc, CL_ResourceManager & gfx,
		std::string name);

	/** Set fields */
	inline void set_nb_cols(int nb_cols){ _nb_cols = nb_cols; }
	inline void set_nb_displayed_rows(int nb_rows){ _nb_displayed_rows = nb_rows; }
	inline void set_choice_width(int choice_width){ _choice_width = choice_width; }
	inline void set_choice_height(int choice_height){ _choice_height = choice_height; }
	inline void set_margin_width(int margin_width){ _choice_margin_width = margin_width; }
	inline void set_margin_height(int margin_height){ _choice_margin_height = margin_height; }
	inline void set_begin_x(int begin_x){ _begin_x = begin_x; }
	inline void set_begin_y(int begin_y){ _begin_y = begin_y; }
	inline void set_cursor_begin_x(int begin_x){ _cursor_begin_x = begin_x; }
	inline void set_cursor_begin_y(int begin_y){ _cursor_begin_y = begin_y; }
	inline void set_arrow_up_x(int x){ _arrow_up_x = x; }
	inline void set_arrow_up_y(int y){ _arrow_up_y = y; }
	inline void set_arrow_down_x(int x){ _arrow_down_x = x; }
	inline void set_arrow_down_y(int y){ _arrow_down_y = y; }

private:

	std::vector<CL_Image*> _choices;

	std::vector<bool> _choices_enabled;

	CL_Image _disabled_choice;

	CL_Sprite _cursor;

	CL_Sprite _arrow_up;

	CL_Sprite _arrow_down;

	int _nb_cols;

	int _nb_displayed_rows;

	int _nb_rows;

	int _choice_width;

	int _choice_height;

	int _choice_margin_width;

	int _choice_margin_height;

	int _cursor_col;

	int _cursor_row;

	int _begin_x;

	int _begin_y;

	int _cursor_begin_x;

	int _cursor_begin_y;

	int _arrow_up_x;

	int _arrow_up_y;

	int _arrow_down_x;

	int _arrow_down_y;

	int _scrolling_row;

	int _mouse_x;

	int _mouse_y;

	void _mouse_clicked();
};

#endif