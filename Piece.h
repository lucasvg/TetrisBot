/* 
 * File:   Piece.h
 * Author: lucasvg
 *
 * Created on November 11, 2013, 3:49 PM
 */

#include <SDL/SDL.h>
#include "Square.h"
#include <vector>

#ifndef PIECE_H
#define	PIECE_H

// a piece is a composed by various squares
class Piece {
private:
    std::vector<Square> mySquares;
public:

    // adds a square to the piece
    void addSquare(Square AddedSquare);

    // moves the piece (all the squares)
    bool move(int y, const int SCREEN_HEIGHT, Piece mainPiece);

    // aggregates the otherPiece to this piece
    bool addPiece(Piece otherPiece);

    // prints the piece on the screen
    void show(SDL_Surface *squares_surfaces[], SDL_Surface *screen);

    // if it collided with bottom of the screen
    bool isColliding(int SCREEN_HEIGHT);

    //verify if it collides with the main piece
    bool isColliding(Piece mainPiece);

    // returns the number of square
    int size();
    
    void deleteSquare(int i);

    // returns the square of index i
    Square operator[](int i);

};

#endif	/* PIECE_H */

