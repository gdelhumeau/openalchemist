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

#define NB_MAX_CHAR_PER_PIC 11
#define SCORE_FONT 0
#define COMBO_FONT 1

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
   int nb_char_per_pic;

  /**
   *  Array of each char
   */
   SDL_Rect charClip[NB_MAX_CHAR_PER_PIC];

  void load_gfx(std::string skin, int which_font);
  void unload_gfx();
  void fillClip();
  void draw(int scoreLeft, int scoreTop, std::string strScore);
  int  GetCharHeight();

  BitmapFont(std::string skin, int which_font);
  ~BitmapFont();
  
   
};


#endif
