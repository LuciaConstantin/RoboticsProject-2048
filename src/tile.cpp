#include "tile.hpp"

bool gameState = false;
String winText = "YOU WIN!";
volatile int16_t matrix[SQUARE_NUMBER][SQUARE_NUMBER] = {0};
volatile int16_t lastStateMatrix[SQUARE_NUMBER][SQUARE_NUMBER] = {0};

void win()
{
    tft.fillScreen(TFT_SKYBLUE);
    tft.setTextDatum(MC_DATUM);
    tft.setTextSize(TEXT_SIZE);
    tft.setTextColor(TFT_DARKCYAN);
    tft.drawString(String(winText), tft.width() / 2, tft.height() / 2);
}

coordinates randomCoordinates()
{
    struct coordinates tileCoordinates;
    tileCoordinates.X = random(SQUARE_NUMBER);
    tileCoordinates.Y = random(SQUARE_NUMBER);
    return tileCoordinates;
}

gridTileCoordinates getGridCoordinates(int x, int y)
{
    struct gridTileCoordinates gridTileCoord;
    gridTileCoord.xGrid = START_X + (WIDTH + SPACE_SQUARE) * x;
    gridTileCoord.yGrid = START_Y + (WIDTH + SPACE_SQUARE) * y;
    return gridTileCoord;
}


void generateTile(int tileNumber)
{
    int16_t i, j; // x, y coordinates
    struct coordinates tileRandomCoordinates;
    struct gridTileCoordinates tileCoord;

    tileRandomCoordinates = randomCoordinates();
    while (matrix[tileRandomCoordinates.X][tileRandomCoordinates.Y] != 0)
    {
        tileRandomCoordinates = randomCoordinates();
    }

    matrix[tileRandomCoordinates.X][tileRandomCoordinates.Y] = tileNumber;
    tileCoord = getGridCoordinates(tileRandomCoordinates.X, tileRandomCoordinates.Y);
    drawTile(tileCoord.xGrid, tileCoord.yGrid, tileNumber);
}

void randomTileInit()
{
    int i, j;
    for (i = 0; i < NUMBER_START_TILES; i++)
        generateTile(TILE_2);

    for (j = 0; j < SQUARE_NUMBER; j++)
        for (i = 0; i < SQUARE_NUMBER; i++)
        {
            lastStateMatrix[i][j] = matrix[i][j];
        }
}