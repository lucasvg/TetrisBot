#include "general_functions.h"

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

bool applyHomeScreen(SDL_Surface *screen) {

    TTF_Init();

    //The font that's going to be used

    TTF_Font *font = NULL;
    font = TTF_OpenFont("lazy.ttf", 28);
    if (font == NULL)
        return false;

    //The color of the font
    SDL_Color textColor = {255, 255, 255};

    SDL_Surface *message = TTF_RenderText_Solid(font, "The quick brown fox jumps over the lazy dog", textColor);
    apply_surface(0, 0, message, screen, NULL);
    SDL_FreeSurface(message);

    message = TTF_RenderText_Solid(font, "press space to continue", textColor);
    apply_surface(0, message->h * 2, message, screen);

    SDL_FreeSurface(message);

    TTF_CloseFont(font);
    TTF_Quit();
    return true;
}

bool applyGameScreen(SDL_Surface *background, SDL_Surface *divider_bar, SDL_Surface *screen, const int SCREEN_PLAYABLE_WIDTH) {
    
    apply_surface(0, 0, background, screen);

    apply_surface(SCREEN_PLAYABLE_WIDTH, 0, divider_bar, screen);
    
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

    TTF_CloseFont(font);
    TTF_Quit();
    return true;
}