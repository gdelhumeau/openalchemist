// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : GameEngine.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include "memory.h"
#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "GameEngine.h"
#include "Preferences.h"
#include "CommonResources.h"
#include "misc.h"
#include "LoadingScreen.h"
#include "AudioManager.h"

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
GameEngine::GameEngine():
_window(GAME_WIDTH, GAME_HEIGHT)
{
	_p_loading_screen = NULL;
}

/************************************************************************/
/* Destructor                                                           */
/************************************************************************/
GameEngine::~GameEngine()
{
}

/************************************************************************/
/* Init                                                                 */
/************************************************************************/
void GameEngine::init()
{
	Preferences* p_pref = pref_get_instance();
	switch(p_pref->render_target)
	{
#ifdef WITH_DX_9
	case Preferences::DX_9:
		target_DX9.set_current();
		break;
#endif

	case Preferences::OPENGL_1:
		target_GL1.set_current();
		break;

	case Preferences::SOFTWARE:
		target_GDI.set_current();
		break;

	case Preferences::OPENGL_2:
		target_GL2.set_current();
		break;	
	}

	_running = true;

	CommonResources* p_resources = common_resources_get_instance();	

	p_resources -> init(this);
	_window.manage(*this);
	CL_GraphicContext gc = _window.get_gc();
	_skins_manager.init();
	_common_state.init();
	_ingame_state.init();
	_gameover_state.init();
	_pausemenu_state.init();
	_skinsmenu_state.init();
	_optionsmenu_state.init();
	_title_state.init();
	_quitmenu_state.init();

	set_skin(p_pref -> skin);

	_framerate_counter.set_fps_limit(p_pref -> maxfps);
}

/************************************************************************/
/* Term                                                                 */
/************************************************************************/
void GameEngine::term()
{
	_common_state.term();
	_ingame_state.term();
	_gameover_state.term();
	_pausemenu_state.term();
	_skinsmenu_state.term();
	_optionsmenu_state.term();
	_title_state.term();
	_quitmenu_state.term();
	_skins_manager.term();
}

/************************************************************************/
/* Run                                                                  */
/************************************************************************/
void GameEngine::run()
{
	if (_running)
	{
		set_state_title();

		CommonResources* p_resources = common_resources_get_instance();
		p_resources -> player1.new_game();

		while (_running)
		{
			_window.prepare();

			_common_state.events(_window);
			_common_state.update(_window.get_gc());
			_common_state.draw(_window.get_gc());

			GameState* p_current_state = _states_stack.top();
			p_current_state -> events(_window);
			p_current_state -> update(_window.get_gc());

			// Drawing the front layer behind the current state or not
			if (p_current_state -> front_layer_behind())
			{
				p_resources -> front_layer.draw(_window.get_gc());
				p_current_state -> draw(_window.get_gc());
			}
			else
			{
				p_current_state -> draw(_window.get_gc());
				p_resources -> front_layer.draw(_window.get_gc());
			}

			// Get the Frame rate
			p_resources -> fps = _framerate_counter.get_fps();
			p_resources -> delta_time = get_time_interval(p_resources->fps);

			_window.display();
			_framerate_counter.keep_alive();        
		}
	}
}

/************************************************************************/
/* Stop                                                                 */
/************************************************************************/
void GameEngine::stop()
{
	_running = false;
}

/************************************************************************/
/* State state title                                                    */
/************************************************************************/
void GameEngine::set_state_title()
{
	while (!_states_stack.empty())
	{
		_states_stack.pop();
	}
	_states_stack.push(&_title_state);
	_title_state.start();
}

/************************************************************************/
/* Set state new game menu                                              */
/************************************************************************/
void GameEngine::set_state_new_game_menu()
{}

/************************************************************************/
/* Set state pause menu                                                 */
/************************************************************************/
void GameEngine::set_state_pause_menu()
{
	if (_states_stack.top() != &_pausemenu_state)
	{
		_states_stack.push(&_pausemenu_state);
		_pausemenu_state.start();
		g_audio_manager.pause_sounds();
	}
}

/************************************************************************/
/* Set state ingame                                                     */
/************************************************************************/
void GameEngine::set_state_ingame()
{
	CommonResources* p_common_resources = common_resources_get_instance();
	p_common_resources -> p_current_player = &(p_common_resources -> player1);
	_states_stack.push(&_ingame_state);
	g_audio_manager.resume_sounds();
}

/************************************************************************/
/* Set state gameover                                                   */
/************************************************************************/
void GameEngine::set_state_gameover(bool is_highscore)
{
	_gameover_state.set_highscore(is_highscore);
	_gameover_state.start();
	_states_stack.push(&_gameover_state);
}

/************************************************************************/
/* Set states options menu                                              */
/************************************************************************/
void GameEngine::set_state_options_menu()
{
	if (_states_stack.top() != &_optionsmenu_state)
	{
		_states_stack.push(&_optionsmenu_state);
		_optionsmenu_state.start();
		_pausemenu_state.start();
	}
}

/************************************************************************/
/* Set state skin menu                                                  */
/************************************************************************/
void GameEngine::set_state_skin_menu()
{
	if (_states_stack.top() != &_skinsmenu_state)
	{
		_states_stack.push(&_skinsmenu_state);
		_skinsmenu_state.start();
		_pausemenu_state.start();
		_optionsmenu_state.start();
	}
}

/************************************************************************/
/* Set state quit menu                                                  */
/************************************************************************/
void GameEngine::set_state_quit_menu(QuitMenuAction action)
{
	if (_states_stack.top() != &_quitmenu_state)
	{
		_quitmenu_state.set_action(action);
		_states_stack.push(&_quitmenu_state);
		_pausemenu_state.start();
		_quitmenu_state.start();
	}
}

/************************************************************************/
/* Stop current state                                                   */
/************************************************************************/
void GameEngine::stop_current_state()
{
	_states_stack.pop();
	if (_states_stack.top() == &_ingame_state)
	{
		g_audio_manager.resume_sounds();
	}
}

/************************************************************************/
/* Toggle screen                                                        */
/************************************************************************/
void GameEngine::toggle_screen()
{
	Preferences* p_pref = pref_get_instance();
	p_pref -> fullscreen = !p_pref -> fullscreen;
	_window.manage(*this);
	_optionsmenu_state.toggle_screen();
	p_pref->write();

}

/************************************************************************/
/* Toggle Color Blind                                                   */
/************************************************************************/
void GameEngine::toggle_colorblind()
{
	// Getting globals
	Preferences* p_pref = pref_get_instance();
	CommonResources* p_common_resources = common_resources_get_instance();
	
	// Changing preferences
	p_pref -> colorblind = !p_pref -> colorblind;

	// Loading new elements (with a loading screen)
	_p_loading_screen = my_new LoadingScreen(_window);
	_p_loading_screen -> init();
	_p_loading_screen -> set_progression(0.0f);
	if(_running)
	{
		p_common_resources->player1.load_gfx(_window.get_gc(), p_pref -> skin);
		_p_loading_screen -> set_progression(1.0f / 2.0f);
	}
	if(_running)
	{
		_title_state.load_gfx(_window.get_gc(), p_pref -> skin);
		_p_loading_screen -> set_progression(2.0f / 2.0f);
	}

	// Delete loading screen
	my_delete(_p_loading_screen);
	_p_loading_screen = NULL;

	// Save preferences
	p_pref->write();
}

/************************************************************************/
/* Refresh framerate limit                                              */
/************************************************************************/
void GameEngine::refresh_framerate_limit()
{
	Preferences* p_pref = pref_get_instance();
	_framerate_counter.set_fps_limit(p_pref -> maxfps);
	p_pref->write();
}

/************************************************************************/
/* Get FPS                                                              */
/************************************************************************/
int GameEngine::get_fps()
{
	return _framerate_counter.get_fps();
}

/************************************************************************/
/* Set skib                                                             */
/************************************************************************/
void GameEngine::set_skin(std::string skin)
{
	CommonResources* p_resources = common_resources_get_instance();

	_p_loading_screen = my_new LoadingScreen(_window);
	_p_loading_screen -> init();
	_p_loading_screen -> set_progression(0.0f);

	Preferences* p_pref = pref_get_instance();

	std::string old_skin = p_pref -> skin;

	CL_GraphicContext& gc = _window.get_gc();
	try
	{
		p_pref -> skin = skin;

		if (!_running) 
			return;
		{
			p_resources -> load_gfx(gc, p_pref -> skin);
			_p_loading_screen -> set_progression(1.0f / 10.0f);
		}

		if (!_running) 
			return;
		{
			_title_state.load_gfx(gc, p_pref -> skin);
			_p_loading_screen -> set_progression(2.0f / 10.0f);
		}

		if (!_running) 
			return;
		{
			_common_state.load_gfx(gc, p_pref -> skin);
			_p_loading_screen -> set_progression(3.0f / 10.0f);
		}

		if (!_running) 
			return;
		{
			_ingame_state.load_gfx(gc, p_pref -> skin);
			_p_loading_screen -> set_progression(4.0f / 10.0f);
		}

		if (!_running) 
			return;
		{
			_gameover_state.load_gfx(gc, p_pref -> skin);
			_p_loading_screen -> set_progression(5.0f / 10.0f);
		}

		if (!_running) 
			return;
		{
			_pausemenu_state.load_gfx(gc, p_pref -> skin);
			_p_loading_screen -> set_progression(6.0f / 10.0f);
		}

		if (!_running) 
			return;
		{
			_skinsmenu_state.load_gfx(gc, p_pref -> skin);
			_p_loading_screen -> set_progression(7.0f / 10.0f);
		}

		if (!_running) 
			return;
		{
			_optionsmenu_state.load_gfx(gc, p_pref -> skin);
			_p_loading_screen -> set_progression(8.0f / 10.0f);
		}

		if (!_running) 
			return;
		{
			_title_state.load_gfx(gc, p_pref -> skin);
			_p_loading_screen -> set_progression(9.0f / 10.0f);
		}

		if (!_running) 
			return;
		{
			_quitmenu_state.load_gfx(gc, p_pref -> skin);
			_p_loading_screen -> set_progression(10.0f / 10.0f);
		}

		p_pref -> write();

	}
	catch (CL_Exception& err)
	{
		CL_ConsoleWindow console("OpenAlchemist Console", 80, 300);
			
		CL_Console::write_line("Skin error : " + err.message);
		CL_Console::write_line("Error in : " + skin);
		if (old_skin.compare(skin))
		{
			CL_Console::write_line("");
			CL_Console::write_line("Now loading default skin.");
			skin = get_skins_path() + get_path_separator() + "aqua.zip";
			CL_Console::write_line(skin);
			console.display_close_message();
			set_skin(skin);
		}
		else
		{
			throw err;
		}
	}

	my_delete(_p_loading_screen);
	_p_loading_screen = NULL;
}

/************************************************************************/
/* Set skin element                                                     */
/************************************************************************/
void GameEngine::set_skin_element(unsigned int element)
{
	_skins_manager.set_skin_elements(element);
}