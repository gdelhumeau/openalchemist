// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : Application.h
//  Description : Application main class
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <ClanLib/core.h>
#include <ClanLib/application.h>

class Application{

public:

	/**
	* Application main function
	*/
	int main(const std::vector<CL_String> &args);

private:

	/** 
	* Instance needed to use ClanLib
	*/
	CL_SetupCore _setup_core;

	/** 
	* Initialize application
	*/
	void _init();

	/** 
	* Terminate application
	*/
	void _term();

	/**
	* Check command lines arguments
	*/
	bool _check_args(const std::vector<CL_String> &args);

	/**
	* Display the help informations
	*/
	void _print_help();

	/**
	* Display the license
	*/
	void _print_license();

};

#endif
