// NOTES

//add the piece collision with the robot and the fire
// finish the createRandomPiece function
// verify leak situations
// get continuous key pressing to move the robot

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
const int SCREEN_PLAYABLE_WIDTH = 304;
const int SCREEN_DIVIDER_BAR_WIDTH = 3;

// surfaces of the colored squares
const int SQUARE_WIDTH = 16;
const int SQUARE_HEIGHT = 16;
const std::string SQUARE_COLORS_FILES[] = {"square_gray.png", "square_pink.png",
    "square_purple.png", "square_red.png", "square_yellow.png"};
SDL_Surface *squares_surfaces[] = {NULL, NULL, NULL, NULL, NULL};

//the robot
SDL_Surface *robot_surface = NULL;
const int ROBOT_WIDTH = 48;
const int ROBOT_HEIGHT = 48;
const int ROBOT_START_AMOUNT_OF_SHOTS = 40;
const int ROBOT_SPEED = 16;

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
        return (box.y + box.h >= SCREEN_HEIGHT - 1);
    }

    bool isCollided(Square otherSquare) {
        if (box.x == otherSquare.getx())
            if (box.y + box.h >= otherSquare.gety())
                return true;
        return false;
    }

    //Shows the square on the screen

    int getx() {
        return box.x;
    }

    int gety() {
        return box.y;
    }

    int getw() {
        return box.w;
    }

    int geth() {
        return box.h;
    }

    void show(SDL_Surface *squares_surfaces[], SDL_Surface *screen) {
        apply_surface(box.x, box.y, squares_surfaces[square_color], screen);
    }

};

class Piece {
private:
    std::vector<Square> mySquares;
public:

    void addSquare(Square AddedSquare) {
        mySquares.push_back(AddedSquare);
    }

    bool move(int y, const int SCREEN_HEIGHT, Piece mainPiece) {
        if (isCollided(SCREEN_HEIGHT))
            return false;
        if (isCollided(mainPiece))
            return false;

        for (int i = 0; i < mySquares.size(); i++)
            mySquares[i].move(y, SCREEN_HEIGHT);
    }

    // aggregates the otherPiece to this piece

    bool addPiece(Piece otherPiece) {
        for (int i = 0; i < otherPiece.size(); i++) {
            mySquares.push_back(otherPiece[i]);
        }
    };

    void show(SDL_Surface *squares_surfaces[], SDL_Surface *screen) {
        for (int i = 0; i < mySquares.size(); i++) {
            mySquares[i].show(squares_surfaces, screen);
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
        for (int i = 0; i < mySquares.size(); i++) {
            for (int j = 0; j < mainPiece.size(); j++) {
                if (mySquares[i].isCollided(mainPiece[j]))
                    return true;
            }
        }
        return false;
    }

    int size() {
        return mySquares.size();
    }

    Square operator[](int i) {
        return mySquares[i];
    }

};

class Robot {
private:
    SDL_Rect box;
    int amoutOfShots;
    int score;
    int speed;
    SDL_Surface *surface;
public:

    Robot(const int ROBOT_WIDTH, const int ROBOT_HEIGHT, const int ROBOT_START_AMOUNT_OF_SHOTS, const int ROBOT_SPEED, SDL_Surface *robot_surface) {
        box.x = (SCREEN_PLAYABLE_WIDTH - ROBOT_WIDTH) / 2;
        box.y = SCREEN_HEIGHT - ROBOT_HEIGHT;
        box.w = ROBOT_WIDTH;
        box.h = ROBOT_HEIGHT;
        speed = ROBOT_SPEED;

        score = 0;
        amoutOfShots = ROBOT_START_AMOUNT_OF_SHOTS;
        surface = robot_surface;
    };

    void fire();

    bool move(int x, int SCREEN_WIDTH, Piece mainPiece) {
        box.x += x;
    };

    bool isCollided(Square square);

    void show(SDL_Surface *screen) {
        apply_surface(box.x, box.y, surface, screen);
    };

    void handleEvents(int SCREEN_WIDTH, Piece mainPiece) {
        if (event.type == SDL_KEYDOWN)
            if (event.key.keysym.sym == SDLK_LEFT)
                move(speed * (-1), SCREEN_WIDTH, mainPiece);
            else if (event.key.keysym.sym == SDLK_RIGHT)
                move(speed, SCREEN_WIDTH, mainPiece);
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
        squares_surfaces[i] = load_image(SQUARE_COLORS_FILES[i]);
        if (squares_surfaces[i] == NULL)
            return 1;
    }

    robot_surface = load_image("robot.png");
    if (robot_surface == NULL)
        return 1;
    
    // seed the rand function
    srand(clock());

    return 0;
}

void clean() {
    for (int i = 0; i < sizeof ( SQUARE_COLORS_FILES) / sizeof ( SQUARE_COLORS_FILES[ 0 ]); i++)
        SDL_FreeSurface(squares_surfaces[i]);
    SDL_FreeSurface(robot_surface);
    SDL_Quit();
}

void handleHomeScreen() {
    if (homeScreen)
        if (event.type == SDL_KEYDOWN)
            if (event.key.keysym.sym == SDLK_SPACE)
                homeScreen = false;
}

Piece createRandomPiece() {
    int type = rand() % 2;
    int color = rand() % 5;

    int randomLeftMargin = 0;
    int piece_width = 0;
    Piece myPiece;

    int firstPieceWidth = 48 + SQUARE_WIDTH;
    int firstPiece[] = {
        0, 0,
        16, 0,
        32, 48,
        48, 16
    };

    int secondPieceWidth = 48 + SQUARE_WIDTH;
    int secondPiece[] = {
        0, 0,
        16, 0,
        32, 0,
        48, 0,
        48, 16
    };

    int thirdPieceWidth = 16 + SQUARE_WIDTH;
    int thirdPiece[] = {
        0, 0,
        0, 16,
        0, 32,
        0, 48,
        16, 48
    };

    int fourthPieceWidth = 32 + SQUARE_WIDTH;
    int fourfhPiece[] = {
        0, 0,
        0, 16,
        16, 16,
        0, 32,
        0, 48
    };

    piece_width = (48 + 16);

    // %16 *16 cast the result to be a multiple of 16.
    randomLeftMargin = ((rand() % (SCREEN_PLAYABLE_WIDTH - piece_width)) % 16) * 16;
    Square mySquare(0 + randomLeftMargin, 0, color);
    Square mySquare1(16 + randomLeftMargin, 0, color);
    Square mySquare2(32 + randomLeftMargin, 0, color);
    Square mySquare3(48 + randomLeftMargin, 0, color);
    Square mySquare4(48 + randomLeftMargin, 16, color);
    myPiece.addSquare(mySquare);
    myPiece.addSquare(mySquare1);
    myPiece.addSquare(mySquare2);
    myPiece.addSquare(mySquare3);
    myPiece.addSquare(mySquare4);
    return myPiece;
}

int main(int argc, char* args[]) {

    if (init() == 1)
        return 1;


    Piece dropPiece;
    dropPiece = createRandomPiece();

    Piece mainPiece;

    Robot myRobot(ROBOT_WIDTH, ROBOT_HEIGHT, ROBOT_START_AMOUNT_OF_SHOTS, ROBOT_SPEED, robot_surface);

    if (homeScreen)
        applyHomeScreen(screen);

    // starts the clock to cap the frames per second
    Timer delta;
    delta.start();
    long double frame = 0;

    //While the user hasn't quit
    while (quit == false) {

        //While there's events to handle
        while (SDL_PollEvent(&event)) {

            //verify if space was pressed
            handleHomeScreen();

            if (!homeScreen)
                myRobot.handleEvents(SCREEN_WIDTH, mainPiece);

                    
            //If the user has quitted the window
            if (event.type == SDL_QUIT) {
                //Quit the program
                quit = true;
            }
        }

        if (homeScreen)
            continue;

        applyGameScreen(screen, SCREEN_PLAYABLE_WIDTH);

        dropPiece.show(squares_surfaces, screen);
        dropPiece.move(SQUARE_SPEED, SCREEN_HEIGHT, mainPiece);

        mainPiece.show(squares_surfaces, screen);

        myRobot.show(screen);

        if (dropPiece.isCollided(SCREEN_HEIGHT) or dropPiece.isCollided(mainPiece)) {
            mainPiece.addPiece(dropPiece);
            //
            // need to verify if I need to delete the dropPiece squares here.
            // I don't think so, because mainPiece is referring to them.
            dropPiece = createRandomPiece();
        }

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