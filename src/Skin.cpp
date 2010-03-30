// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : Skin.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include "Skin.h"
#include "CommonResources.h"

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
Skin::Skin(std::string filename, CL_GraphicContext& gc)
{
	_filename = filename;
	_element = 3;

	// We load the logo sprite in the gfx ressources file
	CL_VirtualFileSystem vfs(filename, true);
	CL_VirtualDirectory vd(vfs, "./");
	CL_ResourceManager gfx("general.xml", vd);
	_logo = CL_Image(gc, "logo", &gfx);
}