/********************************************************************
                          OpenAlchemist

  File : OptionsMenuState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

//#include <ClanLib/core.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "OptionsMenuState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"
#include "../Preferences.h"
#include "../psp_sdl.h"


#define OPTIONS_ITEM_CHANGESKIN 0
#define OPTIONS_ITEM_FULLSCREEN 1
#define OPTIONS_ITEM_SOUND 2
#define OPTIONS_ITEM_MUSIC 3
#define OPTIONS_ITEM_QUIT 4

#define STEP_APPEARING 0
#define STEP_NORMAL 1
#define STEP_DISAPPEARING 2

#define APPEARING_SPEED 0.003

void OptionsMenuState::init()
{
  GameState::init();

  Preferences *pref = pref_get_instance();
  
  sound_level = pref -> sound_level;
  music_level = pref -> music_level;
}

void OptionsMenuState::deinit()
{
  Preferences *pref = pref_get_instance();
  
  pref -> sound_level = sound_level;
  pref -> music_level = music_level;

  pref -> write();
}

void OptionsMenuState::load_gfx(std::string skin)
{
  // Getting skins resources
/*  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("menu_options.xml", &zip, false);
*/
  // First, the sprites
  //background = new CL_Sprite("menu_options/dialog_background", &gfx); 
  background = IMG_Load_fromSkin(skin, "dialogs/options/background.png");

  //items[OPTIONS_ITEM_CHANGESKIN] = new CL_Sprite("menu_options/changeskin/unselected", &gfx);
  //items_selected[OPTIONS_ITEM_CHANGESKIN] = new CL_Sprite("menu_options/changeskin/selected", &gfx);
  items[OPTIONS_ITEM_CHANGESKIN] = IMG_Load_fromSkin(skin, "dialogs/options/changeskin-unselected.png");
  items_selected[OPTIONS_ITEM_CHANGESKIN] = IMG_Load_fromSkin(skin, "dialogs/options/changeskin-selected.png");

  //items[OPTIONS_ITEM_FULLSCREEN] = new CL_Sprite("menu_options/fullscreen/unselected", &gfx);
  //items_selected[OPTIONS_ITEM_FULLSCREEN] = new CL_Sprite("menu_options/fullscreen/selected", &gfx);
  items[OPTIONS_ITEM_FULLSCREEN] = IMG_Load_fromSkin(skin, "dialogs/options/fullscreen-unselected.png");
  items_selected[OPTIONS_ITEM_FULLSCREEN] = IMG_Load_fromSkin(skin, "dialogs/options/fullscreen-selected.png");

  //items[OPTIONS_ITEM_SOUND] = new CL_Sprite("menu_options/sound/unselected", &gfx);
  //items_selected[OPTIONS_ITEM_SOUND] = new CL_Sprite("menu_options/sound/selected", &gfx);
  items[OPTIONS_ITEM_SOUND] = IMG_Load_fromSkin(skin, "dialogs/options/sound-unselected.png");
  items_selected[OPTIONS_ITEM_SOUND] = IMG_Load_fromSkin(skin, "dialogs/options/sound-selected.png");

  //items[OPTIONS_ITEM_MUSIC] = new CL_Sprite("menu_options/music/unselected", &gfx);
  //items_selected[OPTIONS_ITEM_MUSIC] = new CL_Sprite("menu_options/music/selected", &gfx);
  items[OPTIONS_ITEM_MUSIC] = IMG_Load_fromSkin(skin, "dialogs/options/music-selected.png");
  items_selected[OPTIONS_ITEM_MUSIC] = IMG_Load_fromSkin(skin, "dialogs/options/music-unselected.png");

  //items[OPTIONS_ITEM_QUIT] = new CL_Sprite("menu_options/quit/unselected", &gfx);
  //items_selected[OPTIONS_ITEM_QUIT] = new CL_Sprite("menu_options/quit/selected", &gfx);
  items[OPTIONS_ITEM_QUIT] = IMG_Load_fromSkin(skin, "dialogs/options/quit-unselected.png");
  items_selected[OPTIONS_ITEM_QUIT] = IMG_Load_fromSkin(skin, "dialogs/options/quit-selected.png");

  
  for(int i=0; i<=10; ++i)
  {
   char path[30];
   sprintf(path, "dialogs/options/level-%d.png",i);
   //sound_level_sprites[i] = new CL_Sprite("menu_options/sound_level/"+to_string(i), &gfx);
   sound_level_sprites[i] = IMG_Load_fromSkin(skin, path);
  }


  // Then, propreties
 //TODO : resources manager for properties
  items_left[OPTIONS_ITEM_CHANGESKIN] = 50 ;//CL_Integer_to_int("menu_options/changeskin/left", &gfx);
  items_top[OPTIONS_ITEM_CHANGESKIN] = 60 ; //CL_Integer_to_int("menu_options/changeskin/top", &gfx);

  items_left[OPTIONS_ITEM_FULLSCREEN] = 50 ;//CL_Integer_to_int("menu_options/fullscreen/left", &gfx);
  items_top[OPTIONS_ITEM_FULLSCREEN] = 85 ;//CL_Integer_to_int("menu_options/fullscreen/top", &gfx);

  items_left[OPTIONS_ITEM_SOUND] = 50 ;//CL_Integer_to_int("menu_options/sound/left", &gfx);
  items_top[OPTIONS_ITEM_SOUND] = 110 ; //CL_Integer_to_int("menu_options/sound/top", &gfx);

  items_left[OPTIONS_ITEM_MUSIC] = 50 ;//CL_Integer_to_int("menu_options/music/left", &gfx);
  items_top[OPTIONS_ITEM_MUSIC] = 135 ; //CL_Integer_to_int("menu_options/music/top", &gfx);

  items_left[OPTIONS_ITEM_QUIT] = 50 ;//CL_Integer_to_int("menu_options/quit/left", &gfx);
  items_top[OPTIONS_ITEM_QUIT] = 160 ; //CL_Integer_to_int("menu_options/quit/top", &gfx);

  sound_level_left = 140 ; //CL_Integer_to_int("menu_options/sound_level/left", &gfx);

  
}

void OptionsMenuState::unload_gfx()
{
  for (int i=0; i<OPTIONS_NUMBER_OF_ITEMS; i++)
  {
     SDL_FreeSurface(items[i]);
     SDL_FreeSurface(items_selected[i]);
  }

  SDL_FreeSurface(background);

  for (int j=0; j<11; j++)
  {
     SDL_FreeSurface(sound_level_sprites[j]);
  }

}

void OptionsMenuState::draw()
{
//  int x = 400 - background -> get_width()/2;
//  int y = 300 - background -> get_height()/2;
  //TODO : choose or determine correct position of option menu
   // using PSP_SDL_SCREEN_WIDTH and PSP_SDL_SCREEN_HEIGHT
	//background -> draw(x,y);
   int x = PSP_SDL_SCREEN_WIDTH/2 - (background->w + background->w%2)/2;
   int y = PSP_SDL_SCREEN_HEIGHT/10;
   psp_sdl_blit_on_screen_at_XY(background, x, y);
  // Drawing 
  for(int i=0; i<OPTIONS_NUMBER_OF_ITEMS; ++i)
  {

    if(i == selection)
    {
     //items_selected[i] -> draw(x + items_left[i], y + items_top[i]);
     psp_sdl_blit_on_screen_at_XY(items_selected[i],(x + items_left[i]), (y + items_top[i]));
     //items_selected[i] -> update(common_resources -> time_interval);
     //TODO: find equivalent to CL_Sprite::update
     /* ???? SDL_Flip(screen_surface);*/
     
    }
    else
    {
     //items[i] -> draw(x + items_left[i], y + items_top[i]);
     psp_sdl_blit_on_screen_at_XY(items[i],x + items_left[i], y + items_top[i]);
     //items[i] -> update(common_resources -> time_interval);
     //TODO: find equivalent to CL_Sprite::update
     /* ???? SDL_Flip(screen_surface);*/
    }
  }

  // sound_level_sprites[sound_level] -> draw(x + sound_level_left, 
  //                                          y + items_top[OPTIONS_ITEM_SOUND]);
  psp_sdl_blit_on_screen_at_XY(sound_level_sprites[sound_level], 
                               x + sound_level_left, 
                               y + items_top[OPTIONS_ITEM_SOUND]);
  
  //sound_level_sprites[music_level] -> draw(x + sound_level_left, 
  //                                         y + items_top[OPTIONS_ITEM_MUSIC]);
  psp_sdl_blit_on_screen_at_XY(sound_level_sprites[music_level],
                               x + sound_level_left,
                               y + items_top[OPTIONS_ITEM_MUSIC]);
  
// TODO : SDL_Flip ??
//  sound_level_sprites[sound_level] -> update();
//  sound_level_sprites[music_level] -> update();

}

void OptionsMenuState::update()
{
  switch(step)
  {
  case STEP_APPEARING:
    appear();
    break;
  case STEP_DISAPPEARING:
    disappear();
    break;
  }
}

void OptionsMenuState::events()
{
  if(step != STEP_NORMAL)
    return;

  switch(common_resources->CurrentKeyPressed)
  {
   	 case KEY_ESCAPE:
         case KEY_OPTIONS :
 	 {   
 	   step = STEP_DISAPPEARING;
 	   selection = OPTIONS_ITEM_QUIT;
	   common_resources->CurrentKeyPressed = 0;
	   break;
  	 }
	
	  case KEY_SKINS:
	  {   
	   step = STEP_DISAPPEARING;
	   common_resources->CurrentKeyPressed = 0;
	   break;
	  }
	  case KEY_UP:
	  {
	    if(selection == 0)
	      selection = OPTIONS_ITEM_QUIT;
	    else
	    {
	      selection --;
	    }
	   common_resources->CurrentKeyPressed = 0;
	   break;
	  }
	
	  case KEY_DOWN:
	  {
	    if(selection == OPTIONS_ITEM_QUIT)
	      selection = 0;
	    else
	    {
	      selection ++;
	    }
	  common_resources->CurrentKeyPressed = 0;
	  break;
	  }
	
	  case KEY_LEFT: 
	  {
	   if(selection == OPTIONS_ITEM_SOUND)
	    if(sound_level > 0)
	      sound_level--;
           if(selection == OPTIONS_ITEM_MUSIC )
	    if(music_level > 0)
	      music_level--;
	  common_resources->CurrentKeyPressed = 0;
	  break;
	  }

	  case KEY_RIGHT:
	  {
	   if(selection == OPTIONS_ITEM_SOUND)
	    if(sound_level < 10)
	      sound_level++;
	   if(selection == OPTIONS_ITEM_MUSIC)
	    if(music_level < 10)
	      music_level++;
	  common_resources->CurrentKeyPressed = 0;
	  break;
	  }
	
	  case KEY_ENTER:
	  {    
	    switch(selection)
	    {
	    case OPTIONS_ITEM_FULLSCREEN:
	      common_resources -> engine -> toggle_screen();
	      break;
	    case OPTIONS_ITEM_CHANGESKIN:
	    case OPTIONS_ITEM_QUIT:
	      step = STEP_DISAPPEARING;
	      break;
	    }
	  common_resources->CurrentKeyPressed = 0;
	  break;
	  }
	}
}	
void OptionsMenuState::appear()
{ 
  if(alpha + (int)(ALPHA_OPAQUE * APPEARING_SPEED*common_resources -> time_interval) >= ALPHA_OPAQUE)
  {
    step = STEP_NORMAL;
    alpha = SDL_ALPHA_OPAQUE;
  }
  else
    alpha += (int)(ALPHA_OPAQUE * APPEARING_SPEED * common_resources -> time_interval);

  //TODO: see wether SDL has alpha features
  //background -> set_alpha(alpha);
  SDL_SetAlpha(background,SDL_SRCALPHA, alpha);
  psp_sdl_blit_on_screen(background);
  for(int i=0; i<OPTIONS_NUMBER_OF_ITEMS; ++i)
  {
    //items[i] -> set_alpha(alpha);
    SDL_SetAlpha(items[i], SDL_SRCALPHA, alpha);
    psp_sdl_blit_on_screen(items[i]);
    //items_selected[i] -> set_alpha(alpha);
    SDL_SetAlpha(items_selected[i], SDL_SRCALPHA, alpha);
    psp_sdl_blit_on_screen(items_selected[i]);
    
  }

//  sound_level_sprites[sound_level] -> set_alpha(alpha);
//  sound_level_sprites[music_level] -> set_alpha(alpha);
  SDL_SetAlpha(sound_level_sprites[sound_level], SDL_SRCALPHA, alpha);
  psp_sdl_blit_on_screen(sound_level_sprites[sound_level]);
  SDL_SetAlpha(sound_level_sprites[music_level], SDL_SRCALPHA , alpha);
  psp_sdl_blit_on_screen(sound_level_sprites[music_level]);

}

void OptionsMenuState::disappear()
{  
  alpha -= (int)(ALPHA_OPAQUE * APPEARING_SPEED * common_resources -> time_interval);

  //background -> set_alpha(alpha);
  SDL_SetAlpha(background,SDL_SRCALPHA, alpha);	
  psp_sdl_blit_on_screen(background);

  for(int i=0; i<OPTIONS_NUMBER_OF_ITEMS; ++i)
  {
    //items[i] -> set_alpha(alpha);
    SDL_SetAlpha(items[i], SDL_SRCALPHA, alpha);
    psp_sdl_blit_on_screen(items[i]);
    //items_selected[i] -> set_alpha(alpha);
    SDL_SetAlpha(items_selected[i], SDL_SRCALPHA, alpha);
    psp_sdl_blit_on_screen(items_selected[i]);
  }

//  sound_level_sprites[sound_level] -> set_alpha(alpha);
//  sound_level_sprites[music_level] -> set_alpha(alpha);
  SDL_SetAlpha(sound_level_sprites[sound_level], SDL_SRCALPHA, alpha);
  psp_sdl_blit_on_screen(sound_level_sprites[sound_level]);
  SDL_SetAlpha(sound_level_sprites[music_level], SDL_SRCALPHA, alpha);
  psp_sdl_blit_on_screen(sound_level_sprites[music_level]);



  if(alpha <= ALPHA_TRANSPARENT || !common_resources -> engine -> is_opengl_used())
  {
    switch(selection)
    {
    case OPTIONS_ITEM_CHANGESKIN:
      common_resources -> engine -> stop_current_state();
      common_resources -> engine -> set_state_skin_menu();
      break;
    default:
      common_resources -> engine -> stop_current_state();           
    }
  }
 
}

void OptionsMenuState::start()
{
  selection = 0;
  if(common_resources -> engine -> is_opengl_used())
  {
    step = STEP_APPEARING;
    alpha = SDL_ALPHA_TRANSPARENT;
  }
  else
  {
    step = STEP_NORMAL;
  }
}

bool OptionsMenuState::front_layer_behind()
{
  return true;
}

void OptionsMenuState::print()
{
  printf("OptionsMenuState\n");
}


OptionsMenuState::OptionsMenuState()
{

}

OptionsMenuState::~OptionsMenuState()
{
  deinit();
}



