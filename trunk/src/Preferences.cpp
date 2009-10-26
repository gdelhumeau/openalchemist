// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : Preferences.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include <ClanLib/core.h>

#include "Preferences.h"
#include "IniFile.h"
#include "misc.h"
#include "memory.h"

/************************************************************************/
/* Singleton                                                            */
/************************************************************************/
Preferences* pref_get_instance()
{
	static Preferences *instance = NULL;
	if(instance == NULL)
		instance = my_new Preferences();
	return instance;
}

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
Preferences::Preferences()
{
	read();
}

/************************************************************************/
/* Read                                                                 */
/************************************************************************/
void Preferences::read()
{
	std::string options_path = get_save_path();
	std::string options_file = get_save_path() + get_path_separator() +
		"preferences-"+get_version()+".ini";
	_set_default();

	try
	{
		CL_File file(options_file);
		_read_options_file(&file);
	}
	catch(CL_Exception&)
	{
		// File doesn't exist		
		try
		{
			CL_File file(options_file);
			_set_default();
			write();
		}
		catch(CL_Exception&)
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
						_set_default();
						write();
					}
					catch(CL_Exception&)
					{
						std::cout << "Can't create " << options_file <<".\n";
						_set_default();
					}

				}
				else
				{
					std::cout << "Can't access to " << options_path << ".\n";
					_set_default();
				}
			}
			else
			{
				std::cout << "Can't access to " << options_file <<".\n";
				_set_default();
			}

		}

	}
}

/************************************************************************/
/* Write                                                                */
/************************************************************************/
void Preferences::write()
{

	std::string options_path = get_save_path();
	std::string options_file = options_path + get_path_separator() +
		"preferences-"+get_version()+".ini";

	try
	{
		CL_File file(options_file, CL_File::create_always, CL_File::access_write);
		_write_options_file(&file);
	}
	catch(CL_Exception&)
	{
		std::cout << "Can't write file " << options_file <<".\n";
	}
}


/************************************************************************/
/* Read options                                                         */
/************************************************************************/
void Preferences::_read_options_file(CL_File *file)
{
	try{

		IniFile ini;
		ini.read(file);

		render_target = OPENGL_1;

		std::string default_target = "OPENGL_1";
		std::string rt = ini.get("Render Target", default_target);
		if(rt == "OPENGL_1")
		{
			render_target = Preferences::OPENGL_1;
		}
		else if(rt == "SOFTWARE")
		{
			render_target = Preferences::SOFTWARE;
		}
		else if(rt == "OPENGL_2")
		{
			render_target = Preferences::OPENGL_2;
		}
#ifdef WITH_DX_9
		else if(rt == "DX_9")
		{
			render_target = Preferences::DX_9;
		}
#endif

		fullscreen = ini.get("Fullscreen", fullscreen);
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
		catch(CL_Exception&)
		{
			std::cout << "Skin " << skin_file <<
				" was not found or is not a zip file, we use " <<
				skin << " instead."  << std::endl;
		}


		file -> close();

	}
	catch(CL_Exception&)
	{
		std::cout << "Error while reading options file \n";
	}
}

/************************************************************************/
/* Write options                                                        */
/************************************************************************/
void Preferences::_write_options_file(CL_File *file)
{

	IniFile ini;
	ini.clear();

	std::string rt = "SOFTWARE";
	switch(render_target)
	{
	case SOFTWARE:
		rt = "SOFTWARE";
		break;
	case OPENGL_1:
		rt = "OPENGL_1";
		break;
	case OPENGL_2:
		rt = "OPENGL_2";
		break;
#ifdef WITH_DX_9
	case DX_9:
		rt = "DX_9";
		break;
#endif
	}

	ini.add("Render Target", rt);
	ini.add("Fullscreen", fullscreen);
	ini.add("Sound Level", sound_level);
	ini.add("Music Level", music_level);
	ini.add("MaxFPS", maxfps);
	ini.add("Colorblind", colorblind);
	ini.add("Skin", skin);

	ini.write(file);

	file -> close();
}

/************************************************************************/
/* Set Default                                                          */
/************************************************************************/
void Preferences::_set_default()
{
	render_target = OPENGL_1;
	maxfps = 60;
	sound_level = 100;
	music_level = 100;
	fullscreen = false;
	colorblind = false;
	skin = get_skins_path() + get_path_separator() + "aqua.zip";
}