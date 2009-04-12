/* OpenAlchemist - just a simple game 
 * ----------------------------------
 *
 * Copyright (C) 2005, 2006 Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "FrontLayer.h"
#include "misc.h"

void FrontLayer::load_gfx(std::string skin)
{
//  CL_Zip_Archive zip(skin);

  // Look if frontlayer.xml is existing
  enabled = false;
  std::vector<CL_Zip_FileEntry> file_list = zip.get_file_list();
  for(u_int i=0; i<file_list.size(); ++i)
  {
    if(file_list[i].get_filename() == "frontlayer.xml")
      enabled = true;      
  }

  if(enabled)
  {   
    CL_ResourceManager gfx_frontlayer("frontlayer.xml", &zip, false);
    load_gfx(&gfx_frontlayer);
  } 

}


void FrontLayer::load_gfx(CL_ResourceManager *gfx_frontlayer)
{

  int number = CL_Integer_to_int("frontlayer/number_of_sprites", gfx_frontlayer);
  
  list.clear();
  
  for(int i=1; i<=number; ++i)
  {
    FrontLayerSprite *fsprite = new FrontLayerSprite();
    fsprite -> sprite = IMG_Load_fromSkin(skin, "frontlayer/"+to_string(i)+"/sprite", gfx_frontlayer);
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
    delete *it;
    it = list.erase(it);
  }

  enabled = false;

}

void FrontLayer::draw()
{
  std::list<FrontLayerSprite*>::iterator it = list.begin();
  while(it != list.end())
  {
    FrontLayerSprite *fsprite = (FrontLayerSprite*)*it;
    fsprite -> sprite -> draw(fsprite -> left, fsprite -> top);
    fsprite -> sprite -> update();
    it++;
  }
}
