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

#include "piece.h"
#include "game.h"

#define RENDER_SDL 0
#define RENDER_OPENGL 1


class Application : public CL_ClanApplication
{
public:

  CL_DisplayWindow *window;
  CL_Slot quit_event;
  short render;

  Game *game;

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

      quit_event = CL_Display::sig_window_close().connect(this, &Application::quit);

      game = new Game(window);
  
    }

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

 
  virtual int main(int argc, char **argv)
    {
      // Create a console window for text-output if not available
      // Use printf or cout to display some text in your program

      CL_ConsoleWindow console("Console");
      console.redirect_stdio();

      bool dont_run_game = false;

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


      // Display console close message and wait for a key
      console.display_close_message();

      return 0;
    }

  void help()
    {
      std::cout << "OpenAlchemist v0.xxx -- Help\n"
                << "Usage: openalchemist [OPTIONS]\n\n"
                << "Options:\n"
                << "\t--help : Show this message\n"
                << "\t--opengl : Use OpenGL as render target\n"
                << "\t--sdl : Use SDL as render target (default)\n"
                     ;
    }


} app;
