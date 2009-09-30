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
		CL_File file(options_file);
		read_options_file(&file);
	}
	catch(CL_Exception& e)
	{
		// File doesn't exist
		try
		{
			CL_File file(options_file);
			set_default();
			write();
		}
		catch(CL_Exception& e)
		{
			// Directory may doesn't exist
			if(!CL_Directory::set_current(options_path))
			{
				if(CL_Directory::create(options_path))
				{
					// Now we can create the file
					try
					{
						CL_File file(options_file);
						set_default();
						write();
					}
					catch(CL_Exception & e)
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
		CL_File file(options_file, CL_File::create_always, CL_File::access_write);
		write_options_file(&file);
	}
	catch(CL_Exception & e)
	{
		std::cout << "Can't write file " << options_file <<".\n";
	}
}


/** Read preferences from file */
void Preferences::read_options_file(CL_File *file)
{
	try{

		IniFile ini;
		ini.read(file);

		render_target = GDI;

		std::string default_target = "OPENGL_1";
		std::string rt = ini.get("Render Target", default_target);
		if(rt == "OPENGL_1")
		{
			render_target = OPENGL_1;
		}
		else if(rt == "GDI")
		{
			render_target = GDI;
		}
		else if(rt == "OPENGL_2")
		{
			render_target = OPENGL_2;
		}
		else if(rt == "SDL")
		{
			render_target = SDL;
		}

		fullscreen = ini.get("Fullscreen", fullscreen);
		screen_size = ini.get("Screen Size", screen_size);
		sound_level = ini.get("Sound Level", sound_level);
		music_level = ini.get("Music Level", music_level);
		maxfps = ini.get("MaxFPS", maxfps);
		colorblind = ini.get("Colorblind", colorblind);

		std::string skin_file = ini.get("Skin", skin);
		try
		{
			CL_ZipArchive zip_test(skin_file);
			skin = skin_file;
		}
		catch(CL_Exception & e)
		{
			std::cout << "Skin " << skin_file << " was not found or is not a zip file, we use " << skin << " instead."  << std::endl;
		}

		switch(screen_size)
		{
		case SCREEN_SIZE_640x480_WIDE:
		case SCREEN_SIZE_800x600_WIDE:
			widescreen = true;
			break;
		default:
			widescreen = false;
			break;
		}

		file -> close();

	}
	catch(CL_Exception & e)
	{
		std::cout << "Error while reading options file \n";
	}
}


void Preferences::write_options_file(CL_File *file)
{

	IniFile ini;
	ini.clear();

	std::string rt = "GDI";
	switch(render_target)
	{
	case GDI:
		rt = "GDI";
		break;
	case OPENGL_1:
		rt = "OPENGL_1";
		break;
	case OPENGL_2:
		rt = "OPENGL_2";
		break;
	case SDL:
		rt = "SDL";
		break;
	}

	ini.add("Render Target", rt);
	ini.add("Fullscreen", fullscreen);
	ini.add("Screen Size", screen_size);
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
	render_target = OPENGL_1;
	maxfps = 65;
	sound_level = 100;
	music_level = 30;
	fullscreen = false;
	widescreen = false;
	colorblind = false;
	screen_size = SCREEN_SIZE_800x600;
	skin = get_skins_path() + get_path_separator() + "aqua.zip";
}


