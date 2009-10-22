// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : SkinsManager.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include "SkinsManager.h"
#include "memory.h"
#include "misc.h"

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
SkinsManager::SkinsManager()
{
	_p_common_resources = common_resources_get_instance();
}

/************************************************************************/
/* Init                                                                 */
/************************************************************************/
void SkinsManager::init()
{
	_load_registred_skins();
	_scan_skins_path(get_skins_path());
	_scan_skins_path(get_user_skins_path());
	_sort_skins();
}

/************************************************************************/
/* Terminate                                                            */
/************************************************************************/
void SkinsManager::term()
{
	for(unsigned int i = 0; i < _skins.size(); ++i)
	{
		my_delete(_skins[i]);
	}
	_skins.clear();
}

/************************************************************************/
/* Set skin element                                                     */
/************************************************************************/
void SkinsManager::set_skin_elements(unsigned int element)
{
	for(unsigned int i = 0; i < _skins.size(); ++i)
	{
		if(_skins[i] -> get_filename() == _p_common_resources -> skin)
		{
			if(_skins[i] -> get_unlocked_elements() < element)
				_skins[i] -> set_unlocked_elements(element);
		}
	}
}
/************************************************************************/
/* Load registred skins                                                 */
/************************************************************************/
void SkinsManager::_load_registred_skins()
{
	// Fist we load Skin propreties saved in the conf file
	std::string path = get_save_path();
	std::string file_path = path + get_path_separator() + "skins-" + get_version();

	_skins.clear();
	try
	{
		CL_File file(file_path);
		int file_size = file.get_size();
		while(file.get_position() != file_size)
		{    
			std::string skin_filename = file.read_string_a();
			unsigned int unlocked_elements = file.read_uint8();
			Skin * p_skin = NULL;
			try
			{
				p_skin = my_new Skin(skin_filename, *_p_common_resources->p_gc);
				p_skin->set_unlocked_elements(unlocked_elements);
				_skins.push_back(p_skin);
			}
			catch(CL_Exception&)
			{
				// We forget this skin
				std::cout << "We don't use " << skin_filename << 
					" because it doesn't exist." << std::endl;
				if(p_skin)
				{
					my_delete(p_skin);
				}
			}
		}
		file.close();
	}
	catch(CL_Exception&)
	{
		std::cout << "Error while reading " << file_path <<
			" file, probably doesn't exist yet." << std::endl;
	}
}

/************************************************************************/
/* Scan skins path                                                      */
/************************************************************************/
void SkinsManager::_scan_skins_path(std::string path)
{
	CL_DirectoryScanner scanner;
	if (scanner.scan(path, "*.zip"))
	{
		while(scanner.next())
		{
			if(scanner.is_readable())
			{
				try
				{
					std::string filename = path+get_path_separator()
						+scanner.get_name().c_str();
					// We load the logo sprite in the gfx ressources file

					CL_VirtualFileSystem vfs(filename, true);
					CL_VirtualDirectory vd(vfs, "./");
					CL_ResourceManager gfx("general.xml", vd);					

					// Check if this skin is not aleady loaded
					bool found = false;
					for(unsigned int i = 0; i < _skins.size(); ++i)
					{
						if(_skins[i]->get_filename() == filename)
						{
							found = true;
							break;
						}
					}
					if(!found)
					{
						Skin * p_skin = my_new Skin(filename, *_p_common_resources->p_gc);
						_skins.push_back(p_skin);
					}

				}
				catch(CL_Exception&)
				{
					std::cout << "Skin " << path << scanner.get_name().c_str() << 
						" is not valid." << std::endl;
				}
			}        

		}
	}
}

/************************************************************************/
/* Sort skins                                                           */
/************************************************************************/
void SkinsManager::_sort_skins()
{
	// Sorting skin list by alphabetical order (bubble sort)
	for(unsigned int i=0; i<_skins.size(); ++i)
	{
		for(unsigned int j=i+1; j<_skins.size(); ++j)
		{
			if(_skins[i]->get_filename().compare(_skins[j]->get_filename())>0)
			{
				Skin * p_sk = _skins[i];
				_skins[i] = _skins[j];
				_skins[j] = p_sk;
			}
		}
	}
}

/************************************************************************/
/* Save registred skins                                                 */
/************************************************************************/
void SkinsManager::_save_registred_skins()
{
	// Saving progression skin file
	std::string file_path = get_save_path() + get_path_separator() +
		"skins-" + get_version();
	try
	{
		CL_File file(file_path, CL_File::create_always, CL_File::access_write);
		for(unsigned int i = 0; i < _skins.size(); ++i)
		{
			file.write_string_a(_skins[i]->get_filename());
			file.write_uint8 (_skins[i]->get_unlocked_elements());  
		}
		file.close();

	}
	catch(CL_Exception&)
	{
		std::cout << "Error while reading " << file_path <<
			"file, probably doesn't exist yet." << std::endl;
	}
}
