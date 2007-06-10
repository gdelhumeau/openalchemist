/********************************************************************
                          OpenAlchemist

  File : Misc.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _MISC_H_
#define _MISC_H_

#include <string>
#include <sstream>  
#include <iostream>

#include <ClanLib/core.h>

/**
 * This function return a factor to calcul moving with time
 */
inline float get_time_interval(int fps)
{
  
  if(!fps)return 0;
  return 1000.0/((float)fps);
  
}

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
