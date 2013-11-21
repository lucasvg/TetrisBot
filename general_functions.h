/* 
 * File:   general_functions.h
 * Author: lucasvg
 *
 * Created on November 8, 2013, 6:04 PM
 */

#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"

#ifndef GENERAL_FUNCTIONS_H
#define	GENERAL_FUNCTIONS_H

// help loading image files
SDL_Surface *load_image(std::string filename);

// help applying a surface on a screen
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);

// prints the home screen on screen
bool applyHomeScreen(SDL_Surface *screen, SDL_Surface *background, std::string robotDevicePath);

// prints the game over screen on screen
bool applyGameOverScreen(SDL_Surface *screen);

// prints the game running screen on screen
bool applyGameScreen(SDL_Surface *background, SDL_Surface *divider_bar, SDL_Surface *screen, const int SCREEN_PLAYABLE_WIDTH, const int SCORE);

// determines if the homeScreen should be shown
void handleHomeScreen(SDL_Event event, bool & homeScreem, std::string & robotDevicePath);

#endif	/* GENERAL_FUNCTIONS_H */

