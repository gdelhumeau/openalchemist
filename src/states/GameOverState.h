// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : GameOverState.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _GAMEOVER_STATE_H_
#define _GAMEOVER_STATE_H_

#include <ClanLib/display.h>

#include "MenuState.h"
#include "MenuState/DualChoiceItem.h"

/**
* InGame State
*/
class GameOverState : public MenuState{

public:

	/** Constructor */
	GameOverState();

	/** Destructor */
	~GameOverState();

	virtual void init();

	virtual void term();

	virtual void load_gfx(CL_GraphicContext& gc, std::string skin);

	virtual void unload_gfx();

	virtual void draw(CL_GraphicContext& gc);

	virtual void events(Window& window);

	virtual void action_performed(int selection, ActionType action_type);

	virtual void update_child();

	/** Set mode Highscore or not */
	void set_highscore(bool highscore);
	
private:

	/** Choice item */
	DualChoiceItem _quit_choice_item;

	/** Background */
	CL_Sprite _dialog_gameover, _dialog_highscore;

	/** Score coords */
	int _score1_x;
	int _score1_y;
	int _score2_x;
	int _score2_y;

	/** If there is a new highscore */
	bool _is_highscore;

};

#endif
