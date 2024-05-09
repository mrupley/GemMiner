//
//  GameWindow.cpp
//  GemMiner
//
//  Created by Marcus Rupley on 2/25/17.
//  Copyright © 2017 Marcus Rupley. All rights reserved.
//

#include "GameWindow.h"

bool GameWindow::load() {
    //Create window
    window = SDL_CreateWindow( "Gem Miner", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Get window surface
        screenSurface = SDL_GetWindowSurface( window );
        SDL_Surface* background = loadBackground();
        if (background != NULL) {
            //Main loop flag
            bool quit = false;
            
            //Event handler
            SDL_Event e;
            
            TTF_Init();
            
            //The timer starting time
            Uint32 start = SDL_GetTicks();
            
            // Remaining time
            remainingTime = TIMER_SECONDS - (SDL_GetTicks() - start) / 1000;
            
            // Previous time - enables UI updates only when the timer has changed
            previousTime = remainingTime + 1;
            
            // set the old score to a default value
            oldScore = -1;
            
            //The font
            font = TTF_OpenFont( "assets/lazy.ttf", 36 );
            
            //The color of the font
            textColor = { 0xF0, 0xFF, 0xF0 };
            
            GameLogic::loadGameBoard();
            
            GameCell* newCell = nullptr;
            GameCell* mouseOverCell = nullptr;
            
            // mouse is down
            bool mouseDown = false;
            
            // is a cell selected
            bool selectedCell = false;
            
            //Convert the timer's time to a string
            const char* TIME = "TIMER: ";
            
            //Render the time surface
            SDL_Surface *timerSurface = TTF_RenderText_Solid( font, TIME, textColor );
            
            //Convert the timer's time to a string
            const char* SCORE = "SCORE: ";
            
            //Render the time surface
            SDL_Surface *scoreSurface = TTF_RenderText_Solid( font, SCORE, textColor );
            
            //Holds offsets
            SDL_Rect scoreSurfaceOffset;
            
            scoreSurfaceOffset.x = 80;
            scoreSurfaceOffset.y = 170;
            
            //Holds offsets
            SDL_Rect scoreValueSurfaceOffset;
            
            scoreValueSurfaceOffset.x = 100;
            scoreValueSurfaceOffset.y = 200;
            
            //Holds offsets
            SDL_Rect timerSurfaceOffset;
            
            timerSurfaceOffset.x = 80;
            timerSurfaceOffset.y = 80;
            
            //Holds offsets
            SDL_Rect secondsOffset;
            //Get offsets
            secondsOffset.x = 100;
            secondsOffset.y = 110;
            
            //While application is running
            while( !quit )
            {
                
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    
                    if(e.type == SDL_MOUSEMOTION) {
                        mouseOverCell = GameLogic::getCellAtAbsoluteXY(e.motion.x, e.motion.y);
                        if(e.motion.x > 0 && e.motion.y > 0) {
                            if (mouseDown) {
                                mouseOverCell = GameLogic::getCellAtAbsoluteXY(e.motion.x, e.motion.y);
                                if( mouseOverCell != nullptr && newCell != nullptr) {
                                    if(newCell->getUid() == mouseOverCell->getUid()) {
                                        // do nothing
                                    } else if (GameLogic::isValidMove(*newCell, *mouseOverCell)) {
                                        animateMove(newCell, mouseOverCell);
                                        newCell = nullptr;
                                        mouseOverCell = nullptr;
                                    } else {
                                        if(GameLogic::areCellsAdjacent(*newCell, *mouseOverCell)) {
                                            animateNoMove(newCell, mouseOverCell);
                                            newCell = nullptr;
                                            mouseOverCell = nullptr;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        if(remainingTime > 0 && e.motion.x > 0 && e.motion.y > 0) {
                            newCell = GameLogic::getCellAtAbsoluteXY(e.motion.x, e.motion.y);
                            if (selectedCell && newCell != nullptr && mouseOverCell != nullptr) {
                                if(newCell->getUid() == mouseOverCell->getUid()) {
                                    // do nothing
                                } else if (GameLogic::isValidMove(*newCell, *mouseOverCell)) {
                                    animateMove(newCell, mouseOverCell);
                                    newCell = nullptr;
                                    mouseOverCell = nullptr;
                                } else {
                                    if(GameLogic::areCellsAdjacent(*newCell, *mouseOverCell)) {
                                        animateNoMove(newCell, mouseOverCell);
                                        newCell = nullptr;
                                        mouseOverCell = nullptr;
                                    }
                                    selectedCell = false;
                                }
                            }
                        }
                        mouseDown = true;
                    }
                    
                    if(remainingTime > 0 && e.type == SDL_MOUSEBUTTONUP ){
                        if(e.motion.x > 0 && e.motion.y > 0) {
                            mouseOverCell = GameLogic::getCellAtAbsoluteXY(e.motion.x, e.motion.y);
                            if(mouseOverCell != nullptr && newCell != nullptr) {
                                if(newCell->getUid() == mouseOverCell->getUid()) {
                                    // do nothing
                                    selectedCell = !selectedCell;
                                } else {
                                    selectedCell = false;
                                }
                            }
                        }
                        mouseDown = false;
                    }
                    
                }
                
                GameView::animate();
                
                //Apply the PNG image
                SDL_BlitSurface( background , NULL, screenSurface, NULL );
                // load the cells
                loadGems();
                
                // loads the time string
                loadTime();
                
                // updates the score string
                updateScore();
                
                //Blit the timer surface
                SDL_BlitSurface( scoreValue, NULL, screenSurface, &scoreValueSurfaceOffset );
                
                //Blit the timer surface
                SDL_BlitSurface( scoreSurface, NULL, screenSurface, &scoreSurfaceOffset );
                
                //Blit the timer surface
                SDL_BlitSurface( timerSurface, NULL, screenSurface, &timerSurfaceOffset );
                
                //Blit
                SDL_BlitSurface( seconds, NULL, screenSurface, &secondsOffset );
                
                
                //Update the surface
                SDL_UpdateWindowSurface( window );
                
            }
            
            //Destroy window
            SDL_DestroyWindow( window );
            
            //Quit SDL subsystems
            SDL_Quit();
        } else {
            return false;
        }
    }
    return true;
}

void GameWindow::loadGems() {
    for(int i = 0; i < BOARD_CELL_WIDTH; i++) {
        for(int j = 0; j < BOARD_CELL_HEIGHT; j++) {
            int color = GameLogic::getCellColor(i,j);
            if(color >= 0) {
                SDL_Rect DestR;
                DestR.x = i*CELL_WIDTH + BOARD_LEFT + GameView::getXOffset(i, j);
                DestR.y = j*CELL_HEIGHT + BOARD_TOP + GameView::getYOffset(i, j);
                
                SDL_BlitSurface(sprites[color]->sprite, NULL, screenSurface, &DestR);
                
            }
        }
    }
}

void GameWindow::loadTime() {
    // only update the timer once every second to save cycles
    if(remainingTime >= 0) {
        remainingTime = TIMER_SECONDS - (SDL_GetTicks() - start) / 1000;
        if(remainingTime != previousTime) {
            previousTime = remainingTime;
            if( remainingTime <= 0) {
                remainingTime = 0;
            }
            // Update the time string
            secondsString.str("");
            secondsString.clear();
            secondsString << remainingTime;
            
            //Free the time surface
            if(seconds != NULL) {
                SDL_FreeSurface( seconds );
            }
            seconds = TTF_RenderText_Solid( font, secondsString.str().c_str(), textColor );
        }
    }
}

void GameWindow::updateScore() {
    // only update the score when needed
    if(remainingTime >= 0) {
        if(oldScore != GameLogic::getScore()) {
            oldScore = GameLogic::getScore();
            // Update the time string
            scoreString.str("");
            scoreString.clear();
            scoreString << oldScore;
            
            //Free the time surface
            if(scoreValue != NULL) {
                SDL_FreeSurface( scoreValue );
            }
            scoreValue = TTF_RenderText_Solid( font, scoreString.str().c_str(), textColor );
        }
    }
}

void GameWindow::animateNoMove(GameCell *firstCell, GameCell *secondCell) {
    GameView::ANIMATION anim;
    GameCell* cells[2] = {firstCell, secondCell };
    if (firstCell->getX() != secondCell->getX()) {
        anim = GameView::SWAP_HORIZONTAL;
    } else if (firstCell->getY() != secondCell->getY()) {
        anim = GameView::SWAP_VERTICAL;
    }
    GameView::setAnimatingCells(cells, anim);
}

void GameWindow::animateMove(GameCell *firstCell, GameCell *secondCell) {
    GameView::ANIMATION anim;
    GameCell* cells[2] = {firstCell, secondCell };
    if (firstCell->getX() != secondCell->getX()) {
        anim = GameView::MOVE_HORIZONTAL;
    } else if (firstCell->getY() != secondCell->getY()) {
        anim = GameView::MOVE_VERTICAL;
    }
    GameView::setAnimatingCells(cells, anim);
}

//Loads the media
SDL_Surface* GameWindow::loadBackground()
{
    //Current displayed PNG image
    SDL_Surface* gPNGSurface = NULL;
    
    //Load PNG surface
    gPNGSurface = loadSurface( BACKGROUND_IMAGE );
    
    return gPNGSurface;
}

SDL_Surface* GameWindow::loadSurface( std::string path )
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;
    
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, screenSurface->format, NULL );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    
    return optimizedSurface;
}

