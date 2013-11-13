/* 
 * File:   Robot.cpp
 * Author: lucasvg
 * 
 * Created on November 11, 2013, 3:59 PM
 */

#include <iostream>

#include "Robot.h"
#include "ShotsOnTheWorld.h"

Robot::Robot(const int ROBOT_WIDTH, const int ROBOT_HEIGHT, const int ROBOT_START_AMOUNT_OF_SHOTS,
        const int ROBOT_SPEED, SDL_Surface *robot_surface, const int SCREEN_PLAYABLE_WIDTH, const int SCREEN_HEIGHT, 
         int shot_width, int shot_height, int shot_velx, int shot_vely, SDL_Surface *shot_surface){
    
    box.x = (SCREEN_PLAYABLE_WIDTH - ROBOT_WIDTH) / 2;
    box.y = SCREEN_HEIGHT - ROBOT_HEIGHT;
    box.w = ROBOT_WIDTH;
    box.h = ROBOT_HEIGHT;
    speed = ROBOT_SPEED;
    
    this->shot_width = shot_width;
    this->shot_height = shot_height;
    this->shot_velx = shot_velx;
    this->shot_vely = shot_vely;
    this->shot_surface = shot_surface;
            
    score = 0;
    amoutOfShots = ROBOT_START_AMOUNT_OF_SHOTS;
    surface = robot_surface;
};

void Robot::move(int x, int SCREEN_PLAYABLE_WIDTH, Piece mainPiece) {
    // if the robot collides with the borders
    if ((box.x + x < 0) or (box.x + x + box.w > SCREEN_PLAYABLE_WIDTH))
        return;

    //if the robot collides with the mainPiece
    for (int i = 0; i < mainPiece.size(); i++)
        if (x > 0) {
            if (isCollidingRight(mainPiece[i]))
                return;
        } else {
            if (isCollidingLeft(mainPiece[i]))
                return;
        }

    box.x += x;
};

bool Robot::isCollidingLeft(Square square) {
    // if the square is on hight possible to be collided with the robot
    if (box.y <= square.gety())
        // is trying to move to left
        if (((box.x) == (square.getx() + square.getw())))
            return true;

    return false;
}

bool Robot::isCollidingRight(Square square) {
    // if the square is on hight possible to be collided with the robot
    if (box.y <= square.gety())
        // is trying to move to left
        if ((box.x + box.w) == (square.getx()))
            return true;

    return false;
}

bool Robot::isCollidingTop(Piece piece) {
    for (int i = 0; i < piece.size(); i++)
        if (isCollidingTop(piece[i]))
            return true;

    return false;
}

bool Robot::isCollidingTop(Square square) {
    if ((square.getx() >= box.x) and square.getx() < box.x + box.w)
        if (square.gety() + square.geth() >= box.y)
            return true;

    return false;
}

void Robot::show(SDL_Surface *screen) {
    apply_surface(box.x, box.y, surface, screen);
};

void Robot::handleEvents(SDL_Event event, int SCREEN_PLAYABLE_WIDTH, Piece mainPiece, ShotsOnTheWorld & shotsOnTheWorld) {
    if (event.type == SDL_KEYDOWN)
        if (event.key.keysym.sym == SDLK_LEFT)
            move(speed * (-1), SCREEN_PLAYABLE_WIDTH, mainPiece);
        else if (event.key.keysym.sym == SDLK_RIGHT)
            move(speed, SCREEN_PLAYABLE_WIDTH, mainPiece);
        else if (event.key.keysym.sym == SDLK_SPACE)
            // shoot
            shotsOnTheWorld.newShot(Shot(box.x, box.y, shot_width, shot_height, shot_velx, shot_vely, shot_surface));
            
}