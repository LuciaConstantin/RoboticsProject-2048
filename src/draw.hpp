#ifndef DRAW_HPP
#define DRAW_HPP

#include <TFT_eSPI.h>
#include <SPI.h>

extern TFT_eSPI tft; // instance of the TFT_eSPI class

/* Define variables for the grid */
#define START_X 4
#define START_Y 4
#define WIDTH 75
#define SQUARE_NUMBER 4
#define SPACE_SQUARE 4
#define TITLE_Y 420
#define TITLE_FONT 6

extern String gameTitle; // strores the title of the game

/* Define variables for tiles */
#define TILE_NULL 0
#define TILE_2 2
#define TILE_4 4
#define TILE_8 8
#define TILE_16 16
#define TILE_32 32
#define TILE_64 64
#define TILE_128 128
#define TILE_256 256
#define TILE_512 512
#define TILE_1024 1024
#define TILE_2048 2048
#define TILE_4096 4096
#define TILE_8192 8192
#define TILE_16384 16384
#define NUMBER_START_TILES 2
#define TEXT_TILE_SIZE 4
#define TEXT_TILE_SIZE_SMALLER 3

/* Defines for player score display */
#define SCORE_Y 390
#define SCORE_FONT 4

extern String scoreTitle; // stores the string that will be displayed on the screen
extern int32_t score;     // stores the players score

/*The function draws the 4x4 grid*/
void initGrid();

/* The function determines the exact color for each tile number (2, 4, 8, etc. ) */
uint16_t tileColorByNumber(int tileNumber);

/* Draws tiles based on the coordinates and the tile number */
void drawTile(int x, int y, int tileNumber);

#endif