#include "GameState.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

Vector2D MenuPosition;
Vector2D Arrow1Position;
Vector2D Arrow2Position;
Vector2D PaddlePosition;
Vector2D BallPosition;
Vector2D GameOverPosition;

Vector2D BallDirection;

int ScreenSize_W = 0; // Initalized from screen surface size
int ScreenSize_H = 0;

int PaddleOneSize_W = 0; // Initialized from bitmap size
int PaddleOneSize_H = 0;

int PaddleTwoSize_W = 0;
int PaddleTwoSize_H = 0;

int BallSize_W = 0; // Initialized from bitmap size
int BallSize_H = 0;

int GameOver_W = 0; // Initialized from bitmap size
int GameOver_H = 0;

int lives = 3;
int tempState = 0;

bool Movement_H = false;
bool Movement_V = false;
bool Movement_P = false;

State state = MENU;

float ElapsedTime = 0.0f;

static int PressingLeft = 0;
static int PressingRight = 0;
static int PressingUp = 0;
static int PressingDown = 0;
static float BallSpeed = 150.0f;

void InitializeMenu() {
    MenuPosition.X = 0;
    MenuPosition.Y = 0;

    Arrow1Position.X = 120;
    Arrow1Position.Y = 240;

    Arrow2Position.X = 520 - 27;
    Arrow2Position.Y = 240;
    tempState = 0;
}

void InitializeGame() {
    PaddlePosition.X = (ScreenSize_W - PaddleOneSize_W) / 2;
    PaddlePosition.Y = ScreenSize_H - PaddleOneSize_H - 40;

    BallPosition.X = (ScreenSize_W - BallSize_W) / 2;
    BallPosition.Y = ScreenSize_H / 2;

    GameOverPosition.X = (ScreenSize_W - 444) / 2;
    GameOverPosition.Y = (ScreenSize_H - 128) / 2;

    printf("x: %f y: %f\n", GameOverPosition.X, GameOverPosition.Y);

    BallDirection.X = (rand() % 3) - 1;
    BallDirection.Y = 1;
    BallSpeed = 150.0f;
}

void UpdatePlayerInput(const SDL_Event *event) {
    if (!event)
        return;

    // Evento para cuando se preciona la flecha izquierda
    if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_LEFT)
        PressingLeft = 1;

    if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_LEFT)
        PressingLeft = 0;

    // Evento para cuando se preciona la flecha derecha
    if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_RIGHT)
        PressingRight = 1;

    if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_RIGHT)
        PressingRight = 0;

    // Evento para cuando se preciona la flecha de arriba
    if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_UP){
        if(state == MENU && Arrow1Position.Y > 240 && Arrow2Position.Y > 240) {
            Arrow1Position.Y -= 40;
            Arrow2Position.Y -= 40;
            tempState--;
        }
    }

    if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_UP)
        PressingUp = 0;

    // Evento para cuando se preciona la flecha de abajo
    if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_DOWN) {
        if(Arrow1Position.Y < 320 && Arrow2Position.Y < 320 && state == MENU) {
            Arrow1Position.Y += 40;
            Arrow2Position.Y += 40;
            tempState++;
        }
    }

    if(event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_DOWN)
        PressingDown = 0;

    // Evento para cuando se preciona la tecla enter
    if(event->type == SDL_KEYDOWN && event->key.keysym.sym == '\r'){
        if(state == MENU){
            switch (tempState){
                case 0:{
                    state = PLAY1;
                    InitializeGame();
//                    printf("opcion 1\n");
                }break;

                case 1:{
                    state = PLAY2;
//                    printf("opcion 2\n");
                }break;

                case 2:{
//                    printf("opcion 3\n");
                    exit(0);
                }break;
            }
        }
    }

    if (event->key.keysym.sym == SDLK_BACKSPACE) {
        lives = 3;
        InitializeGame();
    }
}

bool IntersectSquares(Vector2D Position1, float Width1, float Height1,
                      Vector2D Position2, float Width2, float Height2) {
    if (Position1.X + Width1 >= Position2.X &&
        Position1.X <= Position2.X + Width2 &&
        Position1.Y + Height1 >= Position2.Y &&
        Position1.Y <= Position2.Y + Height2) {
        return true;
    }
    else {
        return false;
    }
}

void UpdateGameMenu(float deltaTime){
    //adds deltaTime to the game total
    ElapsedTime += deltaTime;

    if (PressingDown){
        Arrow1Position.Y += 40;
        Arrow2Position.Y += 40;
    }
    if(PressingUp){
        Arrow1Position.Y -= 40;
        Arrow2Position.Y -= 40;
    }
}

void UpdateGamePlay(float deltaTime) {

    //adds deltaTime to the game total
    ElapsedTime += deltaTime;

    const float PaddleSpeed = 200.0f;

    BallPosition.Y += BallSpeed * deltaTime * BallDirection.Y;
    BallPosition.X += BallSpeed * deltaTime * BallDirection.X;

    bool collitioned = false;

    //cout << ScreenSize_W - BallPosition.X << "\n";

    //collition with top border
    if (BallPosition.Y < 0) {
        collitioned = true;
        if (!Movement_V) {
            cout << "Cambia direccion V" << endl;
            Movement_V = true;
            BallDirection.Y *= (-1);
        }
    }

    //collition with bottom border
    if (ScreenSize_H - BallPosition.Y - BallSize_H < 0) {
        collitioned = true;
        if (!Movement_V) {
            cout << "Cambia direccion V" << endl;
            Movement_V = true;
            BallDirection.Y *= (-1);
            lives--;
            cout << "Speed Reached: " << BallSpeed << endl;
            if (lives > 0) {
                InitializeGame();
            }
            else {
                BallDirection.Y = 0;
                BallDirection.X = 0;
                cout << "Elapsed Time: " << ElapsedTime << " seconds" << endl;
            }
        }
    }

    //collition with vertical borders
    if ((ScreenSize_W - BallPosition.X - BallSize_W < 0) || (BallPosition.X < 0)) {
        collitioned = true;
        if (!Movement_H) {
            cout << "Cambia direccion H" << endl;
            Movement_H = true;
            BallDirection.X *= (-1);
        }
    }

    //Tests if the full ball is on the screen
    if (!collitioned) {
        Movement_H = false;
        Movement_V = false;
    }

    bool collitioned_P = false;

    if (IntersectSquares(PaddlePosition, PaddleOneSize_W, PaddleOneSize_H, BallPosition, BallSize_W, BallSize_H)) {
        collitioned_P = true;
        cout << "Intersection with paddle" << endl;
        if (!Movement_P) {
            Movement_P = true;
            Vector2D PaddleCenter;
            PaddleCenter.X = PaddlePosition.X + PaddleOneSize_W / 2;
            PaddleCenter.Y = PaddlePosition.Y + PaddleOneSize_H / 2;

            BallDirection.X = (BallPosition.X - PaddleCenter.X);
            BallDirection.Y = (BallPosition.Y - PaddleCenter.Y);

            float length = sqrt(BallDirection.X * BallDirection.X +
                                BallDirection.Y * BallDirection.Y);

            if (length > 0) {
                BallDirection.X /= length;
                BallDirection.Y /= length;
            }
            else {
                BallDirection.Y *= (-1);
            }
            BallSpeed += 50.0f;
            cout << BallSpeed << endl;
        }
    }

    if (!collitioned_P) {
        Movement_P = false;
    }

    //cout << BallDirection.X << endl;

    if (PressingLeft) {
        if (PaddlePosition.X > 0) {
            PaddlePosition.X -= PaddleSpeed * deltaTime;
        }
    }

    if (PressingRight) {
        if (PaddlePosition.X + PaddleOneSize_W < ScreenSize_W) {
            PaddlePosition.X += PaddleSpeed * deltaTime;
        }
    }
}
