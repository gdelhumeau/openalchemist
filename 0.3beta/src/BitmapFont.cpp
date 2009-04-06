/********************************************************************
                          pspOpenAlchemist

  File : Player.h
  Description : Implements Player Class
  License : GNU General Public License 2 or +
  Author : Chrystele MALLET

*********************************************************************/
#include "BitmapFont.h"
#include <SDL/SDL.h>

BitmapFont::BitmapFont(std::string skin)
{
  charSize = 16;
  FontPic = NULL;
  load_gfx(skin);
  fillClip();
}

BitmapFont::~BitmapFont()
{

}

void BitmapFont::load_gfx(std::string skin)
{
   FontPic = IMG_Load_fromSkin(skin, "misc/font.png");
   if (FontPic == NULL)
      printf("could not load font.png\n");
}

void BitmapFont::unload_gfx()
{
    SDL_FreeSurface(FontPic);
}

void BitmapFont::fillClip()
{
  for (int i=0; i<11; i++)
  {
     charClip[i].x = i * charSize; 
     charClip[i].y = 0;
  if(FontPic!=NULL)
     charClip[i].h = FontPic->h;
  else
     charClip[i].h = 16;
     charClip[i].w = charSize;
  }
 
}

void BitmapFont::draw(int score_x, int score_y, std::string strScore)
{
  int intScore = atoi(strScore.c_str());
  int i = 0, j = 0;
  while(intScore != 0)
  {
     //printf("intScore To draw : %d\n",intScore);
     int charToDraw = intScore%10;
     psp_sdl_blit_clip_at_XY(FontPic, &charClip[charToDraw], (score_x - (i+j)*charSize), score_y);
     intScore = int(intScore/10);
     i++;
     if((strScore.length()>3) && (i%3 == 0))
     {  
	  psp_sdl_blit_clip_at_XY(FontPic, &charClip[10], (score_x - (i+j)*charSize), score_y);
	  j++;
     }
     
   }

}
