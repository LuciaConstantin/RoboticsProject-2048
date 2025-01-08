
# 2048 Game

## Introduction  
* This project implements the popular game "2048," commonly found on smartphones and computers, now brought to life on a microcontroller.  
* The purpose of this game is simple yet engaging: the player slides numbered tiles across a grid, merging them to reach the desired 2048 tile.  
* The idea behind this project was to create an interactive and engaging experience for my robotics course, and what could be more interactive than a game? Over the years, one game that has always stood out to me and kept me entertained on my phone is 2048. So I decided to take on the challenge of implementing a new version of this game using a microcontroller.  
* The main utility of this game is mainly for learning. It offers a practical insight into how both software and hardware components communicate in order to create a fully functional project.   
## Project Description 

   A 4x4 game board is displayed on an LCD screen. The player interacts with the game using a joystick. There are four possible directions in which the tiles can move using the joystick: N(up), S(down), E(left) and W(right). By pressing the joystick button, the player can return to the previous game state, effectively undoing the last action (the last move will be reversed). The joystick is also used for starting the game. The player wins when they reach the 2048 tile. The game continues until the board is full, and no further moves or merges are possible. A leaderboard keeps track of every player's name and their highest achieved score.  
   
   ### Block diagram  
![image](https://github.com/user-attachments/assets/8d8c14bb-bbcc-4d6f-80ce-eb6894100840)  

### Components description  

#### Microcontroller  
            The project is based on the ESP32 microcontroller, using the NodeMCU ESP32 development board that integrates the ESP32-WROOM-32 module (processor). The ESP32 is ideal for handling complex tasks, including high-resolution graphics, making it perfect for controlling a high-resolution LCD.    

* Power Supply: The development board is powered via a USB-C connector, which provides 5V. However, the ESP32 itself operates at 3.3 V for proper functioning.  

* Interfaces: In this project the ESP32 is going to communicate with the components using the next communication interfaces: SPI, ADC, and GPIO. These interfaces are used to connect various external modules like the LCD and the joystick.

#### Flash memory
            In order to store the leaderboard, I decided to use the internal memory (Flash) of the ESP32. The Flash memory will be managed using the Non-Volatile Storage (NVS) system, which allows the leaderboard data (player names and scores) to persist even after the device is powered off. The library that implements it is [Preferences.h](https://components101.com/modules/joystick-module). 

* Communication: The communication interface is QSPI and is managed by the hardware.  

#### LCD Display (TFT 3.5” ILI9488 SPI)  
            Because I choose to recreate the popular 2048 game, of course I need a screen to display the grid and the blocks. I chose a 3.5-inch TFT LCD with a resolution of 480x320 pixels, driven by an ILI9488 controller. The display communicates with the microcontroller via the SPI interface, which allows for fast data transfer required for rendering complex images in real-time. To use the LCD screen I included the [TFT_eSPI.h library](https://github.com/Bodmer/TFT_eSPI).

* Power supply: The LCD display requires a 3.3V power supply.  

* Communication: The communication interface is a 4-wire SPI interface, which is going to be used for receiving data from the microcontroller at every correct move from the joystick.  

#### Joystick  
            The main action of the game is moving the components (the blocks) on the display. But how to move them? I choose a joystick to take care of this task.  

            The joystick is used to allow the player to control the movement of the blocks on the screen. The joystick has two axes (X and Y) for directional control, along with a button for additional functionality (start game, return to the last block configuration).  

* Power supply: The joystick requires 5V to operate.  

* Communication: The joystick communicates with the ESP32 via ADC (Analog-to-Digital Converter) for the X and Y axes (it’s needed for the up, down, left, and right movements). The button of the joystick is connected to a GPIO pin (software: it triggers an interrupt each time it is pressed).  


#### ESP32 and communication  
            Starting with the core of the project, the ESP32 microcontroller is connected to both the LCD display and the joystick. It receives data from the joystick and transmits data to the LCD display. The data that the microcontroller receives from the joystick comes from the ADC (for the joystick's X and Y axis movement) or from a GPIO pin (for the button press). The ADC provides the coordinates of the joystick (representing movement along the X and Y axes), or the GPIO pin reads the low-level signal from the button when pressed, so the microcontroller can interpret these inputs and transmit the appropriate changes to the LCD.  

            The LCD receives data via the SPI interface, specifically through the MOSI (Master Out Slave In) line. This transmission happens after the SCK (Serial Clock) is set to the correct frequency, and the LCD is selected using the CS (Chip Select) pin. The SPI protocol ensures fast data transfer, which is ideal for real-time updates of the game state on the LCD display. At the end of the game the player's name and score are going to be saved in the Flash memory.

## Hardware Design  
### Electrical diagram
<img src="https://github.com/user-attachments/assets/9011578e-7e49-4d31-9a70-444d3515cf47" width="600" height="400" />

### Bill of materials
| Component  | Image | Model    | Number| More information |
| ------------- | ------------- | -------------| -------------| -------------|
| Breadboard  |<img src="https://github.com/user-attachments/assets/55cbcf73-1f63-4177-8bd7-0ffa49542146" width="200" height="150" />|Full-sized | 1 | |
| ESP32  | <img src="https://github.com/user-attachments/assets/026a77de-8c00-4a6d-8f2f-649a00fe299f" width="200" height="150" />  | NodeMCU ESP32-WROOM-32 | 1 |[Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)|
| LCD display| <img src="https://github.com/user-attachments/assets/7055b37e-b3f8-48d7-8d5b-3e9809a03cc5" width="200" height="150" /> |ILI9488 | 1 |[Store](https://www.aliexpress.com/item/1005004804238339.html?srcSns=sns_WhatsApp&spreadType=socialShare&bizType=ProductDetail&social_params=60906366425&aff_fcid=a99f5a0b35fd44c9ba29427c56272109-1733949640719-04325-_EHL67gs&tt=MG&aff_fsk=_EHL67gs&aff_platform=default&sk=_EHL67gs&aff_trace_key=a99f5a0b35fd44c9ba29427c56272109-1733949640719-04325-_EHL67gs&shareId=60906366425&businessType=ProductDetail&platform=AE&terminal_id=c35ec2ea804245d1a09f2fcf4cb090a3&afSmartRedirect=y)|
|Joystick|<img src="https://github.com/user-attachments/assets/0b548984-f1c7-4462-a541-aa6dd952a5d7" width="200" height="150" />  | PS2| 1 | [Web page](https://components101.com/modules/joystick-module)|
|USB cable| <img src="https://github.com/user-attachments/assets/0eaf8059-35f7-44d0-9889-27fa78e2b5ef" width="200" height="150" />|Type C| 1 | 
| Jumper wires|<img src="https://github.com/user-attachments/assets/13757708-58f6-4406-9dc5-f7975762d86a" width="200" height="150" /> | Male-Male, Male-Female | many |  

### ESP32 pins  
<img src="https://github.com/user-attachments/assets/1107771c-000d-4476-985c-88bf267c6cad" width="600" height="400" />


| Pin | Functionality | Use|
| ------------- | ------------- | -------------|
| 3.3V | 3.3V power supply | Provides a 3.3V power supply to components in the circuit|
|GND| ground | Ground is the reference point for all voltages in the circuit, ensuring that the components operate correctly|
|GPIO34| ADC| Reads the VRx analog voltage from the joystick|
|GPIO35| ADC| Reads the VRx analog voltage from the joystick|
|GPIO25| Digital Input/Output (I/O)| Connected to the joystick's button, reads the button state|
|GPIO19| SPI MISO| Connected to the LCD, receives data from the LCD|
|GPIO23| SPI MOSI| Connected to the LCD, transmits data to the LCD|
|GPIO18| SPI SCLK| Connected to the LCD, generates the clock signal to synchronize data transfer between the controller and the peripheral|
|GPIO15| SPI CS| Connected to the LCD, used to enable or disable communication with the specific SPI peripheral|
|GPIO2| Data Command control pin (DC)| Connected to the LCD, Used to control whether the data sent to the display is interpreted as data or command|
|GPIO4| RST| Connected to the LCD, used to reset the peripheral|

### LCD display pins  

| Pin | Pin label  | Description| Use|
| ------------- | ------------- | ------------- | ------------- |
|1| VCC|3.3V power input| Powers the LCD|
|2| GND| Ground|Common ground for the circuit|
|3| CS| LCD chip select signal, low level enable| SPI communication with the ESP|
|4| RST| LCD reset signal, low level reset| Resets the LCD|
|5| D/C|LCD register / data selection signal, high level: register, low level: data| Selects whether data or a command is sent to the LCD|
|6| SDI(MOSI)| SPI bus write data signal| SPI communication, receives data from the controller|
|7| SCK| SPI bus clock signal| SPI communication, used for timing and synchronization|
|8| BL| Backlight |Backlight control, high level lighting, if not controlled, connect 3.3V always bright|
|9|SDO(MISO)| SPI communication, transmits data to the controller|

### Joystick pins  

| Pin | Pin label | Use|
| ------------- | ------------- | -------------|
|1| GND|Ground connection|
|2| VCC| Provides power to the joystick(3.3V)|
|3|VRx |Analog input pin for horizontal movement (X-axis)|
|4|VRy|Analog input pin for vertical movement (Y-axis)|
|5|SW|Digital input pin for the joystick button (used to detect button presses)|

### Hardware image  
 
<img src="https://github.com/user-attachments/assets/d70ff279-6f3f-4aad-9ca6-879dea33a8e6" width="800" height="1000" />   


### LCD Functionality Verification
            In order to verify if the LCD screen is functioning properly, I uploaded a test code. After compiling and uploading the code, the LCD screen displays the '2048' text. This confirms that the LCD is properly connected and the SPI protocol is working correctly.  
            
<img src="https://github.com/user-attachments/assets/0b2ececa-e535-41be-a3f6-5aeb313a654b" width="600" height="400" />   

### Joystick Functionality Verification
            In order to verify if the LCD screen is functioning properly, I uploaded a test code. After compiling and uploading the code, I used the Serial Monitor to check if the X and Y coordinates change based on the joystick movement (N, W, S, E). The X, Y coordinate pair changes correctly according to the movement, indicating that the joystick is working properly. In the image, the first value represents the coordinates when the joystick is not being moved, while the subsequent values correspond to the N, W, S, E movements.  
         
![image](https://github.com/user-attachments/assets/09ffd25b-4785-43ac-8fe6-49471e51d729)


## Software Design  
### Game implementation overview
#### 1. Main menu
   The game starts with a menu where the player can choose to either start the game or view the leaderboard.   
* Start button: starts the game when pressed  

* Leaderboard button: shows the top 10 players and their score, to exit the player needs to swipe up the joystick   

#### 2. Game first initialization
   Once the game begins, the LCD displays a 4x4 grid containing two tiles with a value of 2.   
* Players can move the tiles up, down, right and left using the joystick.

* The score start at 0.

* Pressing the button of the joystick won't have an effect on the game

* Swiping the joystik in any direction moves the tiles accross the grid and also merges them if they have the same value.

#### 3. Gameplay mechanics
* Moving tiles: Players can slide tiles across the grid in one of four directions: up, down, left, or right. All tiles move in the selected direction until they either reach the edge of the grid or collide with another tile. Tiles will continue to move as long as there is space or another tile to collide with. 

* Merging Tiles: Two tiles with the same value merge into one, forming a new tile with double the value.

* New Tile Generation: After each move, a new random tile with a value of 2 or 4 appears on the grid, only if the tiles has moved accross the grid or they have merged.

* Undo Move: Players can undo their previous move by pressing the joystick button. The score will also change to the previous one.

* Score Updates: When tiles merge, the score increases based on the value of the new tile. 

#### 4. Winning and Losing Conditions

* Winning Condition: If the player forms a 2048 tile, they receive a congratulatory message: "YOU WIN!". The game can continue after winning by swiping the joystick in any direction.

* Losing Condition: If the grid is full and no merges are possible, the game is over. However, the player can reenter the game by pressing the undo button.

#### 5. High Score and Name Entry

* If the player decides not to reenter the game, they can exit by swiping the joystick in any direction.

* The player must then enter their name to save their score in the game memory.

* If the player achieves the highest score, the game displays "HIGHSCORE."

#### 6. Returning to the Menu   
The player can return to the menu only after losing and entering their name to be stored. To enter the menu they need to swipe down.   

### Project libraries
#### 1. Arduino library
I used the Arduino.h library because it provides the essential functions needed for developing the program on the ESP32 using the Arduino framework. Functions like setup() and loop() were used for the game logic, millis() for button debouncing, pinMode() to configure the button as an input, and analogRead() to read the joystick position. Additionally, the Arduino.h library enables debugging through the Serial object, which was extremely helpful for monitoring and testing the game during development.   

#### 2. TFT_eSPI library
TFT_eSPI is a feature-rich graphics and fonts library compatible with the Arduino IDE, specifically optimized for 32-bit processors. I chose this library because it provides many predefined functions for drawing on the LCD, which significantly enhances the visual appeal of the game. Some of the functions I used include:

* fillScreen() for setting the background color of the grid,
* drawRect() for creating the grid squares,
* drawCentreString() for displaying text in the center of the screen
* setTextSize() for adjusting the text size.
These functions, along with others, allowed me to create a visually engaging and dynamic user interface for the game.


#### 3. SPI.h library
Although the SPI.h library is already included as a dependency in the TFT_eSPI library, I explicitly included it in my code as well. This is considered good practice, as it ensures compatibility and proper configuration of the SPI communication protocol. SPI.h provides lower-level functions than those available in TFT_eSPI, helping to guarantee successful data transmission between the microcontroller and the display hardware.

#### 4. Preferences library
To store data in the ESP32’s non-volatile memory, I used the Preferences library, which is recommended over the now-deprecated EEPROM library. I used it to store information about the player and their score. Data is stored as key-value pairs, making it easy to access and manage. The main functions I used include:

* begin() to open a namespace in memory for storing player data
* putInt() to save the score
* getString() to retrieve the player’s name
This approach ensured that the player’s data persisted even after restarting the device.

### What's new about the project?
The original 2048 game is traditionally played on a keyboard using the up, down, left, and right arrow keys. In this version, the keyboard is replaced by a joystick, offering a more interactive and engaging control method.

Additionally, the player can save their score and compete to enter the leaderboard. Scores are stored in the non-volatile memory of the microcontroller, ensuring that player progress is preserved even after restarting the system.

By leveraging the TFT_eSPI library for the LCD display, the game features optimized graphics rendering, delivering smooth and visually appealing gameplay.

### Functionalities from labs to game
#### Lab 1: Serial Debugging
I primarily used Serial for debugging purposes throughout the project. One of the main tasks was to verify if the movement of the joystick was correctly captured, by printing the direction to the Serial Monitor. I also used it to ensure that, after pressing the joystick button, the correct menu choice was selected, or that the undo function was triggered properly.

Additionally, I employed the Serial monitor to capture the player’s name after finishing the game, so that I could store it in the microcontroller’s non-volatile memory.

One particular instance where Serial Debugging proved extremely helpful was when I encountered an issue after setting the screen rotation. I was unaware that this would modify the matrix structure. By printing the matrix data to the Serial Monitor, I quickly realized that the matrix was being interpreted as columns and rows, instead of rows and columns as initially expected.

#### Lab 2: Interrupt
To select an option in the menu or trigger the undo function in the game, I attached an interrupt to the joystick’s button. The interrupt is activated on the falling edge (when the button is pressed). The interrupt handler (pressButton) function has three main tasks:

* It notifies that the button was pressed (buttonPressed)
* It checks whether the pressed button corresponds to a valid menu option (optionPressed)
* It changes the game status to "on"(true) if the "Start" option is selected (gameState).

#### Lab 4: ADC
In this project, I use the ADC to read the analog signals from the joystick. The joystick consists of two potentiometers, one for the X-axis and one for the Y-axis, each providing an analog voltage proportional to the joystick's position. For each movement of the joystick, the X-axis and Y-axis will have different values.

To detect the movement, I needed to determine the range (interval) of values for the X-axis and Y-axis corresponding to each direction (N, S, E, W). This allowed me to map the joystick's position to the correct directional movement in the game.

#### Lab 5: SPI
The game uses SPI to transmit data to the LCD. The SPI communication is handled by the TFT_eSPI driver, which manages the entire process of data transfer to the display. One of the key functions in this process is begin_tft_write().

This function is responsible for initializing the SPI communication when writing data to the TFT display. It starts by unlocking the SPI access and then begins a new SPI transaction using the specified settings (such as clock frequency and SPI mode). The Chip Select (CS) pin is pulled low, signaling that the display is ready to receive data. Finally, it sets the SPI bus into write mode to ensure that the microcontroller can transmit data to the display.

### Project framework and functionalities

#### Draw
Files draw.hpp and draw.cpp containes the definitions and the functions neded for the tile and grid display.

* initGrid() creates the 4x4 grid using squares, displays the score and the game title using the functions from the TFT_eSPI library (ex.: drawRect(), setTextSize(), setTextColor()).
* tileColorByNumber(int tileNumber) determines the exact color for each tile number (2, 4, 8, etc. ).
* drawTile(int x, int y, int tileNumber) draws tiles based on the coordinates and the tile number.

#### Tile

The tile.hpp and tile.cpp files are responsible for handling all aspects related to the tiles in the 2048 game. These files manage the coordinates of tiles, their positioning on the grid, and the generation of new tiles.

* coordinates randomCoordinates() generates random coordinates for a new tile 
* gridTileCoordinates getGridCoordinates(int x, int y) calculates the x, y coordinates of the tile for the LCD display
* void randomTileInit() generates the 2 random tiles at the begining of the game
* void win() displays YOU WIN ! on the LCD when the player reaches the 2048 tile

#### Moves

The moves.hpp and moves.cpp files are responsible for handling all aspects related to the movement of the tiles and the state of the grid. These files manage the movement of the tiles on the grid, the return to the next state option and checks if the game is over or not.

* int16_t slideUp(bool finale) function for moving and merging the tiles on the grid 
* int16_t slideDown(bool finale)
* int16_t slideRight(bool finale)
* int16_t slideLeft(bool finale)
* checkGameOver() checks if the game is over and displays GAME OVER on the LCD 
* void moveTile(char direction) receives the direction from the joystick and invokes the appropriate slide function
* lastState() if the joystick's button is pressed, the game returns to the previous tile arrangement

#### Menu
The menu.hpp and menu.cpp files are responsible for handling the spect of the game menu. The menu consists of 2 buttons play and leaderboard.

* void playOptions(int optionNr) displays the menu and highlights the button that is selected by the player

#### Memory
The memory.hpp and memory.cpp files are responsible for handling all aspects related to storing and displaying data stored in the nvs memory of the microcontroller. These files manage the storage of the players name and score and displaying the leaderboard.

* void addPlayer() adds a player at the end of the game 
* void readPlayers() displays all the players and their score
* void resetMemory() clears all the data stored in the NVS memory
* bool highScore(int currentScore)  finds if the current player has the highest score
* void leaderboard() displays the first 10 players with the highest score in the game 

#### Choice
The choice.hpp and choice.cpp files are responsible for handling aspects related to the action of pressing the button, either for starting the game, displaying the leaderboard or using the undo function.

* void buttonPressedChoice() handles button press actions by starting the game, displaying the leaderboard, or performing an undo operation based on the current state and selected options

* void clearMatrix() clears the matrix for the next game

#### Main
The main file is responsible for handling aspects of the game state. If the game is on, the tiles can move. If the game is over, the player can be saved, and an option can be chosen.

* void IRAM_ATTR pressButton() function that handles the interrupt for the joystick’s button  
### Examples of functionalities   
#### Menu
<img src="https://github.com/user-attachments/assets/68926873-d7b8-406e-803e-68f7197b7559" width="400" height="600" />     

#### Leaderboard
<img src="https://github.com/user-attachments/assets/3c42681a-442e-4d8d-8fc2-d8d0f18ba761" width="400" height="600" />   

#### Tiles - Slide left + random tile
<img src="https://github.com/user-attachments/assets/2dd86019-0752-4ac3-ac33-ac33cc07415c" width="600" height="400" />  

#### Game over

<img src="https://github.com/user-attachments/assets/bd832670-554e-4a11-811a-430370f929f8" width="400" height="600" /> 

#### Win

<img src="https://github.com/user-attachments/assets/d63e5aab-5709-46a1-8023-7b520eb9426d" width="400" height="600" /> 

#### User input
<img src="https://github.com/user-attachments/assets/74cc1025-5629-4848-a984-1122c67f79cd" width="400" height="600" /> 

### Video

[![image](https://github.com/user-attachments/assets/33286666-0197-4a55-b100-6917e71f0fe0)](https://youtu.be/rahU1v4jxpo)

## Final Results  
The game is fully functional and ready to be presented. Players can view the leaderboard, start a new game, undo the last grid state, and save their name and score.

## Conclusions  
Developing the game was an interesting and engaging process. Implementing the basic functionalities, such as sliding the tiles across the grid, displaying the grid and tiles on the LCD, and adding the undo function, was relatively easy. However, ensuring a smooth and intuitive game flow posed some challenges.

For example, I wanted to allow the player to undo a move and re-enter the game even after the game was over (when no more moves or merges were possible). Additionally, I had to ensure that when the player first reached the 2048 tile, the "YOU WIN!" message was displayed. Furthermore, if the player chose to undo the move, the "YOU WIN!" message would be shown again the next time they achieved the 2048 tile for the first time.

## Source Code  
View the src folder.
## Journal  
* 26.11.2024 Project decision  
*  1.12.2024 Creating a repository for the project on GitHub
*  9.12.2024 Finished the hardware part of the project
*  14.12.2024 Started writing the code for the game.
*  16.12.2024 Update the GitHub repository with all the hardware information.
*  03.01.2025 Finished the software part
*  07.01.2025 Update the GitHub repository with information about the code
*  08.01.2025 Update the GitHub repository with images of the project
## Bibliography  
[Preferences.h](https://components101.com/modules/joystick-module)  
[TFT_eSPI.h library](https://github.com/Bodmer/TFT_eSPI)  
[LCD information](http://www.lcdwiki.com/3.5inch_SPI_Module_ILI9488_SKU:MSP3520)  
[ESP32 information](https://www.sudo.is/docs/esphome/boards/esp32nodemcu/)  
[Joystick and esp32](https://esp32io.com/tutorials/esp32-joystick)  
