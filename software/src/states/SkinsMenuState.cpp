/********************************************************************
                          OpenAlchemist

  File : SkinsMenuState.cpp
  Description :Skins Menu Implementation
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


// Fist we load Skin propreties saved in the conf file

  std::string path = get_save_path();
#ifdef WIN32
  std::string file_path = path + "\\skins";
#else
  std::string file_path = path + "/skins";
#endif

  skins_list.clear();
  try
  {
    CL_InputSource_File file(file_path);
    while(file.tell() != file.size())
    {     
      Skin *sp = new Skin();
      sp -> filename = file.read_string();
      sp -> element = file.read_uint8();
      skins_list.insert(skins_list.end(), sp);

      // We load the logo sprite in the gfx ressources file
      CL_ResourceManager gfx("gfx.xml", new CL_Zip_Archive(sp -> filename), true);
      sp -> logo = new CL_Surface("logo", &gfx);
      
    }
    file.close();
    
  }
  catch(CL_Error e)
  {
    std::cout << "Error while reading " << file_path << " file, probably doesn't exist yet." << std::endl;
  }

// The, we scan the current ./skins folder

#ifdef WIN32
  std::string dir = CL_System::get_exe_path() + "skins\\";
#else
  std::string dir = CL_System::get_exe_path() + "skins/";
#endif

  CL_DirectoryScanner scanner;
  if (scanner.scan(dir, "*.zip"))
  {
    while(scanner.next())
    {
      if(scanner.is_readable())
      {
        try
        {
          std::string filename = dir+scanner.get_name();
          // We load the logo sprite in the gfx ressources file
          CL_ResourceManager gfx("gfx.xml", new CL_Zip_Archive(filename), true);
          CL_Surface *logo = new CL_Surface("logo", &gfx);

          bool found = false;
          for(u_int i = 0; i < skins_list.size(); ++i)
          {
            if(skins_list[i] -> filename == filename)
            {
              found = true;
              break;
            }
          }
          if(!found)
          {
            Skin *sp = new Skin();
            sp -> filename = filename;
            sp -> element = 3;
            sp -> logo = logo;
            skins_list.insert(skins_list.end(), sp);
          }
               
        }
        catch(CL_Error e)
        {
          std::cout << "Skin " << dir << scanner.get_name() << " is not valid." << std::endl;
        }
      }        

    }
  }

  // Calculating the lines number needed for the board
  number_y = skins_list.size() / 2;
  if(skins_list.size() % 2 > 0)
    number_y += 1;

  // Making the board
  skins_board[0] = new Skin* [number_y];
  skins_board[1] = new Skin* [number_y];

  // Initializing the board
  for(int x=0; x<2; ++x)
    for(int y=0; y<number_y; ++y)
    {
      skins_board[x][y] = NULL;
    }
  
  // Setting skins to the board
  int x= 0, y = 0;
  for(u_int i = 0; i < skins_list.size(); ++i)
  {
    skins_board[x][y] = skins_list[i];
    x++;
    if(x > 1)
    {
      y++;
      x = 0;
    }
  }

  // Initalizing variables
  selection_x = selection_y = 0;
  y_start = 0;
}

void SkinsMenuState::deinit()
{
  // Saving progression skin file
  std::string path = get_save_path();
#ifdef WIN32
  std::string file_path = path + "\\skins";
#else
  std::string file_path = path + "/skins";
#endif

  try
  {
    CL_OutputSource_File file(file_path);
    for(u_int i = 0; i < skins_list.size(); ++i)
    {
      file.write_string(skins_list[i]->filename);
      file.write_uint8 (skins_list[i]->element);  
    }
    file.close();
       
  }
  catch(CL_Error e)
  {
    std::cout << "Error while reading " << file_path << "file, probably doesn't exist yet." << std::endl;
  }

  for(u_int i = 0; i < skins_list.size(); ++i)
  {
    delete skins_list[i];
  }

  skins_list.clear();

  delete skins_board[0];
  delete skins_board[1];
}

void SkinsMenuState::load_gfx(std::string skin)
{
  // Getting skins resources
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("menu_skins.xml", &zip, false);

  // First, the sprites
  background = new CL_Sprite("menu/skins/background", &gfx); 
  logo_unavailable = new CL_Surface("menu/skins/logo-unavailable", &gfx); 

  cursor = new CL_Sprite("menu/skins/cursor", &gfx);
  arrow_down = new CL_Sprite("menu/skins/arrow-down/sprite", &gfx);
  arrow_down_left = CL_Integer_to_int("menu/skins/arrow-down/left", &gfx);
  arrow_down_top = CL_Integer_to_int("menu/skins/arrow-down/top", &gfx);

  arrow_up = new CL_Sprite("menu/skins/arrow-up/sprite", &gfx);
  arrow_up_left = CL_Integer_to_int("menu/skins/arrow-up/left", &gfx);
  arrow_up_top = CL_Integer_to_int("menu/skins/arrow-up/top", &gfx);
  
}

void SkinsMenuState::unload_gfx()
{

}

void SkinsMenuState::draw()
{
  int x = 400 - background -> get_width()/2;
  int y = 300 - background -> get_height()/2;
  background -> draw(x,y);

  y+=150;

  // Drawing logo skins
  for(int i=0; i<2; ++i)
    for(int j=0; j<2 && j+y_start<number_y; ++j)
    {
      if(skins_board[i][j+y_start])
      { 
        if(skins_board[i][j] -> logo)
          skins_board[i][j+y_start] -> logo -> draw(x+i*250, y+j*190);

        // If the skin is not available, we draw logo_unavailable
        if(common_resources -> skin != skins_board[i][j+y_start] -> filename
           && skins_board[i][j] -> element < (u_int) common_resources->player1.get_visible_pieces())
          logo_unavailable -> draw(x+i*250, y+j*190);
      }
    }

  // Drawing the cursor
  cursor -> draw(x+selection_x*250+30, y+(selection_y-y_start)*190-10);

  // Drawig arrows, if needed
  if(y_start + 2 < number_y)
  {
    arrow_down -> draw(arrow_down_left, arrow_down_top);
  }

  if(y_start > 0)
  {
    arrow_up -> draw(arrow_up_left, arrow_up_top);
  }

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

  // KEY DOWN
  if(common_resources -> key.down -> get())
  {
    // If we don't go outline
    if(selection_y + 1 < number_y)
    {
      // If there is a skin in this place
      if(skins_board[selection_x][selection_y + 1])
      {
        selection_y++;

        if(selection_y > y_start + 1)
          y_start ++;
      }
      // Else, we juste increment y_start
      else if(selection_y > y_start && selection_x == 1 && !skins_board[1][selection_y+1] && skins_board[0][selection_y+1])
      {
        y_start ++;
      }
    }
  }

  // KEY UP
  if(common_resources -> key.up -> get())
  {
    if(selection_y > 0 && skins_board[selection_x][selection_y-1])
    {
      selection_y--;

      if(selection_y < y_start)
        y_start --;
    }
  }

  // KEY RIGHT
  if(common_resources -> key.right -> get())
  {
    if(selection_x == 0 && skins_board[1][selection_y])
    {
      selection_x = 1;
    }
  }

  // KEY LEFT
  if(common_resources -> key.left -> get())
  {
    if(selection_x == 1 && skins_board[0][selection_y])
    {
      selection_x = 0;
    }
  }

  // KEY ENTER
  if(common_resources -> key.enter -> get())
  {
    if(skins_board[selection_x][selection_y] -> element >= (u_int) common_resources->player1.get_visible_pieces())
    {
      common_resources -> engine -> set_skin(skins_board[selection_x][selection_y] -> filename);
      step = STEP_DISAPPEARING;
    }
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
  arrow_up   -> set_alpha(alpha);
  arrow_down -> set_alpha(alpha);
  cursor     -> set_alpha(alpha);
  logo_unavailable -> set_alpha(alpha);

  for(u_int i = 0; i < skins_list.size(); ++i)
  {
    skins_list[i] -> logo -> set_alpha(alpha);
  }


}

void SkinsMenuState::disappear()
{  
  alpha -= APPEARING_SPEED * common_resources -> time_interval;

  background -> set_alpha(alpha);
  arrow_up   -> set_alpha(alpha);
  arrow_down -> set_alpha(alpha);
  cursor     -> set_alpha(alpha);
  logo_unavailable -> set_alpha(alpha);

  for(u_int i = 0; i < skins_list.size(); ++i)
  {
    skins_list[i] -> logo -> set_alpha(alpha);
  }

  if(alpha <= 0.0 || !common_resources -> engine -> is_opengl_used())
  {
    common_resources -> engine -> stop_current_state(); 
    start();
  }

}

void SkinsMenuState::start()
{
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

void SkinsMenuState::set_skin_elements(u_int element)
{
  for(u_int i = 0; i < skins_list.size(); ++i)
  {
    if(skins_list[i] -> filename == common_resources -> skin)
    {
      if(skins_list[i] -> element < element)
        skins_list[i] -> element = element;
    }
  }
}

SkinsMenuState::SkinsMenuState()
{

}

SkinsMenuState::~SkinsMenuState()
{
  deinit();

}



    