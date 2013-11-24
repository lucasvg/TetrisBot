/* 
 * File:   Shot.cpp
 * Author: lucasvg
 * 
 * Created on November 12, 2013, 6:14 PM
 */

#include <iostream>

#include "Shot.h"
#include "Robot.h"

Shot::Shot(int x, int y, int w, int h, int velx, int vely, SDL_Surface* surface, Robot *whoShoot) {
    this->box.x = x;
    this->box.y = y;
    this->box.w = w;
    this->box.h = h;
    this->velx = velx;
    this->vely = vely;
    this->surface = surface;
    this->whoShoot = whoShoot;
};

void Shot::move(Piece & piece, Piece & mainPiece, const int SCREEN_HEIGHT) {

    for (int i = 0; i < piece.size(); i++) {
        if (willCollid(piece[i], velx, vely)) {
            this->box.y = -1;
            this->whoShoot->setScore(this->whoShoot->getScore() +1 );
            piece.deleteSquare(i);
            return;
        }
    }

    for (int i = 0; i < mainPiece.size(); i++) {
        if (willCollid(mainPiece[i], velx, vely)) {
            this->box.y = -1;
            this->whoShoot->setScore(this->whoShoot->getScore() +1 );
            mainPiece.deleteSquare(i);
            return;
        }
    }

    this->box.x += velx;
    this->box.y += vely;

    // if it is out of the screen

    // if it collide with piece

    // if it collide with mainPiece

}

bool Shot::willCollid(Square square, int x, int y) {
    if ((box.x + x == square.getx()) or ((box.x + x > square.getx()) and (box.x + x < (square.getx() + square.getw())))
            or ((square.getx() > box.x + x) and (square.getx() < (box.x + x + box.w))))
        if ((box.y + y <= square.gety()) and (box.y + y + box.h >= square.gety()))
            return true;
    return false;
};

void Shot::show(SDL_Surface * screen) {
    apply_surface(box.x, box.y, surface, screen);
};

int Shot::getx() {
    return box.x;
}

int Shot::gety() {
    return box.y;
}