/********************************************************************
                          OpenAlchemist

  File : Player.cpp
  Description : Player implementation
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <math.h>

#include "Player.h"
#include "Piece.h"
#include "Preferences.h"
#include "CommonResources.h"
#include "misc.h"
#include "Board.h"
#include "GameEngine.h"
#include "IniFile.h"

#define PI M_PI
#define TO_RAD PI/180
#define PIECE_MOVING_SPEED 4

Player::Player()
{
  // Setting objects to NULL
  next_piece1    = NULL;
  next_piece2    = NULL;
  current_piece1 = NULL;
  current_piece2 = NULL;

for(int i = 0; i<NUMBER_OF_PIECES; ++i)
  {    
    pieces_normal[i]       = NULL;
    pieces_appearing[i]    = NULL;
    pieces_disappearing[i] = NULL;
    pieces_mini[i]         = NULL;
  }

  // Initializing random numbers generator
  srand(SDL_GetTicks());


#ifndef LINUX_MODE
  // Making key objects
  key_change_angle = new KeyboardKey(PSP_CTRL_UP    , true );
  key_left         = new KeyboardKey(PSP_CTRL_LEFT  , true );
  key_right        = new KeyboardKey(PSP_CTRL_RIGHT , true );
  key_falling      = new KeyboardKey(PSP_CTRL_DOWN  , false);
  key_cheatting    = new KeyboardKey(PSP_CTRL_CROSS , true );
#else
   // We create all the usefull KeysboardKeys
  key_change_angle = new KeyboardKey(KEY_UP   , true );
  key_left         = new KeyboardKey(KEY_LEFT , true );
  key_right        = new KeyboardKey(KEY_RIGHT, true );
  key_falling      = new KeyboardKey(KEY_DOWN , false);
  key_cheatting    = new KeyboardKey(KEY_ENTER, true );
#endif
  combo = 0;
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
  printf("current_piece1 : %d\n", current_piece1->get_piece_number());
  current_piece2 = new Piece(rand()%3);
  printf("current_piece2 : %d\n", current_piece2->get_piece_number());
  next_piece1 = new Piece(rand()%3);
  printf("next_piece1 : %d\n", next_piece1->get_piece_number());
  next_piece2 = new Piece(rand()%3);
  printf("next_piece2 : %d\n", next_piece2->get_piece_number());

  // Setting playable pieces position
  angle = 0.0;
  target_angle = 0;
  position = 2;
  position_bis = 1;
  placed = true;
  undo_possible = false;
  next_next_piece1 = 0;
  next_next_piece2 = 0;
  x = (position * (resources->pieces_width)  )+ (position_bis )*resources->pieces_width/2;
  printf("New game created, x = %d\n",x);
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

  combo = 0;
  
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
  FILE * general_ini;
  IniFile general_resources;
  std::string general_ini_path = "skins/" + skin + "/general.ini";
  general_ini = fopen(general_ini_path.c_str(), "r");
  if (general_ini != NULL)
  {
	general_resources.read(general_ini);
	fclose(general_ini);
  }
  else
     exit(1);

  // Getting resources
  CommonResources *resources = common_resources_get_instance();

  // Getting skins resources
  //CL_Zip_Archive zip(skin);
  //CL_ResourceManager gfx_pieces("pieces.xml", &zip, false);
  //CL_ResourceManager gfx_preview_pieces("pieces_preview.xml", &zip, false);
  //CL_ResourceManager gfx("general.xml", &zip, false);
  unload_gfx();
  int piece_preview_1st_x     = general_resources.get("pieces_preview_x",0);
  int piece_preview_1st_y     = general_resources.get("pieces_preview_y",0);
  int piece_preview_space_row = general_resources.get("pieces_preview_sp_rw",0);
  int piece_preview_space_col = general_resources.get("pieces_preview_sp_col",0);
  int piece_preview_nb_col    = general_resources.get("pieces_preview_nb_col",1);

  int piece_preview_per_col   = NUMBER_OF_PIECES / piece_preview_nb_col;
  
  // Getting preferences (to know if colorbling is activated)
  Preferences *pref = pref_get_instance();

  
  // First we load the sprites
  for(int i = 1; i<=NUMBER_OF_PIECES; ++i)
  {
    std::string temp;

    if(pref -> colorblind)
    {
      temp = "piece"+to_string(i)+"/normal-cb.png";
      pieces_normal[i-1] = IMG_Load_fromSkin(skin, (char*)temp.c_str());
    }
    else
    {
      temp = "piece"+to_string(i)+"/normal.png";
      pieces_normal[i-1] = IMG_Load_fromSkin(skin, (char*)temp.c_str());
    }
    temp = "piece"+to_string(i)+"/appear.png";
    pieces_appearing[i-1] = IMG_Load_fromSkin(skin, (char*)temp.c_str());
    temp = "piece"+to_string(i)+"/disappear.png";
    pieces_disappearing[i-1] = IMG_Load_fromSkin(skin, (char*)temp.c_str());
    
    if(pref -> colorblind)
    {
      temp = "piece"+to_string(i)+"/little-cb.png";
      pieces_mini[i-1] = IMG_Load_fromSkin(skin, (char*)temp.c_str());
    }
    else
    {
      temp = "piece"+to_string(i)+"/little.png";
      pieces_mini[i-1] = IMG_Load_fromSkin(skin, (char*)temp.c_str()); 
    }

    pieces_preview_x[i-1] = piece_preview_1st_x + (piece_preview_space_col)*((int)((i-1)/piece_preview_per_col));
    printf("pieces_preview_x[i-1] = %d\n",pieces_preview_x[i-1]);
    pieces_preview_y[i-1] = piece_preview_1st_y + (piece_preview_space_row)*((i-1)%piece_preview_per_col);

    if(i>3)
    {
      temp = "piece"+to_string(i)+"/hidder.png";
      pieces_hidden[i-4] = IMG_Load_fromSkin(skin, (char*)temp.c_str());
    }
  }

  // Getting sprites position
  next_left              = general_resources.get("next_left", 0);
  next_top               = general_resources.get("next_top", 0);

  // Getting game zone postion                   
  board.game_top         = general_resources.get("game_top", 0);
  board.game_left        = general_resources.get("game_left", 0);
  board.zone_top         = general_resources.get("zone_top", 0);

  board.score_top        = general_resources.get("score_top", 0);
  board.score_right      = general_resources.get("score_right", 0);
  board.bonus_top        = general_resources.get("bonus_top", 0);
  board.bonus_right      = general_resources.get("bonus_right", 0);
  board.hightscore_top   = general_resources.get("hightscore_top", 0);
  board.hightscore_right = general_resources.get("hightscore_right", 0);

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

  // Loading gfx for combos painter
  combos_painter.load_gfx(skin);

}

void Player::unload_gfx()
{
  // Delete the pieces sprites
  for(int i = 0; i<NUMBER_OF_PIECES; ++i)
  {
    if(pieces_normal[i])
    {
      SDL_FreeSurface (pieces_normal[i]);
      pieces_normal[i] = NULL;
    }
    if(pieces_appearing[i])
    {
      SDL_FreeSurface (pieces_appearing[i]);
      pieces_appearing[i] = NULL;
    }
    if(pieces_disappearing[i])
    {
      SDL_FreeSurface (pieces_disappearing[i]);
      pieces_disappearing[i] = NULL;
    }
    if(pieces_mini[i])
    {
      SDL_FreeSurface (pieces_mini[i]);
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
      psp_sdl_blit_on_screen_at_XY(pieces_hidden[i-3], pieces_preview_x[i], pieces_preview_y[i]);
      
    else
      psp_sdl_blit_on_screen_at_XY(pieces_mini[i], pieces_preview_x[i], pieces_preview_y[i]);
  }

  // Drawing board
  board.draw();

  // Drawing the progress bar 
  // TODO : must work with differents difficulties
  if(resources -> highscore > 0)
  {
    int percentage = (int)((double)(board.score + board.bonus_score) / (double)resources -> highscore * 100.0);
    if(percentage > 100)
      percentage = 100;
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
    current_piece1 -> set_position(board.game_left+x+cos(angle*TO_RAD)*current_pieces_r,
                                   board.zone_top+resources->pieces_height/2+sin((angle)*TO_RAD)*current_pieces_r);
    current_piece2 -> set_position(board.game_left+x+cos((angle+180)*TO_RAD)*current_pieces_r,
                                   board.zone_top+resources->pieces_height/2+sin((angle+180)*TO_RAD)*current_pieces_r);

    // Displaying playable pieces
    current_piece1 -> draw();
    current_piece2 -> draw();
  }

  // Drawing combo
  if(combo > 1)
  {
    combos_painter.set_score(combo - 1);
  }
  
  combos_painter.draw();
}

void Player::events()
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();
  if(GAME_MODE_PLAYING == game_mode)
  {
   switch(resources->CurrentKeyPressed)
   {
    // Change the order of the pieces 
    case KEY_CHANGE_ANGLE:
    {
      printf("I got change angle event\n");
      change_angle();
      resources->CurrentKeyPressed = 0;
      break;
    }

    // Look the key to know if we have to move the pieces to the left
    case KEY_LEFT:
    {
      printf("I got move left\n");
      move_left();
      resources->CurrentKeyPressed = 0;
      break;
    }

    // Look the key to know if we have to move the pieces to the right
    case KEY_RIGHT:
    {
      printf("I got move right\n");
      move_right();
      resources->CurrentKeyPressed = 0;
      break;
    }

    // It's time for the pieces to fall
    case KEY_FALL:
    {
      printf("I got falling request\n");
      falling_requested = true; 
      resources -> CurrentKeyPressed = 0;
      break;
    } 
    
    // Cheatting
    case KEY_CHEAT:
    {
      printf("I got cheatting request\n");
      board.unlocked_pieces = NUMBER_OF_PIECES;
      board.visible_pieces = NUMBER_OF_PIECES;
      resources -> CurrentKeyPressed = 0;
      break;
    }
   }
  }
  switch(resources->CurrentKeyPressed)
  {

  // Undo the last move
  case KEY_UNDO:
  {
    printf("I got undo request\n");
    undo();
    resources -> CurrentKeyPressed = 0;
    break;
  }

  // Retry current game
  case KEY_RETRY:
  {
    printf("I got retry request\n");
    resources -> engine -> set_state_quit_menu(QUITMENU_RETRY);
    resources -> CurrentKeyPressed = 0;
    break;
  }
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
  combos_painter.update();
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
    if( ((position * (resources -> pieces_width) + position_bis * (resources->pieces_width)/2) )>= x)
    {
      x += (int)((resources->time_interval) / PIECE_MOVING_SPEED);
      if(x > position * (resources->pieces_width) + (position_bis )*resources->pieces_width/2)
      {
        x = position * resources->pieces_width + (position_bis )*resources->pieces_width/2;
        placed = true;
      }
    }
  }

  // Move the pieces to the left
  if(!placed)
  {  
    if( ((position * (resources->pieces_width) + (position_bis )*(resources->pieces_width/2)) ) <= x)
    {
      x -= (int)(resources->time_interval / PIECE_MOVING_SPEED);
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
  //float toPrint;

  falling_requested = false;

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
    // Only the second time - an old limitation
    /*if(combo == 2 && board.is_game_over())
      {
      resources -> engine -> set_state_gameover();
      return;
      }*/

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
        if(board.score + board.bonus_score > resources -> highscore)
        {
          resources -> engine -> set_state_gameover(MODE_HIGHSCORE);
          resources -> old_highscore = resources -> highscore;
          resources -> highscore = board.score + board.bonus_score;
          resources -> save_scores();
        }
        else
          resources -> engine -> set_state_gameover(MODE_GAMEOVER);
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
  board.calc_score();

  // Adding combo bonus
  if(combo > 1)
  {
    u_int delta_score = board.score - board.undo_score; 
    u_int combo_bonus = combo * delta_score / 10;
    board.bonus_score += combo_bonus;
    board.undo_bonus_score += combo_bonus;
  }
  combo = 0;

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

    combo = 0;

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
