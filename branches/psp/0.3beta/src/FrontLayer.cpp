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
#include "IniFile.h"
#include "psp_sdl.h"

FrontLayerSprite::FrontLayerSprite()
{
	this->sprite = NULL;
}

void FrontLayer::load_gfx(std::string skin)
{
//  CL_Zip_Archive zip(skin);

  // Look if frontlayer.xml is existing
/*  enabled = false;
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
  }*/
  FILE * frontLayerIniHandle;
  std::string frontLayerIni = "skins/" + skin + "/frontlayer.ini";
  frontLayerIniHandle = fopen(frontLayerIni.c_str(), "r");
  if (frontLayerIniHandle != NULL)
  {
     printf("------------> we could open frontlayer ini \n");
     load_gfx(frontLayerIniHandle, skin);
     enabled = true;
  }
  else
  {
     enabled = false;
  }
}


void FrontLayer::load_gfx(FILE* FrontLayerIniFile, std::string skin)
{

  IniFile front_layer_resources;
  front_layer_resources.read(FrontLayerIniFile);

  int number = front_layer_resources.get("nb_sprites", 0);
  
  list.clear();
  char image_name[256];
  char coord_name[256];
  for(int i=1; i<=number; ++i)
  {
    FrontLayerSprite *fsprite = new FrontLayerSprite();
    sprintf(image_name,"pic%d", i);
    std::string image = front_layer_resources.get(std::string(image_name),std::string("toto"));
    printf("image = %s\n", image.c_str());
    fsprite -> sprite = IMG_Load_fromSkin(skin, (char*)image.c_str());
    sprintf(coord_name,"%dx", i);
    fsprite -> left = front_layer_resources.get(std::string(coord_name),0);
    sprintf(coord_name,"%dy", i);
    fsprite -> top = front_layer_resources.get(std::string(coord_name),0);
    list.insert(list.end(), fsprite);
  }
}

void FrontLayer::unload_gfx()
{

  std::list<FrontLayerSprite*>::iterator it = list.begin();
  while(!list.empty())
  {//TODO
    //SDL_FreeSurface(it->sprite);
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
    psp_sdl_blit_on_screen_at_XY(fsprite -> sprite, fsprite -> left, fsprite -> top);
    printf ("draw element frontlayer at x: %d, y: %d\n", fsprite -> left, fsprite -> top);
    it++;
  }
}
