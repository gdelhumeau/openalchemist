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
 * This function return the current version name
 */
std::string get_version();

/**
 * This function return a factor to calcul moving with time
 */
inline double get_time_interval(int fps)
{
	static unsigned int last_time = 0;

	unsigned int delta_time = CL_System::get_time() - last_time;

	last_time += delta_time;

	if(fps == 0)
	{
		return delta_time;
	}

	double fps_normal_time = 1000.0/((double)fps);

	if(delta_time > fps_normal_time * 1.1 || delta_time < fps_normal_time * 0.9)
	{
		return delta_time;
	}	
	
	return fps_normal_time;
  
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
  int length = (int)string.length();
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
 * Returning save path 
 */
std::string get_save_path();

std::string get_skins_path();

std::string get_data_path();

std::string get_path_separator();


/**
 * Convert a CL_Integer to a int
 */
int CL_Integer_to_int(const std::string &ressource_name, CL_ResourceManager *gfx);

/**
 * Convert a CL_Boolean to a boolean
 */
int CL_Boolean_to_bool(const std::string &ressource_name, CL_ResourceManager *gfx);




#endif
