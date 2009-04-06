#include "InterfaceC_CPP.h"



void CallToEngine(SDL_Surface* screen_surface)
{
   GameEngine *game;
   game = new GameEngine(screen_surface, false);
   game->init();
   game->run();
}