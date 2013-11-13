/* 
 * File:   Shot.h
 * Author: lucasvg
 *
 * Created on November 12, 2013, 6:14 PM
 */

#include <SDL/SDL.h>
#include "Piece.h"
#include "general_functions.h"

#ifndef SHOT_H
#define	SHOT_H

class Shot {
private:
    SDL_Rect box;
    int velx, vely;
    SDL_Surface *surface;

public:

    Shot(int x, int y, int w, int h, int velx, int vely, SDL_Surface* surface);

    void move(Piece & piece, Piece & mainPiece, const int SCREEN_HEIGHT);

    bool isCollided(Square square);

    void show(SDL_Surface *screen);
    
    int getx();
    
    int gety();
};

#endif	/* SHOT_H */

