#include "menu.hpp"

const char *gameOptions[] = {"PLAY", "Leaderboard"};
volatile int noOptions = sizeof(gameOptions) / sizeof(gameOptions[0]);

void playOptions(int optionNr)
{
  tft.fillScreen(TFT_SKYBLUE);
  tft.setTextSize(1);
  tft.setTextColor(TFT_DARKCYAN, TFT_SKYBLUE);
  
  /* draws the game title */
  int x = tft.width() / 2;
  tft.drawCentreString(gameTitle.c_str(), x, GAME_TITLE_Y, TITLE_FONT_OPTIONS);

  tft.setTextDatum(MC_DATUM);
  int8_t textSize = TEXT_OPTIONS_SIZE;
  tft.setTextSize(textSize);
  tft.setTextColor(TFT_WHITE);
  
  /* changing the color of the button, if selected by the player */
  for (int i = 0; i < noOptions; i++)
  {
    int optionY = OPTION_Y + i * (HEIGHT_OPTION + DISTANCE_OPTIONS);
    if (i == optionNr)
    {
      tft.drawRoundRect(OPTION_X, optionY, WIDTH_OPTION, HEIGHT_OPTION, RADIUS_OPTION, TFT_MAGENTA);
      tft.fillRoundRect(OPTION_X, optionY, WIDTH_OPTION, HEIGHT_OPTION, RADIUS_OPTION, TFT_MAGENTA);
    }
    else
    {
      tft.drawRoundRect(OPTION_X, optionY, WIDTH_OPTION, HEIGHT_OPTION, RADIUS_OPTION, TFT_NAVY);
      tft.fillRoundRect(OPTION_X, optionY, WIDTH_OPTION, HEIGHT_OPTION, RADIUS_OPTION, TFT_NAVY);
    }
    tft.drawCentreString(gameOptions[i], OPTION_X + WIDTH_OPTION / CENTER_X_TEXT, optionY + HEIGHT_OPTION / CENTER_Y_TEXT, TEXT_OPTIONS_SIZE);
  }
}