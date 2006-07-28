/* OpenAlchemist - just a simple game 
 * ----------------------------------
 *
 * Copyright (C) 2006 Guillaume Delhumeau <guillaume.delhumeau at laposte.net>
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

/**
 * This method runs the skin-selector
 */
void Game::choose_skin()
{

  pause_step = PAUSE_STEP_SKINS;

  skins_list.clear();
  skins_logo_list.clear();

  skins_current_selection = 0;
  skins_list_index_top = 0;

#ifdef WIN32
  std::string dir = CL_System::get_exe_path() + "skins\\";
#else
  std::string dir = CL_System::get_exe_path() + "skins/";
#endif

  skins_number = 0;
  CL_DirectoryScanner scanner;
  if (scanner.scan(dir, "*.zip"))
  {
    while(scanner.next())
    {
      if(scanner.is_readable())
      {
        try
          {
            CL_ResourceManager gfx("gfx.xml", new CL_Zip_Archive(dir+scanner.get_name()), true);
            CL_Surface *logo = new CL_Surface("logo", &gfx);
            skins_logo_list.insert(skins_logo_list.end(), logo);
            skins_list.insert(skins_list.end(), dir+scanner.get_name());
            
            if(skin == dir+scanner.get_name())
            {
              skins_current_selection = skins_number;
              skins_list_index_top = skins_number - 2;

              if(skins_list_index_top < 0)
              {               
                skins_list_index_top = 0;
              }
            }         
            skins_number++;
          }
        catch(CL_Error e)
          {
            std::cout << "Skin " << dir << scanner.get_name() << " is not valid \n"; 
          }
      }        
       
    }
  }

  
  

  /*std::list<std::string>::iterator it = skins_list.begin();
  while(it != skins_list.end())
  {
    std::string name = (std::string)*it;
    std::cout << name << "\n";
    it++;
    }*/ 
  
}

void Game::draw_skins_selector()
{

  /*int x = 400 - pause_background -> get_width()/2;*/
    int y = 300 - pause_background -> get_height()/2; 

  for(u_int i=0; i<skins_list.size() && i<3; ++i)
  {
    if((int)i+(int)skins_list_index_top == (int)skins_current_selection)
      skins_selector -> draw(240, y+i*170+40);

    skins_logo_list[i+skins_list_index_top] -> draw(250, y+i*170+50);
  }
}

void Game::key_events_skins_selector()
{
  if(key_echap->get())
  {   
    if(pause_requested)
      pause_step = PAUSE_STEP_MENU;    
    else
      pause = false;
  }
  
  if(key_up -> get())
  {
    skins_current_selection--;
    if(skins_current_selection < 0)
      skins_current_selection = 0;
    if(skins_current_selection < skins_list_index_top)
      skins_list_index_top = skins_current_selection;
  }

  if(key_down -> get())
  {
    if((int)skins_current_selection < (int)skins_list.size()-1)
      skins_current_selection++;
    if(skins_current_selection > skins_list_index_top + 2)
      skins_list_index_top++;    
  }

  if(key_enter -> get())
  {
    skin = skins_list[skins_current_selection];
    load_gfx();
  }
}


