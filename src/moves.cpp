#include "moves.hpp"

int n, s, e, w;
const int initMove = 0;

const int16_t randomTile = 1;

int randomTileNumber;
int16_t auxMatrix[SQUARE_NUMBER][SQUARE_NUMBER] = {0};
bool modified;
String gameOverText = "GAME OVER";

bool inGame = false;
int32_t scoreUndo = 0;
int32_t auxScore = 0;
bool showWin = false;
bool afterWin = false;


int16_t slideUp(bool finale)
{
  int i, j, aux, ok;
  /* Prevents multiple merges in one swipe, e.g., 2 2 2 2 becomes 4 4 instead of 8 */
  bool combined[SQUARE_NUMBER][SQUARE_NUMBER] = {false};
  j = 1;
  ok = 0;

  while (j != SQUARE_NUMBER)
  {
    for (i = 0; i < SQUARE_NUMBER; i++)
    {
      if (matrix[i][j] != 0)
      {
        aux = j;
        /* Move the tile upwards as long as it stays within grid boundaries and the above cell is empty */
        while (aux > 0 && matrix[i][aux - 1] == 0)
        {
          /*
           The 'finale' variable is used to check whether there are any possible merges left
           when the grid is full. If 'finale' is true, the matrix should not be modified,
           as the function is only checking for game-over conditions.
          */
          if (finale == false)
          {
            aux--;
            matrix[i][aux] = matrix[i][aux + 1];
            matrix[i][aux + 1] = TILE_NULL;
            ok = 1;
          }
          else
            return notOver;
        }

        /* Merge with the tile above if they are equal and haven't been merged already */
        if ((aux - 1) >= 0 && matrix[i][aux - 1] == matrix[i][aux] && !combined[i][aux - 1])
        {
          if (finale == false)
          {
            matrix[i][aux - 1] *= 2;
            matrix[i][aux] = TILE_NULL;
            combined[i][aux - 1] = true;
            ok = 1;
            score += matrix[i][aux - 1];
          }
          else
            return notOver;
        }
      }
    }
    j++;
  }

  /*
   Return 'ok = 1' if any tiles were moved or merged during the swipe.
   Otherwise, return 'ok = 0' if no action occurred on the grid.
  */
  return ok;
}

int16_t slideDown(bool finale)
{
  int i, j, aux, ok;
  bool combined[SQUARE_NUMBER][SQUARE_NUMBER] = {false};
  j = SQUARE_NUMBER - 2;
  ok = 0;

  while (j >= 0)
  {
    for (i = 0; i < SQUARE_NUMBER; i++)
    {
      if (matrix[i][j] != 0)
      {
        aux = j;

        while (aux < SQUARE_NUMBER - 1 && matrix[i][aux + 1] == 0)
        {
          if (finale == false)
          {
            aux++;
            matrix[i][aux] = matrix[i][aux - 1];
            matrix[i][aux - 1] = TILE_NULL;
            ok = 1;
          }
          else
            return notOver;
        }

        if ((aux + 1) < SQUARE_NUMBER && matrix[i][aux + 1] == matrix[i][aux] && !combined[i][aux + 1])
        {
          if (finale == false)
          {
            matrix[i][aux + 1] *= 2;
            matrix[i][aux] = TILE_NULL;
            combined[i][aux + 1] = true;
            ok = 1;
            score += matrix[i][aux + 1];
          }
          else
            return notOver;
        }
      }
    }
    j--;
  }

  return ok;
}

int16_t slideRight(bool finale)
{
  int i, j, aux, ok;
  bool combined[SQUARE_NUMBER][SQUARE_NUMBER] = {false};

  j = 0;
  ok = 0;

  while (j < SQUARE_NUMBER)
  {
    for (i = SQUARE_NUMBER - 2; i >= 0; i--)
    {
      if (matrix[i][j] != 0)
      {
        aux = i;

        while (aux < SQUARE_NUMBER - 1 && matrix[aux + 1][j] == 0)
        {
          if (finale == false)
          {
            aux++;
            matrix[aux][j] = matrix[aux - 1][j];
            matrix[aux - 1][j] = TILE_NULL;
            ok = 1;
          }
          else
            return notOver;
        }

        if ((aux + 1) < SQUARE_NUMBER && matrix[aux + 1][j] == matrix[aux][j] && !combined[aux + 1][j])
        {
          if (finale == false)
          {
            matrix[aux + 1][j] *= 2;
            matrix[aux][j] = TILE_NULL;
            combined[aux + 1][j] = true;
            ok = 1;
            score += matrix[aux + 1][j];
          }
          else
            return notOver;
        }
      }
    }
    j++;
  }

  return ok;
}

int16_t slideLeft(bool finale)
{
  int i, j, aux, ok;
  bool combined[SQUARE_NUMBER][SQUARE_NUMBER] = {false};

  j = 0;
  ok = 0;

  while (j < SQUARE_NUMBER)
  {
    for (i = 1; i < SQUARE_NUMBER; i++)
    {
      if (matrix[i][j] != 0)
      {
        aux = i;

        while (aux > 0 && matrix[aux - 1][j] == 0)
        {
          if (finale == false)
          {
            aux--;
            matrix[aux][j] = matrix[aux + 1][j];
            matrix[aux + 1][j] = TILE_NULL;
            ok = 1;
          }
          else
            return notOver;
        }

        if ((aux > 0) && matrix[aux - 1][j] == matrix[aux][j] && !combined[aux - 1][j])
        {
          if (finale == false)
          {
            matrix[aux - 1][j] *= 2;
            matrix[aux][j] = TILE_NULL;
            combined[aux - 1][j] = true;
            ok = 1;
            score += matrix[aux - 1][j];
          }
          else
            return notOver;
        }
      }
    }
    j++;
  }

  return ok;
}

void checkGameOver()
{
  /* Checks if there are still possible moves or merges on the grid */
  bool checkFinale = true;
  n = slideUp(checkFinale);
  s = slideDown(checkFinale);
  e = slideRight(checkFinale);
  w = slideLeft(checkFinale);
  
  /* If not even one of the above functions returs notOver then the game is over and it will be displayed on the screen */
  if (!(n == notOver || s == notOver || e == notOver || w == notOver))
  { 
    gameState = false;
    /* Game over dispay */
    tft.fillScreen(TFT_BLACK);
    tft.setTextDatum(MC_DATUM);
    tft.setTextSize(TEXT_SIZE);
    tft.setTextColor(TFT_WHITE);
    tft.drawString(String(gameOverText), tft.width() / 2, tft.height() / 2);

    /*Score display*/
    String scoreText = scoreTitle + ": " + String(score);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE);
    tft.drawCentreString(scoreText.c_str(), tft.width() / 2, SCORE_Y, SCORE_FONT);
    
    inGame = true;
  }
}

void moveTile(char direction)
{
  int16_t i, j;
  bool checkFinale;
  checkFinale = false;
  n = s = w = e = initMove;

  modified = false;
  for (j = 0; j < SQUARE_NUMBER; j++)
    for (i = 0; i < SQUARE_NUMBER; i++)
      auxMatrix[i][j] = matrix[i][j];

  auxScore = score;

  // clear the text YOU WIN!
  if (showWin == true && afterWin == false)
  {
    initGrid();
    afterWin = true;
  }
  
  
  switch (direction)
  {
  case 'w':
    n = slideUp(checkFinale);
    Serial.println("Up");
    break;
  case 's':
    s = slideDown(checkFinale);
    Serial.println("Down");
    break;
  case 'd':
    e = slideRight(checkFinale);
    Serial.println("Right");
    break;
  case 'a':
    w = slideLeft(checkFinale);
    Serial.println("Left");
    break;
  }
  
  /* Redraws the grid based on the matrix and cjecks if the grid is full */
  checkFinale = true;
  struct gridTileCoordinates tileCoord;
  for (j = 0; j < SQUARE_NUMBER; j++)
  {
    for (i = 0; i < SQUARE_NUMBER; i++)
    {
      tileCoord = getGridCoordinates(i, j);
      drawTile(tileCoord.xGrid, tileCoord.yGrid, matrix[i][j]);
      if (matrix[i][j] == 0)
        checkFinale = false;
    }
  }
  
  /* If the slide of the joystick modifies the grid it will generate a new tile */
  if ((n == randomTile || s == randomTile || e == randomTile || w == randomTile) && checkFinale == false)
  {
    randomTileNumber = random(0, 101);
    if (randomTileNumber < 80)
      generateTile(TILE_2);
    else
      generateTile(TILE_4);
  }

  modified = false;
  checkFinale = true;
  /*Used in case the player makes repeated moves in the same direction that have no effect on the grid, ensuring the last state is not lost */
  for (j = 0; j < SQUARE_NUMBER; j++)
  {
    for (i = 0; i < SQUARE_NUMBER; i++)
    {
      if (matrix[i][j] == 0)
        checkFinale = false;

      if (auxMatrix[i][j] != matrix[i][j])
        modified = true;

      if (matrix[i][j] == TILE_2048 && showWin == false)
      {
        win();
        showWin = true;
      }
    }
  }

  if (modified == true)
  {
    for (j = 0; j < SQUARE_NUMBER; j++)
      for (i = 0; i < SQUARE_NUMBER; i++)
        lastStateMatrix[i][j] = auxMatrix[i][j];

    scoreUndo = auxScore;
  }

  // score display
  String scoreText = scoreTitle + ": " + String(score);
  tft.setTextSize(1);
  tft.setTextColor(TFT_DARKCYAN, TFT_SKYBLUE);
  tft.drawCentreString(scoreText.c_str(), tft.width() / 2, SCORE_Y, SCORE_FONT);
  
  /* If the gird is full check if the game is over */
  if (checkFinale == true)
    checkGameOver();
}

void lastState()
{
  Serial.println("Undo");
  if (gameState == false)
  {
    gameState = true;
    tft.fillScreen(TFT_SKYBLUE);
    initGrid();
  }
  tft.fillScreen(TFT_SKYBLUE);
  int i, j;
  bool checkFinale = true;
  struct gridTileCoordinates tileCoord;
  bool checkWin = false;
  

  for (j = 0; j < SQUARE_NUMBER; j++)
  {
    for (i = 0; i < SQUARE_NUMBER; i++)
    {
      tileCoord = getGridCoordinates(i, j);
      drawTile(tileCoord.xGrid, tileCoord.yGrid, lastStateMatrix[i][j]);
      matrix[i][j] = lastStateMatrix[i][j];
      score = scoreUndo;
      if (matrix[i][j] >= TILE_2048)
        checkWin = true;
    }
  }
  
  /* If, right after the appearance of the 2048 tile, the player presses undo,  
   and later merges a new 2048 tile, the "YOU WIN" text will still be displayed. */
  if (checkWin == false)
  {
    showWin = false;
    afterWin = false;
  }

  // score display
  String scoreText = scoreTitle + ": " + String(score);
  tft.setTextSize(1);
  tft.setTextColor(TFT_DARKCYAN, TFT_SKYBLUE);
  tft.drawCentreString(scoreText.c_str(), tft.width() / 2, SCORE_Y, SCORE_FONT);

  // title display
  tft.setTextSize(1);
  tft.setTextColor(TFT_DARKCYAN, TFT_SKYBLUE);
  tft.drawCentreString(gameTitle.c_str(), tft.width() / 2, TITLE_Y, TITLE_FONT);
}