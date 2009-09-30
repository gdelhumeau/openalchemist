/********************************************************************
                          OpenAlchemist

  File : IniFile.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <ClanLib/core.h>

#include "IniFile.h"

void write_ln(CL_File *file, std::string string)
{
#ifdef WIN32
	string += "\r\n";
#else
	string += "\n";
#endif
	file->write(string.c_str(), string.length());
}

std::string read_ln(CL_File *file)
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


void IniFile::read(CL_File *file)
{
	clear();

	while(file->get_position() != file->get_size())
	{
		IniElement *e = new IniElement();
		std::string line = read_ln(file);

		if(line.length() >1)
		{
			int separator = line.find(" = ", 0);
			if(separator)
			{
				e -> name = line.substr(0, separator);
				e -> value = line.substr(separator + 3, line.length());
				_list.insert(_list.end(), e);
			}
		}

	}
}

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
	catch(CL_Exception& exception)
	{
		std::cout << "Error while writing Ini." << std::endl;
	}
}




void IniFile::clear()
{
	std::list<IniElement*>::iterator it = _list.begin();
	while(!_list.empty())
	{
		IniElement *e = (IniElement*) *it;
		delete e;
		it = _list.erase(it);
	}
}

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

	IniElement *e = new IniElement();
	e -> name = name;
	e -> value = value;
	_list.insert(_list.end(), e);
}

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

	IniElement *e = new IniElement();
	e -> name = name;

	if(value)
		e -> value = "True";
	else
		e -> value = "False";

	_list.insert(_list.end(), e);
}

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
			catch(CL_Exception& exception)
			{
				std::cout << value << " is not a correct int." << std::endl;
			}
		}
		it++;
	}

	IniElement *e = new IniElement();
	e -> name = name;
	try
	{
		e -> value = CL_StringHelp::int_to_text(value);
	}
	catch(CL_Exception& exception)
	{
		std::cout << value << " is not a correct int." << std::endl;
	}

	_list.insert(_list.end(), e);
}

std::string IniFile::get(std::string name, std::string def)
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
	return def;
}

bool IniFile::get(std::string name, bool def)
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
	return def;
}

int IniFile::get(std::string name, int def)
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
			catch(CL_Exception& exception)
			{
				return def;
			}
		}
		it++;
	}
	return def;
}