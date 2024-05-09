//
//  GameBoardConstants.h
//  GemMiner
//
//  Created by Marcus Rupley on 2/25/17.
//  Copyright © 2017 Marcus Rupley. All rights reserved.
//

#ifndef GameBoardConstants_h
#define GameBoardConstants_h

//Board dimension constants
static const int BOARD_WIDTH = 350;
static const int BOARD_HEIGHT = 350;
static const int BOARD_TOP = 115;
static const int BOARD_LEFT = 335;
static const int BOARD_CELL_WIDTH = 8;
static const int BOARD_CELL_HEIGHT = 8;

//The surface contained by the window
static SDL_Surface* screenSurface = NULL;

//The window we'll be rendering to
static SDL_Window* window = NULL;

//Screen dimension constants
static const int SCREEN_WIDTH = 755;
static const int SCREEN_HEIGHT = 600;


#endif /* GameBoardConstants_h */
