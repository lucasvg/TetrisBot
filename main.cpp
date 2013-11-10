// NOTES

//add the piece colision with the robot and the fire

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <vector>
#include "general_functions.h"
#include "iostream"

// handle the exit of the program
bool quit = false;

// to show the homeScreen
bool homeScreen = true;

// the screen
SDL_Surface *screen = NULL;
const int SCREEN_WIDTH = 530;
const int SCREEN_HEIGHT = 400;
const int SCREEN_BPP = 32;
const char *SCREEN_CAPTION = "TetrisBot";
const int FRAMES_PER_SECOND = 40;

// limits of the screen (px)
const int SCREEN_PLAYABLE_WIDTH = 300;
const int SCREEN_DIVIDER_BAR_WIDTH = 3;

// surfaces of the colored squares
const int SQUARE_WIDTH = 16;
const int SQUARE_HEIGHT = 16;
const std::string SQUARE_COLORS_FILES[] = {"square_gray.png", "square_pink.png",
    "square_purple.png", "square_red.png", "square_yellow.png"};
SDL_Surface *SQUARES_SURFACES[] = {NULL, NULL, NULL, NULL, NULL};

//GAME SETTINGS
const int SQUARE_SPEED = 4;

//the event handler
SDL_Event event;

// Timer is the clock handler

class Timer {
private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};

// a square is a part of the piece

class Square {
private:
    //collision box;
    //note: also handles the position on screen
    SDL_Rect box;

    // color of the square
    int square_color;

public:
    //Initializes the variables

    Square(int x, int y, int color) {
        box.x = x;
        box.y = y;
        square_color = color;
        box.w = SQUARE_WIDTH;
        box.h = SQUARE_HEIGHT;
    }

    //Moves the square, return true if it moved (was not collided)

    bool move(int y, const int SCREEN_HEIGHT) {
        if (box.y + box.h + y >= SCREEN_HEIGHT) {
            for (int i = y; i > 0; i--) {
                if (box.y + box.h + y >= SCREEN_HEIGHT) {
                    y -= 1;
                } else {
                    break;
                }
            }
        }
        if (y == 0) return false;

        box.y += y;
        return true;
    }

    bool isCollided(int SCREEN_HEIGHT) {
        //the minus one is because the square colides when it is 1 pixel far
        return (box.y + box.h >= SCREEN_HEIGHT-1);
    }

    //Shows the square on the screen

    void show(SDL_Surface *SQUARES_SURFACES[], SDL_Surface *screen) {
        apply_surface(box.x, box.y, SQUARES_SURFACES[square_color], screen);
    }

};

class Piece {
private:
    std::vector<Square> mySquares;
public:
    
    void addSquare(Square AddedSquare){
        mySquares.push_back(AddedSquare);
    }

    bool move(int y, const int SCREEN_HEIGHT) {
        if (isCollided(SCREEN_HEIGHT))
            return false;

        for (int i = 0; i < mySquares.size(); i++)
            mySquares[i].move(y, SCREEN_HEIGHT);
    }

    // aggregates the otherPiece to this piece
    bool addPiece(Piece otherPiece){
        for(int i=0; i < otherPiece.size(); i++){
            mySquares.push_back(otherPiece[i]);
        }
    };

    void show(SDL_Surface *SQUARES_SURFACES[], SDL_Surface *screen){
        for(int i=0; i<mySquares.size(); i++){
            mySquares[i].show(SQUARES_SURFACES, screen);
        }
    };

    //verify if it collided with bottom

    bool isCollided(int SCREEN_HEIGHT) {
        for (int i = 0; i < mySquares.size(); i++) 
            if (mySquares[i].isCollided(SCREEN_HEIGHT))
                return true;
        
        return false;
    }

    //verify if it collides with the main piece

    bool isCollided(Piece mainPiece) {

    }
    
    int size(){
        return mySquares.size();
    }

};

int init() {
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
    
    // seed the rand function
    srand(clock());
    
    return 0;
}

void clean() {
    SDL_FreeSurface(screen);
    for (int i = 0; i < sizeof ( SQUARE_COLORS_FILES) / sizeof ( SQUARE_COLORS_FILES[ 0 ]); i++)
        SDL_FreeSurface(SQUARES_SURFACES[i]);
    SDL_Quit();
}

void handleHomeScreen() {
    if (homeScreen)
        if (event.type == SDL_KEYDOWN)
            if (event.key.keysym.sym == SDLK_SPACE)
                homeScreen = false;
}

void createFirstPiece(Piece & myPiece){
    int color = rand() %5;
    Square mySquare(0, 0, color);
    Square mySquare1(16, 0, color);
    Square mySquare2(16+16, 0, color);
    Square mySquare3(16+16+16, 0, color);
    Square mySquare4(16+16+16, 16, color);
    myPiece.addSquare(mySquare);
    myPiece.addSquare(mySquare1);
    myPiece.addSquare(mySquare2);
    myPiece.addSquare(mySquare3);
    myPiece.addSquare(mySquare4);
}

void createSecondPiece(Piece & myPiece){
    int color = rand()%5;
    Square mySquare(0, 0, color);
    Square mySquare1(16, 0, color);
    Square mySquare2(16+16, 0, color);
    Square mySquare3(16+16+16, 0, color);
    Square mySquare4(16+16+16, 16, color);
    myPiece.addSquare(mySquare);
    myPiece.addSquare(mySquare1);
    myPiece.addSquare(mySquare2);
    myPiece.addSquare(mySquare3);
    myPiece.addSquare(mySquare4);
}

int main(int argc, char* args[]) {

    if (init() == 1)
        return 1;


    Piece myPiece;
    createFirstPiece(myPiece);

    if (homeScreen)
        applyHomeScreen(screen);

    // starts the clock to cap the fps
    Timer delta;
    delta.start();
    long double frame = 0;

    //While the user hasn't quit
    while (quit == false) {

        //While there's events to handle
        while (SDL_PollEvent(&event)) {

            //verify if space was pressed
            handleHomeScreen();

            //If the user has quitted the window
            if (event.type == SDL_QUIT) {
                //Quit the program
                quit = true;
            }
        }

        if (homeScreen)
            continue;

        applyGameScreen(screen, SCREEN_PLAYABLE_WIDTH);

        myPiece.show(SQUARES_SURFACES, screen);
        
        myPiece.move(SQUARE_SPEED, SCREEN_HEIGHT);
        
        //Update the screen
        if (SDL_Flip(screen) == -1) {
            return 1;
        }

        //Increment the frame counter
        frame++;

        //If we want to cap the frame rate
        if ((delta.get_ticks() < 1000 / FRAMES_PER_SECOND)) {
            //Sleep the remaining frame time
            SDL_Delay((1000 / FRAMES_PER_SECOND) - delta.get_ticks());
        }

        //Restart delta timer
        delta.start();

    }

    clean();
}

Timer::Timer() {
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start() {
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

void Timer::stop() {
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void Timer::pause() {
    //If the timer is running and isn't already paused
    if ((started == true) && (paused == false)) {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause() {
    //If the timer is paused
    if (paused == true) {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::get_ticks() {
    //If the timer is running
    if (started == true) {
        //If the timer is paused
        if (paused == true) {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        } else {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::is_started() {
    return started;
}

bool Timer::is_paused() {
    return paused;
}