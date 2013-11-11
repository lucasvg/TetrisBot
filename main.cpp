// NOTES

// finish the createRandomPiece function
// verify leak situations
// get continuous key pressing to move the robot
// fix bug on side collision between the piece and robot
// make the square destructor

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <vector>
#include "general_functions.h"
#include "iostream"
#include "Timer.h"
#include "Square.h"
#include "Piece.h"
#include "Robot.h"
#include "Shot.h"

// handle the exit of the program
bool quit = false;

bool gameOver = false;

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
const std::string ROBOT_SURFACE_FILE = "robot.png";

const int ROBOT_WIDTH = 48;
const int ROBOT_HEIGHT = 48;
const int ROBOT_START_AMOUNT_OF_SHOTS = 40;
const int ROBOT_SPEED = 16;

//GAME SETTINGS
const int SQUARE_SPEED = 4;

SDL_Surface *background = NULL;
const std::string BACKGROUND_FILE = "background.png";

SDL_Surface *divider_bar = NULL;
const std::string DIVIDER_BAR_FILE = "divider_bar.png";

// shot
SDL_Surface *shot_surface = NULL;
const std::string SHOT_SURFACE_FILE = "shot.png";

//the event handler
SDL_Event event;

int init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return 1;

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    if (screen == NULL)
        return 1;

    SDL_WM_SetCaption(SCREEN_CAPTION, NULL);

    background = load_image(BACKGROUND_FILE);
    if (background == NULL)
        return 1;
    
    divider_bar = load_image(DIVIDER_BAR_FILE);
    if (divider_bar == NULL)
        return 1;
    
    //loads the surfaces of the colored squares
    for (int i = 0; i < sizeof ( SQUARE_COLORS_FILES) / sizeof ( SQUARE_COLORS_FILES[ 0 ]); i++) {
        squares_surfaces[i] = load_image(SQUARE_COLORS_FILES[i]);
        if (squares_surfaces[i] == NULL)
            return 1;
    }

    robot_surface = load_image(ROBOT_SURFACE_FILE);
    if (robot_surface == NULL)
        return 1;
    
    shot_surface = load_image(SHOT_SURFACE_FILE);
    if (shot_surface == NULL)
        return 1;
    
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

    // seed the rand function
    srand(clock());

    // %16 *16 cast the result to be a multiple of 16.
    randomLeftMargin = ((rand() % (SCREEN_PLAYABLE_WIDTH - piece_width)) % 16) * 16;
    Square mySquare(0 + randomLeftMargin, 0, color, SQUARE_WIDTH, SQUARE_HEIGHT);
    Square mySquare1(16 + randomLeftMargin, 0, color, SQUARE_WIDTH, SQUARE_HEIGHT);
    Square mySquare2(32 + randomLeftMargin, 0, color, SQUARE_WIDTH, SQUARE_HEIGHT);
    Square mySquare3(48 + randomLeftMargin, 0, color, SQUARE_WIDTH, SQUARE_HEIGHT);
    Square mySquare4(48 + randomLeftMargin, 16, color, SQUARE_WIDTH, SQUARE_HEIGHT);
    myPiece.addSquare(mySquare);
    myPiece.addSquare(mySquare1);
    myPiece.addSquare(mySquare2);
    myPiece.addSquare(mySquare3);
    myPiece.addSquare(mySquare4);
    return myPiece;
}

bool isGameOver(Robot robot, Piece piece, Piece mainPiece, const int SCREEN_HEIGHT) {

    if (robot.isCollidingTop(piece) and !(piece.isColliding(mainPiece)))
        return true;

    //if mainPiece has the SCREEN_HEIGHT
    for (int i = 0; i < mainPiece.size(); i++) {
        if (mainPiece[i].gety() == 0)
            return true;
    }

    return false;
}

int main(int argc, char* args[]) {

    if (init() == 1)
        return 1;


    Piece dropPiece;
    dropPiece = createRandomPiece();

    Piece mainPiece;

    Robot myRobot(ROBOT_WIDTH, ROBOT_HEIGHT, ROBOT_START_AMOUNT_OF_SHOTS, ROBOT_SPEED, robot_surface, SCREEN_PLAYABLE_WIDTH, SCREEN_HEIGHT);

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

            if (homeScreen) {
                //is at homeScreen
                //verify if space was pressed
                handleHomeScreen();
            } else if (!gameOver) {
                //is during the game
                myRobot.handleEvents(event, SCREEN_PLAYABLE_WIDTH, mainPiece);
            } else {
                //game over
            }

            //If the user has quitted the window
            if (event.type == SDL_QUIT) {
                //Quit the program
                quit = true;
            }
        }

        if ((homeScreen) or (gameOver)) {
            continue;

        }

        applyGameScreen(background, divider_bar , screen, SCREEN_PLAYABLE_WIDTH);
        
        // the game over function needs to be placed after it was checked if the dropPiece is colliding with the mainPiece (in the loop)
        // this ensures the piece will first collide with the mainPiece, and then will not collide with the robot,
        // if robot and mainPiece are at the same hight
        
        dropPiece.move(SQUARE_SPEED, SCREEN_HEIGHT, mainPiece);

        gameOver = isGameOver(myRobot, dropPiece, mainPiece, SCREEN_HEIGHT);
        if (gameOver)
            applyGameOverScreen(screen);
        
        
        dropPiece.show(squares_surfaces, screen);

        mainPiece.show(squares_surfaces, screen);

        myRobot.show(screen);

        if (dropPiece.isColliding(SCREEN_HEIGHT) or dropPiece.isColliding(mainPiece)) {
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

