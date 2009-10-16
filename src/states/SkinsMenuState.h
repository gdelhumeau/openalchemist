// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : SkinMenuState.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _SKINSMENU_STATE_H_
#define _SKINSMENU_STATE_H_

#include <ClanLib/display.h>

#include "MenuState.h"
#include "MenuState/TableChoicesItem.h"

class GameEngine;

/**
* SkinsMenu State
*/
class SkinsMenuState : public MenuState{

public:

	/** Constructor */
	SkinsMenuState();

	/** Destructor */
	~SkinsMenuState();
	
	virtual void init();

	virtual void deinit();

	virtual void load_gfx(CL_GraphicContext &gc, std::string skin);

	virtual void unload_gfx();

	virtual void action_performed(int selection, int action_type);

	virtual void update_child();

	/** Set max unlocked pieces of that skin */
	void set_skin_elements(unsigned int element);	

private:

	/** A skin */
	struct Skin{

		/** Skin filename */
		std::string filename;

		/** Unlocked elements */
		unsigned int element; 

		/** Skin logo presentation	*/
		CL_Image logo;

		/** Constructor	*/
		Skin()
		{
			filename = "";
			element  = 3;
		}
	};

	/** Skins skins list (read in the .openalchemist/skins file) */
	std::vector<Skin*> _skins_list;

	/** Skin chooser item */
	TableChoicesItem _skin_chooser;

	/** Unavaible skin logo	*/
	CL_Image logo_unavailable;

	/** Load already known skins (in APPDATA/skins file) */
	void _load_registred_skins();

	/** Scan a path for skins */
	void _scan_skins_path(std::string path);

	/** Sort skin by alphabetical order */
	void _sort_skins();

	/** Save registred skins */
	void _save_registred_skins();

};

#endif