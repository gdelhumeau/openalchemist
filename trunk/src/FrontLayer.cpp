/********************************************************************
                          OpenAlchemist

  File : FrontLayer.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include "FrontLayer.h"
#include "misc.h"
#include "memory.h"

void FrontLayer::load_gfx(std::string skin)
{
	unload_gfx();
	
  CL_Zip_Archive zip(skin);

  // Look if frontlayer.xml is existing
  is_enabled = false;
  std::vector<CL_Zip_FileEntry> file_list = zip.get_file_list();
  for(u_int i=0; i<file_list.size(); ++i)
  {
    if(file_list[i].get_filename() == "frontlayer.xml")
      is_enabled = true;      
  }

  if(is_enabled)
  {   
    CL_ResourceManager gfx_frontlayer("frontlayer.xml", &zip, false);
    _load_gfx(&gfx_frontlayer);
  } 

}


void FrontLayer::_load_gfx(CL_ResourceManager *gfx_frontlayer)
{

	unload_gfx();
	
  int number = CL_Integer_to_int("frontlayer/number_of_sprites", gfx_frontlayer);
 
  
  for(int i=1; i<=number; ++i)
  {
    FrontLayerSprite *fsprite = my_new FrontLayerSprite();
    fsprite -> p_sprite = my_new CL_Sprite("frontlayer/"+to_string(i)+"/sprite", gfx_frontlayer);
    fsprite -> left = CL_Integer_to_int("frontlayer/"+to_string(i)+"/left", gfx_frontlayer);
    fsprite -> top = CL_Integer_to_int("frontlayer/"+to_string(i)+"/top", gfx_frontlayer);
    list.insert(list.end(), fsprite);
  }
}

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

void FrontLayer::draw()
{
  std::list<FrontLayerSprite*>::iterator it = list.begin();
  while(it != list.end())
  {
    FrontLayerSprite *fsprite = (FrontLayerSprite*)*it;
    fsprite -> p_sprite -> draw(fsprite -> left, fsprite -> top);
    fsprite -> p_sprite -> update();
    it++;
  }
}
