/********************************************************************
                          OpenAlchemist

  File : ProgressBar.h
  Description : ProgressBar implementation
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _PROGRESS_BAR_H_
#define _PROGRESS_BAR_H_

#include <ClanLib/core.h>
#include <ClanLib/display.h>

/**
 * Progress Bar class
 */
class ProgressBar{

  private:
  /**
   * Sprites for progress bar
   */
  CL_Sprite *head, *head_ok;
  CL_Sprite *foot;
  CL_Sprite *item, *item_ok;
  
  /**
   * Progress bar coords
   */
  int left, head_top, foot_top;

  

  public:


  /**
   * Constructor
   */
  ProgressBar();

  /**
   * Destructor
   */
  ~ProgressBar();

  /**
   * Loading GFX
   */
  void load_gfx(std::string skin);

  /**
   * Unloading GFX
   */
  void unload_gfx();

  /**
   * Drawing the percentage bar
   */
  void draw(int percentage);
  

};


#endif
