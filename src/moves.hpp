#ifndef MOVES_HPP
#define MOVES_HPP

#include <Arduino.h>
#include "draw.hpp"
#include "tile.hpp"


/* If the grid is full of tiles but there are still possible merges between tiles, the game is not over and it returns this variable */
const int16_t notOver = 3;

extern int n, s, e, w; // up, down, right, left

extern const int initMove; // no move is detected
extern const int16_t randomTile;
extern int randomTileNumber;
extern int16_t auxMatrix[SQUARE_NUMBER][SQUARE_NUMBER];
extern bool modified; // checks if the matrix was modified after a move
extern int32_t scoreUndo; // the previous score
extern int32_t auxScore;
extern bool showWin; // ensures that the YOU WIN! text is displayed only once right after the aparition of the 2048 tile
extern bool afterWin; // // Used to make the "YOU WIN" text disappear.  

extern String gameOverText; // stores the game over text

extern bool inGame; // If the player has not saved their score, they can still re-enter the game using the undo button.

/* Functions for moving and merging the tiles on the grid */
int16_t slideUp(bool finale);
int16_t slideDown(bool finale);
int16_t slideRight(bool finale);
int16_t slideLeft(bool finale);

/* Checks if the game is over and displays GAME OVER on the LCD */
void checkGameOver();

/* Receives the direction from the joystick and invokes the appropriate slide function */
void moveTile(char direction);

/* If the joystick's button is pressed, the game returns to the previous tile arrangement */
void lastState();



#endif