//
//  Sprite.h
//  GemMiner
//
//  Created by Marcus Rupley on 2/25/17.
//  Copyright © 2017 Marcus Rupley. All rights reserved.
//

#ifndef Sprite_h
#define Sprite_h
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

// Simple Sprite struct to hold the images
struct Sprite {
    SDL_Surface* sprite = NULL;
    
    Sprite(const char* filename) {
        sprite = IMG_Load(filename);
    }
};

#endif /* Sprite_h */
