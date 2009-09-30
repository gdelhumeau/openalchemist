/********************************************************************
                          OpenAlchemist

  File : GameOverState.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _GAMEOVER_STATE_H_
#define _GAMEOVER_STATE_H_

#include <ClanLib/display.h>

#include "GameState.h"
#include "../KeyboardKey.h"

#define MODE_GAMEOVER 1
#define MODE_HIGHSCORE 2

#define GAMEOVER_SELECTION_YES 1
#define GAMEOVER_SELECTION_NO 2

class GameEngine;


/**
* InGame State
*/
class GameOverState : public GameState{

private:

	CL_Sprite _dialog, _dialog_gameover, _dialog_highscore;
	int _dialog_x, _dialog_y;
	int _score1_x;
	int _score1_y;
	int _score2_x;
	int _score2_y;

	CL_Sprite _yes_selected, _yes_unselected;
	CL_Sprite _no_selected, _no_unselected;
	int _yes_x, _yes_y;
	int _no_x, _no_y;

	int _mode;
	int _selection;

public:
	void init();
	void deinit();
	void load_gfx(CL_GraphicContext &gc, std::string skin);
	void unload_gfx();
	void draw(CL_GraphicContext &gc);
	void update(CL_GraphicContext &gc);
	void events(CL_DisplayWindow & window);

	bool front_layer_behind();

	void set_mode(int mode);
	void start();

	GameOverState();
	~GameOverState();


};

#endif
