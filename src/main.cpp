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

#include "headers.h"

#define RENDER_SDL false
#define RENDER_OPENGL true

/**
 * Main application
 */
class Application : public CL_ClanApplication
{
public:

  CL_DisplayWindow *window;
  CL_Slot quit_event;
  bool render;  

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

      Preferences *pref = pref_get_instance();
      if(pref -> fullscreen)
        window -> set_fullscreen(800,600,0,0);

      quit_event = CL_Display::sig_window_close().connect(this, &Application::stop);

      game = new Game(window, render);
  
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

      delete pref_get_instance();

      exit(0);
    }

 
  /**
   * Application main function
   */
  virtual int main(int argc, char **argv)
    {
              
      bool dont_run_game = false;

      render = RENDER_SDL;
      get_informations_from_options_file();      

      
      for(int i = 0; i < argc; ++i)
      {
        if(strcmp(argv[i], "--sdl")==0 && render != RENDER_SDL)
        {
          render = RENDER_SDL;
          Preferences *pref = pref_get_instance();
          pref -> render_opengl = false;
          pref -> write();
         
        }
        if(strcmp(argv[i], "--opengl")==0 && render != RENDER_OPENGL)
        {
          render = RENDER_OPENGL;
          Preferences *pref = pref_get_instance();
          pref -> render_opengl = true;
          pref -> write();
          
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
      std::cout << "OpenAlchemist vSVN -- Help" << std::endl
                << "Usage: openalchemist [OPTIONS]"  << std::endl  << std::endl
                << "Options:"  << std::endl
                << "\t--help : Show this message"  << std::endl
                << "\t--license : Show the license of this program"  << std::endl
                << "\t--opengl : Use OpenGL as render target" << std::endl
                << "\t--sdl : Use SDL as render target (default)" << std::endl
        ;
    }

  /**
   * Display the license
   */
  void license()
    {
      std::cout << " * OpenAlchemist v0.xxx -- License\n" << std::endl
                << " * Copyright (C) 2006 Guillaume Delhumeau <guillaume.delhumeau at laposte.net>" << std::endl 
                << " *"  << std::endl
                << " * This program is free software; you can redistribute it and/or modify " << std::endl
                << " * it under the terms of the GNU General Public License as published by" << std::endl
                << " * the Free Software Foundation; either version 2 of the License, or" << std::endl
                << " * (at your option) any later version." << std::endl
                << " *" << std::endl
                << " * This program is distributed in the hope that it will be useful," << std::endl
                << " * but WITHOUT ANY WARRANTY; without even the implied warranty of" << std::endl
                << " * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the" << std::endl
                << " * GNU General Public License for more details." << std::endl
                << " *" << std::endl
                << " * You should have received a copy of the GNU General Public License" << std::endl
                << " * along with this program; if not, write to the Free Software" << std::endl
                << " * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA." <<std::endl
                << " *" << std::endl << std::endl;
    }



  void get_informations_from_options_file()
    {
      Preferences *pref = pref_get_instance();
      render = pref -> render_opengl;
    }

} app;
