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

class Robot {
private:
    SDL_Rect box;
    int amoutOfShots;
    int score;
    int speed;
    SDL_Surface *surface;
public:

    Robot(const int ROBOT_WIDTH, const int ROBOT_HEIGHT, const int ROBOT_START_AMOUNT_OF_SHOTS, const int ROBOT_SPEED, SDL_Surface *robot_surface, const int SCREEN_PLAYABLE_WIDTH, const int SCREEN_HEIGHT);

    void move(int x, int SCREEN_PLAYABLE_WIDTH, Piece mainPiece);

    bool isCollidedLeft(Square square);

    bool isCollidedRight(Square square);

    bool isCollidedTop(Piece piece);

    bool isCollidedTop(Square square);

    void show(SDL_Surface *screen);

    void handleEvents(SDL_Event event ,int SCREEN_PLAYABLE_WIDTH, Piece mainPiece);
};

#endif	/* ROBOT_H */

