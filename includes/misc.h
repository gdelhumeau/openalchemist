/* OpenAlchemist - just a simple game 
 * ----------------------------------
 *
 * Copyright (C) 2005 Guillaume Delhumeau <guillaume.delhumeau at laposte.net>
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

#ifndef _MISC_H_
#define _MISC_H_

#include <string>
#include <sstream>  
#include <iostream>

template<typename T>
inline std::string to_string( const T & Value )
{
    
    std::ostringstream oss;
    
    oss << Value;
    
    return oss.str();
}

inline std::string format_number(const std::string &string)
{
  int length = string.length();
  std::string string_modified = "";
  for(int i = 0; i<length; ++i)
  {
    if((length - i) % 3 == 0 && i>0)
    {
      string_modified += ".";
    }
    string_modified += string.substr(i,1);
  }
  return string_modified;
}


/**
 * Convert a CL_Integer to a int
 */
int CL_Integer_to_int(const std::string &ressource_name, CL_ResourceManager *gfx);

/**
 * Convert a CL_Boolean to a boolean
 */
int CL_Boolean_to_bool(const std::string &ressource_name, CL_ResourceManager *gfx);




#endif
