// NOTES

//////////////////////////////////////////////
///////////// IMPORTANT !!! //////////////////
//////////////////////////////////////////////// DEFINITIONS


// remake the collision of the shot with the square

// creating a pause option

// already need to do
//      How can I make the connection between the robot and the shot? - forward declaration
//      Shot should have a reference to the robot who shot it
//      but if the robot file imports shot, how can the shot refer to the robot too
//      what would be the good approach here?

// verify leak situations
// get continuous key pressing to move the robot
// fix bug on side collision between the piece and robot
// the next piece display
// the score thing
// implement the serial.h + serial.cpp
// implement the rotate - rotozoomSurface faz isso pra voce http://www.ferzkopp.net/Software/SDL_gfx-2.0/Docs/html/_s_d_l__rotozoom_8h.html

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <vector>
#include <sstream>
#include "general_functions.h"
#include "iostream"
#include "Timer.h"
#include "Square.h"
#include "Piece.h"
#include "Robot.h"
#include "Shot.h"
#include "ShotsOnTheWorld.h"

// handle the game state of quit- do not change!
bool quit = false;

// handle the game state of gameOver - do not change!
bool gameOver = false;

// handle the game state of homeScreen - do not change!
bool homeScreen = true;

// stores the surface of the screen - this is what is being show to the user
SDL_Surface *screen = NULL;

// stores the background that will be shown all the time
SDL_Surface *background = NULL;

// filename of the background
const std::string BACKGROUND_FILE = "background.png";

// properties of the screen
// in pixels
const int SCREEN_WIDTH = 530;
// in pixels
const int SCREEN_HEIGHT = 400;
//bytes per pixel of the screen
const int SCREEN_BPP = 32;
// the title of the screen
const char *SCREEN_CAPTION = "TetrisBot";
//how many frames per second is the screen showing
const int FRAMES_PER_SECOND = 40;

//////////////////////////////////////////////
///////////// IMPORTANT !!! //////////////////
//////////////////////////////////////////////
// the screen is divided by the divider_bar in the sides - the playable and the status area
// the playable screen is the area where the game happens (where the robot and the pieces will be shown...)

// the width of the playable area
const int SCREEN_PLAYABLE_WIDTH = 304;

// the width of the divider_bar
const int SCREEN_DIVIDER_BAR_WIDTH = 3;

// stores the divider_bar surface
SDL_Surface *divider_bar = NULL;

// filename of the surface of the divider_bar
const std::string DIVIDER_BAR_FILE = "divider_bar.png";

// the width of the square   // shouldn't be const
const int SQUARE_WIDTH = 16;

// the height of the square  // shouldn't be const
const int SQUARE_HEIGHT = 16;

// the velocity of the square falls - in pixels   // shouldn't be const
const int SQUARE_SPEED = 3;

// the files names of the squares surfaces
const std::string SQUARE_COLORS_FILES[] = {"square_gray.png", "square_pink.png",
    "square_purple.png", "square_red.png", "square_yellow.png"};

// stores the surface of the squares - each color is one surface
SDL_Surface *squares_surfaces[] = {NULL, NULL, NULL, NULL, NULL};

// stores the robot
SDL_Surface *robot_surface = NULL;

// filename of the robot surface
const std::string ROBOT_SURFACE_FILE = "robot.png";

// width of the robot box collision   // shouldn't be const
const int ROBOT_WIDTH = 48;

// height of the robot box collision  // shouldn't be const
const int ROBOT_HEIGHT = 48;

// the amount of shots the robot starts with
const int ROBOT_START_AMOUNT_OF_SHOTS = 40;

// position of the gun relative to the position of the robot
int robot_gun_position = 16;

// the velocity of the robot moves [left || right]], in pixels  // shouldn't be const
const int ROBOT_SPEED = 4;

// the time (in milliseconds) of the delay of each movement
const int ROBOT__SHOOT_DELAY = 200;
const int ROBOT__MOVE_DELAY = 50;

// stores the shot surface
SDL_Surface *shot_surface = NULL;

// the width of the shot
int shot_width = 16;

// the height of the shot
int shot_height = 16;

// the shot horizontal velocity of the shot
int shot_velx = 0;

// the shot vertical velocity - it is negative because the shot goes from bottom to top
int shot_vely = -8;

// filename of the shot surface
const std::string SHOT_SURFACE_FILE = "shot.png";

// the path to the robot device
std::string robotDevicePath = "/dev/rfcomm0";

//the event handler
SDL_Event event;

bool firstTime;

// starts the SDL, loads all the files

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

    SDL_SetColorKey(robot_surface, SDL_SRCCOLORKEY, SDL_MapRGB(robot_surface->format, 255, 255, 255));

    if (robot_surface == NULL)
        return 1;

    shot_surface = load_image(SHOT_SURFACE_FILE);
    if (shot_surface == NULL)
        return 1;

    SDL_EnableUNICODE(SDL_ENABLE);

    return 0;
}

// frees the memory

void clean() {
    SDL_EnableUNICODE(SDL_DISABLE);

    for (int i = 0; i < sizeof ( SQUARE_COLORS_FILES) / sizeof ( SQUARE_COLORS_FILES[ 0 ]); i++)
        SDL_FreeSurface(squares_surfaces[i]);
    SDL_FreeSurface(background);
    SDL_FreeSurface(divider_bar);
    SDL_FreeSurface(robot_surface);
    SDL_FreeSurface(shot_surface);
    SDL_Quit();
}

// returns a random random piece

Piece createRandomPiece() {
    int type = rand() % 4;
    int color = rand() % 5;

    int randomLeftMargin = 0;
    int piece_width = 0;
    Piece myPiece;

    switch (type) {
        case 0:
            piece_width = 48 + SQUARE_WIDTH;
            randomLeftMargin = ((rand() % (SCREEN_PLAYABLE_WIDTH - piece_width)) % 16) * 16;
            myPiece.addSquare(Square(0 + randomLeftMargin, 0, color, SQUARE_WIDTH, SQUARE_HEIGHT));
            myPiece.addSquare(Square(16 + randomLeftMargin, 0, color, SQUARE_WIDTH, SQUARE_HEIGHT));
            myPiece.addSquare(Square(32 + randomLeftMargin, 0, color, SQUARE_WIDTH, SQUARE_HEIGHT));
            myPiece.addSquare(Square(48 + randomLeftMargin, 0, color, SQUARE_WIDTH, SQUARE_HEIGHT));
            myPiece.addSquare(Square(48 + randomLeftMargin, 16, color, SQUARE_WIDTH, SQUARE_HEIGHT));
            break;
        case 1:
            piece_width = 48 + SQUARE_WIDTH;
            randomLeftMargin = ((rand() % (SCREEN_PLAYABLE_WIDTH - piece_width)) % 16) * 16;
            myPiece.addSquare(Square(0 + randomLeftMargin, 0, color, SQUARE_WIDTH, SQUARE_HEIGHT));
            myPiece.addSquare(Square(16 + randomLeftMargin, 0, color, SQUARE_WIDTH, SQUARE_HEIGHT));
            myPiece.addSquare(Square(32 + randomLeftMargin, 0, color, SQUARE_WIDTH, SQUARE_HEIGHT));
            myPiece.addSquare(Square(32 + randomLeftMargin, 16, color, SQUARE_WIDTH, SQUARE_HEIGHT));
            myPiece.addSquare(Square(48 + randomLeftMargin, 0, color, SQUARE_WIDTH, SQUARE_HEIGHT));
            break;
        case 2:
            piece_width = 16 + SQUARE_WIDTH;
            randomLeftMargin = ((rand() % (SCREEN_PLAYABLE_WIDTH - piece_width)) % 16) * 16;
            myPiece.addSquare(Square(0 + randomLeftMargin, 0, color, SQUARE_WIDTH, SQUARE_HEIGHT));
            myPiece.addSquare(Square(00 + randomLeftMargin, 16, color, SQUARE_WIDTH, SQUARE_HEIGHT));
            myPiece.addSquare(Square(00 + randomLeftMargin, 32, color, SQUARE_WIDTH, SQUARE_HEIGHT));
            myPiece.addSquare(Square(00 + randomLeftMargin, 48, color, SQUARE_WIDTH, SQUARE_HEIGHT));
            myPiece.addSquare(Square(16 + randomLeftMargin, 48, color, SQUARE_WIDTH, SQUARE_HEIGHT));
            break;
        case 3:
            piece_width = 32 + SQUARE_WIDTH;
            randomLeftMargin = ((rand() % (SCREEN_PLAYABLE_WIDTH - piece_width)) % 16) * 16;
            myPiece.addSquare(Square(0 + randomLeftMargin, 0, color, SQUARE_WIDTH, SQUARE_HEIGHT));
            myPiece.addSquare(Square(00 + randomLeftMargin, 16, color, SQUARE_WIDTH, SQUARE_HEIGHT));
            myPiece.addSquare(Square(16 + randomLeftMargin, 16, color, SQUARE_WIDTH, SQUARE_HEIGHT));
            myPiece.addSquare(Square(00 + randomLeftMargin, 32, color, SQUARE_WIDTH, SQUARE_HEIGHT));
            myPiece.addSquare(Square(00 + randomLeftMargin, 48, color, SQUARE_WIDTH, SQUARE_HEIGHT));
            break;
    }

    // seed the rand function
    srand(clock());


    return myPiece;
}

// returns if it is gameOver

bool isGameOver(Robot robot, Piece piece, Piece mainPiece, const int SCREEN_HEIGHT) {

    if (robot.isColliding(piece) and !(piece.isColliding(mainPiece)))
        return true;

    //if mainPiece has the SCREEN_HEIGHT
    for (int i = 0; i < mainPiece.size(); i++) {
        if (mainPiece[i].gety() == 0)
            return true;
    }

    return false;
}

void handlePlayAgain(SDL_Event event, Robot & myRobot, ShotsOnTheWorld & ShotsOnTheWorld, bool & gameOver, bool & quit, Piece & mainPiece, Piece & dropPiece,
        const int SCREEN_PLAYABLE_WIDTH, const int ROBOT_WIDTH, const int ROBOT_START_AMOUNT_OF_SHOTS) {

    if (event.type == SDL_KEYDOWN)
        if (event.key.keysym.sym == SDLK_n) {
            quit = true;
        } else if (event.key.keysym.sym == SDLK_y) {
            myRobot.setX((SCREEN_PLAYABLE_WIDTH - ROBOT_WIDTH) / 2);
            myRobot.setAmountOfShots(ROBOT_START_AMOUNT_OF_SHOTS);

            ShotsOnTheWorld.clean();

            gameOver = false;

            dropPiece.clean();
            mainPiece.clean();
            dropPiece = createRandomPiece();

            myRobot.setScore(0);
        }
}

int main(int argc, char* args[]) {

    std::cout << isCollidingTest() << std::endl;

    if (init() == 1)
        return 1;

    firstTime = true;

    // dropPiece is the piece that is falling down
    Piece dropPiece;
    Piece nextDropPiece;
    dropPiece = createRandomPiece();
    nextDropPiece = createRandomPiece();

    // the mainPiece is compounded by the dropPieces that already fell
    Piece mainPiece;

    // instance of the robot - the player
    // if alter this declaration, update it at handlePlayAgain function
    Robot myRobot(ROBOT_WIDTH, ROBOT_HEIGHT, ROBOT_START_AMOUNT_OF_SHOTS, robot_gun_position, ROBOT_SPEED, robot_surface, SCREEN_PLAYABLE_WIDTH,
            SCREEN_HEIGHT, shot_width, shot_height, shot_velx, shot_vely, shot_surface);

    // this handles the shots on the screen
    // if alter this declaration, update it at handlePlayAgain function
    ShotsOnTheWorld shotsOnTetrisBot(SCREEN_PLAYABLE_WIDTH, SCREEN_HEIGHT);

    // handler of the robot_delay
    Timer delta_robot;
    delta_robot.start();

    // starts the clock "delta" and counter "frame" to cap the frames per second
    Timer delta;
    delta.start();
    long double frame = 0;

    applyHomeScreen(screen, background, robotDevicePath);

    //While the user hasn't quit
    while (quit == false) {

        //While there's events to handle
        while (SDL_PollEvent(&event)) {

            //if is at homeScreen
            if (homeScreen) {

                // handles the home screen window event
                handleHomeScreen(event, homeScreen, robotDevicePath);

                // this is to update the window. It is necessary now because the  user types the robot path device
                applyHomeScreen(screen, background, robotDevicePath);

                if (SDL_Flip(screen) == -1) {
                    return 1;
                }

                // if is not at gameOver == is at game playing mode
            } else if (gameOver) {
                //game over
                handlePlayAgain(event, myRobot, shotsOnTetrisBot, gameOver, quit, mainPiece, dropPiece, SCREEN_PLAYABLE_WIDTH,
                        ROBOT_WIDTH, ROBOT_START_AMOUNT_OF_SHOTS);
            }

            //If the user has quitted the window
            if (event.type == SDL_QUIT) {
                //Quit the program
                quit = true;
            }
        }

        // only pass of this part if is during the game
        if ((homeScreen) or (gameOver)) {
            continue;
        }

        if (firstTime == true) {
            myRobot.startPhisicalRobot(robotDevicePath.c_str());
            firstTime = false;
        }

        if (!homeScreen and !gameOver) {
            myRobot.handleEvents(event, SCREEN_PLAYABLE_WIDTH, mainPiece, shotsOnTetrisBot, delta_robot, ROBOT__SHOOT_DELAY, ROBOT__MOVE_DELAY);
        }

        applyGameScreen(background, divider_bar, screen, SCREEN_PLAYABLE_WIDTH, SCREEN_WIDTH, myRobot.getScore(), nextDropPiece, squares_surfaces);

        dropPiece.move(SQUARE_SPEED, SCREEN_HEIGHT, mainPiece);

        shotsOnTetrisBot.moveShots(dropPiece, mainPiece);

        // if the dropPiece was completely destroyed
        if (dropPiece.size() == 0) {
            dropPiece = nextDropPiece;
            nextDropPiece = createRandomPiece();
        }


        gameOver = isGameOver(myRobot, dropPiece, mainPiece, SCREEN_HEIGHT);

        if (gameOver)
            applyGameOverScreen(screen);


        dropPiece.show(squares_surfaces, screen);

        mainPiece.show(squares_surfaces, screen);

        shotsOnTetrisBot.show(screen);

        myRobot.show(screen);

        if (!dropPiece.move(SQUARE_SPEED, SCREEN_HEIGHT, mainPiece)) {
            mainPiece.addPiece(dropPiece);
            dropPiece = nextDropPiece;
            nextDropPiece = createRandomPiece();
        } else
            dropPiece.move(-SQUARE_SPEED, SCREEN_HEIGHT, mainPiece);

        //Update the screen
        if (SDL_Flip(screen) == -1) {
            return 1;
        }


        // this is to cap the frame rate at FRAMES_PER_SECOND limit
        frame++;
        if ((delta.get_ticks() < 1000 / FRAMES_PER_SECOND)) {
            //Sleep the remaining frame time
            SDL_Delay((1000 / FRAMES_PER_SECOND) - delta.get_ticks());
        }
        delta.start();

    }

    clean();
}