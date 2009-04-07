/********************************************************************
                          OpenAlchemist

  File : GameOverState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include "GameOverState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"
#include "../psp_sdl.h"

void GameOverState::init()
{
  GameState::init();
  selection = GAMEOVER_SELECTION_YES;
}

void GameOverState::deinit()
{

}

void GameOverState::load_gfx(std::string skin)
{
  // Getting skins resources
/*  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("menu_gameover.xml", &zip, false);*/

  //new CL_Sprite("menu_gameover/dialog_gameover", &gfx);
  dialog_gameover = IMG_Load_fromSkin(skin, "dialogs/gameover/dialog-gameover.png");
  // new CL_Sprite("menu_gameover/dialog_highscore", &gfx);
  dialog_highscore = IMG_Load_fromSkin(skin, "dialogs/gameover/dialog-highscore.png");

  dialog_x = PSP_SDL_SCREEN_WIDTH/2 - (dialog_gameover->w + dialog_gameover->w%2)/2; //CL_Integer_to_int("menu_gameover/dialog_left", &gfx);
  dialog_y = PSP_SDL_SCREEN_HEIGHT/2 - (dialog_gameover->h + dialog_gameover->h%2)/2;  //CL_Integer_to_int("menu_gameover/dialog_top", &gfx);

  score1_x = PSP_SDL_SCREEN_WIDTH/2; //CL_Integer_to_int("menu_gameover/score1_left", &gfx);
  score1_y = 80;  //CL_Integer_to_int("menu_gameover/score1_top", &gfx);

  score2_x = PSP_SDL_SCREEN_WIDTH/2; //CL_Integer_to_int("menu_gameover/score2_left", &gfx);
  score2_y = 130; //CL_Integer_to_int("menu_gameover/score2_top", &gfx);

  //yes_selected = new CL_Sprite("menu_gameover/new_game_question/yes/selected", &gfx);
  //yes_unselected = new CL_Sprite("menu_gameover/new_game_question/yes/unselected", &gfx);
  yes_selected = IMG_Load_fromSkin(skin, "dialogs/gameover/yes-selected.png");
  yes_unselected = IMG_Load_fromSkin(skin, "dialogs/gameover/yes-unselected.png");
  //were CL_Sprites too for the NO...
  no_selected = IMG_Load_fromSkin(skin, "dialogs/gameover/no-selected.png");
  no_unselected = IMG_Load_fromSkin(skin, "dialogs/gameover/no-unselected.png");

  yes_x = PSP_SDL_SCREEN_WIDTH*3/10;;  //CL_Integer_to_int("menu_gameover/new_game_question/yes/left", &gfx);
  yes_y = PSP_SDL_SCREEN_HEIGHT*3/4;;  //CL_Integer_to_int("menu_gameover/new_game_question/yes/top", &gfx);

  no_x =  PSP_SDL_SCREEN_WIDTH*6/10;  //CL_Integer_to_int("menu_gameover/new_game_question/no/left", &gfx);
  no_y =  PSP_SDL_SCREEN_HEIGHT*3/4;  //CL_Integer_to_int("menu_gameover/new_game_question/no/top", &gfx);

}


void GameOverState::unload_gfx()
{

  if(dialog_gameover)
  {
    delete dialog_gameover;
    dialog_gameover = NULL;
  }

  if(dialog_highscore)
  {
    delete dialog_highscore;
    dialog_highscore = NULL;
  }


  if(yes_selected)
  {
    delete yes_selected;
    yes_selected = NULL;
  }

  if(yes_unselected)
  {
    delete yes_unselected;
    yes_unselected = NULL;
  }

  if(no_selected)
  {
    delete no_selected;
    no_selected = NULL;
  }

  if(no_unselected)
  {
    delete no_unselected;
    no_unselected = NULL;
  }

}

void GameOverState::draw()
{
  //dialog -> draw(dialog_x, dialog_y);
  psp_sdl_blit_on_screen_at_XY(dialog, dialog_x, dialog_y);

  if(MODE_HIGHSCORE == mode)
  {
    std::string new_score = to_string(common_resources -> highscore);
    std::string old_score = to_string(common_resources -> old_highscore);

    common_resources -> main_font -> draw(score1_x, score1_y, new_score);
    common_resources -> main_font -> draw(score2_x, score2_y, old_score);
  }
  else
  {
    std::string current_score = to_string(common_resources -> player1.get_score());
    std::string highscore = to_string(common_resources -> highscore);

    common_resources -> main_font -> draw(score1_x, score1_y, current_score);
    common_resources -> main_font -> draw(score2_x, score2_y, highscore);
  }

  if(selection == GAMEOVER_SELECTION_YES)
  {
    //yes_selected -> draw(yes_x, yes_y);
    psp_sdl_blit_on_screen_at_XY(yes_selected, yes_x, yes_y);
    //no_unselected  -> draw(no_x, no_y);
    psp_sdl_blit_on_screen_at_XY(no_unselected, no_x, no_y);
  }
  else
  {
    //yes_unselected -> draw(yes_x, yes_y);
    psp_sdl_blit_on_screen_at_XY(yes_unselected, yes_x, yes_y);
    //no_selected  -> draw(no_x, no_y);
    psp_sdl_blit_on_screen_at_XY(no_selected, no_x, no_y);
  }
}

void GameOverState::update()
{
  
}

void GameOverState::events()
{
  switch(common_resources->CurrentKeyPressed)
  {
	case KEY_ENTER:
  	{
		if(selection == GAMEOVER_SELECTION_YES)
    		{
      		  common_resources -> engine -> stop_current_state();
      		  common_resources -> engine -> set_state_ingame();
      		  common_resources -> player1.new_game();
    		}
    		else
    		{
    		  common_resources -> engine -> stop_current_state();
      		  common_resources -> engine -> set_state_title();
    		}
	common_resources->CurrentKeyPressed = 0;
	break;
  	}

  	case KEY_RETRY:
  	{
  	  common_resources -> engine -> stop_current_state();
  	  common_resources -> engine -> set_state_ingame();
  	  common_resources -> player1.new_game();
	  common_resources->CurrentKeyPressed = 0;
  	  break;
  	}

  	case KEY_UNDO:
  	{
  	  common_resources -> engine -> set_state_ingame();
  	  common_resources -> player1.undo();
	  common_resources->CurrentKeyPressed = 0;
  	  break;
  	}

  	case KEY_PAUSE:
  	case KEY_ESCAPE:
  	{
  	  common_resources -> engine -> stop_current_state();
  	  common_resources -> engine -> set_state_title();
//	    common_resources -> engine -> set_state_pause_menu();
	  common_resources->CurrentKeyPressed = 0;
	  break;
  	}

  	case KEY_SKINS:
  	{
  	  common_resources -> engine -> set_state_skin_menu();
  	  common_resources->CurrentKeyPressed = 0;
	  break;
  	}

  	case KEY_LEFT:
  	{
  	  selection = GAMEOVER_SELECTION_YES;
	  common_resources->CurrentKeyPressed = 0;
	  break;
  	}

  	case KEY_RIGHT:
  	{
  	  selection = GAMEOVER_SELECTION_NO;
	  common_resources->CurrentKeyPressed = 0;
	  break;
  	}

   }

}

bool GameOverState::front_layer_behind()
{
  return true;
}

void GameOverState::set_mode(int mode)
{
  this -> mode = mode;
  if(mode == MODE_GAMEOVER)
  {
    dialog = dialog_gameover;
  }
  else
  {
    dialog = dialog_highscore;
  }
}

void GameOverState::start()
{
  selection = GAMEOVER_SELECTION_YES;
}


void GameOverState::print()
{
  printf("GameOverState\n");
}

GameOverState::GameOverState()
{
  dialog_gameover  = NULL;
  dialog_highscore = NULL;

  yes_selected     = NULL;
  yes_unselected   = NULL;
  no_selected      = NULL;
  no_unselected    = NULL;
}

GameOverState::~GameOverState()
{
  unload_gfx();
}

