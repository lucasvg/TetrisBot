/* 
 * File:   Piece.h
 * Author: lucasvg
 *
 * Created on November 11, 2013, 3:49 PM
 */

#include <vector>
#include <SDL/SDL.h>
#include "Square.h"

#ifndef PIECE_H
#define	PIECE_H

class Piece {
private:
    std::vector<Square> mySquares;
public:

    void addSquare(Square AddedSquare);

    bool move(int y, const int SCREEN_HEIGHT, Piece mainPiece);

    // aggregates the otherPiece to this piece

    bool addPiece(Piece otherPiece);

    void show(SDL_Surface *squares_surfaces[], SDL_Surface *screen);

    //verify if it collided with bottom

    bool isColliding(int SCREEN_HEIGHT);

    //verify if it collides with the main piece

    bool isColliding(Piece mainPiece);

    int size();

    Square operator[](int i);

};

#endif	/* PIECE_H */

