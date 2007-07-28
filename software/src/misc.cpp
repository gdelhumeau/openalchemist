/********************************************************************
                          OpenAlchemist

  File : misc.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include "misc.h"

/**
 * Convert a CL_Integer to a int
 */
int CL_Integer_to_int(const std::string &ressource_name, CL_ResourceManager *gfx)
{    
  CL_Integer *cl_int = new CL_Integer(ressource_name, gfx);
  int to_return = (int)*cl_int;
  delete cl_int;
  return to_return;
}

/**
 * Convert a CL_Boolean to a boolean
 */
int CL_Boolean_to_bool(const std::string &ressource_name, CL_ResourceManager *gfx)
{    
  CL_Boolean *cl_bool = new CL_Boolean(ressource_name, gfx);
  bool to_return = (bool)*cl_bool;
  delete cl_bool;
  return to_return;
}

std::string get_save_path()
{
#ifdef WIN32
  return CL_System::get_exe_path() + "\\savedata";
#else
  return ((std::string)getenv("HOME")) + "/.openalchemist";
#endif
}
