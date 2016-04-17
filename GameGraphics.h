
#ifndef GAMEGRAPHICS_H_INCLUDED
#define GAMEGRAPHICS_H_INCLUDED

#include <SDL/SDL.h>

int LoadGameGraphics();
void FreeGameGraphics();
void DrawGameGraphics(SDL_Surface * screen);

#endif // GAMEGRAPHICS_H_INCLUDED
