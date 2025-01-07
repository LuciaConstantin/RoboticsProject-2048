#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <Preferences.h>
#include <Arduino.h>
#include "draw.hpp"
#include "tile.hpp"
#include "moves.hpp"

extern Preferences preferences;

/* For the leaderboard display */
extern String playerKey;
extern String scoreKey;
extern String playerName;
extern String textPlayer;
extern String textHighScore;

#define TEXT_PLAYER_Y 200
#define DISTANCE 20
#define TEXT_LEADERBOARD 50
#define TEXT_PLAYER_FONT 4
#define PLAYER_NAME_Y 250
#define TEXT_HIGHSCORE_Y 150
#define MAX_LENGTH 15

/* Adds a player at the end of the game */
void addPlayer();

/* Displays all the players and their score */
void readPlayers();

/* Clears all the data stored in the NVS memory */
void resetMemory();

/* Finds if the current player has the highest score */
bool highScore(int currentScore);

/* Displays the first 10 players with the highest score in the game */
void leaderboard();



#endif


