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

#ifndef _PREFERENCES_H_
#define _PREFREENCES_H_

#include "headers.h"

class Preferences
{

  public:
  short revision;

  // Render
  bool render_opengl;

  // FPS
  int maxfps;
  
  // Sounds
  int sound_level;
  int music_level;

  // Fullscreen
  bool fullscreen;

  // Color Blind
  bool colorblind;

  // Skin
  std::string skin;

  Preferences();
  void read();
  void write();

  private:
  void read_options_file(CL_InputSource_File *file);
  void write_options_file(CL_OutputSource_File *file);
  void set_default();


};


std::string get_save_path();
Preferences* pref_get_instance();

#endif
