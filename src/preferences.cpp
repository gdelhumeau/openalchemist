/* OpenAlchemist - just a simple game 
 * ----------------------------------
 *
 * Copyright (C) 2006 Guillaume Delhumeau <guillaume.delhumeau at laposte.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "headers.h"

#define OPTIONS_FILE_REVISION 2

Preferences* pref_get_instance()
{
  static Preferences *instance = NULL;
  if(instance == NULL)
    instance = new Preferences();
  return instance;
}

Preferences::Preferences()
{
  read();
}

void Preferences::read()
{
  std::string options_path = get_save_path();
#ifdef WIN32
  std::string options_file = options_path + "\\options";
#else
  std::string options_file = options_path + "/options";
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

void Preferences::write()
{

  std::string options_path = get_save_path();
#ifdef WIN32
  std::string options_file = options_path + "\\options";
#else
  std::string options_file = options_path + "/options";
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



void Preferences::read_options_file(CL_InputSource_File *file)
{
  try{

  file->open();
  revision = file -> read_uint8();
  if(revision >= 1)
  {
    render_opengl = file  -> read_bool8();
    fullscreen = file -> read_bool8();
    sound_level = file -> read_int32();
    music_level = file -> read_int32();
  }
  if(revision >= 2)
  {
    skin = file -> read_string();
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

  file -> close();
}

void Preferences::set_default()
{
  revision = 1;
  render_opengl = false;
  sound_level = 10;
  music_level = 10;
  fullscreen = false;
  skin = CL_System::get_exe_path() + "skins/aqua.zip";
}

void Game::load_preferences()
{
  Preferences *pref = pref_get_instance();
  sound_level = pref -> sound_level;
  music_level = pref -> music_level;
  skin =  pref -> skin;
}

void Game::save_preferences()
{
  Preferences *pref = pref_get_instance();
  pref -> render_opengl = opengl;
  pref -> sound_level = sound_level;
  pref -> music_level = music_level;
  pref -> write();
}



std::string get_save_path()
{
#ifdef WIN32
  return CL_System::get_exe_path() + "\\savedata";
#else
  return ((std::string)getenv("HOME")) + "/.openalchemist";
#endif
}
