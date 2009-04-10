/********************************************************************
                          OpenAlchemist

  File : Piece.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _PIECE_H_
#define _PIECE_H_

#include <iostream>

//#include <ClanLib/display.h>
#include <SDL/SDL.h>
#include "psp_sdl.h"

#define PIECE_SPEED 0.5

#define NORMAL_CTXT   0

#define APPEAR_STEP1  1
#define APPEAR_STEP2  2
#define APPEAR_STEP3  3

#define DISAPP_STEP1  4
#define DISAPP_STEP2  5
#define DISAPP_STEP3  6

#define APPEAR_STEPS  3
#define DISAPP_STEPS  3


#define LAST_APPEAR   APPEAR_STEPS
#define LAST_DISAPP   APPEAR_STEPS + DISAPP_STEPS


class Piece
{
  private:

  // For display:
  SDL_Surface *normal_sprite;
  SDL_Surface *mini_sprite;

  SDL_Surface *appearing_surface;
  SDL_Surface *disappearing_surface;

  SDL_Rect appearing_sprites   [APPEAR_STEPS];
  SDL_Rect disappearing_sprites[DISAPP_STEPS];


//  SDL_Surface *current_sprite;
  

  static const int score[12];

  // For animation appearing/disapearing
  int graph_ctxt;

  // For scores:
  int score_value;

  // For ...
  int piece_number;

  // Real coords on the screen
  double x, y;

  // Goal target coord
  int target_y;

    
  public:

  // Constructor
  Piece(int piece_number)
  {

    normal_sprite        = NULL;
    appearing_surface     = NULL;
    disappearing_surface  = NULL;
    mini_sprite          = NULL;
//    current_sprite       = NULL; 
    graph_ctxt           = NORMAL_CTXT;

    this -> piece_number = piece_number;
    this -> score_value  = score[piece_number];
    x = 0;
    y = 0;
    target_y = 0;
  }

  // Method to set the sprites
  void set_sprites(SDL_Surface *normal, SDL_Surface *appearing, SDL_Surface *disappearing, SDL_Surface *mini)
  {
    if (!normal)
    std::cerr<< "normal sprite is a bad parameter"<<std::endl;
    normal_sprite = normal;
    mini_sprite = mini;
//    current_sprite = normal_sprite;

    // Loading surface containing sprites
    appearing_surface = appearing;
    // Seeting up sprites from loaded surface
    for(int i=0; i<APPEAR_STEPS; i++)
    {
	appearing_sprites[i].x = i* (appearing_surface->w / DISAPP_STEPS);
	appearing_sprites[i].y = 0;
	appearing_sprites[i].h = appearing_surface->h;
	appearing_sprites[i].w = (appearing_surface->w / DISAPP_STEPS);
    }

    // Loading surface containing sprites
    disappearing_surface = disappearing;
    // Seeting up sprites from loaded surface
    for(int i=0; i<DISAPP_STEPS; i++)
    {
	disappearing_sprites[i].x = i* (disappearing_surface->w / DISAPP_STEPS);
	disappearing_sprites[i].y = 0;
	disappearing_sprites[i].h = disappearing_surface->h;
	disappearing_sprites[i].w = (disappearing_surface->w / DISAPP_STEPS);
    }
  }
 
  // Methods to display - be carefull, if current_prite is not initialized
  void draw()
    {
	   if (graph_ctxt == NORMAL_CTXT)
	   	psp_sdl_blit_on_screen_at_XY(normal_sprite, (int)x, (int)y);
	   else
	   {
		if (graph_ctxt < DISAPP_STEP1)
		    psp_sdl_blit_clip_at_XY ( appearing_surface, &appearing_sprites[graph_ctxt], (int) x, (int) y );
		else
		    psp_sdl_blit_clip_at_XY ( disappearing_surface, &disappearing_sprites[graph_ctxt], (int) x, (int) y );

		if((graph_ctxt == LAST_APPEAR) || (graph_ctxt == LAST_DISAPP))
		{
		    graph_ctxt = NORMAL_CTXT;
		}
		else
		{
		    graph_ctxt++;
		}
	   }
	

 //       else
   //        std::cerr<< "piece sprite pas bon" << std::endl;
    }

  void draw_mini(/*CL_GraphicContext* context = 0*/)
    {
     // mini_sprite -> draw(x, y, context); 
        psp_sdl_blit_on_screen_at_XY(mini_sprite, (int)x , (int)y);
    }

  void start_appear()
    {
      graph_ctxt = APPEAR_STEP1;
    }

  void start_disappear()
    {
	graph_ctxt = DISAPP_STEP1;
    }

  void start_fall(int target_x, int target_y)
    {
      this -> target_y = target_y;
      x = target_x;
    }

  void set_normal()
    {
     // current_sprite = normal_sprite;
    }

 // Return true if the piece is appeared
  bool appear()
    {
	/* TODO
	* was CL_Sprite object
	* Get something equivalent in SDL for
	*  update()
	* and is_finished()
	*/
        //appearing_sprite -> update();
//        psp_sdl_blit_on_screen(appearing_sprite);
     // if(appearing_sprite -> is_finished())
      //{
        //current_sprite = normal_sprite;
        return true;
      //}
   
      //return false;
    }

  // Return true if the piece is disappeared
  bool disappear()
    {
	/* TODO
	* was CL_Sprite object
	* Get something equivalent in SDL for
	*  update()
	* and is_finished()
	*/
//        disappearing_sprite -> update();
//        psp_sdl_blit_on_screen(disappearing_sprite);
//      if(disappearing_sprite -> is_finished())
//      {
        //current_sprite = normal_sprite;
        return true;
//      }
//      return false;


    }


  // Return true if the piece is placed
  bool fall(double time_interval)
    {
      y += (int)(PIECE_SPEED * time_interval);
      if(y >= target_y)
      {
        y = target_y;
        return true;
      }

      return false;
    }
    
  void set_score_value(int _score_value)
    {
      score_value = _score_value; 
    }

  int get_score_value()
    {
      return score_value;
    }

  void set_piece_number(int _piece_number)
    {
      piece_number = _piece_number;
      this -> score_value = score[piece_number];
    }

  int get_piece_number()
    {
      return piece_number;
    }

  // Setters
  void set_x(float x)
    {
      this -> x = x;
    }

  void set_y(float y)
    {
      this -> y = y;
    }

  void set_position(float x, float y)
  {
    this -> x = x;
    this -> y = y;
  }
  
  //Getters
  float get_x()
  {
    return x;
  }
  
  float get_y()
  {
    return y;
  }

  void print()
    {
      std::cout << "-----\nnormal_sprite: " << normal_sprite << "\n";
//        << "appearing_sprite: " << appearing_sprite << "\n"
  //              << "disappearing_spirte: " << disappearing_sprite << "\n";
               // << "current_sprite: " << current_sprite << "\n";
      /*if(current_sprite == appearing_sprite)// && appearing_sprite -> is_finished())
      {
        current_sprite = normal_sprite;
      }*/
    }



};


#endif
