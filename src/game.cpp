/* OpenAlchemist - just a simple game 
 * ----------------------------------
 *
 * Copyright (C) 2005, 2006 Guillaume Delhumeau <guillaume.delhumeau at laposte.net>
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

#include "headers.h"
#include "math.h"

const int Piece::score[12] = { 1, 3, 9, 30, 90, 300, 900, 3000, 9000, 30000, 90000, 300000 };

/**
 * This function return a factor to calcul moving with time
 */
inline float get_time_interval(int fps)
{
  
  if(!fps)return 0;
  return 1000.0/((float)fps);
  
}

/**
 * Game constructor
 */
Game::Game(CL_DisplayWindow *window, bool opengl)
{
  this->window = window;
  this->opengl = opengl;
 
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

  pause.requested = false;

  
  // We create all the usefull KeyboardKeys
  key_fullscreen   = new KeyboardKey(CL_KEY_F11   , false);
  key_retry        = new KeyboardKey(CL_KEY_F2    , false);
  key_change_angle = new KeyboardKey(CL_KEY_UP    , true );
  key_left         = new KeyboardKey(CL_KEY_LEFT  , true );
  key_right        = new KeyboardKey(CL_KEY_RIGHT , true );
  key_falling      = new KeyboardKey(CL_KEY_DOWN  , false);
  key_undo         = new KeyboardKey(CL_KEY_F5    , false);
  key_echap        = new KeyboardKey(CL_KEY_ESCAPE, false);
  key_up           = new KeyboardKey(CL_KEY_UP    , true );
  key_down         = new KeyboardKey(CL_KEY_DOWN  , true );
  key_enter        = new KeyboardKey(CL_KEY_ENTER , false);
  
  time_interval = 0;

  // We initalize the randomized-numbers generator
  srand(CL_System::get_time());

  read_scores();

}

/**
 * Destructor
 */
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

  
  delete next_piece1;
  delete next_piece2;
  delete current_piece1;
  delete current_piece2; 

  delete key_fullscreen;
  delete key_retry;
  delete key_change_angle;
  delete key_left;
  delete key_right; 
  delete key_falling; 
  delete key_undo;
  delete key_echap;
  delete key_up;
  delete key_down;
  delete key_enter;
  
}

/**
 * This method start a new game
 */
void Game::new_game(short difficulty)
{

  current_difficulty = difficulty;

  // We have to delete the pieces in the body
  for(int i=0; i<NUMBER_OF_COLS; ++i)
    for(int j=0; j<NUMBER_OF_LINES; ++j)
    {
      if(body[i][j]) delete body[i][j];
      body[i][j] = NULL;   
      undo.body[i][j] = 0;
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
  visible_pieces = 3;
   
  next_piece1 = new Piece(rand()%(unlocked_pieces));
  next_piece2 = new Piece(rand()%(unlocked_pieces));  
  
  current_piece1 = new Piece(rand()%(unlocked_pieces));
  current_piece2 = new Piece(rand()%(unlocked_pieces));
  

  

  int value;
  value = next_piece1 -> get_piece_number();
  next_piece1 -> set_sprites(pieces.normal[value], pieces.appearing[value],
                             pieces.disappearing[value], pieces.mini[value]);
  
  value = next_piece2 -> get_piece_number();
  next_piece2 -> set_sprites(pieces.normal[value], pieces.appearing[value],
                             pieces.disappearing[value], pieces.mini[value]);
  
  value = current_piece1 ->  get_piece_number();
  current_piece1 -> set_sprites(pieces.normal[value], pieces.appearing[value],
                                pieces.disappearing[value], pieces.mini[value]);
  
  value = current_piece2 ->  get_piece_number();
  current_piece2 -> set_sprites(pieces.normal[value], pieces.appearing[value],
                                pieces.disappearing[value], pieces.mini[value]);
  
  // The next_pieces depends on the skin, so:
  next_piece1 -> set_position(next_left, next_top);
  next_piece2 -> set_position(next_left+(pieces.width)/2,next_top);

  // We set some variables
  current_pieces_angle = 0; 
  current_pieces_next_angle = 0;
  current_pieces_placed = true;

  position = NUMBER_OF_COLS/2-1;
  old_position = 0;
  position_bis = 1;
  old_position_bis = 0;
  position_x = position*pieces.width+pieces.width/2;

  undo.possible = false;
  undo.next_next_piece1 = -1;
  undo.next_next_piece2 = -1;
  
  falling_requested = false;

  game_mode = GAME_MODE_PLAYING;
  global_score = 0;
  global_bonus = 0;
  combo = 0;

  pause.is_paused = false;

}


/**
 * Load the selected skin
 */
void Game::load_gfx()
{

  this->unload_gfx();  

  // Load the skin ressources
  CL_ResourceManager gfx("gfx.xml", new CL_Zip_Archive(skin), true);
  CL_ResourceManager gfx_pieces("pieces.xml", new CL_Zip_Archive(skin), true);
  CL_ResourceManager gfx_pause("menu_pause.xml", new CL_Zip_Archive(skin), true);
  
  pieces.load_gfx(&gfx_pieces);
  pause.load_gfx(&gfx_pause);
  progress_bar.load_gfx(&gfx);
  skins_selector.load_gfx(&gfx);

  background = new CL_Surface("background", &gfx);
  game_over = new CL_Surface("gameover", &gfx);  
  new_hightscore = new CL_Sprite("menu/new-hightscore/dialog", &gfx);
  
  // We have to change the sprite references in the Pieces...
  for(int i=0; i<NUMBER_OF_COLS; ++i)
    for(int j=0; j<NUMBER_OF_LINES; ++j)
    {
      if(body[i][j])
      {
        int value = body[i][j] -> get_piece_number();
        body[i][j] -> set_sprites(pieces.normal[value], pieces.appearing[value],
                                  pieces.disappearing[value], pieces.mini[value]);
      }
    }

   
  
  // Here too
  int value;
  value = next_piece1 -> get_piece_number();
  next_piece1 -> set_sprites(pieces.normal[value], pieces.appearing[value],
                             pieces.disappearing[value], pieces.mini[value]);
  
  value = next_piece2 -> get_piece_number();
  next_piece2 -> set_sprites(pieces.normal[value], pieces.appearing[value],
                             pieces.disappearing[value], pieces.mini[value]);
  
  value = current_piece1 -> get_piece_number();
  current_piece1 -> set_sprites(pieces.normal[value], pieces.appearing[value],
                                pieces.disappearing[value], pieces.mini[value]);
  
  value = current_piece2 -> get_piece_number();
  current_piece2 -> set_sprites(pieces.normal[value], pieces.appearing[value],
                                pieces.disappearing[value], pieces.mini[value]);

  // Load the font, to display score and framerate
  font_a = new CL_Font("font", &gfx);  

  // Load some var
  game_top = CL_Integer_to_int("game/top", &gfx);
  game_left = CL_Integer_to_int("game/left", &gfx); 

  zone_top = CL_Integer_to_int("zone_top", &gfx);    
  next_left = CL_Integer_to_int("game/next_left", &gfx);
  next_top = CL_Integer_to_int("game/next_top", &gfx);
  score_top = CL_Integer_to_int("score_top", &gfx);
  score_right = CL_Integer_to_int("score_right", &gfx);
  bonus_right = CL_Integer_to_int("bonus_score_right", &gfx);
  bonus_top = CL_Integer_to_int("bonus_score_top", &gfx);
  hightscore_right = CL_Integer_to_int("hight_score_right", &gfx);
  hightscore_top = CL_Integer_to_int("hight_score_top", &gfx);
  new_score_top = CL_Integer_to_int("menu/new-hightscore/new-score-top", &gfx);
  old_score_top = CL_Integer_to_int("menu/new-hightscore/old-score-top", &gfx);
  

  // The next_pieces depends on the skin, so:
  next_piece1 -> set_position(next_left, next_top);
  next_piece2 -> set_position(next_left+(pieces.width)/2,next_top);
 
  // c² = a²+b³
  current_pieces_r = pieces.width/2;
     
  // So now we can say that the GFX are loaded
  is_gfx_loaded = true;
  
}

/**
 * Unload the skin
 */
void Game::unload_gfx()
{
  if(!is_gfx_loaded)
  {
    // nothing to do
    return;
  }
  
  pieces.unload_gfx();
  pause.unload_gfx();
  progress_bar.unload_gfx();
  skins_selector.unload_gfx();
  
  delete background;
  delete font_a;
  delete new_hightscore;
   
  is_gfx_loaded = false;

}

/**
 * Switch to fullscreen/windowed
 */
void Game::toggle_screen()
{
  Preferences *pref = pref_get_instance();
  pref -> fullscreen = !pref -> fullscreen;
  if(pref -> fullscreen)
  {
    window->set_fullscreen(800,600,0,0);
    CL_Mouse::hide();
  }
  else
  {
    window->set_windowed();
    CL_Mouse::show();
  }
  
  pref -> write();
        
}  

/**
 * Calc the score (except bonus)
 */
void Game::calc_score()
{
  global_score = 0;
  for(int i=0; i<NUMBER_OF_COLS; ++i)
    for(int j=2; j<NUMBER_OF_LINES; ++j)
    {
      if(body[i][j])
      {
        global_score += body[i][j]->get_score_value();                           
      }
    }
}

/**
 * Stop the game from an other thread
 */
void Game::stop()
{
  end = true;
}

/**
 * Main loop
 */
void Game::main_loop()
{

  end = false;
  
  load_preferences();

  new_game(0);
  load_gfx();
  //load_preferences();

  CL_FramerateCounter fps_getter; 

  position_x = position*pieces.width + pieces.width/2;
   

  // Run until someone presses escape
  while (!end)
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
    CL_System::keep_alive();
  }

  unload_gfx();

  save_preferences();
}
