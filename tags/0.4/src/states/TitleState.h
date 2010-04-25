// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : TitleState.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _TITLE_STATE_H_
#define _TITLE_STATE_H_

#include <ClanLib/display.h>

#include "GameState.h"
#include "../KeyboardKey.h"
#include "../DemoPlayer.h"

enum{ NUMBER_OF_SENTENCES = 16 };

/**
* Title State
*/
class TitleState : public GameState{

public:
	
	/** Constructor */
	TitleState();

	/** Destructor */
	~TitleState();

	virtual void init();
	
	virtual void term();
	
	virtual void load_gfx(CL_GraphicContext& gc, std::string skin);
	
	virtual void unload_gfx();
	
	virtual void draw(CL_GraphicContext& gc);
	
	virtual void update(CL_GraphicContext& gc);
	
	virtual void events(Window& window);

	virtual bool front_layer_behind();

	/** Start */
	void start();

private:

	/** Demo player */
	DemoPlayer _demo_player;

	/** Start message */
	CL_Sprite _start_message;

	/** Start message coords */
	int _start_message_x, _start_message_y;

	/** Keys demo */
	CL_Sprite _keydemo_left, _keydemo_up, _keydemo_right, _keydemo_down;
	CL_Sprite _keydemo_escape, _keydemo_options;

	/** Help sentences **/
	CL_Sprite _sentences[NUMBER_OF_SENTENCES];

	/** Help sentences coords **/
	int _sentences_x[NUMBER_OF_SENTENCES], _sentences_y[NUMBER_OF_SENTENCES];

	/** Help sentences time **/
	int _sentences_time[NUMBER_OF_SENTENCES];

	/** Keyboard demo coords **/
	int _keyleft_x, _keyleft_y, _keyup_x, _keyup_y, _keyright_x, _keyright_y,
		_keydown_x, _keydown_y;

	/** Time when will come the next step **/
	unsigned int _next_time;

	/** Current Step **/
	short int _step;

	/** Demo events */
	bool _new_game, _fall, _change_angle, _select_the_position,
		_fall_paused, _destruction_paused;

	/** Fonts */
	CL_Font _p_font;

};

#endif