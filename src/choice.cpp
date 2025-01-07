#include "choice.hpp"

volatile bool buttonPressed = false;
volatile bool optionPressed = false;
unsigned int lastMovement = 0;

volatile int optionNumber = 0;
volatile bool savePlayer = false;
volatile bool gameSession = false;


void buttonPressedChoice()
{
    if (inGame == false && optionPressed == true)
    {
        if (optionNumber == gameOption)
        {
            inGame = true;
            initGrid();
            randomTileInit();
            savePlayer = false;
            gameSession = true;
            optionPressed = false;
        }
        else if (optionNumber == leaderboardOption)
        {
            leaderboard();
        }

        buttonPressed = false;
    }
    else if (!savePlayer)
    {
        lastState();
        buttonPressed = false;
    }
}

void clearMatrix()
{
  for (int i = 0; i < SQUARE_NUMBER; i++)
    for (int j = 0; j < SQUARE_NUMBER; j++)
    {
      matrix[i][j] = 0;
      lastStateMatrix[i][j] = 0;
    }
  score = 0;
  scoreUndo = 0;
  showWin = false;
  afterWin = false;
  matrix[SQUARE_NUMBER][SQUARE_NUMBER] = {0};
  lastStateMatrix[SQUARE_NUMBER][SQUARE_NUMBER] = {0};
}