/* 
 * File:   Robot.h
 * Author: lucasvg
 *
 * Created on November 11, 2013, 3:59 PM
 */

#include <SDL/SDL.h>
#include "Piece.h"
#include "general_functions.h"
#include "Shot.h"
#include "ShotsOnTheWorld.h"

#ifndef ROBOT_H
#define	ROBOT_H

// the robot is the player
class Robot {
private:
    // the collision box of the robot
    SDL_Rect box;
    
    // the amount of shots that the robot have
    int amountOfShots;
    
    // the score the robot accumulated
    int score;
    
    // the speed the robot moves (left | right)
    int speed;
    
    // the surface of the robot
    SDL_Surface *surface;
    
    // the position of the gun, relative to the robot body
    const int ROBOT_GUN_POSITION;
    
    // the width and height of the gun shot (will be used for the collision)
    int shot_width, shot_height;
    
    // the velocity of the gun shot [x and y axis]
    int shot_velx, shot_vely;
    
    // the surface of the gun shot
    SDL_Surface *shot_surface;
    
public:
    //constructor
    Robot(const int ROBOT_WIDTH, const int ROBOT_HEIGHT, const int ROBOT_START_AMOUNT_OF_SHOTS, int robot_gun_position,
            const int ROBOT_SPEED, SDL_Surface *robot_surface, const int SCREEN_PLAYABLE_WIDTH, const int SCREEN_HEIGHT, 
            int shot_width, int shot_height, int shot_velx, int shot_vely, SDL_Surface *shot_surface);

    // set the x position of the robot
    void setX(int x);
    
    // set the amount of shots
    void setAmountOfShots(const int ROBOT_START_AMOUNT_OF_SHOTS);

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
    void handleEvents(SDL_Event event ,int SCREEN_PLAYABLE_WIDTH, Piece mainPiece, ShotsOnTheWorld & shotsOnTheWorld, 
        Timer & delta_robot, const int ROBOT_SHOOT_DELAY, const int ROBOT_MOVE_DELAY);
    
    // gets the score
    int getScore();
    
    // set the score
    void setScore(int score);
    
};

#endif	/* ROBOT_H */

