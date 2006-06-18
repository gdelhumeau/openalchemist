/* OpenAlchemist - just a simple game 
 * ----------------------------------
 *
 * Copyright (C) 2005 Guillaume Delhumeau <guillaume.delhumeau at laposte.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <math.h>
#include <stdlib.h>
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "piece.h"
#include "game.h"
#include "misc.h"



inline float get_time_interval(int fps)
{
  
  if(!fps)return 0;
  return 1000.0/((float)fps);
  
}

// Constructor
Game::Game(CL_DisplayWindow *window)
{
  this->window = window;
  gc = window->get_gc(); 
  is_gfx_loaded = false;   

  // Setting all pointers to NULL
  for(int i=0; i<NUMBER_OF_COLS; ++i)
    for(int j=0; j<NUMBER_OF_LINES; ++j)
    {
      body[i][j] = NULL; 
    } 

  next_piece1 = NULL;
  next_piece2 = NULL;
  current_piece1 = NULL;
  current_piece2 = NULL;

  // We create all the usefull KeyboardKeys
  key_fullscreen   = new KeyboardKey(CL_KEY_F11  , false);
  key_retry        = new KeyboardKey(CL_KEY_F2   , false);
  key_change_angle = new KeyboardKey(CL_KEY_UP   , true );
  key_left         = new KeyboardKey(CL_KEY_LEFT , true );
  key_right        = new KeyboardKey(CL_KEY_RIGHT, true );
  key_falling      = new KeyboardKey(CL_KEY_DOWN , false);
  
  time_interval = 0;
  
  // We initalize the randomized-numbers generator
  srand(CL_System::get_time());

}

// Destructor
Game::~Game()
{
  unload_gfx();

  // Delete the pieces in the body
  for(int i=0; i<NUMBER_OF_COLS; ++i)
    for(int j=0; j<NUMBER_OF_LINES; ++j)
    {
      if(body[i][j]) delete body[i][j];
      body[i][j] = NULL;
    } 
  
  delete( next_piece1);
  delete( next_piece2);
  delete( current_piece1);
  delete( current_piece2); 
  
}

void Game::new_game()
{

  // We have to delete the pieces in the body
  for(int i=0; i<NUMBER_OF_COLS; ++i)
    for(int j=0; j<NUMBER_OF_LINES; ++j)
    {
      if(body[i][j]) delete body[i][j];
      body[i][j] = NULL;   
    } 


  // And to delete the next_pieces...
  if(next_piece1)  
  {
    delete next_piece1;    
  }
  if(next_piece2)
    delete next_piece2; 
      
  if(current_piece1)
    delete current_piece1;
  if(current_piece2)
    delete current_piece2;
 

  // Finally, we create some with new score_values 
  
  unlocked_pieces = 3;
   
  next_piece1 = new Piece(1+rand()%(unlocked_pieces));
  next_piece2 = new Piece(1+rand()%(unlocked_pieces));  
  
  current_piece1 = new Piece(1+rand()%(unlocked_pieces));
  current_piece2 = new Piece(1+rand()%(unlocked_pieces));
  

  

  int value;
  value = next_piece1 -> get_score_value() - 1;
  next_piece1 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                             pieces_disappearing[value], pieces_mini[value]);
  
  value = next_piece2 -> get_score_value() - 1;
  next_piece2 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                             pieces_disappearing[value], pieces_mini[value]);
  
  value = current_piece1 -> get_score_value() - 1;
  current_piece1 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                                pieces_disappearing[value], pieces_mini[value]);
  
  value = current_piece2 -> get_score_value() - 1;
  current_piece2 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                                pieces_disappearing[value], pieces_mini[value]);
  
  // The next_pieces depends on the skin, so:
  next_piece1 -> set_position(next_left, next_top);
  next_piece2 -> set_position(next_left+(pieces_width)/2,next_top);

  // We set some variables
  current_pieces_center_x = game_left + pieces_width/2;
  current_pieces_center_target = (int)current_pieces_center_x;
  current_pieces_angle = 45.0+90.0; 
  current_pieces_next_angle = 45+90;
  current_pieces_placed = true;
  
  falling_requested = false;

  game_mode = GAME_MODE_PLAYING;
  global_score = 0;
  global_bonus = 0;

}

void Game::choose_skin()
{
  skin = "./skins/aqua.zip";
}

int CL_Integer_to_int(const std::string &ressource_name, CL_ResourceManager *gfx)
{    
  CL_Integer *cl_int = new CL_Integer(ressource_name, gfx);
  int to_return = (int)*cl_int;
  delete cl_int;
  return to_return;
}

void Game::load_gfx()
{

  this->unload_gfx();  

  // Load the skin ressource
  CL_ResourceManager gfx("gfx.xml", new CL_Zip_Archive(skin), true);

  background = new CL_Surface("background", &gfx);
  game_over = new CL_Surface("gameover", &gfx);

  for(int i=1; i<=NUMBER_OF_PIECES; ++i)
  {
    pieces_normal[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/normal", &gfx);
    pieces_appearing[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/appear", &gfx);
    pieces_disappearing[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/disappear", &gfx);
    pieces_mini[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/little", &gfx);
  }

  // We have to change the sprite references in the Pieces...
  for(int i=0; i<NUMBER_OF_COLS; ++i)
    for(int j=0; j<NUMBER_OF_LINES; ++j)
    {
      if(body[i][j])
      {
        int value = body[i][j] -> get_score_value() - 1;
        body[i][j] -> set_sprites(pieces_normal[value], pieces_appearing[value],
                                  pieces_disappearing[value], pieces_mini[value]);
      }
    }
  
  // Here too
  int value;
  value = next_piece1 -> get_score_value() - 1;
  next_piece1 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                             pieces_disappearing[value], pieces_mini[value]);
  
  value = next_piece2 -> get_score_value() - 1;
  next_piece2 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                             pieces_disappearing[value], pieces_mini[value]);
  
  value = current_piece1 -> get_score_value() - 1;
  current_piece1 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                                pieces_disappearing[value], pieces_mini[value]);
  
  value = current_piece2 -> get_score_value() - 1;
  current_piece2 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                                pieces_disappearing[value], pieces_mini[value]);

  // Load the font, to display score and framerate
  font_a = new CL_Font("font", &gfx);  

  // Load some var
  game_top = CL_Integer_to_int("game/top", &gfx);
  game_left = CL_Integer_to_int("game/left", &gfx);
  pieces_width = CL_Integer_to_int("pieces/width", &gfx);
  pieces_height = CL_Integer_to_int("pieces/height", &gfx);
  zone_top = CL_Integer_to_int("zone_top", &gfx);    
  next_left = CL_Integer_to_int("game/next_left", &gfx);
  next_top = CL_Integer_to_int("game/next_top", &gfx);
  score_top = CL_Integer_to_int("score_top", &gfx);
  score_left = CL_Integer_to_int("score_left", &gfx);
  bonus_left = CL_Integer_to_int("bonus_score_left", &gfx);
  bonus_top = CL_Integer_to_int("bonus_score_top", &gfx);

  // The next_pieces depends on the skin, so:
  next_piece1 -> set_position(next_left, next_top);
  next_piece2 -> set_position(next_left+(pieces_width)/2,next_top);
  
  current_piece1 -> set_position(100.0,100.0);
  current_piece2 -> set_position(152.0,100.0);
  
  current_pieces_center_x = game_left + pieces_width/2;
  current_pieces_center_target = (int)current_pieces_center_x;
  current_pieces_center_y = zone_top + pieces_height/2;

  // c² = a²+b³
  current_pieces_r = sqrt((float)pieces_width*pieces_width+pieces_height*pieces_height)/2;
     
  // So now we can say that the GFX are loaded
  is_gfx_loaded = true;
  
}

void Game::unload_gfx()
{
  if(!is_gfx_loaded)
  {
    // nothing to do
    return;
  }

  // Delete the pieces sprites
  for(int i = 0; i<NUMBER_OF_PIECES; ++i)
  {
    delete pieces_normal[i];
    delete pieces_appearing[i];
    delete pieces_disappearing[i];
  }


  delete background;
  delete font_a;

 
  is_gfx_loaded = false;

}

void Game::toggle_screen()
{
  static bool fullscreen = false;
  fullscreen = !fullscreen;
  if(fullscreen)
  {
    window->set_fullscreen(800,600,0,0);
    CL_Mouse::hide();
  }
  else
  {
    window->set_windowed();
    CL_Mouse::show();
  }
        
}  

void Game::calc_score()
{
  global_score = 0;
  for(int i=0; i<NUMBER_OF_COLS; ++i)
    for(int j=0; j<NUMBER_OF_LINES; ++j)
    {
      if(body[i][j])
      {
        if(body[i][j]->get_score_value() > 1)
          global_score += (body[i][j]->get_score_value()-1)*3;
        else
          global_score += 1;
      }
    }
}


void Game::main_loop()
{


  choose_skin();
  new_game();
  load_gfx();

  CL_FramerateCounter fps_getter;


  // Run until someone presses escape
  while (!CL_Keyboard::get_keycode(CL_KEY_Q))
  {
    
      
    draw_game();

    key_events(); 
 
    

    // Get the Framerate
    fps = fps_getter.get_fps();
    time_interval = get_time_interval(fps);


    CL_Display::flip();

    // This call updates input and performs other "housekeeping"
    // Call this each frame
    // Also, gives the CPU a rest for 10 milliseconds to catch up
    CL_System::keep_alive(1);
  }

  unload_gfx();
}
