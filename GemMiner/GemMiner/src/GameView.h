//
//  GameView.hpp
//  GemMiner
//
//  Created by Marcus Rupley on 2/26/17.
//  Copyright © 2017 Marcus Rupley. All rights reserved.
//

#ifndef GameView_h
#define GameView_h

#include <stdio.h>
#include "GameCell.h"
#include "GameLogic.h"
#include "GameCellConstants.h"


namespace GameView {
    // Swapping refers to trying to move two cell into the other position
    // Swap return occurs when there is no match.
    // Move is for a valid move
    // Play makes the cells 'disappear'
    // Drop makes the new tiles fall
    // None pauses animations
    enum ANIMATION {
        SWAP_HORIZONTAL,
        SWAP_RETURN_HORIZONTAL,
        SWAP_VERTICAL,
        SWAP_RETURN_VERTICAL,
        MOVE_HORIZONTAL,
        MOVE_VERTICAL,
        PLAY,
        DROP,
        NONE
    };
    
    // Offsets from the origin of the cell location 0,0
    // these are used to swap the lcoations and drop while preserving index in the board.
    int getXOffset(int x, int y);
    int getYOffset(int x, int y);
    
    // This animates all of the ANIMATION values.
    void animate();

    // Set which cells should animate and the animation sequence.
    void setAnimatingCells(GameCell** cells, ANIMATION anim);
    
    // performs the animations for the current frame
    void doAnimation(Direction direction, ANIMATION anim);
    
    // performs the return swap animation on an invalid move
    void doReturnAnimation(Direction direction);

}

#endif /* GameView_h */
