/********************************************************************
                            OpenAlchemist

  File : GameEngine.cpp
  Description :
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include "memory.h"
#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "GameEngine.h"
#include "Preferences.h"
#include "CommonResources.h"
#include "misc.h"
#include "LoadingScreen.h"
#include "AudioManager.h"

GameEngine::GameEngine()
{
    _p_loading_screen = NULL;
}

GameEngine::~GameEngine()
{}

void GameEngine::init()
{
    _running = true;
		set_window();
		CL_GraphicContext gc = _main_window.get_gc();

    CommonResources *resources = common_resources_get_instance();
    Preferences *pref = pref_get_instance();

    _fps_getter.set_fps_limit(pref -> maxfps);
    change_screen_size();

    resources -> init(this);
    _common_state.init();
    _ingame_state.init();
    _gameover_state.init();
    _pausemenu_state.init();
    _skinsmenu_state.init(gc);
    _optionsmenu_state.init();
    _title_state.init();
    _quitmenu_state.init();

    set_skin(pref -> skin);
}

void GameEngine::set_window()
{
	// Save the old main_window (if valid), so graphics are not lost when screen mode is changed.
	// It is destroyed as "previous_window" does out of scope
	CL_DisplayWindow previous_window = _main_window;	

	CL_DisplayWindowDescription desc;
	desc.set_title("OpenAlchemist");
	desc.set_size(CL_Size(800,600), true);
     	Preferences *p_pref = pref_get_instance();
	if(p_pref -> fullscreen)
	{
		desc.set_fullscreen(true);
		desc.set_decorations(false);
	}
	else
	{
		desc.set_allow_resize(true);
	}
	_main_window = CL_DisplayWindow(desc);
	if(p_pref -> fullscreen)
	{
		_main_window.hide_cursor();
	}
	else
	{
		_main_window.show_cursor();
	}

	CommonResources * p_common_resources = common_resources_get_instance();
	p_common_resources -> p_window = &_main_window;
	p_common_resources -> p_gc = &_main_window.get_gc();
      
  // Add a callback when user close the window
  _quit_event = _main_window.sig_window_close().connect(this, &GameEngine::stop);

}

void GameEngine::deinit()
{
    _common_state.deinit();
    _ingame_state.deinit();
    _gameover_state.deinit();
    _pausemenu_state.deinit();
    _skinsmenu_state.deinit();
    _optionsmenu_state.deinit();
    _title_state.deinit();
    _quitmenu_state.deinit();

    g_audio_manager.term();
}

void GameEngine::run()
{
    //Preferences *p_pref = pref_get_instance();

    if (_running)
    {
        set_state_title();

        CommonResources *resources = common_resources_get_instance();
        resources -> player1.new_game();

        while (_running)
        {
						CL_GraphicContext gc = _main_window.get_gc();
						// Stretch the game to the window
						CL_Mat4f matrix = CL_Mat4f::scale( (float) gc.get_width() / 800.0f,
						                                  (float) gc.get_height() / 600.0f,
						                                  1.0f);
						gc.set_modelview(matrix);
					
            _common_state.events(_main_window);
            _common_state.update(gc);
            _common_state.draw(gc);

            GameState* current_state = _states_stack.top();
            current_state -> events(_main_window);
            current_state -> update(gc);

            // Drawing the front layer behind the current state or not
            if (current_state -> front_layer_behind())
            {
                resources -> front_layer.draw(gc);
                current_state -> draw(gc);
            }
            else
            {
                current_state -> draw(gc);
                resources -> front_layer.draw(gc);
            }


            // Get the Framerate
            resources -> fps = _fps_getter.get_fps();
            resources -> time_interval = get_time_interval(resources->fps);

            _main_window.flip(0);

						// This call updates input and performs other "housekeeping"
						// Call this each frame
						CL_KeepAlive::process();
						_fps_getter.keep_alive();

            /*if (_render_mode == RENDER_OPENGL && !p_pref -> fullscreen)
            {
                change_screen_size();
            } */          
        }
    }
}

void GameEngine::stop()
{
    _running = false;
}

void GameEngine::set_state_title()
{
    while (!_states_stack.empty())
    {
        _states_stack.pop();
    }
    _states_stack.push(&_title_state);
    _title_state.start();
}

void GameEngine::set_state_new_game_menu()
{}

void GameEngine::set_state_pause_menu()
{
    if (_states_stack.top() != &_pausemenu_state)
    {
        _states_stack.push(&_pausemenu_state);
        _pausemenu_state.start();
        g_audio_manager.pause_fx();
    }
}

void GameEngine::set_state_ingame()
{
    CommonResources *common_resources = common_resources_get_instance();
    common_resources -> p_current_player = &(common_resources -> player1);
    _states_stack.push(&_ingame_state);
    g_audio_manager.unpause_fx();
}

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


void GameEngine::set_state_options_menu()
{
    if (_states_stack.top() != &_optionsmenu_state)
    {
        _states_stack.push(&_optionsmenu_state);
        _optionsmenu_state.start();
        _pausemenu_state.start();
    }
}

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

void GameEngine::set_state_quit_menu(int action)
{
    if (_states_stack.top() != &_quitmenu_state)
    {
        _quitmenu_state.set_action(action);
        _states_stack.push(&_quitmenu_state);
        _pausemenu_state.start();
        _quitmenu_state.start();
    }
}

void GameEngine::stop_current_state()
{
    _states_stack.pop();
    if (_states_stack.top() == &_ingame_state)
    {
        g_audio_manager.unpause_fx();
    }
}

void GameEngine::change_screen_size()
{
  /*  Preferences *pref = pref_get_instance();

    int width = 800;
    int height = 600;
    bool wide = false;

    if (_render_mode == RENDER_OPENGL)
    {
        switch (pref -> screen_size)
        {
        case SCREEN_SIZE_320x240:
            width = 320;
            height = 240;
            wide = true;
            break;

        case SCREEN_SIZE_640x480:
            width = 640;
            height = 480;
            wide = false;
            break;

        case SCREEN_SIZE_640x480_WIDE:
            width = 640;
            height = 480;
            wide = true;
            break;

        case SCREEN_SIZE_800x600:
            width = 800;
            height = 600;
            wide = false;
            break;

        case SCREEN_SIZE_800x600_WIDE:
            width = 800;
            height = 600;
            wide = true;
            break;
        }
    }

    if (pref -> fullscreen)
    {
        _p_window->set_fullscreen(width,height,0,0);
        CL_Mouse::hide();

        if (_render_mode == RENDER_OPENGL)
        {
            if (!wide)
            {
                CL_GraphicContext *gc = _p_window -> get_gc();
                double scale_width = width / 800.0;
                double scale_height = height / 600.0;
                gc -> set_scale(scale_width, scale_height);
            }
            else
            {
                CL_Display::clear(CL_Color(0, 0, 0));
                CL_Display::flip();

                int new_width = 2 * width - 16.0 / 10.0 * height;
                int dx = (width - new_width) / 2;

                CL_GraphicContext *gc = _p_window -> get_gc();
                double scale_width = new_width / 800.0;
                double scale_height = height / 600.0;
                gc -> set_scale(scale_width, scale_height);
                gc -> add_translate(dx, 0, 0);

            }

        }
    }
    else
    {
        _p_window -> set_windowed();
        CL_Mouse::show();

        if (_render_mode == RENDER_OPENGL)
        {
            _p_window -> set_size(width, height);

            CL_GraphicContext *gc = _p_window -> get_gc();
            double scale_width = width  / 800.0;
            double scale_height = height / 600.0;
            gc -> set_scale(scale_width, scale_height);

        }
    }*/
}


void GameEngine::toggle_screen()
{
    Preferences *pref = pref_get_instance();
    pref -> fullscreen = !pref -> fullscreen;
    change_screen_size();
    _optionsmenu_state.toggle_screen();
}

void GameEngine::refresh_framerate_limit()
{
    Preferences *pref = pref_get_instance();
    _fps_getter.set_fps_limit(pref -> maxfps);
}

int GameEngine::get_fps()
{
    return _fps_getter.get_fps();
}

bool GameEngine::is_opengl_used()
{
    return _render_mode != Preferences::SDL;
}

bool GameEngine::is_fullscreen()
{
    Preferences *pref = pref_get_instance();
    return pref -> fullscreen;
}

void GameEngine::set_skin(std::string skin)
{
    CommonResources *resources = common_resources_get_instance();

    _p_loading_screen = my_new LoadingScreen();
		_p_loading_screen -> init(*resources->p_gc, *resources->p_window);
    _p_loading_screen -> set_progression(0.0f);

    Preferences *pref = pref_get_instance();

    std::string old_skin = pref -> skin;

		CL_GraphicContext gc = _main_window.get_gc();
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

void GameEngine::set_skin_element(unsigned int element)
{
    _skinsmenu_state.set_skin_elements(element);
}
