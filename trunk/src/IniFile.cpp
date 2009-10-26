// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : IniFile.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include <ClanLib/core.h>
#include "IniFile.h"
#include "memory.h"

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
IniFile::IniFile()
{
}

/************************************************************************/
/* Destructor                                                           */
/************************************************************************/
IniFile::~IniFile()
{
	clear();
}

/************************************************************************/
/* Write a line                                                         */
/************************************************************************/
static void write_ln(CL_File *file, std::string string)
{
#ifdef WIN32
	string += "\r\n";
#else
	string += "\n";
#endif
	file->write(string.c_str(), string.length());
}

/************************************************************************/
/* Read a line                                                          */
/************************************************************************/
static std::string read_ln(CL_File *file)
{
	std::string s = "";
	char c = file -> read_uint8();
	while(c != '\n' && c != '\r' && file->get_position() != file->get_size())
	{
		s += c;
		c = file -> read_uint8();
	}

	return s;
}

/************************************************************************/
/* Read                                                                 */
/************************************************************************/
void IniFile::read(CL_File *file)
{
	clear();

	while(file->get_position() != file->get_size())
	{
		// Get line
		std::string line = read_ln(file);

		// Parse line
		if(line.length() >1)
		{
			int separator = line.find(" = ", 0);
			if(separator)
			{
				IniElement *e = my_new IniElement();
				e -> name = line.substr(0, separator);
				e -> value = line.substr(separator + 3, line.length());
				_list.insert(_list.end(), e);
			}
		}

	}
}

/************************************************************************/
/* Write                                                                */
/************************************************************************/
void IniFile::write(CL_File *file)
{
	try
	{
		std::string section = "[Preferences]";
		write_ln(file, section);
		std::list<IniElement*>::iterator it = _list.begin();
		while(it != _list.end())
		{
			IniElement *e = (IniElement*)*it;
			std::string line = e -> name + " = " + e -> value;
			write_ln(file, line);
			it++;
		}

	}
	catch(CL_Exception&)
	{
		std::cout << "Error while writing Ini." << std::endl;
	}
}

/************************************************************************/
/* Clear                                                                */
/************************************************************************/
void IniFile::clear()
{
	std::list<IniElement*>::iterator it = _list.begin();
	while(!_list.empty())
	{
		IniElement *e = (IniElement*) *it;
		my_delete(e);
		it = _list.erase(it);
	}
}

/************************************************************************/
/* Add                                                                  */
/************************************************************************/
void IniFile::add(std::string name, std::string value)
{
	std::list<IniElement*>::iterator it = _list.begin();
	while(it != _list.end())
	{
		IniElement *e = (IniElement*)*it;
		if(e -> name == name)
		{
			e -> value = value;
			return;
		}
		it++;
	}

	IniElement *e = my_new IniElement();
	e -> name = name;
	e -> value = value;
	_list.insert(_list.end(), e);
}

/************************************************************************/
/* Add                                                                  */
/************************************************************************/
void IniFile::add(std::string name, bool value)
{
	std::list<IniElement*>::iterator it = _list.begin();
	while(it != _list.end())
	{
		IniElement *e = (IniElement*)*it;
		if(e -> name == name)
		{
			if(value)
				e -> value = "True";
			else
				e -> value = "False";
			return;
		}
		it++;
	}

	IniElement *e = my_new IniElement();
	e -> name = name;

	if(value)
		e -> value = "True";
	else
		e -> value = "False";

	_list.insert(_list.end(), e);
}

/************************************************************************/
/* Add                                                                  */
/************************************************************************/
void IniFile::add(std::string name, int value)
{
	std::list<IniElement*>::iterator it = _list.begin();
	while(it != _list.end())
	{
		IniElement *e = (IniElement*)*it;
		if(e -> name == name)
		{
			try{
				e -> value = CL_StringHelp::int_to_text(value);
				return;
			}
			catch(CL_Exception&)
			{
				std::cout << value << " is not a correct int." << std::endl;
			}
		}
		it++;
	}

	IniElement *e = my_new IniElement();
	e -> name = name;
	try
	{
		e -> value = CL_StringHelp::int_to_text(value);
	}
	catch(CL_Exception&)
	{
		std::cout << value << " is not a correct int." << std::endl;
	}

	_list.insert(_list.end(), e);
}

/************************************************************************/
/* Get                                                                  */
/************************************************************************/
std::string IniFile::get(std::string name, std::string default_value)
{
	std::list<IniElement*>::iterator it = _list.begin();
	while(it != _list.end())
	{
		IniElement *e = (IniElement*)*it;
		if(e -> name == name)
		{
			return e -> value;
		}
		it++;
	}
	return default_value;
}

/************************************************************************/
/* Get                                                                  */
/************************************************************************/
bool IniFile::get(std::string name, bool default_value)
{
	std::list<IniElement*>::iterator it = _list.begin();
	while(it != _list.end())
	{
		IniElement *e = (IniElement*)*it;
		if(e -> name == name)
		{
			return CL_StringHelp::text_to_bool(e-> value);
		}
		it++;
	}
	return default_value;
}

/************************************************************************/
/* Get                                                                  */
/************************************************************************/
int IniFile::get(std::string name, int default_value)
{
	std::list<IniElement*>::iterator it = _list.begin();
	while(it != _list.end())
	{
		IniElement *e = (IniElement*)*it;
		if(e -> name == name)
		{
			try
			{
				return CL_StringHelp::text_to_int(e-> value);
			}
			catch(CL_Exception&)
			{
				return default_value;
			}
		}
		it++;
	}
	return default_value;
}
