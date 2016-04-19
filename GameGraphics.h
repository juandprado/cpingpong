
#ifndef GAMEGRAPHICS_H_INCLUDED
#define GAMEGRAPHICS_H_INCLUDED

#include <SDL/SDL.h>

int LoadGameGraphics();

void FreeGameGraphics();
void gamePlay1(SDL_Surface * screen);
void gamePlay2(SDL_Surface * screen);
void gameOver(SDL_Surface * screen);
void DrawGameGraphics(SDL_Surface * screen);

#endif // GAMEGRAPHICS_H_INCLUDED
