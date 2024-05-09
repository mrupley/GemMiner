//
//  GameBoard.cpp
//  GemMiner
//
//  Created by Marcus Rupley on 2/25/17.
//  Copyright © 2017 Marcus Rupley. All rights reserved.
//

#include "GameBoard.h"

static GameCell cell[BOARD_CELL_WIDTH][BOARD_CELL_HEIGHT];

void GameBoard::loadGameBoard() {
    int color;
    for(int i = 0; i < BOARD_CELL_WIDTH; i++) {
        for(int j = 0; j < BOARD_CELL_HEIGHT; j++) {
            color = GameLogic::getNonMatchingColorForCell(i, j);
            cell[i][j].initialize(i*BOARD_CELL_HEIGHT + j, color);
        }
    }
}

GameCell* GameBoard::getCellAtAbsoluteXY(int x, int y) {
    int _x = (x - BOARD_LEFT)/CELL_WIDTH;
    int _y = (y - BOARD_TOP)/CELL_HEIGHT;
    if(isValidCell(_x, _y)) {
        return &cell[_x][_y];
    }
    return nullptr;
}

int GameBoard::getCellColorOnBoard(int x, int y) {
    return cell[x][y].getColor();
}

int GameBoard::getCellColorOnBoard(int uid) {
    int x = uid / BOARD_CELL_WIDTH;
    int y = uid % BOARD_CELL_HEIGHT;
    return getCellColorOnBoard(x, y);
}
GameCell* GameBoard::getCellOnBoard(int uid) {
    int x = uid / BOARD_CELL_WIDTH;
    int y = uid % BOARD_CELL_HEIGHT;
    return &cell[x][y];
}
GameCell* GameBoard::getCellOnBoard(int x, int y) {
    return &cell[x][y];
}

bool GameBoard::isValidCell(int x, int y){
    if((x >= 0 && x < BOARD_CELL_WIDTH)
       && (y >= 0 && y < BOARD_CELL_HEIGHT)) {
        return true;
    }
    return false;
}
