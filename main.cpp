// NOTES
//Add to the colision of the square, at square.cpp, the robot and the main piece





//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include "general_functions.h"
#include "iostream"

// handle the exit of the program
bool quit = false;

// to show the homeScreen
bool homeScreen = true;

// the screen
SDL_Surface *screen = NULL;
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const char *SCREEN_CAPTION = "TetrisBot";

// limits of the screen (px)
const int SCREEN_PLAYABLE_WIDTH = 352;
const int SCREEN_DIVIDER_BAR_WIDTH = 3;

// surfaces of the colored squares
const std::string SQUARE_COLORS_FILES[] = {"square_gray.png", "square_pink.png",
    "square_purple.png", "square_red.png", "square_yellow.png"};
SDL_Surface *SQUARES_SURFACES[] = {NULL, NULL, NULL, NULL, NULL};


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

    //loads the surfaces of the colored squares

    for (int i = 0; i < sizeof ( SQUARE_COLORS_FILES) / sizeof ( SQUARE_COLORS_FILES[ 0 ]); i++) {
        SQUARES_SURFACES[i] = load_image(SQUARE_COLORS_FILES[i]);
        if (SQUARES_SURFACES[i] == NULL)
            return 1;
    }


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


            applyGameScreen(screen, SCREEN_PLAYABLE_WIDTH);
            
            



            //If the user has Xed out the window
            if (event.type == SDL_QUIT) {class Square {
private:
    //collision box;
    //note: also handles the position on screen
    SDL_Rect box;
   
    // color of the square
    int square_color;

public:
    //Initializes the variables
    Square(int x, int y, int color){
    box.x = x;
    box.y = y;
    square_color = color;
}

    //Moves the square
    void move(int x, int y, SDL_Surface *screen, const int SCREEN_HEIGHT){
    box.x += x;
    box.y += y;
}

    //Shows the square on the screen
    void show(SDL_Surface *SQUARES_SURFACES[], SDL_Surface *screen){
    apply_surface(box.x, box.y, SQUARES_SURFACES[square_color], screen ); 
}
    
};


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

class Square {
private:
    //collision box;
    //note: also handles the position on screen
    SDL_Rect box;
   
    // color of the square
    int square_color;

public:
    //Initializes the variables
    Square(int x, int y, int color){
    box.x = x;
    box.y = y;
    square_color = color;
}

    //Moves the square
    void move(int x, int y, SDL_Surface *screen, const int SCREEN_HEIGHT){
    box.x += x;
    box.y += y;
}

    //Shows the square on the screen
    void show(SDL_Surface *SQUARES_SURFACES[], SDL_Surface *screen){
    apply_surface(box.x, box.y, SQUARES_SURFACES[square_color], screen ); 
}
    
};

