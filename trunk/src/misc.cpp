// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : misc.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include <cstdlib>
#include "misc.h"
#include "memory.h"

/************************************************************************/
/* Get version                                                          */
/************************************************************************/
std::string get_version()
{
	return "svn";
}

/************************************************************************/
/* CL_Integer to int                                                    */
/************************************************************************/
int CL_Integer_to_int(const std::string &ressource_name, CL_ResourceManager *gfx)
{    
	return gfx->get_integer_resource(ressource_name, 0);
}

/************************************************************************/
/* CL_Boolean to bool                                                   */
/************************************************************************/
int CL_Boolean_to_bool(const std::string &ressource_name, CL_ResourceManager *gfx)
{    
	return gfx->get_boolean_resource(ressource_name, false);
}

/************************************************************************/
/* Get save path                                                        */
/************************************************************************/
std::string get_save_path()
{
#ifdef WIN32
#ifdef PORTABLE_APP
	return CL_System::get_exe_path() + "\\savedata";
#else
	if(getenv("APPDATA") != NULL)
		return ((std::string)getenv("APPDATA")) + "\\OpenAlchemist";
	else
		return CL_System::get_exe_path() + "\\savedata";
#endif
#else
	return ((std::string)getenv("HOME")) + get_path_separator() + ".openalchemist";
#endif
}

/************************************************************************/
/* Get skin path                                                        */
/************************************************************************/
std::string get_skins_path()
{
#ifdef DATA_DIR
	std::string dir = DATA_DIR;
#else
	std::string dir = CL_System::get_exe_path();
	dir += "skins";
#endif

	return dir;
}

/************************************************************************/
/* Get user skin path                                                   */
/************************************************************************/
std::string get_user_skins_path()
{
	std::string dir = get_save_path();
	dir += "skins" + get_path_separator();
	return dir;	
}

/************************************************************************/
/* Get data path                                                        */
/************************************************************************/
std::string get_data_path()
{
#ifdef WIN32
	std::string file_path = CL_System::get_exe_path() + "data\\";
#else
#ifdef DATA_DIR
	std::string file_path = DATA_DIR;
	file_path += "/";
#else
	std::string file_path = CL_System::get_exe_path() + "data/";
#endif
#endif
	return file_path;
}

/************************************************************************/
/* Get path separator                                                   */
/************************************************************************/
std::string get_path_separator()
{
#ifdef WIN32
	return "\\";
#else
	return "/";
#endif
}
