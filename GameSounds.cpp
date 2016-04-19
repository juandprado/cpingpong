#ifdef __cplusplus
#include <cstdlib>
#else

#include <stdlib.h>

#endif

#include <SDL/SDL.h>
#include "GameSounds.h"
#include "GameState.h"
#include <iostream>


SDL_AudioSpec MenuSound;
SDL_AudioSpec *WallSound = (SDL_AudioSpec*) malloc(sizeof(SDL_AudioSpec));
SDL_AudioSpec *PaddleSound = 0;
SDL_AudioSpec *LoseSound = 0;

static Uint8 *audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len;

void my_audio_callback(void *userdata, Uint8 *stream, int len) {

    if (audio_len ==0)
        return;

    len = ( len > audio_len ? audio_len : len );
    //SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
    SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

    audio_pos += len;
    audio_len -= len;
}

int LoadGameSounds(){


    return 0;
}

void * PlaySound(void *arg){

//    if (SDL_Init(SDL_INIT_AUDIO) < 0)
//        return 1;

    static Uint32 wav_length; // length of our sample
    static Uint8 *wav_buffer; // buffer containing our audio file
    static SDL_AudioSpec wav_spec; // the specs of our piece of music

    if( SDL_LoadWAV("sound_paddle.wav", &wav_spec, &wav_buffer, &wav_length) == NULL ){
        printf("Unable to load sound: %s\n", SDL_GetError());
//        return 1;
    }

    // set the callback function
    wav_spec.callback = my_audio_callback;
    wav_spec.userdata = NULL;
    // set our global static variables
    audio_pos = wav_buffer; // copy sound buffer
    audio_len = wav_length; // copy file length
    /* Open the audio device */
    /* Open the audio device */
    if ( SDL_OpenAudio(&wav_spec, NULL) < 0 ){
        fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
        exit(-1);
    }

    /* Start playing */
    SDL_PauseAudio(0);

    // wait until we're don't playing
    while ( audio_len > 0 ) {
        SDL_Delay(10);
    }

    // shut everything down
    SDL_CloseAudio();
    SDL_FreeWAV(wav_buffer);
}