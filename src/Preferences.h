// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : Preferences.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _PREFERENCES_H_
#define _PREFREENCES_H_

#include <ClanLib/core.h>

/** Implements the preferences that users can save */
class Preferences
{

public:

	enum RenderTarget
	{
#ifdef WITH_DX_9
		DX_9,
#endif
		GDI,
		OPENGL_1,
		OPENGL_2,
	};

	/** Render used */
	RenderTarget render_target;

	/** Fps Limit */
	int maxfps;

	/** Sound level */
	int sound_level;

	/** Music level */
	int music_level;

	/** Saves if the game is in fullscreen mode or not */
	bool fullscreen;

	/** Saves if user wants to use blind-mode */
	bool colorblind;

	/** Saves the last skin used */
	std::string skin;

	/** Constructor */
	Preferences();

	/** Read preferences from INI file */
	void read();

	/** Write preferences into INI file */
	void write();

private:

	/** Read INI file */
	void read_options_file(CL_File *file);

	/** Write INI file */
	void write_options_file(CL_File *file);

	/** Set default values */
	void set_default();


};

/** Implementing a singleton instance of Preference */
Preferences* pref_get_instance();

#endif