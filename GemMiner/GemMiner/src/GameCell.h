//
//  GameCell.hpp
//  GemMiner
//
//  Created by Marcus Rupley on 2/25/17.
//  Copyright © 2017 Marcus Rupley. All rights reserved.
//

#ifndef GameCell_h
#define GameCell_h

#include <stdio.h>
#include <iostream>
#include "GameCellConstants.h"
#include "GameBoardConstants.h"

class GameCell {
public:
    void initialize(int uid, int color);
    int getColor();
    int getUid();
    void setColor(int color);
    int getX();
    int getY();
    int getOffset(Direction direction);
    void setOffset(Direction direction, int offset);
    int getXOffset();
    int getYOffset();
    void setXOffset(int offset);
    void setYOffset(int offset);
private:
    int _color;
    int _uid;
    int _xoffset;
    int _yoffest;
};
#endif /* GameCell_h */
