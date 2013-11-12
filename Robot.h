/* 
 * File:   Robot.h
 * Author: lucasvg
 *
 * Created on November 11, 2013, 3:59 PM
 */

#include <SDL/SDL.h>
#include "Piece.h"
#include "general_functions.h"

#ifndef ROBOT_H
#define	ROBOT_H

// the robot is the player
class Robot {
private:
    SDL_Rect box;
    int amoutOfShots;
    int score;
    int speed;
    SDL_Surface *surface;
public:

    Robot(const int ROBOT_WIDTH, const int ROBOT_HEIGHT, const int ROBOT_START_AMOUNT_OF_SHOTS, const int ROBOT_SPEED, SDL_Surface *robot_surface, const int SCREEN_PLAYABLE_WIDTH, const int SCREEN_HEIGHT);

    // the moves the robot only on axis x
    void move(int x, int SCREEN_PLAYABLE_WIDTH, Piece mainPiece);

    // if the left side of the robot is colliding with the square
    bool isCollidingLeft(Square square);

    // if the right side of the robot is colliding with the square
    bool isCollidingRight(Square square);

    // if the top of the robot is colliding with the piece
    bool isCollidingTop(Piece piece);

    // if the top of the robot is colliding with the square
    bool isCollidingTop(Square square);

    // prints the robot image on screen
    void show(SDL_Surface *screen);

    // handles events [ if the user pressed left or right ] ]
    void handleEvents(SDL_Event event ,int SCREEN_PLAYABLE_WIDTH, Piece mainPiece);
    
    // make a shot
    void shot(SDL_Surface *shot_surface);
    
};

#endif	/* ROBOT_H */

