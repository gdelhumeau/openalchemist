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

  /** Render used */
  bool render_opengl;

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

  Preferences();
  void read();
  void write();

  private:
  void read_options_file(CL_InputSource_File *file);
  void write_options_file(CL_OutputSource_File *file);
  void set_default();


};


Preferences* pref_get_instance();

#endif