//
//  GameCell.cpp
//  GemMiner
//
//  Created by Marcus Rupley on 2/25/17.
//  Copyright © 2017 Marcus Rupley. All rights reserved.
//

#include "GameCell.h"

int GameCell::getColor() {
    return _color;
}

void GameCell::setColor(int color) {
    _color = color;
}

int GameCell::getUid() {
    return _uid;
}

void GameCell::initialize(int uid, int color) {
    _uid = uid;
    _color = color;
    _yoffest = 0;
    _xoffset = 0;
}

int GameCell::getX() {
    return _uid / BOARD_CELL_WIDTH;
}

int GameCell::getY() {
    return _uid % BOARD_CELL_HEIGHT;
}

int GameCell::getOffset(Direction direction) {
    if(direction == VERTICAL) {
        return _yoffest;
    } else {
        return _xoffset;
    }
}

void GameCell::setOffset(Direction direction, int offset) {
    if(direction == VERTICAL) {
        _yoffest = offset;
    } else {
        _xoffset = offset;;
    }
}

int GameCell::getXOffset() {
    return _xoffset;
}

int GameCell::getYOffset() {
    return _yoffest;
}

void GameCell::setXOffset(int offset) {
    _xoffset = offset;
}
void GameCell::setYOffset(int offset) {
    _yoffest = offset;
}