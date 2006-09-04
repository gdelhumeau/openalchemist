/* OpenAlchemist - just a simple game 
 * ----------------------------------
 *
 * Copyright (C) 2006 Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
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

#ifndef _FRONTLAYER_H_
#define _FRONTLAYER_H_

class FrontLayerSprite{

  public:
  CL_Sprite *sprite;
  u_int left, top;

};


class FrontLayer{

  public:
  bool enabled;
  
  std::list<FrontLayerSprite*> list;
  void load_gfx(CL_Zip_Archive *zip);
  void load_gfx(CL_ResourceManager *gfx_frontlayer);
  void unload_gfx();
  void draw();

};

#endif