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


#define OPTIONS_FILE_REVISION 4

std::string get_save_path();

/** Implementing a singleton instance of Preference */
Preferences* pref_get_instance()
{
  static Preferences *instance = NULL;
  if(instance == NULL)
    instance = new Preferences();
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
#ifdef WIN32
  std::string options_file = options_path + "\\preferences.ini";
#else
#ifdef SVN
  std::string options_file = options_path + "/preferences-svn";
#else
  std::string options_file = options_path + "/preferences";
#endif
#endif

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
#ifdef WIN32
  std::string options_file = options_path + "\\preferences.ini";
#else
#ifdef SVN
  std::string options_file = options_path + "/preferences-svn";
#else
  std::string options_file = options_path + "/preferences";
#endif
#endif


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



  /*revision = file -> read_uint8();
  if(revision >= 1)
  {
    render_opengl = file  -> read_bool8();
    fullscreen = file -> read_bool8();
    sound_level = file -> read_int32();
    music_level = file -> read_int32();
  }
  if(revision >= 2)
  {
    std::string skin_file = file -> read_string();
    try{
      CL_Zip_Archive zip_test(skin_file);
      skin = skin_file;
    }
    catch(CL_Error e)
    {
      std::cout << "Skin " << skin_file << " was not found or is not a zip file, we use " << skin << " instead."  << std::endl;
    }
  }
  if(revision >= 3)
  {
    maxfps = file -> read_int16();
  }
  if(revision >= 4)
  {
    colorblind = file -> read_bool8();
    }*/
      
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
  ini.add("Sound Level", sound_level);
  ini.add("Music Level", music_level);
  ini.add("MaxFPS", maxfps);
  ini.add("Colorblind", colorblind);
  ini.add("Skin", skin);
  
  ini.write(file);

  

  /*
  // File revision
  file -> write_uint8(OPTIONS_FILE_REVISION);
  // Use OpenGL
  file -> write_bool8(render_opengl);
  // Fullscreen
  file -> write_bool8(fullscreen);
  // Sound level
  file -> write_int32(sound_level);
  // Music level
  file -> write_int32(music_level);
  // Skin
  file -> write_string(skin);
  // Maxfps
  file -> write_int16(maxfps);
  // ColorBlind mode
  file -> write_bool8(colorblind);
  */

  file -> close();
}

void Preferences::set_default()
{
  revision = OPTIONS_FILE_REVISION;
  render_opengl = false;
  maxfps = 250;
  sound_level = 10;
  music_level = 10;
  fullscreen = false;
  colorblind = false;
  skin = CL_System::get_exe_path() + "skins/aqua.zip";
}

/*void Game::load_preferences()
{
  Preferences *pref = pref_get_instance();
  sound_level = pref -> sound_level;
  music_level = pref -> music_level;  
  skin =  pref -> skin;
  colorblind = pref -> colorblind;
 }*/

/*void Game::save_preferences()
{
  Preferences *pref = pref_get_instance();
  pref -> render_opengl = opengl;
  pref -> sound_level = sound_level;
  pref -> music_level = music_level;
  pref -> write();
}*/



std::string get_save_path()
{
#ifdef WIN32
  return CL_System::get_exe_path() + "\\savedata";
#else
  return ((std::string)getenv("HOME")) + "/.openalchemist";
#endif
}
