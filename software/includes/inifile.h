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

#ifndef _INIFILE_H_
#define _INIFILE_H_

#include "headers.h"

class IniElement{
  
  public:
  std::string name;
  std::string value;
  
};



class IniFile{

  std::list<IniElement*> list;

  public:

  void read(CL_InputSource_File *file);
  void write(CL_OutputSource_File *file);
  void clear();

  void add(std::string name, std::string value);

  void add(std::string name, bool value);

  void add(std::string name, int value);

    std::string get(std::string name, std::string def);

  bool get(std::string name, bool def);

  int get(std::string name, int def);

  
  

};

#endif
