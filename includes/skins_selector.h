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

#ifndef _SKINS_SELECTOR_H_
#define _SKINS_SELECTOR_H_

class SkinsPropreties{
  public:
  std::string filename;
  u_int element; 
};

class SkinsSelector{

  public:
  CL_Sprite *menu;
  CL_Sprite *cant_change_skin;
  std::vector<std::string> list;
  std::vector<CL_Surface*> logo_list;
  int number;
  int current_selection;
  int list_index_top;
  int top;
  int separation;

  bool display_cant_change;

  /* About limitations */
  std::vector<SkinsPropreties*> propreties_list;

  void read_file();
  void set_skin_value(std::string skin, int value);
  void write_file();
  void load_gfx(CL_ResourceManager *gfx);
  void unload_gfx();


};

#endif
