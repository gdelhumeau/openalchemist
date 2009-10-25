// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : GameEngine.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

#define GAME_WIDTH 800
#define GAME_HEIGHT 600

#include <stack>

#ifdef WITH_DX_9
#include <ClanLib/d3d9.h>
#endif

#include <ClanLib/display.h>
#include <ClanLib/gl1.h>
#include <ClanLib/gl.h>
#include <ClanLib/gdi.h>

#include "Window.h"
#include "FrameRateCounter.h"
#include "SkinsManager.h"
#include "states/GameState.h"
#include "states/CommonState.h"
#include "states/InGameState.h"
#include "states/GameOverState.h"
#include "states/PauseMenuState.h"
#include "states/SkinsMenuState.h"
#include "states/OptionsMenuState.h"
#include "states/TitleState.h"
#include "states/QuitMenuState.h"

class LoadingScreen;

/**
* GameEngine class - controls the states
*/
class
	GameEngine{

public:

	/**
	* Constructor
	*/
	GameEngine();

	/**
	* Destructor
	*/
	~GameEngine();

	/**
	* Initializing game engine
	*/
	void init();

	/** 
	* Terminate game engine
	*/
	void term();
	
	/**
	* Main loop
	*/
	void run();

	/**
	* Stopping the game engine
	*/
	void stop();

	/** 
	* Set current state to title state
	*/
	void set_state_title();

	/** 
	* Set current state to new game menu state
	*/
	void set_state_new_game_menu();

	/** 
	* Set current state to pause menu state
	*/
	void set_state_pause_menu();

	/** 
	* Set current state to ingame state
	*/
	void set_state_ingame();

	/** 
	* Set current state to game over state
	*/
	void set_state_gameover(bool is_highscore);

	/** 
	* Set current state to options menu state
	*/
	void set_state_options_menu();

	/** 
	* Set current state to skin menu state
	*/
	void set_state_skin_menu();

	/** 
	* Set current state to quit menu state
	*/
	void set_state_quit_menu(QuitMenuAction action);

	/**
	* Deleting current state of the stack
	*/
	void stop_current_state();

	/**
	* Switching to full screen mode or windowed mode
	*/
	void toggle_screen();

	/** 
	* Enable colorblind mode, or not
	*/
	void toggle_colorblind();

	/** 
	* Change max framerate
	*/
	void refresh_framerate_limit();

	/**
	* Returning Frame Rate
	*/
	int get_fps();

	/** 
	* Load a skin
	*/
	void set_skin(std::string skin);

	/** 
	* Change max available elements for current skin
	*/
	void set_skin_element(unsigned int element);

	/** 
	* Get the skins manager
	*/
	inline SkinsManager & get_skins_manager(){ return _skins_manager; }

private:

	/** 
	* Display window
	*/
	Window _window;

	/**
	* Setup display
	*/
	CL_SetupDisplay setup_display;

	/** 
	* Setup OpenGL 1
	*/
	CL_SetupGL1 target_GL1;	

	/**
	* Setup OpenGL 2
	*/
	CL_SetupGL target_GL2;

	/** 
	* Setup GDI (software render)
	*/
	CL_SetupGDI target_GDI;

#ifdef WITH_DX_9
	/** 
	* Setup DirectX 9
	*/
	CL_SetupD3D9 target_DX9;
#endif

	/**
	* Stack of states, the current state is on the top
	*/
	std::stack<GameState*> _states_stack;

	/** 
	* Controlling main loop
	*/
	bool _running;

	/**
	* Fps Getter
	*/
	CL_FramerateCounter _framerate_counter;

	/** 
	* Skins Manager
	*/
	SkinsManager _skins_manager;

	/** 
	* Common State
	*/
	CommonState _common_state;

	/** 
	* InGame State
	*/
	InGameState _ingame_state;

	/** 
	* GameOver State
	*/
	GameOverState _gameover_state;

	/** 
	* Pause Menu State
	*/
	PauseMenuState _pausemenu_state;

	/** 
	* Skins Menu State
	*/
	SkinsMenuState _skinsmenu_state;

	/** 
	* Options Menu State
	*/
	OptionsMenuState _optionsmenu_state;

	/** 
	* Title State
	*/
	TitleState _title_state;

	/** 
	* Quit Menu State
	*/
	QuitMenuState _quitmenu_state;

	/** 
	* Loading Screen
	*/
	LoadingScreen * _p_loading_screen;

};

#endif