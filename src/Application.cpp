/********************************************************************
                          OpenAlchemist

  File : Application.cpp
  Description : implements the begining of the software
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include <ClanLib/core.h>
#include <ClanLib/application.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/sdl.h>

#include "Preferences.h"
#include "GameEngine.h"
#include "misc.h"

#define RENDER_SDL false
#define RENDER_OPENGL true

/**
 * Main application
 */
class Application : public CL_ClanApplication
{
public:

  /** Main Window */
  CL_DisplayWindow *window;
  /** Used to have a callback event when user close the window */
  CL_Slot quit_event;
  /** Rendering used - OpenGL or SDL */
  bool render;  

  GameEngine *game;

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

      window = new CL_DisplayWindow("OpenAlchemist",640,480, false, true, 2);
			
		
				CL_GraphicContext *gc = window -> get_gc();
				gc -> set_scale(0.8, 0.8);
			
      
			Preferences *pref = pref_get_instance();
			if(pref -> fullscreen)
			{
				window -> set_fullscreen(800,600,0,0);
				if(pref -> widescreen && RENDER_OPENGL == render)
				{
					CL_GraphicContext *gc = window -> get_gc();
					gc -> set_scale(0.83, 1.0);
					gc -> add_translate(80, 0, 0);					
				}
			}
			
      // Add a callback when user close the window
      quit_event = CL_Display::sig_window_close().connect(this, &Application::stop);

      game = new GameEngine(window, render);
      game -> init();
  
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
      Preferences *pref = pref_get_instance();
      render = pref -> render_opengl;

      // Checking parameters
      for(int i = 0; i < argc; ++i)
      {
        if(strcmp(argv[i], "--sdl")==0 && render != RENDER_SDL)
        {
          render = RENDER_SDL;
          pref -> render_opengl = false;
          pref -> write();
         
        }
        if(strcmp(argv[i], "--opengl")==0 && render != RENDER_OPENGL)
        {
          render = RENDER_OPENGL;
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
        if(strcmp(argv[i], "--maxfps")==0 && i < argc-1)
        {
          std::string arg(argv[i+1]); 
          int maxfps;
          std::istringstream istr(arg); 

          if(istr>>maxfps)
          {
            pref -> maxfps = maxfps;
          }
          else
          {
            dont_run_game = true;
            std::cout << "Option maxfps must be followed by a number." << std::endl;
          }
          
        }
        if(strcmp(argv[i], "--cb")==0)
        {
          pref -> colorblind = true;
          pref -> write();
         
        }
        if(strcmp(argv[i], "--nocb")==0)
        {
          pref -> colorblind = false;
          pref -> write();
         
        }
				if(strcmp(argv[i], "--wide")==0)
        {
          pref -> widescreen = true;
          pref -> write();         
        }
				if(strcmp(argv[i], "--nowide")==0)
        {
          pref -> widescreen = false;
          pref -> write();         
        }
        
        
      }

      if(!dont_run_game)
      {
        try
        {
      
          this->init();
          game->run();
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
      std::cout << "OpenAlchemist " << get_version() << " -- Help" << std::endl
                << "Usage: openalchemist [OPTIONS]"  << std::endl  << std::endl
                << "Options:"  << std::endl
                << "\t--cb       : Active colorblind mode"  << std::endl
                << "\t--help     : Show this message"  << std::endl
                << "\t--license  : Show the license of this program"  << std::endl
                << "\t--maxfps X : Limit framerate to X"  << std::endl   
                << "\t--nocb     : Disable colorblind mode"  << std::endl
								<< "\t--nowide   : Disable 16:9 wide screen mode"  << std::endl
                << "\t--opengl   : Use OpenGL as render target (default)" << std::endl
                << "\t--sdl      : Use SDL as render target" << std::endl
                << "\t--wide     : Special mode for 16:9 wide screen (only supported with OpenGL)" << std::endl
        ;
    }

  /**
   * Display the license
   */
  void license()
    {
      std::cout << " * OpenAlchemist "<< get_version() << " -- License\n" << std::endl
                << " * Copyright (C) 2006,2009 Guillaume Delhumeau <guillaume.delhumeau at gmail.com>" << std::endl 
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

} app;
