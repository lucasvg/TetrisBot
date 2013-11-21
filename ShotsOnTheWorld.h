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

// this class handles all the shots on the screen
class ShotsOnTheWorld {
private:
    // group of shots on the screen
    std::vector<Shot> shotsAlive;
    
    // this limits the area where the shots can be
    const int WORLD_WIDTH, WORLD_HEIGHT;
public:

    // constructor
    ShotsOnTheWorld(const int WORLD_WIDTH, const int WORLD_HEIGHT);

    // add a "shot" to the group of shots
    void newShot(Shot shot);

    // it moves the shots
    void moveShots(Piece & piece, Piece & mainPiece);
    
    // it shows the shots on "screen"
    void show(SDL_Surface *screen);
    
    // returns the amount of shots
    int size();
    
    // deletes all the shots
    void clean();
};

#endif	/* SHOTSONTHEWORLD_H */

