/* 
 * File:   Shot.cpp
 * Author: lucasvg
 * 
 * Created on November 11, 2013, 8:04 PM
 */

#include "Shot.h"

Shot::Shot(int x, int y, SDL_Surface* surface){
      this->x = x;
      this->y = y;
      this->surface = surface;      
  }  
