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

/*
 *  this is a square. It compounds the piece
*/
class Square {
private:
    //collision box;
    //note: also handles the position on screen
    SDL_Rect box;

    //color of the square
    int square_color;

public:
    //Initializes the variables
   
    Square(int x, int y, int color, const int SQUARE_WIDTH, const int SQUARE_HEIGHT);

    //Moves the square, return true if it moved (was not collided)
    void move(int y, const int SCREEN_HEIGHT);
    
    // moves the square horizontal (if it can't move total, will move the max it can)
    bool moveHorizontal(int x, const int SCREEN_PLAYABLE_WIDTH);

    // if the square is colliding with the bottom of the screen
    bool isColliding(int SCREEN_HEIGHT);

    // if the square is colliding of other square
    bool isColliding(Square otherSquare);

    // returns the x postion of the square
    int getx();

    // returns the y postion of the square
    int gety();

    // returns the width of the square
    int getw();

    // returns the height of the square
    int geth();

    //Shows the square on the screen
    void show(SDL_Surface *squares_surfaces[], SDL_Surface *screen);

    int getSquareColor();
};

#endif	/* SQUARE_H */

