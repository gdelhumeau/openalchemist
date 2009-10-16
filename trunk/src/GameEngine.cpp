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
	Preferences *pref = pref_get_instance();
	switch(pref->render_target)
	{
#ifdef WITH_DX_9
	case Preferences::DX_9:
		target_DX9.set_current();
		break;
#endif

	case Preferences::OPENGL_1:
		target_GL1.set_current();
		break;

	case Preferences::GDI:
		target_GDI.set_current();
		break;

	case Preferences::OPENGL_2:
		target_GL2.set_current();
		break;	
	}

	_running = true;

	CommonResources *resources = common_resources_get_instance();	

	resources -> init(this);
	_window.manage(*this);
	CL_GraphicContext gc = _window.get_gc();
	_common_state.init();
	_ingame_state.init();
	_gameover_state.init();
	_pausemenu_state.init();
	_skinsmenu_state.init();
	_optionsmenu_state.init();
	_title_state.init();
	_quitmenu_state.init();

	set_skin(pref -> skin);

	_framerate_counter.set_fps_limit(pref -> maxfps);
}

/************************************************************************/
/* Term                                                                 */
/************************************************************************/
void GameEngine::term()
{
	_common_state.deinit();
	_ingame_state.deinit();
	_gameover_state.deinit();
	_pausemenu_state.deinit();
	_skinsmenu_state.deinit();
	_optionsmenu_state.deinit();
	_title_state.deinit();
	_quitmenu_state.deinit();
}

/************************************************************************/
/* Run                                                                  */
/************************************************************************/
void GameEngine::run()
{
	if (_running)
	{
		set_state_title();

		CommonResources *resources = common_resources_get_instance();
		resources -> player1.new_game();

		while (_running)
		{
			_window.prepare();

			_common_state.events(_window);
			_common_state.update(_window.get_gc());
			_common_state.draw(_window.get_gc());

			GameState* current_state = _states_stack.top();
			current_state -> events(_window);
			current_state -> update(_window.get_gc());

			// Drawing the front layer behind the current state or not
			if (current_state -> front_layer_behind())
			{
				resources -> front_layer.draw(_window.get_gc());
				current_state -> draw(_window.get_gc());
			}
			else
			{
				current_state -> draw(_window.get_gc());
				resources -> front_layer.draw(_window.get_gc());
			}

			// Get the Frame rate
			resources -> fps = _framerate_counter.get_fps();
			resources -> delta_time = get_time_interval(resources->fps);

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
		g_audio_manager.pause_fx();
	}
}

/************************************************************************/
/* Set state ingame                                                     */
/************************************************************************/
void GameEngine::set_state_ingame()
{
	CommonResources *common_resources = common_resources_get_instance();
	common_resources -> p_current_player = &(common_resources -> player1);
	_states_stack.push(&_ingame_state);
	g_audio_manager.unpause_fx();
}

/************************************************************************/
/* Set state gameover                                                   */
/************************************************************************/
void GameEngine::set_state_gameover(int mode)
{
	_gameover_state.set_mode(mode);
	_gameover_state.start();
	_states_stack.push(&_gameover_state);
}

/*void GameEngine::set_state_highscore()
{
states_stack.push(&highscore_state);
}*/

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
		g_audio_manager.unpause_fx();
	}
}

/************************************************************************/
/* Toggle screen                                                        */
/************************************************************************/
void GameEngine::toggle_screen()
{
	Preferences *pref = pref_get_instance();
	pref -> fullscreen = !pref -> fullscreen;
	_window.manage(*this);
	_optionsmenu_state.toggle_screen();

}

/************************************************************************/
/* Refresh framerate limit                                              */
/************************************************************************/
void GameEngine::refresh_framerate_limit()
{
	Preferences *pref = pref_get_instance();
	_framerate_counter.set_fps_limit(pref -> maxfps);
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
	CommonResources *resources = common_resources_get_instance();

	_p_loading_screen = my_new LoadingScreen(_window);
	_p_loading_screen -> init();
	_p_loading_screen -> set_progression(0.0f);

	Preferences *pref = pref_get_instance();

	std::string old_skin = pref -> skin;

	CL_GraphicContext gc = _window.get_gc();
	try
	{
		pref -> skin = skin;

		if (_running)
		{
			resources -> load_gfx(gc, pref -> skin);
			_p_loading_screen -> set_progression(2.0f / 12.0f);
		}

		if (_running)
		{
			_title_state.load_gfx(gc, pref -> skin);
			_p_loading_screen -> set_progression(3.0f / 12.0f);
		}

		if (_running)
		{
			_common_state.load_gfx(gc, pref -> skin);
			_p_loading_screen -> set_progression(4.0f / 12.0f);
		}

		if (_running)
		{
			_ingame_state.load_gfx(gc, pref -> skin);
			_p_loading_screen -> set_progression(5.0f / 12.0f);
		}

		if (_running)
		{
			_gameover_state.load_gfx(gc, pref -> skin);
			_p_loading_screen -> set_progression(6.0f / 12.0f);
		}

		if (_running)
		{
			_pausemenu_state.load_gfx(gc, pref -> skin);
			_p_loading_screen -> set_progression(7.0f / 12.0f);
		}

		if (_running)
		{
			_skinsmenu_state.load_gfx(gc, pref -> skin);
			_p_loading_screen -> set_progression(8.0f / 12.0f);
		}

		if (_running)
		{
			_optionsmenu_state.load_gfx(gc, pref -> skin);
			_p_loading_screen -> set_progression(9.0f / 12.0f);
		}

		if (_running)
		{
			_optionsmenu_state.load_gfx(gc, pref -> skin);
			_p_loading_screen -> set_progression(10.0f / 12.0f);
		}

		if (_running)
		{
			_title_state.load_gfx(gc, pref -> skin);
			_p_loading_screen -> set_progression(11.0f / 12.0f);
		}

		if (_running)
		{
			_quitmenu_state.load_gfx(gc, pref -> skin);
			_p_loading_screen -> set_progression(12.0f / 12.0f);
		}

		pref -> write();

	}
	catch (CL_Exception & err)
	{
		std::cout << "Skin error : " << err.message.c_str() << std::endl;
		std::cout << "Error in : " << skin << std::endl;
		if (old_skin.compare(skin))
		{
			std::cout << "Now loading default skin." << std::endl;
			skin = get_skins_path() + get_path_separator() + "aqua.zip";
			std::cout << skin << std::endl;
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
	_skinsmenu_state.set_skin_elements(element);
}
