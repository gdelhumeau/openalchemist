/********************************************************************
                          OpenAlchemist

  File : TitleState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <ClanLib/core.h>

#include "TitleState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"



void TitleState::init()
{
  GameState::init();
}

void TitleState::deinit()
{
}

void TitleState::load_gfx(std::string skin)
{
  // Getting skins resources
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("title.xml", &zip, false);

  start_message = new CL_Sprite("start-message", &gfx);
  start_message_x = CL_Integer_to_int("start-message-left", &gfx);
  start_message_y = CL_Integer_to_int("start-message-top", &gfx);

  for(int i=0; i<NUMBER_OF_SENTENCES; ++i)
  {
    sentences[i] = new CL_Sprite("help/"+to_string(i+1)+"/sentence", &gfx);
    sentences_x[i] = CL_Integer_to_int("help/"+to_string(i+1)+"/left", &gfx);
    sentences_y[i] = CL_Integer_to_int("help/"+to_string(i+1)+"/top", &gfx);
    sentences_time[i] = CL_Integer_to_int("help/"+to_string(i+1)+"/time", &gfx);
  }

  keydemo_left    = new CL_Sprite("keydemo/left", &gfx);
  keydemo_up      = new CL_Sprite("keydemo/up", &gfx);
  keydemo_right   = new CL_Sprite("keydemo/right", &gfx);
  keydemo_down    = new CL_Sprite("keydemo/down", &gfx);
  keydemo_escape  = new CL_Sprite("keydemo/escape", &gfx);
  keydemo_options = new CL_Sprite("keydemo/options", &gfx);

  keyleft_x = 50;
  keyleft_y = keyright_y = keydown_y = 100;
  keyup_x = keydown_x = 100;
  keyup_y = 50;
  keyright_x = 150;

  demo_player.load_gfx(skin);
   
}

void TitleState::unload_gfx()
{
  for(int i=0; i<NUMBER_OF_SENTENCES; ++i)
  {
    if(sentences[i])
    {
      delete sentences[i];
      sentences[i] = NULL;
    }
  }
  
  if(start_message)
  {
    delete start_message;
    start_message = NULL;
  }

  if(keydemo_left)
  {
    delete keydemo_left;
    keydemo_left = NULL;
  }

  if(keydemo_up)
  {
    delete keydemo_up;
    keydemo_up = NULL;
  }

  if(keydemo_right)
  {
    delete keydemo_right;
    keydemo_right = NULL;
  }

  if(keydemo_down)
  {
    delete keydemo_down;
    keydemo_down = NULL;
  }

  if(keydemo_escape)
  {
    delete keydemo_escape;
    keydemo_escape = NULL;
  }

  if(keydemo_options)
  {
    delete keydemo_options;
    keydemo_options = NULL;
  }

}

void TitleState::draw()
{
  sentences[step] -> draw (sentences_x[step], sentences_y[step]);

  start_message -> draw(start_message_x,start_message_y);

  switch(step)
  {
  case 2:
    keydemo_left -> draw(sentences_x[step] + sentences[step] -> get_width()/2 - keydemo_left -> get_width()/2,
			 sentences_y[step] + sentences[step] -> get_height());
    keydemo_left -> update();
    break;
  case 3:
    keydemo_right -> draw(sentences_x[step] + sentences[step] -> get_width()/2 - keydemo_left -> get_width()/2,
			 sentences_y[step] + sentences[step] -> get_height());
    keydemo_right -> update();
    break;
  case 4:
    keydemo_up -> draw(sentences_x[step] + sentences[step] -> get_width()/2 - keydemo_left -> get_width()/2,
			 sentences_y[step] + sentences[step] -> get_height());
    keydemo_up -> update();
    break;
  case 5:
  case 7:
    keydemo_down -> draw(sentences_x[step] + sentences[step] -> get_width()/2 - keydemo_left -> get_width()/2,
			 sentences_y[step] + sentences[step] -> get_height());
    keydemo_down -> update();
    break;
  case 6:
    keydemo_left -> draw(sentences_x[step] + sentences[step] -> get_width()/2 - keydemo_left -> get_width(),
			 sentences_y[step] + sentences[step] -> get_height());
    keydemo_left -> update();

    keydemo_right -> draw(sentences_x[step] + sentences[step] -> get_width()/2 + keydemo_left -> get_width(),
			 sentences_y[step] + sentences[step] -> get_height());
    keydemo_right -> update();
    break;
  case 12:
    keydemo_escape -> draw(sentences_x[step] + sentences[step] -> get_width()/2 - keydemo_left -> get_width()/2,
			 sentences_y[step] + sentences[step] -> get_height());
    keydemo_escape -> update();
    break;
  case 13:
    keydemo_options -> draw(sentences_x[step] + sentences[step] -> get_width()/2 - keydemo_left -> get_width()/2,
			 sentences_y[step] + sentences[step] -> get_height());
    keydemo_options -> update();
    break;
    break;
    
  }
}

void TitleState::update()
{
  start_message -> update();

  if(next_time < CL_System::get_time())
  {
    step = (step + 1) % NUMBER_OF_SENTENCES;
    next_time = CL_System::get_time() + sentences_time[step];
    sentences[step] -> update();
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
  if(common_resources -> key.enter -> get())
  {
    common_resources -> engine -> set_state_ingame();
    common_resources -> player1.new_game();
  }

  if(common_resources-> key.escape -> get() || common_resources -> key.pause -> get())
  {
    common_resources -> engine -> set_state_pause_menu();
  }

  if(common_resources -> key.skins -> get())
  {
    common_resources -> engine -> set_state_skin_menu();
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

void TitleState::start()
{
  step = 0;
  next_time = CL_System::get_time() + 5000;
  common_resources -> current_player = &demo_player;
  demo_player.new_game();
}
