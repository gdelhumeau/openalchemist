/********************************************************************
                          OpenAlchemist

  File : PauseMenuState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


 *********************************************************************/

#include <ClanLib/core.h>

#include "PauseMenuState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"

enum
{ 
	PAUSE_ITEM_RESUME,
	PAUSE_ITEM_UNDO,
	PAUSE_ITEM_RETRY,
	PAUSE_ITEM_OPTIONS,
	PAUSE_ITEM_GIVEUP,
	PAUSE_ITEM_QUIT
};

void PauseMenuState::init ()
{
  items.clear();
  items.insert (items.end (), &resume_item);
  items.insert (items.end (), &undo_item);
  items.insert (items.end (), &retry_item);
  items.insert (items.end (), &options_item);
  items.insert (items.end (), &giveup_item);
  items.insert (items.end (), &quit_item);
}

void PauseMenuState::deinit () { }

void PauseMenuState::load_gfx (std::string skin)
{
  // Getting skins resources
  CL_Zip_Archive zip (skin);
  CL_ResourceManager gfx ("menu_pause.xml", &zip, false);

  // First, the sprites
  background = new CL_Sprite ("menu_pause/background", &gfx);

  int x = 400 - background -> get_width () / 2;
  int y = 300 - background -> get_height () / 2;


  // resume
  resume_item.set_gfx (new CL_Sprite ("menu_pause/resume/unselected", &gfx),
                       new CL_Sprite ("menu_pause/resume/selected", &gfx),
                       NULL);
  resume_item.set_x (x + CL_Integer_to_int ("menu_pause/resume/left", &gfx));
  resume_item.set_y (y + CL_Integer_to_int ("menu_pause/resume/top", &gfx));

  // undo
  undo_item.set_gfx (new CL_Sprite ("menu_pause/undo/unselected", &gfx),
                     new CL_Sprite ("menu_pause/undo/selected", &gfx),
                     new CL_Sprite ("menu_pause/undo/unavailable", &gfx));
  undo_item.set_x (x + CL_Integer_to_int ("menu_pause/undo/left", &gfx));
  undo_item.set_y (y + CL_Integer_to_int ("menu_pause/undo/top", &gfx));
  undo_item.set_locked (true);

  // retry
  retry_item.set_gfx (new CL_Sprite ("menu_pause/retry/unselected", &gfx),
                      new CL_Sprite ("menu_pause/retry/selected", &gfx),
                      NULL);
  retry_item.set_x (x + CL_Integer_to_int ("menu_pause/retry/left", &gfx));
  retry_item.set_y (y + CL_Integer_to_int ("menu_pause/retry/top", &gfx));

  // options
  options_item.set_gfx (new CL_Sprite ("menu_pause/options/unselected", &gfx),
                        new CL_Sprite ("menu_pause/options/selected", &gfx),
                        NULL);
  options_item.set_x (x + CL_Integer_to_int ("menu_pause/options/left", &gfx));
  options_item.set_y (y + CL_Integer_to_int ("menu_pause/options/top", &gfx));

  // give up
  giveup_item.set_gfx (new CL_Sprite ("menu_pause/giveup/unselected", &gfx),
                       new CL_Sprite ("menu_pause/giveup/selected", &gfx),
                       NULL);
  giveup_item.set_x (x + CL_Integer_to_int ("menu_pause/giveup/left", &gfx));
  giveup_item.set_y (y + CL_Integer_to_int ("menu_pause/giveup/top", &gfx));

  // quit
  quit_item.set_gfx (new CL_Sprite ("menu_pause/quit/unselected", &gfx),
                     new CL_Sprite ("menu_pause/quit/selected", &gfx),
                     NULL);
  quit_item.set_x (x + CL_Integer_to_int ("menu_pause/quit/left", &gfx));
  quit_item.set_y (y + CL_Integer_to_int ("menu_pause/quit/top", &gfx));


}

void PauseMenuState::unload_gfx ()
{
  resume_item.unload_gfx ();
  undo_item.unload_gfx ();
  retry_item.unload_gfx ();
}

void PauseMenuState::action_performed (int selection)
{
  switch (selection)
    {
    case PAUSE_ITEM_RESUME:
      common_resources -> engine -> stop_current_state ();
      break;
    case PAUSE_ITEM_UNDO:
      common_resources -> player1.undo ();
      common_resources -> engine -> stop_current_state ();
      common_resources -> engine -> set_state_ingame ();
      break;
    case PAUSE_ITEM_RETRY:
      {
        if (common_resources -> player1.is_game_over ())
          {
            common_resources -> player1.new_game ();
            common_resources -> engine -> stop_current_state ();
            common_resources -> engine -> set_state_ingame ();
          }
        else
          {
            common_resources -> engine -> stop_current_state ();
            common_resources -> engine -> set_state_quit_menu (QUITMENU_RETRY);
          }
        break;
      }
    case PAUSE_ITEM_GIVEUP:
      {
        if (common_resources -> player1.is_game_over ())
          {
            common_resources -> engine -> stop_current_state ();
            common_resources -> engine -> set_state_title ();
          }
        else
          {
            common_resources -> player1.give_up ();
            common_resources -> engine -> stop_current_state ();
            common_resources -> engine -> set_state_quit_menu (QUITMENU_GIVE_UP);
          }
        break;
      }
    case PAUSE_ITEM_OPTIONS:
      {
        start ();
        common_resources -> engine -> set_state_options_menu ();
        break;
      }
    case PAUSE_ITEM_QUIT:
      {
        common_resources -> engine -> set_state_quit_menu (QUITMENU_EXIT);
        break;
      }
    }

}

void PauseMenuState::update_child ()
{
  undo_item.set_locked (!common_resources -> player1.is_undo_available ());
}

PauseMenuState::PauseMenuState () {
 }

PauseMenuState::~PauseMenuState ()
{
  deinit ();
}



