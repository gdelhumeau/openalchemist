/********************************************************************
                          OpenAlchemist

  File : IniFile.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <ClanLib/core.h>

#include "IniFile.h"

void write_ln(CL_OutputSource_File *file, std::string string)
{
#ifdef WIN32
  string += "\r\n";
#else
  string += "\n";
#endif
  for(u_int i=0; i<string.length(); ++i)
  {
    char c = *string.substr(i,i+1).c_str();
    file -> write_char8(c);
  }
}

std::string read_ln(CL_InputSource_File *file)
{

  std::string s = "";
  char c = file -> read_char8();
  while(c != '\n' && c != '\r' && file -> tell() != file->size())
  {
    s += c;
    c = file -> read_char8();
  }

  return s;
}


void IniFile::read(CL_InputSource_File *file)
{
  clear();
      
  file -> open();
  while(file -> tell() != file -> size())
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
        list.insert(list.end(), e);
      }
    }

  }
}

void IniFile::write(CL_OutputSource_File *file)
{

  try
  {
    std::string section = "[Preferences]";
    write_ln(file, section);
    std::list<IniElement*>::iterator it = list.begin();
    while(it != list.end())
    {
      IniElement *e = (IniElement*)*it;
      std::string line = e -> name + " = " + e -> value;
      write_ln(file, line);
      it++;
    }

  }
  catch(CL_Error)
  {
    std::cout << "Error while writing Ini." << std::endl;
  }
}
     



void IniFile::clear()
{
  std::list<IniElement*>::iterator it = list.begin();
  while(!list.empty())
  {
    IniElement *e = (IniElement*) *it;
    delete e;
    it = list.erase(it);
  }
}

void IniFile::add(std::string name, std::string value)
{
  std::list<IniElement*>::iterator it = list.begin();
  while(it != list.end())
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
  list.insert(list.end(), e);
}

void IniFile::add(std::string name, bool value)
{
  std::list<IniElement*>::iterator it = list.begin();
  while(it != list.end())
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

  list.insert(list.end(), e);
}

void IniFile::add(std::string name, int value)
{
  std::list<IniElement*>::iterator it = list.begin();
  while(it != list.end())
  {
    IniElement *e = (IniElement*)*it;
    if(e -> name == name)
    {
      try{
        e -> value = CL_String::from_int(value);
        return;
      }
      catch(CL_Error e)
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
    e -> value = CL_String::from_int(value);
  }
  catch(CL_Error e)
  {
    std::cout << value << " is not a correct int." << std::endl;
  }

  list.insert(list.end(), e);
}

std::string IniFile::get(std::string name, std::string def)
{
  std::list<IniElement*>::iterator it = list.begin();
  while(it != list.end())
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
  std::list<IniElement*>::iterator it = list.begin();
  while(it != list.end())
  {
    IniElement *e = (IniElement*)*it;
    if(e -> name == name)
    {
      return CL_String::to_bool(e -> value);
    }
    it++;
  }
  return def;
}

int IniFile::get(std::string name, int def)
{
  std::list<IniElement*>::iterator it = list.begin();
  while(it != list.end())
  {
    IniElement *e = (IniElement*)*it;
    if(e -> name == name)
    {
      try
      {
        return CL_String::to_int(e -> value);
      }
      catch(CL_Error e)
      {
        return def;
      }
    }
    it++;
  }
  return def;
}

  
  
