/********************************************************************
                          pspOpenAlchemist

  File : Player.h
  Description : Implements Player Class
  License : GNU General Public License 2 or +
  Author : Chrystele MALLET

*********************************************************************/
#include "BitmapFont.h"
#include <SDL/SDL.h>

BitmapFont::BitmapFont(std::string skin, int which_font)
{
  FontPic = NULL;
  load_gfx(skin, which_font);
  if (FontPic != NULL)
  {
    charSize = FontPic->w / NB_CHAR_PER_PIC;
    fillClip();
  }
}

BitmapFont::~BitmapFont()
{
   unload_gfx();
}

void BitmapFont::load_gfx(std::string skin, int which_font)
{
   unload_gfx();
   switch(which_font)
   {
      case SCORE_FONT:
	FontPic = IMG_Load_fromSkin(skin, "misc/font.png");
	printf("Score font loaded\n");
   	break;

      case COMBO_FONT:
	FontPic = IMG_Load_fromSkin(skin, "misc/font-combos.png");
	printf("Combo font loaded\n");
   	break;
   }
   if (FontPic == NULL)
      printf("could not load font.png\n");
	
}

void BitmapFont::unload_gfx()
{
    if (FontPic != NULL)
    {
	SDL_FreeSurface(FontPic);
	FontPic = NULL;
    }
printf("unload_gfx done for bitmap font\n");
/*    for (int i=0; i<NB_CHAR_PER_PIC; i++)
    {
	delete &charClip[i];
	charClip[i] = NULL;
    }*/
}

void BitmapFont::fillClip()
{
  for (int i=0; i<NB_CHAR_PER_PIC; i++)
  {
     charClip[i].x = i * charSize; 
     charClip[i].y = 0;
  if(FontPic!=NULL)
     charClip[i].h = FontPic->h;
  else
     charClip[i].h = FontPic->h;
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
     if((intScore>0) && (i%3 == 0))
     {  
	  psp_sdl_blit_clip_at_XY(FontPic, &charClip[10], (score_x - (i+j)*charSize), score_y);
	  j++;
     }
     
   }
}
int BitmapFont::GetCharHeight()
{
   if (FontPic)
    {
	return FontPic->h;
    }
   else
   {
	return 0;
   }
}


