/********************************************************************
                          OpenAlchemist

  File : QuitMenuState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include "QuitMenuState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"

#define SELECTION_YES 1
#define SELECTION_NO  0

void QuitMenuState::init()
{
  GameState::init();

  panel          = NULL;
  yes_selected   = NULL;
  yes_unselected = NULL;
  no_selected    = NULL;
  no_unselected  = NULL;

  selection = SELECTION_NO;
}

void QuitMenuState::deinit()
{

}

void QuitMenuState::load_gfx(std::string skin)
{
  // Getting skins resources
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("menu_quit.xml", &zip, false);

  panel = new CL_Sprite("menu/quit/dialog-panel/sprite", &gfx);
  panel_x = CL_Integer_to_int("menu/quit/dialog-panel/left", &gfx);
  panel_y = CL_Integer_to_int("menu/quit/dialog-panel/top", &gfx); 

  yes_selected   = new CL_Sprite("menu/quit/dialog-yes/selected", &gfx);
  yes_unselected = new CL_Sprite("menu/quit/dialog-yes/unselected", &gfx);
  yes_x = CL_Integer_to_int("menu/quit/dialog-yes/left", &gfx);
  yes_y = CL_Integer_to_int("menu/quit/dialog-yes/top", &gfx); 

  no_selected   = new CL_Sprite("menu/quit/dialog-no/selected", &gfx);
  no_unselected = new CL_Sprite("menu/quit/dialog-no/unselected", &gfx);
  no_x = CL_Integer_to_int("menu/quit/dialog-no/left", &gfx);
  no_y = CL_Integer_to_int("menu/quit/dialog-no/top", &gfx); 

}

void QuitMenuState::unload_gfx()
{
  if(panel)
  {
    delete panel;
    panel = NULL;
  }
  if(yes_selected)
  {
    delete yes_selected;
    yes_selected = NULL;
  }
  if(yes_unselected)
  {
    delete yes_unselected;
    yes_unselected = NULL;
  }
  if(no_selected)
  {
    delete no_selected;
    no_selected = NULL;
  }
  if(no_unselected)
  {
    delete no_unselected;
    no_unselected = NULL;
  }

}


void QuitMenuState::draw()
{
  panel -> draw(panel_x, panel_y);

  if(SELECTION_YES == selection)
  {
    yes_selected -> draw(yes_x, yes_y);
    no_unselected -> draw(no_x, no_y);
  }
  else
  {
    yes_unselected -> draw(yes_x, yes_y);
    no_selected -> draw(no_x, no_y);
  }
}

void QuitMenuState::update()
{
  panel        -> update();
  yes_selected -> update();
  no_selected  -> update();
}

void QuitMenuState::events()
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();  

  if(resources -> key.enter -> get())
  {
    if(SELECTION_YES == selection)
      resources -> engine -> stop();
    else
      resources -> engine -> stop_current_state();
  }

  if(resources -> key.escape -> get())
  {
    resources -> engine -> stop_current_state();
  }

  if(resources -> key.left -> get())
  {
    selection = SELECTION_YES;
  }

  if(resources -> key.right -> get())
  {
    selection = SELECTION_NO;
  }


}

bool QuitMenuState::front_layer_behind()
{
  return true;
}

QuitMenuState::QuitMenuState()
{

}

QuitMenuState::~QuitMenuState()
{
  unload_gfx();
}



