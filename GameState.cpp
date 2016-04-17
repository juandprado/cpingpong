#include "GameState.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

Vector2D MenuPosition;
Vector2D Arrow1Position;
Vector2D Arrow2Position;
Vector2D PaddleOnePosition;
Vector2D PaddleTwoPosition;
Vector2D BallPosition;
Vector2D GameOverPosition;

Vector2D BallDirection;

int ScreenSize_W = 0; // Initialized from screen surface size
int ScreenSize_H = 0;

int PaddleOneSize_W = 0; // Initialized from bitmap size
int PaddleOneSize_H = 0;

int PaddleTwoSize_W = 0; // Initialized from bitmap size
int PaddleTwoSize_H = 0;

int BallSize_W = 0; // Initialized from bitmap size
int BallSize_H = 0;

int GameOver_W = 0; // Initialized from bitmap size
int GameOver_H = 0;

int livesPlayer1 = 3;
int livesPlayer2 = 3;
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

void InitializeGame1(){
    PaddleOnePosition.X = (ScreenSize_W - PaddleOneSize_W) / 2;
    PaddleOnePosition.Y = ScreenSize_H - PaddleOneSize_H - 40;

    BallPosition.X = (ScreenSize_W - BallSize_W) / 2;
    BallPosition.Y = ScreenSize_H / 2;

    GameOverPosition.X = (ScreenSize_W - 444) / 2;
    GameOverPosition.Y = (ScreenSize_H - 128) / 2;

    printf("x: %f y: %f\n", GameOverPosition.X, GameOverPosition.Y);

    BallDirection.X = (rand() % 3) - 1;
    BallDirection.Y = 1;
    BallSpeed = 150.0f;
}

void InitializeGame2(){
    PaddleOnePosition.X = (ScreenSize_W - PaddleOneSize_W) / 2;
    PaddleOnePosition.Y = ScreenSize_H - PaddleOneSize_H - 40;

    PaddleTwoPosition.X = (ScreenSize_W - PaddleTwoSize_W) / 2;
    PaddleTwoPosition.Y =  40;

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
                    InitializeGame1();
//                    printf("opcion 1\n");
                }break;

                case 1:{
                    state = PLAY2;
                    InitializeGame2();
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
        livesPlayer1 = 3;
        livesPlayer2 = 3;
        state = MENU;
    }
}

bool IntersectSquares(Vector2D Position1, float Width1, float Height1,
                      Vector2D Position2, float Width2, float Height2){
    if (Position1.X + Width1 >= Position2.X &&
        Position1.X <= Position2.X + Width2 &&
        Position1.Y + Height1 >= Position2.Y &&
        Position1.Y <= Position2.Y + Height2){
        return true;
    }
    else{
        return false;
    }
}

float BallProjection(float y, float y0, float y1, float x0, float x1){
    float x = ( ( (y - y1) / (y1 - y0) ) * ( x1 - x0)) + (x0);
    while (x < 0 || x > ScreenSize_W - BallSize_W)
    {
        cout << x << endl;
        if (x < 0)
        {
            x *= (-1);
        }
        else
        {
            x = 2 * (ScreenSize_W - BallSize_W) - x;
        }
    }
    return x;
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
    if (BallPosition.Y < 0)
    {
        collitioned = true;
        if (!Movement_V)
        {
            cout << "Cambia direccion V" << endl;
            cout << "Posicion colision x: " << BallPosition.X << endl;
            cout << "Posicion colision y: " << BallPosition.Y << endl;
            Movement_V = true;
            BallDirection.Y *= (-1);
        }
    }

    //collition with bottom border
    if (ScreenSize_H - BallPosition.Y - BallSize_H < 0)
    {
        collitioned = true;
        if (!Movement_V)
        {
            cout << "Cambia direccion V" << endl;
            Movement_V = true;
            BallDirection.Y *= (-1);
            livesPlayer1--;
            cout << "Speed Reached: " << BallSpeed << endl;
            if (livesPlayer1 > 0) {
                InitializeGame1();
            }
            else {
                state = GAMEOVER;
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

    if (IntersectSquares(PaddleOnePosition, PaddleOneSize_W, PaddleOneSize_H, BallPosition, BallSize_W, BallSize_H))
    {
        collitioned_P = true;
        cout << "Intersection with paddle 1" << endl;
        if (!Movement_P)
        {
            Movement_P = true;
            Vector2D PaddleCenter;
            PaddleCenter.X = PaddleOnePosition.X + PaddleOneSize_W / 2;
            PaddleCenter.Y = PaddleOnePosition.Y + PaddleOneSize_H / 2;

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
            float y = 0.0f;
            float y0 = BallPosition.Y;
            float y1 = y0 - BallDirection.Y;
            float x0 = BallPosition.X;
            float x1 = x0 - BallDirection.X;

            float x = BallProjection(y, y0, y1, x0, x1);
            cout << "x projected: " << x << endl;
        }
    }

    if (!collitioned_P) {
        Movement_P = false;
    }

    //cout << BallDirection.X << endl;

    if (PressingLeft) {
        if (PaddleOnePosition.X > 0) {
            PaddleOnePosition.X -= PaddleSpeed * deltaTime;
        }
    }

    if (PressingRight) {
        if (PaddleOnePosition.X + PaddleOneSize_W < ScreenSize_W) {
            PaddleOnePosition.X += PaddleSpeed * deltaTime;
        }
    }
}
