// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : SkinsManager.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _SKINS_MANAGER_H_
#define _SKINS_MANAGER_H_

#include <vector>

#include "Skin.h"
#include "CommonResources.h"

/** Skin manager */
class SkinsManager{

public:
	
	/** Constructor */
	SkinsManager();

	/** Init */
	void init();

	/** Terminate */
	void term();

	/** Set current skin's unlocked elements field */
	void set_skin_elements(unsigned int element);

	/** Get a skin */
	inline Skin* get_skin(unsigned int i){ return _skins[i]; }

	/** Get the number of skins */
	inline unsigned int get_nb_skins() const { return _skins.size(); }

private:

	/** Common resources */
	CommonResources* _p_common_resources;

	/** Skins skins list (read in the .openalchemist/skins file) */
	std::vector<Skin*> _skins;

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