// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : misc.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _MISC_H_
#define _MISC_H_

#include <string>
#include <sstream>  
#include <iostream>
#include <ClanLib/core.h>

#ifndef WIN32
#include <stdint.h>
#endif

/** This function return the current version name */
std::string get_version();

/** This function return a factor to compute move with time */
inline float get_time_interval(int fps)
{
	static unsigned int last_time = 0;
	unsigned int delta_time = CL_System::get_time() - last_time;
	last_time += delta_time;

	if(fps == 0)
	{
		return (float)delta_time;
	}

	float fps_normal_time = 1000.0f/((float)fps);
	if(delta_time > fps_normal_time * 1.1 || delta_time < fps_normal_time * 0.9)
	{
		return (float)delta_time;
	}	

	return fps_normal_time;
}

/** Cast everything to string */
template<typename T>
inline std::string to_string( const T & Value )
{

	std::ostringstream oss;

	oss << Value;

	return oss.str();
}

/** Format number like 000.000.000 */
inline std::string format_number(const std::string& string)
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

/** Returning save path */
std::string get_save_path();

/** Returning skins path */
std::string get_skins_path();

/** Returning user skins path */
std::string get_user_skins_path();

/** Returning data path */
std::string get_data_path();

/** Returning music path */
std::string get_music_path();

/** Returning sounds path */
std::string get_sounds_path();

/** Returning path separator ("/" or "\\" - thx to Windows.) */
std::string get_path_separator();

/** Convert a CL_Integer to a int */
int CL_Integer_to_int(const std::string& ressource_name, CL_ResourceManager* p_gfx);

/** Convert a CL_Boolean to a boolean */
int CL_Boolean_to_bool(const std::string& ressource_name, CL_ResourceManager* p_gfx);

/** Custom random number generator (be sure it's the same on all platforms) */
#ifdef WIN32
typedef unsigned __int32 RandomSeed;
#else
typedef uint32_t RandomSeed;
#endif
inline int random_int(int min, int max, RandomSeed& random_seed)
{
	// Change random seed
	random_seed = random_seed * 214013L + 2531011L;
	// Compute random number
	int rand = (random_seed >> 16) & 0x7fff;
	// Apply range
	return min + rand % (max - min);
}

#endif
