// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : ProgressBar.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _PROGRESS_BAR_H_
#define _PROGRESS_BAR_H_

#include <ClanLib/core.h>
#include <ClanLib/display.h>

/**
* Progress Bar class
*/
class ProgressBar{

private:
	
	/**
	* Sprites for progress bar
	*/
	CL_Sprite _head, _head_ok;
	CL_Sprite _foot;
	CL_Sprite _item, _item_ok;

	/**
	* Progress bar coords
	*/
	int _left, _head_top, _foot_top;

public:

	/**
	* Constructor
	*/
	ProgressBar();

	/**
	* Destructor
	*/
	~ProgressBar();

	/**
	* Loading GFX
	*/
	void load_gfx(CL_GraphicContext & gc, std::string skin);

	/**
	* Unloading GFX
	*/
	void unload_gfx();

	/**
	* Drawing the percentage bar
	*/
	void draw(CL_GraphicContext & gc, int percentage);

};


#endif
