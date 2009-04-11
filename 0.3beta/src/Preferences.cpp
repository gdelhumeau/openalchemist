/********************************************************************
                          OpenAlchemist

  File : Preferences.cpp
  Description : implement the Preference class, which contains
                options that user can save
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

//#include <ClanLib/core.h>

#include "Preferences.h"
#include "IniFile.h"
#include "misc.h"


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
  std::string options_file = /*get_save_path() + get_path_separator() +*/ "preferences-"+get_version()+".ini";
  FILE * OptionFile;
  set_default();
  
//  try
//  {
    OptionFile = fopen(options_file.c_str(), "r");
    if (OptionFile != NULL)
    {
	read_options_file(OptionFile);
printf("after read skin is : %s\n",skin.c_str());
	fclose(OptionFile);
    }
    else
    {
	printf("Could not open ini file so unable to read it \n");
    }
    
//  }
#if 0
  catch(ifstream::failure e)
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
#endif
}

/** Write preferences into file */
void Preferences::write()
{

  std::string options_path = get_save_path();
  std::string options_file = /*options_path + get_path_separator() +*/ "preferences-"+get_version()+".ini";
  FILE * OptionFile;

  OptionFile = fopen(options_file.c_str(), "w");
  if (OptionFile != NULL)
  {
    write_options_file(OptionFile);
    fclose(OptionFile);
  }
#if 0
  try
  {
    CL_OutputSource_File file(options_file);
    write_options_file(&file);
  }
  catch(CL_Error e)
  {
    std::cout << "Can't write file " << options_file <<".\n";
  }
#endif
}


/** Read preferences from file */
void Preferences::read_options_file(FILE *file)
{
/*  try{
*/
    //file->open();
    //allready opened by calling method

    IniFile ini;
    ini.read(file);
    render_opengl = ini.get("OpenGL", render_opengl);
    fullscreen    = ini.get("Fullscreen", fullscreen);
    sound_level   = ini.get("Sound Level", sound_level);
    music_level   = ini.get("Music Level", music_level);
    maxfps        = ini.get("MaxFPS", maxfps);
    colorblind    = ini.get("Colorblind", colorblind);
    skin          = ini.get("Skin", skin);

/*  //We do not manage skins by zip archives on psp, maybe later
    try{
      CL_Zip_Archive zip_test(skin_file);
      skin = skin_file;
    }
    catch(CL_Error e)
    {
      std::cout << "Skin " << skin_file << " was not found or is not a zip file, we use " << skin << " instead."  << std::endl;
    }
*/
      
  //  file -> close();
  // closed in the calling method

 /* }
  catch(CL_Error e)
  {
    std::cout << "Error while reading options file \n";
  }
*/
}


void Preferences::write_options_file(FILE *file)
{
  //file -> open();

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

}

void Preferences::set_default()
{
  render_opengl = false; //was true
  maxfps = 65;
  sound_level = 10;
  music_level = 10;
  fullscreen = false;
  colorblind = false;
  skin = /*get_skins_path() + get_path_separator() + "*/"aqua";/*.zip";*/
}


