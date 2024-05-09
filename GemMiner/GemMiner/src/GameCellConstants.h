//
//  GameCellConstants.h
//  GemMiner
//
//  Created by Marcus Rupley on 2/25/17.
//  Copyright © 2017 Marcus Rupley. All rights reserved.
//

#ifndef GameCellConstants_h
#define GameCellConstants_h
#include "Sprite.h"
#include "Image.h"

//Board dimension constants

// Width of each game cell
static const int CELL_WIDTH = 40;

// Height of each game cell
static const int CELL_HEIGHT = 40;

// By changing this and the values of the sprites, the number of available colors can change
static const int NUMBER_COLORS = 5;

// Game duration in seconds
static const int TIMER_SECONDS = 60;

// should be a factor of the cell size.
static const int ANIMATION_SPEED = 1;

enum Direction {
    HORIZONTAL,
    VERTICAL
};

// This holds the color sprites used in the game.
static const Sprite* sprites[NUMBER_COLORS] {
    new Sprite(BLUE_IMAGE),
    new Sprite(GREEN_IMAGE),
    new Sprite(YELLOW_IMAGE),
    new Sprite(RED_IMAGE),
    new Sprite(PURPLE_IMAGE),
};


#endif /* GameCellConstants_h */
