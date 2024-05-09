//
//  GameBoard.hpp
//  GemMiner
//
//  Created by Marcus Rupley on 2/25/17.
//  Copyright © 2017 Marcus Rupley. All rights reserved.
//

#ifndef GameBoard_h
#define GameBoard_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Image.h"
#include "GameCell.h"
#include "GameCellConstants.h"
#include "GameBoardConstants.h"
#include "GameLogic.h"

class GameBoard {
public:
    // loads the initial GameBoard
    void loadGameBoard();
    
    // Gets the valid cell from the X and Y coordinates of the view
    GameCell* getCellAtAbsoluteXY(int x, int y);
    // Gets the color of the cell based on its x and y index
    int getCellColorOnBoard(int x, int y);
    
    // Gets the cell based on its x and y index
    GameCell* getCellOnBoard(int x, int y);

    // Gets the cell based on its unique identifier
    GameCell* getCellOnBoard(int uid);
    
    // Gets the color of the cell based on its unique identifier
    int getCellColorOnBoard(int uid);
private:
    bool isValidCell(int x, int y);
};

#endif /* GameBoard_h */
