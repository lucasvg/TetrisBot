/* 
 * File:   Shot.h
 * Author: lucasvg
 *
 * Created on November 12, 2013, 6:14 PM
 */

#include <SDL/SDL.h>
#include "Piece.h"
#include "general_functions.h"

#ifndef SHOT_H
#define	SHOT_H

class Robot;

// this is a unique shot
class Shot {
private:
    // the collision box
    SDL_Rect box;
    
    // the velocity of the shot [x and y axis]]
    int velx, vely;
    
    // the surface of the shot
    SDL_Surface *surface;

    // a reference to who shoot this shot
    Robot * whoShoot;
    
public:
    // constructor
    Shot(int x, int y, int w, int h, int velx, int vely, SDL_Surface* surface, Robot *whoShoot);

    // moves the shot on the screen (verifies if it is collided with the piece, mainPiece or the Screen_height)
    void move(Piece & piece, Piece & mainPiece, const int SCREEN_HEIGHT);

    // if the shot will collid with square after moving ("x", "y")
    bool willCollid(Square square, int x, int y);

    // shows the shot on the screen
    void show(SDL_Surface *screen);
    
    // returns x position
    int getx();
    
    // returns y position
    int gety();
};

#endif	/* SHOT_H */

