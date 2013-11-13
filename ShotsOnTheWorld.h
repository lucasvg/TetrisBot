/* 
 * File:   ShotsOnTheWorld.h
 * Author: lucasvg
 *
 * Created on November 12, 2013, 7:41 PM
 */

#include <SDL/SDL.h>
#include "Shot.h"

#ifndef SHOTSONTHEWORLD_H
#define	SHOTSONTHEWORLD_H

class ShotsOnTheWorld {
private:
    std::vector<Shot> shotsAlive;
    const int WORLD_WIDTH, WORLD_HEIGHT;
public:

    ShotsOnTheWorld(const int WORLD_WIDTH, const int WORLD_HEIGHT);

    void newShot(Shot shot);

    void moveShots(Piece & piece, Piece & mainPiece);
    
    void show(SDL_Surface *screen);

    bool isCollided(Square);
    
    int size(){
        return shotsAlive.size();
    }
};

#endif	/* SHOTSONTHEWORLD_H */

