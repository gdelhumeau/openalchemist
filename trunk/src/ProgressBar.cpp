// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : ProgressBar.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include "ProgressBar.h"
#include "misc.h"
#include "memory.h"

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
ProgressBar::ProgressBar()
{
}

/************************************************************************/
/* Destructor                                                           */
/************************************************************************/
ProgressBar::~ProgressBar()
{
	unload_gfx();
}

/************************************************************************/
/* Load GFX                                                             */
/************************************************************************/
void ProgressBar::load_gfx(CL_GraphicContext & gc, std::string skin)
{
	unload_gfx();

	// Getting skins resources
	CL_VirtualFileSystem vfs(skin, true);
	CL_VirtualDirectory vd(vfs, "./");
	CL_ResourceManager gfx("progress_bar.xml", vd);


	_head     = CL_Sprite(gc, "progress_bar/head/sprite",    &gfx);
	_head_ok  = CL_Sprite(gc, "progress_bar/head/sprite_ok", &gfx);
	_foot     = CL_Sprite(gc, "progress_bar/foot/sprite",    &gfx);
	_item     = CL_Sprite(gc, "progress_bar/item/sprite",    &gfx);
	_item_ok  = CL_Sprite(gc, "progress_bar/item/sprite_ok", &gfx);

	_left     = CL_Integer_to_int("progress_bar/left",       &gfx);
	_head_top = CL_Integer_to_int("progress_bar/head/top",   &gfx);
	_foot_top = CL_Integer_to_int("progress_bar/foot/top",   &gfx);

}

/************************************************************************/
/* Unload GFX                                                           */
/************************************************************************/
void ProgressBar::unload_gfx()
{

}

/************************************************************************/
/* Draw                                                                 */
/************************************************************************/
void ProgressBar::draw(CL_GraphicContext & gc, int percentage)
{
	int head_height = _head.get_height();
	int height = _foot_top - (_head_top + head_height);

	/*if(hightscores[current_difficulty] > 0)
	v = height * (global_score + global_bonus) / hightscores[current_difficulty];*/

	int v = height * percentage / 100;
	if(v > height) v = height;

	for(int i=0; i<=height; ++i)
	{
		if(height - i < v)
			_item_ok.draw(gc, _left, _head_top+head_height+i-1);
		else
			_item.draw(gc, _left, _head_top+head_height+i-1);
	}
	_item.update();
	_item_ok.update();

	if(percentage < 100)
	{
		_head.draw(gc, _left, _head_top);
		_head.update();
	}
	else
	{
		_head_ok.draw(gc, _left, _head_top);
		_head_ok.update();
	}
	_foot.draw(gc, _left, _foot_top);
	_foot.update();
}
