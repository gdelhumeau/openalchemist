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

#include "headers.h"
#include "math.h"


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
      body_undo[i][j] = 0;
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
  current_pieces_angle = 0; 
  current_pieces_next_angle = 0;
  current_pieces_placed = true;

  position = NUMBER_OF_COLS/2-1;
  old_position = 0;
  position_bis = 1;
  old_position_bis = 0;
  position_x = position*pieces_width+pieces_width/2;

  undo = false;
  undo_next_next_piece1 = 0;
  undo_next_next_piece2 = 0;
  
  falling_requested = false;

  game_mode = GAME_MODE_PLAYING;
  global_score = 0;
  global_bonus = 0;
  combo = 0;

  pause = false;

}

/**
 * This method runs the skin-selector
 */
void Game::choose_skin()
{
  skin = CL_System::get_exe_path() + "/skins/aqua.zip";
}

/**
 * Convert a CL_Integer to a int
 */
int CL_Integer_to_int(const std::string &ressource_name, CL_ResourceManager *gfx)
{    
  CL_Integer *cl_int = new CL_Integer(ressource_name, gfx);
  int to_return = (int)*cl_int;
  delete cl_int;
  return to_return;
}

/**
 * Convert a CL_Boolean to a boolean
 */
int CL_Boolean_to_bool(const std::string &ressource_name, CL_ResourceManager *gfx)
{    
  CL_Boolean *cl_bool = new CL_Boolean(ressource_name, gfx);
  bool to_return = (bool)*cl_bool;
  delete cl_bool;
  return to_return;
}

/**
 * Load the selected skin
 */
void Game::load_gfx()
{

  this->unload_gfx();  

  // Load the skin ressource
  CL_ResourceManager gfx("gfx.xml", new CL_Zip_Archive(skin), true);

  background = new CL_Surface("background", &gfx);
  game_over = new CL_Surface("gameover", &gfx);
  
  new_hightscore = new CL_Sprite("menu/new-hightscore/dialog", &gfx);
  pause_background = new CL_Sprite("menu/pause/background", &gfx);

  pause_resume = new CL_Sprite("menu/pause/resume/unselected", &gfx);
  pause_resume_selected = new CL_Sprite("menu/pause/resume/selected", &gfx);

  pause_undo = new CL_Sprite("menu/pause/undo/unselected", &gfx);
  pause_undo_selected = new CL_Sprite("menu/pause/undo/selected", &gfx);
  pause_undo_unavailable = new CL_Sprite("menu/pause/undo/unavailable", &gfx);

  pause_retry = new CL_Sprite("menu/pause/retry/unselected", &gfx);
  pause_retry_selected = new CL_Sprite("menu/pause/retry/selected", &gfx);

  pause_changeskin = new CL_Sprite("menu/pause/changeskin/unselected", &gfx);
  pause_changeskin_selected = new CL_Sprite("menu/pause/changeskin/selected", &gfx);

  pause_fullscreen = new CL_Sprite("menu/pause/fullscreen/unselected", &gfx);
  pause_fullscreen_selected = new CL_Sprite("menu/pause/fullscreen/selected", &gfx);

  pause_sound = new CL_Sprite("menu/pause/sound/unselected", &gfx);
  pause_sound_selected = new CL_Sprite("menu/pause/sound/selected", &gfx);

  pause_music = new CL_Sprite("menu/pause/music/unselected", &gfx);
  pause_music_selected = new CL_Sprite("menu/pause/music/selected", &gfx);

  pause_backmain = new CL_Sprite("menu/pause/backmain/unselected", &gfx);
  pause_backmain_selected = new CL_Sprite("menu/pause/backmain/selected", &gfx);

  pause_quit = new CL_Sprite("menu/pause/quit/unselected", &gfx);
  pause_quit_selected = new CL_Sprite("menu/pause/quit/selected", &gfx);

  progress_bar_head = new CL_Sprite("progress-bar/head/sprite", &gfx);
  progress_bar_head_ok = new CL_Sprite("progress-bar/head/sprite-ok", &gfx);
  progress_bar_foot = new CL_Sprite("progress-bar/foot/sprite", &gfx);
  progress_bar_item = new CL_Sprite("progress-bar/item/sprite", &gfx);
  progress_bar_item_ok = new CL_Sprite("progress-bar/item/sprite-ok", &gfx);

  for(int i=1; i<=NUMBER_OF_PIECES; ++i)
  {
    pieces_normal[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/normal", &gfx);
    pieces_appearing[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/appear", &gfx);
    pieces_disappearing[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/disappear", &gfx);
    pieces_mini[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/little", &gfx);

   
    pieces_progress_x[i-1] = CL_Integer_to_int("pieces/piece_"+to_string(i)+"/progress-x", &gfx);
    pieces_progress_y[i-1] = CL_Integer_to_int("pieces/piece_"+to_string(i)+"/progress-y", &gfx);

    if(i>3)
      pieces_hidder[i-4] = new CL_Sprite("pieces/piece_"+to_string(i)+"/hidder", &gfx);
    

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

  for(int i=0; i<=10; i++)
  {
    pause_sound_level[i] = new CL_Sprite("menu/pause/sound-level/"+to_string(i), &gfx);
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
  hightscore_left = CL_Integer_to_int("hight_score_left", &gfx);
  hightscore_top = CL_Integer_to_int("hight_score_top", &gfx);
  new_score_top = CL_Integer_to_int("menu/new-hightscore/new-score-top", &gfx);
  old_score_top = CL_Integer_to_int("menu/new-hightscore/old-score-top", &gfx);

  pause_resume_left = CL_Integer_to_int("menu/pause/resume/left", &gfx);
  pause_resume_top = CL_Integer_to_int("menu/pause/resume/top", &gfx);

  pause_undo_left = CL_Integer_to_int("menu/pause/undo/left", &gfx);
  pause_undo_top = CL_Integer_to_int("menu/pause/undo/top", &gfx);

  pause_retry_left = CL_Integer_to_int("menu/pause/retry/left", &gfx);
  pause_retry_top = CL_Integer_to_int("menu/pause/retry/top", &gfx);

  pause_changeskin_left = CL_Integer_to_int("menu/pause/changeskin/left", &gfx);
  pause_changeskin_top = CL_Integer_to_int("menu/pause/changeskin/top", &gfx);

  pause_fullscreen_left = CL_Integer_to_int("menu/pause/fullscreen/left", &gfx);
  pause_fullscreen_top = CL_Integer_to_int("menu/pause/fullscreen/top", &gfx);

  pause_sound_left = CL_Integer_to_int("menu/pause/sound/left", &gfx);
  pause_sound_top = CL_Integer_to_int("menu/pause/sound/top", &gfx);

  pause_music_left = CL_Integer_to_int("menu/pause/music/left", &gfx);
  pause_music_top = CL_Integer_to_int("menu/pause/music/top", &gfx);
  
  pause_backmain_left = CL_Integer_to_int("menu/pause/backmain/left", &gfx);
  pause_backmain_top = CL_Integer_to_int("menu/pause/backmain/top", &gfx);

  pause_quit_left = CL_Integer_to_int("menu/pause/quit/left", &gfx);
  pause_quit_top = CL_Integer_to_int("menu/pause/quit/top", &gfx);

  pause_sound_level_left = CL_Integer_to_int("menu/pause/sound-level/left", &gfx);

  progress_bar_left = CL_Integer_to_int("progress-bar/left", &gfx);
  progress_bar_head_top = CL_Integer_to_int("progress-bar/head/top", &gfx);
  progress_bar_foot_top = CL_Integer_to_int("progress-bar/foot/top", &gfx);


  
  if(opengl && CL_Boolean_to_bool("menu/pause/alpha_appearing", &gfx))
  {
    pause_appearing = true;
    pause_max_alpha =(float)CL_Integer_to_int("menu/pause/alpha_max", &gfx) / 100.0;
  }
  else
    pause_appearing = false;

  // The next_pieces depends on the skin, so:
  next_piece1 -> set_position(next_left, next_top);
  next_piece2 -> set_position(next_left+(pieces_width)/2,next_top);
 
  // c² = a²+b³
  current_pieces_r = pieces_width/2;
     
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

  // Delete the pieces sprites
  for(int i = 0; i<NUMBER_OF_PIECES; ++i)
  {
    delete pieces_normal[i];
    delete pieces_appearing[i];
    delete pieces_disappearing[i];

    if(i < NUMBER_OF_PIECES - 4)
      delete pieces_hidder[i];
  }

  for(int i=0; i<=10; i++)
  {
    delete pause_sound_level[i];
  }




  delete background;
  delete font_a;

  delete new_hightscore;
  delete pause_background;

  delete pause_resume;
  delete pause_resume_selected;

  delete pause_undo;
  delete pause_undo_selected;
  delete pause_undo_unavailable;

  delete pause_retry;
  delete pause_retry_selected;

  delete pause_changeskin;
  delete pause_changeskin_selected;

  delete pause_fullscreen;
  delete pause_fullscreen_selected;

  delete pause_sound;
  delete pause_sound_selected;

  delete pause_music;
  delete pause_music_selected;

  delete pause_backmain;
  delete pause_backmain_selected;

  delete pause_quit;
  delete pause_quit_selected;

  delete progress_bar_head;
  delete progress_bar_head_ok;
  delete progress_bar_foot;
  delete progress_bar_item;
  delete progress_bar_item_ok;

 
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
    for(int j=1; j<NUMBER_OF_LINES; ++j)
    {
      if(body[i][j])
      {
        global_score += (u_int)pow(3,body[i][j]->get_score_value()-1);                           
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
  choose_skin();
  new_game(0);
  load_gfx();
  load_preferences();

  CL_FramerateCounter fps_getter; 

  position_x = position*pieces_width + pieces_width/2;
   

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
