/* 
 * File:   Square.h
 * Author: lucasvg
 *
 * Created on November 11, 2013, 3:39 PM
 * 
 * a square is a part of the piece
 */

#include <SDL/SDL.h>

#ifndef SQUARE_H
#define	SQUARE_H

class Square {
private:
    //collision box;
    //note: also handles the position on screen
    SDL_Rect box;

    // color of the square
    int square_color;

public:
    //Initializes the variables

    Square(int x, int y, int color, const int SQUARE_WIDTH, const int SQUARE_HEIGHT);

    //Moves the square, return true if it moved (was not collided)

    bool move(int y, const int SCREEN_HEIGHT);

    bool isColliding(int SCREEN_HEIGHT);

    bool isColliding(Square otherSquare);

    int getx();

    int gety();

    int getw();

    int geth();

    //Shows the square on the screen
    void show(SDL_Surface *squares_surfaces[], SDL_Surface *screen);

};

#endif	/* SQUARE_H */

