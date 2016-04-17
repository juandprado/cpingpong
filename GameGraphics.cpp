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

SDL_Surface *MenuGraphic = 0;
SDL_Surface *MenuArrowGraphic1 = 0;
SDL_Surface *MenuArrowGraphic2 = 0;
SDL_Surface *PaddleGraphic1 = 0;
SDL_Surface *PaddleGraphic2 = 0;
SDL_Surface *BallGraphic = 0;
SDL_Surface *GameOverGraphic = 0;

int LoadGameGraphics() {

    MenuGraphic = SDL_LoadBMP("menu.bmp");
    if (!MenuGraphic) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    MenuArrowGraphic1 = SDL_LoadBMP("arrow1.bmp");
    if (!MenuArrowGraphic1) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    MenuArrowGraphic2 = SDL_LoadBMP("arrow2.bmp");
    if (!MenuArrowGraphic2) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    // Image with the paddle 1
    PaddleGraphic1 = SDL_LoadBMP("paddle_1.bmp");
    if (!PaddleGraphic1) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    PaddleOneSize_W = PaddleGraphic1->w;
    PaddleOneSize_H = PaddleGraphic1->h;

    // Image with the paddle 2
    PaddleGraphic2 = SDL_LoadBMP("paddle_2.bmp");
    if (!PaddleGraphic2) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    PaddleTwoSize_W = PaddleGraphic2->w;
    PaddleTwoSize_H = PaddleGraphic2->h;

    //Image with the ball
    BallGraphic = SDL_LoadBMP("ball.bmp");
    if (!BallGraphic) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    BallSize_W = BallGraphic->w;
    BallSize_H = BallGraphic->h;

    // Image with the message GameOver
    GameOverGraphic = SDL_LoadBMP("gameOver.bmp");
    if (!GameOverGraphic) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    GameOver_W = GameOverGraphic->w;
    GameOver_H = GameOverGraphic->h;

    return 0;
}

void FreeGameGraphics() {
    SDL_FreeSurface(PaddleGraphic1);
    SDL_FreeSurface(BallGraphic);
}

void gameMenu(SDL_Surface *screen){
    // clear screen
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

    SDL_Rect dstrect;
    dstrect.x = (int) MenuPosition.X;
    dstrect.y = (int) MenuPosition.Y;

    // Draw menu screen
    SDL_BlitSurface(MenuGraphic, 0, screen, &dstrect);

    dstrect.x = (int) Arrow1Position.X;
    dstrect.y = (int) Arrow1Position.Y;

    // Draw Arrow1 to select
    SDL_BlitSurface(MenuArrowGraphic1, 0, screen, &dstrect);

    dstrect.x = (int) Arrow2Position.X;
    dstrect.y = (int) Arrow2Position.Y;

    // Draw Arrow1 to select
    SDL_BlitSurface(MenuArrowGraphic2, 0, screen, &dstrect);

    // finally, update the screen :)
    SDL_Flip(screen);
}

void gamePlay(SDL_Surface *screen) {
    // clear screen
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

    SDL_Rect dstrect;
    dstrect.x = (int) PaddleOnePosition.X;
    dstrect.y = (int) PaddleOnePosition.Y;

    // draw paddle1 bitmap
    SDL_BlitSurface(PaddleGraphic1, 0, screen, &dstrect);

    dstrect.x = (int) PaddleTwoPosition.X;
    dstrect.y = (int) PaddleTwoPosition.Y;

    // draw paddle2 bitmap
    SDL_BlitSurface(PaddleGraphic2, 0, screen, &dstrect);

    dstrect.x = (int) BallPosition.X;
    dstrect.y = (int) BallPosition.Y;

    // draw ball bitmap
    SDL_BlitSurface(BallGraphic, 0, screen, &dstrect);

    dstrect.x = 5;
    dstrect.y = 5;

    for (int i = 0; i < livesPlayer1; ++i, dstrect.x += 21) {
        SDL_BlitSurface(BallGraphic, 0, screen, &dstrect);
    }

    dstrect.x = 5;
    dstrect.y = 475 - 16;

    for (int i = 0; i < livesPlayer2; ++i, dstrect.x += 21) {
        SDL_BlitSurface(BallGraphic, 0, screen, &dstrect);
    }

    // finally, update the screen :)
    SDL_Flip(screen);
}


void gameOver(SDL_Surface *screen) {
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

    SDL_Rect dstrect;
    dstrect.x = (int) GameOverPosition.X;
    dstrect.y = (int) GameOverPosition.Y;

    // draw paddle bitmap
    SDL_BlitSurface(GameOverGraphic, 0, screen, &dstrect);

    // finally, update the screen :)
    SDL_Flip(screen);
}

void DrawGameGraphics(SDL_Surface *screen) {
    if (state == MENU) {
        gameMenu(screen);
    } else if(state == PLAY1 || state == PLAY2){
        gamePlay(screen);
    } else{
        gameOver(screen);
    }

}
