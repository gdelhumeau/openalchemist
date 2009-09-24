/********************************************************************
                          OpenAlchemist

  File : PauseMenuState.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _PAUSEMENU_STATE_H_
#define _PAUSEMENU_STATE_H_

#include "MenuState.h"
#include "../KeyboardKey.h"
#include "MenuState/BasicItem.h"


/**
 * PauseMenu State
 */
class PauseMenuState : public MenuState{

  private:
  
 	BasicItem _resume_item;
	BasicItem _undo_item;
	BasicItem _retry_item;
	BasicItem _options_item;
	BasicItem _giveup_item;
	BasicItem _quit_item;

  public:
  void init();
  void deinit();
  void load_gfx(CL_GraphicContext &gc, std::string skin);
  void unload_gfx();
  void action_performed(int selection, int action_type);
	void update_child();

  PauseMenuState();
  ~PauseMenuState();


};

#endif
