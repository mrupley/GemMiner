//
//  GameLogic.cpp
//  GemMiner
//
//  Created by Marcus Rupley on 2/25/17.
//  Copyright © 2017 Marcus Rupley. All rights reserved.
//


#include "GameLogic.h"
GameBoard gameBoard;
bool matchCells[BOARD_CELL_WIDTH][BOARD_CELL_HEIGHT];
int _score = 0;

bool GameLogic::isValidMove(GameCell firstCell, GameCell secondCell) {
    if(areCellsAdjacent(firstCell, secondCell)) {
        if(isLegalMove(firstCell, secondCell)) {
            return true;
        }
    }
    return false;
}

void GameLogic::loadGameBoard() {
    gameBoard.loadGameBoard();
}

GameCell* GameLogic::getCellAtAbsoluteXY(int x, int y) {
    return gameBoard.getCellAtAbsoluteXY(x,y);
}
int GameLogic::getCellColor(int x, int y) {
    return gameBoard.getCellColorOnBoard(x, y);
}

bool GameLogic::areCellsAdjacent(GameCell firstCell, GameCell secondCell) {
    int firstUid = firstCell.getUid();
    int secondUid = secondCell.getUid();
    if(firstUid == secondUid + 1 // is the move directly to the left?
       || firstUid == secondUid - 1 // is the move directly to the right?
       || firstUid == secondUid - BOARD_CELL_HEIGHT // is the move directly above?
       || firstUid == secondUid + BOARD_CELL_HEIGHT) { // is the move directly below?
        return true;
    }
    return false;
}

bool GameLogic::isLegalMove(GameCell firstCell, GameCell secondCell) {
    gameBoard.getCellOnBoard(firstCell.getX(), firstCell.getY())->setColor(secondCell.getColor());
    gameBoard.getCellOnBoard(secondCell.getX(), secondCell.getY())->setColor(firstCell.getColor());
    if (isMatch(*gameBoard.getCellOnBoard(firstCell.getX(), firstCell.getY()))
        || isMatch(*gameBoard.getCellOnBoard(secondCell.getX(), secondCell.getY()))) {
        gameBoard.getCellOnBoard(firstCell.getX(), firstCell.getY())->setColor(firstCell.getColor());
        gameBoard.getCellOnBoard(secondCell.getX(), secondCell.getY())->setColor(secondCell.getColor());
        return true;
    }
    gameBoard.getCellOnBoard(firstCell.getX(), firstCell.getY())->setColor(firstCell.getColor());
    gameBoard.getCellOnBoard(secondCell.getX(), secondCell.getY())->setColor(secondCell.getColor());
    
    return false;
}


int getLeftMatchCount(int x, int y, int color) {
    int leftMatch = 0;
    for(int i = x-1; i >= 0; i--) {
        if(color != gameBoard.getCellOnBoard(i, y)->getColor()) {
            break;
        }
        leftMatch++;
    }
    return leftMatch;
}

int getRightMatchCount(int x, int y, int color) {
    int rightMatch = 0;
    GameCell* cell = gameBoard.getCellOnBoard(x, y);
    for(int i = x+1; i < BOARD_CELL_WIDTH; i++ ) {
        if(cell->getColor() != gameBoard.getCellOnBoard(i, cell->getY())->getColor()) {
            break;
        }
        rightMatch++;
    }
    return rightMatch;
}

int getBelowMatchCount(int x, int y, int color) {
    int belowMatch = 0;
    for(int i = y+1; i < BOARD_CELL_HEIGHT; i++ ) {
        if(color != gameBoard.getCellOnBoard(x, i)->getColor()) {
            break;
        }
        belowMatch++;
    }
    return belowMatch;
}

int getAboveMatchCount(int x, int y, int color) {
    int aboveMatch = 0;
    for(int i = y-1; i >= 0; i-- ) {
        if(color != gameBoard.getCellOnBoard(x, i)->getColor()) {
            break;
        }
        aboveMatch++;
    }
    return aboveMatch;
}

int getLeftMatchingColor(int x, int y, int color) {
    if(x > 0) {
        int leftMatch = getLeftMatchCount(x, y, color);
        if(leftMatch >=2) {
            return color;
        }
    }
    return -1;
}

int getAboveMatchingColor(int x, int y, int color) {
    if(y > 0) {
        int aboveMatch = getAboveMatchCount(x, y, color);
        if(aboveMatch >=2) {
            return color;
        }
    }
    return -1;
}

void pushCell(GameCell* cell, int amount) {
    GameCell* otherCell;
    for(int y = cell->getY(); y >= 0; y--) {
        otherCell = gameBoard.getCellOnBoard(cell->getX(), y);
        otherCell->setYOffset((-CELL_HEIGHT) * amount);
    }
}

GameCell* GameLogic::getCellOnBoard(int x, int y) {
    return gameBoard.getCellOnBoard(x, y);
}

GameCell* GameLogic::getCellOnBoard(int uid) {
    return gameBoard.getCellOnBoard(uid);
}

bool GameLogic::isMatch(GameCell cell) {
    int aboveMatch = getAboveMatchCount(cell.getX(), cell.getY(), cell.getColor());
    int belowMatch = getBelowMatchCount(cell.getX(), cell.getY(), cell.getColor());
    int leftMatch = getLeftMatchCount(cell.getX(), cell.getY(), cell.getColor());
    int rightMatch = getRightMatchCount(cell.getX(), cell.getY(), cell.getColor());
    
    if(aboveMatch + belowMatch >= 2
       || rightMatch + leftMatch >= 2) {
        return true;
    }
    return false;
}

int GameLogic::getNonMatchingColorForCell(int x, int y) {
    int color = rand() % NUMBER_COLORS;
    int colorMatchLeft = getLeftMatchingColor(x, y, color);
    int colorMatchAbove = getAboveMatchingColor(x, y, color);
    while(color == colorMatchLeft || color == colorMatchAbove) {
        color++;
        color = color % NUMBER_COLORS;
    }
    
    return color;
}

bool GameLogic::hasValidMove() {
    for (int i = 0; i < BOARD_CELL_WIDTH; i++) {
        for (int j = 0; j < BOARD_CELL_HEIGHT; j++) {
            if (isMatch(*gameBoard.getCellOnBoard(i,j)) ) {
                return true;
            }
        }
    }
    return false;
}

void GameLogic::playMove() {
    GameCell* cell;
    for (int i = 0; i < BOARD_CELL_WIDTH; i++) {
        for (int j = 0; j < BOARD_CELL_HEIGHT; j++) {
            if (isMatch(*gameBoard.getCellOnBoard(i,j)) ) {
                matchCells[i][j] = true;
                _score += 10;
            } else {
                matchCells[i][j] = false;
            }
        }
    }
    for(int i = 0; i < BOARD_CELL_WIDTH; i++) {
        int push = 0;
        int lastPush = 0;
        for(int j = 0; j < BOARD_CELL_HEIGHT; j++) {
            if(matchCells[i][j] == true) {
                push++;
                lastPush = j;
                gameBoard.getCellOnBoard(i, j)->setColor(rand() % NUMBER_COLORS);
                for(int k = j; k > 0; k--) {
                    cell = gameBoard.getCellOnBoard(i, k);
                    swapColors(cell, gameBoard.getCellOnBoard(i, k-1));
                }
            }
        }
        pushCell(gameBoard.getCellOnBoard(i, lastPush), push);
    }
}

void GameLogic::swapColors(GameCell* firstCell, GameCell* secondCell) {
    int tmpColor = firstCell->getColor();
    firstCell->setColor(secondCell->getColor());
    secondCell->setColor(tmpColor);
}

int GameLogic::getScore() {
    return _score;
}

bool GameLogic::setDropAnimation() {
    GameCell* cell;
    int minNumber = 0;
    for(int i = 0; i < BOARD_CELL_WIDTH; i++) {
        for(int j = 0; j < BOARD_CELL_HEIGHT; j++) {
            cell = gameBoard.getCellOnBoard(i,j);
            if(cell->getYOffset() < 0) {
                cell->setYOffset(cell->getYOffset() + 1);
            }
            if(cell->getYOffset() < minNumber) {
                minNumber = cell->getYOffset();
            }
        }
    }
    return minNumber < 0;
}