/* 
 * File:   general_functions.h
 * Author: lucasvg
 *
 * Created on November 8, 2013, 6:04 PM
 */

#ifndef GENERAL_FUNCTIONS_H
#define	GENERAL_FUNCTIONS_H

SDL_Surface *load_image(std::string filename);

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);

bool applyHomeScreen(SDL_Surface *screen);

#endif	/* GENERAL_FUNCTIONS_H */

