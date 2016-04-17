#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include <SDL/SDL.h>

typedef struct
{
    float X;
    float Y;
} Vector2D;

typedef enum {
    MENU, PLAY1, PLAY2, GAMEOVER
} State;

extern Vector2D MenuPosition;
extern Vector2D Arrow1Position;
extern Vector2D Arrow2Position;
extern Vector2D PaddlePosition;
extern Vector2D BallPosition;
extern Vector2D GameOverPosition;

extern int ScreenSize_W;
extern int ScreenSize_H;

extern int PaddleOneSize_W;
extern int PaddleOneSize_H;

extern int PaddleTwoSize_W;
extern int PaddleTwoSize_H;

extern int BallSize_W;
extern int BallSize_H;

extern int GameOver_W;
extern int GameOver_H;

extern int lives;

extern bool Movement_H;
extern bool Movement_V;
extern bool Movement_P;

extern State state;


void InitializeMenu();
void InitializeGame();
void UpdatePlayerInput(const SDL_Event * event);
void UpdateGameMenu(float deltaTime);
void UpdateGamePlay(float deltaTime);
bool IntersecSquares(Vector2D Position1, float Width1, float Height1,
						Vector2D Position2, float Width2, float Height2);

#endif // GAMESTATE_H_INCLUDED
