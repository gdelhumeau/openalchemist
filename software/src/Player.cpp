/********************************************************************
                          OpenAlchemist

  File : Player.cpp
  Description : Player implementation
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <math.h>

#include <ClanLib/core.h>

#include "Player.h"
#include "Piece.h"
#include "Preferences.h"
#include "CommonResources.h"
#include "misc.h"
#include "Board.h"
#include "GameEngine.h"

#define TO_RAD PI/180
#define PIECE_MOVING_SPEED 0.25

Player::Player()
{
  // Setting objects to NULL
  next_piece1    = NULL;
  next_piece2    = NULL;
  current_piece1 = NULL;
  current_piece2 = NULL;

  // Initializing random numbers generator
  srand(CL_System::get_time());

  // Making key objects
  key_change_angle = new KeyboardKey(CL_KEY_UP    , true );
  key_left         = new KeyboardKey(CL_KEY_LEFT  , true );
  key_right        = new KeyboardKey(CL_KEY_RIGHT , true );
  key_falling      = new KeyboardKey(CL_KEY_DOWN  , false);
}

Player::~Player()
{
  unload_gfx();
  // Deleting key objects
  delete key_change_angle;
  delete key_left;
  delete key_right;
  delete key_falling;
}

void Player::new_game()
{
  // Getting resources
  CommonResources *resources = common_resources_get_instance();

  // Creating new pieces for playable pieces and next pieces
  current_piece1 = new Piece(rand()%3);
  current_piece2 = new Piece(rand()%3);
  next_piece1 = new Piece(rand()%3);
  next_piece2 = new Piece(rand()%3);

  // Setting playable pieces position
  angle = 0.0;
  target_angle = 0;
  position = 2;
  position_bis = 1;
  placed = true;
  undo_possible = false;
  next_next_piece1 = 0;
  next_next_piece2 = 0;
  x = position * resources->pieces_width + (position_bis )*resources->pieces_width/2;
  next_piece1 -> set_position(next_left, next_top);
  next_piece2 -> set_position(next_left+((resources->pieces_width)/2),next_top);

  falling_requested = false;
  game_mode = GAME_MODE_PLAYING;

  board.clear();
  board.unlocked_pieces = 3;
  board.visible_pieces  = 3;
  board.score = 0;
  board.bonus_score = 0;
  board.calc_score();
  
  // Applying skin
  int value;
  value = next_piece1 -> get_piece_number();
  
  next_piece1 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                             pieces_disappearing[value], pieces_mini[value]);
  
  value = next_piece2 -> get_piece_number();
  next_piece2 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                             pieces_disappearing[value], pieces_mini[value]);
  
  value = current_piece1 ->  get_piece_number();
  current_piece1 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                                pieces_disappearing[value], pieces_mini[value]);
  
  value = current_piece2 ->  get_piece_number();
  current_piece2 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                                pieces_disappearing[value], pieces_mini[value]);

}

void Player::load_gfx(std::string skin)
{
  // Getting resources
  CommonResources *resources = common_resources_get_instance();

  // Getting skins resources
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx_pieces("pieces.xml", &zip, false);
  CL_ResourceManager gfx("gfx.xml", &zip, false);

  // Getting preferences (to know if colorbling is activated)
  Preferences *pref = pref_get_instance();
  
  // First we load the sprites
  for(int i = 1; i<=NUMBER_OF_PIECES; ++i)
  {
    if(pref -> colorblind)
      pieces_normal[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/normal-color-blind", &gfx_pieces);
    else
      pieces_normal[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/normal", &gfx_pieces);

    pieces_appearing[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/appear", &gfx_pieces);
    pieces_disappearing[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/disappear", &gfx_pieces);
    
    if(pref -> colorblind)
      pieces_mini[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/little-color-blind", &gfx_pieces);
    else
      pieces_mini[i-1] = new CL_Sprite("pieces/piece_"+to_string(i)+"/little", &gfx_pieces); 

    pieces_progress_x[i-1] = CL_Integer_to_int("pieces/piece_"+to_string(i)+"/progress-x", &gfx_pieces);
    pieces_progress_y[i-1] = CL_Integer_to_int("pieces/piece_"+to_string(i)+"/progress-y", &gfx_pieces);

    if(i>3)
      pieces_hidden[i-4] = new CL_Sprite("pieces/piece_"+to_string(i)+"/hidder", &gfx_pieces);
  }

  // Getting sprites position
  next_left = CL_Integer_to_int("game/next_left", &gfx);
  next_top = CL_Integer_to_int("game/next_top", &gfx);

  // Getting game zone position
  board.game_top = CL_Integer_to_int("game/top", &gfx);
  board.game_left = CL_Integer_to_int("game/left", &gfx); 
  board.zone_top = CL_Integer_to_int("zone_top", &gfx);

  board.score_top = CL_Integer_to_int("score_top", &gfx);
  board.score_right = CL_Integer_to_int("score_right", &gfx);
  board.bonus_top = CL_Integer_to_int("bonus_score_top", &gfx);
  board.bonus_right = CL_Integer_to_int("bonus_score_right", &gfx);
  board.hightscore_top = CL_Integer_to_int("hight_score_top", &gfx);
  board.hightscore_right = CL_Integer_to_int("hight_score_right", &gfx);

  // Calculating c² = a²+b³
  current_pieces_r = resources->pieces_width/2;

  // Then, we apply new sprites
  if(next_piece1 && next_piece2 && current_piece1 && current_piece2)
  {
    int value;
    value = next_piece1 -> get_piece_number();
  
    next_piece1 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                               pieces_disappearing[value], pieces_mini[value]);
  
    value = next_piece2 -> get_piece_number();
    next_piece2 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                               pieces_disappearing[value], pieces_mini[value]);
  
    value = current_piece1 ->  get_piece_number();
    current_piece1 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                                  pieces_disappearing[value], pieces_mini[value]);
  
    value = current_piece2 ->  get_piece_number();
    current_piece2 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                                  pieces_disappearing[value], pieces_mini[value]);

    next_piece1 -> set_position(next_left, next_top);
    next_piece2 -> set_position(next_left+((resources->pieces_width)/2),next_top);
  }

  // And to the board too
  board.apply_skin(pieces_normal, pieces_appearing, pieces_disappearing, pieces_mini);

  // Loading gfx for progress bar
  progress_bar.load_gfx(skin);

}

void Player::unload_gfx()
{
  // Delete the pieces sprites
  for(int i = 0; i<NUMBER_OF_PIECES; ++i)
  {
    if(pieces_normal[i])
    {
      delete pieces_normal[i];
      pieces_normal[i] = NULL;
    }
    if(pieces_appearing[i])
    {
      delete pieces_appearing[i];
      pieces_appearing[i] = NULL;
    }
    if(pieces_disappearing[i])
    {
      delete pieces_disappearing[i];
      pieces_disappearing[i] = NULL;
    }
    if(pieces_mini[i])
    {
      delete pieces_mini[i];
      pieces_mini[i] = NULL;
    }
  }

  progress_bar.unload_gfx();
}

void Player::draw()
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();

  // Drawing unlocked pieces
  for(int i=0; i<NUMBER_OF_PIECES; ++i)
  {
    if(i >= board.visible_pieces)
      pieces_hidden[i-3] -> draw(pieces_progress_x[i], pieces_progress_y[i], 0);
    else
      pieces_mini[i] -> draw(pieces_progress_x[i], pieces_progress_y[i], 0);
  }

  // Drawing board
  board.draw();

  // Drawing the progress bar 
  // TODO : must work with differents difficulties
  if(resources -> hightscores[0] > 0)
  {
    int percentage = (int)((double)(board.score + board.bonus_score) / (double)resources -> hightscores[0] * 100.0);
    progress_bar.draw(percentage);
  }
  else
  {
    progress_bar.draw(100);
  }

  // Drawing next pieces
  next_piece1 -> draw_mini();
  next_piece2 -> draw_mini();


  if(GAME_MODE_PLAYING == game_mode)
  {
    // Setting playable pieces position 
    current_piece1 -> set_position(board.game_left+x+cos(angle*TO_RAD)*current_pieces_r,
                                   board.zone_top+resources->pieces_height/2+sin((angle)*TO_RAD)*current_pieces_r);

    current_piece2 -> set_position(board.game_left+x+cos((angle+180)*TO_RAD)*current_pieces_r,
                                   board.zone_top+resources->pieces_height/2+sin((angle+180)*TO_RAD)*current_pieces_r);

    // Displaying playable pieces
    current_piece1 -> draw();
    current_piece2 -> draw();
  }
}

void Player::events()
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();

  if(GAME_MODE_PLAYING == game_mode)
  {
    // Change the order of the pieces 
    if(key_change_angle->get())
    {
      change_angle();
    }

    // Look the key to know if we have to move the pieces to the left
    if(key_left->get())
    {
      move_left();
    }

    // Look the key to know if we have to move the pieces to the right
    if(key_right->get())
    {
      move_right();
    }

    // It's time for the pieces to fall
    if(key_falling -> get())
    {
      falling_requested = true; 
    } 
    
    // Cheatting
    if(CL_Keyboard::get_keycode(CL_KEY_A) && CL_Keyboard::get_keycode(CL_KEY_L))
    {
      board.unlocked_pieces = NUMBER_OF_PIECES;
      board.visible_pieces = NUMBER_OF_PIECES;
    }
  }

  // Undo the last move
  if(resources->key.undo -> get())
  {
    undo();
  }

  // Retry current game
  if(resources -> key.retry -> get())
  {
    resources -> engine -> set_state_quit_menu(QUITMENU_RETRY);
  }

}

void Player::change_angle()
{
  // Change the order of the pieces 
  if(target_angle<=target_angle+90)
  {     
    target_angle += 90;
    placed = false;

    if((target_angle%180 == 90))
    {
      position_bis = 0;
    }
    else
    {
      if(position == NUMBER_OF_COLS -1)
        position --;
        
      position_bis = 1;
    }

  }
}

void Player::move_left()
{
  if(position > 0)
  {
    old_position = position;
    old_position_bis = position_bis;
    position--;
    placed = false;
  }
}

void Player::move_right()
{
  if(position < NUMBER_OF_COLS - 1)
  {
    if(!(position == NUMBER_OF_COLS - 2 && position_bis))
    {
      old_position = position;
      old_position_bis = position_bis;
      position++;
      placed = false;
    }
  }
}

void Player::update()
{
  if(GAME_MODE_PLAYING == game_mode)
  {
    update_playing();
  }
  else if(GAME_MODE_FALLING_AND_CREATING == game_mode)
  {
    update_falling_and_creating();
  }
  else if(GAME_MODE_DESTROYING == game_mode)
  {
    update_destroying();
  }
}

void Player::update_playing()
{
  static CommonResources *resources = common_resources_get_instance();

  // Move the pieces if the order has been changed      
  if(angle<target_angle)
  {
    angle += resources->time_interval * 0.35;
    if(angle>=target_angle)
    {
      while(target_angle>=360)
      {
        target_angle-=360;             
      }
      angle = target_angle;
    }
  }
  
  // Move the pieces to the right
  if(!placed)
  {
    if(position * resources->pieces_width + position_bis *resources->pieces_width/2 >= x)
    {
      x += resources->time_interval * PIECE_MOVING_SPEED;
      if(x > position * resources->pieces_width + (position_bis )*resources->pieces_width/2)
      {
        x = position * resources->pieces_width + (position_bis )*resources->pieces_width/2;
        placed = true;
      }
    }
  }

  // Move the pieces to the left
  if(!placed)
  {  
    if(position * resources->pieces_width + (position_bis )*resources->pieces_width/2 <= x)
    {
      x -= resources->time_interval * PIECE_MOVING_SPEED;
      if(x < position * resources->pieces_width + (position_bis)*resources->pieces_width/2)
      {
        x = position * resources->pieces_width + (position_bis)*resources->pieces_width/2;
        placed = true;
      }
    }
  }

  // Falling the playable pieces
  if(falling_requested && placed && (angle >= target_angle))
  {
    fall();
  }
}

void Player::fall()
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();

  falling_requested = false;
  combo = 0;

  undo_possible = true;  
  undo_position = position;
  undo_position_bis = position_bis;
  undo_piece1_number = current_piece1 -> get_piece_number();
  undo_piece2_number = current_piece2 -> get_piece_number();
  undo_angle = target_angle;

  
  current_piece1 -> set_position(board.game_left+x+cos(angle*TO_RAD)*current_pieces_r,
                                 board.zone_top+resources->pieces_height/2+sin((angle)*TO_RAD)*current_pieces_r);

  current_piece2 -> set_position(board.game_left+x+cos((angle+180)*TO_RAD)*current_pieces_r,
                                 board.zone_top+resources->pieces_height/2+sin((angle+180)*TO_RAD)*current_pieces_r);

  board.add_pieces(current_piece1, current_piece2);
      
      

  // We must respect the next piece order (ex: red to the left, blue to the right...)
  float piece1x = cos(angle*TO_RAD)*current_pieces_r;
  float piece2x = cos((angle+180)*TO_RAD)*current_pieces_r;

  if(piece1x < piece2x)
  {        
    current_piece1 = new Piece(next_piece1->get_piece_number());
    current_piece2 = new Piece(next_piece2->get_piece_number());
  }
  else
  {
    current_piece1 = new Piece(next_piece2->get_piece_number());
    current_piece2 = new Piece(next_piece1->get_piece_number());     
  }      
            
    
  int value = current_piece1 -> get_piece_number();
  current_piece1 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                                pieces_disappearing[value], pieces_mini[value]);
      
  value = current_piece2 -> get_piece_number();
  current_piece2 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                                pieces_disappearing[value], pieces_mini[value]);
            
            
  game_mode = GAME_MODE_FALLING_AND_CREATING;      
}

void Player::update_falling_and_creating()
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();

  bool placed = board.fall_and_create();

  if(placed)
  {
    
    combo ++;
    
    // Only the second time
    if(combo == 2 && board.is_game_over())
    {
      resources -> engine -> set_state_gameover();
      return;
    }
     
    bool to_destroy = board.detect_pieces_to_destroy();

    if(to_destroy)
    {
      game_mode = GAME_MODE_DESTROYING;
      //game_mode = GAME_MODE_TO_PLAYING;
    }
    else
    {
      if(board.is_game_over())
      {
        resources -> engine -> set_skin_element(board.visible_pieces);
        if(board.score + board.bonus_score > resources -> hightscores[0])
        {
          resources -> engine -> set_state_hightscore();
	  resources -> old_hightscore = resources -> hightscores[0];
          resources -> hightscores[0] = board.score + board.bonus_score;
          resources -> save_scores();
        }
        else
          resources -> engine -> set_state_gameover();
        return;
      }
      prepare_to_play();
      game_mode = GAME_MODE_PLAYING;
    }

  }
}

void Player::update_destroying()
{
  bool destroyed = board.destroy();

  if(destroyed)
  {
    board.create_new_pieces(pieces_normal, pieces_appearing, pieces_disappearing, pieces_mini);

    board.detect_pieces_to_fall();
    game_mode = GAME_MODE_FALLING_AND_CREATING;
  }
  
}

void Player::prepare_to_play()
{
  if(next_next_piece1 >= 0)
  {
    next_piece1 -> set_piece_number(next_next_piece1);
    next_piece2 -> set_piece_number(next_next_piece2);
    next_next_piece1 = -1;
  }
  else
  {    
    next_piece1 -> set_piece_number(rand()%(board.unlocked_pieces));
    next_piece2 -> set_piece_number(rand()%(board.unlocked_pieces));
  }
          
  int value;
  value = next_piece1 -> get_piece_number();
  next_piece1 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                             pieces_disappearing[value], pieces_mini[value]);
      
  value = next_piece2 -> get_piece_number();
  next_piece2 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                             pieces_disappearing[value], pieces_mini[value]);
          
  board.calc_score();
}

void Player::undo()
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();
  
  // First verify than the last move is not the first one
  if(undo_possible)
  {
    undo_possible = false;

    board.undo(pieces_normal, pieces_appearing, pieces_disappearing, pieces_mini);

    next_next_piece1 = next_piece1 -> get_piece_number();
    next_next_piece2 = next_piece2 -> get_piece_number();
  
    
    int value = current_piece1 -> get_piece_number();
    next_piece1 -> set_piece_number(value);
    next_piece1 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                               pieces_disappearing[value], pieces_mini[value]);

    value = current_piece2 -> get_piece_number();
    next_piece2 -> set_piece_number(value);
    next_piece2 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                               pieces_disappearing[value], pieces_mini[value]);

    value = undo_piece1_number;
    current_piece1 -> set_piece_number(value);
    current_piece1 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                                  pieces_disappearing[value], pieces_mini[value]);

    value = undo_piece2_number;
    current_piece2 -> set_piece_number(value);
    current_piece2 -> set_sprites(pieces_normal[value], pieces_appearing[value],
                                  pieces_disappearing[value], pieces_mini[value]);
    
        
    position = undo_position;
    position_bis = undo_position_bis;
    x = position * resources->pieces_width + position_bis * resources->pieces_width / 2;

    angle = undo_angle;
    target_angle = (int)undo_angle;

    game_mode = GAME_MODE_PLAYING;

  }
}

bool Player::is_undo_available()
{
  return undo_possible;
}

int Player::get_visible_pieces()
{
  return board.visible_pieces;
}

u_int Player::get_score()
{
  return board.score + board.bonus_score;
}

bool Player::is_game_over()
{
  return board.is_game_over();
}

void Player::give_up()
{
 // Getting resources
  static CommonResources *resources = common_resources_get_instance();
  resources -> engine -> set_skin_element(board.visible_pieces);
  board.clear();
  board.unlocked_pieces = 3;
  board.visible_pieces  = 3;
  board.score = 0;
  board.bonus_score = 0;

}
