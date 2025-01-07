#include "draw.hpp"

TFT_eSPI tft = TFT_eSPI();

String gameTitle = "2048";
String scoreTitle = "Score"; 
int32_t score = 0; // score of the player
 
void initGrid()
{
    int16_t i, j, x, y;
    tft.fillScreen(TFT_SKYBLUE);
    
    /* Creates a 4x4 grid using squares */
    for (j = 0; j < SQUARE_NUMBER; j++)
    {
        y = START_Y + (WIDTH + SPACE_SQUARE) * j;

        for (i = 0; i < SQUARE_NUMBER; i++)
        {
            x = START_X + (WIDTH + SPACE_SQUARE) * i;
            tft.drawRect(x, y, WIDTH, WIDTH, TFT_DARKCYAN);
        }
    }
    
    /* Displays the score in the center */
    String scoreText = scoreTitle + ": " + String(score);
    tft.setTextSize(1);
    tft.setTextColor(TFT_DARKCYAN, TFT_SKYBLUE);
    tft.drawCentreString(scoreText.c_str(), tft.width() / 2, SCORE_Y, SCORE_FONT);

    /* Show game title "2048" */
    tft.setTextSize(1);
    tft.setTextColor(TFT_DARKCYAN, TFT_SKYBLUE);
    x = tft.width() / 2;
    y = TITLE_Y;
    tft.drawCentreString(gameTitle.c_str(), x, TITLE_Y, TITLE_FONT);
}

uint16_t tileColorByNumber(int tileNumber)
{
    switch (tileNumber)
    {
    case TILE_2:
        return TFT_OLIVE;
        break;
    case TILE_4:
        return TFT_BLUE;
        break;
    case TILE_8:
        return TFT_DARKCYAN;
        break;
    case TILE_16:
        return TFT_GREEN;
        break;
    case TILE_32:
        return TFT_VIOLET;
        break;
    case TILE_64:
        return TFT_ORANGE;
        break;
    case TILE_128:
        return TFT_RED;
        break;
    case TILE_256:
        return TFT_MAGENTA;
        break;
    case TILE_512:
        return TFT_PASET;
        break;
    case TILE_1024:
        return TFT_NAVY;
        break;
    case TILE_2048:
        return TFT_PINK;
        break;
    case TILE_4096:
        return TFT_GOLD;
    case TILE_8192:
        return TFT_BROWN;
    case TILE_16384:
        return TFT_BLACK;
    default:
        return TFT_PINK;
    }
}

void drawTile(int x, int y, int tileNumber)
{

    uint16_t tileColor = tileColorByNumber(tileNumber);

    if (tileNumber == TILE_NULL)
    {
        tft.fillRect(x, y, WIDTH, WIDTH, TFT_SKYBLUE);
        tft.drawRect(x, y, WIDTH, WIDTH, TFT_DARKCYAN);
    }
    else
        tft.fillRect(x, y, WIDTH, WIDTH, tileColor);

    tft.setTextDatum(MC_DATUM); // Sets text in middle centre
    int8_t textSize = TEXT_TILE_SIZE;
    
    /* If the number has more than 4 digits the font needs to be decreased to fit in the tile */
    if (tileNumber >= TILE_1024)
        textSize = TEXT_TILE_SIZE_SMALLER;

    tft.setTextSize(textSize);
    tft.setTextColor(TFT_WHITE);

    /* Draw text in the center of the tile */
    if (tileNumber != TILE_NULL)
        tft.drawString(String(tileNumber), x + (WIDTH + START_X) / 2, y + (WIDTH + START_Y) / 2);
}

