/********************************************************************
                          OpenAlchemist

  File : Application.cpp
  Description : implements the begining of the software
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/
#include "memory.h"

#include <ClanLib/core.h>
#include <ClanLib/application.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/sdl.h>

#include "Preferences.h"
#include "GameEngine.h"
#include "CommonResources.h"
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
    CL_DisplayWindow *_p_window;
    /** Used to have a callback event when user close the window */
    CL_Slot _quit_event;
    /** Used to have a callback event when user resize the window */
    CL_Slot _resize_event;
    /** Rendering used - OpenGL or SDL */
    bool _render;

    GameEngine *_p_game;

    /**
     * Initialise the game
     */
    void init()
    {
        CL_SetupCore::init();
        CL_SetupDisplay::init();

        if(RENDER_OPENGL == _render)
        {
            CL_SetupGL::init();
            _p_window = my_new CL_DisplayWindow("OpenAlchemist",800,600, false, false, 2);
            //window -> set_size(800,600);
            CL_System::keep_alive();
        }
        else
        {
            CL_SetupSDL::init();
            _p_window = my_new CL_DisplayWindow("OpenAlchemist",800,600, false, false, 2);
        }

        Preferences *p_pref = pref_get_instance();
        if(p_pref -> fullscreen)
        {
            _p_window -> set_fullscreen(800,600,0,0);
            if(p_pref -> widescreen && RENDER_OPENGL == _render)
            {
                CL_GraphicContext *gc = _p_window -> get_gc();
                gc -> set_scale(0.83, 1.0);
                gc -> add_translate(80, 0, 0);
            }
        }

        // Add a callback when user close the window
        _quit_event = CL_Display::sig_window_close().connect(this, &Application::stop);

				common_resources_init();
        _p_game = my_new GameEngine(_p_window, _render);

        // Add a callback when user resize the window
        //resize_event = window -> sig_resize().connect(game, &GameEngine::resize);
    }

    /**
     * Stop the application
     */
    void stop()
    {
        _p_game -> stop();
    }

    /**
     * Quit the application
     */
    void quit()
    {
        CL_Display::sig_window_close().disconnect(_quit_event);

        _p_game -> deinit();
        my_delete(_p_game);
				common_resources_term();
				my_delete(_p_window);

        if(_render == RENDER_OPENGL)
        {
            CL_SetupGL::deinit();
        }
        else
        {
            CL_SetupSDL::deinit();
        }
			

        CL_SetupDisplay::deinit();
        CL_SetupCore::deinit();

        my_delete(pref_get_instance());
        
    }


    /**
     * Application main function
     */
    virtual int main(int argc, char **argv)
    {
        init_memory();			  	
				{					
		      bool dont_run_game = false;
		      Preferences *_p_pref = pref_get_instance();
		      _render = _p_pref -> render_opengl;

		      // Checking parameters
		      for(int i = 0; i < argc; ++i)
		      {
		          if(strcmp(argv[i], "--sdl")==0 && _render != RENDER_SDL)
		          {
		              _render = RENDER_SDL;
		              _p_pref -> render_opengl = false;
		              _p_pref -> write();

		          }
		          if(strcmp(argv[i], "--opengl")==0 && _render != RENDER_OPENGL)
		          {
		              _render = RENDER_OPENGL;
		              _p_pref -> render_opengl = true;
		              _p_pref -> write();

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
		                  _p_pref -> maxfps = maxfps;
		              }
		              else
		              {
		                  dont_run_game = true;
		                  std::cout << "Option maxfps must be followed by a number." << std::endl;
		              }

		          }
		          if(strcmp(argv[i], "--cb")==0)
		          {
		              _p_pref -> colorblind = true;
		              _p_pref -> write();

		          }
		          if(strcmp(argv[i], "--nocb")==0)
		          {
		              _p_pref -> colorblind = false;
		              _p_pref -> write();

		          }
		          if(strcmp(argv[i], "--wide")==0)
		          {
		              _p_pref -> widescreen = true;
		              _p_pref -> write();
		          }
		          if(strcmp(argv[i], "--nowide")==0)
		          {
		              _p_pref -> widescreen = false;
		              _p_pref -> write();
		          }


		      }

		      if(!dont_run_game)
		      {
		          try
		          {

		              this->init();
		              _p_game->run();
		              this->quit();

		          }
		          // Catch any errors from ClanLib
		          catch (CL_Error err)
		          {
		              // Display the error message
		              std::cout << err.message.c_str() << std::endl;
		          }
		      }
        }				
				term_memory();

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


}
app;
