#ifndef MENU_HPP
#define MENU_HPP

#include "draw.hpp"
#include <Arduino.h>

/* List of defines and variables used for creating the menu display */
#define GAME_TITLE_Y 20
#define TITLE_FONT_OPTIONS 8
#define TEXT_OPTIONS_SIZE 2
#define OPTION_X 40
#define OPTION_Y 120
#define WIDTH_OPTION 240
#define HEIGHT_OPTION 120
#define RADIUS_OPTION 4
#define DISTANCE_OPTIONS 30
#define CENTER_X_TEXT 2
#define CENTER_Y_TEXT 3
extern const char *gameOptions[];
extern volatile int noOptions;

/* Displays the menu options */
void playOptions(int optionNr);


#endif
