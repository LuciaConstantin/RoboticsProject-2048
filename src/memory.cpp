#include "memory.hpp"

Preferences preferences;

String playerKey = "player";
String scoreKey = "score";
String playerName = "player";
String textPlayer = "Enter player name: ";
String textHighScore = "HIGHSCORE!";

bool highScore(int currentScore)
{
    preferences.begin("2048Game", true);
    int32_t totalPlayers = preferences.getUInt("playerNumber", 0);
    int32_t maxScore = 0;

    for (int i = 1; i <= totalPlayers; i++)
    {
        String sKey = scoreKey + String(i);
        int playerScore = preferences.getInt(sKey.c_str(), 0);

        if (playerScore > maxScore)
        {
            maxScore = playerScore;
        }
    }
    preferences.end();

    if (currentScore > maxScore)
    {
        maxScore = currentScore;
        return true;
    }
    else
        return false;
}

void addPlayer()
{
    tft.fillScreen(TFT_SKYBLUE);
    tft.setTextSize(1);
    tft.setTextColor(TFT_DARKCYAN, TFT_SKYBLUE);
    tft.drawCentreString(textPlayer.c_str(), tft.width() / 2, TEXT_PLAYER_Y, TEXT_PLAYER_FONT);

    bool scoreState = highScore(score);

    bool checkPlayer = false;
    /* Waits for the players name */
    Serial.println("Enter player name:");
    while (!Serial.available())
    {
    }

    playerName = Serial.readStringUntil('\n');
    playerName.trim();

    tft.drawCentreString(playerName.c_str(), tft.width() / 2, PLAYER_NAME_Y, TEXT_PLAYER_FONT);

    preferences.begin("2048Game", false);
    int32_t players = preferences.getUInt("playerNumber", 0);

    /* The key and the value stored in the memory can't have more than 15 characters (library requirement)*/
    if (playerName.length() == 0 || playerName.length() > MAX_LENGTH)
    {
        playerName = "player";
    }

    String pKey = playerKey + String(players + 1);
    String sKey = scoreKey + String(players + 1);

    /* Displays HIGHSCORE based on the result from the highScore() function*/
    if (scoreState)
    {
        tft.setTextColor(TFT_PINK, TFT_SKYBLUE);
        tft.drawCentreString(textHighScore.c_str(), tft.width() / 2, TEXT_HIGHSCORE_Y, TEXT_PLAYER_FONT);
    }

    /* Adds the player to memory. If the player already exists, 
    it updates the score only if the current score is higher than the previous one. */
    for (int i = 1; i <= players; i++)
    {
        String checkNameKey = playerKey + String(i);
        String savedName = preferences.getString(checkNameKey.c_str(), "");

        if (savedName == playerName)
        {
            String checkScoreKey = scoreKey + String(i);
            int savedScore = preferences.getInt(checkScoreKey.c_str(), 0);

            if (score > savedScore)
            {
                preferences.putInt(checkScoreKey.c_str(), score);
            }

            checkPlayer = true;
            break;
        }
    }

    if (!checkPlayer)
    {
        players++;
        preferences.putString(pKey.c_str(), playerName.c_str());
        preferences.putInt(sKey.c_str(), score);
    }

    preferences.putUInt("playerNumber", players);
    gameState = false;
    Serial.println("Player saved: " + playerName);
    Serial.println("Score saved: " + String(score));

    inGame = false;
    preferences.end();
}

void readPlayers()
{

    preferences.begin("2048Game", true);
    int totalPlayers = preferences.getUInt("playerNumber", 0);

    Serial.println("Total Players: " + String(totalPlayers));

    for (int i = 1; i <= totalPlayers; i++)
    {
        String pKey = playerKey + String(i);
        String sKey = scoreKey + String(i);

        String savedName = preferences.getString(pKey.c_str(), "N/A");
        int savedScore = preferences.getInt(sKey.c_str(), 0);

        Serial.println("Player " + String(i) + ": " + savedName);
        Serial.println("Score: " + String(savedScore));
    }

    preferences.end();
}

void resetMemory()
{
    preferences.begin("2048Game", false);
    preferences.clear();
    preferences.end();
    Serial.println("All player data has been cleared!");
}

void leaderboard()
{
    preferences.begin("2048Game", true);
    int totalPlayers = preferences.getUInt("playerNumber", 0);

    String playerNames[10];
    int playerScores[10];

    for (int i = 0; i < 10; i++)
    {
        playerNames[i] = "N/A";
        playerScores[i] = 0;
    }

    for (int i = 1; i <= totalPlayers; i++)
    {
        String pKey = playerKey + String(i);
        String sKey = scoreKey + String(i);

        String savedName = preferences.getString(pKey.c_str(), "N/A");
        int savedScore = preferences.getInt(sKey.c_str(), 0);

        for (int j = 0; j < 10; j++)
        {
            if (savedScore > playerScores[j])
            {
                for (int k = 9; k > j; k--)
                {
                    playerScores[k] = playerScores[k - 1];
                    playerNames[k] = playerNames[k - 1];
                }
                playerScores[j] = savedScore;
                playerNames[j] = savedName;
                break;
            }
        }
    }

    tft.fillScreen(TFT_SKYBLUE);
    tft.setTextSize(1);
    tft.setTextColor(TFT_DARKCYAN, TFT_SKYBLUE);
    tft.drawCentreString("TOP 10 PLAYERS", tft.width() / 2, TEXT_LEADERBOARD, TEXT_PLAYER_FONT);

    for (int i = 0; i < 10; i++)
    {
        if (playerNames[i] != "N/A")
        {
            String playerInfo = String(i + 1) + ". " + playerNames[i] + " - " + String(playerScores[i]);
            tft.drawCentreString(playerInfo.c_str(), tft.width() / 2, TEXT_PLAYER_Y + i * DISTANCE, TEXT_PLAYER_FONT);
        }
    }

    preferences.end();
}