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

/**
 * This class represent the skin selector menu
 */
class SkinsSelector{

  public:
  /** Sprite witch contains the menu background */
  CL_Sprite *menu;
  /** Dialogs when you can't change the skin */
  CL_Sprite *cant_change_skin;
  /** Skins filename list */
  std::vector<std::string> list;
  /** Logos of the skin list */
  std::vector<CL_Surface*> logo_list;
  /** Number of skins scanning in the /skins folder */
  int number;
  /** Current skin index */
  int current_selection;
  /** Top index of the list displaying (english to correct)*/
  int list_index_top;
  /** Y coord of the menu */
  int top;
  /** Y seperatation between the skin logos */
  int separation;

  /** To know if we have to show the "can't change skin" message */
  bool display_cant_change;

  /** Skins propreties list (read in the .openalchemist/skins file) */
  std::vector<SkinsPropreties*> propreties_list;

  SkinsSelector();
  void read_file();
  void set_skin_value(std::string skin, int value);
  void write_file();
  void load_gfx(CL_ResourceManager *gfx);
  void unload_gfx();


};

#endif
