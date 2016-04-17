#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include "GameGraphics.h"
#include "GameState.h"
#include <iostream>
using namespace std;

SDL_Surface* PaddleGraphic1 = 0;
SDL_Surface* BallGraphic = 0;
SDL_Surface* GameOverGraphic = 0;

int LoadGameGraphics()
{
    PaddleGraphic1 = SDL_LoadBMP("paddle_1.bmp");
    if (!PaddleGraphic1)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    PaddleSize_W = PaddleGraphic1->w;
    PaddleSize_H = PaddleGraphic1->h;

    BallGraphic = SDL_LoadBMP("ball.bmp");
    if (!BallGraphic)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    BallSize_W = BallGraphic->w;
    BallSize_H = BallGraphic->h;

    GameOverGraphic = SDL_LoadBMP("gameOver.bmp");
    if (!GameOverGraphic){
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }



    return 0;
}

void FreeGameGraphics()
{
    SDL_FreeSurface(PaddleGraphic1);
    SDL_FreeSurface(BallGraphic);
}

void gamePlay(SDL_Surface * screen){
    // clear screen
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

    SDL_Rect dstrect;
    dstrect.x = (int)PaddlePosition.X;
    dstrect.y = (int)PaddlePosition.Y;

    // draw paddle bitmap
    SDL_BlitSurface(PaddleGraphic1, 0, screen, &dstrect);

    dstrect.x = (int)BallPosition.X;
    dstrect.y = (int)BallPosition.Y;

    // draw ball bitmap
    SDL_BlitSurface(BallGraphic, 0, screen, &dstrect);

    dstrect.x = 5;
    dstrect.y = 5;

    for (int i = 0; i < lives; ++i, dstrect.x += 21){
        SDL_BlitSurface(BallGraphic, 0, screen, &dstrect);
    }

    // finally, update the screen :)
    SDL_Flip(screen);
}

void gameOver(SDL_Surface * screen){
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

    SDL_Rect dstrect;
    dstrect.x = (int)GameOverPosition.X;
    dstrect.y = (int)GameOverPosition.Y;

    // draw paddle bitmap
    SDL_BlitSurface(GameOverGraphic, 0, screen, &dstrect);

    // finally, update the screen :)
    SDL_Flip(screen);
}

void DrawGameGraphics(SDL_Surface * screen){
    if (lives <= 0){
        gameOver(screen);
    }else{
        gamePlay(screen);
    }
}
