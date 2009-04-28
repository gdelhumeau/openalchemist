/********************************************************************
                          OpenAlchemist

  File : Preferences.cpp
  Description : implement the Preference class, which contains
                options that user can save
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <ClanLib/core.h>

#include "Preferences.h"
#include "IniFile.h"
#include "misc.h"
#include "memory.h"

/** Implementing a singleton instance of Preference */
Preferences* pref_get_instance()
{
  static Preferences *instance = NULL;
  if(instance == NULL)
    instance = my_new Preferences();
  return instance;
}

/** Constructor */
Preferences::Preferences()
{
  read();
}

/** Read preferences from file */
void Preferences::read()
{
  std::string options_path = get_save_path();
  std::string options_file = get_save_path() + get_path_separator() + "preferences-"+get_version()+".ini";
  set_default();

  try
  {
    CL_InputSource_File file(options_file);
    read_options_file(&file);
  }
  catch(CL_Error e)
  {
    // File doesn't exist
    try
    {
      CL_OutputSource_File file(options_file);
      set_default();
      write();
    }
    catch(CL_Error e)
    {
      // Directory may doesn't exist
      if(!CL_Directory::change_to(options_path))
      {
        if(CL_Directory::create(options_path))
        {
          // Now we can create the file
          try
          {
            CL_OutputSource_File file(options_file);
            set_default();
            write();
          }
          catch(CL_Error e)
          {
            std::cout << "Can't create " << options_file <<".\n";
            set_default();
          }
              
        }
        else
        {
          std::cout << "Can't access to " << options_path << ".\n";
          set_default();
        }
      }
      else
      {
        std::cout << "Can't access to " << options_file <<".\n";
        set_default();
      }
          
    }

  }
}

/** Write preferences into file */
void Preferences::write()
{

  std::string options_path = get_save_path();
  std::string options_file = options_path + get_path_separator() + "preferences-"+get_version()+".ini";

  try
  {
    CL_OutputSource_File file(options_file);
    write_options_file(&file);
  }
  catch(CL_Error e)
  {
    std::cout << "Can't write file " << options_file <<".\n";
  }
}


/** Read preferences from file */
void Preferences::read_options_file(CL_InputSource_File *file)
{
  try{

    file->open();
  
    IniFile ini;
    ini.read(file);
  
    render_opengl = ini.get("OpenGL", render_opengl);
    fullscreen = ini.get("Fullscreen", fullscreen);
		widescreen = ini.get("Widescreen", widescreen);
    sound_level = ini.get("Sound Level", sound_level);
    music_level = ini.get("Music Level", music_level);
    maxfps = ini.get("MaxFPS", maxfps);
    colorblind = ini.get("Colorblind", colorblind);
  
    std::string skin_file = ini.get("Skin", skin);
    try{
      CL_Zip_Archive zip_test(skin_file);
      skin = skin_file;
    }
    catch(CL_Error e)
    {
      std::cout << "Skin " << skin_file << " was not found or is not a zip file, we use " << skin << " instead."  << std::endl;
    }
      
    file -> close();

  }
  catch(CL_Error e)
  {
    std::cout << "Error while reading options file \n";
  }
}


void Preferences::write_options_file(CL_OutputSource_File *file)
{
  file -> open();

  IniFile ini;
  ini.clear();
  ini.add("OpenGL", render_opengl);
  ini.add("Fullscreen", fullscreen);
	ini.add("Widescreen", widescreen);
  ini.add("Sound Level", sound_level);
  ini.add("Music Level", music_level);
  ini.add("MaxFPS", maxfps);
  ini.add("Colorblind", colorblind);
  ini.add("Skin", skin);
  
  ini.write(file);

  file -> close();
}

void Preferences::set_default()
{
  render_opengl = true;
  maxfps = 65;
  sound_level = 10;
  music_level = 10;
  fullscreen = false;
	widescreen = false;
  colorblind = false;
  skin = get_skins_path() + get_path_separator() + "aqua.zip";
}


