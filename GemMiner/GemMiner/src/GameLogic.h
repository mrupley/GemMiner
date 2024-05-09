//
//  GameLogic.hpp
//  GemMiner
//
//  Created by Marcus Rupley on 2/25/17.
//  Copyright © 2017 Marcus Rupley. All rights reserved.
//

#ifndef GameLogic_h
#define GameLogic_h

#include <stdio.h>
#include "GameCell.h"
#include "GameBoardConstants.h"
#include "GameBoard.h"

namespace GameLogic {
    
    //Check if the move is a valid move on the board
    bool isValidMove(GameCell firstCell, GameCell secondCell);
    
    //Checks if the cells are directly above, below, to the left, or right of the cell
    bool areCellsAdjacent(GameCell firstCell, GameCell secondCell);
    
    // Are the two cells allowed to be swapped?
    bool isLegalMove(GameCell firstCell, GameCell secondCell);
    
    // has this cell matched into a combination of 3 or more of the same color?
    bool isMatch(GameCell cell);
    
    // returns the cell given an x and y touch on the screen
    GameCell* getCellAtAbsoluteXY(int x, int y);
    
    // gets the cell color at a given x and y coordinate on the board
    int getCellColor(int x, int y);
    
    //loads the gameboard
    void loadGameBoard();
    
    // plays all moves on the board and repositions the board to animate
    void playMove();
    
    // used to prevent plays for cells
    int getNonMatchingColorForCell(int x, int y);
    
    // gets the cell at a given x and y coordinate on the board
    GameCell* getCellOnBoard(int x, int y);
    
    // gets the cell at a given uid on the board
    GameCell* getCellOnBoard(int uid);
    // swaps the colors of two cells
    void swapColors(GameCell* firstCell,GameCell* secondCell);
    
    // sets the cell y offsets for the GameView to animate
    bool setDropAnimation();
    
    // returns true if there is a valid move on the board
    bool hasValidMove();
    
    // gets the player score
    int getScore();
}

#endif /* GameLogic_h */
