/********************************************************************
                          OpenAlchemist

  File : Preferences.h
  Description : implements the Preference class, which contains
                options that user can save
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/


#ifndef _PREFERENCES_H_
#define _PREFREENCES_H_

#include <ClanLib/core.h>

/** Implements the preferences that users can save */
class Preferences
{

  public:

  enum RenderTarget
	{
		GDI,
		OPENGL_1,
		OPENGL_2,
		SDL
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

	/** Saves if user have a wide screen */
	bool widescreen;

	/** Saves screen size */
	int screen_size;

  /** Saves the last skin used */
  std::string skin;

  Preferences();
  void read();
  void write();

  private:
  void read_options_file(CL_File *file);
  void write_options_file(CL_File *file);
  void set_default();


};


Preferences* pref_get_instance();

enum{
		SCREEN_SIZE_320x240	= 0,
		SCREEN_SIZE_640x480,
		SCREEN_SIZE_640x480_WIDE,
		SCREEN_SIZE_800x600,
		SCREEN_SIZE_800x600_WIDE,		
};


#endif
