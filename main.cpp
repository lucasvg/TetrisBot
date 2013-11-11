// NOTES

// add the piece collision with the robot and the fire
// finish the createRandomPiece function
// verify leak situations
// get continuous key pressing to move the robot
// do the fire class

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
const int ROBOT_WIDTH = 48;
const int ROBOT_HEIGHT = 48;
const int ROBOT_START_AMOUNT_OF_SHOTS = 40;
const int ROBOT_SPEED = 16;

//GAME SETTINGS
const int SQUARE_SPEED = 4;

//the event handler
SDL_Event event;

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

    void move(int x, int SCREEN_PLAYABLE_WIDTH, Piece mainPiece) {
        // if the robot collides with the borders
        if ((box.x + x < 0) or (box.x + x + box.w > SCREEN_PLAYABLE_WIDTH))
            return;

        //if the robot collides with the mainPiece
        for (int i = 0; i < mainPiece.size(); i++)
            if (x > 0) {
                if (isCollidedRight(mainPiece[i]))
                    return;
            } else {
                if (isCollidedLeft(mainPiece[i]))
                    return;
            }

        box.x += x;
    };

    bool isCollidedLeft(Square square) {
        // if the square is on hight possible to be collided with the robot
        if (box.y <= square.gety())
            // is trying to move to left
            if (((box.x) == (square.getx() + square.getw())))
                return true;

        return false;
    }

    bool isCollidedRight(Square square) {
        // if the square is on hight possible to be collided with the robot
        if (box.y <= square.gety())
            // is trying to move to left
            if ((box.x + box.w) == (square.getx()))
                return true;

        return false;
    }

    bool isCollidedTop(Piece piece) {
        for (int i = 0; i < piece.size(); i++)
            if (isCollidedTop(piece[i]))
                return true;

        return false;
    }

    bool isCollidedTop(Square square) {
        if ((square.getx() >= box.x) and square.getx() < box.x + box.w)
            if (square.gety() + square.geth() >= box.y)
                return true;

        return false;
    }

    void show(SDL_Surface *screen) {
        apply_surface(box.x, box.y, surface, screen);
    };

    void handleEvents(int SCREEN_PLAYABLE_WIDTH, Piece mainPiece) {
        if (event.type == SDL_KEYDOWN)
            if (event.key.keysym.sym == SDLK_LEFT)
                move(speed * (-1), SCREEN_PLAYABLE_WIDTH, mainPiece);
            else if (event.key.keysym.sym == SDLK_RIGHT)
                move(speed, SCREEN_PLAYABLE_WIDTH, mainPiece);
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
    
    if (robot.isCollidedTop(piece))
        return true;
    
    //if mainPiece has the SCREEN_HEIGHT
    for(int i = 0; i<mainPiece.size(); i++){
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

            if (homeScreen) {
                //is at homeScreen
                //verify if space was pressed
                handleHomeScreen();
            } else if (!gameOver) {
                //is during the game
                myRobot.handleEvents(SCREEN_PLAYABLE_WIDTH, mainPiece);
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

        applyGameScreen(screen, SCREEN_PLAYABLE_WIDTH);
        
        gameOver = isGameOver(myRobot, dropPiece, mainPiece, SCREEN_HEIGHT);
        if (gameOver)
            applyGameOverScreen(screen);
        
        dropPiece.move(SQUARE_SPEED, SCREEN_HEIGHT, mainPiece);
        dropPiece.show(squares_surfaces, screen);

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

