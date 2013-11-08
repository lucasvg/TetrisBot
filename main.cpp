//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include "general_functions.h"


// handle the exit of the program
bool quit = false;

// to show the homeScreen
bool homeScreen = true;

// the screen
SDL_Surface *screen = NULL;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const char *SCREEN_CAPTION = "Move the Dot";

//the event handler
SDL_Event event;

int main(int argc, char* args[]) {

    //INICIALIZATION-------------------------
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return 1;

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    if (screen == NULL)
        return 1;

    SDL_WM_SetCaption(SCREEN_CAPTION, NULL);
    //END INICIALIZATION--------------------    


    if (homeScreen)
        applyHomeScreen(screen);

    //While the user hasn't quit
    while (quit == false) {

        //While there's events to handle
        while (SDL_PollEvent(&event)) {

            //verify if space was 
            if (homeScreen)
                if (event.type == SDL_KEYDOWN)
                    if (event.key.keysym.sym == SDLK_SPACE)
                        homeScreen = false;                
            if (homeScreen)
                continue;


            quit = true;

            //If the user has Xed out the window
            if (event.type == SDL_QUIT) {
                //Quit the program
                quit = true;
            }


        }

        //Update the screen
        if (SDL_Flip(screen) == -1) {
            return 1;
        }
    }

}