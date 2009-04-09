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
  keydemo_left    = NULL;
  keydemo_up      = NULL;
  keydemo_right   = NULL;
  keydemo_down    = NULL;
  keydemo_escape  = NULL;
  keydemo_options = NULL;
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
  start_message_x = 220 ; //CL_Integer_to_int("title/start_message/left", &gfx);
  start_message_y = 40 ;  //CL_Integer_to_int("title/start_message/top", &gfx);

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
  keydemo_left    = IMG_Load_fromSkin(skin, "dialogs/title/key-left.png");
  keydemo_up      = IMG_Load_fromSkin(skin, "dialogs/title/key-up.png");
  keydemo_right   = IMG_Load_fromSkin(skin, "dialogs/title/key-right.png");
  keydemo_down    = IMG_Load_fromSkin(skin, "dialogs/title/key-down.png");
  keydemo_escape  = IMG_Load_fromSkin(skin, "dialogs/title/key-escape.png");
  keydemo_options = IMG_Load_fromSkin(skin, "dialogs/title/key-options.png");


  keyleft_x = 120;
  keyleft_y = keyright_y = keydown_y = 150;
  keyup_x = keydown_x = 190;
  keyup_y = 120;
  keyright_x = 220;

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

  if(keydemo_left)
  {
    SDL_FreeSurface (keydemo_left);
    keydemo_left = NULL;
  }

  if(keydemo_up)
  {
    SDL_FreeSurface (keydemo_up);
    keydemo_up = NULL;
  }

  if(keydemo_right)
  {
    SDL_FreeSurface (keydemo_right);
    keydemo_right = NULL;
  }

  if(keydemo_down)
  {
    SDL_FreeSurface (keydemo_down);
    keydemo_down = NULL;
  }

  if(keydemo_escape)
  {
    SDL_FreeSurface (keydemo_escape);
    keydemo_escape = NULL;
  }

  if(keydemo_options)
  {
    SDL_FreeSurface (keydemo_options);
    keydemo_options = NULL;
  }

}

void TitleState::draw()
{
  //sentences[step] -> draw (sentences_x[step], sentences_y[step]);
 /* if (sentences[step] != NULL)
  {
  	psp_sdl_blit_on_screen_at_XY(sentences[step], sentences_x[step], sentences_y[step]);
  }
  else
	printf(" le pointeur sur l'image load est foireux");
*/
  //start_message -> draw(start_message_x,start_message_y);
  psp_sdl_blit_on_screen_at_XY(start_message, start_message_x, start_message_y);

  switch(step)
  {
  case 2: /// Key_left Demo TODO : Use clips to make draw blink, change picture
    psp_sdl_blit_on_screen_at_XY(keydemo_left,
                                 sentences_x[step]+sentences[step] -> w/2-keydemo_left -> w/2,
			         sentences_y[step] + sentences[step] -> h);
    break;

  case 3: /// Key_right Demo TODO : Use clips to make draw blink, change picture
    psp_sdl_blit_on_screen_at_XY(keydemo_right, 
                                 sentences_x[step] + sentences[step] -> w/2 - keydemo_left -> w/2,
			         sentences_y[step] + sentences[step] -> h);
    break;

  case 4: /// keydemo_up Demo TODO : Use clips to make draw blink, change picture
    psp_sdl_blit_on_screen_at_XY(keydemo_up, sentences_x[step] + sentences[step] -> w/2 - keydemo_left -> w/2,
			 sentences_y[step] + sentences[step] -> h);
    break;
  case 5:
  case 7: /// keydemo_down Demo TODO : Use clips to make draw blink, change picture
    psp_sdl_blit_on_screen_at_XY(keydemo_down,sentences_x[step] + sentences[step] -> w/2 - keydemo_left -> w/2,
			 sentences_y[step] + sentences[step] -> h);
    break;
  case 6: /// move Demo TODO : Use clips to make draw blink, change picture
    psp_sdl_blit_on_screen_at_XY(keydemo_left, 
                         sentences_x[step] + sentences[step] -> w/2 - keydemo_left -> w,
                         sentences_y[step] + sentences[step] -> h);
    psp_sdl_blit_on_screen_at_XY(keydemo_right, 
                             sentences_x[step] + sentences[step] -> w/2 + keydemo_left -> w,
                             sentences_y[step] + sentences[step] -> h);
    break;
  case 12: /// keydemo_escape Demo TODO : Use clips to make draw blink, change picture
    psp_sdl_blit_on_screen_at_XY(keydemo_escape, 
             sentences_x[step] + sentences[step] -> w/2 - keydemo_left -> w/2, sentences_y[step] + sentences[step] -> h);
    //keydemo_escape -> update();
    //psp_sdl_flip();
    break;
  case 13: /// keydemo_options Demo TODO : Use clips to make draw blink, change picture
    psp_sdl_blit_on_screen_at_XY(keydemo_options, 
                   sentences_x[step] + sentences[step] -> w/2 - keydemo_left -> w/2, sentences_y[step] + sentences[step] -> h);
    break;
    break;
    
  }
}

void TitleState::update()
{
  //start_message -> update();
  psp_sdl_blit_on_screen(start_message);
//  psp_sdl_flip();
  if(next_time < SDL_GetTicks())
  {
    step = (step + 1) % NUMBER_OF_SENTENCES;
    next_time = SDL_GetTicks() + sentences_time[step];
    //sentences[step] -> update();
    psp_sdl_blit_on_screen(start_message);
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
  keydemo_left    = NULL;
  keydemo_up      = NULL;
  keydemo_right   = NULL;
  keydemo_down    = NULL;
  keydemo_escape  = NULL;
  keydemo_options = NULL;

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
