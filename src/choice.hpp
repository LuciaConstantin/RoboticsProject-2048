#ifndef CHOICE_HPP
#define CHOICE_HPP

#include "draw.hpp"
#include "tile.hpp"
#include "moves.hpp"
#include "menu.hpp"
#include "memory.hpp"

extern volatile bool buttonPressed; // if the button was pressed
extern volatile bool optionPressed; // if one of the option was pressed 
extern volatile int optionNumber; // what option the user choses
extern volatile bool savePlayer; // if the player is saved
extern volatile bool gameSession; // if the game is over but the player still hasn't saved their name.
//extern unsigned int lastMovement; 

#define leaderboardOption 1
#define gameOption 0

/* Values used for detecting the exact movement of the joystick */
#define LEFT_X_MIN 0
#define LEFT_X_MAX 50
#define RIGHT_X_MIN 4045
#define RIGHT_X_MAX 4095

#define UP_Y_MIN 1700
#define UP_Y_MAX 1900
#define DOWN_Y_MIN 1700
#define DOWN_Y_MAX 1900

#define CENTER_X_MIN 1800
#define CENTER_X_MAX 2000
#define TOP_Y_MIN 0
#define TOP_Y_MAX 50
#define BOTTOM_Y_MIN 4045
#define BOTTOM_Y_MAX 4095

/* handles button press actions by starting the game, displaying the leaderboard, 
or performing an undo operation based on the current state and selected options*/
void buttonPressedChoice();

/* Clears the matrix for the next game */
void clearMatrix();

#endif