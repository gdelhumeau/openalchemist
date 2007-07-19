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
 * Game constructor
 */
Game::Game(CL_DisplayWindow *window, bool opengl)
{
  this->window = window;
  this->opengl = opengl;

#ifdef WIN32
  std::string file_path = CL_System::get_exe_path() + "\\data\\";
#else
  std::string file_path = CL_System::get_exe_path() + "/data/";
#endif

  CL_Surface loading(file_path+"loading.png");
  CL_Display::clear(CL_Color(0, 0, 0));
  loading.draw(400-loading.get_width()/2,300-loading.get_height()/2);
  CL_Display::flip();
  
  
 
  //gc = window->get_gc(); 
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

   
  time_interval = 0;

  // We initalize the randomized-numbers generator
  srand(CL_System::get_time());

  read_scores();
  skins_selector.read_file();

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

  skins_selector.write_file();

  
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
  

  

  apply_skin();
  
  

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
  options.is_optionsd = false;
  playable = true;

}


/**
 * Load the selected skin
 */
void Game::load_gfx()
{

  this->unload_gfx();  

  CL_Zip_Archive zip(skin);

  // Load the skin ressources
  CL_ResourceManager gfx("gfx.xml",&zip, false);
  CL_ResourceManager gfx_pieces("pieces.xml", &zip, false);
  CL_ResourceManager gfx_pause("menu_pause.xml", &zip, false);
  CL_ResourceManager gfx_options("menu_options.xml", &zip, false);
  

  gfx_misc.load_gfx(&gfx);
  pieces.load_gfx(&gfx_pieces, colorblind);
  pause.load_gfx(&gfx_pause);
  options.load_gfx(&gfx_options);
  progress_bar.load_gfx(&gfx);
  skins_selector.load_gfx(&gfx);
  front_layer.load_gfx(&zip);
 
  // c² = a²+b³
  current_pieces_r = pieces.width/2;

  apply_skin();
  calc_score();
 

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
  
  gfx_misc.unload_gfx();
  pieces.unload_gfx();
  pause.unload_gfx();
  options.unload_gfx();
  progress_bar.unload_gfx();
  skins_selector.unload_gfx();

  if(front_layer.enabled)
    front_layer.unload_gfx();
  
   
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

  str_score = format_number(to_string(global_score));
  str_bonus = format_number(to_string(global_bonus));
  str_hightscore = format_number(to_string(hightscores[current_difficulty])); 

  int score_width = gfx_misc.font_a->get_width(str_score, CL_Size(0, 0));
  int bonus_width = gfx_misc.font_a->get_width(str_bonus, CL_Size(0, 0));
  int hightscore_width = gfx_misc.font_a->get_width(str_hightscore, CL_Size(0, 0));

  score_left = gfx_misc.score_right - score_width;
  bonus_left = gfx_misc.bonus_right - bonus_width;
  hightscore_left = gfx_misc.hightscore_right - hightscore_width;
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


  Preferences *pref = pref_get_instance();
  CL_FramerateCounter fps_getter; 
  fps_getter.set_fps_limit(pref -> maxfps);


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