// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : IniFile.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _INIFILE_H_
#define _INIFILE_H_

#include <list>
#include <ClanLib/core.h>

/** Ini variable */
class IniElement{

public:
	/** Variable name */
	std::string name;

	/** Variable value */
	std::string value;

};


/** INI file (to save preferences) */
class IniFile{

public:

	/** Constructor */
	IniFile();
	
	/** Destructor */
	~IniFile();

	/** Read file */
	void read(CL_File* p_file);

	/** Write file */
	void write(CL_File* p_file);

	/** Clear variables */
	void clear();

	/** Add a string variable */
	void add(std::string name, std::string value);

	/** Add a boolean variable */
	void add(std::string name, bool value);

	/** Add an integer variable */
	void add(std::string name, int value);

	/** Get a string variable value */
	std::string get(std::string name, std::string default_value);

	/** Get a boolean variable value */
	bool get(std::string name, bool default_value);

	/** Get an integer variable value */
	int get(std::string name, int default_value);

private:
	
	/** Variables list */
	std::list<IniElement*> _list;

};

#endif
