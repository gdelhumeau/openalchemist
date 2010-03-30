// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : Skin.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _SKIN_H_
#define _SKIN_H_

#include <ClanLib/display.h>

/** A skin class */
class Skin{

public:

	/** Constructor	*/
	Skin(std::string filename, CL_GraphicContext& gc);

	/** Get filename */
	inline std::string get_filename() const { return _filename; }

	/** Get logo */
	inline CL_Image& get_logo() { return _logo; }

	/** Get unlocked elements */
	inline unsigned int get_unlocked_elements() const { return _element; }

	/** Set unlocked elements */
	inline void set_unlocked_elements(unsigned int e) { _element = e; }

private:

	/** Skin filename */
	std::string _filename;

	/** Unlocked elements */
	unsigned int _element; 

	/** Skin logo presentation	*/
	CL_Image _logo;

};

#endif