/* 
 * File:   Shot.h
 * Author: lucasvg
 *
 * Created on November 11, 2013, 8:04 PM
 */

#include <SDL/SDL.h>
#include "Piece.h"


#ifndef SHOT_H
#define	SHOT_H

class Shot{
private:
    SDL_Rect box;
    int x, y;
    SDL_Surface *surface;
    
public:
  Shot(int x, int y, SDL_Surface *surface);
  
  bool move(int y);
  
  bool isCollided(Piece piece);
  
  bool isCollided(Square square);
  
  ~Shot();
  
  void show(SDL_Surface *screen);
};

#endif	/* SHOT_H */

