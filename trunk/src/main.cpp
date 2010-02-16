// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : main.cpp
//  Description : Programme entry point
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include <ClanLib/application.h>
#include "Application.h"

int my_main(const std::vector<CL_String> & args)
{
	Application application;
	return application.main(args);	
}

CL_ClanApplication app(&my_main);
