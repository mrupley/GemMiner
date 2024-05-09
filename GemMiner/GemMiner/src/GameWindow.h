//
//  GameWindow.hpp
//  GemMiner
//
//  Created by Marcus Rupley on 2/25/17.
//  Copyright © 2017 Marcus Rupley. All rights reserved.
//

#ifndef GameWindow_h
#define GameWindow_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <vector>
#include <sstream>
#include <string>
#include "Image.h"
#include "GameBoardConstants.h"
#include "GameView.h"
#include "GameLogic.h"
#include <stdlib.h>	

class GameWindow {
public:
    bool load();
private:
    //The timer starting time
    Uint32 start;
    
    // Remaining time to display
    int remainingTime;
    
    // Previous time - enables UI updates only when the timer has changed
    int previousTime;
    
    // previous score, only updates when changed
    int oldScore;
    
    //The timer's time as a string
    std::stringstream secondsString;
    
    //THe score as a string
    std::stringstream scoreString;
    
    // Surface to display the number of seconds remaining
    SDL_Surface *seconds;
    
    // Surface to display the number of seconds remaining
    SDL_Surface *scoreValue;
    
    //The font
    TTF_Font *font;
    //TODO RELEASE VERSION OF FONT
    //             font = TTF_OpenFont( "assets/lazy.ttf", 36 );
    
    //The color of the font
    SDL_Color textColor;
    
    SDL_Surface* loadBackground();
    SDL_Surface* loadSurface( std::string path );
    void loadGems();
    void loadTime();
    void updateScore();
    void animateNoMove(GameCell *firstCell, GameCell *secondCell);
    void animateMove(GameCell *firstCell, GameCell *secondCell);

};

#endif /* GameWindow_h */
