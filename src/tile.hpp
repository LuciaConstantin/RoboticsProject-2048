#ifndef TILE_HPP
#define TILE_HPP

#include <Arduino.h>
#include "draw.hpp"

/* The matrix used to store the tiles for the game */
extern volatile int16_t matrix[SQUARE_NUMBER][SQUARE_NUMBER];
extern volatile int16_t lastStateMatrix[SQUARE_NUMBER][SQUARE_NUMBER];
extern bool gameState;

extern String winText; // stores the win text
#define TEXT_SIZE 6

/* x, y coordinates of the top-left corner of the rectangle used for random */
struct coordinates
{
    int16_t X;
    int16_t Y;
};

/* x, y coordinates of the top-left corner of the rectangle used for display on the LCD */
struct gridTileCoordinates
{
    int16_t xGrid;
    int16_t yGrid;
};

/* Generates random coordinates for a new tile */
coordinates randomCoordinates();

/* Calculates the x, y coordinates for the LCD display */
gridTileCoordinates getGridCoordinates(int x, int y);

/* Generates a random tile */
void generateTile(int tileNumber);

/* Displays YOU WIN ! on the LCD when the player reaches the 2048 tile */
void win();

/* Generates the 2 random tiles at the begining of the game */
void randomTileInit();

#endif