/* 
 * File:   Piece.cpp
 * Author: lucasvg
 * 
 * Created on November 11, 2013, 3:49 PM
 */

#include <iostream>

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

void Piece::deleteSquare(int i) {
    mySquares.erase(mySquares.begin() + i);
}

Square Piece::operator[](int i) {
    return mySquares[i];
}

void Piece::clean(){
    int amoutOfSquares = size();
    for(int i = 0; i<amoutOfSquares; i++){ 
        mySquares.erase(mySquares.begin() + i);
    }
}

int Piece::getPieceWidth(){
    if(size()==0)
        return 0;
    int firstX, lastX;
    firstX = mySquares[0].getx();
    lastX = mySquares[0].getx() + mySquares[0].getw();
    for(int i=1; i<size(); i++){
        if(firstX < mySquares[i].getx())
            firstX = mySquares[i].getx();
        if(lastX < mySquares[i].getx() + mySquares[i].getw())
            firstX = mySquares[i].getx() + mySquares[i].getw();
    }
    return lastX - firstX;
}