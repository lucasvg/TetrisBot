/* 
 * File:   Shot.cpp
 * Author: lucasvg
 * 
 * Created on November 12, 2013, 6:14 PM
 */

#include <iostream>

#include "Shot.h"

Shot::Shot(int x, int y, int w, int h, int velx, int vely, SDL_Surface* surface) {
    this->box.x = x;
    this->box.y = y;
    this->box.w = w;
    this->box.h = h;
    this->velx = velx;
    this->vely = vely;
    this->surface = surface;
};

bool Shot::move(Piece piece, Piece mainPiece, const int SCREEN_HEIGHT) {

    this->box.x += velx;
    this->box.y += vely;

    // if it is out of the screen

    // if it collide with piece

    // if it collide with mainPiece

}

bool Shot::isCollided(Piece piece) {

};

bool Shot::isCollided(Square square) {

};

void Shot::show(SDL_Surface *screen) {
    apply_surface(box.x, box.y, surface, screen);
    using namespace std;
    cout<< "x=" << box.x << " y=" << box.y << "w=" << box.w << "h=" << box.h << endl;
};