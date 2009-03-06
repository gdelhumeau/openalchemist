/********************************************************************
                          OpenAlchemist
 
  File : MenuState.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
 
 
 *********************************************************************/


#include "MenuState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"

enum{
    STEP_APPEARING,
    STEP_NORMAL,
    STEP_DISAPPEARING
};

#define APPEARING_SPEED 0.003

MenuState::MenuState ()
{
    selection = 0;
}

bool MenuState::front_layer_behind ()
{
    return true;
}

void MenuState::init ()
{
    std::cout << "MenuState class may not be used cause it is an abstract class" << std::endl;
}

void MenuState::deinit ()
{
    std::cout << "MenuState class may not be used cause it is an abstract class" << std::endl;
}

void MenuState::load_gfx (std::string skin)
{
    std::cout << "MenuState class may not be used cause it is an abstract class" << std::endl;
}

void MenuState::unload_gfx ()
{
    std::cout << "MenuState class may not be used cause it is an abstract class" << std::endl;
}

void MenuState::action_performed (int selection)
{
    std::cout << "MenuState class may not be used cause it is an abstract class" << std::endl;
}

void MenuState::update_child ()
{
    std::cout << "MenuState class may not be used cause it is an abstract class" << std::endl;
}

void MenuState::set_background_sprite (CL_Sprite *background)
{
    this -> background = background;
}

void MenuState::draw ()
{
    // Displaying background
    int x = 400 - background -> get_width () / 2;
    int y = 300 - background -> get_height () / 2;
    background -> draw (x, y);
	
    // Displaying items
    std::vector<MenuItem*>::iterator it = items.begin ();
    while (it != items.end ())
    {
        MenuItem *item = (MenuItem*) * it;
        item -> draw ();
        ++it;
    }

}

void MenuState::update ()
{
    switch (step)
    {
    case STEP_APPEARING:
        appear ();
        break;
    case STEP_DISAPPEARING:
        disappear ();
        break;
    }
    this -> update_child ();
}

void MenuState::events ()
{
    // Leaving the state
    if (common_resources -> key.escape->get () || common_resources -> key.pause->get ())
    {
        start_disappear ();
        selection = -1;
    }

    // Key ENTER
    if (common_resources -> key.enter -> get ())
    {
        start_disappear ();
    }

    // Key UP
    if (common_resources -> key.up -> get ())
    {
        items[selection] -> set_selected (false);
        bool changed = false;
        while (!changed)
        {
            if (selection == 0)
            {
                selection = items.size () - 1;
            }
            else
            {
                selection--;
            }

            if (!items[selection] -> is_locked ())
            {
                changed = true;
                items[selection] -> set_selected (true);
            }
        }
    }

    // Key DOWN
    if (common_resources -> key.down -> get ())
    {
        items[selection] -> set_selected (false);
        bool changed = false;
        while (!changed)
        {
            if (selection == (int) items.size () - 1)
            {
                selection = 0;
            }
            else
            {
                selection++;
            }

            if (!items[selection] -> is_locked ())
            {
                changed = true;
                items[selection] -> set_selected (true);
            }
        }
    }
    
    if(selection > -1)
    {
    	items[selection] -> events();
    }

}

void MenuState::start ()
{
    selection = 0;
    // All items are not selected
    
    std::vector<MenuItem*>::iterator it = items.begin ();
    while (it != items.end ())
    {
        MenuItem *item = (MenuItem*) * it;
        item -> set_selected (false);
        ++it;
    }
    // Except the selection
    items[selection] -> set_selected (true);

    // Now, begining appearing
    if (common_resources -> engine -> is_opengl_used ())
    {
        step = STEP_APPEARING;
        alpha = 0.0;
    }
    else
    {
        step = STEP_NORMAL;
    }
}

void MenuState::appear ()
{
    // Updating alpha value
    if (alpha + APPEARING_SPEED * common_resources -> time_interval >= 1.0)
    {
        step = STEP_NORMAL;
        alpha = 1.0;
    }
    else
    {
        alpha += APPEARING_SPEED * common_resources -> time_interval;
    }

    // Updating background sprite
    background -> set_alpha (alpha);

    // Updating items
    std::vector<MenuItem*>::iterator it = items.begin ();
    while (it != items.end ())
    {
        MenuItem *item = (MenuItem*) * it;
        item -> set_alpha (alpha);
        ++it;
    }

}

void MenuState::disappear ()
{
    // Updating alpha value
    alpha -= APPEARING_SPEED * common_resources -> time_interval;

    // Updating background sprite
    background -> set_alpha (alpha);

    // Updating items
    std::vector<MenuItem*>::iterator it = items.begin ();
    while (it != items.end ())
    {
        MenuItem *item = (MenuItem*) * it;
        item -> set_alpha (alpha);
        ++it;
    }

    if (alpha <= 0)
    {
        // Now perfom child action or leaving the state
        if (selection == -1)
            common_resources -> engine -> stop_current_state ();
        else
            this -> action_performed (selection);
    }
}

void MenuState::start_disappear ()
{
    step = STEP_DISAPPEARING;
}

