/********************************************************************
                          OpenAlchemist

  File : SkinsMenuState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <ClanLib/core.h>

#include "SkinsMenuState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"

#define STEP_APPEARING 0
#define STEP_NORMAL 1
#define STEP_DISAPPEARING 2

#define APPEARING_SPEED 0.003

void SkinsMenuState::init()
{
  GameState::init();

  std::string path = get_save_path();
#ifdef WIN32
  std::string file_path = path + "\\skins";
#else
  std::string file_path = path + "/skins";
#endif

  propreties_list.clear();
  try
  {
    CL_InputSource_File file(file_path);
    while(file.tell() != file.size())
    {
      SkinsPropreties *sp = new SkinsPropreties();
      sp -> filename = file.read_string();
      sp -> element = file.read_uint8();
      propreties_list.insert(propreties_list.end(), sp);
    }
    file.close();
    
  }
  catch(CL_Error e)
  {
    std::cout << "Error while reading " << file_path << " file, probably doesn't exist yet." << std::endl;
  }
}

void SkinsMenuState::deinit()
{
  
}

void SkinsMenuState::load_gfx(std::string skin)
{
  // Getting skins resources
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("menu_skins.xml", &zip, false);

  // First, the sprites
  background = new CL_Sprite("menu/skins/background", &gfx); 
  
}

void SkinsMenuState::unload_gfx()
{

}

void SkinsMenuState::draw()
{
  int x = 400 - background -> get_width()/2;
  int y = 300 - background -> get_height()/2;
  background -> draw(x,y);

}

void SkinsMenuState::update()
{
  switch(step)
  {
  case STEP_APPEARING:
    appear();
    break;
  case STEP_DISAPPEARING:
    disappear();
    break;
  }
}

void SkinsMenuState::events()
{
  if(step != STEP_NORMAL)
    return;

  if(common_resources->key.echap->get() || common_resources->key.skins->get())
  {   
    step = STEP_DISAPPEARING;
  }

}

void SkinsMenuState::appear()
{ 
  if(alpha + APPEARING_SPEED*common_resources -> time_interval >= 1.0)
  {
    step = STEP_NORMAL;
    alpha = 1.0;
  }
  else
    alpha += APPEARING_SPEED * common_resources -> time_interval;

  background -> set_alpha(alpha);


}

void SkinsMenuState::disappear()
{  
  alpha -= APPEARING_SPEED * common_resources -> time_interval;

  background -> set_alpha(alpha);

  if(alpha <= 0.0 || !common_resources -> engine -> is_opengl_used())
  {
    common_resources -> engine -> stop_current_state(); 
    start();
  }
 
}

void SkinsMenuState::start()
{
  selection = 0;
  if(common_resources -> engine -> is_opengl_used())
  {
    step = STEP_APPEARING;
    alpha = 0.0;
  }
  else
  {
    step = STEP_NORMAL;
  }
}

bool SkinsMenuState::front_layer_behind()
{
  return true;
}

SkinsMenuState::SkinsMenuState()
{

}

SkinsMenuState::~SkinsMenuState()
{
  deinit();
}



