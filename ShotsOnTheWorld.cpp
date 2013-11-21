/* 
 * File:   ShotsOnTheWorld.cpp
 * Author: lucasvg
 * 
 * Created on November 12, 2013, 7:41 PM
 */

#include <iostream>

#include "ShotsOnTheWorld.h"

ShotsOnTheWorld::ShotsOnTheWorld(const int WORLD_WIDTH, const int WORLD_HEIGHT) : WORLD_WIDTH(WORLD_WIDTH), WORLD_HEIGHT(WORLD_HEIGHT) {
}

void ShotsOnTheWorld::newShot(Shot shot) {
    shotsAlive.push_back(shot);
}

void ShotsOnTheWorld::moveShots(Piece & piece, Piece & mainPiece) {
    for (int i = 0; i < shotsAlive.size(); i++) {
        shotsAlive[i].move(piece, mainPiece, WORLD_HEIGHT);
        if (shotsAlive[i].gety() < 0)
            shotsAlive.erase(shotsAlive.begin() + i);
    }
}

void ShotsOnTheWorld::show(SDL_Surface *screen) {
    for (int i = 0; i < shotsAlive.size(); i++) {
        shotsAlive[i].show(screen);
    }
}

int ShotsOnTheWorld::size() {
    return shotsAlive.size();
}

void ShotsOnTheWorld::clean() {
    for(int i = 0; i<size(); i++){
        shotsAlive.erase(shotsAlive.begin() + i);
    }
}