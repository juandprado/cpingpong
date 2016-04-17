#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include <SDL/SDL.h>

typedef struct
{
    float X;
    float Y;
} Vector2D;

extern Vector2D PaddlePosition;
extern Vector2D BallPosition;
extern Vector2D GameOverPosition;

extern int ScreenSize_W;
extern int ScreenSize_H;

extern int PaddleSize_W;
extern int PaddleSize_H;

extern int BallSize_W;
extern int BallSize_H;

extern int GameOver_W;
extern int GameOver_H;

extern int lives;

extern bool Movement_H;
extern bool Movement_V;
extern bool Movement_P;

void InitializeGame();
void UpdatePlayerInput(const SDL_Event * event);
void UpdateGame(float deltaTime);
bool IntersecSquares(Vector2D Position1, float Width1, float Height1,
						Vector2D Position2, float Width2, float Height2);

#endif // GAMESTATE_H_INCLUDED
