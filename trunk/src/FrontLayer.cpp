// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : FrontLayer.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include <list>
#include "FrontLayer.h"
#include "misc.h"
#include "memory.h"

/************************************************************************/
/* Load GFX                                                             */
/************************************************************************/
void FrontLayer::load_gfx(CL_GraphicContext & gc, std::string skin)
{
	unload_gfx();
	CL_ZipArchive zip(skin);

	// Look if frontlayer.xml is existing
	is_enabled = false;
	std::vector<CL_ZipFileEntry> file_list = zip.get_file_list();
	for(unsigned int i=0; i<file_list.size(); ++i)
	{
		if(file_list[i].get_archive_filename() == "frontlayer.xml")
			is_enabled = true;      
	}

	if(is_enabled)
	{   
		CL_VirtualFileSystem vfs(skin, true);
		CL_VirtualDirectory vd(vfs, "./");
		CL_ResourceManager gfx_frontlayer("frontlayer.xml", vd);
		_load_gfx(gc, &gfx_frontlayer);
	} 

}

/************************************************************************/
/* Load GFX                                                             */
/************************************************************************/
void FrontLayer::_load_gfx(CL_GraphicContext & gc, CL_ResourceManager *gfx_frontlayer)
{
	unload_gfx();

	int number = CL_Integer_to_int("frontlayer/number_of_sprites", gfx_frontlayer);
	for(int i=1; i<=number; ++i)
	{
		FrontLayerSprite *fsprite = my_new FrontLayerSprite();
		fsprite -> _sprite = CL_Sprite(gc, "frontlayer/"+to_string(i)+"/sprite", gfx_frontlayer);
		fsprite -> left = CL_Integer_to_int("frontlayer/"+to_string(i)+"/left", gfx_frontlayer);
		fsprite -> top = CL_Integer_to_int("frontlayer/"+to_string(i)+"/top", gfx_frontlayer);
		list.insert(list.end(), fsprite);
	}
}

/************************************************************************/
/* Unload GFX                                                           */
/************************************************************************/
void FrontLayer::unload_gfx()
{
	std::list<FrontLayerSprite*>::iterator it = list.begin();
	while(!list.empty())
	{
		my_delete(*it);
		it = list.erase(it);
	}

	is_enabled = false;
	list.clear();
}

/************************************************************************/
/* Draw                                                                 */
/************************************************************************/
void FrontLayer::draw(CL_GraphicContext & gc)
{
	std::list<FrontLayerSprite*>::iterator it = list.begin();
	while(it != list.end())
	{
		FrontLayerSprite *fsprite = (FrontLayerSprite*)*it;
		fsprite -> _sprite.draw(gc, fsprite -> left, fsprite -> top);
		fsprite -> _sprite.update();
		it++;
	}
}