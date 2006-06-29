/* OpenAlchemist - just a simple game 
 * ----------------------------------
 *
 * Copyright (C) 2005 Guillaume Delhumeau <guillaume.delhumeau at laposte.net>
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

#include <ClanLib/gl.h>
#include <ClanLib/sdl.h>
#include <ClanLib/core.h>
#include <ClanLib/application.h>

#include "headers.h"

#define RENDER_SDL 0
#define RENDER_OPENGL 1

#define OPTIONS_FILE_REVISION 1

/** ! Windows user ! Uncomment this to compile for windows: */

//#define _WINDOWS_

/**
 * Main application
 */
class Application : public CL_ClanApplication
{
public:

  CL_DisplayWindow *window;
  CL_Slot quit_event;
  short render;  

  Game *game;

  /**
   * Initialise the game
   */
  void init()
    {
      CL_SetupCore::init();
      CL_SetupDisplay::init();
      
      if(RENDER_OPENGL == render)
      {
        CL_SetupGL::init();
      }
      else
      {
        CL_SetupSDL::init();
      }

      window = new CL_DisplayWindow("OpenAlchemist",800,600);

      quit_event = CL_Display::sig_window_close().connect(this, &Application::stop);

      game = new Game(window);
  
    }

  /**
   * Stop the application
   */
  void stop()
    {
      game -> stop();
    }

  /**
   * Quit the application
   */
  void quit()
    {
      CL_Display::sig_window_close().disconnect(quit_event);

      delete game;
      
      delete window;

      if(render == RENDER_OPENGL)
      {
        CL_SetupGL::deinit();
      }
      else
      {
        CL_SetupSDL::deinit();
      }
     
      CL_SetupDisplay::deinit();
      CL_SetupCore::deinit();

      exit(0);
    }

 
  /**
   * Application main function
   */
  virtual int main(int argc, char **argv)
    {
              
      bool dont_run_game = false;

     
      get_informations_from_options_file();
      

      render = RENDER_SDL;
      for(int i = 0; i < argc; ++i)
      {
        if(strcmp(argv[i], "--sdl")==0)
        {
          render = RENDER_SDL;
        }
        if(strcmp(argv[i], "--opengl")==0)
        {
          render = RENDER_OPENGL;
        }
        if(strcmp(argv[i], "--help")==0)
        {
          help();
          dont_run_game = true;
        }
        if(strcmp(argv[i], "--license")==0)
        {
          license();
          dont_run_game = true;
        }
        
        
      }

      if(!dont_run_game)
      {
        try
        {
      
          this->init();
          game->main_loop();
          this->quit();
               
        }
        // Catch any errors from ClanLib
        catch (CL_Error err)
        {
          // Display the error message
          std::cout << err.message.c_str() << std::endl;
        }
      }


      
      return 0;
    }

  /**
   * Display the help informations
   */
  void help()
    {
      std::cout << "OpenAlchemist v0.xxx -- Help\n"
                << "Usage: openalchemist [OPTIONS]\n\n"
                << "Options:\n"
                << "\t--help : Show this message\n"
                << "\t--license : Show the license of this program\n"
                << "\t--opengl : Use OpenGL as render target\n"
                << "\t--sdl : Use SDL as render target (default)\n"
                     ;
    }

  /**
   * Display the license
   */
  void license()
    {
      std::cout << " * OpenAlchemist v0.xxx -- License\n"
                << " * Copyright (C) 2006 Guillaume Delhumeau <guillaume.delhumeau at laposte.net>\n\n"
                << " *\n" 
                << " * This program is free software; you can redistribute it and/or modify \n"
                << " * it under the terms of the GNU General Public License as published by\n"
                << " * the Free Software Foundation; either version 2 of the License, or\n"
                << " * (at your option) any later version.\n"
                << " *\n"
                << " * This program is distributed in the hope that it will be useful,\n"
                << " * but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
                << " * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
                << " * GNU General Public License for more details.\n"
                << " *\n"
                << " * You should have received a copy of the GNU General Public License\n"
                << " * along with this program; if not, write to the Free Software\n"
                << " * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.\n *\n\n";
    }



  void get_informations_from_options_file()
    {
      std::string options_path = get_save_path();
      std::string options_file = options_path + "/options";

      try
      {
        CL_InputSource_File file(options_file);
        read_options_file(&file);
      }
      catch(CL_Error e)
      {
        // File doesn't exist
        try
          {
            CL_OutputSource_File file(options_file);
            create_options_file(&file);
          }
        catch(CL_Error e)
        {
          // Directory may doesn't exist
          if(!CL_Directory::change_to(options_path))
          {
            if(CL_Directory::create(options_path))
            {
              // Now we can create the file
              try
              {
                 CL_OutputSource_File file(options_file);
                 create_options_file(&file);
              }
              catch(CL_Error e)
              {
                std::cout << "Can't create " << options_file <<".\n";
              }
              
            }
            else
            {
              std::cout << "Can't access to " << options_path << ".\n";
            }
          }
          else
          {
            std::cout << "Can't access to " << options_file <<".\n";
          }
          
        }

      }
    }

  void read_options_file(CL_InputSource_File *file)
    {
      file->open();
      int revision = file -> read_uint8();
      if(revision == 1)
      {
      }
      bool use_opengl = file  -> read_bool8();
      if(use_opengl)
      {
        render = RENDER_OPENGL;
      }
      else
      {
        render = RENDER_SDL;
      }
      file -> close();
    }

  void create_options_file(CL_OutputSource_File *file)
    {
      file -> open();
      // File revision
      file -> write_uint8(OPTIONS_FILE_REVISION);
      // Use OpenGL
      file -> write_bool8(false);
      
      file -> close();
    }
 


} app;
