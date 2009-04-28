/********************************************************************
                          OpenAlchemist

  File : IniFile.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/


#ifndef _INIFILE_H_
#define _INIFILE_H_

#include <ClanLib/core.h>

class IniElement{
  
  public:
  std::string name;
  std::string value;
  
};



class IniFile{

  std::list<IniElement*> list;

  public:
	IniFile();
	~IniFile();

  void read(CL_InputSource_File *file);
  void write(CL_OutputSource_File *file);
  void clear();

  void add(std::string name, std::string value);

  void add(std::string name, bool value);

  void add(std::string name, int value);

  std::string get(std::string name, std::string def);

  bool get(std::string name, bool def);

  int get(std::string name, int def);

  
  

};

#endif
