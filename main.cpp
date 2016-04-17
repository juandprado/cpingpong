#ifdef __cplusplus
#include <cstdlib>
#else

#include <stdlib.h>

#endif

#include <SDL/SDL.h>
#include <time.h>
#include "GameGraphics.h"
#include "GameState.h"

int main(int argc, char **argv) {
    // seed initialize
    srand(time(NULL));
    // initialize SDL video
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface *screen = SDL_SetVideoMode(640, 480, 16,
                                           SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!screen) {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    ScreenSize_W = screen->w;
    ScreenSize_H = screen->h;

    // load game graphics
    int errorCode = LoadGameGraphics();

    if (errorCode) {
        printf("Error loading game graphics.\n");
        return 1;
    }
    InitializeMenu();
//    InitializeGame();

    // program main loop
    float lastTime = (float) SDL_GetTicks() / 1000.0f;
    bool done = false;
    while (!done) {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // check for messages
            switch (event.type) {
                // exit if the window is closed
                case SDL_QUIT:
                    done = true;
                    break;

                    // check for keypresses
                case SDL_KEYDOWN: {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;

                    break;
                }
            } // end switch

            if (!done)
                UpdatePlayerInput(&event);

        } // end of message processing

        switch (state) {
            case MENU:{
                float currentTime = (float) SDL_GetTicks() / 1000.0f;
//                float currentTime = (float) SDL_GetTicks() / 1000.0f;
//                float deltaTime = currentTime - lastTime;

//                if (deltaTime > 0)
//                    UpdateGameMenu(deltaTime);
                lastTime = currentTime;
            }break;

            case PLAY1:{

                float currentTime = (float) SDL_GetTicks() / 1000.0f;
                float deltaTime = currentTime - lastTime;

                if (deltaTime > 0)
                    UpdateGamePlay(deltaTime);

                lastTime = currentTime;
            }break;

            case PLAY2:{

            }break;

            case GAMEOVER:{

            }
        }
        DrawGameGraphics(screen);

    } // end main loop

    FreeGameGraphics();

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
