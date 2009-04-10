/********************************************************************
                          pspOpenAlchemist

  File : Player.h
  Description : Implements Player Class
  License : GNU General Public License 2 or +
  Author : Chrystele MALLET

*********************************************************************/

#ifndef _BITMAP_FONT_H
#define _BITMAP_FONT_H

#include <string>
#include <SDL/SDL.h>
#include "psp_sdl.h"
#include "misc.h"

class BitmapFont
{

public:

   /**
    * Picture containing the 10 digits of the desirated font
    */ 
   SDL_Surface *FontPic;

  /**
   * Size of each char
   */
   int charSize;

  /**
   *  Array of each char
   */
   SDL_Rect charClip[11];

  void load_gfx(std::string skin);
  void unload_gfx();
  void fillClip();
  void draw(int scoreLeft, int scoreTop, std::string strScore);
  int  GetCharHeight();

  BitmapFont(std::string skin);
  ~BitmapFont();
  
   
};


#endif
