FRAMEWORKS USED:
SDL2_ttf.framework
SDL2_image.framework
SDL2.framework

FONT IMPORTED:
lazy.ttf

My goal for the architecture was to separate the GameLogic, GameView, and GameWindow from one another. GameLogic.cpp file holds the gameBoard and all relevant logical data for making moves and applying them. GameView.cpp holds all of the animation sequences, and it interfaces with GameWindow.cpp, which holds the SDL surfaces. GameBoard.cpp is the Gameboard itself, and GameCell holds data for each individual cell. The remaining files hold constants and Sprite data.

The constants can be manipulated to change the animation speed, the game timer, variety of game cells, and the game board dimensions. The gameboard is playable in any board with equal dimensions with at least 2 colors with minor modifications to NUMBER_COLORS, the number of sprite objects, the size / spacing of the board, and the game board dimensions. I also included a score into the game to make the game more fun.

I took care to limit the number of operations done on the main UI thread while drawing, since those are performed once every frame. Such optimizations as only updating the timer once a second and updating the score only when it increases were accounted for.

I have included the XCode Project as well as the OSX executable.

Cheers,
Marc Rupley