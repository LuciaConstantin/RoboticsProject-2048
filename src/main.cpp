//#include <Arduino.h>
//#include <SPI.h> // draw.hpp
#include "choice.hpp"


/* Pins used by the joystick */
const int pinX = 34;
const int pinY = 35;
const int buttonPin = 25;
int valueX = 0;
int valueY = 0;

/* Variables used for debouncing */
volatile unsigned long previousDebounceButton = 0;
const int delayButton = 500;
const int debounceDelay = 500;
unsigned long lastMoveTime = 0;

char move; // the direction of the joystick

/* Function that handles the interrupt */
void IRAM_ATTR pressButton()
{
  if (millis() - previousDebounceButton > delayButton)
  {
    previousDebounceButton = millis();
    buttonPressed = true;

    if (gameState == false && optionNumber != noOptions)
    {
      if (optionNumber == gameOption)
        gameState = true;
      optionPressed = true;
    }
  }
}

void setup(void)
{
  Serial.begin(9600);
  tft.init();
  tft.setRotation(2); // for x, y coordinates
  tft.fillScreen(TFT_SKYBLUE);
  randomSeed(analogRead(12)); // random
  pinMode(buttonPin, INPUT_PULLUP);
  analogSetAttenuation(ADC_11db); // for the joystick to work on 3.3 V not 5 V
  attachInterrupt(buttonPin, pressButton, FALLING); // interrupt for the button
  playOptions(0); // menu
}

void loop()
{

  if (buttonPressed)
  {
    buttonPressedChoice();
  }

  int valueX = analogRead(pinX);
  int valueY = analogRead(pinY);

  unsigned long currentTime = millis();

  if (currentTime - lastMoveTime > debounceDelay)
  {
    move = 'o';
    if ((valueX >= LEFT_X_MIN && valueX <= LEFT_X_MAX) &&
        (valueY >= UP_Y_MIN && valueY <= UP_Y_MAX))
    {
      move = 'w'; // Up
      lastMoveTime = currentTime;
    }
    else if ((valueX >= RIGHT_X_MIN && valueX <= RIGHT_X_MAX) &&
             (valueY >= DOWN_Y_MIN && valueY <= DOWN_Y_MAX))
    {
      move = 's'; // Down
      lastMoveTime = currentTime;
    }
    else if ((valueX >= CENTER_X_MIN && valueX <= CENTER_X_MAX) &&
             (valueY >= TOP_Y_MIN && valueY <= TOP_Y_MAX))
    {
      move = 'd'; // Right
      lastMoveTime = currentTime;
    }
    else if ((valueX >= CENTER_X_MIN && valueX <= CENTER_X_MAX) &&
             (valueY >= BOTTOM_Y_MIN && valueY <= BOTTOM_Y_MAX))
    {
      move = 'a'; // Left
      lastMoveTime = currentTime;
    }
    
    /* Moves the tiles if the game is started */
    if (move != 'o' && gameState == true)
    {
      moveTile(move);
    }
    /* The game session is not over until the player saves their name, even if the game has ended */
    else if (move != 'o' && gameState == false && savePlayer == false && gameSession == true)
    {
      addPlayer();
      savePlayer = true;
    }
    /* Menu select option */
    else if ((move == 'w' || move == 's') && gameState == false)
    {
      if (move == 'w' && optionNumber > 0)
      {
        optionNumber--;
        playOptions(optionNumber);
      }
      else if (move == 's' && optionNumber < (noOptions - 1))
      {
        optionNumber++;
        playOptions(optionNumber);
      }
      inGame = false;
      clearMatrix();
    }
  }
}