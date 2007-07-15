/********************************************************************
                          OpenAlchemist

  File : Player.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <ClanLib/core.h>

#include "Player.h"
#include "Piece.h"
#include "Preferences.h"
#include "CommonResources.h"
#include "misc.h"
#include <math.h>

#define TO_RAD PI/180

Player::Player()
{
  next_piece1    = NULL;
  next_piece2    = NULL;

  current_piece1 = NULL;
  current_piece2 = NULL;

  srand(CL_System::get_time());
}

void Player::new_game()
{
  CommonResources *resources = common_resources_get_instance();

  angle = 0.0;
  x = resources->pieces_width/2 + 2*(resources->pieces_width);

  current_piece1 = new Piece(rand()%3);
  current_piece2 = new Piece(rand()%3);

  next_piece1 = new Piece(rand()%3);
  next_piece2 = new Piece(rand()%3);
  
  // Apply skin
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

void Player::load_gfx(std::string skin)
{
  CommonResources *resources = common_resources_get_instance();

  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx_pieces("pieces.xml", &zip, false);

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
   
  }

  CL_ResourceManager gfx("gfx.xml", &zip, false);
  next_left = CL_Integer_to_int("game/next_left", &gfx);
  next_top = CL_Integer_to_int("game/next_top", &gfx);

  game_top = CL_Integer_to_int("game/top", &gfx);
  game_left = CL_Integer_to_int("game/left", &gfx); 
  zone_top = CL_Integer_to_int("zone_top", &gfx);

  // c² = a²+b³
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
}

void Player::draw()
{
  board.draw();

  next_piece1 -> draw_mini();
  next_piece2 -> draw_mini();

  CommonResources *resources = common_resources_get_instance();

  current_piece1 -> set_position(game_left+x+cos(angle*TO_RAD)*current_pieces_r,
                                 zone_top+resources->pieces_height/2+sin((angle)*TO_RAD)*current_pieces_r);

  current_piece2 -> set_position(game_left+x+cos((angle+180)*TO_RAD)*current_pieces_r,
                                 zone_top+resources->pieces_height/2+sin((angle+180)*TO_RAD)*current_pieces_r);
     
  current_piece1 -> draw();
  current_piece2 -> draw();
}
