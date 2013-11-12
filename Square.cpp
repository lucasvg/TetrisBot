/* 
 * File:   Square.cpp
 * Author: lucasvg
 * 
 * Created on November 11, 2013, 3:39 PM
 */

#include "Square.h"
#include <SDL/SDL.h>
#include "general_functions.h"

    //Initializes the variables

    Square::Square(int x, int y, int color, const int SQUARE_WIDTH, const int SQUARE_HEIGHT) {
        box.x = x;
        box.y = y;
        square_color = color;
        box.w = SQUARE_WIDTH;
        box.h = SQUARE_HEIGHT;
    }

    void Square::move(int y, const int SCREEN_HEIGHT) {
        if (box.y + box.h + y >= SCREEN_HEIGHT) {
            for (int i = y; i > 0; i--) {
                if (box.y + box.h + y >= SCREEN_HEIGHT) {
                    y -= 1;
                } else {
                    break;
                }
            }
        }
        box.y += y;        
    }

    bool Square::isColliding(int SCREEN_HEIGHT) {
        //the minus one is because the square colides when it is 1 pixel far
        return (box.y + box.h >= SCREEN_HEIGHT - 1);
    }

    bool Square::isColliding(Square otherSquare) {
        if (box.x == otherSquare.getx())
            if (box.y + box.h >= otherSquare.gety())
                return true;
        return false;
    }

    int Square::getx() {
        return box.x;
    }

    int Square::gety() {
        return box.y;
    }
    
    int Square::getw() {
        return box.w;
    }

    int Square::geth() {
        return box.h;
    }

    void Square::show(SDL_Surface *squares_surfaces[], SDL_Surface *screen) {
        apply_surface(box.x, box.y, squares_surfaces[square_color], screen);
    }
