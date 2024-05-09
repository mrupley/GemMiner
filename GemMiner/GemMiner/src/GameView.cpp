//
//  GameView.cpp
//  GemMiner
//
//  Created by Marcus Rupley on 2/26/17.
//  Copyright © 2017 Marcus Rupley. All rights reserved.
//

#include "GameView.h"
GameView::ANIMATION _animation = GameView::NONE;
GameCell* firstCell;
GameCell* secondCell;

int GameView::getXOffset(int x, int y) {
    return GameLogic::getCellOnBoard(x, y)->getXOffset();
}

int GameView::getYOffset(int x, int y) {
    return GameLogic::getCellOnBoard(x, y)->getYOffset();
}

void GameView::animate() {
    switch (_animation) {
        case SWAP_HORIZONTAL:
            doAnimation(HORIZONTAL, SWAP_RETURN_HORIZONTAL);
            break;
        case SWAP_RETURN_HORIZONTAL:
            doReturnAnimation(HORIZONTAL);
            break;
        case SWAP_VERTICAL:
            doAnimation(VERTICAL, SWAP_RETURN_VERTICAL);
            break;
        case SWAP_RETURN_VERTICAL:
            doReturnAnimation(VERTICAL);
            break;
        case MOVE_VERTICAL:
            doAnimation(VERTICAL, PLAY);
            break;
        case MOVE_HORIZONTAL:
            doAnimation(HORIZONTAL, PLAY);
            break;
        case PLAY:
            if(GameLogic::hasValidMove()) {
                firstCell->setXOffset(0);
                firstCell->setYOffset(0);
                secondCell->setXOffset(0);
                secondCell->setYOffset(0);
                GameLogic::playMove();
                _animation = GameView::DROP;
            } else {
                _animation = GameView::NONE;
            }
            break;
        case DROP:
            if(!GameLogic::setDropAnimation()) {
                _animation = GameView::PLAY;
            }
            break;
        case NONE:
            break;
    }
}

void GameView::doAnimation(Direction direction, ANIMATION animation) {
    if(firstCell->getOffset(direction) < CELL_WIDTH) {
        firstCell->setOffset(direction, firstCell->getOffset(direction) + ANIMATION_SPEED);
    }
    if(secondCell->getOffset(direction) > -CELL_WIDTH) {
        secondCell->setOffset(direction, secondCell->getOffset(direction) - ANIMATION_SPEED);
    }
    
    if (secondCell->getOffset(direction) == -CELL_WIDTH
        || firstCell->getOffset(direction) == CELL_WIDTH) {
        if(animation == PLAY) {
           GameLogic::swapColors(firstCell, secondCell);
        }
        _animation = animation;
    }
}

void GameView::doReturnAnimation(Direction direction) {
    if(firstCell->getOffset(direction) > 0) {
        firstCell->setOffset(direction, firstCell->getOffset(direction) - ANIMATION_SPEED);
    }
    
    if(secondCell->getOffset(direction) < 0) {
        secondCell->setOffset(direction, secondCell->getOffset(direction) + ANIMATION_SPEED);
    }
    
    if (secondCell->getOffset(direction) == 0
        || firstCell->getOffset(direction) == 0) {
        _animation = GameView::NONE;
    }
}

void GameView::setAnimatingCells(GameCell** cells, ANIMATION anim) {
    if(cells[0]->getX() < cells[1]->getX() || cells[0]->getY() < cells[1]->getY()) {
        firstCell = cells[0];
        secondCell = cells[1];
    } else {
        secondCell = cells[0];
        firstCell = cells[1];
    }
    _animation = anim;
}