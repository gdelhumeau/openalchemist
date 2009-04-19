/********************************************************************
                          OpenAlchemist

  File : TitleState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

//#include <ClanLib/core.h>

#include "TitleState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"
#include "../psp_sdl.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

extern "C"{
void psp_sdl_blit_on_screen_at_XY(SDL_Surface * surface, int surface_x, int surface_y);
}


void TitleState::init()
{
  GameState::init();
  for(int i=0; i<NUMBER_OF_SENTENCES; ++i)
  {
      sentences[i] = NULL;
  }
  start_message   = NULL;

  for(int i = 0; i < NUMBER_OF_KEYS; i++)
  {
       keydemo[i] = NULL;
  }

  blinking_steps  = 0;
  blink_clip      = 0;
}

void TitleState::deinit()
{
}

void TitleState::load_gfx(std::string skin)
{
  // Getting skins resources
  /*CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("title.xml", &zip, false);
*/
  unload_gfx();
  //start_message = new CL_Sprite("title/start_message/sprite", &gfx);
  start_message = IMG_Load_fromSkin(skin, "dialogs/title/start_message.png");
//  start_message_x = PSP_SDL_SCREEN_WIDTH - start_message->w ; //CL_Integer_to_int("title/start_message/left", &gfx);
//  start_message_y = PSP_SDL_SCREEN_HEIGHT - start_message->h ;  //CL_Integer_to_int("title/start_message/top", &gfx);

  for(int i=0; i<NUMBER_OF_SENTENCES; ++i)
  {
    char spriteToLoad[256];
    sprintf(spriteToLoad, "dialogs/title/sentences/%02d.png",i+1);
    sentences[i] = IMG_Load_fromSkin(skin, spriteToLoad);
    
    sentences_x[i]    = 120 ; //CL_Integer_to_int("title/help/"+to_string(i+1)+"/left", &gfx);
    sentences_y[i]    = 120 ; //CL_Integer_to_int("title/help/"+to_string(i+1)+"/top", &gfx);
    sentences_time[i] = 3000; //CL_Integer_to_int("title/help/"+to_string(i+1)+"/time", &gfx);
  }

  //keydemo_left    = new CL_Sprite("title/keydemo/left", &gfx);
  //keydemo_up      = new CL_Sprite("title/keydemo/up", &gfx);
  //keydemo_right   = new CL_Sprite("title/keydemo/right", &gfx);
  //keydemo_down    = new CL_Sprite("title/keydemo/down", &gfx);
  //keydemo_escape  = new CL_Sprite("title/keydemo/escape", &gfx);
  //keydemo_options = new CL_Sprite("title/keydemo/options", &gfx);
/*  keydemo[LEFT]    = IMG_Load_fromSkin(skin, "dialogs/title/key-left.png"); 
  keydemo[UP]      = IMG_Load_fromSkin(skin, "dialogs/title/key-up.png");
  keydemo[RIGHT]   = IMG_Load_fromSkin(skin, "dialogs/title/key-right.png");
  keydemo[DOWN]    = IMG_Load_fromSkin(skin, "dialogs/title/key-down.png");*/
  keydemo[ESCAPE]  = IMG_Load_fromSkin(skin, "dialogs/title/key-escape.png");
  keydemo[OPTIONS] = IMG_Load_fromSkin(skin, "dialogs/title/key-options.png");

  keydemo[LEFT]    = IMG_Load_fromSkin("common", "left_clip.png"); 
  keydemo[UP]      = IMG_Load_fromSkin("common", "up_clip.png");
  keydemo[RIGHT]   = IMG_Load_fromSkin("common", "right_clip.png");
  keydemo[DOWN]    = IMG_Load_fromSkin("common", "down_clip.png");
  keydemo[ROTATE]  = IMG_Load_fromSkin("common", "cross_clip.png");
//  keydemo[ESCAPE]  = IMG_Load_fromSkin(skin, "dialogs/title/key-escape.png");
//  keydemo[OPTIONS] = IMG_Load_fromSkin(skin, "dialogs/title/key-options.png");

  /* We assume that all those pics are same size and ratio, so we take one to compute clips coord */
  for (int j = 0; j<NUMBER_OF_KEYS; j++)
  {
    for (int i = 0; i<NUMBER_OF_PIC_BLINK ; i++)
    {
      keydemo_tab_clips[i][j].x = i*(keydemo[j] -> w / NUMBER_OF_PIC_BLINK);
      keydemo_tab_clips[i][j].y = 0;
      keydemo_tab_clips[i][j].w = (keydemo[j] -> w / NUMBER_OF_PIC_BLINK);
      keydemo_tab_clips[i][j].h = keydemo[j] -> h;
    }
  }

  arrow_key_x = 125;
  arrow_key_y = 160;
  round_key_x = arrow_key_x + keydemo[LEFT]->w/2 - keydemo[ROTATE]->w/2;
  round_key_y = arrow_key_y + keydemo[LEFT]->h/2 - keydemo[ROTATE]->h/2;
  
  demo_player.load_gfx(skin);
}

void TitleState::unload_gfx()
{
  for(int i=0; i<NUMBER_OF_SENTENCES; ++i)
  {
    if(sentences[i])
    {
      SDL_FreeSurface (sentences[i]);
      sentences[i] = NULL;
    }
  }
  
  if(start_message)
  {
    SDL_FreeSurface (start_message);
    start_message = NULL;
  }

  for(int i = 0; i < NUMBER_OF_KEYS; i++)
  {
    if(keydemo[i]!=NULL)
    {
       SDL_FreeSurface(keydemo[i]);
       keydemo[i] = NULL;
    }
  }
 
}

void TitleState::draw()
{
  if(blinking_steps == BLINK_REMANENCE)
  {
     blinking_steps = 0;
     blink_clip++;
     if(blink_clip == NUMBER_OF_PIC_BLINK)
     {
        blink_clip = 0; 
     }
  }
  else
  {
     blinking_steps++;
  }
  
  //sentences[step] -> draw (sentences_x[step], sentences_y[step]);
  if (sentences[step] != NULL)
  {
  	psp_sdl_blit_on_screen_at_XY(sentences[step], sentences_x[step], sentences_y[step]);
  }
  else
	printf(" le pointeur sur l'image load est foireux");
  
  //start_message -> draw(start_message_x,start_message_y);
  if(blink_clip != 0)
    psp_sdl_blit_on_screen_at_XY(start_message, PSP_SDL_SCREEN_WIDTH - start_message->w, 
					        PSP_SDL_SCREEN_HEIGHT - start_message->h );

  switch(step)
  {
  case 2: /// Key_left Demo 
    psp_sdl_blit_clip_at_XY(keydemo[LEFT], &keydemo_tab_clips[blink_clip][LEFT],
                                 arrow_key_x,
			         arrow_key_y);
// Draw fix pads also
    psp_sdl_blit_clip_at_XY(keydemo[RIGHT], &keydemo_tab_clips[0][RIGHT],
                                 arrow_key_x,
			         arrow_key_y);
    psp_sdl_blit_clip_at_XY(keydemo[UP], &keydemo_tab_clips[0][UP],
                                 arrow_key_x,
			         arrow_key_y);
    psp_sdl_blit_clip_at_XY(keydemo[DOWN], &keydemo_tab_clips[0][DOWN],
                                 arrow_key_x,
			         arrow_key_y);

    break;

  case 3: /// Key_right Demo 
    psp_sdl_blit_clip_at_XY(keydemo[RIGHT], &keydemo_tab_clips[blink_clip][RIGHT], 
                                 arrow_key_x,
			         arrow_key_y);
// Draw fix pads also
    psp_sdl_blit_clip_at_XY(keydemo[LEFT], &keydemo_tab_clips[0][LEFT],
                                 arrow_key_x,
			         arrow_key_y);
    psp_sdl_blit_clip_at_XY(keydemo[UP], &keydemo_tab_clips[0][UP],
                                 arrow_key_x,
			         arrow_key_y);
    psp_sdl_blit_clip_at_XY(keydemo[DOWN], &keydemo_tab_clips[0][DOWN],
                                 arrow_key_x,
			         arrow_key_y);
    break;

  case 4: /// keydemo rotate Demo 
    psp_sdl_blit_clip_at_XY(keydemo[ROTATE], &keydemo_tab_clips[blink_clip][ROTATE], 
				round_key_x,
				round_key_y);
    break;
  case 5:
  case 7: /// keydemo FALL Demo 
    psp_sdl_blit_clip_at_XY(keydemo[DOWN], &keydemo_tab_clips[blink_clip][DOWN], 
				arrow_key_x,
				arrow_key_y);
// Draw fix pads also
    psp_sdl_blit_clip_at_XY(keydemo[LEFT], &keydemo_tab_clips[0][LEFT],
                                 arrow_key_x,
			         arrow_key_y);
    psp_sdl_blit_clip_at_XY(keydemo[UP], &keydemo_tab_clips[0][UP],
                                 arrow_key_x,
			         arrow_key_y);
    psp_sdl_blit_clip_at_XY(keydemo[RIGHT], &keydemo_tab_clips[0][RIGHT],
                                 arrow_key_x,
			         arrow_key_y);
    break;
  case 6: /// move Demo 
    psp_sdl_blit_clip_at_XY(keydemo[RIGHT], &keydemo_tab_clips[blink_clip][RIGHT], 
                                 arrow_key_x,
			         arrow_key_y);
    psp_sdl_blit_clip_at_XY(keydemo[LEFT], &keydemo_tab_clips[(blink_clip+1)%2][LEFT],
                                 arrow_key_x,
			         arrow_key_y);
// Draw fix pads also
    psp_sdl_blit_clip_at_XY(keydemo[UP], &keydemo_tab_clips[0][UP],
                                 arrow_key_x,
			         arrow_key_y);
    psp_sdl_blit_clip_at_XY(keydemo[DOWN], &keydemo_tab_clips[0][DOWN],
                                 arrow_key_x,
			         arrow_key_y);

    break;
  case 12: /// keydemo_escape Demo 
    psp_sdl_blit_clip_at_XY(keydemo[ESCAPE], &keydemo_tab_clips[blink_clip][ESCAPE],
				sentences_x[step] + sentences[step] -> w/2 - keydemo[ESCAPE] -> w/2, 
				sentences_y[step] + sentences[step] -> h);
    //keydemo_escape -> update();
    //psp_sdl_flip();
    break;
  case 13: /// keydemo_options Demo 
    psp_sdl_blit_clip_at_XY(keydemo[OPTIONS], &keydemo_tab_clips[blink_clip][OPTIONS],
				sentences_x[step] + sentences[step] -> w/2 - keydemo[OPTIONS] -> w/2, 
				sentences_y[step] + sentences[step] -> h);
    break;
    break;
    
  }
  
}

void TitleState::update()
{
  //start_message -> update();
  //psp_sdl_blit_on_screen(start_message);
//  psp_sdl_flip();
  if(next_time < SDL_GetTicks())
  {
    step = (step + 1) % NUMBER_OF_SENTENCES;
    next_time = SDL_GetTicks() + sentences_time[step];
    //sentences[step] -> update();
    //psp_sdl_blit_on_screen(start_message);
  //  psp_sdl_flip();
  }

  switch(step)
  {
    // Welcome to OpenAlchemist !
  case 0:
    new_game = false;
    break;

    // This is your pieces
  case 1:
    if(!new_game)
    {
      new_game = true;
      demo_player.new_game();
    }
    break;

    // You can move them to the left...
  case 2:
    demo_player.move_left();
    break;

    // ...or to the right !
  case 3:
    demo_player.move_right();
    change_angle = false;
    break;

    // You can also rotate pieces...
  case 4:
    if(!change_angle)
    {
      demo_player.change_angle();
      change_angle = true;
    }
    fall = false;
    break;

    // ...and make them fall !
  case 5:
    if(!fall)
    {
      demo_player.fall();
      fall = true;
      select_the_position = false;
    }
    break;

    // Select the position...
  case 6:
    if(!select_the_position)
    {
      select_the_position = true;
      demo_player.move_left();
      fall = false;
    }
    break;

    // ...and fall !
  case 7:
    if(!fall)
    {
      demo_player.fall();
      fall = true;
    }
    break;

    // When you have more than 3 same items...
  case 8:
    break;

    // ...they're destroyed...
  case 9:
    break;

    // ...and a new one is created !
  case 10:
    break;

    // Align more than 3 items and you get bonus !
  case 11:
    break;

    // You can also open the game menu...
  case 12:
    break;

    // ...or the options menu !
  case 13:
    break;

    // Now you know everything...
  case 14:
    break;

    // ...so start a new game and have fun !
  case 15:
    break;
  }

  demo_player.update();
}

void TitleState::events()
{

//printf("in TitleState events :\n");
switch(common_resources->CurrentKeyPressed)
{
  case KEY_ENTER:
  {
    printf("in TitleState key.enter event got\n");
    common_resources -> engine -> set_state_ingame();
    common_resources -> player1.new_game();
    common_resources->CurrentKeyPressed = 0;
    break;
  }

  case KEY_ESCAPE:
  {
    printf("in TitleState key.escape event got\n");
    common_resources -> engine -> set_state_pause_menu();
    common_resources->CurrentKeyPressed = 0;
    break;
  }

  case KEY_SKINS:
  {
    printf("in TitleState key.skins event got\n");
    common_resources -> engine -> set_state_skin_menu();
    common_resources->CurrentKeyPressed = 0;
    break;
  }

  case KEY_OPTIONS:
  {
    printf("in TitleState key.options event got\n");
    common_resources -> engine -> set_state_options_menu();
    common_resources->CurrentKeyPressed = 0;
    break;
  }
}
}

bool TitleState::front_layer_behind()
{
  return true;
}

TitleState::TitleState()
{
  start_message   = NULL;
  for(int i = 0; i < NUMBER_OF_KEYS; i++)
  {
       keydemo[i] = NULL;
  }

  for(int i=0; i<NUMBER_OF_SENTENCES; ++i)
  {
    sentences[i] = NULL;
  }
}

TitleState::~TitleState()
{
  unload_gfx();
}

void TitleState::print()
{
  printf("TitleState\n");
}


void TitleState::start()
{
  step = 0;
  next_time = SDL_GetTicks() + 5000;
  common_resources -> current_player = &demo_player;
  demo_player.new_game();
}
