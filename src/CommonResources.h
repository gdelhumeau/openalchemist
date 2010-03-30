// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : CommonResources.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _COMMON_RESOURCES_H_
#define _COMMON_RESOURCES_H_

/************************************************************************/
/* Includes                                                             */
/************************************************************************/
#include <ClanLib/display.h>

#include "Board.h"
#include "HumanPlayer.h"
#include "DemoPlayer.h"
#include "FrontLayer.h"
#include "Keys.h"

/************************************************************************/
/* Class used                                                           */
/************************************************************************/
class GameEngine;

/** 
* Resources used everywhere
*/
class CommonResources{

public:

	/** GameEngine instance	*/
	GameEngine* p_engine;

	/** Main font */
	CL_Font main_font;

	/** Graphic context */
	CL_GraphicContext* p_gc;

	/** Window instance	*/
	CL_DisplayWindow* p_window;

	/** Human player */
	HumanPlayer player1;

	/** Common player */
	Player* p_current_player;

	/** Front layer */
	FrontLayer front_layer;

	/** Keys most used */
	Keys key;

	/** Current skin */
	std::string skin;

	/** Pieces dimension */
	int pieces_width, pieces_height;

	/** Time elapsed between current frame and the last one	*/
	float delta_time;

	/** Framerate (in frame / sec) */
	int fps;

	/** Highscore */
	unsigned int highscore;

	/** Previous highscore	*/
	unsigned int old_highscore;

	/** Constructor */
	CommonResources();

	/** Destructor */
	~CommonResources();
	
	/** Init resources */
	void init(GameEngine* p_engine);

	/** Load GFX */
	void load_gfx(CL_GraphicContext& gc, std::string skin);

	/** Unload GFX */
	void unload_gfx();

	/** Read scores	*/
	void read_scores();

	/** Save scores	*/
	void save_scores();

};

/** 
* Init common resources
*/
void common_resources_init();

/** 
* Terminate common resources
*/
void common_resources_term();

/** 
* Get the common resources singleton instance
*/
CommonResources* common_resources_get_instance();

#endif
