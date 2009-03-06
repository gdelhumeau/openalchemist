/********************************************************************
                          OpenAlchemist
 
  File : QuitMenuSate.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
 
 
*********************************************************************/

#ifndef _QUITMENU_STATE_H_
#define _QUITMENU_STATE_H_

#include <ClanLib/display.h>

#include "MenuState.h"
#include "GameState.h"
#include "../KeyboardKey.h"
#include "MenuState/BasicItem.h"
#include "MenuState/DualChoiceItem.h"

#define QUITMENU_GIVE_UP 1
#define QUITMENU_RETRY 2
#define QUITMENU_EXIT 3


class GameEngine;


/**
 * QuitMenuGame State
 */
class QuitMenuState : public MenuState
{

private:

    DualChoiceItem _choice_item;

    CL_Sprite * panel_give_up, *panel_retry, *panel_exit;
    int panel_x, panel_y;

    int yes_x, yes_y;
    int no_x, no_y;
    int selection;

    int action;
    int step;

    double alpha;


public:
    void init();
    void deinit();
    void load_gfx(std::string skin);
    void unload_gfx();

    void action_performed(int selection);
    void update_child();

    QuitMenuState();
    ~QuitMenuState();

    void set_action(int a);


};

#endif
