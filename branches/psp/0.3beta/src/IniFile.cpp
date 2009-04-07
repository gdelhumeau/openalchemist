/********************************************************************
                          OpenAlchemist

  File : IniFile.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

//#include <ClanLib/core.h>

#include "IniFile.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

#if 0
void write_ln(/*CL_OutputSource_File*/ std::fstream *file, std::string string)
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
#endif

#if 0
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
#endif


void IniFile::read(/*CL_InputSource_File*/ FILE *file)
{
  clear();
  printf("inifile->read method called, clear done\n");
  //file -> open();
  // We will consider it as allready opened for conveniance
  char c_temp = fgetc(file);
  printf("fgetc done\n");
  while(c_temp != EOF)
  { 
    char tempStr[MAX_LENGTH_LINE]="";

    IniElement *e = new IniElement();
    std::string line;

    while(c_temp != '\n')
    { 
        sprintf(tempStr,"%s%c", tempStr, c_temp);
        c_temp = fgetc(file);
    }

    line = std::string(tempStr);

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
    c_temp = fgetc(file);

  }
  printf("out of the loop\n");
}

void IniFile::write(/*CL_OutputSource_File*/ FILE * OptionFile)
{

//TODO: check write error
/*  try
  {
*/    //std::string section = "[Preferences]";
    //write_ln(file, section);
    //file->write("[Preferences]\n", sizeof("[Preferences]\n"));
    fprintf(OptionFile, "[Preferences]\n");
    std::list<IniElement*>::iterator it = list.begin();
    while(it != list.end())
    {
      IniElement *e = (IniElement*)*it;
      std::string line = e -> name + " = " + e -> value + "\n";
      //write_ln(file, line);
      //file->write(line.c_str(), line.length());
      fprintf(OptionFile, "%s",line.c_str());
      // << endl;
      it++;
    }

/*  }
  catch(fstream::failure Error)
  {
    std::cout << "Error : while writing Ini." << std::endl;
  }
*/

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
//      try{
	std::stringstream stringValue;
	stringValue << value;
        e -> value = stringValue.str();
/*        return;
      }
      catch( e)
      {
        std::cout << value << " is not a correct int." << std::endl;
      }
*/
    }
    it++;
  }

  IniElement *e = new IniElement();
  e -> name = name;
/*  try
  {
*/
    std::stringstream stringValue;
    stringValue << value;
    e -> value = stringValue.str();
/*  }
  catch(CL_Error e)
  {
    std::cout << value << " is not a correct int." << std::endl;
  }
*/
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
	if( e->value == "True")
            return true;
	if( e->value == "False")
	    return false;
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
/*      try
      {
*/
        return atoi((e -> value).c_str());
/*      }
      catch(CL_Error e)
      {
        return def;
      }
*/
    }
    it++;
  }
  return def;
}

  
  
