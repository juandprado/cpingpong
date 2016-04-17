
#ifndef GAMEGRAPHICS_H_INCLUDED
#define GAMEGRAPHICS_H_INCLUDED

#include <SDL/SDL.h>

int LoadGameGraphics();
void FreeGameGraphics();
void gamePlay(SDL_Surface * screen);
void gameOver(SDL_Surface * screen);
void DrawGameGraphics(SDL_Surface * screen);

#endif // GAMEGRAPHICS_H_INCLUDED
