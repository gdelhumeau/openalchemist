/********************************************************************
                          OpenAlchemist
 
  File : Player.cpp
  Description : Player implementation
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
 
 
*********************************************************************/

#include "memory.h"
#include <math.h>
#include <cstdlib>

#include <ClanLib/core.h>

#include "Player.h"
#include "Piece.h"
#include "Preferences.h"
#include "CommonResources.h"
#include "misc.h"
#include "Board.h"
#include "GameEngine.h"
#include "AudioManager.h"

static const float PI = 3.1415926535897932384f;
static const float TO_RAD 		= PI / 180;
static const float PIECE_MOVING_SPEED 	= 0.4;
static const float PIECE_ROTATION_SPEED = 0.45;

Player::Player()
{
  // Setting objects to NULL
  _p_next_piece1    = NULL;
  _p_next_piece2    = NULL;
  _p_current_piece1 = NULL;
  _p_current_piece2 = NULL;

  // Initializing random numbers generator
  srand(CL_System::get_time());

  // Making key objects
  _p_key_change_angle = my_new KeyboardKey(CL_KEY_UP    , true );
  _p_key_left         = my_new KeyboardKey(CL_KEY_LEFT  , true );
  _p_key_right        = my_new KeyboardKey(CL_KEY_RIGHT , true );
  _p_key_falling      = my_new KeyboardKey(CL_KEY_DOWN  , false);

  _combo = 0;  

}

Player::~Player()
{
  unload_gfx();
  // Deleting key objects
  my_delete(_p_key_change_angle);
  my_delete(_p_key_left);
  my_delete(_p_key_right);
  my_delete(_p_key_falling);
	
  if(_p_current_piece1)
  {
    my_delete(_p_current_piece1);
    _p_current_piece1 = NULL;
  }
  if(_p_current_piece2)
  {
    my_delete(_p_current_piece2);
    _p_current_piece2 = NULL;
  }
  if(_p_next_piece1)
  {
    my_delete(_p_next_piece1);
    _p_next_piece1 = NULL;
  }
  if(_p_next_piece2)
  {
    my_delete(_p_next_piece2);
    _p_next_piece2 = NULL;
  }
}

void Player::new_game()
{
  term_game();
		
  // Getting resources
  CommonResources *resources = common_resources_get_instance();

  // Creating my_new pieces for playable pieces and next pieces		
  _p_current_piece1 = my_new Piece(rand()%3);
  _p_current_piece2 = my_new Piece(rand()%3);
  _p_next_piece1 = my_new Piece(rand()%3);
  _p_next_piece2 = my_new Piece(rand()%3);

  // Setting playable pieces position
  _angle = 0.0;
  _aimed_angle = 0;
  _position = 2;
  _position_bis = 1;
  _is_forced_bis = false;
  _is_placed = true;
  _undo_possible = false;
  _next_next_piece1 = 0;
  _next_next_piece2 = 0;
  _x = _position * resources->pieces_width + (_position_bis )*resources->pieces_width/2;
  _p_next_piece1 -> set_position(_next_left, _next_top);
  _p_next_piece2 -> set_position(_next_left+((resources->pieces_width)/2),_next_top);

  _is_falling_requested = false;
  _game_mode = GAME_MODE_PLAYING;

  _board.clear();
  _board.unlocked_pieces = 3;
  _board.visible_pieces  = 3;
  _board.score = 0;
  _board.bonus_score = 0;
  _board.calc_score();

  _combo = 0;

  // Applying skin
  int value;
  value = _p_next_piece1 -> get_piece_number();

  _p_next_piece1 -> set_sprites(&_pieces_normal[value], &_pieces_appearing[value],
				&_pieces_disappearing[value], &_pieces_mini[value]);

  value = _p_next_piece2 -> get_piece_number();
  _p_next_piece2 -> set_sprites(&_pieces_normal[value], &_pieces_appearing[value],
				&_pieces_disappearing[value], &_pieces_mini[value]);

  value = _p_current_piece1 ->  get_piece_number();
  _p_current_piece1 -> set_sprites(&_pieces_normal[value], &_pieces_appearing[value],
				   &_pieces_disappearing[value], &_pieces_mini[value]);

  value = _p_current_piece2 ->  get_piece_number();
  _p_current_piece2 -> set_sprites(&_pieces_normal[value], &_pieces_appearing[value],
				   &_pieces_disappearing[value], &_pieces_mini[value]);

}

void Player::term_game()
{
  if(_p_current_piece1)
  {
    my_delete(_p_current_piece1);
    _p_current_piece1 = NULL;
  }
		
  if(_p_current_piece2)
  {
    my_delete(_p_current_piece2);
    _p_current_piece2 = NULL;
  }
		
  if(_p_next_piece1)
  {
    my_delete(_p_next_piece1);
    _p_next_piece1 = NULL;
  }
		
  if(_p_next_piece2)
  {
    my_delete(_p_next_piece2);
    _p_next_piece2 = NULL;
  }
}

void Player::load_gfx(CL_GraphicContext & gc, std::string skin)
{
  unload_gfx();
	
  // Getting resources
  CommonResources *resources = common_resources_get_instance();

  // Getting skins resources
  CL_VirtualFileSystem vfs(skin, true);
  CL_VirtualDirectory vd(vfs, "./");
  CL_ResourceManager gfx_pieces("pieces.xml", vd);
  CL_ResourceManager gfx_preview_pieces("pieces_preview.xml", vd);
  CL_ResourceManager gfx("general.xml", vd);

  // Getting preferences (to know if colorbling is activated)
  Preferences *pref = pref_get_instance();

  // First we load the sprites
  for(int i = 1; i<=NUMBER_OF_PIECES; ++i)
  {
    if(pref -> colorblind)
      _pieces_normal[i-1] = CL_Sprite(gc, "pieces/piece_"+to_string(i)+"/normal_color_blind", &gfx_pieces);
    else
      _pieces_normal[i-1] = CL_Sprite(gc, "pieces/piece_"+to_string(i)+"/normal", &gfx_pieces);

    _pieces_appearing[i-1] = CL_Sprite(gc, "pieces/piece_"+to_string(i)+"/appear", &gfx_pieces);
    _pieces_disappearing[i-1] = CL_Sprite(gc, "pieces/piece_"+to_string(i)+"/disappear", &gfx_pieces);

    if(pref -> colorblind)
      _pieces_mini[i-1] = CL_Sprite(gc, "pieces_preview/piece_"+to_string(i)+"/little_color_blind", &gfx_preview_pieces);
    else
      _pieces_mini[i-1] = CL_Sprite(gc, "pieces_preview/piece_"+to_string(i)+"/little", &gfx_preview_pieces);

    _pieces_preview_x[i-1] = CL_Integer_to_int("pieces_preview/piece_"+to_string(i)+"/left", &gfx_preview_pieces);
    _pieces_preview_y[i-1] = CL_Integer_to_int("pieces_preview/piece_"+to_string(i)+"/top", &gfx_preview_pieces);

    if(i>3)
    {
      _pieces_hidden[i-4] = CL_Sprite(gc, "pieces_preview/piece_"+to_string(i)+"/hidden", &gfx_preview_pieces);
    }
  }

  // Getting sprites position
  _next_left = CL_Integer_to_int("game/next_left", &gfx);
  _next_top = CL_Integer_to_int("game/next_top", &gfx);

  // Getting game zone position
  _board.game_top = CL_Integer_to_int("game/top", &gfx);
  _board.game_left = CL_Integer_to_int("game/left", &gfx);
  _board.zone_top = CL_Integer_to_int("zone_top", &gfx);

  _board.score_top = CL_Integer_to_int("score_top", &gfx);
  _board.score_right = CL_Integer_to_int("score_right", &gfx);
  _board.bonus_top = CL_Integer_to_int("bonus_score_top", &gfx);
  _board.bonus_right = CL_Integer_to_int("bonus_score_right", &gfx);
  _board.hightscore_top = CL_Integer_to_int("hight_score_top", &gfx);
  _board.hightscore_right = CL_Integer_to_int("hight_score_right", &gfx);

  // Calculating c² = a²+b³
  _current_pieces_r = resources->pieces_width/2;

  // Then, we appmy_new ew sprites
  if(_p_next_piece1 && _p_next_piece2 && _p_current_piece1 && _p_current_piece2)
  {
    int value;
    value = _p_next_piece1 -> get_piece_number();

    _p_next_piece1 -> set_sprites(&_pieces_normal[value], &_pieces_appearing[value],
				  &_pieces_disappearing[value], &_pieces_mini[value]);

    value = _p_next_piece2 -> get_piece_number();
    _p_next_piece2 -> set_sprites(&_pieces_normal[value], &_pieces_appearing[value],
				  &_pieces_disappearing[value], &_pieces_mini[value]);

    value = _p_current_piece1 ->  get_piece_number();
    _p_current_piece1 -> set_sprites(&_pieces_normal[value], &_pieces_appearing[value],
				     &_pieces_disappearing[value], &_pieces_mini[value]);

    value = _p_current_piece2 ->  get_piece_number();
    _p_current_piece2 -> set_sprites(&_pieces_normal[value], &_pieces_appearing[value],
				     &_pieces_disappearing[value], &_pieces_mini[value]);

    _p_next_piece1 -> set_position(_next_left, _next_top);
    _p_next_piece2 -> set_position(_next_left+((resources->pieces_width)/2),_next_top);
  }

  // And to the board too
  _board.apply_skin(_pieces_normal, _pieces_appearing, _pieces_disappearing, _pieces_mini);

  // Loading gfx for progress bar
  _progress_bar.load_gfx(gc, skin);

  // Loading gfx for combos painter
  _combos_painter.load_gfx(gc, skin);

}

void Player::unload_gfx()
{
   _progress_bar.unload_gfx();
}

void Player::draw(CL_GraphicContext & gc)
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();

  // Drawing unlocked pieces
  for(int i=0; i<NUMBER_OF_PIECES; ++i)
  {
    if(i >= _board.visible_pieces)
      _pieces_hidden[i-3].draw(gc, _pieces_preview_x[i], _pieces_preview_y[i]);
    else
      _pieces_mini[i].draw(gc, _pieces_preview_x[i], _pieces_preview_y[i]);
  }

  // Drawing board
  _board.draw(gc);

  // Drawing the progress bar
  // TODO : must work with differents difficulties
  if(resources -> highscore > 0)
  {
    int percentage = (int)((double)(_board.score + _board.bonus_score) / (double)resources -> highscore * 100.0);
    if(percentage > 100)
      percentage = 100;
    _progress_bar.draw(gc, percentage);
  }
  else
  {
    _progress_bar.draw(gc, 100);
  }

  // Drawing next pieces
  _p_next_piece1 -> draw_mini(gc);
  _p_next_piece2 -> draw_mini(gc);


  if(GAME_MODE_PLAYING == _game_mode)
  {
    // Setting playable pieces position
    _p_current_piece1 -> set_position(_board.game_left+_x+cos(_angle*TO_RAD)*_current_pieces_r,
				      _board.zone_top+resources->pieces_height/2+sin((_angle)*TO_RAD)*_current_pieces_r);

    _p_current_piece2 -> set_position(_board.game_left+_x+cos((_angle+180)*TO_RAD)*_current_pieces_r,
				      _board.zone_top+resources->pieces_height/2+sin((_angle+180)*TO_RAD)*_current_pieces_r);

    // Displaying playable pieces
    _p_current_piece1 -> draw(gc);
    _p_current_piece2 -> draw(gc);
  }

  // Drawing combo
  if(_combo > 1)
  {
    _combos_painter.set_score(_combo - 1);
  }

  _combos_painter.draw(gc);
}

void Player::events(CL_DisplayWindow & window)
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();

  if(GAME_MODE_PLAYING == _game_mode)
  {
    // Change the order of the pieces
    if(_p_key_change_angle->get(window))
    {
      change_angle();
    }

    // Look the key to know if we have to move the pieces to the left
    if(_p_key_left->get(window))
    {
      move_left();
    }

    // Look the key to know if we have to move the pieces to the right
    if(_p_key_right->get(window))
    {
      move_right();
    }

    // It's time for the pieces to fall
    if(_p_key_falling -> get(window))
    {
      _is_falling_requested = true;
    }

    // Cheatting
		CL_InputDevice &keyboard = window.get_ic().get_keyboard();
    if(keyboard.get_keycode(CL_KEY_A) && keyboard.get_keycode(CL_KEY_L))
    {
      _board.unlocked_pieces = NUMBER_OF_PIECES;
      _board.visible_pieces = NUMBER_OF_PIECES;
    }
  }

  // Undo the last move
  if(resources->key.undo -> get(window))
  {
    undo();
  }

  // Retry current game
  if(resources -> key.retry -> get(window))
  {
    resources -> p_engine -> set_state_quit_menu(QUITMENU_RETRY);
  }

}

void Player::change_angle()
{
  // Change the order of the pieces    
  _aimed_angle += 90;
  _is_placed = false;

  if((_aimed_angle%180 == 90))
  {
    _position_bis = 0;
    if(_is_forced_bis)
    {
      _position ++;
      _is_forced_bis = false;
    }
  }
  else
  {
    if(_position == NUMBER_OF_COLS -1)
    {
      _position --;
      _is_forced_bis = true;
    }        

    _position_bis = 1;
  }

}

void Player::move_left()
{
  if(_position > 0)
  {
    _old_position = _position;
    _old_position_bis = _position_bis;
    _position--;
    _is_placed = false;
  }
}

void Player::move_right()
{
  if(_position < NUMBER_OF_COLS - 1)
  {
    if(!(_position == NUMBER_OF_COLS - 2 && _position_bis))
    {
      _old_position = _position;
      _old_position_bis = _position_bis;
      _position++;
      _is_placed = false;
    }
  }
}

void Player::update()
{
  if(GAME_MODE_PLAYING == _game_mode)
  {
    _update_playing();
  }
  else if(GAME_MODE_FALLING_AND_CREATING == _game_mode)
  {
    _update_falling_and_creating();
  }
  else if(GAME_MODE_DESTROYING == _game_mode)
  {
    _update_destroying();
  }
  _combos_painter.update();
}

void Player::_update_playing()
{
  static CommonResources *resources = common_resources_get_instance();

  // Move the pieces if the order has been changed
  if(_angle<_aimed_angle)
  {
    _angle += resources->time_interval * PIECE_ROTATION_SPEED;
    if(_angle>=_aimed_angle)
    {
      while(_aimed_angle>=360)
      {
	_aimed_angle-=360;
      }
      _angle = _aimed_angle;
    }
  }

  // Move the pieces to the right
  if(!_is_placed)
  {
    if(_position * resources->pieces_width + _position_bis *resources->pieces_width/2 >= _x)
    {
      _x += resources->time_interval * PIECE_MOVING_SPEED;
      if(_x > _position * resources->pieces_width + (_position_bis )*resources->pieces_width/2)
      {
	_x = _position * resources->pieces_width + (_position_bis )*resources->pieces_width/2;
	_is_placed = true;
      }
    }
  }

  // Move the pieces to the left
  if(!_is_placed)
  {
    if(_position * resources->pieces_width + (_position_bis )*resources->pieces_width/2 <= _x)
    {
      _x -= resources->time_interval * PIECE_MOVING_SPEED;
      if(_x < _position * resources->pieces_width + (_position_bis)*resources->pieces_width/2)
      {
	_x = _position * resources->pieces_width + (_position_bis)*resources->pieces_width/2;
	_is_placed = true;
      }
    }
  }

  // Falling the playable pieces
  if(_is_falling_requested && _is_placed && (_angle >= _aimed_angle))
  {
    fall();
  }
}

void Player::fall()
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();

  _is_falling_requested = false;

  _undo_possible = true;
  _undo_position = _position;
  _undo_position_bis = _position_bis;
  _undo_piece1_number = _p_current_piece1 -> get_piece_number();
  _undo_piece2_number = _p_current_piece2 -> get_piece_number();
  _undo_angle = _aimed_angle;


  _p_current_piece1 -> set_position(_board.game_left+_x+cos(_angle*TO_RAD)*_current_pieces_r,
				    _board.zone_top+resources->pieces_height/2+sin((_angle)*TO_RAD)*_current_pieces_r);

  _p_current_piece2 -> set_position(_board.game_left+_x+cos((_angle+180)*TO_RAD)*_current_pieces_r,
				    _board.zone_top+resources->pieces_height/2+sin((_angle+180)*TO_RAD)*_current_pieces_r);

  _board.add_pieces(_p_current_piece1, _p_current_piece2);
	
  _p_current_piece1 = NULL;
  _p_current_piece2 = NULL;



  // We must respect the next piece order (ex: red to the left, blue to the right...)
  float piece1x = cos(_angle*TO_RAD)*_current_pieces_r;
  float piece2x = cos((_angle+180)*TO_RAD)*_current_pieces_r;

  if(piece1x < piece2x)
  {
    _p_current_piece1 = my_new Piece(_p_next_piece1->get_piece_number());
    _p_current_piece2 = my_new Piece(_p_next_piece2->get_piece_number());
  }
  else
  {
    _p_current_piece1 = my_new Piece(_p_next_piece2->get_piece_number());
    _p_current_piece2 = my_new Piece(_p_next_piece1->get_piece_number());
  }


  int value = _p_current_piece1 -> get_piece_number();
  _p_current_piece1 -> set_sprites(&_pieces_normal[value], &_pieces_appearing[value],
				   &_pieces_disappearing[value], &_pieces_mini[value]);

  value = _p_current_piece2 -> get_piece_number();
  _p_current_piece2 -> set_sprites(&_pieces_normal[value], &_pieces_appearing[value],
				   &_pieces_disappearing[value], &_pieces_mini[value]);


  _game_mode = GAME_MODE_FALLING_AND_CREATING;

  g_audio_manager.play_sound(SOUND_FALL);
}

void Player::_update_falling_and_creating()
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();

  bool placed = _board.fall_and_create();

  if(placed)
  {

    _combo ++;

    // Only the second time - an old limitation
    /*if(combo == 2 && board.is_game_over())
      {
      resources -> engine -> set_state_gameover();
      return;
      }*/

    bool to_destroy = _board.detect_pieces_to_destroy();

    if(to_destroy)
    {
      _game_mode = GAME_MODE_DESTROYING;
      //game_mode = GAME_MODE_TO_PLAYING;
      g_audio_manager.play_sound(SOUND_DESTROY);
    }
    else
    {
      if(_board.is_game_over())
      {
	resources -> p_engine -> set_skin_element(_board.visible_pieces);
	if(_board.score + _board.bonus_score > resources -> highscore)
	{
	  resources -> p_engine -> set_state_gameover(MODE_HIGHSCORE);
	  resources -> old_highscore = resources -> highscore;
	  resources -> highscore = _board.score + _board.bonus_score;
	  resources -> save_scores();
	}
	else
	  resources -> p_engine -> set_state_gameover(MODE_GAMEOVER);
	return;
      }
      _prepare_to_play();
      _game_mode = GAME_MODE_PLAYING;
    }

  }
}

void Player::_update_destroying()
{
  bool destroyed = _board.destroy();

  if(destroyed)
  {
    _board.create_new_pieces(_pieces_normal, _pieces_appearing, _pieces_disappearing, _pieces_mini);

    _board.detect_pieces_to_fall();
    _game_mode = GAME_MODE_FALLING_AND_CREATING;

    g_audio_manager.play_sound(SOUND_CREATION);

  }

}

void Player::_prepare_to_play()
{
  _board.calc_score();

  // Adding combo bonus
  if(_combo > 1)
  {
    u_int delta_score = _board.score - _board.undo_score;
    u_int combo_bonus = _combo * delta_score / 10;
    _board.bonus_score += combo_bonus;
    _board.undo_bonus_score += combo_bonus;
  }
  _combo = 0;

  if(_next_next_piece1 >= 0)
  {
    _p_next_piece1 -> set_piece_number(_next_next_piece1);
    _p_next_piece2 -> set_piece_number(_next_next_piece2);
    _next_next_piece1 = -1;
  }
  else
  {
    _p_next_piece1 -> set_piece_number(rand()%(_board.unlocked_pieces));
    _p_next_piece2 -> set_piece_number(rand()%(_board.unlocked_pieces));
  }

  int value;
  value = _p_next_piece1 -> get_piece_number();
  _p_next_piece1 -> set_sprites(&_pieces_normal[value], &_pieces_appearing[value],
				&_pieces_disappearing[value], &_pieces_mini[value]);

  value = _p_next_piece2 -> get_piece_number();
  _p_next_piece2 -> set_sprites(&_pieces_normal[value], &_pieces_appearing[value],
				&_pieces_disappearing[value], &_pieces_mini[value]);

  _board.calc_score();

}

void Player::undo()
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();

  // First verify than the last move is not the first one
  if(_undo_possible)
  {
    _undo_possible = false;

    _board.undo(_pieces_normal, _pieces_appearing, _pieces_disappearing, _pieces_mini);

    _next_next_piece1 = _p_next_piece1 -> get_piece_number();
    _next_next_piece2 = _p_next_piece2 -> get_piece_number();


    int value = _p_current_piece1 -> get_piece_number();
    _p_next_piece1 -> set_piece_number(value);
    _p_next_piece1 -> set_sprites(&_pieces_normal[value], &_pieces_appearing[value],
				  &_pieces_disappearing[value], &_pieces_mini[value]);

    value = _p_current_piece2 -> get_piece_number();
    _p_next_piece2 -> set_piece_number(value);
    _p_next_piece2 -> set_sprites(&_pieces_normal[value], &_pieces_appearing[value],
				  &_pieces_disappearing[value], &_pieces_mini[value]);

    value = _undo_piece1_number;
    _p_current_piece1 -> set_piece_number(value);
    _p_current_piece1 -> set_sprites(&_pieces_normal[value], &_pieces_appearing[value],
				     &_pieces_disappearing[value], &_pieces_mini[value]);

    value = _undo_piece2_number;
    _p_current_piece2 -> set_piece_number(value);
    _p_current_piece2 -> set_sprites(&_pieces_normal[value], &_pieces_appearing[value],
				     &_pieces_disappearing[value], &_pieces_mini[value]);


    _position = _undo_position;
    _position_bis = _undo_position_bis;
    _x = _position * resources->pieces_width + _position_bis * resources->pieces_width / 2;

    _angle = _undo_angle;
    _aimed_angle = (int)_undo_angle;

    _combo = 0;

    _game_mode = GAME_MODE_PLAYING;

  }
}

bool Player::is_undo_available()
{
  return _undo_possible;
}

int Player::get_visible_pieces()
{
  return _board.visible_pieces;
}

u_int Player::get_score()
{
  return _board.score + _board.bonus_score;
}

bool Player::is_game_over()
{
  return _board.is_game_over();
}

void Player::give_up()
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();
  resources -> p_engine -> set_skin_element(_board.visible_pieces);
  _board.clear();
  _board.unlocked_pieces = 3;
  _board.visible_pieces  = 3;
  _board.score = 0;
  _board.bonus_score = 0;

}
