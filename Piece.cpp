/* 
 * File:   Piece.cpp
 * Author: lucasvg
 * 
 * Created on November 11, 2013, 3:49 PM
 */

#include "Piece.h"

void Piece::addSquare(Square AddedSquare) {
    mySquares.push_back(AddedSquare);
}

bool Piece::move(int y, const int SCREEN_HEIGHT, Piece mainPiece) {
    if (isColliding(SCREEN_HEIGHT))
        return false;
    if (isColliding(mainPiece))
        return false;

    for (int i = 0; i < mySquares.size(); i++)
        mySquares[i].move(y, SCREEN_HEIGHT);
}

bool Piece::addPiece(Piece otherPiece) {
    for (int i = 0; i < otherPiece.size(); i++) {
        mySquares.push_back(otherPiece[i]);
    }
};

void Piece::show(SDL_Surface *squares_surfaces[], SDL_Surface *screen) {
    for (int i = 0; i < mySquares.size(); i++) {
        mySquares[i].show(squares_surfaces, screen);
    }
};

bool Piece::isColliding(int SCREEN_HEIGHT) {
    for (int i = 0; i < mySquares.size(); i++)
        if (mySquares[i].isColliding(SCREEN_HEIGHT))
            return true;

    return false;
}

bool Piece::isColliding(Piece mainPiece) {
    for (int i = 0; i < mySquares.size(); i++) {
        for (int j = 0; j < mainPiece.size(); j++) {
            if (mySquares[i].isColliding(mainPiece[j]))
                return true;
        }
    }
    return false;
}

int Piece::size() {
    return mySquares.size();
}

Square Piece::operator[](int i) {
    return mySquares[i];
}

