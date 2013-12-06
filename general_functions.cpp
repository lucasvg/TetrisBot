#include <iostream>

#include "general_functions.h"
#include "Robot.h"
#include <sstream>

SDL_Surface *load_image(std::string filename) {
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load(filename.c_str());

    //If the image loaded
    if (loadedImage != NULL) {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat(loadedImage);

        //Free the old surface
        SDL_FreeSurface(loadedImage);

        //If the surface was optimized
        if (optimizedImage != NULL) {
            //Color key surface
            SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF));
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip) {
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface(source, clip, destination, &offset);
}

bool applyHomeScreen(SDL_Surface *screen, SDL_Surface *background, std::string robotDevicePath) {
    
    
    
    TTF_Init();

    //The font that's going to be used

    TTF_Font *fontTitle = NULL;
    TTF_Font *font = NULL;
    
    fontTitle = TTF_OpenFont("lazy.ttf", 36);
    font = TTF_OpenFont("lazy.ttf", 20);
    if ((fontTitle == NULL) or (font == NULL))
        return false;

    //The color of the font
    SDL_Color textColor = {255, 255, 255};

    apply_surface(0, 0, background, screen);
    
    int distance = 0;
    SDL_Surface *message = TTF_RenderText_Solid(fontTitle, "TetrisBot", textColor);
    apply_surface(0, 0, message, screen);
    SDL_FreeSurface(message);
    
    
    distance += 3;    
    std::stringstream ss;
    ss << "Path to robot device: " << robotDevicePath;
    
    message = TTF_RenderText_Solid(font, ss.str().c_str(), textColor);
    apply_surface(0, message->h * distance, message, screen);
    SDL_FreeSurface(message);
    
    distance +=3;
    message = TTF_RenderText_Solid(font, "left and right arrow to move the robot - space to shoot", textColor);
    apply_surface(0, message->h * distance, message, screen);
    SDL_FreeSurface(message);
    
    distance += 3;    
    message = TTF_RenderText_Solid(font, "press space to continue", textColor);
    apply_surface(0, message->h * distance, message, screen);
    SDL_FreeSurface(message);

    TTF_CloseFont(fontTitle);
    TTF_CloseFont(font);
    TTF_Quit();
    return true;
}

bool applyGameScreen(SDL_Surface *background, SDL_Surface *divider_bar, SDL_Surface *screen, const int SCREEN_PLAYABLE_WIDTH, 
        const int SCREEN_WIDTH, const int SCORE, Piece nextPiece, SDL_Surface *squares_surfaces[]) {
    
    apply_surface(0, 0, background, screen);

    apply_surface(SCREEN_PLAYABLE_WIDTH, 0, divider_bar, screen);
    
    
    TTF_Init();
    TTF_Font *font = NULL;
    font = TTF_OpenFont("lazy.ttf", 25);
    
    if (font == NULL)
        return false;
    
    SDL_Color textColor = {255, 255, 255};
    SDL_Surface * message = NULL;
    message = TTF_RenderText_Solid(font, "Score:", textColor);
    if (message == NULL)
        return false;
    apply_surface((SCREEN_PLAYABLE_WIDTH + 10), (message->h), message, screen);
    SDL_FreeSurface(message);
    message = NULL;
    
    
    std::stringstream ss;
    ss << SCORE;
    message = TTF_RenderText_Solid(font, ss.str().c_str(), textColor);
    if (message == NULL)
        return false;
    apply_surface((SCREEN_PLAYABLE_WIDTH + 10), (message->h * 2), message, screen);
    SDL_FreeSurface(message);
    message = NULL;
    
    message = TTF_RenderText_Solid(font, "Next Piece:", textColor);
    if (message == NULL)
        return false;
    apply_surface((SCREEN_PLAYABLE_WIDTH + 10), (message->h*6), message, screen);
    
    Square firstSquare = nextPiece[0];
    for(int i = 0; i<nextPiece.size(); i++){
        apply_surface((SCREEN_PLAYABLE_WIDTH + (SCREEN_WIDTH - SCREEN_PLAYABLE_WIDTH - nextPiece.getPieceWidth() - 80)/2 + nextPiece[i].getx() - firstSquare.getx()), 
                (message->h*8 + nextPiece[i].gety() - firstSquare.gety()),
                squares_surfaces[nextPiece[i].getSquareColor()],
                screen);
    }
    //nextPiece.show(squares_surfaces, screen);
    
    SDL_FreeSurface(message);
    message = NULL;    
    
    TTF_CloseFont(font);
    TTF_Quit();
    return true;
}

bool applyGameOverScreen(SDL_Surface *screen) {
    TTF_Init();

    //The font that's going to be used

    TTF_Font *font = NULL;
    font = TTF_OpenFont("lazy.ttf", 28);
    if (font == NULL)
        return false;

    //The color of the font
    SDL_Color textColor = {255, 255, 255};

    SDL_Surface *message = TTF_RenderText_Solid(font, "GameOver!!! MUHAHAHAHA", textColor);
    apply_surface(0, 0, message, screen, NULL);
    SDL_FreeSurface(message);
    
    message = TTF_RenderText_Solid(font, "Wanna play again?", textColor);
    apply_surface(0, message->h *2, message, screen, NULL);
    SDL_FreeSurface(message);
    
    message = TTF_RenderText_Solid(font, "(Y/N)", textColor);
    apply_surface(0, message->h *3, message, screen, NULL);
    SDL_FreeSurface(message);

    TTF_CloseFont(font);
    TTF_Quit();
    return true;
}

void handleHomeScreen(SDL_Event event, bool & homeScreen, std::string & robotDevicePath) {
    
    if (homeScreen)
        if (event.type == SDL_KEYDOWN)
            if (event.key.keysym.sym == SDLK_SPACE){
                homeScreen = false;
            }else if (event.key.keysym.sym == SDLK_BACKSPACE){
                if(robotDevicePath.size()>0){
                robotDevicePath = robotDevicePath.erase(robotDevicePath.size()-1);
                }
            }else{
                robotDevicePath += (char)event.key.keysym.unicode; 
            }
}

std::string isCollidingTest(){
    std::string error = "";
    SDL_Rect box1, box2;
    
    box1.y = 1;
    box1.h = 1;
    box2.y = 5;
    box2.h = 1;
    
    if(isColliding(box1, box2))
        error += "error on IsColliding Test, nº1 \n";
    
    box1.h = 4;
    if(!isColliding(box1, box2))
        error += "error on IsColliding Test, nº2 \n";
    
    box1.y = 7;    
    if(isColliding(box1, box2))
        error += "error on IsColliding Test, nº3 \n";
    
    box2.y = 6;    
    if(!isColliding(box1, box2))
        error += "error on IsColliding Test, nº4 \n";    
    
    box1.x = 1;
    box1.w = 2;
    box1.y = 1;
    box1.h = 3;
    
    box2.x = 4;
    box2.w = 2;
    box2.y = 1;
    box2.h = 3;
    
    if(isColliding(box1, box2))
        error += "error on IsColliding Test, nº5 \n";
    
    box1.x = 3;
    if(!isColliding(box1, box2))
        error += "error on IsColliding Test, nº6 \n";
    
    box1.x = 7;
    if(isColliding(box1, box2))
        error += "error on IsColliding Test, nº7 \n";
    
    box2.x = 5;
    if(!isColliding(box1, box2))
        error += "error on IsColliding Test, nº8 \n";
    return error;
}

bool isColliding(SDL_Rect box1, SDL_Rect box2){
    return !(((box1.y + box1.h) < box2.y) or (box1.y > (box2.y + box2.h)) or ((box1.x+box1.w) < box2.x) or (box1.x > (box2.x + box2.w)));
}