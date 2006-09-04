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

void SkinsSelector::read_file()
{

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

void SkinsSelector::set_skin_value(std::string skin, int value)
{
  bool is_setted = false;
  for(u_int i=0; i<propreties_list.size(); ++i)
  {
    if(propreties_list[i]->filename == skin && (int)propreties_list[i]->element < value)
    {
      propreties_list[i]->element = value;
      is_setted = true;
    }
  }

  if(!is_setted)
  {
    SkinsPropreties *sp = new SkinsPropreties();
    sp -> filename = skin;
    sp -> element = value;
    propreties_list.insert(propreties_list.end(), sp);
  }
}

void SkinsSelector::write_file()
{
  std::string path = get_save_path();
#ifdef WIN32
  std::string file_path = path + "\\skins";
#else
  std::string file_path = path + "/skins";
#endif

  try
  {
    CL_OutputSource_File file(file_path);
    std::vector<SkinsPropreties*>::iterator it = propreties_list.begin();
    while(!propreties_list.empty())
    {
      SkinsPropreties *sp = (SkinsPropreties*)*it;
      file.write_string(sp->filename);
      file.write_uint8(sp->element);
      delete sp;
      it = propreties_list.erase(it);
    }
    file.close();
        
  }
  catch(CL_Error e)
  {
    std::cout << "Error reading " << file_path << "file, probably doesn't exist yet." << std::endl;
  }
}


void SkinsSelector::load_gfx(CL_ResourceManager *gfx)
{
  menu = new CL_Sprite("skins-selector/cursor", gfx);
  top = CL_Integer_to_int("skins-selector/top", gfx);
  separation = CL_Integer_to_int("skins-selector/separation", gfx);
  cant_change_skin = new CL_Sprite("skins-selector/cant_change", gfx);
}

void SkinsSelector::unload_gfx()
{
  delete menu;
}



/**
 * This method runs the skin-selector
 */
void Game::choose_skin()
{

  pause.step = PAUSE_STEP_SKINS;

  skins_selector.list.clear();
  skins_selector.logo_list.clear();

  skins_selector.current_selection = 0;
  skins_selector.list_index_top = 0;

#ifdef WIN32
  std::string dir = CL_System::get_exe_path() + "skins\\";
#else
  std::string dir = CL_System::get_exe_path() + "skins/";
#endif

  skins_selector.number = 0;
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
            skins_selector.logo_list.insert(skins_selector.logo_list.end(), logo);
            skins_selector.list.insert(skins_selector.list.end(), dir+scanner.get_name());
            
            if(skin == dir+scanner.get_name())
            {
              skins_selector.current_selection = skins_selector.number;
              skins_selector.list_index_top = skins_selector.number - 1;

              if(skins_selector.list_index_top < 0)
              {               
                skins_selector.list_index_top = 0;
              }
            }         
            skins_selector.number++;
          }
        catch(CL_Error e)
          {
            std::cout << "Skin " << dir << scanner.get_name() << " is not valid \n"; 
          }
      }        
       
    }
  }
  
}

void Game::draw_skins_selector()
{

  int y = 300 - pause.background -> get_height()/2; 

  for(u_int i=0; i<skins_selector.list.size() && i<2; ++i)
  {
    if((int)i+(int)skins_selector.list_index_top == (int)skins_selector.current_selection)
      skins_selector.menu -> draw(240, y+skins_selector.top-10+i*(150+skins_selector.separation));

    skins_selector.logo_list[i+skins_selector.list_index_top] -> 
      draw(250, y+skins_selector.top+i*(150+skins_selector.separation));
  }

  if(skins_selector.display_cant_change)
  {
     if(key.enter -> get())
       skins_selector.display_cant_change = false;

     int x = 400 - skins_selector.cant_change_skin -> get_width()/2;
     int y = 300 - skins_selector.cant_change_skin -> get_height()/2;
     skins_selector.cant_change_skin -> draw(x,y);

   }
 }

 void Game::key_events_skins_selector()
 {
   if(key.echap->get())
   {   
     if(pause.requested)
       pause.step = PAUSE_STEP_MENU;    
     else
       pause.is_paused = false;
   }

   if(key.up -> get())
   {
     skins_selector.current_selection--;
     if(skins_selector.current_selection < 0)
       skins_selector.current_selection = 0;
     if(skins_selector.current_selection < skins_selector.list_index_top)
       skins_selector.list_index_top = skins_selector.current_selection;
   }

   if(key.down -> get())
   {
     if((int)skins_selector.current_selection < (int)skins_selector.list.size()-1)
       skins_selector.current_selection++;
     if(skins_selector.current_selection > skins_selector.list_index_top + 1)
       skins_selector.list_index_top++;    
   }

   if(key.enter -> get())
   {
     std::string requested_skin = skins_selector.list[skins_selector.current_selection];

     /* We llook if last element is unlocked with the requested skin */
     bool skin_enabled = false;
     if(visible_pieces > 3)
     {
       for(u_int i=0; i<skins_selector.propreties_list.size(); ++i)
       {
         if(skins_selector.propreties_list[i]->filename == requested_skin && 
            (int)skins_selector.propreties_list[i]->element >= visible_pieces )
           skin_enabled = true;

       }
     }
     else
     {
       skin_enabled = true;
     }

     if(skin_enabled)
     {
       skin = requested_skin;
       Preferences* pref = pref_get_instance();
       pref -> skin = skin;
       save_preferences();
       load_gfx();
     }
     else
     {
       skins_selector.display_cant_change = true;
     }
  }
}


