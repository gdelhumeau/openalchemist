/********************************************************************
                          OpenAlchemist

  File : IniFile.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/


#ifndef _INIFILE_H_
#define _INIFILE_H_

//#include <ClanLib/core.h>
#include <fstream>
#include <list>

#define MAX_LENGTH_LINE 100

class IniElement{
  
  public:
  std::string name;
  std::string value;
  
};



class IniFile{

  std::list<IniElement*> list;

  public:

  void read(std::fstream *file);
  void write(std::fstream *file);
  void clear();

  void add(std::string name, std::string value);

  void add(std::string name, bool value);

  void add(std::string name, int value);

  std::string get(std::string name, std::string def);

  bool get(std::string name, bool def);

  int get(std::string name, int def);

  
  

};

#endif
